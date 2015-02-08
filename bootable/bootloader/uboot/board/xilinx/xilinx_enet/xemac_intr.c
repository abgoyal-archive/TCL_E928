
/*****************************************************************************/

/***************************** Include Files *********************************/

#include "xbasic_types.h"
#include "xemac_i.h"
#include "xio.h"
#include "xipif_v1_23_b.h"	/* Uses v1.23b of the IPIF */

/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Variable Definitions *****************************/

/************************** Function Prototypes ******************************/

/*****************************************************************************/
void
XEmac_SetErrorHandler(XEmac * InstancePtr, void *CallBackRef,
		      XEmac_ErrorHandler FuncPtr)
{
	XASSERT_VOID(InstancePtr != NULL);
	XASSERT_VOID(FuncPtr != NULL);
	XASSERT_VOID(InstancePtr->IsReady == XCOMPONENT_IS_READY);

	InstancePtr->ErrorHandler = FuncPtr;
	InstancePtr->ErrorRef = CallBackRef;
}

/****************************************************************************/
void
XEmac_CheckEmacError(XEmac * InstancePtr, u32 IntrStatus)
{
	u32 ResetError = FALSE;

	/*
	 * First check for receive fifo overrun/underrun errors. Most require a
	 * reset by the user to clear, but the data FIFO overrun error does not.
	 */
	if (IntrStatus & XEM_EIR_RECV_DFIFO_OVER_MASK) {
		InstancePtr->Stats.RecvOverrunErrors++;
		InstancePtr->Stats.FifoErrors++;
	}

	if (IntrStatus & XEM_EIR_RECV_LFIFO_OVER_MASK) {
		/*
		 * Receive Length FIFO overrun interrupts no longer occur in v1.00l
		 * and later of the EMAC device. Frames are just dropped by the EMAC
		 * if the length FIFO is full. The user would notice the Receive Missed
		 * Frame count incrementing without any other errors being reported.
		 * This code is left here for backward compatibility with v1.00k and
		 * older EMAC devices.
		 */
		InstancePtr->Stats.RecvOverrunErrors++;
		InstancePtr->Stats.FifoErrors++;
		ResetError = TRUE;	/* requires a reset */
	}

	if (IntrStatus & XEM_EIR_RECV_LFIFO_UNDER_MASK) {
		InstancePtr->Stats.RecvUnderrunErrors++;
		InstancePtr->Stats.FifoErrors++;
		ResetError = TRUE;	/* requires a reset */
	}

	/*
	 * Now check for general receive errors. Get the latest count where
	 * available, otherwise just bump the statistic so we know the interrupt
	 * occurred.
	 */
	if (IntrStatus & XEM_EIR_RECV_ERROR_MASK) {
		if (IntrStatus & XEM_EIR_RECV_MISSED_FRAME_MASK) {
			/*
			 * Caused by length FIFO or data FIFO overruns on receive side
			 */
			InstancePtr->Stats.RecvMissedFrameErrors =
			    XIo_In32(InstancePtr->BaseAddress +
				     XEM_RMFC_OFFSET);
		}

		if (IntrStatus & XEM_EIR_RECV_COLLISION_MASK) {
			InstancePtr->Stats.RecvCollisionErrors =
			    XIo_In32(InstancePtr->BaseAddress + XEM_RCC_OFFSET);
		}

		if (IntrStatus & XEM_EIR_RECV_FCS_ERROR_MASK) {
			InstancePtr->Stats.RecvFcsErrors =
			    XIo_In32(InstancePtr->BaseAddress +
				     XEM_RFCSEC_OFFSET);
		}

		if (IntrStatus & XEM_EIR_RECV_LEN_ERROR_MASK) {
			InstancePtr->Stats.RecvLengthFieldErrors++;
		}

		if (IntrStatus & XEM_EIR_RECV_SHORT_ERROR_MASK) {
			InstancePtr->Stats.RecvShortErrors++;
		}

		if (IntrStatus & XEM_EIR_RECV_LONG_ERROR_MASK) {
			InstancePtr->Stats.RecvLongErrors++;
		}

		if (IntrStatus & XEM_EIR_RECV_ALIGN_ERROR_MASK) {
			InstancePtr->Stats.RecvAlignmentErrors =
			    XIo_In32(InstancePtr->BaseAddress +
				     XEM_RAEC_OFFSET);
		}

		/*
		 * Bump recv interrupts stats only if not scatter-gather DMA (this
		 * stat gets bumped elsewhere in that case)
		 */
		if (!XEmac_mIsSgDma(InstancePtr)) {
			InstancePtr->Stats.RecvInterrupts++;	/* TODO: double bump? */
		}

	}

	/*
	 * Check for transmit errors. These apply to both DMA and non-DMA modes
	 * of operation. The entire device should be reset after overruns or
	 * underruns.
	 */
	if (IntrStatus & (XEM_EIR_XMIT_SFIFO_OVER_MASK |
			  XEM_EIR_XMIT_LFIFO_OVER_MASK)) {
		InstancePtr->Stats.XmitOverrunErrors++;
		InstancePtr->Stats.FifoErrors++;
		ResetError = TRUE;
	}

	if (IntrStatus & (XEM_EIR_XMIT_SFIFO_UNDER_MASK |
			  XEM_EIR_XMIT_LFIFO_UNDER_MASK)) {
		InstancePtr->Stats.XmitUnderrunErrors++;
		InstancePtr->Stats.FifoErrors++;
		ResetError = TRUE;
	}

	if (ResetError) {
		/*
		 * If a reset error occurred, disable the EMAC interrupts since the
		 * reset-causing interrupt(s) is latched in the EMAC - meaning it will
		 * keep occurring until the device is reset. In order to give the higher
		 * layer software time to reset the device, we have to disable the
		 * overrun/underrun interrupts until that happens. We trust that the
		 * higher layer resets the device. We are able to get away with disabling
		 * all EMAC interrupts since the only interrupts it generates are for
		 * error conditions, and we don't care about any more errors right now.
		 */
		XIIF_V123B_WRITE_IIER(InstancePtr->BaseAddress, 0);

		/*
		 * Invoke the error handler callback, which should result in a reset
		 * of the device by the upper layer software.
		 */
		InstancePtr->ErrorHandler(InstancePtr->ErrorRef,
					  XST_RESET_ERROR);
	}
}

