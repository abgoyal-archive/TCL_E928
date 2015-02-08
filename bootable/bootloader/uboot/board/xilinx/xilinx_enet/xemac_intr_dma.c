
/*****************************************************************************/

/***************************** Include Files *********************************/

#include "xbasic_types.h"
#include "xemac_i.h"
#include "xio.h"
#include "xbuf_descriptor.h"
#include "xdma_channel.h"
#include "xipif_v1_23_b.h"	/* Uses v1.23b of the IPIF */

/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Variable Definitions *****************************/

/************************** Function Prototypes ******************************/

static void HandleDmaRecvIntr(XEmac * InstancePtr);
static void HandleDmaSendIntr(XEmac * InstancePtr);
static void HandleEmacDmaIntr(XEmac * InstancePtr);

/*****************************************************************************/
XStatus
XEmac_SgSend(XEmac * InstancePtr, XBufDescriptor * BdPtr, int Delay)
{
	XStatus Result;
	u32 BdControl;

	XASSERT_NONVOID(InstancePtr != NULL);
	XASSERT_NONVOID(BdPtr != NULL);
	XASSERT_NONVOID(InstancePtr->IsReady == XCOMPONENT_IS_READY);

	/*
	 * Be sure the device is configured for scatter-gather DMA, then be sure
	 * it is started.
	 */
	if (!XEmac_mIsSgDma(InstancePtr)) {
		return XST_NOT_SGDMA;
	}

	/*
	 * Set some descriptor control word defaults (source address increment
	 * and local destination address) and the destination address
	 * (the FIFO).  These are the same for every transmit descriptor.
	 */
	BdControl = XBufDescriptor_GetControl(BdPtr);
	XBufDescriptor_SetControl(BdPtr, BdControl | XEM_DFT_SEND_BD_MASK);

	XBufDescriptor_SetDestAddress(BdPtr,
				      InstancePtr->BaseAddress +
				      XEM_PFIFO_TXDATA_OFFSET);

	/*
	 * Put the descriptor in the send list. The DMA component accesses data
	 * here that can also be modified in interrupt context, so a critical
	 * section is required.
	 */
	XIIF_V123B_GINTR_DISABLE(InstancePtr->BaseAddress);

	Result = XDmaChannel_PutDescriptor(&InstancePtr->SendChannel, BdPtr);
	if (Result != XST_SUCCESS) {
		XIIF_V123B_GINTR_ENABLE(InstancePtr->BaseAddress);
		return Result;
	}

	/*
	 * If this is the last buffer in the frame, commit the inserts and start
	 * the DMA engine if necessary
	 */
	if (XBufDescriptor_IsLastControl(BdPtr)) {
		Result = XDmaChannel_CommitPuts(&InstancePtr->SendChannel);
		if (Result != XST_SUCCESS) {
			XIIF_V123B_GINTR_ENABLE(InstancePtr->BaseAddress);
			return Result;
		}

		if (Delay == XEM_SGDMA_NODELAY) {
			/*
			 * Start the DMA channel. Ignore the return status since we know the
			 * list exists and has at least one entry and we don't care if the
			 * channel is already started.  The DMA component accesses data here
			 * that can be modified at interrupt or task levels, so a critical
			 * section is required.
			 */
			(void) XDmaChannel_SgStart(&InstancePtr->SendChannel);
		}
	}

	XIIF_V123B_GINTR_ENABLE(InstancePtr->BaseAddress);

	return XST_SUCCESS;
}

