

#include <common.h>
#include <nand.h>
#include <asm/io.h>

static void nand_addr_hwcontrol(struct mtd_info *mtd, int cmd, uint ctrl)
{
	struct nand_chip *this = mtd->priv;
	ulong IO_ADDR_W;

	if (ctrl & NAND_CTRL_CHANGE) {
		IO_ADDR_W = (ulong)this->IO_ADDR_W;

		IO_ADDR_W &= ~(CONFIG_SYS_NAND_ACTL_CLE |
				CONFIG_SYS_NAND_ACTL_ALE |
				CONFIG_SYS_NAND_ACTL_NCE);
		if (ctrl & NAND_CLE)
			IO_ADDR_W |= CONFIG_SYS_NAND_ACTL_CLE;
		if (ctrl & NAND_ALE)
			IO_ADDR_W |= CONFIG_SYS_NAND_ACTL_ALE;
		if (ctrl & NAND_NCE)
			IO_ADDR_W |= CONFIG_SYS_NAND_ACTL_NCE;

		this->IO_ADDR_W = (void *)IO_ADDR_W;
	}

	if (cmd != NAND_CMD_NONE)
		writeb(cmd, this->IO_ADDR_W);
}

int board_nand_init(struct nand_chip *nand)
{
	nand->ecc.mode = NAND_ECC_SOFT;
	nand->cmd_ctrl = nand_addr_hwcontrol;
	nand->chip_delay = CONFIG_SYS_NAND_ACTL_DELAY;

	return 0;
}