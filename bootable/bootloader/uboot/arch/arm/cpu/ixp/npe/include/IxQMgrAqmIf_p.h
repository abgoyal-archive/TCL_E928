

#ifndef IXQMGRAQMIF_P_H
#define IXQMGRAQMIF_P_H

#include "IxOsalTypes.h"

 
#ifdef IX_OSAL_INLINE_ALL
#define IX_QMGR_AQMIF_INLINE IX_OSAL_INLINE_EXTERN
#else   
#ifdef IXQMGRAQMIF_C
#ifndef IX_QMGR_AQMIF_INLINE
#define IX_QMGR_AQMIF_INLINE
#endif
#else  
#ifndef IX_QMGR_AQMIF_INLINE
#define IX_QMGR_AQMIF_INLINE IX_OSAL_INLINE_EXTERN
#endif
#endif /* IXQMGRAQMIF_C */
#endif /* IX_OSAL_INLINE */


#include "IxQMgr.h"
#include "IxQMgrLog_p.h"
#include "IxQMgrQCfg_p.h"

#define IX_QMGR_AQMIF_SAVED_COMPONENT_NAME IX_COMPONENT_NAME
#undef  IX_COMPONENT_NAME
#define IX_COMPONENT_NAME ix_qmgr
#include "IxOsal.h" 


/* Number of bytes per word */
#define IX_QMGR_NUM_BYTES_PER_WORD 4

/* Underflow bit mask  */
#define IX_QMGR_UNDERFLOW_BIT_OFFSET    0x0

/* Overflow bit mask */
#define IX_QMGR_OVERFLOW_BIT_OFFSET     0x1

/* Queue access register, queue 0 */
#define IX_QMGR_QUEACC0_OFFSET      0x0000

/* Size of queue access register in words */
#define IX_QMGR_QUEACC_SIZE         0x4/*words*/

/* Queue status register, queues 0-7 */
#define IX_QMGR_QUELOWSTAT0_OFFSET  (IX_QMGR_QUEACC0_OFFSET +\
(IX_QMGR_MAX_NUM_QUEUES * IX_QMGR_QUEACC_SIZE * IX_QMGR_NUM_BYTES_PER_WORD))

/* Queue status register, queues 8-15 */
#define IX_QMGR_QUELOWSTAT1_OFFSET  (IX_QMGR_QUELOWSTAT0_OFFSET +\
                                     IX_QMGR_NUM_BYTES_PER_WORD)

/* Queue status register, queues 16-23 */
#define IX_QMGR_QUELOWSTAT2_OFFSET  (IX_QMGR_QUELOWSTAT1_OFFSET +\
                                     IX_QMGR_NUM_BYTES_PER_WORD)

/* Queue status register, queues 24-31 */
#define IX_QMGR_QUELOWSTAT3_OFFSET  (IX_QMGR_QUELOWSTAT2_OFFSET +\
                                     IX_QMGR_NUM_BYTES_PER_WORD)

/* Queue status register Q status bits mask */
#define IX_QMGR_QUELOWSTAT_QUE_STS_BITS_MASK 0xF

/* Size of queue 0-31 status register */
#define IX_QMGR_QUELOWSTAT_SIZE     0x4 /*words*/

/* The number of queues' status specified per word */
#define IX_QMGR_QUELOWSTAT_NUM_QUE_PER_WORD 0x8

/* Queue UF/OF status register queues 0-15  */
#define IX_QMGR_QUEUOSTAT0_OFFSET   (IX_QMGR_QUELOWSTAT3_OFFSET +\
                                     IX_QMGR_NUM_BYTES_PER_WORD)
/* Queue UF/OF status register queues 16-31 */
#define IX_QMGR_QUEUOSTAT1_OFFSET   (IX_QMGR_QUEUOSTAT0_OFFSET +\
                                     IX_QMGR_NUM_BYTES_PER_WORD)

/* The number of queues' underflow/overflow status specified per word */
#define IX_QMGR_QUEUOSTAT_NUM_QUE_PER_WORD 0x10

