

#include <common.h>
#include <asm/processor.h>

#include <asm/immap.h>

int get_clocks(void)
{
	DECLARE_GLOBAL_DATA_PTR;

	gd->bus_clk = CONFIG_SYS_CLK;
	gd->cpu_clk = (gd->bus_clk * 2);

#ifdef CONFIG_FSL_I2C
	gd->i2c1_clk = gd->bus_clk;
#endif

	return (0);
}
