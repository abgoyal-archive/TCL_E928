
#include <common.h>
#include <netdev.h>
#ifdef CONFIG_STATUS_LED
#include <status_led.h>
#endif
#include <twl4030.h>
#include <asm/io.h>
#include <asm/arch/gpio.h>
#include <asm/arch/mem.h>
#include <asm/arch/mux.h>
#include <asm/arch/sys_proto.h>
#include <asm/mach-types.h>
#include "zoom2.h"
#include "zoom2_serial.h"

static u32 gpmc_serial_TL16CP754C[GPMC_MAX_REG] = {
	0x00011000,
	0x001F1F01,
	0x00080803,
	0x1D091D09,
	0x041D1F1F,
	0x1D0904C4, 0
};

/* Used to track the revision of the board */
static zoom2_revision revision = ZOOM2_REVISION_UNKNOWN;

zoom2_revision zoom2_get_revision(void)
{
	return revision;
}

void zoom2_identify(void)
{
	/*
	 * To check for production board vs beta board,
	 * check if gpio 94 is clear.
	 *
	 * No way yet to check for alpha board identity.
	 * Alpha boards were produced in very limited quantities
	 * and they are not commonly used.  They are mentioned here
	 * only for completeness.
	 */
	if (!omap_request_gpio(94)) {
		unsigned int val;

		omap_set_gpio_direction(94, 1);
		val = omap_get_gpio_datain(94);
		omap_free_gpio(94);

		if (val)
			revision = ZOOM2_REVISION_BETA;
		else
			revision = ZOOM2_REVISION_PRODUCTION;
	}

	printf("Board revision ");
	switch (revision) {
	case ZOOM2_REVISION_PRODUCTION:
		printf("Production\n");
		break;
	case ZOOM2_REVISION_BETA:
		printf("Beta\n");
		break;
	default:
		printf("Unknown\n");
		break;
	}
}

int board_init (void)
{
	DECLARE_GLOBAL_DATA_PTR;
	u32 *gpmc_config;

	gpmc_init ();		/* in SRAM or SDRAM, finish GPMC */

	/* Configure console support on zoom2 */
	gpmc_config = gpmc_serial_TL16CP754C;
	enable_gpmc_cs_config(gpmc_config, &gpmc_cfg->cs[3],
			SERIAL_TL16CP754C_BASE, GPMC_SIZE_16M);

	/* board id for Linux */
	gd->bd->bi_arch_number = MACH_TYPE_OMAP_ZOOM2;
	/* boot param addr */
	gd->bd->bi_boot_params = (OMAP34XX_SDRC_CS0 + 0x100);

#if defined(CONFIG_STATUS_LED) && defined(STATUS_LED_BOOT)
	status_led_set (STATUS_LED_BOOT, STATUS_LED_ON);
#endif
	return 0;
}

int misc_init_r(void)
{
	zoom2_identify();
	twl4030_power_init();
	twl4030_led_init(TWL4030_LED_LEDEN_LEDAON | TWL4030_LED_LEDEN_LEDBON);
	dieid_num_r();

	/*
	 * Board Reset
	 * The board is reset by holding the the large button
	 * on the top right side of the main board for
	 * eight seconds.
	 *
	 * There are reported problems of some beta boards
	 * continously resetting.  For those boards, disable resetting.
	 */
	if (ZOOM2_REVISION_PRODUCTION <= zoom2_get_revision())
		twl4030_power_reset_init();

	return 0;
}

void set_muxconf_regs (void)
{
	/* platform specific muxes */
	MUX_ZOOM2 ();
}

#ifdef CONFIG_CMD_NET
int board_eth_init(bd_t *bis)
{
	int rc = 0;
#ifdef CONFIG_LAN91C96
	rc = lan91c96_initialize(0, CONFIG_LAN91C96_BASE);
#endif
	return rc;
}
#endif
