
/* taken from arch/powerpc/kernel/ppc-stub.c */



#include <common.h>

#include <kgdb.h>
#include <command.h>

#undef KGDB_DEBUG

#define BUFMAX 1024
static char remcomInBuffer[BUFMAX];
static char remcomOutBuffer[BUFMAX];
static char remcomRegBuffer[BUFMAX];

static int initialized = 0;
static int kgdb_active = 0, first_entry = 1;
static struct pt_regs entry_regs;
static long error_jmp_buf[BUFMAX/2];
static int longjmp_on_fault = 0;
#ifdef KGDB_DEBUG
static int kdebug = 1;
#endif

static const char hexchars[]="0123456789abcdef";

/* Convert ch from a hex digit to an int */
static int
hex(unsigned char ch)
{
	if (ch >= 'a' && ch <= 'f')
		return ch-'a'+10;
	if (ch >= '0' && ch <= '9')
		return ch-'0';
	if (ch >= 'A' && ch <= 'F')
		return ch-'A'+10;
	return -1;
}

static unsigned char *
mem2hex(char *mem, char *buf, int count)
{
	char *tmp;
	unsigned char ch;

	/*
	 * We use the upper half of buf as an intermediate buffer for the
	 * raw memory copy.  Hex conversion will work against this one.
	 */
	tmp = buf + count;
	longjmp_on_fault = 1;

	memcpy(tmp, mem, count);

	while (count-- > 0) {
		ch = *tmp++;
		*buf++ = hexchars[ch >> 4];
		*buf++ = hexchars[ch & 0xf];
	}
	*buf = 0;
	longjmp_on_fault = 0;
	return (unsigned char *)buf;
}

static char *
hex2mem(char *buf, char *mem, int count)
{
	int hexValue;
	char *tmp_raw, *tmp_hex;

	/*
	 * We use the upper half of buf as an intermediate buffer for the
	 * raw memory that is converted from hex.
	 */
	tmp_raw = buf + count * 2;
	tmp_hex = tmp_raw - 1;

	longjmp_on_fault = 1;
	while (tmp_hex >= buf) {
		tmp_raw--;
		hexValue = hex(*tmp_hex--);
		if (hexValue < 0)
			kgdb_error(KGDBERR_NOTHEXDIG);
		*tmp_raw = hexValue;
		hexValue = hex(*tmp_hex--);
		if (hexValue < 0)
			kgdb_error(KGDBERR_NOTHEXDIG);
		*tmp_raw |= hexValue << 4;

	}

	memcpy(mem, tmp_raw, count);

	kgdb_flush_cache_range((void *)mem, (void *)(mem+count));
	longjmp_on_fault = 0;

	return buf;
}

static int
hexToInt(char **ptr, int *intValue)
{
	int numChars = 0;
	int hexValue;

	*intValue = 0;

	longjmp_on_fault = 1;
	while (**ptr) {
		hexValue = hex(**ptr);
		if (hexValue < 0)
			break;

		*intValue = (*intValue << 4) | hexValue;
		numChars ++;

		(*ptr)++;
	}
	longjmp_on_fault = 0;

	return (numChars);
}

/* scan for the sequence $<data>#<checksum>     */
static void
getpacket(char *buffer)
{
	unsigned char checksum;
	unsigned char xmitcsum;
	int i;
	int count;
	unsigned char ch;

	do {
		/* wait around for the start character, ignore all other
		 * characters */
		while ((ch = (getDebugChar() & 0x7f)) != '$') {
#ifdef KGDB_DEBUG
			if (kdebug)
				putc(ch);
#endif
			;
		}

		checksum = 0;
		xmitcsum = -1;

		count = 0;

		/* now, read until a # or end of buffer is found */
		while (count < BUFMAX) {
			ch = getDebugChar() & 0x7f;
			if (ch == '#')
				break;
			checksum = checksum + ch;
			buffer[count] = ch;
			count = count + 1;
		}

		if (count >= BUFMAX)
			continue;

		buffer[count] = 0;

		if (ch == '#') {
			xmitcsum = hex(getDebugChar() & 0x7f) << 4;
			xmitcsum |= hex(getDebugChar() & 0x7f);
			if (checksum != xmitcsum)
				putDebugChar('-');	/* failed checksum */
			else {
				putDebugChar('+'); /* successful transfer */
				/* if a sequence char is present, reply the ID */
				if (buffer[2] == ':') {
					putDebugChar(buffer[0]);
					putDebugChar(buffer[1]);
					/* remove sequence chars from buffer */
					count = strlen(buffer);
					for (i=3; i <= count; i++)
						buffer[i-3] = buffer[i];
				}
			}
		}
	} while (checksum != xmitcsum);
}

