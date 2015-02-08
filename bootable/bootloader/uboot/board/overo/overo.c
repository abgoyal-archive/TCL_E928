
#include <common.h>
#include <netdev.h>
#include <twl4030.h>
#include <asm/io.h>
#include <asm/arch/mux.h>
#include <asm/arch/mem.h>
#include <asm/arch/sys_proto.h>
#include <asm/arch/gpio.h>
#include <asm/mach-types.h>
#include "overo.h"

#if defined(CONFIG_CMD_NET)
static void setup_net_chip(void);
#endif

int board_init(void)
{
	DECLARE_GLOBAL_DATA_PTR;

	gpmc_init(); /* in SRAM or SDRAM, finish GPMC */
	/* board id for Linux */
	gd->bd->bi_arch_number = MACH_TYPE_OVERO;
	/* boot param addr */
	gd->bd->bi_boot_params = (OMAP34XX_SDRC_CS0 + 0x100);

	return 0;
}

int misc_init_r(void)
{
	twl4030_power_init();
	twl4030_led_init(TWL4030_LED_LEDEN_LEDAON | TWL4030_LED_LEDEN_LEDBON);

#if defined(CONFIG_CMD_NET)
	setup_net_chip();
#endif

	dieid_num_r();

	return 0;
}

void set_muxconf_regs(void)
{
	MUX_OVERO();
}

#if defined(CONFIG_CMD_NET)
static void setup_net_chip(void)
{
	struct ctrl *ctrl_base = (struct ctrl *)OMAP34XX_CTRL_BASE;

	/* Configure GPMC registers */
	writel(NET_LAN9221_GPMC_CONFIG1, &gpmc_cfg->cs[5].config1);
	writel(NET_LAN9221_GPMC_CONFIG2, &gpmc_cfg->cs[5].config2);
	writel(NET_LAN9221_GPMC_CONFIG3, &gpmc_cfg->cs[5].config3);
	writel(NET_LAN9221_GPMC_CONFIG4, &gpmc_cfg->cs[5].config4);
	writel(NET_LAN9221_GPMC_CONFIG5, &gpmc_cfg->cs[5].config5);
	writel(NET_LAN9221_GPMC_CONFIG6, &gpmc_cfg->cs[5].config6);
	writel(NET_LAN9221_GPMC_CONFIG7, &gpmc_cfg->cs[5].config7);

	/* Enable off mode for NWE in PADCONF_GPMC_NWE register */
	writew(readw(&ctrl_base ->gpmc_nwe) | 0x0E00, &ctrl_base->gpmc_nwe);
	/* Enable off mode for NOE in PADCONF_GPMC_NADV_ALE register */
	writew(readw(&ctrl_base->gpmc_noe) | 0x0E00, &ctrl_base->gpmc_noe);
	/* Enable off mode for ALE in PADCONF_GPMC_NADV_ALE register */
	writew(readw(&ctrl_base->gpmc_nadv_ale) | 0x0E00,
		&ctrl_base->gpmc_nadv_ale);

	/* Make GPIO 64 as output pin and send a magic pulse through it */
	if (!omap_request_gpio(64)) {
		omap_set_gpio_direction(64, 0);
		omap_set_gpio_dataout(64, 1);
		udelay(1);
		omap_set_gpio_dataout(64, 0);
		udelay(1);
		omap_set_gpio_dataout(64, 1);
	}
}
#endif

int board_eth_init(bd_t *bis)
{
	int rc = 0;
#ifdef CONFIG_SMC911X
	rc = smc911x_initialize(0, CONFIG_SMC911X_BASE);
#endif
	return rc;
}
