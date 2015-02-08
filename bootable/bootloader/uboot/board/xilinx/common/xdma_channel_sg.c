
/* $Id: xdma_channel_sg.c,v 1.6 2003/02/03 19:50:33 moleres Exp $ */

/***************************** Include Files *********************************/

#include "xdma_channel.h"
#include "xbasic_types.h"
#include "xio.h"
#include "xbuf_descriptor.h"
#include "xstatus.h"

/************************** Constant Definitions *****************************/

#define XDC_SWCR_SG_ENABLE_MASK 0x80000000UL	/* scatter gather enable */

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/

#define CopyBufferDescriptor(InstancePtr, DestinationPtr)	   \
{								   \
    *((u32 *)DestinationPtr + XBD_CONTROL_OFFSET) =	       \
	*((u32 *)InstancePtr + XBD_CONTROL_OFFSET);	       \
    *((u32 *)DestinationPtr + XBD_SOURCE_OFFSET) =	       \
	*((u32 *)InstancePtr + XBD_SOURCE_OFFSET);	       \
    *((u32 *)DestinationPtr + XBD_DESTINATION_OFFSET) =	       \
	*((u32 *)InstancePtr + XBD_DESTINATION_OFFSET);	       \
    *((u32 *)DestinationPtr + XBD_LENGTH_OFFSET) =	       \
	*((u32 *)InstancePtr + XBD_LENGTH_OFFSET);	       \
    *((u32 *)DestinationPtr + XBD_STATUS_OFFSET) =	       \
	*((u32 *)InstancePtr + XBD_STATUS_OFFSET);	       \
    *((u32 *)DestinationPtr + XBD_DEVICE_STATUS_OFFSET) =      \
	*((u32 *)InstancePtr + XBD_DEVICE_STATUS_OFFSET);      \
    *((u32 *)DestinationPtr + XBD_ID_OFFSET) =		       \
	*((u32 *)InstancePtr + XBD_ID_OFFSET);		       \
    *((u32 *)DestinationPtr + XBD_FLAGS_OFFSET) =	       \
	*((u32 *)InstancePtr + XBD_FLAGS_OFFSET);	       \
    *((u32 *)DestinationPtr + XBD_RQSTED_LENGTH_OFFSET) =      \
	*((u32 *)InstancePtr + XBD_RQSTED_LENGTH_OFFSET);      \
}

/************************** Variable Definitions *****************************/

/************************** Function Prototypes ******************************/