/* Queue NE status register, queues 32-63   */
#define IX_QMGR_QUEUPPSTAT0_OFFSET  (IX_QMGR_QUEUOSTAT1_OFFSET +\
                                     IX_QMGR_NUM_BYTES_PER_WORD)

/* Queue F status register, queues 32-63    */
#define IX_QMGR_QUEUPPSTAT1_OFFSET  (IX_QMGR_QUEUPPSTAT0_OFFSET +\
                                     IX_QMGR_NUM_BYTES_PER_WORD)

/* Size of queue 32-63 status register */
#define IX_QMGR_QUEUPPSTAT_SIZE     0x2 /*words*/

/* The number of queues' status specified per word */
#define IX_QMGR_QUEUPPSTAT_NUM_QUE_PER_WORD 0x20

/* Queue INT source select register, queues 0-7   */
#define IX_QMGR_INT0SRCSELREG0_OFFSET (IX_QMGR_QUEUPPSTAT1_OFFSET   +\
                                       IX_QMGR_NUM_BYTES_PER_WORD)

/* Queue INT source select register, queues 8-15  */
#define IX_QMGR_INT0SRCSELREG1_OFFSET (IX_QMGR_INT0SRCSELREG0_OFFSET+\
                                       IX_QMGR_NUM_BYTES_PER_WORD)

/* Queue INT source select register, queues 16-23 */
#define IX_QMGR_INT0SRCSELREG2_OFFSET (IX_QMGR_INT0SRCSELREG1_OFFSET+\
                                       IX_QMGR_NUM_BYTES_PER_WORD)

/* Queue INT source select register, queues 24-31 */
#define IX_QMGR_INT0SRCSELREG3_OFFSET (IX_QMGR_INT0SRCSELREG2_OFFSET+\
                                       IX_QMGR_NUM_BYTES_PER_WORD)

/* Size of interrupt source select reegister */
#define IX_QMGR_INT0SRCSELREG_SIZE  0x4 /*words*/

/* The number of queues' interrupt source select specified per word*/
#define IX_QMGR_INTSRC_NUM_QUE_PER_WORD 0x8

/* Queue INT enable register, queues 0-31  */
#define IX_QMGR_QUEIEREG0_OFFSET    (IX_QMGR_INT0SRCSELREG3_OFFSET +\
                                     IX_QMGR_NUM_BYTES_PER_WORD)

/* Queue INT enable register, queues 32-63 */
#define IX_QMGR_QUEIEREG1_OFFSET    (IX_QMGR_QUEIEREG0_OFFSET      +\
                                     IX_QMGR_NUM_BYTES_PER_WORD)

/* Queue INT register, queues 0-31  */
#define IX_QMGR_QINTREG0_OFFSET     (IX_QMGR_QUEIEREG1_OFFSET +\
                                     IX_QMGR_NUM_BYTES_PER_WORD)

/* Queue INT register, queues 32-63 */
#define IX_QMGR_QINTREG1_OFFSET     (IX_QMGR_QINTREG0_OFFSET  +\
                                     IX_QMGR_NUM_BYTES_PER_WORD)

/* Size of interrupt register */
#define IX_QMGR_QINTREG_SIZE        0x2 /*words*/

/* Number of queues' status specified per word */
#define IX_QMGR_QINTREG_NUM_QUE_PER_WORD 0x20

/* Number of bits per queue interrupt status */
#define IX_QMGR_QINTREG_BITS_PER_QUEUE 0x1
#define IX_QMGR_QINTREG_BIT_OFFSET 0x1

/* Size of address space not used by AQM */
#define IX_QMGR_AQM_UNUSED_ADDRESS_SPACE_SIZE_IN_BYTES  0x1bC0

/* Queue config register, queue 0 */
#define IX_QMGR_QUECONFIG_BASE_OFFSET (IX_QMGR_QINTREG1_OFFSET +\
                             IX_QMGR_NUM_BYTES_PER_WORD +\
                             IX_QMGR_AQM_UNUSED_ADDRESS_SPACE_SIZE_IN_BYTES)

/* Total size of configuration words */
#define IX_QMGR_QUECONFIG_SIZE      0x100