/*****************************************************************************/
XStatus
XEmac_SgRecv(XEmac * InstancePtr, XBufDescriptor * BdPtr)
{
	XStatus Result;
	u32 BdControl;

	XASSERT_NONVOID(InstancePtr != NULL);
	XASSERT_NONVOID(BdPtr != NULL);
	XASSERT_NONVOID(InstancePtr->IsReady == XCOMPONENT_IS_READY);

	/*
	 * Be sure the device is configured for scatter-gather DMA
	 */
	if (!XEmac_mIsSgDma(InstancePtr)) {
		return XST_NOT_SGDMA;
	}

	/*
	 * Set some descriptor control word defaults (destination address increment
	 * and local source address) and the source address (the FIFO). These are
	 * the same for every receive descriptor.
	 */
	BdControl = XBufDescriptor_GetControl(BdPtr);
	XBufDescriptor_SetControl(BdPtr, BdControl | XEM_DFT_RECV_BD_MASK);
	XBufDescriptor_SetSrcAddress(BdPtr,
				     InstancePtr->BaseAddress +
				     XEM_PFIFO_RXDATA_OFFSET);

	/*
	 * Put the descriptor into the channel's descriptor list and commit.
	 * Although this function is likely called within interrupt context, there
	 * is the possibility that the upper layer software queues it to a task.
	 * In this case, a critical section is needed here to protect shared data
	 * in the DMA component.
	 */
	XIIF_V123B_GINTR_DISABLE(InstancePtr->BaseAddress);

	Result = XDmaChannel_PutDescriptor(&InstancePtr->RecvChannel, BdPtr);
	if (Result != XST_SUCCESS) {
		XIIF_V123B_GINTR_ENABLE(InstancePtr->BaseAddress);
		return Result;
	}

	Result = XDmaChannel_CommitPuts(&InstancePtr->RecvChannel);
	if (Result != XST_SUCCESS) {
		XIIF_V123B_GINTR_ENABLE(InstancePtr->BaseAddress);
		return Result;
	}

	/*
	 * Start the DMA channel. Ignore the return status since we know the list
	 * exists and has at least one entry and we don't care if the channel is
	 * already started. The DMA component accesses data here that can be
	 * modified at interrupt or task levels, so a critical section is required.
	 */
	(void) XDmaChannel_SgStart(&InstancePtr->RecvChannel);

	XIIF_V123B_GINTR_ENABLE(InstancePtr->BaseAddress);

	return XST_SUCCESS;
}

/*****************************************************************************/
void
XEmac_IntrHandlerDma(void *InstancePtr)
{
	u32 IntrStatus;
	XEmac *EmacPtr = (XEmac *) InstancePtr;

	EmacPtr->Stats.TotalIntrs++;

	/*
	 * Get the interrupt status from the IPIF. There is no clearing of
	 * interrupts in the IPIF. Interrupts must be cleared at the source.
	 */
	IntrStatus = XIIF_V123B_READ_DIPR(EmacPtr->BaseAddress);

	/*
	 * See which type of interrupt is being requested, and service it
	 */
	if (IntrStatus & XEM_IPIF_RECV_DMA_MASK) {	/* Receive DMA interrupt */
		EmacPtr->Stats.RecvInterrupts++;
		HandleDmaRecvIntr(EmacPtr);
	}

	if (IntrStatus & XEM_IPIF_SEND_DMA_MASK) {	/* Send DMA interrupt */
		EmacPtr->Stats.XmitInterrupts++;
		HandleDmaSendIntr(EmacPtr);
	}

	if (IntrStatus & XEM_IPIF_EMAC_MASK) {	/* MAC interrupt */
		EmacPtr->Stats.EmacInterrupts++;
		HandleEmacDmaIntr(EmacPtr);
	}

	if (IntrStatus & XEM_IPIF_RECV_FIFO_MASK) {	/* Receive FIFO interrupt */
		EmacPtr->Stats.RecvInterrupts++;
		XEmac_CheckFifoRecvError(EmacPtr);
	}

	if (IntrStatus & XEM_IPIF_SEND_FIFO_MASK) {	/* Send FIFO interrupt */
		EmacPtr->Stats.XmitInterrupts++;
		XEmac_CheckFifoSendError(EmacPtr);
	}

	if (IntrStatus & XIIF_V123B_ERROR_MASK) {
		/*
		 * An error occurred internal to the IPIF. This is more of a debug and
		 * integration issue rather than a production error. Don't do anything
		 * other than clear it, which provides a spot for software to trap
		 * on the interrupt and begin debugging.
		 */
		XIIF_V123B_WRITE_DISR(EmacPtr->BaseAddress,
				      XIIF_V123B_ERROR_MASK);
	}
}