XStatus
XDmaChannel_SgStart(XDmaChannel * InstancePtr)
{
	u32 Register;
	XBufDescriptor *LastDescriptorPtr;

	/* assert to verify input arguments */

	XASSERT_NONVOID(InstancePtr != NULL);
	XASSERT_NONVOID(InstancePtr->IsReady == XCOMPONENT_IS_READY);

	/* if a scatter gather list has not been created yet, return a status */

	if (InstancePtr->TotalDescriptorCount == 0) {
		return XST_DMA_SG_NO_LIST;
	}

	/* if the scatter gather list exists but is empty then return a status */

	if (XDmaChannel_IsSgListEmpty(InstancePtr)) {
		return XST_DMA_SG_LIST_EMPTY;
	}

	/* if scatter gather is busy for the DMA channel, return a status because
	 * restarting it could lose data
	 */

	Register = XIo_In32(InstancePtr->RegBaseAddress + XDC_DMAS_REG_OFFSET);
	if (Register & XDC_DMASR_SG_BUSY_MASK) {
		return XST_DMA_SG_IS_STARTED;
	}

	/* get the address of the last buffer descriptor which the DMA hardware
	 * finished processing
	 */
	LastDescriptorPtr =
	    (XBufDescriptor *) XIo_In32(InstancePtr->RegBaseAddress +
					XDC_BDA_REG_OFFSET);

	/* setup the first buffer descriptor that will be sent when the scatter
	 * gather channel is enabled, this is only necessary one time since
	 * the BDA register of the channel maintains the last buffer descriptor
	 * processed
	 */
	if (LastDescriptorPtr == NULL) {
		XIo_Out32(InstancePtr->RegBaseAddress + XDC_BDA_REG_OFFSET,
			  (u32) InstancePtr->GetPtr);
	} else {
		XBufDescriptor *NextDescriptorPtr;

		/* get the next descriptor to be started, if the status indicates it
		 * hasn't already been used by the h/w, then it's OK to start it,
		 * s/w sets the status of each descriptor to busy and then h/w clears
		 * the busy when it is complete
		 */
		NextDescriptorPtr =
		    XBufDescriptor_GetNextPtr(LastDescriptorPtr);

		if ((XBufDescriptor_GetStatus(NextDescriptorPtr) &
		     XDC_DMASR_BUSY_MASK) == 0) {
			return XST_DMA_SG_NO_DATA;
		}
		/* don't start the DMA SG channel if the descriptor to be processed
		 * by h/w is to be committed by the s/w, this function can be called
		 * such that it interrupts a thread that was putting into the list
		 */
		if (NextDescriptorPtr == InstancePtr->CommitPtr) {
			return XST_DMA_SG_BD_NOT_COMMITTED;
		}
	}

	/* start the scatter gather operation by clearing the stop bit in the
	 * control register and setting the enable bit in the s/w control register,
	 * both of these are necessary to cause it to start, right now the order of
	 * these statements is important, the software control register should be
	 * set 1st.  The other order can cause the CPU to have a loss of sync
	 * because it cannot read/write the register while the DMA operation is
	 * running
	 */

	Register = XIo_In32(InstancePtr->RegBaseAddress + XDC_SWCR_REG_OFFSET);

	XIo_Out32(InstancePtr->RegBaseAddress + XDC_SWCR_REG_OFFSET,
		  Register | XDC_SWCR_SG_ENABLE_MASK);

	Register = XIo_In32(InstancePtr->RegBaseAddress + XDC_DMAC_REG_OFFSET);

	XIo_Out32(InstancePtr->RegBaseAddress + XDC_DMAC_REG_OFFSET,
		  Register & ~XDC_DMACR_SG_DISABLE_MASK);

	/* indicate the DMA channel scatter gather operation was started
	 * successfully
	 */
	return XST_SUCCESS;
}

XStatus
XDmaChannel_SgStop(XDmaChannel * InstancePtr,
		   XBufDescriptor ** BufDescriptorPtr)
{
	u32 Register;

	/* assert to verify input arguments */

	XASSERT_NONVOID(InstancePtr != NULL);
	XASSERT_NONVOID(BufDescriptorPtr != NULL);
	XASSERT_NONVOID(InstancePtr->IsReady == XCOMPONENT_IS_READY);

	/* get the contents of the software control register, if scatter gather is not
	 * enabled (started), then return a status because the disable acknowledge
	 * would not be generated
	 */
	Register = XIo_In32(InstancePtr->RegBaseAddress + XDC_SWCR_REG_OFFSET);

	if ((Register & XDC_SWCR_SG_ENABLE_MASK) == 0) {
		return XST_DMA_SG_IS_STOPPED;
	}

	/* Ensure the interrupt status for the scatter gather is cleared such
	 * that this function will wait til the disable has occurred, writing
	 * a 1 to only that bit in the register will clear only it
	 */
	XIo_Out32(InstancePtr->RegBaseAddress + XDC_IS_REG_OFFSET,
		  XDC_IXR_SG_DISABLE_ACK_MASK);

	/* disable scatter gather by writing to the software control register
	 * without modifying any other bits of the register
	 */
	XIo_Out32(InstancePtr->RegBaseAddress + XDC_SWCR_REG_OFFSET,
		  Register & ~XDC_SWCR_SG_ENABLE_MASK);

	/* scatter gather does not disable immediately, but after the current
	 * buffer descriptor is complete, so wait for the DMA channel to indicate
	 * the disable is complete
	 */
	do {
		Register =
		    XIo_In32(InstancePtr->RegBaseAddress + XDC_IS_REG_OFFSET);
	} while ((Register & XDC_IXR_SG_DISABLE_ACK_MASK) == 0);

	/* Ensure the interrupt status for the scatter gather disable is cleared,
	 * writing a 1 to only that bit in the register will clear only it
	 */
	XIo_Out32(InstancePtr->RegBaseAddress + XDC_IS_REG_OFFSET,
		  XDC_IXR_SG_DISABLE_ACK_MASK);

	/* set the specified buffer descriptor pointer to point to the buffer
	 * descriptor that the scatter gather DMA channel was processing
	 */
	*BufDescriptorPtr =
	    (XBufDescriptor *) XIo_In32(InstancePtr->RegBaseAddress +
					XDC_BDA_REG_OFFSET);

	return XST_SUCCESS;
}