/* send the packet in buffer.  */
static void
putpacket(unsigned char *buffer)
{
	unsigned char checksum;
	int count;
	unsigned char ch, recv;

	/*  $<packet info>#<checksum>. */
	do {
		putDebugChar('$');
		checksum = 0;
		count = 0;

		while ((ch = buffer[count])) {
			putDebugChar(ch);
			checksum += ch;
			count += 1;
		}

		putDebugChar('#');
		putDebugChar(hexchars[checksum >> 4]);
		putDebugChar(hexchars[checksum & 0xf]);
		recv = getDebugChar();
	} while ((recv & 0x7f) != '+');
}

static int
handle_exception (struct pt_regs *regs)
{
	int addr;
	int length;
	char *ptr;
	kgdb_data kd;
	int i;

	if (!initialized) {
		printf("kgdb: exception before kgdb is initialized! huh?\n");
		return (0);
	}

	/* probably should check which exception occured as well */
	if (longjmp_on_fault) {
		longjmp_on_fault = 0;
		kgdb_longjmp(error_jmp_buf, KGDBERR_MEMFAULT);
		panic("kgdb longjump failed!\n");
	}

	if (kgdb_active) {
		printf("kgdb: unexpected exception from within kgdb\n");
		return (0);
	}
	kgdb_active = 1;

	kgdb_interruptible(0);

	printf("kgdb: handle_exception; trap [0x%x]\n", kgdb_trap(regs));

	if (kgdb_setjmp(error_jmp_buf) != 0)
		panic("kgdb: error or fault in entry init!\n");

	kgdb_enter(regs, &kd);

	if (first_entry) {
		/*
		 * the first time we enter kgdb, we save the processor
		 * state so that we can return to the monitor if the
		 * remote end quits gdb (or at least, tells us to quit
		 * with the 'k' packet)
		 */
		entry_regs = *regs;
		first_entry = 0;
	}

	ptr = remcomOutBuffer;

	*ptr++ = 'T';

	*ptr++ = hexchars[kd.sigval >> 4];
	*ptr++ = hexchars[kd.sigval & 0xf];

	for (i = 0; i < kd.nregs; i++) {
		kgdb_reg *rp = &kd.regs[i];

		*ptr++ = hexchars[rp->num >> 4];
		*ptr++ = hexchars[rp->num & 0xf];
		*ptr++ = ':';
		ptr = (char *)mem2hex((char *)&rp->val, ptr, 4);
		*ptr++ = ';';
	}

	*ptr = 0;

#ifdef KGDB_DEBUG
	if (kdebug)
		printf("kgdb: remcomOutBuffer: %s\n", remcomOutBuffer);
#endif

	putpacket((unsigned char *)&remcomOutBuffer);

	while (1) {
		volatile int errnum;

		remcomOutBuffer[0] = 0;

		getpacket(remcomInBuffer);
		ptr = &remcomInBuffer[1];

#ifdef KGDB_DEBUG
		if (kdebug)
			printf("kgdb:  remcomInBuffer: %s\n", remcomInBuffer);
#endif

		errnum = kgdb_setjmp(error_jmp_buf);

		if (errnum == 0) switch (remcomInBuffer[0]) {

		case '?':               /* report most recent signal */
			remcomOutBuffer[0] = 'S';
			remcomOutBuffer[1] = hexchars[kd.sigval >> 4];
			remcomOutBuffer[2] = hexchars[kd.sigval & 0xf];
			remcomOutBuffer[3] = 0;
			break;

#ifdef KGDB_DEBUG
		case 'd':
			/* toggle debug flag */
			kdebug ^= 1;
			break;
#endif

		case 'g':	/* return the value of the CPU registers. */
			length = kgdb_getregs(regs, remcomRegBuffer, BUFMAX);
			mem2hex(remcomRegBuffer, remcomOutBuffer, length);
			break;

		case 'G':   /* set the value of the CPU registers */
			length = strlen(ptr);
			if ((length & 1) != 0) kgdb_error(KGDBERR_BADPARAMS);
			hex2mem(ptr, remcomRegBuffer, length/2);
			kgdb_putregs(regs, remcomRegBuffer, length/2);
			strcpy(remcomOutBuffer,"OK");
			break;

		case 'm':	/* mAA..AA,LLLL  Read LLLL bytes at address AA..AA */
				/* Try to read %x,%x.  */

			if (hexToInt(&ptr, &addr)
			    && *ptr++ == ','
			    && hexToInt(&ptr, &length))	{
				mem2hex((char *)addr, remcomOutBuffer, length);
			} else {
				kgdb_error(KGDBERR_BADPARAMS);
			}
			break;

		case 'M': /* MAA..AA,LLLL: Write LLLL bytes at address AA.AA return OK */
			/* Try to read '%x,%x:'.  */

			if (hexToInt(&ptr, &addr)
			    && *ptr++ == ','
			    && hexToInt(&ptr, &length)
			    && *ptr++ == ':') {
				hex2mem(ptr, (char *)addr, length);
				strcpy(remcomOutBuffer, "OK");
			} else {
				kgdb_error(KGDBERR_BADPARAMS);
			}
			break;


		case 'k':    /* kill the program, actually return to monitor */
			kd.extype = KGDBEXIT_KILL;
			*regs = entry_regs;
			first_entry = 1;
			goto doexit;

		case 'C':    /* CSS  continue with signal SS */
			*ptr = '\0';	/* ignore the signal number for now */
			/* fall through */

		case 'c':    /* cAA..AA  Continue; address AA..AA optional */
			/* try to read optional parameter, pc unchanged if no parm */
			kd.extype = KGDBEXIT_CONTINUE;

			if (hexToInt(&ptr, &addr)) {
				kd.exaddr = addr;
				kd.extype |= KGDBEXIT_WITHADDR;
			}

			goto doexit;

		case 'S':    /* SSS  single step with signal SS */
			*ptr = '\0';	/* ignore the signal number for now */
			/* fall through */

		case 's':
			kd.extype = KGDBEXIT_SINGLE;

			if (hexToInt(&ptr, &addr)) {
				kd.exaddr = addr;
				kd.extype |= KGDBEXIT_WITHADDR;
			}

		doexit:
			kgdb_flush_cache_all();
			kgdb_exit(regs, &kd);
			kgdb_active = 0;
			kgdb_interruptible(1);
			return (1);

		case 'r':		/* Reset (if user process..exit ???)*/
			panic("kgdb reset.");
			break;

		case 'P':    /* Pr=v  set reg r to value v (r and v are hex) */
			if (hexToInt(&ptr, &addr)
			    && *ptr++ == '='
			    && ((length = strlen(ptr)) & 1) == 0) {
				hex2mem(ptr, remcomRegBuffer, length/2);
				kgdb_putreg(regs, addr,
					remcomRegBuffer, length/2);
				strcpy(remcomOutBuffer,"OK");
			} else {
				kgdb_error(KGDBERR_BADPARAMS);
			}
			break;
		}			/* switch */

		if (errnum != 0)
			sprintf(remcomOutBuffer, "E%02d", errnum);

#ifdef KGDB_DEBUG
		if (kdebug)
			printf("kgdb: remcomOutBuffer: %s\n", remcomOutBuffer);
#endif

		/* reply to the request */
		putpacket((unsigned char *)&remcomOutBuffer);

	} /* while(1) */
}