/*****************************************************************************/
XStatus
XEmac_SetPktThreshold(XEmac * InstancePtr, u32 Direction, u8 Threshold)
{
	XASSERT_NONVOID(InstancePtr != NULL);
	XASSERT_NONVOID(Direction == XEM_SEND || Direction == XEM_RECV);
	XASSERT_NONVOID(InstancePtr->IsReady == XCOMPONENT_IS_READY);

	/*
	 * Be sure device is configured for scatter-gather DMA and has been stopped
	 */
	if (!XEmac_mIsSgDma(InstancePtr)) {
		return XST_NOT_SGDMA;
	}

	if (InstancePtr->IsStarted == XCOMPONENT_IS_STARTED) {
		return XST_DEVICE_IS_STARTED;
	}

	/*
	 * Based on the direction, set the packet threshold in the
	 * corresponding DMA channel component.  Default to the receive
	 * channel threshold register (if an invalid Direction is passed).
	 */
	switch (Direction) {
	case XEM_SEND:
		return XDmaChannel_SetPktThreshold(&InstancePtr->SendChannel,
						   Threshold);

	case XEM_RECV:
		return XDmaChannel_SetPktThreshold(&InstancePtr->RecvChannel,
						   Threshold);

	default:
		return XST_INVALID_PARAM;
	}
}

/*****************************************************************************/
XStatus
XEmac_GetPktThreshold(XEmac * InstancePtr, u32 Direction, u8 * ThreshPtr)
{
	XASSERT_NONVOID(InstancePtr != NULL);
	XASSERT_NONVOID(Direction == XEM_SEND || Direction == XEM_RECV);
	XASSERT_NONVOID(ThreshPtr != NULL);
	XASSERT_NONVOID(InstancePtr->IsReady == XCOMPONENT_IS_READY);

	if (!XEmac_mIsSgDma(InstancePtr)) {
		return XST_NOT_SGDMA;
	}

	/*
	 * Based on the direction, return the packet threshold set in the
	 * corresponding DMA channel component.  Default to the value in
	 * the receive channel threshold register (if an invalid Direction
	 * is passed).
	 */
	switch (Direction) {
	case XEM_SEND:
		*ThreshPtr =
		    XDmaChannel_GetPktThreshold(&InstancePtr->SendChannel);
		break;

	case XEM_RECV:
		*ThreshPtr =
		    XDmaChannel_GetPktThreshold(&InstancePtr->RecvChannel);
		break;

	default:
		return XST_INVALID_PARAM;
	}

	return XST_SUCCESS;
}

/*****************************************************************************/
XStatus
XEmac_SetPktWaitBound(XEmac * InstancePtr, u32 Direction, u32 TimerValue)
{
	XASSERT_NONVOID(InstancePtr != NULL);
	XASSERT_NONVOID(Direction == XEM_SEND || Direction == XEM_RECV);
	XASSERT_NONVOID(TimerValue <= XEM_SGDMA_MAX_WAITBOUND);
	XASSERT_NONVOID(InstancePtr->IsReady == XCOMPONENT_IS_READY);

	/*
	 * Be sure device is configured for scatter-gather DMA and has been stopped
	 */
	if (!XEmac_mIsSgDma(InstancePtr)) {
		return XST_NOT_SGDMA;
	}

	if (InstancePtr->IsStarted == XCOMPONENT_IS_STARTED) {
		return XST_DEVICE_IS_STARTED;
	}

	/*
	 * Based on the direction, set the packet wait bound in the
	 * corresponding DMA channel component.  Default to the receive
	 * channel wait bound register (if an invalid Direction is passed).
	 */
	switch (Direction) {
	case XEM_SEND:
		XDmaChannel_SetPktWaitBound(&InstancePtr->SendChannel,
					    TimerValue);
		break;

	case XEM_RECV:
		XDmaChannel_SetPktWaitBound(&InstancePtr->RecvChannel,
					    TimerValue);
		break;

	default:
		return XST_INVALID_PARAM;
	}

	return XST_SUCCESS;
}

