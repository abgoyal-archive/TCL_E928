
#include <common.h>
#include <twl4030.h>
#include <asm/io.h>
#include <asm/arch/mux.h>
#include <asm/arch/sys_proto.h>
#include <asm/mach-types.h>
#include "pandora.h"

int board_init(void)
{
	DECLARE_GLOBAL_DATA_PTR;

	gpmc_init(); /* in SRAM or SDRAM, finish GPMC */
	/* board id for Linux */
	gd->bd->bi_arch_number = MACH_TYPE_OMAP3_PANDORA;
	/* boot param addr */
	gd->bd->bi_boot_params = (OMAP34XX_SDRC_CS0 + 0x100);

	return 0;
}

int misc_init_r(void)
{
	struct gpio *gpio1_base = (struct gpio *)OMAP34XX_GPIO1_BASE;
	struct gpio *gpio4_base = (struct gpio *)OMAP34XX_GPIO4_BASE;
	struct gpio *gpio5_base = (struct gpio *)OMAP34XX_GPIO5_BASE;
	struct gpio *gpio6_base = (struct gpio *)OMAP34XX_GPIO6_BASE;

	twl4030_led_init(TWL4030_LED_LEDEN_LEDBON);

	/* Configure GPIOs to output */
	writel(~(GPIO14 | GPIO15 | GPIO16 | GPIO23), &gpio1_base->oe);
	writel(~GPIO22, &gpio4_base->oe);	/* 118 */
	writel(~(GPIO0 | GPIO1 | GPIO28 | GPIO29 | GPIO30 | GPIO31),
		&gpio5_base->oe);	/* 128, 129, 156-159 */
	writel(~GPIO4, &gpio6_base->oe);	/* 164 */

	/* Set GPIOs */
	writel(GPIO28, &gpio5_base->setdataout);
	writel(GPIO4, &gpio6_base->setdataout);

	dieid_num_r();

	return 0;
}

void set_muxconf_regs(void)
{
	MUX_PANDORA();
}
