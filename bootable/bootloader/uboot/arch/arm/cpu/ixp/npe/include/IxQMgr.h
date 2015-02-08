


#ifndef IXQMGR_H
#define IXQMGR_H


#include "IxOsal.h"

#if defined (__BIG_ENDIAN)

#define IX_QMGR_INLINE_READ_LONG IX_OSAL_READ_LONG_BE
#define IX_QMGR_INLINE_WRITE_LONG IX_OSAL_WRITE_LONG_BE

#else

#define IX_QMGR_INLINE_READ_LONG IX_OSAL_READ_LONG_LE_DC
#define IX_QMGR_INLINE_WRITE_LONG IX_OSAL_WRITE_LONG_LE_DC

#endif



#ifndef __wince

#ifdef IXQMGRQACCESS_C
#    ifdef NO_INLINE_APIS
#        undef NO_INLINE_APIS
#    endif
#    define IX_QMGR_INLINE  /* Empty Define */
#else
#    ifndef NO_INLINE_APIS
#       define IX_QMGR_INLINE IX_OSAL_INLINE_EXTERN
#    else
#       define IX_QMGR_INLINE /* Empty Define */
#    endif
#endif

#else /* ndef __wince */

#    ifndef NO_INLINE_APIS
#       define NO_INLINE_APIS
#    endif
#    define IX_QMGR_INLINE

#endif


#define IX_QMGR_MAX_NUM_QUEUES  64

#define IX_QMGR_MIN_QID IX_QMGR_QUEUE_0

#define IX_QMGR_MAX_QID IX_QMGR_QUEUE_63

#define IX_QMGR_MIN_QUEUPP_QID 32

#define IX_QMGR_MAX_QNAME_LEN 16

#define IX_QMGR_WARNING 2

#define IX_QMGR_PARAMETER_ERROR 3

#define IX_QMGR_INVALID_Q_ENTRY_SIZE 4

#define IX_QMGR_INVALID_Q_ID 5

#define IX_QMGR_INVALID_CB_ID 6

#define IX_QMGR_CB_ALREADY_SET 7

#define IX_QMGR_NO_AVAILABLE_SRAM 8

#define IX_QMGR_INVALID_INT_SOURCE_ID 9

#define IX_QMGR_INVALID_QSIZE 10

#define IX_QMGR_INVALID_Q_WM 11

#define IX_QMGR_Q_NOT_CONFIGURED 12

#define IX_QMGR_Q_ALREADY_CONFIGURED 13

#define IX_QMGR_Q_UNDERFLOW 14

#define IX_QMGR_Q_OVERFLOW 15

#define IX_QMGR_Q_INVALID_PRIORITY 16

#define IX_QMGR_ENTRY_INDEX_OUT_OF_BOUNDS 17

#define ixQMgrDispatcherLoopRun ixQMgrDispatcherLoopRunA0


