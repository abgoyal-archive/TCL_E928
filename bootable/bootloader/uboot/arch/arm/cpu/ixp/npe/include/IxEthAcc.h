

#ifndef IxEthAcc_H
#define IxEthAcc_H

#include <IxOsBuffMgt.h>
#include <IxTypes.h>


typedef enum /* IxEthAccStatus */
{
    IX_ETH_ACC_SUCCESS = IX_SUCCESS, /**< return success*/
    IX_ETH_ACC_FAIL = IX_FAIL, /**< return fail*/
    IX_ETH_ACC_INVALID_PORT, /**< return invalid port*/
    IX_ETH_ACC_PORT_UNINITIALIZED, /**< return uninitialized*/
    IX_ETH_ACC_MAC_UNINITIALIZED, /**< return MAC uninitialized*/
    IX_ETH_ACC_INVALID_ARG, /**< return invalid arg*/
    IX_ETH_TX_Q_FULL, /**< return tx queue is full*/
    IX_ETH_ACC_NO_SUCH_ADDR /**< return no such address*/
} IxEthAccStatus;

typedef enum  
{
	IX_ETH_PORT_1 = 0, /**< Ethernet Port 1 */
	IX_ETH_PORT_2 = 1  /**< Ethernet port 2 */
	,IX_ETH_PORT_3 = 2 /**< Ethernet port 3 */
} IxEthAccPortId;

#ifdef __ixp46X
#define IX_ETH_ACC_NUMBER_OF_PORTS (3)
#else
#define IX_ETH_ACC_NUMBER_OF_PORTS (2)
#endif

#define IX_IEEE803_MAC_ADDRESS_SIZE (6)


typedef struct  
{
    UINT8 macAddress[IX_IEEE803_MAC_ADDRESS_SIZE]; /**< MAC address */
} IxEthAccMacAddr;

#define IX_ETH_ACC_NUM_TX_PRIORITIES (8)

typedef enum  
{
	IX_ETH_ACC_TX_PRIORITY_0 = 0, /**<Lowest Priority submission */
	IX_ETH_ACC_TX_PRIORITY_1 = 1, /**<submission prority of 1 (0 is lowest)*/
	IX_ETH_ACC_TX_PRIORITY_2 = 2, /**<submission prority of 2 (0 is lowest)*/
	IX_ETH_ACC_TX_PRIORITY_3 = 3, /**<submission prority of 3 (0 is lowest)*/
	IX_ETH_ACC_TX_PRIORITY_4 = 4, /**<submission prority of 4 (0 is lowest)*/
	IX_ETH_ACC_TX_PRIORITY_5 = 5, /**<submission prority of 5 (0 is lowest)*/
	IX_ETH_ACC_TX_PRIORITY_6 = 6, /**<submission prority of 6 (0 is lowest)*/
	IX_ETH_ACC_TX_PRIORITY_7 = 7, /**<Highest priority submission */

	IX_ETH_ACC_TX_DEFAULT_PRIORITY = IX_ETH_ACC_TX_PRIORITY_0 /**< By default send all 
								 packets with lowest priority */
} IxEthAccTxPriority;

typedef enum  
{
	IX_ETHACC_RX_LLCTYPE = 0x00, /**< 802.3 - 8802, with LLC/SNAP */
	IX_ETHACC_RX_ETHTYPE = 0x10, /**< 802.3 (Ethernet) without LLC/SNAP */
	IX_ETHACC_RX_STATYPE = 0x20, /**< 802.11, AP <=> STA */
	IX_ETHACC_RX_APTYPE  = 0x30  /**< 802.11, AP <=> AP */
} IxEthAccRxFrameType;

typedef enum
{
    IX_ETH_ACC_FULL_DUPLEX, /**< Full duplex operation of the MAC */
    IX_ETH_ACC_HALF_DUPLEX  /**< Half duplex operation of the MAC */
} IxEthAccDuplexMode;


