

#ifndef IXTIMESYNCACC_H
#define IXTIMESYNCACC_H

#ifdef  __ixp46X

#include "IxOsal.h"


typedef enum /**< IxTimeSyncAccStatus */
{
    IX_TIMESYNCACC_SUCCESS = IX_SUCCESS,    /**< Requested operation successful */
    IX_TIMESYNCACC_INVALIDPARAM,            /**< An invalid parameter was passed */
    IX_TIMESYNCACC_NOTIMESTAMP,             /**< While polling no time stamp available */
    IX_TIMESYNCACC_INTERRUPTMODEINUSE,      /**< Polling not allowed while operating in interrupt mode */
    IX_TIMESYNCACC_FAILED                   /**< Internal error occurred */
}IxTimeSyncAccStatus;

typedef enum /**< IxTimeSyncAccAuxMode */
{
    IX_TIMESYNCACC_AUXMODE_MASTER,          /**< Auxiliary Master Mode */
    IX_TIMESYNCACC_AUXMODE_SLAVE,           /**< Auxiliary Slave Mode */
    IX_TIMESYNCACC_AUXMODE_INVALID          /**< Invalid Auxiliary Mode */
}IxTimeSyncAccAuxMode;

typedef enum /**< IxTimeSyncAcc1588PTPPort */
{
    IX_TIMESYNCACC_NPE_A_1588PTP_PORT,      /**< PTP Communication Port on NPE-A */
    IX_TIMESYNCACC_NPE_B_1588PTP_PORT,      /**< PTP Communication Port on NPE-B */
    IX_TIMESYNCACC_NPE_C_1588PTP_PORT,      /**< PTP Communication Port on NPE-C */
    IX_TIMESYNCACC_NPE_1588PORT_INVALID     /**< Invalid PTP Communication Port */
} IxTimeSyncAcc1588PTPPort;

typedef enum  /**< IxTimeSyncAcc1588PTPPortMode */
{
    IX_TIMESYNCACC_1588PTP_PORT_MASTER,       /**< PTP Communication Port in Master Mode */
    IX_TIMESYNCACC_1588PTP_PORT_SLAVE,        /**< PTP Communication Port in Slave Mode */
    IX_TIMESYNCACC_1588PTP_PORT_ANYMODE,      /**< PTP Communication Port in ANY Mode
                                                  allows time stamping of all messages
                                                  including non-1588 PTP */
    IX_TIMESYNCACC_1588PTP_PORT_MODE_INVALID  /**< Invalid PTP Port Mode */
}IxTimeSyncAcc1588PTPPortMode;

typedef enum  /**< IxTimeSyncAcc1588PTPMsgType */
{
    IX_TIMESYNCACC_1588PTP_MSGTYPE_SYNC,     /**< PTP Sync message sent by Master or received by Slave */
    IX_TIMESYNCACC_1588PTP_MSGTYPE_DELAYREQ, /**< PTP Delay_Req message sent by Slave or received by Master */
    IX_TIMESYNCACC_1588PTP_MSGTYPE_UNKNOWN   /**< Other PTP and non-PTP message sent or received by both
                                                Master and/or Slave */
} IxTimeSyncAcc1588PTPMsgType;


typedef struct  /**< IxTimeSyncAccTimeValue */
{
    UINT32 timeValueLowWord;               /**< Lower 32 bits of the time value */
    UINT32 timeValueHighWord;              /**< Upper 32 bits of the time value */  
} IxTimeSyncAccTimeValue;

typedef struct  /**< IxTimeSyncAccUuid */
{
    UINT32 uuidValueLowWord;               /**<The lower 32 bits of the UUID */
    UINT16 uuidValueHighHalfword;          /**<The upper 16 bits of the UUID */  
} IxTimeSyncAccUuid;

typedef struct  /**< IxTimeSyncAccPtpMsgData */
{
    IxTimeSyncAcc1588PTPMsgType ptpMsgType; /**< PTP Messages type */
    IxTimeSyncAccTimeValue ptpTimeStamp;    /**< 64 bit TimeStamp value from PTP Message */
    IxTimeSyncAccUuid ptpUuid;              /**< 48 bit UUID value from the PTP Message */
    UINT16 ptpSequenceNumber;               /**< 16 bit Sequence Number from PTP Message */
} IxTimeSyncAccPtpMsgData;