XStatus
XDmaChannel_CreateSgList(XDmaChannel * InstancePtr,
			 u32 * MemoryPtr, u32 ByteCount)
{
	XBufDescriptor *BufferDescriptorPtr = (XBufDescriptor *) MemoryPtr;
	XBufDescriptor *PreviousDescriptorPtr = NULL;
	XBufDescriptor *StartOfListPtr = BufferDescriptorPtr;
	u32 UsedByteCount;

	/* assert to verify valid input arguments, alignment for those
	 * arguments that have alignment restrictions, and at least enough
	 * memory for one buffer descriptor
	 */
	XASSERT_NONVOID(InstancePtr != NULL);
	XASSERT_NONVOID(MemoryPtr != NULL);
	XASSERT_NONVOID(((u32) MemoryPtr & 3) == 0);
	XASSERT_NONVOID(ByteCount != 0);
	XASSERT_NONVOID(ByteCount >= sizeof (XBufDescriptor));
	XASSERT_NONVOID(InstancePtr->IsReady == XCOMPONENT_IS_READY);

	/* if the scatter gather list has already been created, then return
	 * with a status
	 */
	if (InstancePtr->TotalDescriptorCount != 0) {
		return XST_DMA_SG_LIST_EXISTS;
	}

	/* loop thru the specified memory block and create as many buffer
	 * descriptors as possible putting each into the list which is
	 * implemented as a ring buffer, make sure not to use any memory which
	 * is not large enough for a complete buffer descriptor
	 */
	UsedByteCount = 0;
	while ((UsedByteCount + sizeof (XBufDescriptor)) <= ByteCount) {
		/* setup a pointer to the next buffer descriptor in the memory and
		 * update # of used bytes to know when all of memory is used
		 */
		BufferDescriptorPtr = (XBufDescriptor *) ((u32) MemoryPtr +
							  UsedByteCount);

		/* initialize the new buffer descriptor such that it doesn't contain
		 * garbage which could be used by the DMA hardware
		 */
		XBufDescriptor_Initialize(BufferDescriptorPtr);

		/* if this is not the first buffer descriptor to be created,
		 * then link it to the last created buffer descriptor
		 */
		if (PreviousDescriptorPtr != NULL) {
			XBufDescriptor_SetNextPtr(PreviousDescriptorPtr,
						  BufferDescriptorPtr);
		}

		/* always keep a pointer to the last created buffer descriptor such
		 * that they can be linked together in the ring buffer
		 */
		PreviousDescriptorPtr = BufferDescriptorPtr;

		/* keep a count of the number of descriptors in the list to allow
		 * error processing to be performed
		 */
		InstancePtr->TotalDescriptorCount++;

		UsedByteCount += sizeof (XBufDescriptor);
	}

	/* connect the last buffer descriptor created and inserted in the list
	 * to the first such that a ring buffer is created
	 */
	XBufDescriptor_SetNextPtr(BufferDescriptorPtr, StartOfListPtr);

	/* initialize the ring buffer to indicate that there are no
	 * buffer descriptors in the list which point to valid data buffers
	 */
	InstancePtr->PutPtr = BufferDescriptorPtr;
	InstancePtr->GetPtr = BufferDescriptorPtr;
	InstancePtr->CommitPtr = NULL;
	InstancePtr->LastPtr = BufferDescriptorPtr;
	InstancePtr->ActiveDescriptorCount = 0;

	/* indicate the scatter gather list was successfully created */

	return XST_SUCCESS;
}

