
/*****************************************************************************/

/***************************** Include Files *********************************/

#include "xbasic_types.h"
#include "xio.h"
#include "xstatus.h"
#include "xpacket_fifo_v1_00_b.h"

/************************** Constant Definitions *****************************/

/* width of a FIFO word */

#define XPF_FIFO_WIDTH_BYTE_COUNT       4UL

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/

/************************* Variable Definitions ******************************/

/************************** Function Prototypes ******************************/

/*****************************************************************************/
XStatus
XPacketFifoV100b_Initialize(XPacketFifoV100b * InstancePtr,
			    u32 RegBaseAddress, u32 DataBaseAddress)
{
	/* assert to verify input argument are valid */

	XASSERT_NONVOID(InstancePtr != NULL);

	/* initialize the component variables to the specified state */

	InstancePtr->RegBaseAddress = RegBaseAddress;
	InstancePtr->DataBaseAddress = DataBaseAddress;
	InstancePtr->IsReady = XCOMPONENT_IS_READY;

	/* reset the FIFO such that it's empty and ready to use and indicate the
	 * initialization was successful, note that the is ready variable must be
	 * set prior to calling the reset function to prevent an assert
	 */
	XPF_V100B_RESET(InstancePtr);

	return XST_SUCCESS;
}

/*****************************************************************************/
XStatus
XPacketFifoV100b_SelfTest(XPacketFifoV100b * InstancePtr, u32 FifoType)
{
	u32 Register;

	/* assert to verify valid input arguments */

	XASSERT_NONVOID(InstancePtr != NULL);
	XASSERT_NONVOID((FifoType == XPF_READ_FIFO_TYPE) ||
			(FifoType == XPF_WRITE_FIFO_TYPE));
	XASSERT_NONVOID(InstancePtr->IsReady == XCOMPONENT_IS_READY);

	/* reset the fifo and then check to make sure the occupancy/vacancy
	 * register contents are correct for a reset condition
	 */
	XPF_V100B_RESET(InstancePtr);

	Register = XIo_In32(InstancePtr->RegBaseAddress +
			    XPF_COUNT_STATUS_REG_OFFSET);

	/* check the value of the register to ensure that it's correct for the
	 * specified FIFO type since both FIFO types reset to empty, but a bit
	 * in the register changes definition based upon FIFO type
	 */

	if (FifoType == XPF_READ_FIFO_TYPE) {
		/* check the regiser value for a read FIFO which should be empty */

		if (Register != XPF_EMPTY_FULL_MASK) {
			return XST_PFIFO_BAD_REG_VALUE;
		}
	} else {
		/* check the register value for a write FIFO which should not be full
		 * on reset
		 */
		if ((Register & XPF_EMPTY_FULL_MASK) != 0) {
			return XST_PFIFO_BAD_REG_VALUE;
		}
	}

	/* the test was successful */

	return XST_SUCCESS;
}

/*****************************************************************************/
XStatus
XPacketFifoV100b_Read(XPacketFifoV100b * InstancePtr,
		      u8 * BufferPtr, u32 ByteCount)
{
	u32 FifoCount;
	u32 WordCount;
	u32 ExtraByteCount;
	u32 *WordBuffer = (u32 *) BufferPtr;

	/* assert to verify valid input arguments including 32 bit alignment of
	 * the buffer pointer
	 */
	XASSERT_NONVOID(InstancePtr != NULL);
	XASSERT_NONVOID(BufferPtr != NULL);
	XASSERT_NONVOID(((u32) BufferPtr &
			 (XPF_FIFO_WIDTH_BYTE_COUNT - 1)) == 0);
	XASSERT_NONVOID(ByteCount != 0);
	XASSERT_NONVOID(InstancePtr->IsReady == XCOMPONENT_IS_READY);

	/* get the count of how many 32 bit words are in the FIFO, if there aren't
	 * enought words to satisfy the request, return an error
	 */

	FifoCount = XIo_In32(InstancePtr->RegBaseAddress +
			     XPF_COUNT_STATUS_REG_OFFSET) & XPF_COUNT_MASK;

	if ((FifoCount * XPF_FIFO_WIDTH_BYTE_COUNT) < ByteCount) {
		return XST_PFIFO_LACK_OF_DATA;
	}

	/* calculate the number of words to read from the FIFO before the word
	 * containing the extra bytes, and calculate the number of extra bytes
	 * the extra bytes are defined as those at the end of the buffer when
	 * the buffer does not end on a 32 bit boundary
	 */
	WordCount = ByteCount / XPF_FIFO_WIDTH_BYTE_COUNT;
	ExtraByteCount = ByteCount % XPF_FIFO_WIDTH_BYTE_COUNT;

	/* Read the 32 bit words from the FIFO for all the buffer except the
	 * last word which contains the extra bytes, the following code assumes
	 * that the buffer is 32 bit aligned, otherwise an alignment exception could
	 * be generated
	 */
	for (FifoCount = 0; FifoCount < WordCount; FifoCount++) {
		WordBuffer[FifoCount] = XIo_In32(InstancePtr->DataBaseAddress);
	}

	/* if there are extra bytes to handle, read the last word from the FIFO
	 * and insert the extra bytes into the buffer
	 */
	if (ExtraByteCount > 0) {
		u32 LastWord;
		u8 *ExtraBytesBuffer = (u8 *) (WordBuffer + WordCount);

		/* get the last word from the FIFO for the extra bytes */

		LastWord = XIo_In32(InstancePtr->DataBaseAddress);

		/* one extra byte in the last word, put the byte into the next location
		 * of the buffer, bytes in a word of the FIFO are ordered from most
		 * significant byte to least
		 */
		if (ExtraByteCount == 1) {
			ExtraBytesBuffer[0] = (u8) (LastWord >> 24);
		}

		/* two extra bytes in the last word, put each byte into the next two
		 * locations of the buffer
		 */
		else if (ExtraByteCount == 2) {
			ExtraBytesBuffer[0] = (u8) (LastWord >> 24);
			ExtraBytesBuffer[1] = (u8) (LastWord >> 16);
		}
		/* three extra bytes in the last word, put each byte into the next three
		 * locations of the buffer
		 */
		else if (ExtraByteCount == 3) {
			ExtraBytesBuffer[0] = (u8) (LastWord >> 24);
			ExtraBytesBuffer[1] = (u8) (LastWord >> 16);
			ExtraBytesBuffer[2] = (u8) (LastWord >> 8);
		}
	}
	return XST_SUCCESS;
}