/*****************************************************************************/
XStatus
XEmac_GetPktWaitBound(XEmac * InstancePtr, u32 Direction, u32 * WaitPtr)
{
	XASSERT_NONVOID(InstancePtr != NULL);
	XASSERT_NONVOID(Direction == XEM_SEND || Direction == XEM_RECV);
	XASSERT_NONVOID(WaitPtr != NULL);
	XASSERT_NONVOID(InstancePtr->IsReady == XCOMPONENT_IS_READY);

	if (!XEmac_mIsSgDma(InstancePtr)) {
		return XST_NOT_SGDMA;
	}

	/*
	 * Based on the direction, return the packet wait bound set in the
	 * corresponding DMA channel component.  Default to the value in
	 * the receive channel wait bound register (if an invalid Direction
	 * is passed).
	 */
	switch (Direction) {
	case XEM_SEND:
		*WaitPtr =
		    XDmaChannel_GetPktWaitBound(&InstancePtr->SendChannel);
		break;

	case XEM_RECV:
		*WaitPtr =
		    XDmaChannel_GetPktWaitBound(&InstancePtr->RecvChannel);
		break;

	default:
		return XST_INVALID_PARAM;
	}

	return XST_SUCCESS;
}

/*****************************************************************************/
XStatus
XEmac_SetSgRecvSpace(XEmac * InstancePtr, u32 * MemoryPtr, u32 ByteCount)
{
	XASSERT_NONVOID(InstancePtr != NULL);
	XASSERT_NONVOID(MemoryPtr != NULL);
	XASSERT_NONVOID(ByteCount != 0);
	XASSERT_NONVOID(InstancePtr->IsReady == XCOMPONENT_IS_READY);

	if (!XEmac_mIsSgDma(InstancePtr)) {
		return XST_NOT_SGDMA;
	}

	return XDmaChannel_CreateSgList(&InstancePtr->RecvChannel, MemoryPtr,
					ByteCount);
}

/*****************************************************************************/
XStatus
XEmac_SetSgSendSpace(XEmac * InstancePtr, u32 * MemoryPtr, u32 ByteCount)
{
	XASSERT_NONVOID(InstancePtr != NULL);
	XASSERT_NONVOID(MemoryPtr != NULL);
	XASSERT_NONVOID(ByteCount != 0);
	XASSERT_NONVOID(InstancePtr->IsReady == XCOMPONENT_IS_READY);

	if (!XEmac_mIsSgDma(InstancePtr)) {
		return XST_NOT_SGDMA;
	}

	return XDmaChannel_CreateSgList(&InstancePtr->SendChannel, MemoryPtr,
					ByteCount);
}

/*****************************************************************************/
void
XEmac_SetSgRecvHandler(XEmac * InstancePtr, void *CallBackRef,
		       XEmac_SgHandler FuncPtr)
{
	/*
	 * Asserted IsDmaSg here instead of run-time check because there is really
	 * no ill-effects of setting these when not configured for scatter-gather.
	 */
	XASSERT_VOID(InstancePtr != NULL);
	XASSERT_VOID(FuncPtr != NULL);
	XASSERT_VOID(XEmac_mIsSgDma(InstancePtr));
	XASSERT_VOID(InstancePtr->IsReady == XCOMPONENT_IS_READY);

	InstancePtr->SgRecvHandler = FuncPtr;
	InstancePtr->SgRecvRef = CallBackRef;
}

/*****************************************************************************/
void
XEmac_SetSgSendHandler(XEmac * InstancePtr, void *CallBackRef,
		       XEmac_SgHandler FuncPtr)
{
	/*
	 * Asserted IsDmaSg here instead of run-time check because there is really
	 * no ill-effects of setting these when not configured for scatter-gather.
	 */
	XASSERT_VOID(InstancePtr != NULL);
	XASSERT_VOID(FuncPtr != NULL);
	XASSERT_VOID(XEmac_mIsSgDma(InstancePtr));
	XASSERT_VOID(InstancePtr->IsReady == XCOMPONENT_IS_READY);

	InstancePtr->SgSendHandler = FuncPtr;
	InstancePtr->SgSendRef = CallBackRef;
}

