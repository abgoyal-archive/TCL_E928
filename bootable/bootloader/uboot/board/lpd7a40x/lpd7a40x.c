

#include <common.h>
#include <netdev.h>
#if defined(CONFIG_LH7A400)
#include <lh7a400.h>
#elif defined(CONFIG_LH7A404)
#include <lh7a404.h>
#else
#error "No CPU defined!"
#endif
#include <asm/mach-types.h>

#include <lpd7a400_cpld.h>

DECLARE_GLOBAL_DATA_PTR;


int board_init (void)
{
	/* set up the I/O ports */

	/* enable flash programming */
	*(LPD7A400_CPLD_REGPTR(LPD7A400_CPLD_FLASH_REG)) |= FLASH_FPEN;

	/* Auto wakeup, LCD disable, WLAN enable */
	*(LPD7A400_CPLD_REGPTR(LPD7A400_CPLD_CECTL_REG)) &=
		~(CECTL_AWKP|CECTL_LCDV|CECTL_WLPE);

	/* Status LED 2 on (leds are active low) */
	*(LPD7A400_CPLD_REGPTR(LPD7A400_CPLD_EXTGPIO_REG)) =
		(EXTGPIO_STATUS1|EXTGPIO_GPIO1) & ~(EXTGPIO_STATUS2);

#if defined(CONFIG_LH7A400)
	/* arch number of Logic-Board - MACH_TYPE_LPD7A400 */
	gd->bd->bi_arch_number = MACH_TYPE_LPD7A400;
#elif defined(CONFIG_LH7A404)
	/* arch number of Logic-Board - MACH_TYPE_LPD7A400 */
	gd->bd->bi_arch_number = MACH_TYPE_LPD7A404;
#endif

	/* adress of boot parameters */
	gd->bd->bi_boot_params = 0xc0000100;

	return 0;
}

int dram_init (void)
{
	gd->bd->bi_dram[0].start = PHYS_SDRAM_1;
	gd->bd->bi_dram[0].size = PHYS_SDRAM_1_SIZE;

	return 0;
}

#ifdef CONFIG_CMD_NET
int board_eth_init(bd_t *bis)
{
	int rc = 0;
#ifdef CONFIG_SMC91111
	rc = smc91111_initialize(0, CONFIG_SMC91111_BASE);
#endif
	return rc;
}
#endif
