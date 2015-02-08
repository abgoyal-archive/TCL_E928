

#include <common.h>
#include <asm/io.h>

#if defined(CONFIG_CMD_NAND)

#include <nand.h>

#if defined(CONFIG_IDS852_REV1)
static void nc650_hwcontrol(struct mtd_info *mtd, int cmd, unsigned int ctrl)
{
	struct nand_chip *this = mtd->priv;

	if (ctrl & NAND_CTRL_CHANGE) {
		if ( ctrl & NAND_CLE )
			this->IO_ADDR_W += 2;
		else
			this->IO_ADDR_W -= 2;
		if ( ctrl & NAND_ALE )
			this->IO_ADDR_W += 1;
		else
			this->IO_ADDR_W -= 1;
	}

	if (cmd != NAND_CMD_NONE)
		writeb(cmd, this->IO_ADDR_W);
}
#elif defined(CONFIG_IDS852_REV2)
static void nc650_hwcontrol(struct mtd_info *mtd, int cmd, unsigned int ctrl)
{
	struct nand_chip *this = mtd->priv;

	if (ctrl & NAND_CTRL_CHANGE) {
		if ( ctrl & NAND_CLE )
			writeb(0, (volatile __u8 *) this->IO_ADDR_W + 0xa);
		else
			writeb(0, (volatile __u8 *) this->IO_ADDR_W) + 0x8);
		if ( ctrl & NAND_ALE )
			writeb(0, (volatile __u8 *) this->IO_ADDR_W) + 0x9);
		else
			writeb(0, (volatile __u8 *) this->IO_ADDR_W) + 0x8);
		if ( ctrl & NAND_NCE )
			writeb(0, (volatile __u8 *) this->IO_ADDR_W) + 0x8);
		else
			writeb(0, (volatile __u8 *) this->IO_ADDR_W) + 0xc);
	}

	if (cmd != NAND_CMD_NONE)
		writeb(cmd, this->IO_ADDR_W);
}
#else
#error Unknown IDS852 module revision
#endif

int board_nand_init(struct nand_chip *nand)
{

	nand->cmd_ctrl = nc650_hwcontrol;
	nand->ecc.mode = NAND_ECC_SOFT;
	nand->chip_delay = 12;
/*	nand->options = NAND_SAMSUNG_LP_OPTIONS;*/
	return 0;
}
#endif
