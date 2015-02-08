

#include <common.h>
#include <asm/processor.h>

#include <asm/immap.h>

DECLARE_GLOBAL_DATA_PTR;
int get_clocks(void)
{
	volatile pll_t *pll = (volatile pll_t *)(MMAP_PLL);

	pll->syncr = PLL_SYNCR_MFD(1);

	while (!(pll->synsr & PLL_SYNSR_LOCK));

	gd->bus_clk = CONFIG_SYS_CLK;
	gd->cpu_clk = (gd->bus_clk * 2);

#ifdef CONFIG_FSL_I2C
	gd->i2c1_clk = gd->bus_clk;
#endif

	return (0);
}