typedef struct
{
    UINT32 ixReserved_next;    /**< reserved for chaining */
    UINT32 ixReserved_lengths; /**< reserved for buffer lengths */
    UINT32 ixReserved_data;    /**< reserved for buffer pointer */
    UINT8  ixDestinationPortId; /**< Destination portId for this packet, if known by NPE */
    UINT8  ixSourcePortId; /**< Source portId for this packet */
    UINT16 ixFlags;        /**< BitField of option for this frame */
    UINT8  ixQoS;          /**< QoS class of the frame */
    UINT8  ixReserved;     /**< reserved */
    UINT16 ixVlanTCI;      /**< Vlan TCI */
    UINT8  ixDestMac[IX_IEEE803_MAC_ADDRESS_SIZE]; /**< Destination MAC address */
    UINT8  ixSourceMac[IX_IEEE803_MAC_ADDRESS_SIZE]; /**< Source MAC address */
} IxEthAccNe;

#define IX_ETHACC_NE_PORT_UNKNOWN   (0xff)

#define IX_ETHACC_NE_DESTMAC(mBufPtr) ((IxEthAccNe *)&((mBufPtr)->ix_ne))->ixDestMac

#define IX_ETHACC_NE_SOURCEMAC(mBufPtr) ((IxEthAccNe *)&((mBufPtr)->ix_ne))->ixSourceMac

#define IX_ETHACC_NE_VLANTCI(mBufPtr) ((IxEthAccNe *)&((mBufPtr)->ix_ne))->ixVlanTCI

#define IX_ETHACC_NE_SOURCEPORTID(mBufPtr) ((IxEthAccNe *)&((mBufPtr)->ix_ne))->ixSourcePortId

#define IX_ETHACC_NE_DESTPORTID(mBufPtr) ((IxEthAccNe *)&((mBufPtr)->ix_ne))->ixDestinationPortId

#define IX_ETHACC_NE_QOS(mBufPtr) ((IxEthAccNe *)&((mBufPtr)->ix_ne))->ixQoS

#define IX_ETHACC_NE_FLAGS(mBufPtr) ((IxEthAccNe *)&((mBufPtr)->ix_ne))->ixFlags

#define IX_ETHACC_NE_BCASTMASK      (0x1)

#define IX_ETHACC_NE_MCASTMASK      (0x1 << 1)

#define IX_ETHACC_NE_IPMASK         (0x1 << 2)

#define IX_ETHACC_NE_VLANMASK       (0x1 << 3)

#define IX_ETHACC_NE_LINKMASK       (0x3 << 4)

#define IX_ETHACC_NE_STMASK         (0x1 << 6)

#define IX_ETHACC_NE_FILTERMASK     (0x1 << 7)

#define IX_ETHACC_NE_PORTOVERMASK   (0x1 << 8)

#define IX_ETHACC_NE_TAGMODEMASK    (0x1 << 9)

#define IX_ETHACC_NE_TAGOVERMASK    (0x1 << 10)

#define IX_ETHACC_NE_VLANENABLEMASK (0x1 << 14)

#define IX_ETHACC_NE_NEWSRCMASK     (0x1 << 15)

#define IX_ETHACC_RX_MBUF_MIN_SIZE (2048)

#define IXP425_ETH_ACC_MII_MAX_ADDR   32

PUBLIC IxEthAccStatus ixEthAccInit(void);


PUBLIC void ixEthAccUnload(void);

PUBLIC IxEthAccStatus ixEthAccPortInit(IxEthAccPortId portId);





PUBLIC IxEthAccStatus ixEthAccPortTxFrameSubmit( 
    IxEthAccPortId portId,
    IX_OSAL_MBUF *buffer, 
    IxEthAccTxPriority priority);

typedef void (*IxEthAccPortTxDoneCallback) ( UINT32 callbackTag, IX_OSAL_MBUF *buffer );



PUBLIC IxEthAccStatus
ixEthAccPortTxDoneCallbackRegister(IxEthAccPortId portId,
								   IxEthAccPortTxDoneCallback txCallbackFn,
								   UINT32 callbackTag);



typedef void (*IxEthAccPortRxCallback) (UINT32 callbackTag, IX_OSAL_MBUF *buffer, UINT32 reserved);


typedef void (*IxEthAccPortMultiBufferRxCallback) (UINT32 callbackTag, IX_OSAL_MBUF **buffer);




PUBLIC IxEthAccStatus
ixEthAccPortRxCallbackRegister(IxEthAccPortId portId,
							   IxEthAccPortRxCallback rxCallbackFn,
							   UINT32 callbackTag);


PUBLIC IxEthAccStatus
ixEthAccPortMultiBufferRxCallbackRegister(IxEthAccPortId portId,
										  IxEthAccPortMultiBufferRxCallback rxCallbackFn,
										  UINT32 callbackTag);

