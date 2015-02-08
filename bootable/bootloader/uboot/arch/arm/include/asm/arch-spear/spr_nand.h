

#ifndef __SPR_NAND_H__
#define __SPR_NAND_H__

struct fsmc_regs {
	u32 reserved_1[0x10];
	u32 genmemctrl_pc;
	u32 reserved_2;
	u32 genmemctrl_comm;
	u32 genmemctrl_attrib;
	u32 reserved_3;
	u32 genmemctrl_ecc;
};

/* genmemctrl_pc register definitions */
#define FSMC_RESET		(1 << 0)
#define FSMC_WAITON		(1 << 1)
#define FSMC_ENABLE		(1 << 2)
#define FSMC_DEVTYPE_NAND	(1 << 3)
#define FSMC_DEVWID_8		(0 << 4)
#define FSMC_DEVWID_16		(1 << 4)
#define FSMC_ECCEN		(1 << 6)
#define FSMC_ECCPLEN_512	(0 << 7)
#define FSMC_ECCPLEN_256	(1 << 7)
#define FSMC_TCLR_1		(1 << 9)
#define FSMC_TAR_1		(1 << 13)

/* genmemctrl_comm register definitions */
#define FSMC_TSET_0		(0 << 0)
#define FSMC_TWAIT_6		(6 << 8)
#define FSMC_THOLD_4		(4 << 16)
#define FSMC_THIZ_1		(1 << 24)

extern int spear_nand_init(struct nand_chip *nand);
#endif
