
/*****************************************************************************/

#ifndef XEMAC_H			/* prevent circular inclusions */
#define XEMAC_H			/* by using protection macros */

/***************************** Include Files *********************************/

#include <config.h>
#include "xbasic_types.h"
#include "xstatus.h"
#include "xpacket_fifo_v1_00_b.h"	/* Uses v1.00b of Packet Fifo */
#include "xdma_channel.h"

/************************** Constant Definitions *****************************/

#define XEM_DEVICE_NAME	    "xemac"
#define XEM_DEVICE_DESC	    "Xilinx Ethernet 10/100 MAC"

#define XEM_UNICAST_OPTION	  0x00000001UL
#define XEM_BROADCAST_OPTION	  0x00000002UL
#define XEM_PROMISC_OPTION	  0x00000004UL
#define XEM_FDUPLEX_OPTION	  0x00000008UL
#define XEM_POLLED_OPTION	  0x00000010UL
#define XEM_LOOPBACK_OPTION	  0x00000020UL
#define XEM_FLOW_CONTROL_OPTION	  0x00000080UL
#define XEM_INSERT_PAD_OPTION	  0x00000100UL
#define XEM_INSERT_FCS_OPTION	  0x00000200UL
#define XEM_INSERT_ADDR_OPTION	  0x00000400UL
#define XEM_OVWRT_ADDR_OPTION	  0x00000800UL
#define XEM_STRIP_PAD_FCS_OPTION  0x00002000UL
/*@}*/
/* NOT SUPPORTED YET... */
#define XEM_MULTICAST_OPTION	  0x00000040UL

#define XEM_SGDMA_DFT_THRESHOLD	    1	/* Default pkt threshold */
#define XEM_SGDMA_MAX_THRESHOLD	    255 /* Maximum pkt theshold */
#define XEM_SGDMA_DFT_WAITBOUND	    5	/* Default pkt wait bound (msec) */
#define XEM_SGDMA_MAX_WAITBOUND	    1023	/* Maximum pkt wait bound (msec) */

#define XEM_SEND    1
#define XEM_RECV    2

#define XEM_SGDMA_NODELAY     0 /* start SG DMA immediately */
#define XEM_SGDMA_DELAY	      1 /* do not start SG DMA */

#define XEM_CFG_NO_IPIF		    0	/* Not supported by the driver */
#define XEM_CFG_NO_DMA		    1	/* No DMA */
#define XEM_CFG_SIMPLE_DMA	    2	/* Simple DMA */
#define XEM_CFG_DMA_SG		    3	/* DMA scatter gather */

#define XEM_MAC_ADDR_SIZE   6	/* six-byte MAC address */
#define XEM_MTU		    1500	/* max size of Ethernet frame */
#define XEM_HDR_SIZE	    14	/* size of Ethernet header */
#define XEM_HDR_VLAN_SIZE   18	/* size of Ethernet header with VLAN */
#define XEM_TRL_SIZE	    4	/* size of Ethernet trailer (FCS) */
#define XEM_MAX_FRAME_SIZE  (XEM_MTU + XEM_HDR_SIZE + XEM_TRL_SIZE)
#define XEM_MAX_VLAN_FRAME_SIZE	 (XEM_MTU + XEM_HDR_VLAN_SIZE + XEM_TRL_SIZE)

#define XEM_MIN_RECV_BUFS   32	/* minimum # of recv buffers */
#define XEM_DFT_RECV_BUFS   64	/* default # of recv buffers */

#define XEM_MIN_SEND_BUFS   16	/* minimum # of send buffers */
#define XEM_DFT_SEND_BUFS   32	/* default # of send buffers */

#define XEM_MIN_BUFFERS	    (XEM_MIN_RECV_BUFS + XEM_MIN_SEND_BUFS)
#define XEM_DFT_BUFFERS	    (XEM_DFT_RECV_BUFS + XEM_DFT_SEND_BUFS)

#define XEM_MIN_RECV_DESC   16	/* minimum # of recv descriptors */
#define XEM_DFT_RECV_DESC   32	/* default # of recv descriptors */

#define XEM_MIN_SEND_DESC   8	/* minimum # of send descriptors */
#define XEM_DFT_SEND_DESC   16	/* default # of send descriptors */

/**************************** Type Definitions *******************************/

