

/* define DEBUG for debugging output (obviously ;-)) */
#if 0
#define DEBUG
#endif

#include <common.h>
#include <i2c.h>
#include <command.h>
#include <post.h>
#include <serial.h>
#include <malloc.h>

#include <linux/types.h>
#include <linux/string.h>	/* for strdup */

DECLARE_GLOBAL_DATA_PTR;

static void kbd_init (void);
static int compare_magic (uchar *kbd_data, uchar *str);

/*--------------------- Local macros and constants --------------------*/
#define	_NOT_USED_	0xFFFFFFFF

/*------------------------- Keyboard controller -----------------------*/
/* command codes */
#define	KEYBD_CMD_READ_KEYS	0x01
#define KEYBD_CMD_READ_VERSION	0x02
#define KEYBD_CMD_READ_STATUS	0x03
#define KEYBD_CMD_RESET_ERRORS	0x10

/* status codes */
#define KEYBD_STATUS_MASK	0x3F
#define	KEYBD_STATUS_H_RESET	0x20
#define KEYBD_STATUS_BROWNOUT	0x10
#define KEYBD_STATUS_WD_RESET	0x08
#define KEYBD_STATUS_OVERLOAD	0x04
#define KEYBD_STATUS_ILLEGAL_WR	0x02
#define KEYBD_STATUS_ILLEGAL_RD	0x01

/* Number of bytes returned from Keyboard Controller */
#define KEYBD_VERSIONLEN	2	/* version information */

#define	KEYBD_DATALEN		6	/* normal key scan data */

/* maximum number of "magic" key codes that can be assigned */

static uchar kbd_addr = CONFIG_SYS_I2C_KEYBD_ADDR;

static uchar *key_match (uchar *);

#define	KEYBD_SET_DEBUGMODE	'#'	/* Magic key to enable debug output */

int board_postclk_init (void)
{
	kbd_init();

	return (0);
}

static void kbd_init (void)
{
	uchar kbd_data[KEYBD_DATALEN];
	uchar tmp_data[KEYBD_DATALEN];
	uchar val, errcd;
	int i;

	i2c_init (CONFIG_SYS_I2C_SPEED, CONFIG_SYS_I2C_SLAVE);

	gd->kbd_status = 0;

	/* Forced by PIC. Delays <= 175us loose */
	udelay(1000);

	/* Read initial keyboard error code */
	val = KEYBD_CMD_READ_STATUS;
	i2c_write (kbd_addr, 0, 0, &val, 1);
	i2c_read (kbd_addr, 0, 0, &errcd, 1);
	/* clear unused bits */
	errcd &= KEYBD_STATUS_MASK;
	/* clear "irrelevant" bits. Recommended by Martin Rajek, LWN */
	errcd &= ~(KEYBD_STATUS_H_RESET|KEYBD_STATUS_BROWNOUT);
	if (errcd) {
		gd->kbd_status |= errcd << 8;
	}
	/* Reset error code and verify */
	val = KEYBD_CMD_RESET_ERRORS;
	i2c_write (kbd_addr, 0, 0, &val, 1);
	udelay(1000);	/* delay NEEDED by keyboard PIC !!! */

	val = KEYBD_CMD_READ_STATUS;
	i2c_write (kbd_addr, 0, 0, &val, 1);
	i2c_read (kbd_addr, 0, 0, &val, 1);

	val &= KEYBD_STATUS_MASK;	/* clear unused bits */
	if (val) {			/* permanent error, report it */
		gd->kbd_status |= val;
		return;
	}

	/*
	 * Read current keyboard state.
	 *
	 * After the error reset it may take some time before the
	 * keyboard PIC picks up a valid keyboard scan - the total
	 * scan time is approx. 1.6 ms (information by Martin Rajek,
	 * 28 Sep 2002). We read a couple of times for the keyboard
	 * to stabilize, using a big enough delay.
	 * 10 times should be enough. If the data is still changing,
	 * we use what we get :-(
	 */

	memset (tmp_data, 0xFF, KEYBD_DATALEN);	/* impossible value */
	for (i=0; i<10; ++i) {
		val = KEYBD_CMD_READ_KEYS;
		i2c_write (kbd_addr, 0, 0, &val, 1);
		i2c_read (kbd_addr, 0, 0, kbd_data, KEYBD_DATALEN);

		if (memcmp(kbd_data, tmp_data, KEYBD_DATALEN) == 0) {
			/* consistent state, done */
			break;
		}
		/* remeber last state, delay, and retry */
		memcpy (tmp_data, kbd_data, KEYBD_DATALEN);
		udelay (5000);
	}
}

