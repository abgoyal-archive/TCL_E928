
/*****************************************************************************/

/***************************** Include Files *********************************/

#include "xbasic_types.h"
#include "xemac_i.h"
#include "xio.h"

/************************** Constant Definitions *****************************/

#define XEM_MAX_IFG         32	/* Maximum Interframe gap value */

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Function Prototypes ******************************/

/************************** Variable Definitions *****************************/

typedef struct {
	u32 Option;
	u32 Mask;
} OptionMap;

static OptionMap OptionsTable[] = {
	{XEM_UNICAST_OPTION, XEM_ECR_UNICAST_ENABLE_MASK},
	{XEM_BROADCAST_OPTION, XEM_ECR_BROAD_ENABLE_MASK},
	{XEM_PROMISC_OPTION, XEM_ECR_PROMISC_ENABLE_MASK},
	{XEM_FDUPLEX_OPTION, XEM_ECR_FULL_DUPLEX_MASK},
	{XEM_LOOPBACK_OPTION, XEM_ECR_LOOPBACK_MASK},
	{XEM_MULTICAST_OPTION, XEM_ECR_MULTI_ENABLE_MASK},
	{XEM_FLOW_CONTROL_OPTION, XEM_ECR_PAUSE_FRAME_MASK},
	{XEM_INSERT_PAD_OPTION, XEM_ECR_XMIT_PAD_ENABLE_MASK},
	{XEM_INSERT_FCS_OPTION, XEM_ECR_XMIT_FCS_ENABLE_MASK},
	{XEM_INSERT_ADDR_OPTION, XEM_ECR_XMIT_ADDR_INSERT_MASK},
	{XEM_OVWRT_ADDR_OPTION, XEM_ECR_XMIT_ADDR_OVWRT_MASK},
	{XEM_STRIP_PAD_FCS_OPTION, XEM_ECR_RECV_STRIP_ENABLE_MASK}
};

#define XEM_NUM_OPTIONS     (sizeof(OptionsTable) / sizeof(OptionMap))

/*****************************************************************************/
XStatus
XEmac_SetOptions(XEmac * InstancePtr, u32 OptionsFlag)
{
	u32 ControlReg;
	int Index;

	XASSERT_NONVOID(InstancePtr != NULL);
	XASSERT_NONVOID(InstancePtr->IsReady == XCOMPONENT_IS_READY);

	if (InstancePtr->IsStarted == XCOMPONENT_IS_STARTED) {
		return XST_DEVICE_IS_STARTED;
	}

	ControlReg = XIo_In32(InstancePtr->BaseAddress + XEM_ECR_OFFSET);

	/*
	 * Loop through the options table, turning the option on or off
	 * depending on whether the bit is set in the incoming options flag.
	 */
	for (Index = 0; Index < XEM_NUM_OPTIONS; Index++) {
		if (OptionsFlag & OptionsTable[Index].Option) {
			ControlReg |= OptionsTable[Index].Mask;	/* turn it on */
		} else {
			ControlReg &= ~OptionsTable[Index].Mask;	/* turn it off */
		}
	}

	/*
	 * TODO: need to validate addr-overwrite only if addr-insert?
	 */

	/*
	 * Now write the control register. Leave it to the upper layers
	 * to restart the device.
	 */
	XIo_Out32(InstancePtr->BaseAddress + XEM_ECR_OFFSET, ControlReg);

	/*
	 * Check the polled option
	 */
	if (OptionsFlag & XEM_POLLED_OPTION) {
		InstancePtr->IsPolled = TRUE;
	} else {
		InstancePtr->IsPolled = FALSE;
	}

	return XST_SUCCESS;
}

/*****************************************************************************/
u32
XEmac_GetOptions(XEmac * InstancePtr)
{
	u32 OptionsFlag = 0;
	u32 ControlReg;
	int Index;

	XASSERT_NONVOID(InstancePtr != NULL);
	XASSERT_NONVOID(InstancePtr->IsReady == XCOMPONENT_IS_READY);

	/*
	 * Get the control register to determine which options are currently set.
	 */
	ControlReg = XIo_In32(InstancePtr->BaseAddress + XEM_ECR_OFFSET);

	/*
	 * Loop through the options table to determine which options are set
	 */
	for (Index = 0; Index < XEM_NUM_OPTIONS; Index++) {
		if (ControlReg & OptionsTable[Index].Mask) {
			OptionsFlag |= OptionsTable[Index].Option;
		}
	}

	if (InstancePtr->IsPolled) {
		OptionsFlag |= XEM_POLLED_OPTION;
	}

	return OptionsFlag;
}

/*****************************************************************************/
XStatus
XEmac_SetInterframeGap(XEmac * InstancePtr, u8 Part1, u8 Part2)
{
	u32 Ifg;

	XASSERT_NONVOID(InstancePtr != NULL);
	XASSERT_NONVOID(Part1 < XEM_MAX_IFG);
	XASSERT_NONVOID(Part2 < XEM_MAX_IFG);
	XASSERT_NONVOID(InstancePtr->IsReady == XCOMPONENT_IS_READY);

	/*
	 * Be sure device has been stopped
	 */
	if (InstancePtr->IsStarted == XCOMPONENT_IS_STARTED) {
		return XST_DEVICE_IS_STARTED;
	}

	Ifg = Part1 << XEM_IFGP_PART1_SHIFT;
	Ifg |= (Part2 << XEM_IFGP_PART2_SHIFT);
	XIo_Out32(InstancePtr->BaseAddress + XEM_IFGP_OFFSET, Ifg);

	return XST_SUCCESS;
}

/*****************************************************************************/
void
XEmac_GetInterframeGap(XEmac * InstancePtr, u8 * Part1Ptr, u8 * Part2Ptr)
{
	u32 Ifg;

	XASSERT_VOID(InstancePtr != NULL);
	XASSERT_VOID(Part1Ptr != NULL);
	XASSERT_VOID(Part2Ptr != NULL);
	XASSERT_VOID(InstancePtr->IsReady == XCOMPONENT_IS_READY);

	Ifg = XIo_In32(InstancePtr->BaseAddress + XEM_IFGP_OFFSET);
	*Part1Ptr = (Ifg & XEM_IFGP_PART1_MASK) >> XEM_IFGP_PART1_SHIFT;
	*Part2Ptr = (Ifg & XEM_IFGP_PART2_MASK) >> XEM_IFGP_PART2_SHIFT;
}
