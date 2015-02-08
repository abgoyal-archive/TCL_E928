
/*****************************************************************************/

/***************************** Include Files *********************************/

#include "xbasic_types.h"
#include "xemac_i.h"
#include "xio.h"
#include "xipif_v1_23_b.h"	/* Uses v1.23b of the IPIF */

/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Function Prototypes ******************************/

static XStatus ConfigureDma(XEmac * InstancePtr);
static XStatus ConfigureFifo(XEmac * InstancePtr);
static void StubFifoHandler(void *CallBackRef);
static void StubErrorHandler(void *CallBackRef, XStatus ErrorCode);
static void StubSgHandler(void *CallBackRef, XBufDescriptor * BdPtr,
			  u32 NumBds);

/************************** Variable Definitions *****************************/

/*****************************************************************************/
XStatus
XEmac_Initialize(XEmac * InstancePtr, u16 DeviceId)
{
	XStatus Result;
	XEmac_Config *ConfigPtr;	/* configuration information */

	XASSERT_NONVOID(InstancePtr != NULL);

	/*
	 * If the device is started, disallow the initialize and return a status
	 * indicating it is started.  This allows the user to stop the device
	 * and reinitialize, but prevents a user from inadvertently initializing
	 */
	if (InstancePtr->IsStarted == XCOMPONENT_IS_STARTED) {
		return XST_DEVICE_IS_STARTED;
	}

	/*
	 * Lookup the device configuration in the temporary CROM table. Use this
	 * configuration info down below when initializing this component.
	 */
	ConfigPtr = XEmac_LookupConfig(DeviceId);
	if (ConfigPtr == NULL) {
		return XST_DEVICE_NOT_FOUND;
	}

	/*
	 * Set some default values
	 */
	InstancePtr->IsReady = 0;
	InstancePtr->IsStarted = 0;
	InstancePtr->IpIfDmaConfig = ConfigPtr->IpIfDmaConfig;
	InstancePtr->HasMii = ConfigPtr->HasMii;
	InstancePtr->HasMulticastHash = FALSE;

	/* Always default polled to false, let user configure this mode */
	InstancePtr->IsPolled = FALSE;
	InstancePtr->FifoRecvHandler = StubFifoHandler;
	InstancePtr->FifoSendHandler = StubFifoHandler;
	InstancePtr->ErrorHandler = StubErrorHandler;
	InstancePtr->SgRecvHandler = StubSgHandler;
	InstancePtr->SgSendHandler = StubSgHandler;

	/*
	 * Clear the statistics for this driver
	 */
	XEmac_mClearStruct((u8 *) & InstancePtr->Stats, sizeof (XEmac_Stats));

	/*
	 * Initialize the device register base addresses
	 */
	InstancePtr->BaseAddress = ConfigPtr->BaseAddress;

	/*
	 * Configure the send and receive FIFOs in the MAC
	 */
	Result = ConfigureFifo(InstancePtr);
	if (Result != XST_SUCCESS) {
		return Result;
	}

	/*
	 * If the device is configured for DMA, configure the send and receive DMA
	 * channels in the MAC.
	 */
	if (XEmac_mIsDma(InstancePtr)) {
		Result = ConfigureDma(InstancePtr);
		if (Result != XST_SUCCESS) {
			return Result;
		}
	}

	/*
	 * Indicate the component is now ready to use. Note that this is done before
	 * we reset the device and the PHY below, which may seem a bit odd. The
	 * choice was made to move it here rather than remove the asserts in various
	 * functions (e.g., Reset() and all functions that it calls).  Applications
	 * that use multiple threads, one to initialize the XEmac driver and one
	 * waiting on the IsReady condition could have a problem with this sequence.
	 */
	InstancePtr->IsReady = XCOMPONENT_IS_READY;

	/*
	 * Reset the MAC to get it into its initial state. It is expected that
	 * device configuration by the user will take place after this
	 * initialization is done, but before the device is started.
	 */
	XEmac_Reset(InstancePtr);

	return XST_SUCCESS;
}