typedef struct  /**< IxTimeSyncAccStats */
{
    UINT32 rxMsgs; /**< Count of timestamps for received PTP Messages */
    UINT32 txMsgs; /**< Count of timestamps for transmitted PTP Messages */
} IxTimeSyncAccStats;

typedef void (*IxTimeSyncAccTargetTimeCallback)(IxTimeSyncAccTimeValue targetTime);

typedef void (*IxTimeSyncAccAuxTimeCallback)(IxTimeSyncAccAuxMode auxMode,
             IxTimeSyncAccTimeValue auxTime);


PUBLIC IxTimeSyncAccStatus
ixTimeSyncAccPTPPortConfigSet(IxTimeSyncAcc1588PTPPort ptpPort,
       IxTimeSyncAcc1588PTPPortMode ptpPortMode);

PUBLIC IxTimeSyncAccStatus
ixTimeSyncAccPTPPortConfigGet(IxTimeSyncAcc1588PTPPort ptpPort,
    IxTimeSyncAcc1588PTPPortMode *ptpPortMode);

PUBLIC IxTimeSyncAccStatus
ixTimeSyncAccPTPRxPoll(IxTimeSyncAcc1588PTPPort ptpPort,
    IxTimeSyncAccPtpMsgData  *ptpMsgData);

PUBLIC IxTimeSyncAccStatus
ixTimeSyncAccPTPTxPoll(IxTimeSyncAcc1588PTPPort ptpPort,
    IxTimeSyncAccPtpMsgData  *ptpMsgData);

PUBLIC IxTimeSyncAccStatus
ixTimeSyncAccSystemTimeSet(IxTimeSyncAccTimeValue systemTime);

PUBLIC IxTimeSyncAccStatus
ixTimeSyncAccSystemTimeGet(IxTimeSyncAccTimeValue *systemTime);

PUBLIC IxTimeSyncAccStatus
ixTimeSyncAccTickRateSet(UINT32 tickRate);

PUBLIC IxTimeSyncAccStatus
ixTimeSyncAccTickRateGet(UINT32 *tickRate);

PUBLIC IxTimeSyncAccStatus
ixTimeSyncAccTargetTimeInterruptEnable(IxTimeSyncAccTargetTimeCallback targetTimeCallback);

PUBLIC IxTimeSyncAccStatus
ixTimeSyncAccTargetTimeInterruptDisable(void);

PUBLIC IxTimeSyncAccStatus
ixTimeSyncAccTargetTimePoll(BOOL *ttmPollFlag,
    IxTimeSyncAccTimeValue *targetTime);

PUBLIC IxTimeSyncAccStatus
ixTimeSyncAccTargetTimeSet(IxTimeSyncAccTimeValue targetTime);

PUBLIC IxTimeSyncAccStatus
ixTimeSyncAccTargetTimeGet(IxTimeSyncAccTimeValue *targetTime);

PUBLIC IxTimeSyncAccStatus
ixTimeSyncAccAuxTimeInterruptEnable(IxTimeSyncAccAuxMode auxMode,
    IxTimeSyncAccAuxTimeCallback auxTimeCallback);

PUBLIC IxTimeSyncAccStatus
ixTimeSyncAccAuxTimeInterruptDisable(IxTimeSyncAccAuxMode auxMode);

PUBLIC IxTimeSyncAccStatus
ixTimeSyncAccAuxTimePoll(IxTimeSyncAccAuxMode auxMode,
    BOOL *auxPollFlag,
    IxTimeSyncAccTimeValue *auxTime);

PUBLIC IxTimeSyncAccStatus
ixTimeSyncAccReset(void);

PUBLIC IxTimeSyncAccStatus
ixTimeSyncAccStatsGet(IxTimeSyncAccStats *timeSyncStats);

PUBLIC void
ixTimeSyncAccStatsReset(void);

PUBLIC IxTimeSyncAccStatus
ixTimeSyncAccShow(void);

#endif /* __ixp46X */
#endif /* IXTIMESYNCACC_H */