/*****************************************************************************/
void
XEmac_CheckFifoRecvError(XEmac * InstancePtr)
{
	/*
	 * Although the deadlock is currently the only interrupt from a packet
	 * FIFO, make sure it is deadlocked before taking action. There is no
	 * need to clear this interrupt since it requires a reset of the device.
	 */
	if (XPF_V100B_IS_DEADLOCKED(&InstancePtr->RecvFifo)) {
		u32 IntrEnable;

		InstancePtr->Stats.FifoErrors++;

		/*
		 * Invoke the error callback function, which should result in a reset
		 * of the device by the upper layer software. We first need to disable
		 * the FIFO interrupt, since otherwise the upper layer thread that
		 * handles the reset may never run because this interrupt condition
		 * doesn't go away until a reset occurs (there is no way to ack it).
		 */
		IntrEnable = XIIF_V123B_READ_DIER(InstancePtr->BaseAddress);
		XIIF_V123B_WRITE_DIER(InstancePtr->BaseAddress,
				      IntrEnable & ~XEM_IPIF_RECV_FIFO_MASK);

		InstancePtr->ErrorHandler(InstancePtr->ErrorRef,
					  XST_FIFO_ERROR);
	}
}

/*****************************************************************************/
void
XEmac_CheckFifoSendError(XEmac * InstancePtr)
{
	/*
	 * Although the deadlock is currently the only interrupt from a packet
	 * FIFO, make sure it is deadlocked before taking action. There is no
	 * need to clear this interrupt since it requires a reset of the device.
	 */
	if (XPF_V100B_IS_DEADLOCKED(&InstancePtr->SendFifo)) {
		u32 IntrEnable;

		InstancePtr->Stats.FifoErrors++;

		/*
		 * Invoke the error callback function, which should result in a reset
		 * of the device by the upper layer software. We first need to disable
		 * the FIFO interrupt, since otherwise the upper layer thread that
		 * handles the reset may never run because this interrupt condition
		 * doesn't go away until a reset occurs (there is no way to ack it).
		 */
		IntrEnable = XIIF_V123B_READ_DIER(InstancePtr->BaseAddress);
		XIIF_V123B_WRITE_DIER(InstancePtr->BaseAddress,
				      IntrEnable & ~XEM_IPIF_SEND_FIFO_MASK);

		InstancePtr->ErrorHandler(InstancePtr->ErrorRef,
					  XST_FIFO_ERROR);
	}
}
