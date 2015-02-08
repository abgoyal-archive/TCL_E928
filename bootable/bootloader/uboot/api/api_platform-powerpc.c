

#include <config.h>
#include <linux/types.h>
#include <api_public.h>

#include <asm/u-boot.h>
#include <asm/global_data.h>

#include "api_private.h"

DECLARE_GLOBAL_DATA_PTR;

int platform_sys_info(struct sys_info *si)
{
	si->clk_bus = gd->bus_clk;
	si->clk_cpu = gd->cpu_clk;

#if defined(CONFIG_5xx) || defined(CONFIG_8xx) || defined(CONFIG_8260) || \
    defined(CONFIG_E500) || defined(CONFIG_MPC86xx)
#define bi_bar	bi_immr_base
#elif defined(CONFIG_MPC5xxx)
#define bi_bar	bi_mbar_base
#elif defined(CONFIG_MPC83xx)
#define bi_bar	bi_immrbar
#elif defined(CONFIG_MPC8220)
#define bi_bar	bi_mbar_base
#endif

#if defined(bi_bar)
	si->bar = gd->bd->bi_bar;
#undef bi_bar
#else
	si->bar = 0;
#endif

	platform_set_mr(si, gd->bd->bi_memstart, gd->bd->bi_memsize, MR_ATTR_DRAM);
	platform_set_mr(si, gd->bd->bi_flashstart, gd->bd->bi_flashsize, MR_ATTR_FLASH);
	platform_set_mr(si, gd->bd->bi_sramstart, gd->bd->bi_sramsize, MR_ATTR_SRAM);

	return 1;
}