#define IX_QMGR_QUEUE_0 (0)      /**< Queue Number 0 */
#define IX_QMGR_QUEUE_1 (1)      /**< Queue Number 1 */
#define IX_QMGR_QUEUE_2 (2)      /**< Queue Number 2 */
#define IX_QMGR_QUEUE_3 (3)      /**< Queue Number 3 */
#define IX_QMGR_QUEUE_4 (4)      /**< Queue Number 4 */
#define IX_QMGR_QUEUE_5 (5)      /**< Queue Number 5 */
#define IX_QMGR_QUEUE_6 (6)      /**< Queue Number 6 */
#define IX_QMGR_QUEUE_7 (7)      /**< Queue Number 7 */
#define IX_QMGR_QUEUE_8 (8)      /**< Queue Number 8 */
#define IX_QMGR_QUEUE_9 (9)      /**< Queue Number 9 */
#define IX_QMGR_QUEUE_10 (10)    /**< Queue Number 10 */
#define IX_QMGR_QUEUE_11 (11)    /**< Queue Number 11 */
#define IX_QMGR_QUEUE_12 (12)    /**< Queue Number 12 */
#define IX_QMGR_QUEUE_13 (13)    /**< Queue Number 13 */
#define IX_QMGR_QUEUE_14 (14)    /**< Queue Number 14 */
#define IX_QMGR_QUEUE_15 (15)    /**< Queue Number 15 */
#define IX_QMGR_QUEUE_16 (16)    /**< Queue Number 16 */
#define IX_QMGR_QUEUE_17 (17)    /**< Queue Number 17 */
#define IX_QMGR_QUEUE_18 (18)    /**< Queue Number 18 */
#define IX_QMGR_QUEUE_19 (19)    /**< Queue Number 19 */
#define IX_QMGR_QUEUE_20 (20)    /**< Queue Number 20 */
#define IX_QMGR_QUEUE_21 (21)    /**< Queue Number 21 */
#define IX_QMGR_QUEUE_22 (22)    /**< Queue Number 22 */
#define IX_QMGR_QUEUE_23 (23)    /**< Queue Number 23 */
#define IX_QMGR_QUEUE_24 (24)    /**< Queue Number 24 */
#define IX_QMGR_QUEUE_25 (25)    /**< Queue Number 25 */
#define IX_QMGR_QUEUE_26 (26)    /**< Queue Number 26 */
#define IX_QMGR_QUEUE_27 (27)    /**< Queue Number 27 */
#define IX_QMGR_QUEUE_28 (28)    /**< Queue Number 28 */
#define IX_QMGR_QUEUE_29 (29)    /**< Queue Number 29 */
#define IX_QMGR_QUEUE_30 (30)    /**< Queue Number 30 */
#define IX_QMGR_QUEUE_31 (31)    /**< Queue Number 31 */
#define IX_QMGR_QUEUE_32 (32)    /**< Queue Number 32 */
#define IX_QMGR_QUEUE_33 (33)    /**< Queue Number 33 */
#define IX_QMGR_QUEUE_34 (34)    /**< Queue Number 34 */
#define IX_QMGR_QUEUE_35 (35)    /**< Queue Number 35 */
#define IX_QMGR_QUEUE_36 (36)    /**< Queue Number 36 */
#define IX_QMGR_QUEUE_37 (37)    /**< Queue Number 37 */
#define IX_QMGR_QUEUE_38 (38)    /**< Queue Number 38 */
#define IX_QMGR_QUEUE_39 (39)    /**< Queue Number 39 */
#define IX_QMGR_QUEUE_40 (40)    /**< Queue Number 40 */
#define IX_QMGR_QUEUE_41 (41)    /**< Queue Number 41 */
#define IX_QMGR_QUEUE_42 (42)    /**< Queue Number 42 */
#define IX_QMGR_QUEUE_43 (43)    /**< Queue Number 43 */
#define IX_QMGR_QUEUE_44 (44)    /**< Queue Number 44 */
#define IX_QMGR_QUEUE_45 (45)    /**< Queue Number 45 */
#define IX_QMGR_QUEUE_46 (46)    /**< Queue Number 46 */
#define IX_QMGR_QUEUE_47 (47)    /**< Queue Number 47 */
#define IX_QMGR_QUEUE_48 (48)    /**< Queue Number 48 */
#define IX_QMGR_QUEUE_49 (49)    /**< Queue Number 49 */
#define IX_QMGR_QUEUE_50 (50)    /**< Queue Number 50 */
#define IX_QMGR_QUEUE_51 (51)    /**< Queue Number 51 */
#define IX_QMGR_QUEUE_52 (52)    /**< Queue Number 52 */
#define IX_QMGR_QUEUE_53 (53)    /**< Queue Number 53 */
#define IX_QMGR_QUEUE_54 (54)    /**< Queue Number 54 */
#define IX_QMGR_QUEUE_55 (55)    /**< Queue Number 55 */
#define IX_QMGR_QUEUE_56 (56)    /**< Queue Number 56 */
#define IX_QMGR_QUEUE_57 (57)    /**< Queue Number 57 */
#define IX_QMGR_QUEUE_58 (58)    /**< Queue Number 58 */
#define IX_QMGR_QUEUE_59 (59)    /**< Queue Number 59 */
#define IX_QMGR_QUEUE_60 (60)    /**< Queue Number 60 */
#define IX_QMGR_QUEUE_61 (61)    /**< Queue Number 61 */
#define IX_QMGR_QUEUE_62 (62)    /**< Queue Number 62 */
#define IX_QMGR_QUEUE_63 (63)    /**< Queue Number 63 */
#define IX_QMGR_QUEUE_INVALID (64)     /**< AQM Queue Number Delimiter */



typedef int IxQMgrQId;

typedef UINT32 IxQMgrQStatus;