/* Start of SRAM queue buffer space */
#define IX_QMGR_QUEBUFFER_SPACE_OFFSET (IX_QMGR_QUECONFIG_BASE_OFFSET +\
                                 IX_QMGR_MAX_NUM_QUEUES * IX_QMGR_NUM_BYTES_PER_WORD)

/* Total bits in a word */
#define BITS_PER_WORD 32

/* Size of queue buffer space */
#define IX_QMGR_QUE_BUFFER_SPACE_SIZE 0x1F00

#define IX_QMGR_Q_ACCESS_ADDR_GET(qId)\
        (((qId) * (IX_QMGR_QUEACC_SIZE * IX_QMGR_NUM_BYTES_PER_WORD))\
	 + IX_QMGR_QUEACC0_OFFSET)

#define IX_QMGR_INT0SRCSELREG0_BIT3 3

extern UINT32 aqmBaseAddress;

void
ixQMgrAqmIfInit (void);

void
ixQMgrAqmIfUninit (void);

unsigned
ixQMgrAqmIfLog2 (unsigned number);

void
ixQMgrAqmIfQRegisterBitsWrite (IxQMgrQId qId, 
			       UINT32 registerBaseAddrOffset,
			       unsigned queuesPerRegWord,
			       UINT32 value);

void
ixQMgrAqmIfQStatusCheckValsCalc (IxQMgrQId qId,
				 IxQMgrSourceId srcSel,
				 unsigned int *statusWordOffset,
				 UINT32 *checkValue,
				 UINT32 *mask);
void
ixQMgrAqmIfBaseAddressSet (UINT32 address);

void
ixQMgrAqmIfBaseAddressGet (UINT32 *address);

void
ixQMgrAqmIfSramBaseAddressGet (UINT32 *address);

void
ixQMgrAqmIfQueStatRead (IxQMgrQId qId,
			IxQMgrQStatus* status);


void ixQMgrAqmIfIntSrcSelReg0Bit3Set (void);


void
ixQMgrAqmIfIntSrcSelWrite (IxQMgrQId qId,
			   IxQMgrSourceId sourceId);

void
ixQMgrAqmIfQInterruptEnable (IxQMgrQId qId);

void
ixQMgrAqmIfQInterruptDisable (IxQMgrQId qId);

void
ixQMgrAqmIfQueCfgWrite (IxQMgrQId qId,
			IxQMgrQSizeInWords qSizeInWords,
			IxQMgrQEntrySizeInWords entrySizeInWords,
			UINT32 freeSRAMAddress);

void
ixQMgrAqmIfQueCfgRead (IxQMgrQId qId,
		       unsigned int numEntries,
		       UINT32 *baseAddress,
		       unsigned int *ne,
		       unsigned int *nf,
		       UINT32 *readPtr,
		       UINT32 *writePtr);

void
ixQMgrAqmIfWatermarkSet (IxQMgrQId qId,
			 unsigned ne,
			 unsigned nf);

/* Inspect an entry without moving the read pointer */
IX_STATUS
ixQMgrAqmIfQPeek (IxQMgrQId qId,
		  unsigned int entryIndex,
		  unsigned int *entry);

/* Modify an entry without moving the write pointer */
IX_STATUS
ixQMgrAqmIfQPoke (IxQMgrQId qId,
		  unsigned int entryIndex,
		  unsigned int *entry);

IX_QMGR_AQMIF_INLINE void
ixQMgrAqmIfWordWrite (VUINT32 *address,
		      UINT32 word);

IX_QMGR_AQMIF_INLINE void
ixQMgrAqmIfWordRead (VUINT32 *address,
		     UINT32 *word);

IX_QMGR_AQMIF_INLINE void
ixQMgrAqmIfQPop (IxQMgrQId qId,
		 IxQMgrQEntrySizeInWords numWords,
		 UINT32 *entry);

IX_QMGR_AQMIF_INLINE void
ixQMgrAqmIfQPush (IxQMgrQId qId,
		  IxQMgrQEntrySizeInWords numWords,
		  UINT32 *entry);

