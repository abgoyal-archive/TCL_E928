

#ifndef XDMA_CHANNEL_H		/* prevent circular inclusions */
#define XDMA_CHANNEL_H		/* by using protection macros */

/***************************** Include Files *********************************/

#include "xdma_channel_i.h"	/* constants shared with buffer descriptor */
#include "xbasic_types.h"
#include "xstatus.h"
#include "xversion.h"
#include "xbuf_descriptor.h"

/************************** Constant Definitions *****************************/

#define XDC_DMACR_SOURCE_INCR_MASK	0x80000000UL	/* increment source address */
#define XDC_DMACR_DEST_INCR_MASK	0x40000000UL	/* increment dest address */
#define XDC_DMACR_SOURCE_LOCAL_MASK 0x20000000UL	/* local source address */
#define XDC_DMACR_DEST_LOCAL_MASK	0x10000000UL	/* local dest address */
#define XDC_DMACR_SG_DISABLE_MASK	0x08000000UL	/* scatter gather disable */
#define XDC_DMACR_GEN_BD_INTR_MASK	0x04000000UL	/* descriptor interrupt */
#define XDC_DMACR_LAST_BD_MASK		XDC_CONTROL_LAST_BD_MASK	/* last buffer */
															 /*     descriptor  */

#define XDC_DMASR_BUSY_MASK			0x80000000UL	/* channel is busy */
#define XDC_DMASR_BUS_ERROR_MASK	0x40000000UL	/* bus error occurred */
#define XDC_DMASR_BUS_TIMEOUT_MASK	0x20000000UL	/* bus timeout occurred */
#define XDC_DMASR_LAST_BD_MASK		XDC_STATUS_LAST_BD_MASK	/* last buffer */
														    /* descriptor  */
#define XDC_DMASR_SG_BUSY_MASK		0x08000000UL	/* scatter gather is busy */

#define XDC_IXR_DMA_DONE_MASK		0x1UL	/* dma operation done */
#define XDC_IXR_DMA_ERROR_MASK	    0x2UL	/* dma operation error */
#define XDC_IXR_PKT_DONE_MASK	    0x4UL	/* packet done */
#define XDC_IXR_PKT_THRESHOLD_MASK	0x8UL	/* packet count threshold */
#define XDC_IXR_PKT_WAIT_BOUND_MASK 0x10UL	/* packet wait bound reached */
#define XDC_IXR_SG_DISABLE_ACK_MASK 0x20UL	/* scatter gather disable
						   acknowledge occurred */
#define XDC_IXR_SG_END_MASK			0x40UL	/* last buffer descriptor
							   disabled scatter gather */
#define XDC_IXR_BD_MASK				0x80UL	/* buffer descriptor done */

/**************************** Type Definitions *******************************/

typedef struct XDmaChannelTag {
	XVersion Version;	/* version of the driver */
	u32 RegBaseAddress;	/* base address of registers */
	u32 IsReady;		/* device is initialized and ready */

	XBufDescriptor *PutPtr;	/* keep track of where to put into list */
	XBufDescriptor *GetPtr;	/* keep track of where to get from list */
	XBufDescriptor *CommitPtr;	/* keep track of where to commit in list */
	XBufDescriptor *LastPtr;	/* keep track of the last put in the list */
	u32 TotalDescriptorCount;	/* total # of descriptors in the list */
	u32 ActiveDescriptorCount;	/* # of descriptors pointing to buffers
					   * in the buffer descriptor list */
} XDmaChannel;

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Function Prototypes ******************************/

XStatus XDmaChannel_Initialize(XDmaChannel * InstancePtr, u32 BaseAddress);
u32 XDmaChannel_IsReady(XDmaChannel * InstancePtr);
XVersion *XDmaChannel_GetVersion(XDmaChannel * InstancePtr);
XStatus XDmaChannel_SelfTest(XDmaChannel * InstancePtr);
void XDmaChannel_Reset(XDmaChannel * InstancePtr);

/* Control functions */

u32 XDmaChannel_GetControl(XDmaChannel * InstancePtr);
void XDmaChannel_SetControl(XDmaChannel * InstancePtr, u32 Control);

/* Status functions */

u32 XDmaChannel_GetStatus(XDmaChannel * InstancePtr);
void XDmaChannel_SetIntrStatus(XDmaChannel * InstancePtr, u32 Status);
u32 XDmaChannel_GetIntrStatus(XDmaChannel * InstancePtr);
void XDmaChannel_SetIntrEnable(XDmaChannel * InstancePtr, u32 Enable);
u32 XDmaChannel_GetIntrEnable(XDmaChannel * InstancePtr);

/* DMA without scatter gather functions */

void XDmaChannel_Transfer(XDmaChannel * InstancePtr,
			  u32 * SourcePtr, u32 * DestinationPtr, u32 ByteCount);

/* Scatter gather functions */

XStatus XDmaChannel_SgStart(XDmaChannel * InstancePtr);
XStatus XDmaChannel_SgStop(XDmaChannel * InstancePtr,
			   XBufDescriptor ** BufDescriptorPtr);
XStatus XDmaChannel_CreateSgList(XDmaChannel * InstancePtr,
				 u32 * MemoryPtr, u32 ByteCount);
u32 XDmaChannel_IsSgListEmpty(XDmaChannel * InstancePtr);

XStatus XDmaChannel_PutDescriptor(XDmaChannel * InstancePtr,
				  XBufDescriptor * BufDescriptorPtr);
XStatus XDmaChannel_CommitPuts(XDmaChannel * InstancePtr);
XStatus XDmaChannel_GetDescriptor(XDmaChannel * InstancePtr,
				  XBufDescriptor ** BufDescriptorPtr);

/* Packet functions for interrupt collescing */

u32 XDmaChannel_GetPktCount(XDmaChannel * InstancePtr);
void XDmaChannel_DecrementPktCount(XDmaChannel * InstancePtr);
XStatus XDmaChannel_SetPktThreshold(XDmaChannel * InstancePtr, u8 Threshold);
u8 XDmaChannel_GetPktThreshold(XDmaChannel * InstancePtr);
void XDmaChannel_SetPktWaitBound(XDmaChannel * InstancePtr, u32 WaitBound);
u32 XDmaChannel_GetPktWaitBound(XDmaChannel * InstancePtr);

#endif				/* end of protection macro */
