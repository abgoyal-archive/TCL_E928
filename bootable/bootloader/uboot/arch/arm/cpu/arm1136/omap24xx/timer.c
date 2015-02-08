

#include <common.h>
#include <asm/arch/bits.h>
#include <asm/arch/omap2420.h>

#define TIMER_LOAD_VAL 0

/* macro to read the 32 bit timer */
#define READ_TIMER (*((volatile ulong *)(CONFIG_SYS_TIMERBASE+TCRR)))

static ulong timestamp;
static ulong lastinc;

int timer_init (void)
{
	int32_t val;

	/* Start the counter ticking up */
	*((int32_t *) (CONFIG_SYS_TIMERBASE + TLDR)) = TIMER_LOAD_VAL;	/* reload value on overflow*/
	val = (CONFIG_SYS_PTV << 2) | BIT5 | BIT1 | BIT0;		/* mask to enable timer*/
	*((int32_t *) (CONFIG_SYS_TIMERBASE + TCLR)) = val;	/* start timer */

	reset_timer_masked(); /* init the timestamp and lastinc value */

	return(0);
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
	timestamp = t;
}

/* delay x useconds AND preserve advance timestamp value */
void __udelay (unsigned long usec)
{
	ulong tmo, tmp;

	if (usec >= 1000) {		/* if "big" number, spread normalization to seconds */
		tmo = usec / 1000;	/* start to normalize for usec to ticks per sec */
		tmo *= CONFIG_SYS_HZ;	/* find number of "ticks" to wait to achieve target */
		tmo /= 1000;		/* finish normalize. */
	} else {			/* else small number, don't kill it prior to HZ multiply */
		tmo = usec * CONFIG_SYS_HZ;
		tmo /= (1000*1000);
	}

	tmp = get_timer (0);		/* get current timestamp */
	if ( (tmo + tmp + 1) < tmp )	/* if setting this forward will roll time stamp */
		reset_timer_masked ();	/* reset "advancing" timestamp to 0, set lastinc value */
	else
		tmo	+= tmp;		/* else, set advancing stamp wake up time */
	while (get_timer_masked () < tmo)/* loop till event */
		/*NOP*/;
}

void reset_timer_masked (void)
{
	/* reset time */
	lastinc = READ_TIMER;		/* capture current incrementer value time */
	timestamp = 0;			/* start "advancing" time stamp from 0 */
}

ulong get_timer_masked (void)
{
	ulong now = READ_TIMER;		/* current tick value */

	if (now >= lastinc)		/* normal mode (non roll) */
		timestamp += (now - lastinc); /* move stamp fordward with absoulte diff ticks */
	else				/* we have rollover of incrementer */
		timestamp += (0xFFFFFFFF - lastinc) + now;
	lastinc = now;
	return timestamp;
}

/* waits specified delay value and resets timestamp */
void udelay_masked (unsigned long usec)
{
	ulong tmo;
	ulong endtime;
	signed long diff;

	if (usec >= 1000) {			/* if "big" number, spread normalization to seconds */
		tmo = usec / 1000;		/* start to normalize for usec to ticks per sec */
		tmo *= CONFIG_SYS_HZ;			/* find number of "ticks" to wait to achieve target */
		tmo /= 1000;			/* finish normalize. */
	} else {					/* else small number, don't kill it prior to HZ multiply */
		tmo = usec * CONFIG_SYS_HZ;
		tmo /= (1000*1000);
	}
	endtime = get_timer_masked () + tmo;

	do {
		ulong now = get_timer_masked ();
		diff = endtime - now;
	} while (diff >= 0);
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
