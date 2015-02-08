

#include <common.h>
#include <watchdog.h>
#include <command.h>
#include <stdio_dev.h>
#include <timestamp.h>
#include <version.h>
#include <malloc.h>
#include <net.h>
#include <ide.h>
#include <serial.h>
#include <asm/u-boot-i386.h>
#include <elf.h>

#ifdef CONFIG_BITBANGMII
#include <miiphy.h>
#endif

DECLARE_GLOBAL_DATA_PTR;

/* Exports from the Linker Script */
extern ulong _i386boot_text_start;
extern ulong _i386boot_rel_dyn_start;
extern ulong _i386boot_rel_dyn_end;
extern ulong _i386boot_bss_start;
extern ulong _i386boot_bss_size;

void ram_bootstrap (void *, ulong);

const char version_string[] =
	U_BOOT_VERSION" (" U_BOOT_DATE " - " U_BOOT_TIME ")";

static int init_baudrate (void)
{
	char tmp[64];	/* long enough for environment variables */
	int i = getenv_r("baudrate", tmp, 64);

	gd->baudrate = (i != 0)
			? (int) simple_strtoul (tmp, NULL, 10)
			: CONFIG_BAUDRATE;

	return (0);
}

static int display_banner (void)
{

	printf ("\n\n%s\n\n", version_string);

	return (0);
}

static int display_dram_config (void)
{
	int i;

	puts ("DRAM Configuration:\n");

	for (i=0; i<CONFIG_NR_DRAM_BANKS; i++) {
		printf ("Bank #%d: %08lx ", i, gd->bd->bi_dram[i].start);
		print_size (gd->bd->bi_dram[i].size, "\n");
	}

	return (0);
}

static void display_flash_config (ulong size)
{
	puts ("Flash: ");
	print_size (size, "\n");
}



typedef int (init_fnc_t) (void);

init_fnc_t *init_sequence[] = {
	cpu_init_r,		/* basic cpu dependent setup */
	board_early_init_r,	/* basic board dependent setup */
	dram_init,		/* configure available RAM banks */
	interrupt_init,		/* set up exceptions */
	timer_init,
	env_init,		/* initialize environment */
	init_baudrate,		/* initialze baudrate settings */
	serial_init,		/* serial communications setup */
	display_banner,
	display_dram_config,

	NULL,
};

static gd_t gd_data;
gd_t *gd;

void board_init_f (ulong stack_limit)
{
	void *text_start = &_i386boot_text_start;
	void *u_boot_cmd_end = &__u_boot_cmd_end;
	Elf32_Rel *rel_dyn_start = (Elf32_Rel *)&_i386boot_rel_dyn_start;
	Elf32_Rel *rel_dyn_end = (Elf32_Rel *)&_i386boot_rel_dyn_end;
	void *bss_start = &_i386boot_bss_start;
	ulong bss_size = (ulong)&_i386boot_bss_size;

	ulong uboot_size;
	void *dest_addr;
	ulong rel_offset;
	Elf32_Rel *re;

	void (*start_func)(void *, ulong);

	uboot_size = (ulong)u_boot_cmd_end - (ulong)text_start;
	dest_addr  = (void *)stack_limit - (uboot_size + (ulong)bss_size);
	rel_offset = text_start - dest_addr;
	start_func = ram_bootstrap - rel_offset;

	/* First stage CPU initialization */
	if (cpu_init_f() != 0)
		hang();

	/* First stage Board initialization */
	if (board_early_init_f() != 0)
		hang();

	/* Copy U-Boot into RAM */
	memcpy(dest_addr, text_start, uboot_size);

	/* Clear BSS */
	memset(bss_start - rel_offset,	0, bss_size);

	/* Perform relocation adjustments */
	for (re = rel_dyn_start; re < rel_dyn_end; re++)
	{
		if (re->r_offset >= TEXT_BASE)
			if (*(ulong *)re->r_offset >= TEXT_BASE)
				*(ulong *)(re->r_offset - rel_offset) -= (Elf32_Addr)rel_offset;
	}

	/* Enter the relocated U-Boot! */
	start_func(dest_addr, rel_offset);
	/* NOTREACHED - board_init_f() does not return */
	while(1);
}

void ram_bootstrap (void *dest_addr, ulong rel_offset)
{
	/* compiler optimization barrier needed for GCC >= 3.4 */
	__asm__ __volatile__("": : :"memory");

	/* tell others: relocation done */
	gd_data.reloc_off = rel_offset;
	gd_data.flags |= GD_FLG_RELOC;

	board_init_r(&gd_data, (ulong)dest_addr);
}