PUBLIC IxEthAccStatus
ixEthAccPortRxFreeReplenish( IxEthAccPortId portId, IX_OSAL_MBUF *buffer);




PUBLIC IxEthAccStatus ixEthAccPortEnable(IxEthAccPortId portId);

PUBLIC IxEthAccStatus ixEthAccPortDisable(IxEthAccPortId portId);

PUBLIC IxEthAccStatus
ixEthAccPortEnabledQuery(IxEthAccPortId portId, BOOL *enabled);

PUBLIC IxEthAccStatus ixEthAccPortPromiscuousModeClear(IxEthAccPortId portId);


PUBLIC IxEthAccStatus ixEthAccPortPromiscuousModeSet(IxEthAccPortId portId);

PUBLIC IxEthAccStatus ixEthAccPortUnicastMacAddressSet(IxEthAccPortId portId,
													   IxEthAccMacAddr *macAddr);

PUBLIC IxEthAccStatus
ixEthAccPortUnicastMacAddressGet(IxEthAccPortId portId,
								 IxEthAccMacAddr *macAddr);




PUBLIC IxEthAccStatus
ixEthAccPortMulticastAddressJoin(IxEthAccPortId portId,
								 IxEthAccMacAddr *macAddr);

PUBLIC IxEthAccStatus
ixEthAccPortMulticastAddressJoinAll(IxEthAccPortId portId);

PUBLIC IxEthAccStatus
ixEthAccPortMulticastAddressLeave(IxEthAccPortId portId,
								  IxEthAccMacAddr *macAddr);

PUBLIC IxEthAccStatus
ixEthAccPortMulticastAddressLeaveAll(IxEthAccPortId portId);

PUBLIC IxEthAccStatus ixEthAccPortUnicastAddressShow(IxEthAccPortId portId);


PUBLIC void ixEthAccPortMulticastAddressShow( IxEthAccPortId portId);

PUBLIC IxEthAccStatus 
ixEthAccPortDuplexModeSet(IxEthAccPortId portId,IxEthAccDuplexMode mode);

PUBLIC IxEthAccStatus 
ixEthAccPortDuplexModeGet(IxEthAccPortId portId,IxEthAccDuplexMode *mode );

PUBLIC IxEthAccStatus
ixEthAccPortTxFrameAppendPaddingEnable(IxEthAccPortId portId);

PUBLIC IxEthAccStatus
ixEthAccPortTxFrameAppendPaddingDisable(IxEthAccPortId portId);

PUBLIC IxEthAccStatus
ixEthAccPortTxFrameAppendFCSEnable(IxEthAccPortId portId);

PUBLIC IxEthAccStatus
ixEthAccPortTxFrameAppendFCSDisable(IxEthAccPortId portId);

PUBLIC IxEthAccStatus
ixEthAccPortRxFrameAppendFCSEnable(IxEthAccPortId portId);

PUBLIC IxEthAccStatus
ixEthAccPortRxFrameAppendFCSDisable(IxEthAccPortId portId);




typedef  enum 
{
    FIFO_NO_PRIORITY, /**<frames submitted with no priority*/
    FIFO_PRIORITY /**<higher prority frames submitted before lower priority*/
}IxEthAccSchedulerDiscipline;

#define IxEthAccTxSchedulerDiscipline IxEthAccSchedulerDiscipline



PUBLIC IxEthAccStatus
ixEthAccTxSchedulingDisciplineSet(IxEthAccPortId portId, 
								  IxEthAccSchedulerDiscipline sched);


PUBLIC IxEthAccStatus
ixEthAccRxSchedulingDisciplineSet(IxEthAccSchedulerDiscipline sched);

PUBLIC IxEthAccStatus 
ixEthAccPortNpeLoopbackEnable(IxEthAccPortId portId);

PUBLIC IxEthAccStatus 
ixEthAccPortNpeLoopbackDisable(IxEthAccPortId portId);

PUBLIC IxEthAccStatus 
ixEthAccPortTxEnable(IxEthAccPortId portId);

PUBLIC IxEthAccStatus 
ixEthAccPortTxDisable(IxEthAccPortId portId);

PUBLIC IxEthAccStatus 
ixEthAccPortRxEnable(IxEthAccPortId portId);

PUBLIC IxEthAccStatus 
ixEthAccPortRxDisable(IxEthAccPortId portId);