/*****************************************************************************/
static void
HandleDmaRecvIntr(XEmac * InstancePtr)
{
	u32 IntrStatus;

	/*
	 * Read the interrupt status
	 */
	IntrStatus = XDmaChannel_GetIntrStatus(&InstancePtr->RecvChannel);

	/*
	 * For packet threshold or wait bound interrupts, process desciptors. Also
	 * process descriptors on a SG end acknowledgement, which means the end of
	 * the descriptor list has been reached by the hardware. For receive, this
	 * is potentially trouble since it means the descriptor list is full,
	 * unless software can process enough packets quickly enough so the
	 * hardware has room to put new packets.
	 */
	if (IntrStatus & (XDC_IXR_PKT_THRESHOLD_MASK |
			  XDC_IXR_PKT_WAIT_BOUND_MASK | XDC_IXR_SG_END_MASK)) {
		XStatus Result = XST_SUCCESS;
		u32 NumFrames;
		u32 NumProcessed;
		u32 NumBuffers;
		u32 NumBytes;
		u32 IsLast;
		XBufDescriptor *FirstBdPtr;
		XBufDescriptor *BdPtr;

		/*
		 * Get the number of unserviced packets
		 */
		NumFrames = XDmaChannel_GetPktCount(&InstancePtr->RecvChannel);

		for (NumProcessed = 0; NumProcessed < NumFrames; NumProcessed++) {
			IsLast = FALSE;
			FirstBdPtr = NULL;
			NumBuffers = 0;
			NumBytes = 0;

			/*
			 * For each packet, get the descriptor from the list. On the
			 * last one in the frame, make the callback to the upper layer.
			 */
			while (!IsLast) {
				Result =
				    XDmaChannel_GetDescriptor(&InstancePtr->
							      RecvChannel,
							      &BdPtr);
				if (Result != XST_SUCCESS) {
					/*
					 * An error getting a buffer descriptor from the list.
					 * This should not happen, but if it does, report it to
					 * the error callback and break out of the loops to service
					 * other interrupts.
					 */
					InstancePtr->ErrorHandler(InstancePtr->
								  ErrorRef,
								  Result);
					break;
				}

				/*
				 * Keep a pointer to the first descriptor in the list, as it
				 * will be passed to the upper layers in a bit. By the fact
				 * that we received this packet means no errors occurred, so
				 * no need to check the device status word for errors.
				 */
				if (FirstBdPtr == NULL) {
					FirstBdPtr = BdPtr;
				}

				NumBytes += XBufDescriptor_GetLength(BdPtr);

				/*
				 * Check to see if this is the last descriptor in the frame,
				 * and if so, set the IsLast flag to get out of the loop.
				 */
				if (XBufDescriptor_IsLastStatus(BdPtr)) {
					IsLast = TRUE;
				}

				/*
				 * Bump the number of buffers in this packet
				 */
				NumBuffers++;

			}	/* end while loop */

			/*
			 * Check for error that occurred inside the while loop, and break
			 * out of the for loop if there was one so other interrupts can
			 * be serviced.
			 */
			if (Result != XST_SUCCESS) {
				break;
			}

			InstancePtr->Stats.RecvFrames++;
			InstancePtr->Stats.RecvBytes += NumBytes;

			/*
			 * Make the callback to the upper layers, passing it the first
			 * descriptor in the packet and the number of descriptors in the
			 * packet.
			 */
			InstancePtr->SgRecvHandler(InstancePtr->SgRecvRef,
						   FirstBdPtr, NumBuffers);

			/*
			 * Decrement the packet count register to reflect the fact we
			 * just processed a packet
			 */
			XDmaChannel_DecrementPktCount(&InstancePtr->
						      RecvChannel);

		}		/* end for loop */

		/*
		 * If the interrupt was an end-ack, check the descriptor list again to
		 * see if it is empty. If not, go ahead and restart the scatter-gather
		 * channel. This is to fix a possible race condition where, on receive,
		 * the driver attempted to start a scatter-gather channel that was
		 * already started, which resulted in no action from the XDmaChannel
		 * component. But, just after the XDmaChannel component saw that the
		 * hardware was already started, the hardware stopped because it
		 * reached the end of the list.  In that case, this interrupt is
		 * generated and we can restart the hardware here.
		 */
		if (IntrStatus & XDC_IXR_SG_END_MASK) {
			/*
			 * Ignore the return status since we know the list exists and we
			 * don't care if the list is empty or the channel is already started.
			 */
			(void) XDmaChannel_SgStart(&InstancePtr->RecvChannel);
		}
	}

	/*
	 * All interrupts are handled (except the error below) so acknowledge
	 * (clear) the interrupts by writing the value read above back to the status
	 * register. The packet count interrupt must be acknowledged after the
	 * decrement, otherwise it will come right back. We clear the interrupts
	 * before we handle the error interrupt because the ErrorHandler should
	 * result in a reset, which clears the interrupt status register. So we
	 * don't want to toggle the interrupt back on by writing the interrupt
	 * status register with an old value after a reset.
	 */
	XDmaChannel_SetIntrStatus(&InstancePtr->RecvChannel, IntrStatus);

	/*
	 * Check for DMA errors and call the error callback function if an error
	 * occurred (DMA bus or timeout error), which should result in a reset of
	 * the device by the upper layer software.
	 */
	if (IntrStatus & XDC_IXR_DMA_ERROR_MASK) {
		InstancePtr->Stats.DmaErrors++;
		InstancePtr->ErrorHandler(InstancePtr->ErrorRef, XST_DMA_ERROR);
	}
}

