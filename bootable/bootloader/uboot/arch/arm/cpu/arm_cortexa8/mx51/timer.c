

#include <common.h>
#include <asm/io.h>
#include <asm/arch/imx-regs.h>

/* General purpose timers registers */
struct mxc_gpt {
	unsigned int control;
	unsigned int prescaler;
	unsigned int status;
	unsigned int nouse[6];
	unsigned int counter;
};

static struct mxc_gpt *cur_gpt = (struct mxc_gpt *)GPT1_BASE_ADDR;

/* General purpose timers bitfields */
#define GPTCR_SWR       (1<<15)	/* Software reset */
#define GPTCR_FRR       (1<<9)	/* Freerun / restart */
#define GPTCR_CLKSOURCE_32 (4<<6)	/* Clock source */
#define GPTCR_TEN       (1)	/* Timer enable */

static ulong timestamp;
static ulong lastinc;

int timer_init(void)
{
	int i;

	/* setup GP Timer 1 */
	__raw_writel(GPTCR_SWR, &cur_gpt->control);

	/* We have no udelay by now */
	for (i = 0; i < 100; i++)
		__raw_writel(0, &cur_gpt->control);

	__raw_writel(0, &cur_gpt->prescaler); /* 32Khz */

	/* Freerun Mode, PERCLK1 input */
	i = __raw_readl(&cur_gpt->control);
	__raw_writel(i | GPTCR_CLKSOURCE_32 | GPTCR_TEN, &cur_gpt->control);
	reset_timer_masked();
	return 0;
}

void reset_timer(void)
{
	reset_timer_masked();
}

void reset_timer_masked(void)
{
	ulong val = __raw_readl(&cur_gpt->counter);
	lastinc = val / (CONFIG_MX51_CLK32 / CONFIG_SYS_HZ);
	timestamp = 0;
}

ulong get_timer_masked(void)
{
	ulong val = __raw_readl(&cur_gpt->counter);
	val /= (CONFIG_MX51_CLK32 / CONFIG_SYS_HZ);
	if (val >= lastinc)
		timestamp += (val - lastinc);
	else
		timestamp += ((0xFFFFFFFF / (CONFIG_MX51_CLK32 / CONFIG_SYS_HZ))
				- lastinc) + val;
	lastinc = val;
	return val;
}

ulong get_timer(ulong base)
{
	return get_timer_masked() - base;
}

void set_timer(ulong t)
{
	timestamp = t;
}

/* delay x useconds AND preserve advance timestamp value */
void __udelay(unsigned long usec)
{
	unsigned long now, start, tmo;
	tmo = usec * (CONFIG_MX51_CLK32 / 1000) / 1000;

	if (!tmo)
		tmo = 1;

	now = start = readl(&cur_gpt->counter);

	while ((now - start) < tmo)
		now = readl(&cur_gpt->counter);

}
