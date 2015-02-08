

#include <common.h>
#include <asm/mipsregs.h>

static unsigned long timestamp;

/* how many counter cycles in a jiffy */
#define CYCLES_PER_JIFFY	(CONFIG_SYS_MIPS_TIMER_FREQ + CONFIG_SYS_HZ / 2) / CONFIG_SYS_HZ


int timer_init(void)
{
	/* Set up the timer for the first expiration. */
	timestamp = 0;
	write_c0_compare(read_c0_count() + CYCLES_PER_JIFFY);

	return 0;
}

void reset_timer(void)
{
	timestamp = 0;
	write_c0_compare(read_c0_count() + CYCLES_PER_JIFFY);
}

ulong get_timer(ulong base)
{
	unsigned int count;
	unsigned int expirelo = read_c0_compare();

	/* Check to see if we have missed any timestamps. */
	count = read_c0_count();
	while ((count - expirelo) < 0x7fffffff) {
		expirelo += CYCLES_PER_JIFFY;
		timestamp++;
	}
	write_c0_compare(expirelo);

	return (timestamp - base);
}

void set_timer(ulong t)
{
	timestamp = t;
	write_c0_compare(read_c0_count() + CYCLES_PER_JIFFY);
}

void __udelay(unsigned long usec)
{
	unsigned int tmo;

	tmo = read_c0_count() + (usec * (CONFIG_SYS_MIPS_TIMER_FREQ / 1000000));
	while ((tmo - read_c0_count()) < 0x7fffffff)
		/*NOP*/;
}

unsigned long long get_ticks(void)
{
	return get_timer(0);
}

ulong get_tbclk(void)
{
	return CONFIG_SYS_HZ;
}