typedef struct {
	u32 XmitFrames;		 /**< Number of frames transmitted */
	u32 XmitBytes;		 /**< Number of bytes transmitted */
	u32 XmitLateCollisionErrors;
				 /**< Number of transmission failures
					  due to late collisions */
	u32 XmitExcessDeferral;	 /**< Number of transmission failures
					  due o excess collision deferrals */
	u32 XmitOverrunErrors;	 /**< Number of transmit overrun errors */
	u32 XmitUnderrunErrors;	 /**< Number of transmit underrun errors */
	u32 RecvFrames;		 /**< Number of frames received */
	u32 RecvBytes;		 /**< Number of bytes received */
	u32 RecvFcsErrors;	 /**< Number of frames discarded due
					  to FCS errors */
	u32 RecvAlignmentErrors; /**< Number of frames received with
					  alignment errors */
	u32 RecvOverrunErrors;	 /**< Number of frames discarded due
					  to overrun errors */
	u32 RecvUnderrunErrors;	 /**< Number of recv underrun errors */
	u32 RecvMissedFrameErrors;
				 /**< Number of frames missed by MAC */
	u32 RecvCollisionErrors; /**< Number of frames discarded due
					  to collisions */
	u32 RecvLengthFieldErrors;
				 /**< Number of frames discarded with
					  invalid length field */
	u32 RecvShortErrors;	 /**< Number of short frames discarded */
	u32 RecvLongErrors;	 /**< Number of long frames discarded */
	u32 DmaErrors;		 /**< Number of DMA errors since init */
	u32 FifoErrors;		 /**< Number of FIFO errors since init */
	u32 RecvInterrupts;	 /**< Number of receive interrupts */
	u32 XmitInterrupts;	 /**< Number of transmit interrupts */
	u32 EmacInterrupts;	 /**< Number of MAC (device) interrupts */
	u32 TotalIntrs;		 /**< Total interrupts */
} XEmac_Stats;

typedef struct {
	u16 DeviceId;	    /**< Unique ID  of device */
	u32 BaseAddress;    /**< Register base address */
	u32 HasCounters;   /**< Does device have counters? */
	u8 IpIfDmaConfig;   /**< IPIF/DMA hardware configuration */
	u32 HasMii;	   /**< Does device support MII? */

} XEmac_Config;

typedef void (*XEmac_SgHandler) (void *CallBackRef, XBufDescriptor * BdPtr,
				 u32 NumBds);

typedef void (*XEmac_FifoHandler) (void *CallBackRef);

typedef void (*XEmac_ErrorHandler) (void *CallBackRef, XStatus ErrorCode);
/*@}*/

typedef struct {
	u32 BaseAddress;	/* Base address (of IPIF) */
	u32 IsStarted;		/* Device is currently started */
	u32 IsReady;		/* Device is initialized and ready */
	u32 IsPolled;		/* Device is in polled mode */
	u8 IpIfDmaConfig;	/* IPIF/DMA hardware configuration */
	u32 HasMii;		/* Does device support MII? */
	u32 HasMulticastHash;	/* Does device support multicast hash table? */

	XEmac_Stats Stats;
	XPacketFifoV100b RecvFifo;	/* FIFO used to receive frames */
	XPacketFifoV100b SendFifo;	/* FIFO used to send frames */

	/*
	 * Callbacks
	 */
	XEmac_FifoHandler FifoRecvHandler;	/* for non-DMA/simple DMA interrupts */
	void *FifoRecvRef;
	XEmac_FifoHandler FifoSendHandler;	/* for non-DMA/simple DMA interrupts */
	void *FifoSendRef;
	XEmac_ErrorHandler ErrorHandler;	/* for asynchronous errors */
	void *ErrorRef;

	XDmaChannel RecvChannel;	/* DMA receive channel driver */
	XDmaChannel SendChannel;	/* DMA send channel driver */

	XEmac_SgHandler SgRecvHandler;	/* callback for scatter-gather DMA */
	void *SgRecvRef;
	XEmac_SgHandler SgSendHandler;	/* callback for scatter-gather DMA */
	void *SgSendRef;
} XEmac;

/***************** Macros (Inline Functions) Definitions *********************/

/*****************************************************************************/
#define XEmac_mIsSgDma(InstancePtr) \
	    ((InstancePtr)->IpIfDmaConfig == XEM_CFG_DMA_SG)

/*****************************************************************************/
#define XEmac_mIsSimpleDma(InstancePtr) \
	    ((InstancePtr)->IpIfDmaConfig == XEM_CFG_SIMPLE_DMA)

