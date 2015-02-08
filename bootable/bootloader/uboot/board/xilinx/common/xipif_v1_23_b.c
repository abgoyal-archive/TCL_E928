
/* $Id: xipif_v1_23_b.c,v 1.1 2002/03/18 23:24:52 linnj Exp $ */

/***************************** Include Files *********************************/

#include "xipif_v1_23_b.h"
#include "xio.h"

/************************** Constant Definitions *****************************/

#define XIIF_V123B_FIRST_BIT_MASK     1UL

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Variable Definitions *****************************/

/************************** Function Prototypes ******************************/

static XStatus IpIntrSelfTest(u32 RegBaseAddress, u32 IpRegistersWidth);


#define XIIF_V123B_MAX_REG_BIT_COUNT 32

XStatus
XIpIfV123b_SelfTest(u32 RegBaseAddress, u8 IpRegistersWidth)
{
	XStatus Status;

	/* assert to verify arguments are valid */

	XASSERT_NONVOID(IpRegistersWidth <= XIIF_V123B_MAX_REG_BIT_COUNT);

	/* reset the IPIF such that it's in a known state before the test
	 * and interrupts are globally disabled
	 */
	XIIF_V123B_RESET(RegBaseAddress);

	/* perform the self test on the IP interrupt registers, if
	 * it is not successful exit with the status
	 */
	Status = IpIntrSelfTest(RegBaseAddress, IpRegistersWidth);
	if (Status != XST_SUCCESS) {
		return Status;
	}

	/* reset the IPIF such that it's in a known state before exiting test */

	XIIF_V123B_RESET(RegBaseAddress);

	/* reaching this point means there were no errors, return success */

	return XST_SUCCESS;
}

static XStatus
IpIntrSelfTest(u32 RegBaseAddress, u32 IpRegistersWidth)
{
	/* ensure that the IP interrupt interrupt enable register is  zero
	 * as it should be at reset, the interrupt status is dependent upon the
	 * IP such that it's reset value is not known
	 */
	if (XIIF_V123B_READ_IIER(RegBaseAddress) != 0) {
		return XST_IPIF_RESET_REGISTER_ERROR;
	}

	/* if there are any used IP interrupts, then test all of the interrupt
	 * bits in all testable registers
	 */
	if (IpRegistersWidth > 0) {
		u32 BitCount;
		u32 IpInterruptMask = XIIF_V123B_FIRST_BIT_MASK;
		u32 Mask = XIIF_V123B_FIRST_BIT_MASK;	/* bits assigned MSB to LSB */
		u32 InterruptStatus;

		/* generate the register masks to be used for IP register tests, the
		 * number of bits supported by the hardware is parameterizable such
		 * that only that number of bits are implemented in the registers, the
		 * bits are allocated starting at the MSB of the registers
		 */
		for (BitCount = 1; BitCount < IpRegistersWidth; BitCount++) {
			Mask = Mask << 1;
			IpInterruptMask |= Mask;
		}

		/* get the current IP interrupt status register contents, any bits
		 * already set must default to 1 at reset in the device and these
		 * bits can't be tested in the following test, remove these bits from
		 * the mask that was generated for the test
		 */
		InterruptStatus = XIIF_V123B_READ_IISR(RegBaseAddress);
		IpInterruptMask &= ~InterruptStatus;

		/* set the bits in the device status register and verify them by reading
		 * the register again, all bits of the register are latched
		 */
		XIIF_V123B_WRITE_IISR(RegBaseAddress, IpInterruptMask);
		InterruptStatus = XIIF_V123B_READ_IISR(RegBaseAddress);
		if ((InterruptStatus & IpInterruptMask) != IpInterruptMask)
		{
			return XST_IPIF_IP_STATUS_ERROR;
		}

		/* test to ensure that the bits set in the IP interrupt status register
		 * can be cleared by acknowledging them in the IP interrupt status
		 * register then read it again and verify it was cleared
		 */
		XIIF_V123B_WRITE_IISR(RegBaseAddress, IpInterruptMask);
		InterruptStatus = XIIF_V123B_READ_IISR(RegBaseAddress);
		if ((InterruptStatus & IpInterruptMask) != 0) {
			return XST_IPIF_IP_ACK_ERROR;
		}

		/* set the IP interrupt enable set register and then read the IP
		 * interrupt enable register and verify the interrupts were enabled
		 */
		XIIF_V123B_WRITE_IIER(RegBaseAddress, IpInterruptMask);
		if (XIIF_V123B_READ_IIER(RegBaseAddress) != IpInterruptMask) {
			return XST_IPIF_IP_ENABLE_ERROR;
		}

		/* clear the IP interrupt enable register and then read the
		 * IP interrupt enable register and verify the interrupts were disabled
		 */
		XIIF_V123B_WRITE_IIER(RegBaseAddress, 0);
		if (XIIF_V123B_READ_IIER(RegBaseAddress) != 0) {
			return XST_IPIF_IP_ENABLE_ERROR;
		}
	}
	return XST_SUCCESS;
}
