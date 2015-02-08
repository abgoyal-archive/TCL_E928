

#include <common.h>
#include <div64.h>
#include <asm/processor.h>
#include <asm/clk.h>
#include <asm/io.h>

#define TMU_MAX_COUNTER (~0UL)

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

static void tmu_timer_start (unsigned int timer)
{
	if (timer > 2)
		return;
	writeb(readb(TSTR) | (1 << timer), TSTR);
}

static void tmu_timer_stop (unsigned int timer)
{
	if (timer > 2)
		return;
	writeb(readb(TSTR) & ~(1 << timer), TSTR);
}

int timer_init (void)
{
	/* Divide clock by CONFIG_SYS_TMU_CLK_DIV */
	u16 bit = 0;

	switch (CONFIG_SYS_TMU_CLK_DIV) {
	case 1024:
		bit = 4;
		break;
	case 256:
		bit = 3;
		break;
	case 64:
		bit = 2;
		break;
	case 16:
		bit = 1;
		break;
	case 4:
	default:
		break;
	}
	writew(readw(TCR0) | bit, TCR0);

	/* Calc clock rate */
	timer_freq = get_tmu0_clk_rate() >> ((bit + 1) * 2);

	tmu_timer_stop(0);
	tmu_timer_start(0);

	return 0;
}

unsigned long long get_ticks (void)
{
	return 0 - readl(TCNT0);
}

void __udelay (unsigned long usec)
{
	unsigned long long tmp;
	ulong tmo;

	tmo = usec_to_tick(usec);
	tmp = get_ticks() + tmo;	/* get current timestamp */

	while (get_ticks() < tmp)	/* loop till event */
		 /*NOP*/;
}

unsigned long get_timer (unsigned long base)
{
	/* return msec */
	return tick_to_time(get_ticks()) - base;
}

void set_timer (unsigned long t)
{
	writel((0 - t), TCNT0);
}

void reset_timer (void)
{
	tmu_timer_stop(0);
	set_timer (0);
	tmu_timer_start(0);
}

unsigned long get_tbclk (void)
{
	return timer_freq;
}
