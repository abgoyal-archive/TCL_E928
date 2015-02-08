

#include <common.h>
#include <asm/processor.h>

int watchdog_init(void)
{
	return 0;
}

void reset_cpu(unsigned long ignored)
{
	while (1)
		;
}