/*****************************************************************************/
XStatus
XEmac_Start(XEmac * InstancePtr)
{
	u32 ControlReg;
	XStatus Result;

	XASSERT_NONVOID(InstancePtr != NULL);
	XASSERT_NONVOID(InstancePtr->IsReady == XCOMPONENT_IS_READY);

	/*
	 * If it is already started, return a status indicating so
	 */
	if (InstancePtr->IsStarted == XCOMPONENT_IS_STARTED) {
		return XST_DEVICE_IS_STARTED;
	}

	/*
	 * If not polled, enable interrupts
	 */
	if (!InstancePtr->IsPolled) {
		/*
		 * Verify that the callbacks have been registered, then enable
		 * interrupts
		 */
		if (XEmac_mIsSgDma(InstancePtr)) {
			if ((InstancePtr->SgRecvHandler == StubSgHandler) ||
			    (InstancePtr->SgSendHandler == StubSgHandler)) {
				return XST_NO_CALLBACK;
			}

			/* Enable IPIF interrupts */
			XIIF_V123B_WRITE_DIER(InstancePtr->BaseAddress,
					      XEM_IPIF_DMA_DFT_MASK |
					      XIIF_V123B_ERROR_MASK);
			XIIF_V123B_WRITE_IIER(InstancePtr->BaseAddress,
					      XEM_EIR_DFT_SG_MASK);

			/* Enable scatter-gather DMA interrupts */
			XDmaChannel_SetIntrEnable(&InstancePtr->RecvChannel,
						  XEM_DMA_SG_INTR_MASK);
			XDmaChannel_SetIntrEnable(&InstancePtr->SendChannel,
						  XEM_DMA_SG_INTR_MASK);
		} else {
			if ((InstancePtr->FifoRecvHandler == StubFifoHandler) ||
			    (InstancePtr->FifoSendHandler == StubFifoHandler)) {
				return XST_NO_CALLBACK;
			}

			/* Enable IPIF interrupts (used by simple DMA also) */
			XIIF_V123B_WRITE_DIER(InstancePtr->BaseAddress,
					      XEM_IPIF_FIFO_DFT_MASK |
					      XIIF_V123B_ERROR_MASK);
			XIIF_V123B_WRITE_IIER(InstancePtr->BaseAddress,
					      XEM_EIR_DFT_FIFO_MASK);
		}

		/* Enable the global IPIF interrupt output */
		XIIF_V123B_GINTR_ENABLE(InstancePtr->BaseAddress);
	}

	/*
	 * Indicate that the device is started before we enable the transmitter
	 * or receiver. This needs to be done before because as soon as the
	 * receiver is enabled we may get an interrupt, and there are functions
	 * in the interrupt handling path that rely on the IsStarted flag.
	 */
	InstancePtr->IsStarted = XCOMPONENT_IS_STARTED;

	/*
	 * Enable the transmitter, and receiver (do a read/modify/write to preserve
	 * current settings). There is no critical section here since this register
	 * is not modified during interrupt context.
	 */
	ControlReg = XIo_In32(InstancePtr->BaseAddress + XEM_ECR_OFFSET);
	ControlReg &= ~(XEM_ECR_XMIT_RESET_MASK | XEM_ECR_RECV_RESET_MASK);
	ControlReg |= (XEM_ECR_XMIT_ENABLE_MASK | XEM_ECR_RECV_ENABLE_MASK);

	XIo_Out32(InstancePtr->BaseAddress + XEM_ECR_OFFSET, ControlReg);

	/*
	 * If configured with scatter-gather DMA and not polled, restart the
	 * DMA channels in case there are buffers ready to be sent or received into.
	 * The DMA SgStart function uses data that can be modified during interrupt
	 * context, so a critical section is required here.
	 */
	if ((XEmac_mIsSgDma(InstancePtr)) && (!InstancePtr->IsPolled)) {
		XIIF_V123B_GINTR_DISABLE(InstancePtr->BaseAddress);

		/*
		 * The only error we care about is if the list has not yet been
		 * created, or on receive, if no buffer descriptors have been
		 * added yet (the list is empty). Other errors are benign at this point.
		 */
		Result = XDmaChannel_SgStart(&InstancePtr->RecvChannel);
		if ((Result == XST_DMA_SG_NO_LIST)
		    || (Result == XST_DMA_SG_LIST_EMPTY)) {
			XIIF_V123B_GINTR_ENABLE(InstancePtr->BaseAddress);
			return Result;
		}

		Result = XDmaChannel_SgStart(&InstancePtr->SendChannel);
		if (Result == XST_DMA_SG_NO_LIST) {
			XIIF_V123B_GINTR_ENABLE(InstancePtr->BaseAddress);
			return Result;
		}

		XIIF_V123B_GINTR_ENABLE(InstancePtr->BaseAddress);
	}

	return XST_SUCCESS;
}

