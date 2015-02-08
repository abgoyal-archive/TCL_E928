

#include <common.h>
#include <asm/io.h>

#if defined(CONFIG_CMD_NAND)

#include <nand.h>

static void ppchameleonevb_hwcontrol(struct mtd_info *mtd, int cmd, unsigned int ctrl)
{
	struct nand_chip *this = mtd->priv;
	ulong base = (ulong) this->IO_ADDR_W;

	if (ctrl & NAND_CTRL_CHANGE) {
		if ( ctrl & NAND_CLE )
			MACRO_NAND_CTL_SETCLE((unsigned long)base);
		else
			MACRO_NAND_CTL_CLRCLE((unsigned long)base);
		if ( ctrl & NAND_ALE )
			MACRO_NAND_CTL_CLRCLE((unsigned long)base);
		else
			MACRO_NAND_CTL_CLRALE((unsigned long)base);
		if ( ctrl & NAND_NCE )
			MACRO_NAND_ENABLE_CE((unsigned long)base);
		else
			MACRO_NAND_DISABLE_CE((unsigned long)base);
	}

	if (cmd != NAND_CMD_NONE)
		writeb(cmd, this->IO_ADDR_W);
}


static int ppchameleonevb_device_ready(struct mtd_info *mtdinfo)
{
	struct nand_chip *this = mtdinfo->priv;
	ulong rb_gpio_pin;

	/* use the base addr to find out which chip are we dealing with */
	switch((ulong) this->IO_ADDR_W) {
	case CONFIG_SYS_NAND0_BASE:
		rb_gpio_pin = CONFIG_SYS_NAND0_RDY;
		break;
	case CONFIG_SYS_NAND1_BASE:
		rb_gpio_pin = CONFIG_SYS_NAND1_RDY;
		break;
	default: /* this should never happen */
		return 0;
		break;
	}

	if (in32(GPIO0_IR) & rb_gpio_pin)
		return 1;
	return 0;
}


int board_nand_init(struct nand_chip *nand)
{

	nand->cmd_ctrl = ppchameleonevb_hwcontrol;
	nand->dev_ready = ppchameleonevb_device_ready;
	nand->ecc.mode = NAND_ECC_SOFT;
	nand->chip_delay = NAND_BIG_DELAY_US;
	nand->options = NAND_SAMSUNG_LP_OPTIONS;
	return 0;
}
#endif