void board_init_r(gd_t *id, ulong dest_addr)
{
	char *s;
	int i;
	ulong size;
	static bd_t bd_data;
	init_fnc_t **init_fnc_ptr;

	show_boot_progress(0x21);

	gd = id;
	/* compiler optimization barrier needed for GCC >= 3.4 */
	__asm__ __volatile__("": : :"memory");

	gd->bd = &bd_data;
	memset (gd->bd, 0, sizeof (bd_t));
	show_boot_progress(0x22);

	gd->baudrate =  CONFIG_BAUDRATE;

	mem_malloc_init((((ulong)dest_addr - CONFIG_SYS_MALLOC_LEN)+3)&~3,
			CONFIG_SYS_MALLOC_LEN);

	for (init_fnc_ptr = init_sequence, i=0; *init_fnc_ptr; ++init_fnc_ptr, i++) {
		show_boot_progress(0xa130|i);

		if ((*init_fnc_ptr)() != 0) {
			hang ();
		}
	}
	show_boot_progress(0x23);

#ifdef CONFIG_SERIAL_MULTI
	serial_initialize();
#endif
	/* configure available FLASH banks */
	size = flash_init();
	display_flash_config(size);
	show_boot_progress(0x24);

	show_boot_progress(0x25);

	/* initialize environment */
	env_relocate ();
	show_boot_progress(0x26);


#ifdef CONFIG_CMD_NET
	/* IP Address */
	bd_data.bi_ip_addr = getenv_IPaddr ("ipaddr");
#endif

#if defined(CONFIG_PCI)
	/*
	 * Do pci configuration
	 */
	pci_init();
#endif

	show_boot_progress(0x27);


	stdio_init ();

	jumptable_init ();

	/* Initialize the console (after the relocation and devices init) */
	console_init_r();

#ifdef CONFIG_MISC_INIT_R
	/* miscellaneous platform dependent initialisations */
	misc_init_r();
#endif

#if defined(CONFIG_CMD_PCMCIA) && !defined(CONFIG_CMD_IDE)
	WATCHDOG_RESET();
	puts ("PCMCIA:");
	pcmcia_init();
#endif

#if defined(CONFIG_CMD_KGDB)
	WATCHDOG_RESET();
	puts("KGDB:  ");
	kgdb_init();
#endif

	/* enable exceptions */
	enable_interrupts();
	show_boot_progress(0x28);

	/* Must happen after interrupts are initialized since
	 * an irq handler gets installed
	 */
#ifdef CONFIG_SERIAL_SOFTWARE_FIFO
	serial_buffered_init();
#endif

#ifdef CONFIG_STATUS_LED
	status_led_set (STATUS_LED_BOOT, STATUS_LED_BLINKING);
#endif

	udelay(20);

	set_timer (0);

	/* Initialize from environment */
	if ((s = getenv ("loadaddr")) != NULL) {
		load_addr = simple_strtoul (s, NULL, 16);
	}
#if defined(CONFIG_CMD_NET)
	if ((s = getenv ("bootfile")) != NULL) {
		copy_filename (BootFile, s, sizeof (BootFile));
	}
#endif

	WATCHDOG_RESET();

#if defined(CONFIG_CMD_IDE)
	WATCHDOG_RESET();
	puts("IDE:   ");
	ide_init();
#endif

#if defined(CONFIG_CMD_SCSI)
	WATCHDOG_RESET();
	puts("SCSI:  ");
	scsi_init();
#endif

#if defined(CONFIG_CMD_DOC)
	WATCHDOG_RESET();
	puts("DOC:   ");
	doc_init();
#endif

#ifdef CONFIG_BITBANGMII
	bb_miiphy_init();
#endif
#if defined(CONFIG_CMD_NET)
#if defined(CONFIG_NET_MULTI)
	WATCHDOG_RESET();
	puts("Net:   ");
#endif
	eth_initialize(gd->bd);
#endif

#if ( defined(CONFIG_CMD_NET)) && (0)
	WATCHDOG_RESET();
# ifdef DEBUG
	puts ("Reset Ethernet PHY\n");
# endif
	reset_phy();
#endif

#ifdef CONFIG_LAST_STAGE_INIT
	WATCHDOG_RESET();
	/*
	 * Some parts can be only initialized if all others (like
	 * Interrupts) are up and running (i.e. the PC-style ISA
	 * keyboard).
	 */
	last_stage_init();
#endif


#ifdef CONFIG_POST
	post_run (NULL, POST_RAM | post_bootmode_get(0));
#endif


	show_boot_progress(0x29);

	/* main_loop() can return to retry autoboot, if so just run it again. */
	for (;;) {
		main_loop();
	}

	/* NOTREACHED - no way out of command loop except booting */
}

void hang (void)
{
	puts ("### ERROR ### Please RESET the board ###\n");
	for (;;);
}

unsigned long do_go_exec (ulong (*entry)(int, char *[]), int argc, char *argv[])
{
	/*
	 * x86 does not use a dedicated register to pass the pointer
	 * to the global_data
	 */
	argv[-1] = (char *)gd;

	return (entry) (argc, argv);
}

void setup_pcat_compatibility(void)
	__attribute__((weak, alias("__setup_pcat_compatibility")));

void __setup_pcat_compatibility(void)
{
}