u32
XDmaChannel_IsSgListEmpty(XDmaChannel * InstancePtr)
{
	/* assert to verify valid input arguments */

	XASSERT_NONVOID(InstancePtr != NULL);
	XASSERT_NONVOID(InstancePtr->IsReady == XCOMPONENT_IS_READY);

	/* if the number of descriptors which are being used in the list is zero
	 * then the list is empty
	 */
	return (InstancePtr->ActiveDescriptorCount == 0);
}

XStatus
XDmaChannel_PutDescriptor(XDmaChannel * InstancePtr,
			  XBufDescriptor * BufferDescriptorPtr)
{
	u32 Control;

	/* assert to verify valid input arguments and alignment for those
	 * arguments that have alignment restrictions
	 */
	XASSERT_NONVOID(InstancePtr != NULL);
	XASSERT_NONVOID(BufferDescriptorPtr != NULL);
	XASSERT_NONVOID(((u32) BufferDescriptorPtr & 3) == 0);
	XASSERT_NONVOID(InstancePtr->IsReady == XCOMPONENT_IS_READY);

	/* if a scatter gather list has not been created yet, return a status */

	if (InstancePtr->TotalDescriptorCount == 0) {
		return XST_DMA_SG_NO_LIST;
	}

	/* if the list is full because all descriptors are pointing to valid
	 * buffers, then indicate an error, this code assumes no list or an
	 * empty list is detected above
	 */
	if (InstancePtr->ActiveDescriptorCount ==
	    InstancePtr->TotalDescriptorCount) {
		return XST_DMA_SG_LIST_FULL;
	}

	/* if the buffer descriptor in the list which is to be overwritten is
	 * locked, then don't overwrite it and return a status
	 */
	if (XBufDescriptor_IsLocked(InstancePtr->PutPtr)) {
		return XST_DMA_SG_BD_LOCKED;
	}

	/* set the scatter gather stop bit in the control word of the descriptor
	 * to cause the h/w to stop after it processes this descriptor since it
	 * will be the last in the list
	 */
	Control = XBufDescriptor_GetControl(BufferDescriptorPtr);
	XBufDescriptor_SetControl(BufferDescriptorPtr,
				  Control | XDC_DMACR_SG_DISABLE_MASK);

	/* set both statuses in the descriptor so we tell if they are updated with
	 * the status of the transfer, the hardware should change the busy in the
	 * DMA status to be false when it completes
	 */
	XBufDescriptor_SetStatus(BufferDescriptorPtr, XDC_DMASR_BUSY_MASK);
	XBufDescriptor_SetDeviceStatus(BufferDescriptorPtr, 0);

	/* copy the descriptor into the next position in the list so it's ready to
	 * be used by the h/w, this assumes the descriptor in the list prior to this
	 * one still has the stop bit in the control word set such that the h/w
	 * use this one yet
	 */
	CopyBufferDescriptor(BufferDescriptorPtr, InstancePtr->PutPtr);

	/* only the last in the list and the one to be committed have scatter gather
	 * disabled in the control word, a commit requires only one descriptor
	 * to be changed, when # of descriptors to commit > 2 all others except the
	 * 1st and last have scatter gather enabled
	 */
	if ((InstancePtr->CommitPtr != InstancePtr->LastPtr) &&
	    (InstancePtr->CommitPtr != NULL)) {
		Control = XBufDescriptor_GetControl(InstancePtr->LastPtr);
		XBufDescriptor_SetControl(InstancePtr->LastPtr,
					  Control & ~XDC_DMACR_SG_DISABLE_MASK);
	}

	/* update the list data based upon putting a descriptor into the list,
	 * these operations must be last
	 */
	InstancePtr->ActiveDescriptorCount++;

	/* only update the commit pointer if it is not already active, this allows
	 * it to be deactivated after every commit such that a single descriptor
	 * which is committed does not appear to be waiting to be committed
	 */
	if (InstancePtr->CommitPtr == NULL) {
		InstancePtr->CommitPtr = InstancePtr->LastPtr;
	}

	/* these updates MUST BE LAST after the commit pointer update in order for
	 * the commit pointer to track the correct descriptor to be committed
	 */
	InstancePtr->LastPtr = InstancePtr->PutPtr;
	InstancePtr->PutPtr = XBufDescriptor_GetNextPtr(InstancePtr->PutPtr);

	return XST_SUCCESS;
}

