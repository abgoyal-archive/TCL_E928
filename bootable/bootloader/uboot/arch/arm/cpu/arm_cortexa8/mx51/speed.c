

#include <common.h>
#include <asm/arch/imx-regs.h>
#include <asm/arch/clock.h>

int get_clocks(void)
{
	DECLARE_GLOBAL_DATA_PTR;

#ifdef CONFIG_FSL_ESDHC
	gd->sdhc_clk = mxc_get_clock(MXC_IPG_PERCLK);
#endif
	return 0;
}