typedef enum
{
    IX_QMGR_Q_STATUS_E_BIT_MASK  = 0x1,
    IX_QMGR_Q_STATUS_NE_BIT_MASK = 0x2,
    IX_QMGR_Q_STATUS_NF_BIT_MASK = 0x4,
    IX_QMGR_Q_STATUS_F_BIT_MASK  = 0x8,
    IX_QMGR_Q_STATUS_UF_BIT_MASK = 0x10,
    IX_QMGR_Q_STATUS_OF_BIT_MASK = 0x20
} IxQMgrQStatusMask;

typedef enum
{
    IX_QMGR_Q_SOURCE_ID_E = 0,  /**< Queue Empty due to last read             */
    IX_QMGR_Q_SOURCE_ID_NE,     /**< Queue Nearly Empty due to last read      */
    IX_QMGR_Q_SOURCE_ID_NF,     /**< Queue Nearly Full due to last write      */
    IX_QMGR_Q_SOURCE_ID_F,      /**< Queue Full due to last write             */
    IX_QMGR_Q_SOURCE_ID_NOT_E,  /**< Queue Not Empty due to last write        */
    IX_QMGR_Q_SOURCE_ID_NOT_NE, /**< Queue Not Nearly Empty due to last write */
    IX_QMGR_Q_SOURCE_ID_NOT_NF, /**< Queue Not Nearly Full due to last read   */
    IX_QMGR_Q_SOURCE_ID_NOT_F   /**< Queue Not Full due to last read          */
} IxQMgrSourceId;

typedef enum
{
    IX_QMGR_Q_ENTRY_SIZE1 = 1,   /**< 1 word entry       */
    IX_QMGR_Q_ENTRY_SIZE2 = 2,   /**< 2 word entry       */
    IX_QMGR_Q_ENTRY_SIZE4 = 4    /**< 4 word entry       */
} IxQMgrQEntrySizeInWords;

typedef enum
{
    IX_QMGR_Q_SIZE16 = 16,   /**< 16 word buffer     */
    IX_QMGR_Q_SIZE32 = 32,   /**< 32 word buffer     */
    IX_QMGR_Q_SIZE64 = 64,   /**< 64 word buffer     */
    IX_QMGR_Q_SIZE128 = 128, /**< 128 word buffer    */
    IX_QMGR_Q_SIZE_INVALID = 129  /**< Insure that this is greater than largest
				    * queue size supported by the hardware
				    */
} IxQMgrQSizeInWords;

typedef enum
{
    IX_QMGR_Q_WM_LEVEL0 = 0,    /**< 0 entry watermark  */
    IX_QMGR_Q_WM_LEVEL1 = 1,    /**< 1 entry watermark  */
    IX_QMGR_Q_WM_LEVEL2 = 2,    /**< 2 entry watermark  */
    IX_QMGR_Q_WM_LEVEL4 = 4,    /**< 4 entry watermark  */
    IX_QMGR_Q_WM_LEVEL8 = 8,    /**< 8 entry watermark  */
    IX_QMGR_Q_WM_LEVEL16 = 16,  /**< 16 entry watermark */
    IX_QMGR_Q_WM_LEVEL32 = 32,  /**< 32 entry watermark */
    IX_QMGR_Q_WM_LEVEL64 = 64   /**< 64 entry watermark */
} IxQMgrWMLevel;

typedef enum
{
    IX_QMGR_QUELOW_GROUP = 0, /**< Queues 0-31  */
    IX_QMGR_QUEUPP_GROUP      /**< Queues 32-63 */
} IxQMgrDispatchGroup;

typedef enum
{
  IX_QMGR_Q_PRIORITY_0 = 0,  /**< Priority level 0 */
  IX_QMGR_Q_PRIORITY_1,      /**< Priority level 1 */
  IX_QMGR_Q_PRIORITY_2,      /**< Priority level 2 */
  IX_QMGR_Q_PRIORITY_INVALID /**< Invalid Priority level */
} IxQMgrPriority;


typedef enum
{
  IX_QMGR_TYPE_REALTIME_OTHER = 0, /**< Real time callbacks-always allowed run*/
  IX_QMGR_TYPE_REALTIME_PERIODIC,  /**< Periodic callbacks-always allowed run */
  IX_QMGR_TYPE_REALTIME_SPORADIC   /**< Sporadic callbacks-only run if no
                                        periodic callbacks are in progress    */
} IxQMgrType;


typedef unsigned IxQMgrCallbackId;

