

#include <common.h>
#include <nand.h>
#include <asm/io.h>
#include <asm/arch/hardware.h>
#include <asm/arch/emif_defs.h>
#include <asm/arch/nand_defs.h>
#include <asm/arch/gpio_defs.h>
#include <netdev.h>
#include "../common/misc.h"

DECLARE_GLOBAL_DATA_PTR;

int board_init(void)
{
	gd->bd->bi_arch_number = MACH_TYPE_DAVINCI_DM365_EVM;
	gd->bd->bi_boot_params = PHYS_SDRAM_1 + 0x100;

	return 0;
}

#ifdef CONFIG_DRIVER_TI_EMAC
int board_eth_init(bd_t *bis)
{
	uint8_t eeprom_enetaddr[6];
	int i;
	struct davinci_gpio *gpio1_base =
			(struct davinci_gpio *)DAVINCI_GPIO_BANK01;

	/* Configure PINMUX 3 to enable EMAC pins */
	writel((readl(PINMUX3) | 0x1affff), PINMUX3);

	/* Configure GPIO20 as output */
	writel((readl(&gpio1_base->dir) & ~(1 << 20)), &gpio1_base->dir);

	/* Toggle GPIO 20 */
	for (i = 0; i < 20; i++) {
		/* GPIO 20 low */
		writel((readl(&gpio1_base->out_data) & ~(1 << 20)),
						&gpio1_base->out_data);

		udelay(1000);

		/* GPIO 20 high */
		writel((readl(&gpio1_base->out_data) | (1 << 20)),
						&gpio1_base->out_data);
	}

	/* Configure I2C pins so that EEPROM can be read */
	writel((readl(PINMUX3) | 0x01400000), PINMUX3);

	/* Read Ethernet MAC address from EEPROM */
	if (dvevm_read_mac_address(eeprom_enetaddr))
		dv_configure_mac_address(eeprom_enetaddr);

	davinci_emac_initialize();

	return 0;
}
#endif

#ifdef CONFIG_NAND_DAVINCI
static void nand_dm365evm_select_chip(struct mtd_info *mtd, int chip)
{
	struct nand_chip	*this = mtd->priv;
	unsigned long		wbase = (unsigned long) this->IO_ADDR_W;
	unsigned long		rbase = (unsigned long) this->IO_ADDR_R;

	if (chip == 1) {
		__set_bit(14, &wbase);
		__set_bit(14, &rbase);
	} else {
		__clear_bit(14, &wbase);
		__clear_bit(14, &rbase);
	}
	this->IO_ADDR_W = (void *)wbase;
	this->IO_ADDR_R = (void *)rbase;
}

int board_nand_init(struct nand_chip *nand)
{
	davinci_nand_init(nand);
	nand->select_chip = nand_dm365evm_select_chip;
	return 0;
}
#endif
