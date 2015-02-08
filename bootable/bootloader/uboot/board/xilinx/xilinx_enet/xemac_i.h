
/*****************************************************************************/

#ifndef XEMAC_I_H		/* prevent circular inclusions */
#define XEMAC_I_H		/* by using protection macros */

/***************************** Include Files *********************************/

#include "xemac.h"
#include "xemac_l.h"

/************************** Constant Definitions *****************************/

#define XEM_DFT_SEND_BD_MASK	(XDC_DMACR_SOURCE_INCR_MASK | \
				 XDC_DMACR_DEST_LOCAL_MASK)
#define XEM_DFT_RECV_BD_MASK	(XDC_DMACR_DEST_INCR_MASK |  \
				 XDC_DMACR_SOURCE_LOCAL_MASK)

#define XEM_IPIF_EMAC_MASK	0x00000004UL	/* MAC interrupt */
#define XEM_IPIF_SEND_DMA_MASK	0x00000008UL	/* Send DMA interrupt */
#define XEM_IPIF_RECV_DMA_MASK	0x00000010UL	/* Receive DMA interrupt */
#define XEM_IPIF_RECV_FIFO_MASK 0x00000020UL	/* Receive FIFO interrupt */
#define XEM_IPIF_SEND_FIFO_MASK 0x00000040UL	/* Send FIFO interrupt */

#define XEM_IPIF_DMA_DFT_MASK	(XEM_IPIF_SEND_DMA_MASK |   \
				 XEM_IPIF_RECV_DMA_MASK |   \
				 XEM_IPIF_EMAC_MASK |	    \
				 XEM_IPIF_SEND_FIFO_MASK |  \
				 XEM_IPIF_RECV_FIFO_MASK)

#define XEM_IPIF_FIFO_DFT_MASK	(XEM_IPIF_EMAC_MASK |	    \
				 XEM_IPIF_SEND_FIFO_MASK |  \
				 XEM_IPIF_RECV_FIFO_MASK)

#define XEM_IPIF_DMA_DEV_INTR_COUNT   7 /* Number of interrupt sources */
#define XEM_IPIF_FIFO_DEV_INTR_COUNT  5 /* Number of interrupt sources */
#define XEM_IPIF_DEVICE_INTR_COUNT  7	/* Number of interrupt sources */
#define XEM_IPIF_IP_INTR_COUNT	    22	/* Number of MAC interrupts */

/* a mask for all transmit interrupts, used in polled mode */
#define XEM_EIR_XMIT_ALL_MASK	(XEM_EIR_XMIT_DONE_MASK |	    \
				 XEM_EIR_XMIT_ERROR_MASK |	    \
				 XEM_EIR_XMIT_SFIFO_EMPTY_MASK |    \
				 XEM_EIR_XMIT_LFIFO_FULL_MASK)

/* a mask for all receive interrupts, used in polled mode */
#define XEM_EIR_RECV_ALL_MASK	(XEM_EIR_RECV_DONE_MASK |	    \
				 XEM_EIR_RECV_ERROR_MASK |	    \
				 XEM_EIR_RECV_LFIFO_EMPTY_MASK |    \
				 XEM_EIR_RECV_LFIFO_OVER_MASK |	    \
				 XEM_EIR_RECV_LFIFO_UNDER_MASK |    \
				 XEM_EIR_RECV_DFIFO_OVER_MASK |	    \
				 XEM_EIR_RECV_MISSED_FRAME_MASK |   \
				 XEM_EIR_RECV_COLLISION_MASK |	    \
				 XEM_EIR_RECV_FCS_ERROR_MASK |	    \
				 XEM_EIR_RECV_LEN_ERROR_MASK |	    \
				 XEM_EIR_RECV_SHORT_ERROR_MASK |    \
				 XEM_EIR_RECV_LONG_ERROR_MASK |	    \
				 XEM_EIR_RECV_ALIGN_ERROR_MASK)

/* a default interrupt mask for scatter-gather DMA operation */
#define XEM_EIR_DFT_SG_MASK    (XEM_EIR_RECV_ERROR_MASK |	    \
				XEM_EIR_RECV_LFIFO_OVER_MASK |	    \
				XEM_EIR_RECV_LFIFO_UNDER_MASK |	    \
				XEM_EIR_XMIT_SFIFO_OVER_MASK |	    \
				XEM_EIR_XMIT_SFIFO_UNDER_MASK |	    \
				XEM_EIR_XMIT_LFIFO_OVER_MASK |	    \
				XEM_EIR_XMIT_LFIFO_UNDER_MASK |	    \
				XEM_EIR_RECV_DFIFO_OVER_MASK |	    \
				XEM_EIR_RECV_MISSED_FRAME_MASK |    \
				XEM_EIR_RECV_COLLISION_MASK |	    \
				XEM_EIR_RECV_FCS_ERROR_MASK |	    \
				XEM_EIR_RECV_LEN_ERROR_MASK |	    \
				XEM_EIR_RECV_SHORT_ERROR_MASK |	    \
				XEM_EIR_RECV_LONG_ERROR_MASK |	    \
				XEM_EIR_RECV_ALIGN_ERROR_MASK)

/* a default interrupt mask for non-DMA operation (direct FIFOs) */
#define XEM_EIR_DFT_FIFO_MASK  (XEM_EIR_XMIT_DONE_MASK |	    \
				XEM_EIR_RECV_DONE_MASK |	    \
				XEM_EIR_DFT_SG_MASK)

#define XEM_DMA_SG_INTR_MASK	(XDC_IXR_DMA_ERROR_MASK	 |	\
				 XDC_IXR_PKT_THRESHOLD_MASK |	\
				 XDC_IXR_PKT_WAIT_BOUND_MASK |	\
				 XDC_IXR_SG_END_MASK)

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/

/*****************************************************************************/
#define XEmac_mClearStruct(StructPtr, NumBytes)	    \
{						    \
    int i;					    \
    u8 *BytePtr = (u8 *)(StructPtr);	    \
    for (i=0; i < (unsigned int)(NumBytes); i++)    \
    {						    \
	*BytePtr++ = 0;				    \
    }						    \
}

/************************** Variable Definitions *****************************/

extern XEmac_Config XEmac_ConfigTable[];

/************************** Function Prototypes ******************************/

void XEmac_CheckEmacError(XEmac * InstancePtr, u32 IntrStatus);
void XEmac_CheckFifoRecvError(XEmac * InstancePtr);
void XEmac_CheckFifoSendError(XEmac * InstancePtr);

#endif				/* end of protection macro */