typedef void (*IxQMgrCallback)(IxQMgrQId qId,
                               IxQMgrCallbackId cbId);

typedef void (*IxQMgrDispatcherFuncPtr)(IxQMgrDispatchGroup group);



PUBLIC IX_STATUS
ixQMgrInit (void);

PUBLIC IX_STATUS
ixQMgrUnload (void);

PUBLIC void
ixQMgrShow (void);

PUBLIC IX_STATUS
ixQMgrQShow (IxQMgrQId qId);



PUBLIC IX_STATUS
ixQMgrQConfig (char *qName,
	       IxQMgrQId qId,
	       IxQMgrQSizeInWords qSizeInWords,
	       IxQMgrQEntrySizeInWords qEntrySizeInWords);

PUBLIC IX_STATUS
ixQMgrQSizeInEntriesGet (IxQMgrQId qId,
			 unsigned *qSizeInEntries);

PUBLIC IX_STATUS
ixQMgrWatermarkSet (IxQMgrQId qId,
		    IxQMgrWMLevel ne,
		    IxQMgrWMLevel nf);

PUBLIC IX_STATUS
ixQMgrAvailableSramAddressGet (UINT32 *address,
			       unsigned *sizeOfFreeSram);



PUBLIC IX_STATUS
ixQMgrQReadWithChecks (IxQMgrQId qId,
                       UINT32 *entry);



typedef struct
{
    /* fields related to write functions */
    UINT32 qOflowStatBitMask;         /**< overflow status mask */
    UINT32 qWriteCount;               /**< queue write count */

    /* fields related to read and write functions */
    volatile UINT32 *qAccRegAddr;     /**< access register */
    volatile UINT32 *qUOStatRegAddr;  /**< status register */
    volatile UINT32 *qConfigRegAddr;  /**< config register */
    UINT32 qEntrySizeInWords;         /**< queue entry size in words */
    UINT32 qSizeInEntries;            /**< queue size in entries */

    /* fields related to read functions */
    UINT32 qUflowStatBitMask;         /**< underflow status mask */
    UINT32 qReadCount;                /**< queue read count */
} IxQMgrQInlinedReadWriteInfo;


PUBLIC IX_STATUS
ixQMgrQReadMWordsMinus1 (IxQMgrQId qId,
			 UINT32 *entry);



#ifdef NO_INLINE_APIS
PUBLIC IX_STATUS
ixQMgrQRead (IxQMgrQId qId,
             UINT32 *entryPtr);
#else 
extern IxQMgrQInlinedReadWriteInfo ixQMgrQInlinedReadWriteInfo[];
extern IX_STATUS ixQMgrQReadMWordsMinus1 (IxQMgrQId qId, UINT32 *entryPtr);

IX_QMGR_INLINE PUBLIC IX_STATUS
ixQMgrQRead (IxQMgrQId qId,
             UINT32 *entryPtr);
#endif

IX_QMGR_INLINE PUBLIC IX_STATUS
ixQMgrQRead (IxQMgrQId qId,
	     UINT32 *entryPtr)
#ifdef NO_INLINE_APIS
    ;
