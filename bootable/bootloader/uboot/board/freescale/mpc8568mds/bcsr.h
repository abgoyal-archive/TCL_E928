

#ifndef __BCSR_H_
#define __BCSR_H_

#include <common.h>


#define BCSR_UCC1_GETH_EN	(0x1 << 7)
#define BCSR_UCC2_GETH_EN	(0x1 << 7)
#define BCSR_UCC1_MODE_MSK	(0x3 << 4)
#define BCSR_UCC2_MODE_MSK	(0x3 << 0)

/*BCSR Utils functions*/

void enable_8568mds_duart(void);
void enable_8568mds_flash_write(void);
void disable_8568mds_flash_write(void);
void enable_8568mds_qe_mdio(void);

#if defined(CONFIG_UEC_ETH1) || defined(CONFIG_UEC_ETH2)
void reset_8568mds_uccs(void);
#endif

#endif	/* __BCSR_H_ */
