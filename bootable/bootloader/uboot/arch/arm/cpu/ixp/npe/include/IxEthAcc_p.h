


#ifndef IxEthAcc_p_H
#define IxEthAcc_p_H

#include "IxOsal.h"

#include "IxNpeDl.h"
#include "IxQMgr.h"

#include "IxEthNpe.h"


#include "IxEthAccDataPlane_p.h"
#include "IxEthAccMac_p.h"


#define INLINE __inline__

#ifdef NDEBUG

#define IX_ETH_ACC_PRIVATE static

#else

#define IX_ETH_ACC_PRIVATE

#endif /* ndef NDEBUG */

#define IX_ETH_ACC_PUBLIC


#define IX_ETH_ACC_IS_PORT_VALID(port) ((port) <  IX_ETH_ACC_NUMBER_OF_PORTS  ? TRUE : FALSE )



#ifndef NDEBUG
#define IX_ETH_ACC_FATAL_LOG(a,b,c,d,e,f,g)   { ixOsalLog ( IX_OSAL_LOG_LVL_FATAL,IX_OSAL_LOG_DEV_STDOUT,a,b,c,d,e,f,g);}
#define IX_ETH_ACC_WARNING_LOG(a,b,c,d,e,f,g) { ixOsalLog ( IX_OSAL_LOG_LVL_WARNING,IX_OSAL_LOG_DEV_STDOUT,a,b,c,d,e,f,g);}
#define IX_ETH_ACC_DEBUG_LOG(a,b,c,d,e,f,g)   { ixOsalLog ( IX_OSAL_LOG_LVL_FATAL,IX_OSAL_LOG_DEV_STDOUT,a,b,c,d,e,f,g);}
#else
#define IX_ETH_ACC_FATAL_LOG(a,b,c,d,e,f,g)   { ixOsalLog ( IX_OSAL_LOG_LVL_FATAL,IX_OSAL_LOG_DEV_STDOUT,a,b,c,d,e,f,g);}
#define IX_ETH_ACC_WARNING_LOG(a,b,c,d,e,f,g) { ixOsalLog ( IX_OSAL_LOG_LVL_WARNING,IX_OSAL_LOG_DEV_STDOUT,a,b,c,d,e,f,g);}
#define IX_ETH_ACC_DEBUG_LOG(a,b,c,d,e,f,g)   {}
#endif

IX_ETH_ACC_PUBLIC IxEthAccStatus ixEthAccInitDataPlane(void);
IX_ETH_ACC_PUBLIC IxEthAccStatus ixEthAccQMgrQueuesConfig(void);
IX_ETH_ACC_PUBLIC IxEthAccStatus ixEthAccQMgrRxCallbacksRegister(IxQMgrCallback ixQMgrCallback);
IX_ETH_ACC_PUBLIC IxEthAccStatus ixEthAccSingleEthNpeCheck(IxEthAccPortId portId);
IX_ETH_ACC_PUBLIC void ixEthAccQMgrRxQEntryGet(UINT32 *numRxQueueEntries);

