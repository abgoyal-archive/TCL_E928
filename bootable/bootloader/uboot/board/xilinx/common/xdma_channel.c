

/***************************** Include Files *********************************/

#include "xdma_channel.h"
#include "xbasic_types.h"
#include "xio.h"

/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Function Prototypes ******************************/

XStatus
XDmaChannel_Initialize(XDmaChannel * InstancePtr, u32 BaseAddress)
{
	/* assert to verify input arguments, don't assert base address */

	XASSERT_NONVOID(InstancePtr != NULL);

	/* setup the base address of the registers for the DMA channel such
	 * that register accesses can be done
	 */
	InstancePtr->RegBaseAddress = BaseAddress;

	/* initialize the scatter gather list such that it indicates it has not
	 * been created yet and the DMA channel is ready to use (initialized)
	 */
	InstancePtr->GetPtr = NULL;
	InstancePtr->PutPtr = NULL;
	InstancePtr->CommitPtr = NULL;
	InstancePtr->LastPtr = NULL;

	InstancePtr->TotalDescriptorCount = 0;
	InstancePtr->ActiveDescriptorCount = 0;
	InstancePtr->IsReady = XCOMPONENT_IS_READY;

	/* initialize the version of the component
	 */
	XVersion_FromString(&InstancePtr->Version, (s8 *)"1.00a");

	/* reset the DMA channel such that it's in a known state and ready
	 * and indicate the initialization occured with no errors, note that
	 * the is ready variable must be set before this call or reset will assert
	 */
	XDmaChannel_Reset(InstancePtr);

	return XST_SUCCESS;
}

u32
XDmaChannel_IsReady(XDmaChannel * InstancePtr)
{
	/* assert to verify input arguments used by the base component */

	XASSERT_NONVOID(InstancePtr != NULL);

	return InstancePtr->IsReady == XCOMPONENT_IS_READY;
}

XVersion *
XDmaChannel_GetVersion(XDmaChannel * InstancePtr)
{
	/* assert to verify input arguments */

	XASSERT_NONVOID(InstancePtr != NULL);
	XASSERT_NONVOID(InstancePtr->IsReady == XCOMPONENT_IS_READY);

	/* return a pointer to the version of the DMA channel */

	return &InstancePtr->Version;
}


#define XDC_CONTROL_REG_RESET_MASK  0x98000000UL	/* control reg reset value */

XStatus
XDmaChannel_SelfTest(XDmaChannel * InstancePtr)
{
	u32 ControlReg;

	/* assert to verify input arguments */

	XASSERT_NONVOID(InstancePtr != NULL);
	XASSERT_NONVOID(InstancePtr->IsReady == XCOMPONENT_IS_READY);

	/* reset the DMA channel such that it's in a known state before the test
	 * it resets to no interrupts enabled, the desired state for the test
	 */
	XDmaChannel_Reset(InstancePtr);

	/* this should be the first test to help prevent a lock up with the polling
	 * loop that occurs later in the test, check the reset value of the DMA
	 * control register to make sure it's correct, return with an error if not
	 */
	ControlReg = XDmaChannel_GetControl(InstancePtr);
	if (ControlReg != XDC_CONTROL_REG_RESET_MASK) {
		return XST_DMA_RESET_REGISTER_ERROR;
	}

	return XST_SUCCESS;
}

void
XDmaChannel_Reset(XDmaChannel * InstancePtr)
{
	/* assert to verify input arguments */

	XASSERT_VOID(InstancePtr != NULL);
	XASSERT_VOID(InstancePtr->IsReady == XCOMPONENT_IS_READY);

	/* reset the DMA channel such that it's in a known state, the reset
	 * register is self clearing such that it only has to be set
	 */
	XIo_Out32(InstancePtr->RegBaseAddress + XDC_RST_REG_OFFSET,
		  XDC_RESET_MASK);
}

u32
XDmaChannel_GetControl(XDmaChannel * InstancePtr)
{
	/* assert to verify input arguments */

	XASSERT_NONVOID(InstancePtr != NULL);
	XASSERT_NONVOID(InstancePtr->IsReady == XCOMPONENT_IS_READY);

	/* return the contents of the DMA control register */

	return XIo_In32(InstancePtr->RegBaseAddress + XDC_DMAC_REG_OFFSET);
}