XStatus
XDmaChannel_CommitPuts(XDmaChannel * InstancePtr)
{
	/* assert to verify input arguments */

	XASSERT_NONVOID(InstancePtr != NULL);
	XASSERT_NONVOID(InstancePtr->IsReady == XCOMPONENT_IS_READY);

	/* if the buffer descriptor to be committed is already committed or
	 * the list is empty (none have been put in), then indicate an error
	 */
	if ((InstancePtr->CommitPtr == NULL) ||
	    XDmaChannel_IsSgListEmpty(InstancePtr)) {
		return XST_DMA_SG_NOTHING_TO_COMMIT;
	}

	/* last descriptor in the list must have scatter gather disabled so the end
	 * of the list is hit by h/w, if descriptor to commit is not last in list,
	 * commit descriptors by enabling scatter gather in the descriptor
	 */
	if (InstancePtr->CommitPtr != InstancePtr->LastPtr) {
		u32 Control;

		Control = XBufDescriptor_GetControl(InstancePtr->CommitPtr);
		XBufDescriptor_SetControl(InstancePtr->CommitPtr, Control &
					  ~XDC_DMACR_SG_DISABLE_MASK);
	}
	/* Update the commit pointer to indicate that there is nothing to be
	 * committed, this state is used by start processing to know that the
	 * buffer descriptor to start is not waiting to be committed
	 */
	InstancePtr->CommitPtr = NULL;

	return XST_SUCCESS;
}

XStatus
XDmaChannel_GetDescriptor(XDmaChannel * InstancePtr,
			  XBufDescriptor ** BufDescriptorPtr)
{
	u32 Control;

	/* assert to verify input arguments */

	XASSERT_NONVOID(InstancePtr != NULL);
	XASSERT_NONVOID(BufDescriptorPtr != NULL);
	XASSERT_NONVOID(InstancePtr->IsReady == XCOMPONENT_IS_READY);

	/* if a scatter gather list has not been created yet, return a status */

	if (InstancePtr->TotalDescriptorCount == 0) {
		return XST_DMA_SG_NO_LIST;
	}

	/* if the buffer descriptor list is empty, then indicate an error */

	if (XDmaChannel_IsSgListEmpty(InstancePtr)) {
		return XST_DMA_SG_LIST_EMPTY;
	}

	/* retrieve the next buffer descriptor which is ready to be processed from
	 * the buffer descriptor list for the DMA channel, set the control word
	 * such that hardware will stop after the descriptor has been processed
	 */
	Control = XBufDescriptor_GetControl(InstancePtr->GetPtr);
	XBufDescriptor_SetControl(InstancePtr->GetPtr,
				  Control | XDC_DMACR_SG_DISABLE_MASK);

	/* set the input argument, which is also an output, to point to the
	 * buffer descriptor which is to be retrieved from the list
	 */
	*BufDescriptorPtr = InstancePtr->GetPtr;

	/* update the pointer of the DMA channel to reflect the buffer descriptor
	 * was retrieved from the list by setting it to the next buffer descriptor
	 * in the list and indicate one less descriptor in the list now
	 */
	InstancePtr->GetPtr = XBufDescriptor_GetNextPtr(InstancePtr->GetPtr);
	InstancePtr->ActiveDescriptorCount--;

	return XST_SUCCESS;
}

