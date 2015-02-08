

#include <common.h>
#include <asm/arch/hardware.h>
#include <asm/arch/at91_pit.h>
#include <asm/arch/at91_pmc.h>
#include <asm/arch/clk.h>
#include <asm/arch/io.h>
#include <div64.h>

#define TIMER_LOAD_VAL	0xfffff

static ulong timestamp;
static ulong lastinc;
static ulong timer_freq;

static inline unsigned long long tick_to_time(unsigned long long tick)
{
	tick *= CONFIG_SYS_HZ;
	do_div(tick, timer_freq);

	return tick;
}

static inline unsigned long long usec_to_tick(unsigned long long usec)
{
	usec *= timer_freq;
	do_div(usec, 1000000);

	return usec;
}

/* nothing really to do with interrupts, just starts up a counter. */
int timer_init(void)
{
	at91_pmc_t *pmc = (at91_pmc_t *) AT91_PMC_BASE;
	at91_pit_t *pit = (at91_pit_t *) AT91_PIT_BASE;
	/*
	 * Enable PITC Clock
	 * The clock is already enabled for system controller in boot
	 */
	writel(1 << AT91_ID_SYS, &pmc->pcer);

	/* Enable PITC */
	writel(TIMER_LOAD_VAL | AT91_PIT_MR_EN , &pit->mr);

	reset_timer_masked();

	timer_freq = get_mck_clk_rate() >> 4;

	return 0;
}

unsigned long long get_ticks(void)
{
	at91_pit_t *pit = (at91_pit_t *) AT91_PIT_BASE;

	ulong now = readl(&pit->piir);

	if (now >= lastinc)	/* normal mode (non roll) */
		/* move stamp forward with absolut diff ticks */
		timestamp += (now - lastinc);
	else			/* we have rollover of incrementer */
		timestamp += (0xFFFFFFFF - lastinc) + now;
	lastinc = now;
	return timestamp;
}

void reset_timer_masked(void)
{
	/* reset time */
	at91_pit_t *pit = (at91_pit_t *) AT91_PIT_BASE;

	/* capture current incrementer value time */
	lastinc = readl(&pit->piir);
	timestamp = 0; /* start "advancing" time stamp from 0 */
}

ulong get_timer_masked(void)
{
	return tick_to_time(get_ticks());
}

void __udelay(unsigned long usec)
{
	unsigned long long tmp;
	ulong tmo;

	tmo = usec_to_tick(usec);
	tmp = get_ticks() + tmo;	/* get current timestamp */

	while (get_ticks() < tmp)	/* loop till event */
		 /*NOP*/;
}

void reset_timer(void)
{
	reset_timer_masked();
}

ulong get_timer(ulong base)
{
	return get_timer_masked () - base;
}

ulong get_tbclk(void)
{
	ulong tbclk;

	tbclk = CONFIG_SYS_HZ;
	return tbclk;
}
