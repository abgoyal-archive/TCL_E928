

#include <common.h>
#include <asm/io.h>

struct davinci_timer {
	u_int32_t	pid12;
	u_int32_t	emumgt;
	u_int32_t	na1;
	u_int32_t	na2;
	u_int32_t	tim12;
	u_int32_t	tim34;
	u_int32_t	prd12;
	u_int32_t	prd34;
	u_int32_t	tcr;
	u_int32_t	tgcr;
	u_int32_t	wdtcr;
};

static struct davinci_timer * const timer =
	(struct davinci_timer *)CONFIG_SYS_TIMERBASE;

#define TIMER_LOAD_VAL	(CONFIG_SYS_HZ_CLOCK / CONFIG_SYS_HZ)
#define TIM_CLK_DIV	16

static ulong timestamp;
static ulong lastinc;

int timer_init(void)
{
	/* We are using timer34 in unchained 32-bit mode, full speed */
	writel(0x0, &timer->tcr);
	writel(0x0, &timer->tgcr);
	writel(0x06 | ((TIM_CLK_DIV - 1) << 8), &timer->tgcr);
	writel(0x0, &timer->tim34);
	writel(TIMER_LOAD_VAL, &timer->prd34);
	lastinc = 0;
	timestamp = 0;
	writel(2 << 22, &timer->tcr);

	return(0);
}

void reset_timer(void)
{
	writel(0x0, &timer->tcr);
	writel(0x0, &timer->tim34);
	lastinc = 0;
	timestamp = 0;
	writel(2 << 22, &timer->tcr);
}

static ulong get_timer_raw(void)
{
	ulong now = readl(&timer->tim34);

	if (now >= lastinc) {
		/* normal mode */
		timestamp += now - lastinc;
	} else {
		/* overflow ... */
		timestamp += now + TIMER_LOAD_VAL - lastinc;
	}
	lastinc = now;
	return timestamp;
}

ulong get_timer(ulong base)
{
	return((get_timer_raw() / (TIMER_LOAD_VAL / TIM_CLK_DIV)) - base);
}

void set_timer(ulong t)
{
	timestamp = t;
}

void __udelay(unsigned long usec)
{
	ulong tmo;
	ulong endtime;
	signed long diff;

	tmo = CONFIG_SYS_HZ_CLOCK / 1000;
	tmo *= usec;
	tmo /= (1000 * TIM_CLK_DIV);

	endtime = get_timer_raw() + tmo;

	do {
		ulong now = get_timer_raw();
		diff = endtime - now;
	} while (diff >= 0);
}

unsigned long long get_ticks(void)
{
	return(get_timer(0));
}

ulong get_tbclk(void)
{
	return CONFIG_SYS_HZ;
}