#else
{
    IxQMgrQInlinedReadWriteInfo *infoPtr = &ixQMgrQInlinedReadWriteInfo[qId];
    UINT32 entry, entrySize;

    /* get a new entry */
    entrySize = infoPtr->qEntrySizeInWords;
    entry = IX_QMGR_INLINE_READ_LONG(infoPtr->qAccRegAddr);

    if (entrySize != IX_QMGR_Q_ENTRY_SIZE1)
    {	
	*entryPtr = entry;
	/* process the remaining part of the entry */
	return ixQMgrQReadMWordsMinus1(qId, entryPtr);
    }

    /* underflow is available for lower queues only */
    if (qId < IX_QMGR_MIN_QUEUPP_QID)
    {
	/* the counter of queue entries is decremented. In happy 
	 * day scenario there are many entries in the queue
	 * and the counter does not reach zero.
	 */
	if (infoPtr->qReadCount-- == 0)
	{
	    /* There is maybe no entry in the queue
	     * qReadCount is now negative, but will be corrected before
	     * the function returns.
	     */
	    UINT32 qPtrs; /* queue internal pointers */

	    /* when a queue is empty, the hw guarantees to return 
	     * a null value. If the value is not null, the queue is
	     * not empty.
	     */
	    if (entry == 0)
	    {
		/* get the queue status */
		UINT32 status = IX_QMGR_INLINE_READ_LONG(infoPtr->qUOStatRegAddr);
	
		/* check the underflow status */
		if (status & infoPtr->qUflowStatBitMask)
		{
		    /* the queue is empty 
		    *  clear the underflow status bit if it was set 
		    */
		    IX_QMGR_INLINE_WRITE_LONG(infoPtr->qUOStatRegAddr,
					 status & ~infoPtr->qUflowStatBitMask);
		    *entryPtr = 0;
		    infoPtr->qReadCount = 0;
		    return IX_QMGR_Q_UNDERFLOW;
		}
	    }
	    /* store the result */
	    *entryPtr = entry;

	    /* No underflow occured : someone is filling the queue
	     * or the queue contains null entries.
	     * The current counter needs to be
	     * updated from the current number of entries in the queue
	     */

	    /* get snapshot of queue pointers */
	    qPtrs = IX_QMGR_INLINE_READ_LONG(infoPtr->qConfigRegAddr);

	    /* Mod subtraction of pointers to get number of words in Q. */
	    qPtrs = (qPtrs - (qPtrs >> 7)) & 0x7f; 
  
	    if (qPtrs == 0)
	    {
		/* no entry in the queue */
		infoPtr->qReadCount = 0;
	    }
	    else
	    {
		/* convert the number of words inside the queue
		 * to a number of entries 
		 */
		infoPtr->qReadCount = qPtrs & (infoPtr->qSizeInEntries - 1);
	    }
	    return IX_SUCCESS;
	}
    }
    *entryPtr = entry;
    return IX_SUCCESS;
}
#endif

#ifdef NO_INLINE_APIS  
PUBLIC IX_STATUS
ixQMgrQBurstRead (IxQMgrQId qId,
                  UINT32 numEntries,
                  UINT32 *entries);
#else
IX_QMGR_INLINE PUBLIC IX_STATUS
ixQMgrQBurstRead (IxQMgrQId qId,
                  UINT32 numEntries,
                  UINT32 *entries);
#endif  /* endif NO_INLINE_APIS */

IX_QMGR_INLINE PUBLIC IX_STATUS
ixQMgrQBurstRead (IxQMgrQId qId,
		  UINT32 numEntries,
		  UINT32 *entries)
#ifdef NO_INLINE_APIS
;
#else
{
    IxQMgrQInlinedReadWriteInfo *infoPtr = &ixQMgrQInlinedReadWriteInfo[qId];
    UINT32 nullCheckEntry;

    if (infoPtr->qEntrySizeInWords == IX_QMGR_Q_ENTRY_SIZE1)
    {
	volatile UINT32 *qAccRegAddr = infoPtr->qAccRegAddr;

	/* the code is optimized to take care of data dependencies:
	 * Durig a read, there are a few cycles needed to get the 
	 * read complete. During these cycles, it is poossible to
	 * do some CPU, e.g. increment pointers and decrement 
	 * counters.
	 */

	/* fetch a queue entry */
	nullCheckEntry = IX_QMGR_INLINE_READ_LONG(infoPtr->qAccRegAddr);

	/* iterate the specified number of queue entries */ 
	while (--numEntries)
	{
	    /* check the result of the previous read */
	    if (nullCheckEntry == 0)
	    {
		/* if we read a NULL entry, stop. We have underflowed */
		break;
	    }
	    else
	    {
		/* write the entry */
		*entries = nullCheckEntry;
		/* fetch next entry */
		nullCheckEntry = IX_QMGR_INLINE_READ_LONG(qAccRegAddr);
		/* increment the write address */
		entries++;
	    }
	}
	/* write the pre-fetched entry */
	*entries = nullCheckEntry;
    }
    else
    {
	IxQMgrQEntrySizeInWords entrySizeInWords = infoPtr->qEntrySizeInWords;
	/* read the specified number of queue entries */
	nullCheckEntry = 0;
	while (numEntries--)
	{
	    UINT32 i;

	    for (i = 0; i < (UINT32)entrySizeInWords; i++)
	    {
		*entries = IX_QMGR_INLINE_READ_LONG(infoPtr->qAccRegAddr + i);
		nullCheckEntry |= *entries++;
	    }

	    /* if we read a NULL entry, stop. We have underflowed */
	    if (nullCheckEntry == 0)
	    {
		break;
	    }
	    nullCheckEntry = 0;
	}
    }

    /* reset the current read count : next access to the read function 
     * will force a underflow status check 
     */
    infoPtr->qReadCount = 0;

    /* Check if underflow occurred on the read */
    if (nullCheckEntry == 0 && qId < IX_QMGR_MIN_QUEUPP_QID)
    {
	/* get the queue status */
	UINT32 status = IX_QMGR_INLINE_READ_LONG(infoPtr->qUOStatRegAddr);

	if (status & infoPtr->qUflowStatBitMask)
	{
	    /* clear the underflow status bit if it was set */
	    IX_QMGR_INLINE_WRITE_LONG(infoPtr->qUOStatRegAddr,
				 status & ~infoPtr->qUflowStatBitMask);
	    return IX_QMGR_Q_UNDERFLOW;
	}
    }

    return IX_SUCCESS;
}
#endif