/*****************************************************************************/
XStatus
XPacketFifoV100b_Write(XPacketFifoV100b * InstancePtr,
		       u8 * BufferPtr, u32 ByteCount)
{
	u32 FifoCount;
	u32 WordCount;
	u32 ExtraByteCount;
	u32 *WordBuffer = (u32 *) BufferPtr;

	/* assert to verify valid input arguments including 32 bit alignment of
	 * the buffer pointer
	 */
	XASSERT_NONVOID(InstancePtr != NULL);
	XASSERT_NONVOID(BufferPtr != NULL);
	XASSERT_NONVOID(((u32) BufferPtr &
			 (XPF_FIFO_WIDTH_BYTE_COUNT - 1)) == 0);
	XASSERT_NONVOID(ByteCount != 0);
	XASSERT_NONVOID(InstancePtr->IsReady == XCOMPONENT_IS_READY);

	/* get the count of how many words may be inserted into the FIFO */

	FifoCount = XIo_In32(InstancePtr->RegBaseAddress +
			     XPF_COUNT_STATUS_REG_OFFSET) & XPF_COUNT_MASK;

	/* Calculate the number of 32 bit words required to insert the specified
	 * number of bytes in the FIFO and determine the number of extra bytes
	 * if the buffer length is not a multiple of 32 bit words
	 */

	WordCount = ByteCount / XPF_FIFO_WIDTH_BYTE_COUNT;
	ExtraByteCount = ByteCount % XPF_FIFO_WIDTH_BYTE_COUNT;

	/* take into account the extra bytes in the total word count */

	if (ExtraByteCount > 0) {
		WordCount++;
	}

	/* if there's not enough room in the FIFO to hold the specified
	 * number of bytes, then indicate an error,
	 */
	if (FifoCount < WordCount) {
		return XST_PFIFO_NO_ROOM;
	}

	/* readjust the word count to not take into account the extra bytes */

	if (ExtraByteCount > 0) {
		WordCount--;
	}

	/* Write all the bytes of the buffer which can be written as 32 bit
	 * words into the FIFO, waiting to handle the extra bytes seperately
	 */
	for (FifoCount = 0; FifoCount < WordCount; FifoCount++) {
		XIo_Out32(InstancePtr->DataBaseAddress, WordBuffer[FifoCount]);
	}

	/* if there are extra bytes to handle, extract them from the buffer
	 * and create a 32 bit word and write it to the FIFO
	 */
	if (ExtraByteCount > 0) {
		u32 LastWord = 0;
		u8 *ExtraBytesBuffer = (u8 *) (WordBuffer + WordCount);

		/* one extra byte in the buffer, put the byte into the last word
		 * to be inserted into the FIFO, perform this processing inline rather
		 * than in a loop to help performance
		 */
		if (ExtraByteCount == 1) {
			LastWord = ExtraBytesBuffer[0] << 24;
		}

		/* two extra bytes in the buffer, put each byte into the last word
		 * to be inserted into the FIFO
		 */
		else if (ExtraByteCount == 2) {
			LastWord = ExtraBytesBuffer[0] << 24 |
			    ExtraBytesBuffer[1] << 16;
		}

		/* three extra bytes in the buffer, put each byte into the last word
		 * to be inserted into the FIFO
		 */
		else if (ExtraByteCount == 3) {
			LastWord = ExtraBytesBuffer[0] << 24 |
			    ExtraBytesBuffer[1] << 16 |
			    ExtraBytesBuffer[2] << 8;
		}

		/* write the last 32 bit word to the FIFO and return with no errors */

		XIo_Out32(InstancePtr->DataBaseAddress, LastWord);
	}

	return XST_SUCCESS;
}
