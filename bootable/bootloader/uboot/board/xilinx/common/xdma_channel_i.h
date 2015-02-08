

#ifndef XDMA_CHANNEL_I_H	/* prevent circular inclusions */
#define XDMA_CHANNEL_I_H	/* by using protection macros */

/***************************** Include Files *********************************/

#include "xbasic_types.h"
#include "xstatus.h"
#include "xversion.h"

/************************** Constant Definitions *****************************/

#define XDC_DMA_CHANNEL_V1_00_A		"1.00a"

#define XDC_CONTROL_LAST_BD_MASK	0x02000000UL	/* last buffer descriptor */

#define XDC_STATUS_LAST_BD_MASK		0x10000000UL	/* last buffer descriptor */

#define XDC_RST_REG_OFFSET	0	/* reset register */
#define XDC_MI_REG_OFFSET	0	/* module information register */
#define XDC_DMAC_REG_OFFSET	4	/* DMA control register */
#define XDC_SA_REG_OFFSET	8	/* source address register */
#define XDC_DA_REG_OFFSET	12	/* destination address register */
#define XDC_LEN_REG_OFFSET	16	/* length register */
#define XDC_DMAS_REG_OFFSET	20	/* DMA status register */
#define XDC_BDA_REG_OFFSET	24	/* buffer descriptor address register */
#define XDC_SWCR_REG_OFFSET 28	/* software control register */
#define XDC_UPC_REG_OFFSET	32	/* unserviced packet count register */
#define	XDC_PCT_REG_OFFSET	36	/* packet count threshold register */
#define XDC_PWB_REG_OFFSET	40	/* packet wait bound register */
#define XDC_IS_REG_OFFSET	44	/* interrupt status register */
#define XDC_IE_REG_OFFSET	48	/* interrupt enable register */

#define XDC_RESET_MASK				0x0000000AUL

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Function Prototypes ******************************/

#endif				/* end of protection macro */