PUBLIC IX_STATUS
ixQMgrQPeek (IxQMgrQId qId,
	     unsigned int entryIndex,
	     UINT32 *entry);

PUBLIC IX_STATUS
ixQMgrQWriteWithChecks (IxQMgrQId qId,
                        UINT32 *entry);

#ifdef NO_INLINE_APIS
PUBLIC IX_STATUS
ixQMgrQWrite (IxQMgrQId qId,
	      UINT32 *entry);
#else
IX_QMGR_INLINE PUBLIC IX_STATUS
ixQMgrQWrite (IxQMgrQId qId,
	      UINT32 *entry);
#endif /* NO_INLINE_APIS */

IX_QMGR_INLINE PUBLIC IX_STATUS
ixQMgrQWrite (IxQMgrQId qId,
	      UINT32 *entry)
#ifdef NO_INLINE_APIS
    ;
#else
{
    IxQMgrQInlinedReadWriteInfo *infoPtr = &ixQMgrQInlinedReadWriteInfo[qId];
    UINT32 entrySize;

    /* write the entry */
    IX_QMGR_INLINE_WRITE_LONG(infoPtr->qAccRegAddr, *entry);
    entrySize = infoPtr->qEntrySizeInWords;

    if (entrySize != IX_QMGR_Q_ENTRY_SIZE1)
    {	
	/* process the remaining part of the entry */
	volatile UINT32 *qAccRegAddr = infoPtr->qAccRegAddr;
	while (--entrySize)
	{
	    ++entry;
	    IX_QMGR_INLINE_WRITE_LONG(++qAccRegAddr, *entry);
	}
	entrySize = infoPtr->qEntrySizeInWords;
    }

    /* overflow is available for lower queues only */
    if (qId < IX_QMGR_MIN_QUEUPP_QID)
    {   
	UINT32 qSize = infoPtr->qSizeInEntries;
	/* increment the current number of entries in the queue
	 * and check for overflow 
	 */
	if (infoPtr->qWriteCount++ == qSize)
	{
	    /* the queue may have overflow */
	    UINT32 qPtrs; /* queue internal pointers */
  
	    /* get the queue status */
	    UINT32 status = IX_QMGR_INLINE_READ_LONG(infoPtr->qUOStatRegAddr);

	    /* read the status twice because the status may 
	     * not be immediately ready after the write operation
	     */
	    if ((status & infoPtr->qOflowStatBitMask) ||
		((status = IX_QMGR_INLINE_READ_LONG(infoPtr->qUOStatRegAddr))
		 & infoPtr->qOflowStatBitMask))
	    {
		/* the queue is full, clear the overflow status
		 *  bit if it was set 
		 */
		IX_QMGR_INLINE_WRITE_LONG(infoPtr->qUOStatRegAddr,
				     status & ~infoPtr->qOflowStatBitMask);
		infoPtr->qWriteCount = infoPtr->qSizeInEntries;
		return IX_QMGR_Q_OVERFLOW;
	    }
	    /* No overflow occured : someone is draining the queue
	     * and the current counter needs to be
	     * updated from the current number of entries in the queue
	     */

	    /* get q pointer snapshot */
	    qPtrs = IX_QMGR_INLINE_READ_LONG(infoPtr->qConfigRegAddr);

	    /* Mod subtraction of pointers to get number of words in Q. */
	    qPtrs = (qPtrs - (qPtrs >> 7)) & 0x7f; 

	    if (qPtrs == 0)
	    {
		/* the queue may be full at the time of the 
		 * snapshot. Next access will check 
		 * the overflow status again.
		 */
		infoPtr->qWriteCount = qSize;
	    }
	    else 
	    {
		/* convert the number of words to a number of entries */
		if (entrySize == IX_QMGR_Q_ENTRY_SIZE1)
		{
		    infoPtr->qWriteCount = qPtrs & (qSize - 1);
		}
		else
		{
		    infoPtr->qWriteCount = (qPtrs / entrySize) & (qSize - 1);
		}
	    }
	}
    }
    return IX_SUCCESS;
}
#endif