/* prototypes for the private control plane functions (used by the control interface wrapper) */
IX_ETH_ACC_PUBLIC IxEthAccStatus ixEthAccPortEnablePriv(IxEthAccPortId portId);
IX_ETH_ACC_PUBLIC IxEthAccStatus ixEthAccPortDisablePriv(IxEthAccPortId portId);
IX_ETH_ACC_PUBLIC IxEthAccStatus ixEthAccPortEnabledQueryPriv(IxEthAccPortId portId, BOOL *enabled);
IX_ETH_ACC_PUBLIC IxEthAccStatus ixEthAccPortPromiscuousModeClearPriv(IxEthAccPortId portId);
IX_ETH_ACC_PUBLIC IxEthAccStatus ixEthAccPortPromiscuousModeSetPriv(IxEthAccPortId portId);
IX_ETH_ACC_PUBLIC IxEthAccStatus ixEthAccPortUnicastMacAddressSetPriv(IxEthAccPortId portId, IxEthAccMacAddr *macAddr);
IX_ETH_ACC_PUBLIC IxEthAccStatus ixEthAccPortUnicastMacAddressGetPriv(IxEthAccPortId portId, IxEthAccMacAddr *macAddr);
IX_ETH_ACC_PUBLIC IxEthAccStatus ixEthAccPortMulticastAddressJoinPriv(IxEthAccPortId portId, IxEthAccMacAddr *macAddr);
IX_ETH_ACC_PUBLIC IxEthAccStatus ixEthAccPortMulticastAddressJoinAllPriv(IxEthAccPortId portId);
IX_ETH_ACC_PUBLIC IxEthAccStatus ixEthAccPortMulticastAddressLeavePriv(IxEthAccPortId portId, IxEthAccMacAddr *macAddr);
IX_ETH_ACC_PUBLIC IxEthAccStatus ixEthAccPortMulticastAddressLeaveAllPriv(IxEthAccPortId portId);
IX_ETH_ACC_PUBLIC IxEthAccStatus ixEthAccPortUnicastAddressShowPriv(IxEthAccPortId portId);
IX_ETH_ACC_PUBLIC void ixEthAccPortMulticastAddressShowPriv(IxEthAccPortId portId);
IX_ETH_ACC_PUBLIC IxEthAccStatus ixEthAccPortDuplexModeSetPriv(IxEthAccPortId portId, IxEthAccDuplexMode mode);
IX_ETH_ACC_PUBLIC IxEthAccStatus ixEthAccPortDuplexModeGetPriv(IxEthAccPortId portId, IxEthAccDuplexMode *mode);
IX_ETH_ACC_PUBLIC IxEthAccStatus ixEthAccPortTxFrameAppendPaddingEnablePriv(IxEthAccPortId portId);
IX_ETH_ACC_PUBLIC IxEthAccStatus ixEthAccPortTxFrameAppendPaddingDisablePriv(IxEthAccPortId portId);
IX_ETH_ACC_PUBLIC IxEthAccStatus ixEthAccPortTxFrameAppendFCSEnablePriv(IxEthAccPortId portId);
IX_ETH_ACC_PUBLIC IxEthAccStatus ixEthAccPortTxFrameAppendFCSDisablePriv(IxEthAccPortId portId);
IX_ETH_ACC_PUBLIC IxEthAccStatus ixEthAccPortRxFrameAppendFCSEnablePriv(IxEthAccPortId portId);
IX_ETH_ACC_PUBLIC IxEthAccStatus ixEthAccPortRxFrameAppendFCSDisablePriv(IxEthAccPortId portId);
IX_ETH_ACC_PUBLIC IxEthAccStatus ixEthAccTxSchedulingDisciplineSetPriv(IxEthAccPortId portId, IxEthAccSchedulerDiscipline sched);
IX_ETH_ACC_PUBLIC IxEthAccStatus ixEthAccRxSchedulingDisciplineSetPriv(IxEthAccSchedulerDiscipline sched);

typedef struct
{ 
    UINT32 rxFrameClientCallback;
    UINT32 rxFreeRepOK;
    UINT32 rxFreeRepDelayed;
    UINT32 rxFreeRepFromSwQOK;
    UINT32 rxFreeRepFromSwQDelayed;
    UINT32 rxFreeLateNotificationEnabled;
    UINT32 rxFreeLowCallback;
    UINT32 rxFreeOverflow;
    UINT32 rxFreeLock;
    UINT32 rxDuringDisable;
    UINT32 rxSwQDuringDisable;
    UINT32 rxUnlearnedMacAddress;
    UINT32 rxPriority[IX_ETH_ACC_TX_PRIORITY_7 + 1];
    UINT32 rxUnexpectedError;
    UINT32 rxFiltered;
} IxEthAccRxDataStats;

typedef struct
{   
    UINT32 txQOK;
    UINT32 txQDelayed;
    UINT32 txFromSwQOK;
    UINT32 txFromSwQDelayed;
    UINT32 txLowThreshCallback;
    UINT32 txDoneClientCallback;
    UINT32 txDoneClientCallbackDisable;
    UINT32 txOverflow;
    UINT32 txLock;
    UINT32 txPriority[IX_ETH_ACC_TX_PRIORITY_7 + 1];
    UINT32 txLateNotificationEnabled;
    UINT32 txDoneDuringDisable;
    UINT32 txDoneSwQDuringDisable;
    UINT32 txUnexpectedError;
} IxEthAccTxDataStats;

/* port Disable state machine : list of states */
typedef enum
{
    /* general port states */
    DISABLED = 0,
    ACTIVE,

    /* particular Tx/Rx states */
    REPLENISH,
    RECEIVE,
    TRANSMIT,
    TRANSMIT_DONE
} IxEthAccPortDisableState;

