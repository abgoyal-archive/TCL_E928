

#include <common.h>
#include <asm/io.h>

unsigned long get_board_sys_clk(ulong dummy)
{
#if defined(CONFIG_MPC85xx)
	volatile ccsr_gur_t *gur = (void *)(CONFIG_SYS_MPC85xx_GUTS_ADDR);
#elif defined(CONFIG_MPC86xx)
	immap_t *immap = (immap_t *)CONFIG_SYS_IMMR;
	volatile ccsr_gur_t *gur = &immap->im_gur;
#endif

	if (in_be32(&gur->gpporcr) & 0x10000)
		return 66666666;
	else
		return 50000000;
}

#ifdef CONFIG_MPC85xx
unsigned long get_board_ddr_clk(ulong dummy)
{
	volatile ccsr_gur_t *gur = (void *)(CONFIG_SYS_MPC85xx_GUTS_ADDR);
	u32 ddr_ratio = (in_be32(&gur->porpllsr) & 0x00003e00) >> 9;

	if (ddr_ratio == 0x7)
		return get_board_sys_clk(dummy);

	return 66666666;
}
#endif
