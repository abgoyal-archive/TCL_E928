

#include <common.h>
#if defined (CONFIG_IMX)

#include <asm/arch/imx-regs.h>

int timer_init (void)
{
	int i;
	/* setup GP Timer 1 */
	TCTL1 = TCTL_SWR;
	for ( i=0; i<100; i++) TCTL1 = 0; /* We have no udelay by now */
	TPRER1 = get_PERCLK1() / 1000000; /* 1 MHz */
	TCTL1 |= TCTL_FRR | (1<<1); /* Freerun Mode, PERCLK1 input */

	reset_timer_masked();

	return (0);
}


void reset_timer (void)
{
	reset_timer_masked ();
}

ulong get_timer (ulong base)
{
	return get_timer_masked() - base;
}

void set_timer (ulong t)
{
	/* nop */
}

void reset_timer_masked (void)
{
	TCTL1 &= ~TCTL_TEN;
	TCTL1 |= TCTL_TEN; /* Enable timer */
}

ulong get_timer_masked (void)
{
	return TCN1;
}

void udelay_masked (unsigned long usec)
{
	ulong endtime = get_timer_masked() + usec;
	signed long diff;

	do {
		ulong now = get_timer_masked ();
		diff = endtime - now;
	} while (diff >= 0);
}

void __udelay (unsigned long usec)
{
	udelay_masked(usec);
}

unsigned long long get_ticks(void)
{
	return get_timer(0);
}

ulong get_tbclk (void)
{
	ulong tbclk;

	tbclk = CONFIG_SYS_HZ;

	return tbclk;
}

void reset_cpu (ulong ignored)
{
	/* Disable watchdog and set Time-Out field to 0 */
	WCR = 0x00000000;

	/* Write Service Sequence */
	WSR = 0x00005555;
	WSR = 0x0000AAAA;

	/* Enable watchdog */
	WCR = 0x00000001;

	while (1);
	/*NOTREACHED*/
}

#endif /* defined (CONFIG_IMX) */
