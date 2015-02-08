

#include <common.h>
#include <command.h>
#include <malloc.h>
#include <timestamp.h>
#include <version.h>
#include <watchdog.h>
#include <stdio_dev.h>

DECLARE_GLOBAL_DATA_PTR;

const char version_string[] = U_BOOT_VERSION " ("U_BOOT_DATE" - "U_BOOT_TIME")";

#ifdef CONFIG_SYS_GPIO_0
extern int gpio_init (void);
#endif
#ifdef CONFIG_SYS_INTC_0
extern int interrupts_init (void);
#endif
#if defined(CONFIG_CMD_NET)
extern int eth_init (bd_t * bis);
#endif
#ifdef CONFIG_SYS_TIMER_0
extern int timer_init (void);
#endif
#ifdef CONFIG_SYS_FSL_2
extern void fsl_init2 (void);
#endif

typedef int (init_fnc_t) (void);

init_fnc_t *init_sequence[] = {
	env_init,
	serial_init,
#ifdef CONFIG_SYS_GPIO_0
	gpio_init,
#endif
#ifdef CONFIG_SYS_INTC_0
	interrupts_init,
#endif
#ifdef CONFIG_SYS_TIMER_0
	timer_init,
#endif
#ifdef CONFIG_SYS_FSL_2
	fsl_init2,
#endif
	NULL,
};

void board_init (void)
{
	bd_t *bd;
	init_fnc_t **init_fnc_ptr;
	gd = (gd_t *) CONFIG_SYS_GBL_DATA_OFFSET;
	char *s;
#if defined(CONFIG_CMD_FLASH)
	ulong flash_size = 0;
#endif
	asm ("nop");	/* FIXME gd is not initialize - wait */
	memset ((void *)gd, 0, CONFIG_SYS_GBL_DATA_SIZE);
	gd->bd = (bd_t *) (gd + 1);	/* At end of global data */
	gd->baudrate = CONFIG_BAUDRATE;
	bd = gd->bd;
	bd->bi_baudrate = CONFIG_BAUDRATE;
	bd->bi_memstart = CONFIG_SYS_SDRAM_BASE;
	bd->bi_memsize = CONFIG_SYS_SDRAM_SIZE;
	gd->flags |= GD_FLG_RELOC;      /* tell others: relocation done */

	/*
	 * The Malloc area is immediately below the monitor copy in DRAM
	 * aka CONFIG_SYS_MONITOR_BASE - Note there is no need for reloc_off
	 * as our monitory code is run from SDRAM
	 */
	mem_malloc_init (CONFIG_SYS_MALLOC_BASE, CONFIG_SYS_MALLOC_LEN);

	for (init_fnc_ptr = init_sequence; *init_fnc_ptr; ++init_fnc_ptr) {
		WATCHDOG_RESET ();
		if ((*init_fnc_ptr) () != 0) {
			hang ();
		}
	}

	puts ("SDRAM :\n");
	printf ("\t\tIcache:%s\n", icache_status() ? "ON" : "OFF");
	printf ("\t\tDcache:%s\n", dcache_status() ? "ON" : "OFF");
	printf ("\tU-Boot Start:0x%08x\n", TEXT_BASE);

#if defined(CONFIG_CMD_FLASH)
	puts ("FLASH: ");
	bd->bi_flashstart = CONFIG_SYS_FLASH_BASE;
	if (0 < (flash_size = flash_init ())) {
		bd->bi_flashsize = flash_size;
		bd->bi_flashoffset = CONFIG_SYS_FLASH_BASE + flash_size;
# ifdef CONFIG_SYS_FLASH_CHECKSUM
		print_size (flash_size, "");
		/*
		 * Compute and print flash CRC if flashchecksum is set to 'y'
		 *
		 * NOTE: Maybe we should add some WATCHDOG_RESET()? XXX
		 */
		s = getenv ("flashchecksum");
		if (s && (*s == 'y')) {
			printf ("  CRC: %08X",
				crc32 (0, (const unsigned char *) CONFIG_SYS_FLASH_BASE, flash_size)
			);
		}
		putc ('\n');
# else	/* !CONFIG_SYS_FLASH_CHECKSUM */
		print_size (flash_size, "\n");
# endif /* CONFIG_SYS_FLASH_CHECKSUM */
	} else {
		puts ("Flash init FAILED");
		bd->bi_flashstart = 0;
		bd->bi_flashsize = 0;
		bd->bi_flashoffset = 0;
	}
#endif

	/* relocate environment function pointers etc. */
	env_relocate ();

	/* Initialize stdio devices */
	stdio_init ();

	if ((s = getenv ("loadaddr")) != NULL) {
		load_addr = simple_strtoul (s, NULL, 16);
	}

#if defined(CONFIG_CMD_NET)
	/* IP Address */
	bd->bi_ip_addr = getenv_IPaddr ("ipaddr");
	eth_init (bd);
#endif

	/* main_loop */
	for (;;) {
		WATCHDOG_RESET ();
		main_loop ();
	}
}

void hang (void)
{
	puts ("### ERROR ### Please RESET the board ###\n");
	for (;;) ;
}
