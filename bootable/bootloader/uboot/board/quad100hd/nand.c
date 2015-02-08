

#include <common.h>
#include <config.h>
#if defined(CONFIG_CMD_NAND)
#include <asm/gpio.h>
#include <asm/io.h>
#include <nand.h>

static void quad100hd_hwcontrol(struct mtd_info *mtd,
				int cmd, unsigned int ctrl)
{
	struct nand_chip *this = mtd->priv;

	if (ctrl & NAND_CTRL_CHANGE) {
		gpio_write_bit(CONFIG_SYS_NAND_CLE, !!(ctrl & NAND_CLE));
		gpio_write_bit(CONFIG_SYS_NAND_ALE, !!(ctrl & NAND_ALE));
		gpio_write_bit(CONFIG_SYS_NAND_CE, !(ctrl & NAND_NCE));
	}

	if (cmd != NAND_CMD_NONE)
		writeb(cmd, this->IO_ADDR_W);
}

static int quad100hd_nand_ready(struct mtd_info *mtd)
{
	return gpio_read_in_bit(CONFIG_SYS_NAND_RDY);
}

int board_nand_init(struct nand_chip *nand)
{
	/* Set address of hardware control function */
	nand->cmd_ctrl = quad100hd_hwcontrol;
	nand->dev_ready = quad100hd_nand_ready;
	nand->ecc.mode = NAND_ECC_SOFT;
	/* 15 us command delay time */
	nand->chip_delay =  20;

	/* Return happy */
	return 0;
}
#endif /* CONFIG_CMD_NAND */