/*****************************************************************************/
#define XEmac_mIsDma(InstancePtr) \
	    (XEmac_mIsSimpleDma(InstancePtr) || XEmac_mIsSgDma(InstancePtr))

/************************** Function Prototypes ******************************/

XStatus XEmac_Initialize(XEmac * InstancePtr, u16 DeviceId);
XStatus XEmac_Start(XEmac * InstancePtr);
XStatus XEmac_Stop(XEmac * InstancePtr);
void XEmac_Reset(XEmac * InstancePtr);
XEmac_Config *XEmac_LookupConfig(u16 DeviceId);

XStatus XEmac_SelfTest(XEmac * InstancePtr);

XStatus XEmac_PollSend(XEmac * InstancePtr, u8 * BufPtr, u32 ByteCount);
XStatus XEmac_PollRecv(XEmac * InstancePtr, u8 * BufPtr, u32 * ByteCountPtr);

XStatus XEmac_SgSend(XEmac * InstancePtr, XBufDescriptor * BdPtr, int Delay);
XStatus XEmac_SgRecv(XEmac * InstancePtr, XBufDescriptor * BdPtr);
XStatus XEmac_SetPktThreshold(XEmac * InstancePtr, u32 Direction, u8 Threshold);
XStatus XEmac_GetPktThreshold(XEmac * InstancePtr, u32 Direction,
			      u8 * ThreshPtr);
XStatus XEmac_SetPktWaitBound(XEmac * InstancePtr, u32 Direction,
			      u32 TimerValue);
XStatus XEmac_GetPktWaitBound(XEmac * InstancePtr, u32 Direction,
			      u32 * WaitPtr);
XStatus XEmac_SetSgRecvSpace(XEmac * InstancePtr, u32 * MemoryPtr,
			     u32 ByteCount);
XStatus XEmac_SetSgSendSpace(XEmac * InstancePtr, u32 * MemoryPtr,
			     u32 ByteCount);
void XEmac_SetSgRecvHandler(XEmac * InstancePtr, void *CallBackRef,
			    XEmac_SgHandler FuncPtr);
void XEmac_SetSgSendHandler(XEmac * InstancePtr, void *CallBackRef,
			    XEmac_SgHandler FuncPtr);

void XEmac_IntrHandlerDma(void *InstancePtr);	/* interrupt handler */

XStatus XEmac_FifoSend(XEmac * InstancePtr, u8 * BufPtr, u32 ByteCount);
XStatus XEmac_FifoRecv(XEmac * InstancePtr, u8 * BufPtr, u32 * ByteCountPtr);
void XEmac_SetFifoRecvHandler(XEmac * InstancePtr, void *CallBackRef,
			      XEmac_FifoHandler FuncPtr);
void XEmac_SetFifoSendHandler(XEmac * InstancePtr, void *CallBackRef,
			      XEmac_FifoHandler FuncPtr);

void XEmac_IntrHandlerFifo(void *InstancePtr);	/* interrupt handler */

void XEmac_SetErrorHandler(XEmac * InstancePtr, void *CallBackRef,
			   XEmac_ErrorHandler FuncPtr);

XStatus XEmac_SetOptions(XEmac * InstancePtr, u32 OptionFlag);
u32 XEmac_GetOptions(XEmac * InstancePtr);
XStatus XEmac_SetMacAddress(XEmac * InstancePtr, u8 * AddressPtr);
void XEmac_GetMacAddress(XEmac * InstancePtr, u8 * BufferPtr);
XStatus XEmac_SetInterframeGap(XEmac * InstancePtr, u8 Part1, u8 Part2);
void XEmac_GetInterframeGap(XEmac * InstancePtr, u8 * Part1Ptr, u8 * Part2Ptr);

XStatus XEmac_MulticastAdd(XEmac * InstancePtr, u8 * AddressPtr);
XStatus XEmac_MulticastClear(XEmac * InstancePtr);

XStatus XEmac_PhyRead(XEmac * InstancePtr, u32 PhyAddress,
		      u32 RegisterNum, u16 * PhyDataPtr);
XStatus XEmac_PhyWrite(XEmac * InstancePtr, u32 PhyAddress,
		       u32 RegisterNum, u16 PhyData);

void XEmac_GetStats(XEmac * InstancePtr, XEmac_Stats * StatsPtr);
void XEmac_ClearStats(XEmac * InstancePtr);

#endif				/* end of protection macro */