IX_QMGR_AQMIF_INLINE void
ixQMgrAqmIfQStatusRegsRead (IxQMgrDispatchGroup group, 
			    UINT32 *qStatusWords);

IX_QMGR_AQMIF_INLINE BOOL
ixQMgrAqmIfQStatusCheck (UINT32 *oldQStatusWords,
			 UINT32 *newQStatusWords,
			 unsigned int statusWordOffset,			 
			 UINT32 checkValue,
			 UINT32 mask);

IX_QMGR_AQMIF_INLINE BOOL
ixQMgrAqmIfRegisterBitCheck (IxQMgrQId qId, 
			     UINT32 registerBaseAddrOffset,
			     unsigned queuesPerRegWord,
			     unsigned relativeBitOffset,
			     BOOL reset);

IX_QMGR_AQMIF_INLINE BOOL
ixQMgrAqmIfUnderflowCheck (IxQMgrQId qId);

IX_QMGR_AQMIF_INLINE BOOL
ixQMgrAqmIfOverflowCheck (IxQMgrQId qId);

IX_QMGR_AQMIF_INLINE UINT32
ixQMgrAqmIfQRegisterBitsRead (IxQMgrQId qId, 
			      UINT32 registerBaseAddrOffset,
			      unsigned queuesPerRegWord);
IX_QMGR_AQMIF_INLINE void
ixQMgrAqmIfQInterruptRegWrite (IxQMgrDispatchGroup group, 
			       UINT32 reg);
IX_QMGR_AQMIF_INLINE void
ixQMgrAqmIfQInterruptRegRead (IxQMgrDispatchGroup group, 
			      UINT32 *regVal);

IX_QMGR_AQMIF_INLINE void
ixQMgrAqmIfQueLowStatRead (IxQMgrQId qId,
			   IxQMgrQStatus *status);

IX_QMGR_AQMIF_INLINE void
ixQMgrAqmIfQueUppStatRead (IxQMgrQId qId,
			   IxQMgrQStatus *status);

IX_QMGR_AQMIF_INLINE void
ixQMgrAqmIfQueStatRead (IxQMgrQId qId, 
			IxQMgrQStatus *qStatus);

IX_QMGR_AQMIF_INLINE unsigned
ixQMgrAqmIfPow2NumDivide (unsigned numerator, 
			  unsigned denominator);

IX_QMGR_AQMIF_INLINE void
ixQMgrAqmIfQInterruptEnableRegRead (IxQMgrDispatchGroup group, 
			            UINT32 *regVal);

IX_QMGR_AQMIF_INLINE void
ixQMgrAqmIfWordWrite (VUINT32 *address,
		      UINT32 word)
{
    IX_OSAL_WRITE_LONG(address, word);
}

IX_QMGR_AQMIF_INLINE void
ixQMgrAqmIfWordRead (VUINT32 *address,
		     UINT32 *word)
{
    *word = IX_OSAL_READ_LONG(address);
}


IX_QMGR_AQMIF_INLINE void
ixQMgrAqmIfQPop (IxQMgrQId qId,
		 IxQMgrQEntrySizeInWords numWords,
		 UINT32 *entry)
{
    volatile UINT32 *accRegAddr;

    accRegAddr = (UINT32*)(aqmBaseAddress +
			   IX_QMGR_Q_ACCESS_ADDR_GET(qId));

    switch (numWords)
    {
	case IX_QMGR_Q_ENTRY_SIZE1:
	    ixQMgrAqmIfWordRead (accRegAddr, entry);
	    break;
	case IX_QMGR_Q_ENTRY_SIZE2:
	    ixQMgrAqmIfWordRead (accRegAddr++, entry++);
	    ixQMgrAqmIfWordRead (accRegAddr, entry);
	    break;
	case IX_QMGR_Q_ENTRY_SIZE4:
	    ixQMgrAqmIfWordRead (accRegAddr++, entry++);
	    ixQMgrAqmIfWordRead (accRegAddr++, entry++);
	    ixQMgrAqmIfWordRead (accRegAddr++, entry++);
	    ixQMgrAqmIfWordRead (accRegAddr, entry);
	    break;
	default:
	    IX_QMGR_LOG_ERROR0("Invalid Q Entry size passed to ixQMgrAqmIfQPop");
	    break;
    }
}