typedef struct
{
    BOOL fullDuplex;
    BOOL rxFCSAppend;
    BOOL txFCSAppend;
    BOOL txPADAppend;
    BOOL enabled;
    BOOL promiscuous;
    BOOL joinAll;
    IxOsalMutex ackMIBStatsLock;
    IxOsalMutex ackMIBStatsResetLock;
    IxOsalMutex MIBStatsGetAccessLock;
    IxOsalMutex MIBStatsGetResetAccessLock;
    IxOsalMutex npeLoopbackMessageLock;
    IxEthAccMacAddr mcastAddrsTable[IX_ETH_ACC_MAX_MULTICAST_ADDRESSES];
    UINT32 mcastAddrIndex;
    IX_OSAL_MBUF *portDisableTxMbufPtr;
    IX_OSAL_MBUF *portDisableRxMbufPtr;

    volatile IxEthAccPortDisableState portDisableState;
    volatile IxEthAccPortDisableState rxState;
    volatile IxEthAccPortDisableState txState;

    BOOL initDone;
    BOOL macInitialised;
} IxEthAccMacState;

typedef struct
{
  IxQMgrQId higherPriorityQueue[IX_QMGR_MAX_NUM_QUEUES]; /**< higher priority queue list */
  IxEthAccSchedulerDiscipline schDiscipline; /**< Receive Xscale QoS type */
} IxEthAccInfo; 

typedef struct
{
  IxQMgrQId rxFreeQueue; /**< rxFree Queue for this port */
  IxEthAccPortRxCallback rxCallbackFn;
  UINT32  rxCallbackTag;
  IxEthAccDataPlaneQList freeBufferList;
  IxEthAccPortMultiBufferRxCallback rxMultiBufferCallbackFn;
  UINT32  rxMultiBufferCallbackTag;
  BOOL rxMultiBufferCallbackInUse;
  IxEthAccRxDataStats stats; /**< Receive s/w stats */
} IxEthAccRxDataInfo; 

typedef struct
{
  IxEthAccPortTxDoneCallback  txBufferDoneCallbackFn;
  UINT32  txCallbackTag;
  IxEthAccDataPlaneQList	txQ[IX_ETH_ACC_NUM_TX_PRIORITIES]; /**< Transmit Q */
  IxEthAccSchedulerDiscipline schDiscipline; /**< Transmit Xscale QoS */
  IxQMgrQId txQueue; /**< txQueue for this port */
  IxEthAccTxDataStats stats; /**< Transmit s/w stats */
} IxEthAccTxDataInfo; 


typedef struct
{
    BOOL               portInitialized;
    UINT32 npeId; /**< NpeId for this port */
    IxEthAccTxDataInfo ixEthAccTxData; /**< Transmit data control structures */
    IxEthAccRxDataInfo ixEthAccRxData; /**< Recieve data control structures */
} IxEthAccPortDataInfo; 

extern IxEthAccPortDataInfo  ixEthAccPortData[];
#define IX_ETH_IS_PORT_INITIALIZED(port) (ixEthAccPortData[port].portInitialized)

extern BOOL ixEthAccServiceInit;
#define IX_ETH_ACC_IS_SERVICE_INITIALIZED() (ixEthAccServiceInit == TRUE )


#define IX_ETH_ACC_MAX_RX_FRAME_CONSUME_PER_CALLBACK (128)

#define IX_ETH_ACC_MAX_RX_FREE_BUFFERS_LOAD (256)  /* Set greater than depth of h/w Q + drain time at line rate */


#define IX_ETH_ACC_MAX_TX_FRAME_DONE_CONSUME_PER_CALLBACK (256)


#define IX_ETH_ACC_MAX_TX_FRAME_TX_CONSUME_PER_CALLBACK (16)


#define IX_ETH_ACC_FLUSH_CACHE(addr,size)  IX_OSAL_CACHE_FLUSH((addr),(size))
#define IX_ETH_ACC_INVALIDATE_CACHE(addr,size)  IX_OSAL_CACHE_INVALIDATE((addr),(size))


#define IX_ETH_ACC_MEMSET(start,value,size) memset(start,value,size)

#endif /* ndef IxEthAcc_p_H */