int misc_init_r_kbd (void)
{
	uchar kbd_data[KEYBD_DATALEN];
	char keybd_env[2 * KEYBD_DATALEN + 1];
	uchar kbd_init_status = gd->kbd_status >> 8;
	uchar kbd_status = gd->kbd_status;
	uchar val;
	char *str;
	int i;

	if (kbd_init_status) {
		printf ("KEYBD: Error %02X\n", kbd_init_status);
	}
	if (kbd_status) {		/* permanent error, report it */
		printf ("*** Keyboard error code %02X ***\n", kbd_status);
		sprintf (keybd_env, "%02X", kbd_status);
		setenv ("keybd", keybd_env);
		return 0;
	}

	/*
	 * Now we know that we have a working  keyboard,  so  disable
	 * all output to the LCD except when a key press is detected.
	 */

	if ((console_assign (stdout, "serial") < 0) ||
		(console_assign (stderr, "serial") < 0)) {
		printf ("Can't assign serial port as output device\n");
	}

	/* Read Version */
	val = KEYBD_CMD_READ_VERSION;
	i2c_write (kbd_addr, 0, 0, &val, 1);
	i2c_read (kbd_addr, 0, 0, kbd_data, KEYBD_VERSIONLEN);
	printf ("KEYBD: Version %d.%d\n", kbd_data[0], kbd_data[1]);

	/* Read current keyboard state */
	val = KEYBD_CMD_READ_KEYS;
	i2c_write (kbd_addr, 0, 0, &val, 1);
	i2c_read (kbd_addr, 0, 0, kbd_data, KEYBD_DATALEN);

	for (i = 0; i < KEYBD_DATALEN; ++i) {
		sprintf (keybd_env + i + i, "%02X", kbd_data[i]);
	}
	setenv ("keybd", keybd_env);

	str = strdup ((char *)key_match (kbd_data));	/* decode keys */
#ifdef KEYBD_SET_DEBUGMODE
	if (kbd_data[0] == KEYBD_SET_DEBUGMODE) {	/* set debug mode */
		if ((console_assign (stdout, "lcd") < 0) ||
			(console_assign (stderr, "lcd") < 0)) {
			printf ("Can't assign LCD display as output device\n");
		}
	}
#endif /* KEYBD_SET_DEBUGMODE */
#ifdef CONFIG_PREBOOT	/* automatically configure "preboot" command on key match */
	setenv ("preboot", str);	/* set or delete definition */
#endif /* CONFIG_PREBOOT */
	if (str != NULL) {
		free (str);
	}
	return (0);
}

#ifdef CONFIG_PREBOOT

static uchar kbd_magic_prefix[] = "key_magic";
static uchar kbd_command_prefix[] = "key_cmd";

static int compare_magic (uchar *kbd_data, uchar *str)
{
	uchar compare[KEYBD_DATALEN-1];
	char *nxt;
	int i;

	/* Don't include modifier byte */
	memcpy (compare, kbd_data+1, KEYBD_DATALEN-1);

	for (; str != NULL; str = (*nxt) ? (uchar *)(nxt+1) : (uchar *)nxt) {
		uchar c;
		int k;

		c = (uchar) simple_strtoul ((char *)str, (char **) (&nxt), 16);

		if (str == (uchar *)nxt) {	/* invalid character */
			break;
		}

		/*
		 * Check if this key matches the input.
		 * Set matches to zero, so they match only once
		 * and we can find duplicates or extra keys
		 */
		for (k = 0; k < sizeof(compare); ++k) {
			if (compare[k] == '\0')	/* only non-zero entries */
				continue;
			if (c == compare[k]) {	/* found matching key */
				compare[k] = '\0';
				break;
			}
		}
		if (k == sizeof(compare)) {
			return -1;		/* unmatched key */
		}
	}

	/*
	 * A full match leaves no keys in the `compare' array,
	 */
	for (i = 0; i < sizeof(compare); ++i) {
		if (compare[i])
		{
			return -1;
		}
	}

	return 0;
}