IX_QMGR_AQMIF_INLINE void
ixQMgrAqmIfQPush (IxQMgrQId qId,
		  IxQMgrQEntrySizeInWords numWords,
		  UINT32 *entry)
{
    volatile UINT32 *accRegAddr;

    accRegAddr = (UINT32*)(aqmBaseAddress +
			   IX_QMGR_Q_ACCESS_ADDR_GET(qId));
    
    switch (numWords)
    {
	case IX_QMGR_Q_ENTRY_SIZE1:
	    ixQMgrAqmIfWordWrite (accRegAddr, *entry);
	    break;
	case IX_QMGR_Q_ENTRY_SIZE2:
	    ixQMgrAqmIfWordWrite (accRegAddr++, *entry++);
	    ixQMgrAqmIfWordWrite (accRegAddr, *entry);
	    break;
	case IX_QMGR_Q_ENTRY_SIZE4:
	    ixQMgrAqmIfWordWrite (accRegAddr++, *entry++);
	    ixQMgrAqmIfWordWrite (accRegAddr++, *entry++);
	    ixQMgrAqmIfWordWrite (accRegAddr++, *entry++);
	    ixQMgrAqmIfWordWrite (accRegAddr, *entry);
	    break;
	default:
	    IX_QMGR_LOG_ERROR0("Invalid Q Entry size passed to ixQMgrAqmIfQPush");
	    break;
    }
}

IX_QMGR_AQMIF_INLINE void
ixQMgrAqmIfQStatusRegsRead (IxQMgrDispatchGroup group, 
			    UINT32 *qStatusWords)
{
    volatile UINT32 *regAddress = NULL;

    if (group == IX_QMGR_QUELOW_GROUP)
    {
	regAddress = (UINT32*)(aqmBaseAddress +
			       IX_QMGR_QUELOWSTAT0_OFFSET);

	ixQMgrAqmIfWordRead (regAddress++, qStatusWords++);
	ixQMgrAqmIfWordRead (regAddress++, qStatusWords++);
	ixQMgrAqmIfWordRead (regAddress++, qStatusWords++);
	ixQMgrAqmIfWordRead (regAddress, qStatusWords);
    }
    else /* We have the upper queues */
    {
       /* Only need to read the Nearly Empty status register for
	* queues 32-63 as for therse queues the interrtupt source
	* condition is fixed to Nearly Empty
	*/
	regAddress = (UINT32*)(aqmBaseAddress +
			       IX_QMGR_QUEUPPSTAT0_OFFSET);
	ixQMgrAqmIfWordRead (regAddress, qStatusWords);
    }
}


IX_QMGR_AQMIF_INLINE BOOL
ixQMgrAqmIfQStatusCheck (UINT32 *oldQStatusWords,
			 UINT32 *newQStatusWords,
			 unsigned int statusWordOffset,			 
			 UINT32 checkValue,
			 UINT32 mask)
{
    if (((oldQStatusWords[statusWordOffset] & mask) != 
	 (newQStatusWords[statusWordOffset] & mask)) &&
	((newQStatusWords[statusWordOffset] & mask) == checkValue))
    {
	return TRUE;
    }

    return FALSE;
}

IX_QMGR_AQMIF_INLINE void
ixQMgrAqmIfQInterruptRegRead (IxQMgrDispatchGroup group, 
			      UINT32 *regVal)
{
    volatile UINT32 *regAddress;

    if (group == IX_QMGR_QUELOW_GROUP)
    {
	regAddress = (UINT32*)(aqmBaseAddress +
			       IX_QMGR_QINTREG0_OFFSET);
    }
    else
    {
	regAddress = (UINT32*)(aqmBaseAddress +
			       IX_QMGR_QINTREG1_OFFSET);
    }

    ixQMgrAqmIfWordRead (regAddress, regVal);
}

