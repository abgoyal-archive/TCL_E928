
/*****************************************************************************/
#ifndef XPACKET_FIFO_H		/* prevent circular inclusions */
#define XPACKET_FIFO_H		/* by using protection macros */

/***************************** Include Files *********************************/

#include "xbasic_types.h"
#include "xstatus.h"

/************************** Constant Definitions *****************************/

#define XPF_READ_FIFO_TYPE      0	/* a read FIFO */
#define XPF_WRITE_FIFO_TYPE     1	/* a write FIFO */

#define XPF_RESET_REG_OFFSET            0UL
#define XPF_MODULE_INFO_REG_OFFSET      0UL
#define XPF_COUNT_STATUS_REG_OFFSET     4UL

#define XPF_RESET_FIFO_MASK             0x0000000A

#define XPF_COUNT_MASK                  0x0000FFFF
#define XPF_DEADLOCK_MASK               0x20000000
#define XPF_ALMOST_EMPTY_FULL_MASK      0x40000000
#define XPF_EMPTY_FULL_MASK             0x80000000

/**************************** Type Definitions *******************************/

typedef struct {
	u32 RegBaseAddress;	/* Base address of registers */
	u32 IsReady;		/* Device is initialized and ready */
	u32 DataBaseAddress;	/* Base address of data for FIFOs */
} XPacketFifoV100b;

/***************** Macros (Inline Functions) Definitions *********************/

/*****************************************************************************/
#define XPF_V100B_RESET(InstancePtr) \
    XIo_Out32((InstancePtr)->RegBaseAddress + XPF_RESET_REG_OFFSET, XPF_RESET_FIFO_MASK);

/*****************************************************************************/
#define XPF_V100B_GET_COUNT(InstancePtr) \
    (XIo_In32((InstancePtr)->RegBaseAddress + XPF_COUNT_STATUS_REG_OFFSET) & \
    XPF_COUNT_MASK)

/*****************************************************************************/
#define XPF_V100B_IS_ALMOST_EMPTY(InstancePtr) \
    (XIo_In32((InstancePtr)->RegBaseAddress + XPF_COUNT_STATUS_REG_OFFSET) & \
    XPF_ALMOST_EMPTY_FULL_MASK)

/*****************************************************************************/
#define XPF_V100B_IS_ALMOST_FULL(InstancePtr) \
    (XIo_In32((InstancePtr)->RegBaseAddress + XPF_COUNT_STATUS_REG_OFFSET) & \
    XPF_ALMOST_EMPTY_FULL_MASK)

/*****************************************************************************/
#define XPF_V100B_IS_EMPTY(InstancePtr) \
    (XIo_In32((InstancePtr)->RegBaseAddress + XPF_COUNT_STATUS_REG_OFFSET) & \
    XPF_EMPTY_FULL_MASK)

/*****************************************************************************/
#define XPF_V100B_IS_FULL(InstancePtr) \
    (XIo_In32((InstancePtr)->RegBaseAddress + XPF_COUNT_STATUS_REG_OFFSET) & \
    XPF_EMPTY_FULL_MASK)

/*****************************************************************************/
#define XPF_V100B_IS_DEADLOCKED(InstancePtr) \
    (XIo_In32((InstancePtr)->RegBaseAddress + XPF_COUNT_STATUS_REG_OFFSET) & \
    XPF_DEADLOCK_MASK)

/************************** Function Prototypes ******************************/

/* Standard functions */

XStatus XPacketFifoV100b_Initialize(XPacketFifoV100b * InstancePtr,
				    u32 RegBaseAddress, u32 DataBaseAddress);
XStatus XPacketFifoV100b_SelfTest(XPacketFifoV100b * InstancePtr, u32 FifoType);

/* Data functions */

XStatus XPacketFifoV100b_Read(XPacketFifoV100b * InstancePtr,
			      u8 * ReadBufferPtr, u32 ByteCount);
XStatus XPacketFifoV100b_Write(XPacketFifoV100b * InstancePtr,
			       u8 * WriteBufferPtr, u32 ByteCount);

#endif				/* end of protection macro */