#ifdef NO_INLINE_APIS
PUBLIC IX_STATUS
ixQMgrQBurstWrite (IxQMgrQId qId,
		   unsigned numEntries,
		   UINT32 *entries);
#else
IX_QMGR_INLINE PUBLIC IX_STATUS
ixQMgrQBurstWrite (IxQMgrQId qId,
		   unsigned numEntries,
		   UINT32 *entries);
#endif /* NO_INLINE_APIS */

IX_QMGR_INLINE PUBLIC IX_STATUS
ixQMgrQBurstWrite (IxQMgrQId qId,
		   unsigned numEntries,
		   UINT32 *entries)
#ifdef NO_INLINE_APIS
;
#else
{
    IxQMgrQInlinedReadWriteInfo *infoPtr = &ixQMgrQInlinedReadWriteInfo[qId];
    UINT32 status;

    /* update the current write count */
    infoPtr->qWriteCount += numEntries;

    if (infoPtr->qEntrySizeInWords == IX_QMGR_Q_ENTRY_SIZE1)
    {
	volatile UINT32 *qAccRegAddr = infoPtr->qAccRegAddr;
	while (numEntries--)
	{
	    IX_QMGR_INLINE_WRITE_LONG(qAccRegAddr, *entries);
	    entries++;
	}
    }
    else
    {
	IxQMgrQEntrySizeInWords entrySizeInWords = infoPtr->qEntrySizeInWords;
	UINT32 i;

	/* write each queue entry */
	while (numEntries--)
	{
	    /* write the queueEntrySize number of words for each entry */
	    for (i = 0; i < (UINT32)entrySizeInWords; i++)
	    {
		IX_QMGR_INLINE_WRITE_LONG((infoPtr->qAccRegAddr + i), *entries);
		entries++;
	    }
	}
    }

    /* check if the write count overflows */
    if (infoPtr->qWriteCount > infoPtr->qSizeInEntries)
    {
	/* reset the current write count */
	infoPtr->qWriteCount = infoPtr->qSizeInEntries;
    }

    /* Check if overflow occurred on the write operation */
    if (qId < IX_QMGR_MIN_QUEUPP_QID)
    {
	/* get the queue status */
	status = IX_QMGR_INLINE_READ_LONG(infoPtr->qUOStatRegAddr);

	/* read the status twice because the status may 
	 * not be ready at the time of the write
	 */
	if ((status & infoPtr->qOflowStatBitMask) ||
	    ((status = IX_QMGR_INLINE_READ_LONG(infoPtr->qUOStatRegAddr))
	     & infoPtr->qOflowStatBitMask))
	{
	    /* clear the underflow status bit if it was set */
	    IX_QMGR_INLINE_WRITE_LONG(infoPtr->qUOStatRegAddr,
				 status & ~infoPtr->qOflowStatBitMask);
	    return IX_QMGR_Q_OVERFLOW;
	}
    }

    return IX_SUCCESS;
}
#endif

PUBLIC IX_STATUS
ixQMgrQPoke (IxQMgrQId qId,
	     unsigned int entryIndex,
	     UINT32 *entry);

PUBLIC IX_STATUS
ixQMgrQNumEntriesGet (IxQMgrQId qId,
		      unsigned *numEntries);

PUBLIC IX_STATUS
ixQMgrQStatusGetWithChecks (IxQMgrQId qId,
                            IxQMgrQStatus *qStatus);


#ifdef NO_INLINE_APIS
PUBLIC IX_STATUS
ixQMgrQStatusGet (IxQMgrQId qId,
		  IxQMgrQStatus *qStatus);
#else  
extern UINT32 ixQMgrAqmIfQueLowStatRegAddr[];
extern UINT32 ixQMgrAqmIfQueLowStatBitsOffset[];
extern UINT32 ixQMgrAqmIfQueLowStatBitsMask;
extern UINT32 ixQMgrAqmIfQueUppStat0RegAddr;
extern UINT32 ixQMgrAqmIfQueUppStat1RegAddr;
extern UINT32 ixQMgrAqmIfQueUppStat0BitMask[];
extern UINT32 ixQMgrAqmIfQueUppStat1BitMask[];