IX_QMGR_AQMIF_INLINE void
ixQMgrAqmIfQInterruptEnableRegRead (IxQMgrDispatchGroup group, 
			            UINT32 *regVal)
{
    volatile UINT32 *regAddress;

    if (group == IX_QMGR_QUELOW_GROUP)
    {
	regAddress = (UINT32*)(aqmBaseAddress +
			       IX_QMGR_QUEIEREG0_OFFSET);
    }
    else
    {
	regAddress = (UINT32*)(aqmBaseAddress +
			       IX_QMGR_QUEIEREG1_OFFSET);
    }

    ixQMgrAqmIfWordRead (regAddress, regVal);
}


IX_QMGR_AQMIF_INLINE BOOL
ixQMgrAqmIfRegisterBitCheck (IxQMgrQId qId, 
			     UINT32 registerBaseAddrOffset,
			     unsigned queuesPerRegWord,
			     unsigned relativeBitOffset,
			     BOOL reset)
{
    UINT32 actualBitOffset;
    volatile UINT32 *registerAddress;
    UINT32 registerWord;

    /*
     * Calculate the registerAddress
     * multiple queues split accross registers
     */
    registerAddress = (UINT32*)(aqmBaseAddress +
				registerBaseAddrOffset +
				((qId / queuesPerRegWord) *
				 IX_QMGR_NUM_BYTES_PER_WORD));

    /*
     * Get the status word
     */
    ixQMgrAqmIfWordRead (registerAddress, &registerWord);
    
    /*
     * Calculate the actualBitOffset
     * status for multiple queues stored in one register
     */
    actualBitOffset = (relativeBitOffset + 1) <<
	((qId & (queuesPerRegWord - 1)) * (BITS_PER_WORD / queuesPerRegWord));

    /* Check if the status bit is set */
    if (registerWord & actualBitOffset)
    {
	/* Clear the bit if reset */
	if (reset)
	{
	    ixQMgrAqmIfWordWrite (registerAddress, registerWord & (~actualBitOffset));
	}
	return TRUE;
    }

    /* Bit not set */
    return FALSE;
}


IX_QMGR_AQMIF_INLINE BOOL
ixQMgrAqmIfUnderflowCheck (IxQMgrQId qId)
{
    if (qId < IX_QMGR_MIN_QUEUPP_QID)
    {
	return (ixQMgrAqmIfRegisterBitCheck (qId,
					     IX_QMGR_QUEUOSTAT0_OFFSET,
					     IX_QMGR_QUEUOSTAT_NUM_QUE_PER_WORD,
					     IX_QMGR_UNDERFLOW_BIT_OFFSET,
					     TRUE/*reset*/));
    }
    else
    {
	/* Qs 32-63 have no underflow status */
	return FALSE;
    }
}

IX_QMGR_AQMIF_INLINE BOOL
ixQMgrAqmIfOverflowCheck (IxQMgrQId qId)
{
    if (qId < IX_QMGR_MIN_QUEUPP_QID)
    {
	return (ixQMgrAqmIfRegisterBitCheck (qId,
					     IX_QMGR_QUEUOSTAT0_OFFSET,
					     IX_QMGR_QUEUOSTAT_NUM_QUE_PER_WORD,
					     IX_QMGR_OVERFLOW_BIT_OFFSET,
					     TRUE/*reset*/));
    }
    else
    {
	/* Qs 32-63 have no overflow status */
	return FALSE;
    }
}

IX_QMGR_AQMIF_INLINE UINT32
ixQMgrAqmIfQRegisterBitsRead (IxQMgrQId qId, 
			      UINT32 registerBaseAddrOffset,
			      unsigned queuesPerRegWord)
{
    volatile UINT32 *registerAddress;
    UINT32 registerWord;
    UINT32 statusBitsMask;
    UINT32 bitsPerQueue;

    bitsPerQueue = BITS_PER_WORD / queuesPerRegWord;

    /*
     * Calculate the registerAddress
     * multiple queues split accross registers
     */
    registerAddress = (UINT32*)(aqmBaseAddress +
				registerBaseAddrOffset +
				((qId / queuesPerRegWord) *
				 IX_QMGR_NUM_BYTES_PER_WORD));
    /*
     * Read the status word
     */
    ixQMgrAqmIfWordRead (registerAddress, &registerWord);
    

    /*
     * Calculate the mask for the status bits for this queue.
     */
    statusBitsMask = ((1 << bitsPerQueue) - 1);

    /*
     * Shift the status word so it is right justified
     */    
    registerWord >>= ((qId & (queuesPerRegWord - 1)) * bitsPerQueue);

    /*
     * Mask out all bar the status bits for this queue
     */
    return (registerWord &= statusBitsMask);
}

