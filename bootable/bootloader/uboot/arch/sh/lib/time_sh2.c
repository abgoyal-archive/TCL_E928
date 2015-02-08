

#include <common.h>
#include <asm/io.h>
#include <asm/processor.h>

#define CMT_CMCSR_INIT	0x0001	/* PCLK/32 */
#define CMT_CMCSR_CALIB 0x0000
#define CMT_MAX_COUNTER (0xFFFFFFFF)
#define CMT_TIMER_RESET (0xFFFF)

static vu_long cmt0_timer;

static void cmt_timer_start(unsigned int timer)
{
	writew(readw(CMSTR) | 0x01, CMSTR);
}

static void cmt_timer_stop(unsigned int timer)
{
	writew(readw(CMSTR) & ~0x01, CMSTR);
}

int timer_init(void)
{
	cmt0_timer = 0;
	/* Divide clock by 32 */
	readw(CMCSR_0);
	writew(CMT_CMCSR_INIT, CMCSR_0);

	/* User Device 0 only */
	cmt_timer_stop(0);
	set_timer(CMT_TIMER_RESET);
	cmt_timer_start(0);

	return 0;
}

unsigned long long get_ticks(void)
{
	return cmt0_timer;
}

static vu_long cmcnt = 0;
static unsigned long get_usec (void)
{
	ulong data = readw(CMCNT_0);

	if (data >= cmcnt)
		cmcnt = data - cmcnt;
	else
		cmcnt = (CMT_TIMER_RESET - cmcnt) + data;

	if ((cmt0_timer + cmcnt) > CMT_MAX_COUNTER)
		cmt0_timer = ((cmt0_timer + cmcnt) - CMT_MAX_COUNTER);
	else
		cmt0_timer += cmcnt;

	cmcnt = data;
	return cmt0_timer;
}

/* return msec */
ulong get_timer(ulong base)
{
	return (get_usec() / 1000) - base;
}

void set_timer(ulong t)
{
	writew((u16) t, CMCOR_0);
}

void reset_timer(void)
{
	cmt_timer_stop(0);
	set_timer(CMT_TIMER_RESET);
	cmt0_timer = 0;
	cmt_timer_start(0);
}

void __udelay(unsigned long usec)
{
	unsigned long end = get_usec() + usec;

	while (get_usec() < end)
		continue;
}

unsigned long get_tbclk(void)
{
	return CONFIG_SYS_HZ;
}
