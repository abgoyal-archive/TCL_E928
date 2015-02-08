

#include <common.h>

#ifdef CONFIG_SYS_TIMER_0
void __udelay (unsigned long usec)
{
	int i;
	i = get_timer (0);
	while ((get_timer (0) - i) < (usec / 1000)) ;
}
#else
void __udelay (unsigned long usec)
{
	unsigned int i;
	for (i = 0; i < (usec * CONFIG_XILINX_CLOCK_FREQ / 10000000); i++);
}
#endif