/*****************************************************************************/
XStatus
XEmac_Stop(XEmac * InstancePtr)
{
	u32 ControlReg;

	XASSERT_NONVOID(InstancePtr != NULL);
	XASSERT_NONVOID(InstancePtr->IsReady == XCOMPONENT_IS_READY);

	/*
	 * If the device is already stopped, do nothing but return a status
	 * indicating so
	 */
	if (InstancePtr->IsStarted != XCOMPONENT_IS_STARTED) {
		return XST_DEVICE_IS_STOPPED;
	}

	/*
	 * If configured for scatter-gather DMA, stop the DMA channels. Ignore
	 * the XST_DMA_SG_IS_STOPPED return code. There is a critical section
	 * here between SgStart and SgStop, and SgStart can be called in interrupt
	 * context, so disable interrupts while calling SgStop.
	 */
	if (XEmac_mIsSgDma(InstancePtr)) {
		XBufDescriptor *BdTemp;	/* temporary descriptor pointer */

		XIIF_V123B_GINTR_DISABLE(InstancePtr->BaseAddress);

		(void) XDmaChannel_SgStop(&InstancePtr->SendChannel, &BdTemp);
		(void) XDmaChannel_SgStop(&InstancePtr->RecvChannel, &BdTemp);

		XIIF_V123B_GINTR_ENABLE(InstancePtr->BaseAddress);
	}

	/*
	 * Disable the transmitter and receiver. There is no critical section
	 * here since this register is not modified during interrupt context.
	 */
	ControlReg = XIo_In32(InstancePtr->BaseAddress + XEM_ECR_OFFSET);
	ControlReg &= ~(XEM_ECR_XMIT_ENABLE_MASK | XEM_ECR_RECV_ENABLE_MASK);
	XIo_Out32(InstancePtr->BaseAddress + XEM_ECR_OFFSET, ControlReg);

	/*
	 * If not in polled mode, disable interrupts for IPIF (includes MAC and
	 * DMAs)
	 */
	if (!InstancePtr->IsPolled) {
		XIIF_V123B_GINTR_DISABLE(InstancePtr->BaseAddress);
	}

	InstancePtr->IsStarted = 0;

	return XST_SUCCESS;
}

/*****************************************************************************/
void
XEmac_Reset(XEmac * InstancePtr)
{
	XASSERT_VOID(InstancePtr != NULL);
	XASSERT_VOID(InstancePtr->IsReady == XCOMPONENT_IS_READY);

	/*
	 * Stop the device first
	 */
	(void) XEmac_Stop(InstancePtr);

	/*
	 * Take the driver out of polled mode
	 */
	InstancePtr->IsPolled = FALSE;

	/*
	 * Reset the entire IPIF at once.  If we choose someday to reset each
	 * hardware block separately, the reset should occur in the direction of
	 * data flow. For example, for the send direction the reset order is DMA
	 * first, then FIFO, then the MAC transmitter.
	 */
	XIIF_V123B_RESET(InstancePtr->BaseAddress);

	if (XEmac_mIsSgDma(InstancePtr)) {
		/*
		 * After reset, configure the scatter-gather DMA packet threshold and
		 * packet wait bound registers to default values. Ignore the return
		 * values of these functions since they only return error if the device
		 * is not stopped.
		 */
		(void) XEmac_SetPktThreshold(InstancePtr, XEM_SEND,
					     XEM_SGDMA_DFT_THRESHOLD);
		(void) XEmac_SetPktThreshold(InstancePtr, XEM_RECV,
					     XEM_SGDMA_DFT_THRESHOLD);
		(void) XEmac_SetPktWaitBound(InstancePtr, XEM_SEND,
					     XEM_SGDMA_DFT_WAITBOUND);
		(void) XEmac_SetPktWaitBound(InstancePtr, XEM_RECV,
					     XEM_SGDMA_DFT_WAITBOUND);
	}
}

