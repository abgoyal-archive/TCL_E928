

#include <common.h>
#include <command.h>
#include <malloc.h>
#include <asm/arch/ixp425.h>

#include <miiphy.h>

#include "actux4_hw.h"

DECLARE_GLOBAL_DATA_PTR;

int board_init (void)
{
	gd->bd->bi_arch_number = MACH_TYPE_ACTUX4;

	/* adress of boot parameters */
	gd->bd->bi_boot_params = 0x00000100;

	GPIO_OUTPUT_CLEAR (CONFIG_SYS_GPIO_nPWRON);
	GPIO_OUTPUT_ENABLE (CONFIG_SYS_GPIO_nPWRON);

	GPIO_OUTPUT_CLEAR (CONFIG_SYS_GPIO_IORST);
	GPIO_OUTPUT_ENABLE (CONFIG_SYS_GPIO_IORST);

	/* led not populated on board*/
	GPIO_OUTPUT_ENABLE (CONFIG_SYS_GPIO_LED3);
	GPIO_OUTPUT_SET (CONFIG_SYS_GPIO_LED3);

	/* middle LED */
	GPIO_OUTPUT_ENABLE (CONFIG_SYS_GPIO_LED2);
	GPIO_OUTPUT_SET (CONFIG_SYS_GPIO_LED2);

	/* right LED */
	/* weak pulldown = LED weak on */
	GPIO_OUTPUT_DISABLE (CONFIG_SYS_GPIO_LED1);
	GPIO_OUTPUT_SET (CONFIG_SYS_GPIO_LED1);

	/* Setup GPIO's for Interrupt inputs */
	GPIO_OUTPUT_DISABLE (CONFIG_SYS_GPIO_USBINTA);
	GPIO_OUTPUT_DISABLE (CONFIG_SYS_GPIO_USBINTB);
	GPIO_OUTPUT_DISABLE (CONFIG_SYS_GPIO_USBINTC);
	GPIO_OUTPUT_DISABLE (CONFIG_SYS_GPIO_RTCINT);
	GPIO_OUTPUT_DISABLE (CONFIG_SYS_GPIO_PCI_INTA);
	GPIO_OUTPUT_DISABLE (CONFIG_SYS_GPIO_PCI_INTB);

	GPIO_INT_ACT_LOW_SET (CONFIG_SYS_GPIO_USBINTA);
	GPIO_INT_ACT_LOW_SET (CONFIG_SYS_GPIO_USBINTB);
	GPIO_INT_ACT_LOW_SET (CONFIG_SYS_GPIO_USBINTC);
	GPIO_INT_ACT_LOW_SET (CONFIG_SYS_GPIO_RTCINT);
	GPIO_INT_ACT_LOW_SET (CONFIG_SYS_GPIO_PCI_INTA);
	GPIO_INT_ACT_LOW_SET (CONFIG_SYS_GPIO_PCI_INTB);

	/* Setup GPIO's for 33MHz clock output */
	*IXP425_GPIO_GPCLKR = 0x011001FF;
	GPIO_OUTPUT_ENABLE (CONFIG_SYS_GPIO_EXTBUS_CLK);
	GPIO_OUTPUT_ENABLE (CONFIG_SYS_GPIO_PCI_CLK);

	*IXP425_EXP_CS1 = 0xbd113c42;

	udelay (10000);
	GPIO_OUTPUT_SET (CONFIG_SYS_GPIO_IORST);
	udelay (10000);
	GPIO_OUTPUT_CLEAR (CONFIG_SYS_GPIO_IORST);
	udelay (10000);
	GPIO_OUTPUT_SET (CONFIG_SYS_GPIO_IORST);

	return 0;
}

/* Check Board Identity */
int checkboard (void)
{
	puts ("Board: AcTux-4\n");
	return (0);
}

int dram_init (void)
{
	gd->bd->bi_dram[0].start = PHYS_SDRAM_1;
	gd->bd->bi_dram[0].size = PHYS_SDRAM_1_SIZE;

	return (0);
}

ulong board_flash_get_legacy (ulong base, int banknum, flash_info_t * info)
{
	if (banknum == 0) {	/* non-CFI boot flash */
		info->portwidth = 1;
		info->chipwidth = 1;
		info->interface = FLASH_CFI_X8;
		return 1;
	} else
		return 0;
}