IX_QMGR_AQMIF_INLINE void
ixQMgrAqmIfQInterruptRegWrite (IxQMgrDispatchGroup group, 
			       UINT32 reg)
{
    volatile UINT32 *address;

    if (group == IX_QMGR_QUELOW_GROUP)
    {
	address = (UINT32*)(aqmBaseAddress +
			    IX_QMGR_QINTREG0_OFFSET);
    }
    else
    {
	address = (UINT32*)(aqmBaseAddress +
			    IX_QMGR_QINTREG1_OFFSET);
    }

    ixQMgrAqmIfWordWrite (address, reg);
}

IX_QMGR_AQMIF_INLINE void
ixQMgrAqmIfQueLowStatRead (IxQMgrQId qId,
			   IxQMgrQStatus *status)
{
    /* Read the general status bits */
    *status = ixQMgrAqmIfQRegisterBitsRead (qId,
					    IX_QMGR_QUELOWSTAT0_OFFSET,
					    IX_QMGR_QUELOWSTAT_NUM_QUE_PER_WORD);
}

IX_QMGR_AQMIF_INLINE void
ixQMgrAqmIfQueUppStatRead (IxQMgrQId qId,
			   IxQMgrQStatus *status)
{
    /* Reset the status bits */
    *status = 0;

    /* 
     * Check if the queue is nearly empty,
     * N.b. QUPP stat register contains status for regs 32-63 at each
     *      bit position so subtract 32 to get bit offset
     */
    if (ixQMgrAqmIfRegisterBitCheck ((qId - IX_QMGR_MIN_QUEUPP_QID),
				     IX_QMGR_QUEUPPSTAT0_OFFSET,
				     IX_QMGR_QUEUPPSTAT_NUM_QUE_PER_WORD,
				     0/*relativeBitOffset*/,
				     FALSE/*!reset*/))
    {
	*status |= IX_QMGR_Q_STATUS_NE_BIT_MASK;
    }

    /* 
     * Check if the queue is full,
     * N.b. QUPP stat register contains status for regs 32-63 at each
     *      bit position so subtract 32 to get bit offset
     */
    if (ixQMgrAqmIfRegisterBitCheck ((qId - IX_QMGR_MIN_QUEUPP_QID),
				     IX_QMGR_QUEUPPSTAT1_OFFSET,
				     IX_QMGR_QUEUPPSTAT_NUM_QUE_PER_WORD,
				     0/*relativeBitOffset*/,
				     FALSE/*!reset*/))
    {
	*status |= IX_QMGR_Q_STATUS_F_BIT_MASK;
    }
}

IX_QMGR_AQMIF_INLINE void
ixQMgrAqmIfQueStatRead (IxQMgrQId qId, 
			IxQMgrQStatus *qStatus)
{
    if (qId < IX_QMGR_MIN_QUEUPP_QID)
    {
	ixQMgrAqmIfQueLowStatRead (qId, qStatus);
    }
    else
    {
	ixQMgrAqmIfQueUppStatRead (qId, qStatus);
    }
}


IX_QMGR_AQMIF_INLINE unsigned
ixQMgrAqmIfPow2NumDivide (unsigned numerator, 
			  unsigned denominator)
{
    /* Number is evenly divisable by 2 */
    return (numerator >> ixQMgrAqmIfLog2 (denominator));
}

/* Restore IX_COMPONENT_NAME */
#undef IX_COMPONENT_NAME
#define IX_COMPONENT_NAME IX_QMGR_AQMIF_SAVED_COMPONENT_NAME

#endif/*IXQMGRAQMIF_P_H*/