/*********************** Interrupt Collescing Functions **********************/

u32
XDmaChannel_GetPktCount(XDmaChannel * InstancePtr)
{
	/* assert to verify input arguments */

	XASSERT_NONVOID(InstancePtr != NULL);
	XASSERT_NONVOID(InstancePtr->IsReady == XCOMPONENT_IS_READY);

	/* get the unserviced packet count from the register and return it */

	return XIo_In32(InstancePtr->RegBaseAddress + XDC_UPC_REG_OFFSET);
}

void
XDmaChannel_DecrementPktCount(XDmaChannel * InstancePtr)
{
	u32 Register;

	/* assert to verify input arguments */

	XASSERT_VOID(InstancePtr != NULL);
	XASSERT_VOID(InstancePtr->IsReady == XCOMPONENT_IS_READY);

	/* if the unserviced packet count register can be decremented (rather
	 * than rolling over) decrement it by writing a 1 to the register,
	 * this is the only valid write to the register as it serves as an
	 * acknowledge that a packet was handled by the software
	 */
	Register = XIo_In32(InstancePtr->RegBaseAddress + XDC_UPC_REG_OFFSET);
	if (Register > 0) {
		XIo_Out32(InstancePtr->RegBaseAddress + XDC_UPC_REG_OFFSET,
			  1UL);
	}
}

XStatus
XDmaChannel_SetPktThreshold(XDmaChannel * InstancePtr, u8 Threshold)
{
	/* assert to verify input arguments, don't assert the threshold since
	 * it's range is unknown
	 */
	XASSERT_NONVOID(InstancePtr != NULL);
	XASSERT_NONVOID(InstancePtr->IsReady == XCOMPONENT_IS_READY);

	/* set the packet count threshold in the register such that an interrupt
	 * may be generated, if enabled, when the packet count threshold is
	 * reached or exceeded
	 */
	XIo_Out32(InstancePtr->RegBaseAddress + XDC_PCT_REG_OFFSET,
		  (u32) Threshold);

	/* indicate the packet count threshold was successfully set */

	return XST_SUCCESS;
}

u8
XDmaChannel_GetPktThreshold(XDmaChannel * InstancePtr)
{
	/* assert to verify input arguments */

	XASSERT_NONVOID(InstancePtr != NULL);
	XASSERT_NONVOID(InstancePtr->IsReady == XCOMPONENT_IS_READY);

	/* get the packet count threshold from the register and return it,
	 * since only 8 bits are used, cast it to return only those bits */

	return (u8) XIo_In32(InstancePtr->RegBaseAddress + XDC_PCT_REG_OFFSET);
}

void
XDmaChannel_SetPktWaitBound(XDmaChannel * InstancePtr, u32 WaitBound)
{
	/* assert to verify input arguments */

	XASSERT_VOID(InstancePtr != NULL);
	XASSERT_VOID(WaitBound < 1024);
	XASSERT_VOID(InstancePtr->IsReady == XCOMPONENT_IS_READY);

	/* set the packet wait bound in the register such that interrupt may be
	 * generated, if enabled, when packets have not been handled for a specific
	 * amount of time
	 */
	XIo_Out32(InstancePtr->RegBaseAddress + XDC_PWB_REG_OFFSET, WaitBound);
}

u32
XDmaChannel_GetPktWaitBound(XDmaChannel * InstancePtr)
{
	/* assert to verify input arguments */

	XASSERT_NONVOID(InstancePtr != NULL);
	XASSERT_NONVOID(InstancePtr->IsReady == XCOMPONENT_IS_READY);

	/* get the packet wait bound from the register and return it */

	return XIo_In32(InstancePtr->RegBaseAddress + XDC_PWB_REG_OFFSET);
}
