


#include <common.h>
#include <watchdog.h>
#include <command.h>
#include <mpc8220.h>
#include <netdev.h>
#include <asm/processor.h>

DECLARE_GLOBAL_DATA_PTR;

int checkcpu (void)
{
	ulong clock = gd->cpu_clk;
	char buf[32];

	puts ("CPU:   ");

	printf (CPU_ID_STR);

	printf (" (JTAG ID %08lx)", *(vu_long *) (CONFIG_SYS_MBAR + 0x50));

	printf (" at %s MHz\n", strmhz (buf, clock));

	return 0;
}

/* ------------------------------------------------------------------------- */

int do_reset (cmd_tbl_t * cmdtp, int flag, int argc, char *argv[])
{
	volatile gptmr8220_t *gptmr = (volatile gptmr8220_t *) MMAP_GPTMR;
	ulong msr;

	/* Interrupts and MMU off */
	__asm__ __volatile__ ("mfmsr    %0":"=r" (msr):);

	msr &= ~(MSR_ME | MSR_EE | MSR_IR | MSR_DR);
	__asm__ __volatile__ ("mtmsr    %0"::"r" (msr));

	/* Charge the watchdog timer */
	gptmr->Prescl = 10;
	gptmr->Count = 1;

	gptmr->Mode = GPT_TMS_SGPIO;

	gptmr->Control = GPT_CTRL_WDEN | GPT_CTRL_CE;

	return 1;
}

/* ------------------------------------------------------------------------- */

unsigned long get_tbclk (void)
{
	ulong tbclk;

	tbclk = (gd->bus_clk + 3L) / 4L;

	return (tbclk);
}

/* ------------------------------------------------------------------------- */

int cpu_eth_init(bd_t *bis)
{
#if defined(CONFIG_MPC8220_FEC)
	mpc8220_fec_initialize(bis);
#endif
	return 0;
}
