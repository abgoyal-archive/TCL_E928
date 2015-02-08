

#include <common.h>
#include <stdio_dev.h>
#include <watchdog.h>
#include <malloc.h>
#include <mmc.h>
#include <net.h>
#ifdef CONFIG_STATUS_LED
#include <status_led.h>
#endif
#if defined(CONFIG_SYS_NIOS_EPCSBASE)
#include <nios2-epcs.h>
#endif
#ifdef CONFIG_CMD_NAND
#include <nand.h>	/* cannot even include nand.h if it isnt configured */
#endif

DECLARE_GLOBAL_DATA_PTR;



typedef int (init_fnc_t) (void);



init_fnc_t *init_sequence[] = {

#if defined(CONFIG_BOARD_EARLY_INIT_F)
	board_early_init_f,	/* Call board-specific init code early.*/
#endif
#if defined(CONFIG_SYS_NIOS_EPCSBASE)
	epcs_reset,
#endif

	env_init,
	serial_init,
	console_init_f,
	display_options,
	checkcpu,
	checkboard,
	NULL,			/* Terminate this list */
};


/***********************************************************************/
void board_init (void)
{
	bd_t *bd;
	init_fnc_t **init_fnc_ptr;

	/* Pointer is writable since we allocated a register for it.
	 * Nios treats CONFIG_SYS_GBL_DATA_OFFSET as an address.
	 */
	gd = (gd_t *)CONFIG_SYS_GBL_DATA_OFFSET;
	/* compiler optimization barrier needed for GCC >= 3.4 */
	__asm__ __volatile__("": : :"memory");

	memset( gd, 0, CONFIG_SYS_GBL_DATA_SIZE );

	gd->bd = (bd_t *)(gd+1);	/* At end of global data */
	gd->baudrate = CONFIG_BAUDRATE;
	gd->cpu_clk = CONFIG_SYS_CLK_FREQ;

	bd = gd->bd;
	bd->bi_memstart	= CONFIG_SYS_SDRAM_BASE;
	bd->bi_memsize = CONFIG_SYS_SDRAM_SIZE;
#ifndef CONFIG_SYS_NO_FLASH
	bd->bi_flashstart = CONFIG_SYS_FLASH_BASE;
#endif
#if	defined(CONFIG_SYS_SRAM_BASE) && defined(CONFIG_SYS_SRAM_SIZE)
	bd->bi_sramstart= CONFIG_SYS_SRAM_BASE;
	bd->bi_sramsize	= CONFIG_SYS_SRAM_SIZE;
#endif
	bd->bi_baudrate	= CONFIG_BAUDRATE;

	for (init_fnc_ptr = init_sequence; *init_fnc_ptr; ++init_fnc_ptr) {
		WATCHDOG_RESET ();
		if ((*init_fnc_ptr) () != 0) {
			hang ();
		}
	}

	WATCHDOG_RESET ();

	/* The Malloc area is immediately below the monitor copy in RAM */
	mem_malloc_init(CONFIG_SYS_MALLOC_BASE, CONFIG_SYS_MALLOC_LEN);

#ifndef CONFIG_SYS_NO_FLASH
	WATCHDOG_RESET ();
	bd->bi_flashsize = flash_init();
#endif

#ifdef CONFIG_CMD_NAND
	puts("NAND:  ");
	nand_init();
#endif

#ifdef CONFIG_GENERIC_MMC
	puts("MMC:   ");
	mmc_initialize(bd);
#endif

	WATCHDOG_RESET ();
	env_relocate();

	bd->bi_ip_addr = getenv_IPaddr ("ipaddr");

	WATCHDOG_RESET ();
	stdio_init();
	jumptable_init();
	console_init_r();

	WATCHDOG_RESET ();
	interrupt_init ();

#if defined(CONFIG_BOARD_LATE_INIT)
	board_late_init ();
#endif

#if defined(CONFIG_CMD_NET)
#if defined(CONFIG_NET_MULTI)
	puts ("Net:   ");
#endif
	eth_initialize (bd);
#endif

	/* main_loop */
	for (;;) {
		WATCHDOG_RESET ();
		main_loop ();
	}
}


/***********************************************************************/

void hang (void)
{
	disable_interrupts ();
	puts("### ERROR ### Please reset board ###\n");
	for (;;);
}