void
kgdb_init(void)
{
	kgdb_serial_init();
	debugger_exception_handler = handle_exception;
	initialized = 1;

	putDebugStr("kgdb ready\n");
	puts("ready\n");
}

void
kgdb_error(int errnum)
{
	longjmp_on_fault = 0;
	kgdb_longjmp(error_jmp_buf, errnum);
	panic("kgdb_error: longjmp failed!\n");
}

int
kgdb_output_string (const char* s, unsigned int count)
{
	char buffer[512];

	count = (count <= (sizeof(buffer) / 2 - 2))
		? count : (sizeof(buffer) / 2 - 2);

	buffer[0] = 'O';
	mem2hex ((char *)s, &buffer[1], count);
	putpacket((unsigned char *)&buffer);

	return 1;
}

void
breakpoint(void)
{
	if (!initialized) {
		printf("breakpoint() called b4 kgdb init\n");
		return;
	}

	kgdb_breakpoint(0, 0);
}

int
do_kgdb(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
    printf("Entering KGDB mode via exception handler...\n\n");
    kgdb_breakpoint(argc - 1, argv + 1);
    printf("\nReturned from KGDB mode\n");
    return 0;
}

U_BOOT_CMD(
	kgdb, CONFIG_SYS_MAXARGS, 1,	do_kgdb,
	"enter gdb remote debug mode",
	"[arg0 arg1 .. argN]\n"
	"    - executes a breakpoint so that kgdb mode is\n"
	"      entered via the exception handler. To return\n"
	"      to the monitor, the remote gdb debugger must\n"
	"      execute a \"continue\" or \"quit\" command.\n"
	"\n"
	"      if a program is loaded by the remote gdb, any args\n"
	"      passed to the kgdb command are given to the loaded\n"
	"      program if it is executed (see the \"hello_world\"\n"
	"      example program in the U-Boot examples directory)."
);