IX_QMGR_INLINE PUBLIC IX_STATUS
ixQMgrQStatusGet (IxQMgrQId qId,
		  IxQMgrQStatus *qStatus);
#endif  /* endif NO_INLINE_APIS */

IX_QMGR_INLINE PUBLIC IX_STATUS
ixQMgrQStatusGet (IxQMgrQId qId,
		  IxQMgrQStatus *qStatus)
#ifdef NO_INLINE_APIS
    ;
#else
{
    /* read the status of a queue in the range 0-31 */
    if (qId < IX_QMGR_MIN_QUEUPP_QID)
    {
	volatile UINT32 *lowStatRegAddr = (UINT32*)ixQMgrAqmIfQueLowStatRegAddr[qId];

	UINT32 lowStatBitsOffset = ixQMgrAqmIfQueLowStatBitsOffset[qId];
	UINT32 lowStatBitsMask   = ixQMgrAqmIfQueLowStatBitsMask;

	/* read the status register for this queue */
	*qStatus = IX_QMGR_INLINE_READ_LONG(lowStatRegAddr);

	/* mask out the status bits relevant only to this queue */
	*qStatus = (*qStatus >> lowStatBitsOffset) & lowStatBitsMask;

    }
    else /* read status of a queue in the range 32-63 */
    {

	volatile UINT32 *qNearEmptyStatRegAddr = (UINT32*)ixQMgrAqmIfQueUppStat0RegAddr;
	volatile UINT32 *qFullStatRegAddr      = (UINT32*)ixQMgrAqmIfQueUppStat1RegAddr;
	int maskIndex = qId - IX_QMGR_MIN_QUEUPP_QID;
	UINT32 qNearEmptyStatBitMask = ixQMgrAqmIfQueUppStat0BitMask[maskIndex];
	UINT32 qFullStatBitMask      = ixQMgrAqmIfQueUppStat1BitMask[maskIndex];

	/* Reset the status bits */
	*qStatus = 0;

	/* Check if the queue is nearly empty */
	if (IX_QMGR_INLINE_READ_LONG(qNearEmptyStatRegAddr) & qNearEmptyStatBitMask)
	{
	    *qStatus |= IX_QMGR_Q_STATUS_NE_BIT_MASK;
	}

	/* Check if the queue is full */
	if (IX_QMGR_INLINE_READ_LONG(qFullStatRegAddr) & qFullStatBitMask)
	{
	    *qStatus |= IX_QMGR_Q_STATUS_F_BIT_MASK;
	}
    }
    return IX_SUCCESS;
}
#endif


PUBLIC IX_STATUS
ixQMgrDispatcherPrioritySet (IxQMgrQId qId,
			     IxQMgrPriority priority);
PUBLIC IX_STATUS
ixQMgrNotificationEnable (IxQMgrQId qId,
			  IxQMgrSourceId sourceId);

PUBLIC IX_STATUS
ixQMgrNotificationDisable (IxQMgrQId qId);

PUBLIC void
ixQMgrDispatcherLoopRunA0 (IxQMgrDispatchGroup group);

PUBLIC void
ixQMgrDispatcherLoopRunB0 (IxQMgrDispatchGroup group);

PUBLIC void
ixQMgrDispatcherLoopRunB0LLP (IxQMgrDispatchGroup group);

PUBLIC IX_STATUS
ixQMgrNotificationCallbackSet (IxQMgrQId qId,
			       IxQMgrCallback callback,
			       IxQMgrCallbackId callbackId);

PUBLIC void
ixQMgrDispatcherLoopGet (IxQMgrDispatcherFuncPtr *qDispatcherFuncPtr);

PUBLIC void
ixQMgrStickyInterruptRegEnable(void);


PUBLIC IX_STATUS
ixQMgrCallbackTypeSet(IxQMgrQId qId,
                      IxQMgrType type);

PUBLIC IX_STATUS
ixQMgrCallbackTypeGet(IxQMgrQId qId,
                      IxQMgrType *type);

PUBLIC void
ixQMgrPeriodicDone(void);


PUBLIC void
ixQMgrLLPShow(int resetStats);


#endif /* IXQMGR_H */