/*****************************************************************************/
static void
HandleDmaSendIntr(XEmac * InstancePtr)
{
	u32 IntrStatus;

	/*
	 * Read the interrupt status
	 */
	IntrStatus = XDmaChannel_GetIntrStatus(&InstancePtr->SendChannel);

	/*
	 * For packet threshold or wait bound interrupt, process descriptors. Also
	 * process descriptors on a SG end acknowledgement, which means the end of
	 * the descriptor list has been reached by the hardware. For transmit,
	 * this is a normal condition during times of light traffic.  In fact, the
	 * wait bound interrupt may be masked for transmit since the end-ack would
	 * always occur before the wait bound expires.
	 */
	if (IntrStatus & (XDC_IXR_PKT_THRESHOLD_MASK |
			  XDC_IXR_PKT_WAIT_BOUND_MASK | XDC_IXR_SG_END_MASK)) {
		XStatus Result = XST_SUCCESS;
		u32 NumFrames;
		u32 NumProcessed;
		u32 NumBuffers;
		u32 NumBytes;
		u32 IsLast;
		XBufDescriptor *FirstBdPtr;
		XBufDescriptor *BdPtr;

		/*
		 * Get the number of unserviced packets
		 */
		NumFrames = XDmaChannel_GetPktCount(&InstancePtr->SendChannel);

		for (NumProcessed = 0; NumProcessed < NumFrames; NumProcessed++) {
			IsLast = FALSE;
			FirstBdPtr = NULL;
			NumBuffers = 0;
			NumBytes = 0;

			/*
			 * For each frame, traverse the descriptor list and look for
			 * errors. On the last one in the frame, make the callback.
			 */
			while (!IsLast) {
				Result =
				    XDmaChannel_GetDescriptor(&InstancePtr->
							      SendChannel,
							      &BdPtr);
				if (Result != XST_SUCCESS) {
					/*
					 * An error getting a buffer descriptor from the list.
					 * This should not happen, but if it does, report it to
					 * the error callback and break out of the loops to service
					 * other interrupts
					 */
					InstancePtr->ErrorHandler(InstancePtr->
								  ErrorRef,
								  Result);
					break;
				}

				/*
				 * Keep a pointer to the first descriptor in the list and
				 * check the device status for errors. The device status is
				 * only available in the first descriptor of a packet.
				 */
				if (FirstBdPtr == NULL) {
					u32 XmitStatus;

					FirstBdPtr = BdPtr;

					XmitStatus =
					    XBufDescriptor_GetDeviceStatus
					    (BdPtr);
					if (XmitStatus &
					    XEM_TSR_EXCESS_DEFERRAL_MASK) {
						InstancePtr->Stats.
						    XmitExcessDeferral++;
					}

					if (XmitStatus &
					    XEM_TSR_LATE_COLLISION_MASK) {
						InstancePtr->Stats.
						    XmitLateCollisionErrors++;
					}
				}

				NumBytes += XBufDescriptor_GetLength(BdPtr);

				/*
				 * Check to see if this is the last descriptor in the frame,
				 * and if so, set the IsLast flag to get out of the loop. The
				 * transmit channel must check the last bit in the control
				 * word, not the status word (the DMA engine does not update
				 * the last bit in the status word for the transmit direction).
				 */
				if (XBufDescriptor_IsLastControl(BdPtr)) {
					IsLast = TRUE;
				}

				/*
				 * Bump the number of buffers in this packet
				 */
				NumBuffers++;

			}	/* end while loop */

			/*
			 * Check for error that occurred inside the while loop, and break
			 * out of the for loop if there was one so other interrupts can
			 * be serviced.
			 */
			if (Result != XST_SUCCESS) {
				break;
			}

			InstancePtr->Stats.XmitFrames++;
			InstancePtr->Stats.XmitBytes += NumBytes;

			/*
			 * Make the callback to the upper layers, passing it the first
			 * descriptor in the packet and the number of descriptors in the
			 * packet.
			 */
			InstancePtr->SgSendHandler(InstancePtr->SgSendRef,
						   FirstBdPtr, NumBuffers);

			/*
			 * Decrement the packet count register to reflect the fact we
			 * just processed a packet
			 */
			XDmaChannel_DecrementPktCount(&InstancePtr->
						      SendChannel);

		}		/* end for loop */

		/*
		 * If the interrupt was an end-ack, check the descriptor list again to
		 * see if it is empty. If not, go ahead and restart the scatter-gather
		 * channel. This is to fix a possible race condition where, on transmit,
		 * the driver attempted to start a scatter-gather channel that was
		 * already started, which resulted in no action from the XDmaChannel
		 * component. But, just after the XDmaChannel component saw that the
		 * hardware was already started, the hardware stopped because it
		 * reached the end of the list.  In that case, this interrupt is
		 * generated and we can restart the hardware here.
		 */
		if (IntrStatus & XDC_IXR_SG_END_MASK) {
			/*
			 * Ignore the return status since we know the list exists and we
			 * don't care if the list is empty or the channel is already started.
			 */
			(void) XDmaChannel_SgStart(&InstancePtr->SendChannel);
		}
	}

	/*
	 * All interrupts are handled (except the error below) so acknowledge
	 * (clear) the interrupts by writing the value read above back to the status
	 * register. The packet count interrupt must be acknowledged after the
	 * decrement, otherwise it will come right back. We clear the interrupts
	 * before we handle the error interrupt because the ErrorHandler should
	 * result in a reset, which clears the interrupt status register. So we
	 * don't want to toggle the interrupt back on by writing the interrupt
	 * status register with an old value after a reset.
	 */
	XDmaChannel_SetIntrStatus(&InstancePtr->SendChannel, IntrStatus);

	/*
	 * Check for DMA errors and call the error callback function if an error
	 * occurred (DMA bus or timeout error), which should result in a reset of
	 * the device by the upper layer software.
	 */
	if (IntrStatus & XDC_IXR_DMA_ERROR_MASK) {
		InstancePtr->Stats.DmaErrors++;
		InstancePtr->ErrorHandler(InstancePtr->ErrorRef, XST_DMA_ERROR);
	}
}

/*****************************************************************************/
static void
HandleEmacDmaIntr(XEmac * InstancePtr)
{
	u32 IntrStatus;

	/*
	 * When configured with DMA, the EMAC generates interrupts only when errors
	 * occur. We clear the interrupts immediately so that any latched status
	 * interrupt bits will reflect the true status of the device, and so any
	 * pulsed interrupts (non-status) generated during the Isr will not be lost.
	 */
	IntrStatus = XIIF_V123B_READ_IISR(InstancePtr->BaseAddress);
	XIIF_V123B_WRITE_IISR(InstancePtr->BaseAddress, IntrStatus);

	/*
	 * Check the MAC for errors
	 */
	XEmac_CheckEmacError(InstancePtr, IntrStatus);
}
