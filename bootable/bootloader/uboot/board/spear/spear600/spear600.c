

#include <common.h>
#include <nand.h>
#include <asm/io.h>
#include <asm/arch/hardware.h>
#include <asm/arch/spr_defs.h>
#include <asm/arch/spr_misc.h>
#include <asm/arch/spr_nand.h>

int board_init(void)
{
	return spear_board_init(MACH_TYPE_SPEAR600);
}


int board_nand_init(struct nand_chip *nand)
{
	struct misc_regs *const misc_regs_p =
	    (struct misc_regs *)CONFIG_SPEAR_MISCBASE;

	if (!(readl(&misc_regs_p->auto_cfg_reg) & MISC_NANDDIS))
		return spear_nand_init(nand);

	return -1;
}