void
XDmaChannel_SetControl(XDmaChannel * InstancePtr, u32 Control)
{
	/* assert to verify input arguments except the control which can't be
	 * asserted since all values are valid
	 */
	XASSERT_VOID(InstancePtr != NULL);
	XASSERT_VOID(InstancePtr->IsReady == XCOMPONENT_IS_READY);

	/* set the DMA control register to the specified value */

	XIo_Out32(InstancePtr->RegBaseAddress + XDC_DMAC_REG_OFFSET, Control);
}

u32
XDmaChannel_GetStatus(XDmaChannel * InstancePtr)
{
	/* assert to verify input arguments */

	XASSERT_NONVOID(InstancePtr != NULL);
	XASSERT_NONVOID(InstancePtr->IsReady == XCOMPONENT_IS_READY);

	/* return the contents of the DMA status register */

	return XIo_In32(InstancePtr->RegBaseAddress + XDC_DMAS_REG_OFFSET);
}

void
XDmaChannel_SetIntrStatus(XDmaChannel * InstancePtr, u32 Status)
{
	/* assert to verify input arguments except the status which can't be
	 * asserted since all values are valid
	 */
	XASSERT_VOID(InstancePtr != NULL);
	XASSERT_VOID(InstancePtr->IsReady == XCOMPONENT_IS_READY);

	/* set the interrupt status register with the specified value such that
	 * all bits which are set in the register are cleared effectively clearing
	 * any active interrupts
	 */
	XIo_Out32(InstancePtr->RegBaseAddress + XDC_IS_REG_OFFSET, Status);
}

u32
XDmaChannel_GetIntrStatus(XDmaChannel * InstancePtr)
{
	/* assert to verify input arguments */

	XASSERT_NONVOID(InstancePtr != NULL);
	XASSERT_NONVOID(InstancePtr->IsReady == XCOMPONENT_IS_READY);

	/* return the contents of the interrupt status register */

	return XIo_In32(InstancePtr->RegBaseAddress + XDC_IS_REG_OFFSET);
}

void
XDmaChannel_SetIntrEnable(XDmaChannel * InstancePtr, u32 Enable)
{
	/* assert to verify input arguments except the enable which can't be
	 * asserted since all values are valid
	 */
	XASSERT_VOID(InstancePtr != NULL);
	XASSERT_VOID(InstancePtr->IsReady == XCOMPONENT_IS_READY);

	/* set the interrupt enable register to the specified value */

	XIo_Out32(InstancePtr->RegBaseAddress + XDC_IE_REG_OFFSET, Enable);
}

u32
XDmaChannel_GetIntrEnable(XDmaChannel * InstancePtr)
{
	/* assert to verify input arguments */

	XASSERT_NONVOID(InstancePtr != NULL);
	XASSERT_NONVOID(InstancePtr->IsReady == XCOMPONENT_IS_READY);

	/* return the contents of the interrupt enable register */

	return XIo_In32(InstancePtr->RegBaseAddress + XDC_IE_REG_OFFSET);
}

void
XDmaChannel_Transfer(XDmaChannel * InstancePtr,
		     u32 * SourcePtr, u32 * DestinationPtr, u32 ByteCount)
{
	/* assert to verify input arguments and the alignment of any arguments
	 * which have expected alignments
	 */
	XASSERT_VOID(InstancePtr != NULL);
	XASSERT_VOID(SourcePtr != NULL);
	XASSERT_VOID(((u32) SourcePtr & 3) == 0);
	XASSERT_VOID(DestinationPtr != NULL);
	XASSERT_VOID(((u32) DestinationPtr & 3) == 0);
	XASSERT_VOID(ByteCount != 0);
	XASSERT_VOID(InstancePtr->IsReady == XCOMPONENT_IS_READY);

	/* setup the source and destination address registers for the transfer */

	XIo_Out32(InstancePtr->RegBaseAddress + XDC_SA_REG_OFFSET,
		  (u32) SourcePtr);

	XIo_Out32(InstancePtr->RegBaseAddress + XDC_DA_REG_OFFSET,
		  (u32) DestinationPtr);

	/* start the DMA transfer to copy from the source buffer to the
	 * destination buffer by writing the length to the length register
	 */
	XIo_Out32(InstancePtr->RegBaseAddress + XDC_LEN_REG_OFFSET, ByteCount);
}
