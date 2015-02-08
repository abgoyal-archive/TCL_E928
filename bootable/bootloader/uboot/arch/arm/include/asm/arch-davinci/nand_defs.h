
#ifndef _NAND_DEFS_H_
#define _NAND_DEFS_H_

#include <asm/arch/hardware.h>

#ifdef CONFIG_SOC_DM646X
#define	MASK_CLE	0x80000
#define	MASK_ALE	0x40000
#else
#define	MASK_CLE	0x10
#define	MASK_ALE	0x08
#endif

#define NAND_READ_START		0x00
#define NAND_READ_END		0x30
#define NAND_STATUS		0x70

extern void davinci_nand_init(struct nand_chip *nand);

#endif
