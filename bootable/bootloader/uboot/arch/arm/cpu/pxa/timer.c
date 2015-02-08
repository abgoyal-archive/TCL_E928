

#include <common.h>
#include <asm/arch/pxa-regs.h>
#include <div64.h>

#ifdef CONFIG_USE_IRQ
#error: interrupts not implemented yet
#endif

#if defined(CONFIG_PXA27X) || defined(CONFIG_CPU_MONAHANS)
#define TIMER_FREQ_HZ 3250000
#elif defined(CONFIG_PXA250)
#define TIMER_FREQ_HZ 3686400
#else
#error "Timer frequency unknown - please config PXA CPU type"
#endif

static inline unsigned long long tick_to_time(unsigned long long tick)
{
	tick *= CONFIG_SYS_HZ;
	do_div(tick, TIMER_FREQ_HZ);
	return tick;
}

static inline unsigned long long us_to_tick(unsigned long long us)
{
	us = us * TIMER_FREQ_HZ + 999999;
	do_div(us, 1000000);
	return us;
}

int timer_init (void)
{
	reset_timer();

	return 0;
}

void reset_timer (void)
{
	reset_timer_masked ();
}

ulong get_timer (ulong base)
{
	return get_timer_masked () - base;
}

void set_timer (ulong t)
{
	/* nop */
}

void __udelay (unsigned long usec)
{
	udelay_masked (usec);
}


void reset_timer_masked (void)
{
	OSCR = 0;
}

ulong get_timer_masked (void)
{
	return tick_to_time(get_ticks());
}

void udelay_masked (unsigned long usec)
{
	unsigned long long tmp;
	ulong tmo;

	tmo = us_to_tick(usec);
	tmp = get_ticks() + tmo;	/* get current timestamp */

	while (get_ticks() < tmp)	/* loop till event */
		 /*NOP*/;

}

unsigned long long get_ticks(void)
{
	return OSCR;
}

ulong get_tbclk (void)
{
	ulong tbclk;
	tbclk = TIMER_FREQ_HZ;
	return tbclk;
}