static uchar *key_match (uchar *kbd_data)
{
	char magic[sizeof (kbd_magic_prefix) + 1];
	uchar *suffix;
	char *kbd_magic_keys;

	/*
	 * The following string defines the characters that can pe appended
	 * to "key_magic" to form the names of environment variables that
	 * hold "magic" key codes, i. e. such key codes that can cause
	 * pre-boot actions. If the string is empty (""), then only
	 * "key_magic" is checked (old behaviour); the string "125" causes
	 * checks for "key_magic1", "key_magic2" and "key_magic5", etc.
	 */
	if ((kbd_magic_keys = getenv ("magic_keys")) == NULL)
		kbd_magic_keys = "";

	/* loop over all magic keys;
	 * use '\0' suffix in case of empty string
	 */
	for (suffix=(uchar *)kbd_magic_keys; *suffix || suffix==(uchar *)kbd_magic_keys; ++suffix) {
		sprintf (magic, "%s%c", kbd_magic_prefix, *suffix);
		debug ("### Check magic \"%s\"\n", magic);
		if (compare_magic(kbd_data, (uchar *)getenv(magic)) == 0) {
			char cmd_name[sizeof (kbd_command_prefix) + 1];
			char *cmd;

			sprintf (cmd_name, "%s%c", kbd_command_prefix, *suffix);

			cmd = getenv (cmd_name);
			debug ("### Set PREBOOT to $(%s): \"%s\"\n",
					cmd_name, cmd ? cmd : "<<NULL>>");
			*kbd_data = *suffix;
			return ((uchar *)cmd);
		}
	}
	debug ("### Delete PREBOOT\n");
	*kbd_data = '\0';
	return (NULL);
}
#endif /* CONFIG_PREBOOT */

int do_kbd (cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
	uchar kbd_data[KEYBD_DATALEN];
	char keybd_env[2 * KEYBD_DATALEN + 1];
	uchar val;
	int i;

#if 0 /* Done in kbd_init */
	i2c_init (CONFIG_SYS_I2C_SPEED, CONFIG_SYS_I2C_SLAVE);
#endif

	/* Read keys */
	val = KEYBD_CMD_READ_KEYS;
	i2c_write (kbd_addr, 0, 0, &val, 1);
	i2c_read (kbd_addr, 0, 0, kbd_data, KEYBD_DATALEN);

	puts ("Keys:");
	for (i = 0; i < KEYBD_DATALEN; ++i) {
		sprintf (keybd_env + i + i, "%02X", kbd_data[i]);
		printf (" %02x", kbd_data[i]);
	}
	putc ('\n');
	setenv ("keybd", keybd_env);
	return 0;
}

U_BOOT_CMD(
	kbd,	1,	1,	do_kbd,
	"read keyboard status",
	""
);

/*----------------------------- Utilities -----------------------------*/

#ifdef CONFIG_POST
int post_hotkeys_pressed(void)
{
	uchar kbd_data[KEYBD_DATALEN];
	uchar val;

	/* Read keys */
	val = KEYBD_CMD_READ_KEYS;
	i2c_write (kbd_addr, 0, 0, &val, 1);
	i2c_read (kbd_addr, 0, 0, kbd_data, KEYBD_DATALEN);

	return (compare_magic(kbd_data, (uchar *)CONFIG_POST_KEY_MAGIC) == 0);
}
#endif
