

#include <common.h>
#include <asm/arch/ixp425.h>

#ifdef CONFIG_TIMER_IRQ

#define FREQ		66666666
#define CLOCK_TICK_RATE	(((FREQ / CONFIG_SYS_HZ & ~IXP425_OST_RELOAD_MASK) + 1) * CONFIG_SYS_HZ)
#define LATCH		((CLOCK_TICK_RATE + CONFIG_SYS_HZ/2) / CONFIG_SYS_HZ)	/* For divider */


static volatile ulong timestamp;

static void timer_isr(void *data)
{
	unsigned int *pTime = (unsigned int *)data;

	(*pTime)++;

	/*
	 * Reset IRQ source
	 */
	*IXP425_OSST = IXP425_OSST_TIMER_2_PEND;
}

ulong get_timer (ulong base)
{
	return timestamp - base;
}

void reset_timer (void)
{
	timestamp = 0;
}

int timer_init (void)
{
	/* install interrupt handler for timer */
	irq_install_handler(IXP425_TIMER_2_IRQ, timer_isr, (void *)&timestamp);

	/* setup the Timer counter value */
	*IXP425_OSRT2 = (LATCH & ~IXP425_OST_RELOAD_MASK) | IXP425_OST_ENABLE;

	/* enable timer irq */
	*IXP425_ICMR = (1 << IXP425_TIMER_2_IRQ);

	return 0;
}
#else
ulong get_timer (ulong base)
{
       return get_timer_masked () - base;
}

void ixp425_udelay(unsigned long usec)
{
	/*
	 * This function has a max usec, but since it is called from udelay
	 * we should not have to worry... be happy
	 */
	unsigned long usecs = CONFIG_SYS_HZ/1000000L & ~IXP425_OST_RELOAD_MASK;

	*IXP425_OSST = IXP425_OSST_TIMER_1_PEND;
	usecs |= IXP425_OST_ONE_SHOT | IXP425_OST_ENABLE;
	*IXP425_OSRT1 = usecs;
	while (!(*IXP425_OSST & IXP425_OSST_TIMER_1_PEND));
}

void __udelay (unsigned long usec)
{
	while (usec--) ixp425_udelay(1);
}

static ulong reload_constant = 0xfffffff0;

void reset_timer_masked (void)
{
	ulong reload = reload_constant | IXP425_OST_ONE_SHOT | IXP425_OST_ENABLE;

	*IXP425_OSST = IXP425_OSST_TIMER_1_PEND;
	*IXP425_OSRT1 = reload;
}

ulong get_timer_masked (void)
{
	/*
	 * Note that it is possible for this to wrap!
	 * In this case we return max.
	 */
	ulong current = *IXP425_OST1;
	if (*IXP425_OSST & IXP425_OSST_TIMER_1_PEND)
	{
		return reload_constant;
	}
	return (reload_constant - current);
}

int timer_init(void)
{
	return 0;
}
#endif
