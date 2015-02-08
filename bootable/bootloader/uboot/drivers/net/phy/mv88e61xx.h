

#ifndef _MV88E61XX_H
#define _MV88E61XX_H

#include <miiphy.h>

#define MV88E61XX_CPU_PORT		0x5
#define MV88E61XX_MAX_PORTS_NUM		0x6

#define MV88E61XX_PHY_TIMEOUT		100000

#define MV88E61XX_PRT_STS_REG		0x1
#define MV88E61XX_PRT_CTRL_REG		0x4
#define MV88E61XX_PRT_VMAP_REG		0x6
#define MV88E61XX_PRT_VID_REG		0x7

#define MV88E61XX_PRT_OFST		0x10
#define MV88E61XX_PHY_CMD		0x18
#define MV88E61XX_PHY_DATA		0x19
#define MV88E61XX_RGMII_TIMECTRL_REG	0x1A
#define MV88E61XX_GLB2REG_DEVADR	0x1C

#define MV88E61XX_BUSY_OFST		15
#define MV88E61XX_MODE_OFST		12
#define MV88E61XX_OP_OFST			10
#define MV88E61XX_ADDR_OFST		5

#ifdef CONFIG_MV88E61XX_MULTICHIP_ADRMODE
static int mv88e61xx_busychk_multic(char *name, u32 devaddr);
static void mv88e61xx_wr_phy(char *name, u32 phy_adr, u32 reg_ofs, u16 data);
static void mv88e61xx_rd_phy(char *name, u32 phy_adr, u32 reg_ofs, u16 * data);
#define WR_PHY mv88e61xx_wr_phy
#define RD_PHY mv88e61xx_rd_phy
#else
#define WR_PHY miiphy_write
#define RD_PHY miiphy_read
#endif /* CONFIG_MV88E61XX_MULTICHIP_ADRMODE */

#endif /* _MV88E61XX_H */
