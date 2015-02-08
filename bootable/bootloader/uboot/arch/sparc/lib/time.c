

#include <common.h>

/* Implemented by SPARC CPUs */
extern void cpu_wait_ticks(unsigned long ticks);
extern unsigned long cpu_usec2ticks(unsigned long usec);
extern unsigned long cpu_ticks2usec(unsigned long ticks);

/* ------------------------------------------------------------------------- */

void wait_ticks(unsigned long ticks)
{
	cpu_wait_ticks(ticks);
}

unsigned long usec2ticks(unsigned long usec)
{
	return cpu_usec2ticks(usec);
}

/* ------------------------------------------------------------------------- */

void __udelay(unsigned long usec)
{
	ulong ticks = usec2ticks(usec);

	wait_ticks(ticks);
}

/* ------------------------------------------------------------------------- */

unsigned long ticks2usec(unsigned long ticks)
{
	return cpu_ticks2usec(ticks);
}

/* ------------------------------------------------------------------------- */

int init_timebase(void)
{

	return (0);
}

/* ------------------------------------------------------------------------- */
