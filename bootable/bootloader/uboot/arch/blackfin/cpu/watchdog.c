

#include <common.h>
#include <watchdog.h>
#include <asm/blackfin.h>

void hw_watchdog_reset(void)
{
	bfin_write_WDOG_STAT(0);
}

void hw_watchdog_init(void)
{
	bfin_write_WDOG_CNT(5 * get_sclk());	/* 5 second timeout */
	hw_watchdog_reset();
	bfin_write_WDOG_CTL(0x0);
}