PUBLIC IxEthAccStatus 
ixEthAccPortMacReset(IxEthAccPortId portId);



typedef struct   
{
    UINT32 dot3StatsAlignmentErrors;            /**< link error count (rx) */
    UINT32 dot3StatsFCSErrors;                  /**< link error count (rx) */
    UINT32 dot3StatsInternalMacReceiveErrors;   /**< link error count (rx) */
    UINT32 RxOverrunDiscards;                   /**< NPE: discarded frames count (rx) */
    UINT32 RxLearnedEntryDiscards;                /**< NPE: discarded frames count(rx)  */
    UINT32 RxLargeFramesDiscards;                 /**< NPE: discarded frames count(rx)  */
    UINT32 RxSTPBlockedDiscards;                  /**< NPE: discarded frames count(rx)  */
    UINT32 RxVLANTypeFilterDiscards;              /**< NPE: discarded frames count (rx) */
    UINT32 RxVLANIdFilterDiscards;                /**< NPE: discarded frames count (rx) */
    UINT32 RxInvalidSourceDiscards;               /**< NPE: discarded frames count (rx) */
    UINT32 RxBlackListDiscards;                   /**< NPE: discarded frames count (rx) */
    UINT32 RxWhiteListDiscards;                   /**< NPE: discarded frames count (rx) */
    UINT32 RxUnderflowEntryDiscards;              /**< NPE: discarded frames count (rx) */
    UINT32 dot3StatsSingleCollisionFrames;      /**< link error count (tx) */
    UINT32 dot3StatsMultipleCollisionFrames;    /**< link error count (tx) */
    UINT32 dot3StatsDeferredTransmissions;      /**< link error count (tx) */
    UINT32 dot3StatsLateCollisions;             /**< link error count (tx) */
    UINT32 dot3StatsExcessiveCollsions;         /**< link error count (tx) */
    UINT32 dot3StatsInternalMacTransmitErrors;  /**< link error count (tx) */
    UINT32 dot3StatsCarrierSenseErrors;         /**< link error count (tx) */
    UINT32 TxLargeFrameDiscards;                /**< NPE: discarded frames count (tx) */
    UINT32 TxVLANIdFilterDiscards;              /**< NPE: discarded frames count (tx) */

}IxEthEthObjStats;

PUBLIC IxEthAccStatus
ixEthAccMibIIStatsGet(IxEthAccPortId portId, IxEthEthObjStats *retStats );

PUBLIC IxEthAccStatus
ixEthAccMibIIStatsGetClear(IxEthAccPortId portId, IxEthEthObjStats *retStats);

PUBLIC IxEthAccStatus ixEthAccMibIIStatsClear(IxEthAccPortId portId);

PUBLIC IxEthAccStatus ixEthAccMacInit(IxEthAccPortId portId);

PUBLIC void ixEthAccStatsShow(IxEthAccPortId portId);



PUBLIC IxEthAccStatus
ixEthAccMiiReadRtn (UINT8 phyAddr, UINT8 phyReg, UINT16 *value);

PUBLIC IxEthAccStatus
ixEthAccMiiWriteRtn (UINT8 phyAddr, UINT8 phyReg, UINT16 value);

PUBLIC IxEthAccStatus
ixEthAccMiiAccessTimeoutSet(UINT32 timeout, UINT32 retryCount);

PUBLIC IxEthAccStatus ixEthAccMiiStatsShow (UINT32 phyAddr);



/******* BOARD SPECIFIC DEPRECATED API *********/


 #include "IxEthMii.h"

#define ixEthAccMiiPhyScan(phyPresent) ixEthMiiPhyScan(phyPresent,IXP425_ETH_ACC_MII_MAX_ADDR)

#define ixEthAccMiiPhyConfig(phyAddr,speed100,fullDuplex,autonegotiate) \
           ixEthMiiPhyConfig(phyAddr,speed100,fullDuplex,autonegotiate)

#define ixEthAccMiiPhyReset(phyAddr) \
           ixEthMiiPhyReset(phyAddr)

#define ixEthAccMiiLinkStatus(phyAddr,linkUp,speed100,fullDuplex,autoneg) \
           ixEthMiiLinkStatus(phyAddr,linkUp,speed100,fullDuplex,autoneg)



#define ixEthAccMiiShow(phyAddr) \
        ixEthMiiPhyShow(phyAddr)

#endif /* ndef IxEthAcc_H */
