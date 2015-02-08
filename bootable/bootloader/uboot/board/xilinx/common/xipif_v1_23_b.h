
/* $Id: xipif_v1_23_b.h,v 1.1 2002/03/18 23:24:52 linnj Exp $ */

#ifndef XIPIF_H			/* prevent circular inclusions */
#define XIPIF_H			/* by using protection macros */

/***************************** Include Files *********************************/
#include "xbasic_types.h"
#include "xstatus.h"
#include "xversion.h"

/************************** Constant Definitions *****************************/

#define XIIF_V123B_DISR_OFFSET	   0UL	/* device interrupt status register */
#define XIIF_V123B_DIPR_OFFSET	   4UL	/* device interrupt pending register */
#define XIIF_V123B_DIER_OFFSET	   8UL	/* device interrupt enable register */
#define XIIF_V123B_DIIR_OFFSET	   24UL /* device interrupt ID register */
#define XIIF_V123B_DGIER_OFFSET	   28UL /* device global interrupt enable reg */
#define XIIF_V123B_IISR_OFFSET	   32UL /* IP interrupt status register */
#define XIIF_V123B_IIER_OFFSET	   40UL /* IP interrupt enable register */
#define XIIF_V123B_RESETR_OFFSET   64UL /* reset register */

#define XIIF_V123B_RESET_MASK		  0xAUL

#define XIIF_V123B_GINTR_ENABLE_MASK	  0x80000000UL

#define XIIF_V123B_ERROR_MASK		  1UL	/* LSB of the register */

#define XIIF_V123B_ERROR_INTERRUPT_ID	  0	/* interrupt bit #, (LSB = 0) */
#define XIIF_V123B_NO_INTERRUPT_ID	  128	/* no interrupts are pending */

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/


#define XIIF_V123B_RESET(RegBaseAddress) \
    XIo_Out32(RegBaseAddress + XIIF_V123B_RESETR_OFFSET, XIIF_V123B_RESET_MASK)

#define XIIF_V123B_WRITE_DISR(RegBaseAddress, Status) \
    XIo_Out32((RegBaseAddress) + XIIF_V123B_DISR_OFFSET, (Status))

#define XIIF_V123B_READ_DISR(RegBaseAddress) \
    XIo_In32((RegBaseAddress) + XIIF_V123B_DISR_OFFSET)

#define XIIF_V123B_WRITE_DIER(RegBaseAddress, Enable) \
    XIo_Out32((RegBaseAddress) + XIIF_V123B_DIER_OFFSET, (Enable))

#define XIIF_V123B_READ_DIER(RegBaseAddress) \
    XIo_In32((RegBaseAddress) + XIIF_V123B_DIER_OFFSET)

#define XIIF_V123B_READ_DIPR(RegBaseAddress) \
    XIo_In32((RegBaseAddress) + XIIF_V123B_DIPR_OFFSET)

#define XIIF_V123B_READ_DIIR(RegBaseAddress) \
    XIo_In32((RegBaseAddress) + XIIF_V123B_DIIR_OFFSET)

#define XIIF_V123B_GINTR_DISABLE(RegBaseAddress) \
    XIo_Out32((RegBaseAddress) + XIIF_V123B_DGIER_OFFSET, 0)

#define XIIF_V123B_GINTR_ENABLE(RegBaseAddress)		  \
    XIo_Out32((RegBaseAddress) + XIIF_V123B_DGIER_OFFSET, \
	       XIIF_V123B_GINTR_ENABLE_MASK)

#define XIIF_V123B_IS_GINTR_ENABLED(RegBaseAddress)		\
    (XIo_In32((RegBaseAddress) + XIIF_V123B_DGIER_OFFSET) ==	\
	      XIIF_V123B_GINTR_ENABLE_MASK)

#define XIIF_V123B_WRITE_IISR(RegBaseAddress, Status) \
    XIo_Out32((RegBaseAddress) + XIIF_V123B_IISR_OFFSET, (Status))

#define XIIF_V123B_READ_IISR(RegBaseAddress) \
    XIo_In32((RegBaseAddress) + XIIF_V123B_IISR_OFFSET)

#define XIIF_V123B_WRITE_IIER(RegBaseAddress, Enable) \
    XIo_Out32((RegBaseAddress) + XIIF_V123B_IIER_OFFSET, (Enable))

#define XIIF_V123B_READ_IIER(RegBaseAddress) \
    XIo_In32((RegBaseAddress) + XIIF_V123B_IIER_OFFSET)

/************************** Function Prototypes ******************************/

XStatus XIpIfV123b_SelfTest(u32 RegBaseAddress, u8 IpRegistersWidth);

#endif				/* end of protection macro */
