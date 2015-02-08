
#include <common.h>
#include <twl4030.h>
#include <asm/io.h>
#include <asm/arch/mux.h>
#include <asm/arch/sys_proto.h>
#include <asm/arch/gpio.h>
#include <asm/mach-types.h>
#include "beagle.h"

static int beagle_revision_c;

int board_init(void)
{
	DECLARE_GLOBAL_DATA_PTR;

	gpmc_init(); /* in SRAM or SDRAM, finish GPMC */
	/* board id for Linux */
	gd->bd->bi_arch_number = MACH_TYPE_OMAP3_BEAGLE;
	/* boot param addr */
	gd->bd->bi_boot_params = (OMAP34XX_SDRC_CS0 + 0x100);

	return 0;
}

int beagle_get_revision(void)
{
	return beagle_revision_c;
}

void beagle_identify(void)
{
	beagle_revision_c = 0;
	if (!omap_request_gpio(171)) {
		unsigned int val;

		omap_set_gpio_direction(171, 1);
		val = omap_get_gpio_datain(171);
		omap_free_gpio(171);

		if (val)
			beagle_revision_c = 0;
		else
			beagle_revision_c = 1;
	}

	printf("Board revision ");
	if (beagle_revision_c)
		printf("C\n");
	else
		printf("Ax/Bx\n");
}

int misc_init_r(void)
{
	struct gpio *gpio5_base = (struct gpio *)OMAP34XX_GPIO5_BASE;
	struct gpio *gpio6_base = (struct gpio *)OMAP34XX_GPIO6_BASE;

	twl4030_power_init();
	twl4030_led_init(TWL4030_LED_LEDEN_LEDAON | TWL4030_LED_LEDEN_LEDBON);

	/* Configure GPIOs to output */
	writel(~(GPIO23 | GPIO10 | GPIO8 | GPIO2 | GPIO1), &gpio6_base->oe);
	writel(~(GPIO31 | GPIO30 | GPIO29 | GPIO28 | GPIO22 | GPIO21 |
		GPIO15 | GPIO14 | GPIO13 | GPIO12), &gpio5_base->oe);

	/* Set GPIOs */
	writel(GPIO23 | GPIO10 | GPIO8 | GPIO2 | GPIO1,
		&gpio6_base->setdataout);
	writel(GPIO31 | GPIO30 | GPIO29 | GPIO28 | GPIO22 | GPIO21 |
		GPIO15 | GPIO14 | GPIO13 | GPIO12, &gpio5_base->setdataout);

	beagle_identify();

	dieid_num_r();

	return 0;
}

void set_muxconf_regs(void)
{
	MUX_BEAGLE();

	if (beagle_revision_c) {
		MUX_BEAGLE_C();
	}
}