/*****************************************************************************/
XStatus
XEmac_SetMacAddress(XEmac * InstancePtr, u8 * AddressPtr)
{
	u32 MacAddr = 0;

	XASSERT_NONVOID(InstancePtr != NULL);
	XASSERT_NONVOID(AddressPtr != NULL);
	XASSERT_NONVOID(InstancePtr->IsReady == XCOMPONENT_IS_READY);

	/*
	 * The device must be stopped before setting the MAC address
	 */
	if (InstancePtr->IsStarted == XCOMPONENT_IS_STARTED) {
		return XST_DEVICE_IS_STARTED;
	}

	/*
	 * Set the device station address high and low registers
	 */
	MacAddr = (AddressPtr[0] << 8) | AddressPtr[1];
	XIo_Out32(InstancePtr->BaseAddress + XEM_SAH_OFFSET, MacAddr);

	MacAddr = (AddressPtr[2] << 24) | (AddressPtr[3] << 16) |
	    (AddressPtr[4] << 8) | AddressPtr[5];

	XIo_Out32(InstancePtr->BaseAddress + XEM_SAL_OFFSET, MacAddr);

	return XST_SUCCESS;
}

/*****************************************************************************/
void
XEmac_GetMacAddress(XEmac * InstancePtr, u8 * BufferPtr)
{
	u32 MacAddrHi;
	u32 MacAddrLo;

	XASSERT_VOID(InstancePtr != NULL);
	XASSERT_VOID(BufferPtr != NULL);
	XASSERT_VOID(InstancePtr->IsReady == XCOMPONENT_IS_READY);

	MacAddrHi = XIo_In32(InstancePtr->BaseAddress + XEM_SAH_OFFSET);
	MacAddrLo = XIo_In32(InstancePtr->BaseAddress + XEM_SAL_OFFSET);

	BufferPtr[0] = (u8) (MacAddrHi >> 8);
	BufferPtr[1] = (u8) MacAddrHi;
	BufferPtr[2] = (u8) (MacAddrLo >> 24);
	BufferPtr[3] = (u8) (MacAddrLo >> 16);
	BufferPtr[4] = (u8) (MacAddrLo >> 8);
	BufferPtr[5] = (u8) MacAddrLo;
}

/******************************************************************************/
static XStatus
ConfigureDma(XEmac * InstancePtr)
{
	XStatus Result;

	/*
	 * Initialize the DMA channels with their base addresses. We assume
	 * scatter-gather DMA is the only possible configuration. Descriptor space
	 * will need to be set later by the upper layer.
	 */
	Result = XDmaChannel_Initialize(&InstancePtr->RecvChannel,
					InstancePtr->BaseAddress +
					XEM_DMA_RECV_OFFSET);
	if (Result != XST_SUCCESS) {
		return Result;
	}

	Result = XDmaChannel_Initialize(&InstancePtr->SendChannel,
					InstancePtr->BaseAddress +
					XEM_DMA_SEND_OFFSET);

	return Result;
}

/******************************************************************************/
static XStatus
ConfigureFifo(XEmac * InstancePtr)
{
	XStatus Result;

	/*
	 * Return status from the packet FIFOs initialization is ignored since
	 * they always return success.
	 */
	Result = XPacketFifoV100b_Initialize(&InstancePtr->RecvFifo,
					     InstancePtr->BaseAddress +
					     XEM_PFIFO_RXREG_OFFSET,
					     InstancePtr->BaseAddress +
					     XEM_PFIFO_RXDATA_OFFSET);
	if (Result != XST_SUCCESS) {
		return Result;
	}

	Result = XPacketFifoV100b_Initialize(&InstancePtr->SendFifo,
					     InstancePtr->BaseAddress +
					     XEM_PFIFO_TXREG_OFFSET,
					     InstancePtr->BaseAddress +
					     XEM_PFIFO_TXDATA_OFFSET);
	return Result;
}

/******************************************************************************/
static void
StubSgHandler(void *CallBackRef, XBufDescriptor * BdPtr, u32 NumBds)
{
	XASSERT_VOID_ALWAYS();
}

/******************************************************************************/
static void
StubFifoHandler(void *CallBackRef)
{
	XASSERT_VOID_ALWAYS();
}

/******************************************************************************/
static void
StubErrorHandler(void *CallBackRef, XStatus ErrorCode)
{
	XASSERT_VOID_ALWAYS();
}

/*****************************************************************************/
XEmac_Config *
XEmac_LookupConfig(u16 DeviceId)
{
	XEmac_Config *CfgPtr = NULL;
	int i;

	for (i = 0; i < XPAR_XEMAC_NUM_INSTANCES; i++) {
		if (XEmac_ConfigTable[i].DeviceId == DeviceId) {
			CfgPtr = &XEmac_ConfigTable[i];
			break;
		}
	}

	return CfgPtr;
}
