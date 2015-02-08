
 
#ifndef IxEthDB_H
#define IxEthDB_H

#include <IxOsBuffMgt.h>
#include <IxTypes.h>


#define INLINE __inline__

#define IX_ETH_DB_PRIVATE PRIVATE /* imported from IxTypes.h */

#define IX_ETH_DB_PUBLIC PUBLIC

#define IX_ETH_DB_PORT_ID_TO_NPE(id) (id == 0 ? 1 : (id == 1 ? 2 : (id == 2 ? 0 : -1)))

#define IX_ETH_DB_NPE_TO_PORT_ID(npe) (npe == 0 ? 2 : (npe == 1 ? 0 : (npe == 2 ? 1 : -1)))

/* temporary define - won't work for Azusa */
#define IX_ETH_DB_PORT_ID_TO_NPE_LOGICAL_ID(id) (IX_ETH_DB_PORT_ID_TO_NPE(id) << 4)
#define IX_ETH_DB_NPE_LOGICAL_ID_TO_PORT_ID(id) (IX_ETH_DB_NPE_TO_PORT_ID(id >> 4))

#define IX_IEEE803_MAC_ADDRESS_SIZE (6)

#define IX_IEEE802_1Q_QOS_PRIORITY_COUNT (8)

typedef enum /* IxEthDBStatus */
{
  IX_ETH_DB_SUCCESS = IX_SUCCESS,   /**< Success */
  IX_ETH_DB_FAIL = IX_FAIL,         /**< Failure */
  IX_ETH_DB_INVALID_PORT,           /**< Invalid port */
  IX_ETH_DB_PORT_UNINITIALIZED,     /**< Port not initialized */
  IX_ETH_DB_MAC_UNINITIALIZED,      /**< MAC not initialized */
  IX_ETH_DB_INVALID_ARG,            /**< Invalid argument */
  IX_ETH_DB_NO_SUCH_ADDR,           /**< Address not found for search or delete operations */
  IX_ETH_DB_NOMEM,                  /**< Learning database memory full */
  IX_ETH_DB_BUSY,                   /**< Learning database cannot complete operation, access temporarily blocked */
  IX_ETH_DB_END,                    /**< Database browser passed the end of the record set */
  IX_ETH_DB_INVALID_VLAN,           /**< Invalid VLAN ID (valid range is 0..4094, 0 signifies no VLAN membership, used for priority tagged frames) */
  IX_ETH_DB_INVALID_PRIORITY,       /**< Invalid QoS priority/traffic class (valid range for QoS priority is 0..7, valid range for traffic class depends on run-time configuration) */
  IX_ETH_DB_NO_PERMISSION,          /**< No permission for attempted operation */
  IX_ETH_DB_FEATURE_UNAVAILABLE,    /**< Feature not available (or not enabled) */
  IX_ETH_DB_INVALID_KEY,            /**< Invalid search key */
  IX_ETH_DB_INVALID_RECORD_TYPE     /**< Invalid record type */
} IxEthDBStatus;
    
/** @brief VLAN ID type, valid range is 0..4094, 0 signifying no VLAN membership */
typedef UINT32 IxEthDBVlanId;

/** @brief 802.1Q VLAN tag, contains 3 bits user priority, 1 bit CFI, 12 bits VLAN ID */
typedef UINT32 IxEthDBVlanTag;

/** @brief QoS priority/traffic class type, valid range is 0..7, 0 being the lowest */
typedef UINT32 IxEthDBPriority;

/** @brief Priority mapping table; 0..7 QoS priorities used to index, table contains traffic classes */
typedef UINT8 IxEthDBPriorityTable[8];

/** @brief A 4096 bit array used to map the complete VLAN ID range */
typedef UINT8 IxEthDBVlanSet[512];

#define IX_ETH_DB_802_1Q_VLAN_MASK (0xFFF)
#define IX_ETH_DB_802_1Q_QOS_MASK  (0x7)

#define IX_ETH_DB_802_1Q_MAX_VLAN_ID (0xFFE)

#define IX_ETH_DB_SET_VLAN_ID(vlanTag, vlanID) (((vlanTag) & 0xF000) | ((vlanID) & IX_ETH_DB_802_1Q_VLAN_MASK))

#define IX_ETH_DB_GET_VLAN_ID(vlanTag) ((vlanTag) & IX_ETH_DB_802_1Q_VLAN_MASK)

#define IX_ETH_DB_GET_QOS_PRIORITY(vlanTag) (((vlanTag) >> 13) & IX_ETH_DB_802_1Q_QOS_MASK)

#define IX_ETH_DB_SET_QOS_PRIORITY(vlanTag, priority) (((vlanTag) & 0x1FFF) | (((priority) & IX_ETH_DB_802_1Q_QOS_MASK) << 13))

#define IX_ETH_DB_CHECK_VLAN_TAG(vlanTag) { if(((vlanTag & 0xFFFF0000) != 0) || (IX_ETH_DB_GET_VLAN_ID(vlanTag) > 4094)) return IX_ETH_DB_INVALID_VLAN; }

#define IX_ETH_DB_CHECK_VLAN_ID(vlanId) { if (vlanId > IX_ETH_DB_802_1Q_MAX_VLAN_ID) return IX_ETH_DB_INVALID_VLAN; }

#define IX_IEEE802_1Q_VLAN_TPID (0x8100)
    
typedef enum
{
  IX_ETH_DB_UNTAGGED_FRAMES        = 0x1, /**< Accepts untagged frames */
  IX_ETH_DB_VLAN_TAGGED_FRAMES     = 0x2, /**< Accepts tagged frames */
  IX_ETH_DB_PRIORITY_TAGGED_FRAMES = 0x4, /**< Accepts tagged frames with VLAN ID set to 0 (no VLAN membership) */
  IX_ETH_DB_ACCEPT_ALL_FRAMES      = 
      IX_ETH_DB_UNTAGGED_FRAMES | IX_ETH_DB_VLAN_TAGGED_FRAMES /**< Accepts all the frames */
} IxEthDBFrameFilter;

typedef enum
{
  IX_ETH_DB_PASS_THROUGH = 0x1, /**< Leave frame as-is */
  IX_ETH_DB_ADD_TAG      = 0x2, /**< Add default port VLAN tag */
  IX_ETH_DB_REMOVE_TAG   = 0x3  /**< Remove VLAN tag from frame */
} IxEthDBTaggingAction;

typedef enum
{
  IX_ETH_DB_FIREWALL_WHITE_LIST = 0x1,  /**< Firewall operates in white-list mode (MAC address based admission) */
  IX_ETH_DB_FIREWALL_BLACK_LIST = 0x2   /**< Firewall operates in black-list mode (MAC address based blocking) */
} IxEthDBFirewallMode;
  
typedef enum
{
  IX_ETH_DB_FILTERING_RECORD        = 0x01, /**< <table><caption> Filtering record </caption> 
                                             *      <tr><td> MAC address <td> static/dynamic type <td> age 
                                             *   </table> 
                                             */
  IX_ETH_DB_FILTERING_VLAN_RECORD   = 0x02, /**< <table><caption> VLAN-enabled filtering record </caption>
                                             *      <tr><td> MAC address <td> static/dynamic type <td> age <td> 802.1Q tag 
                                             *   </table> 
                                             */
  IX_ETH_DB_WIFI_RECORD             = 0x04, /**< <table><caption> WiFi header conversion record </caption>
                                             *      <tr><td> MAC address <td> optional gateway MAC address <td> 
                                             *   </table>
                                             */
  IX_ETH_DB_FIREWALL_RECORD         = 0x08, /**< <table><caption> Firewall record </caption>
                                             *      <tr><td> MAC address 
                                             *   </table>
                                             */
  IX_ETH_DB_GATEWAY_RECORD          = 0x10, /**< <i>For internal use only</i> */
  IX_ETH_DB_MAX_RECORD_TYPE_INDEX   = 0x10, /**< <i>For internal use only</i> */
  IX_ETH_DB_NO_RECORD_TYPE          = 0,    /**< None of the registered record types */
  IX_ETH_DB_ALL_FILTERING_RECORDS   = IX_ETH_DB_FILTERING_RECORD | IX_ETH_DB_FILTERING_VLAN_RECORD, /**< All the filtering records */
  IX_ETH_DB_ALL_RECORD_TYPES        = IX_ETH_DB_FILTERING_RECORD | IX_ETH_DB_FILTERING_VLAN_RECORD |
      IX_ETH_DB_WIFI_RECORD | IX_ETH_DB_FIREWALL_RECORD /**< All the record types registered within EthDB */    
} IxEthDBRecordType;
  
typedef enum
{
  IX_ETH_DB_LEARNING                = 0x01, /**< Learning feature; enables EthDB to learn MAC address (filtering) records, including 802.1Q enabled records */
  IX_ETH_DB_FILTERING               = 0x02, /**< Filtering feature; enables EthDB to communicate with the NPEs for downloading filtering information in the NPEs; depends on the learning feature */
  IX_ETH_DB_VLAN_QOS                = 0x04, /**< VLAN/QoS feature; enables EthDB to configure NPEs to operate in VLAN/QoS aware modes */
  IX_ETH_DB_FIREWALL                = 0x08, /**< Firewall feature; enables EthDB to configure NPEs to operate in firewall mode, using white/black address lists */
  IX_ETH_DB_SPANNING_TREE_PROTOCOL  = 0x10, /**< Spanning tree protocol feature; enables EthDB to configure the NPEs as STP nodes */
  IX_ETH_DB_WIFI_HEADER_CONVERSION  = 0x20  /**< WiFi 802.3 to 802.11 header conversion feature; enables EthDB to handle WiFi conversion data */
} IxEthDBFeature;
  
typedef UINT32 IxEthDBProperty;  /**< Property ID type */

typedef enum
{
  IX_ETH_DB_INTEGER_PROPERTY  = 0x1, /**< 4 byte unsigned integer type */
  IX_ETH_DB_STRING_PROPERTY   = 0x2, /**< NULL-terminated string type of maximum 255 characters (including the terminator) */
  IX_ETH_DB_MAC_ADDR_PROPERTY = 0x3, /**< 6 byte MAC address type */
  IX_ETH_DB_BOOL_PROPERTY     = 0x4  /**< 4 byte boolean type; can contain only TRUE and FALSE values */
} IxEthDBPropertyType;

/* list of supported properties for the IX_ETH_DB_VLAN_QOS feature */
#define IX_ETH_DB_QOS_TRAFFIC_CLASS_COUNT_PROPERTY   (0x01)     /**< Property identifying number the supported number of traffic classes */
#define IX_ETH_DB_QOS_TRAFFIC_CLASS_0_RX_QUEUE_PROPERTY (0x10)  /**< Rx queue assigned to traffic class 0 */
#define IX_ETH_DB_QOS_TRAFFIC_CLASS_1_RX_QUEUE_PROPERTY (0x11)  /**< Rx queue assigned to traffic class 1 */
#define IX_ETH_DB_QOS_TRAFFIC_CLASS_2_RX_QUEUE_PROPERTY (0x12)  /**< Rx queue assigned to traffic class 2 */
#define IX_ETH_DB_QOS_TRAFFIC_CLASS_3_RX_QUEUE_PROPERTY (0x13)  /**< Rx queue assigned to traffic class 3 */
#define IX_ETH_DB_QOS_TRAFFIC_CLASS_4_RX_QUEUE_PROPERTY (0x14)  /**< Rx queue assigned to traffic class 4 */
#define IX_ETH_DB_QOS_TRAFFIC_CLASS_5_RX_QUEUE_PROPERTY (0x15)  /**< Rx queue assigned to traffic class 5 */
#define IX_ETH_DB_QOS_TRAFFIC_CLASS_6_RX_QUEUE_PROPERTY (0x16)  /**< Rx queue assigned to traffic class 6 */
#define IX_ETH_DB_QOS_TRAFFIC_CLASS_7_RX_QUEUE_PROPERTY (0x17)  /**< Rx queue assigned to traffic class 7 */

/* private property used by EthAcc to indicate queue configuration complete */
#define IX_ETH_DB_QOS_QUEUE_CONFIGURATION_COMPLETE (0x18)
      
typedef struct  
{
   UINT8 macAddress[IX_IEEE803_MAC_ADDRESS_SIZE];
} IxEthDBMacAddr;

typedef UINT32 IxEthDBPortId;

typedef UINT8 IxEthDBPortMap[32];
    
IX_ETH_DB_PUBLIC 
IxEthDBStatus ixEthDBInit(void);
 
IX_ETH_DB_PUBLIC
IxEthDBStatus ixEthDBUnload(void);

IX_ETH_DB_PUBLIC 
void ixEthDBPortInit(IxEthDBPortId portID);

IX_ETH_DB_PUBLIC 
IxEthDBStatus ixEthDBPortEnable(IxEthDBPortId portID);

IX_ETH_DB_PUBLIC 
IxEthDBStatus ixEthDBPortDisable(IxEthDBPortId portID);

IX_ETH_DB_PUBLIC 
IxEthDBStatus ixEthDBPortAddressSet(IxEthDBPortId portID, IxEthDBMacAddr *macAddr);

IX_ETH_DB_PUBLIC 
IxEthDBStatus ixEthDBFilteringPortMaximumFrameSizeSet(IxEthDBPortId portID, UINT32 maximumFrameSize);

IX_ETH_DB_PUBLIC 
IxEthDBStatus ixEthDBFilteringStaticEntryProvision(IxEthDBPortId portID, IxEthDBMacAddr *macAddr);

IX_ETH_DB_PUBLIC 
IxEthDBStatus ixEthDBFilteringDynamicEntryProvision(IxEthDBPortId portID, IxEthDBMacAddr *macAddr);

IX_ETH_DB_PUBLIC 
IxEthDBStatus ixEthDBFilteringEntryDelete(IxEthDBMacAddr *macAddr);

IX_ETH_DB_PUBLIC 
IxEthDBStatus ixEthDBFilteringPortSearch(IxEthDBPortId portID, IxEthDBMacAddr *macAddr);

IX_ETH_DB_PUBLIC 
IxEthDBStatus ixEthDBFilteringDatabaseSearch(IxEthDBPortId *portID, IxEthDBMacAddr *macAddr);

IX_ETH_DB_PUBLIC 
IxEthDBStatus ixEthDBFilteringPortUpdatingSearch(IxEthDBPortId *portID, IxEthDBMacAddr *macAddr);

#define IX_ETH_DB_MAINTENANCE_TIME (1 * 60) /* 1 Minute */

#define IX_ETH_DB_LEARNING_ENTRY_AGE_TIME (15 * 60 ) /* 15 Mins */

IX_ETH_DB_PUBLIC 
IxEthDBStatus ixEthDBPortAgingDisable(IxEthDBPortId portID);

IX_ETH_DB_PUBLIC 
IxEthDBStatus ixEthDBPortAgingEnable(IxEthDBPortId portID);

IX_ETH_DB_PUBLIC 
void ixEthDBDatabaseMaintenance(void);

IX_ETH_DB_PUBLIC 
IxEthDBStatus ixEthDBFilteringDatabaseShow(IxEthDBPortId portID);

IX_ETH_DB_PUBLIC 
void ixEthDBFilteringDatabaseShowAll(void);

IX_ETH_DB_PUBLIC 
IxEthDBStatus ixEthDBFilteringDatabaseShowRecords(IxEthDBPortId portID, IxEthDBRecordType recordFilter);

IX_ETH_DB_PUBLIC
IxEthDBStatus ixEthDBPortDependencyMapSet(IxEthDBPortId portID, IxEthDBPortMap dependencyPortMap);

IX_ETH_DB_PUBLIC
IxEthDBStatus ixEthDBPortDependencyMapGet(IxEthDBPortId portID, IxEthDBPortMap dependencyPortMap);

IX_ETH_DB_PUBLIC 
IxEthDBStatus ixEthDBPortVlanTagSet(IxEthDBPortId portID, IxEthDBVlanTag vlanTag);

IX_ETH_DB_PUBLIC 
IxEthDBStatus ixEthDBPortVlanTagGet(IxEthDBPortId portID, IxEthDBVlanTag *vlanTag);

IX_ETH_DB_PUBLIC 
IxEthDBStatus ixEthDBVlanTagSet(IxEthDBMacAddr *macAddr, IxEthDBVlanTag vlanTag);

IX_ETH_DB_PUBLIC 
IxEthDBStatus ixEthDBVlanTagGet(IxEthDBMacAddr *macAddr, IxEthDBVlanTag *vlanTag);

IX_ETH_DB_PUBLIC 
IxEthDBStatus ixEthDBPortVlanMembershipAdd(IxEthDBPortId portID, IxEthDBVlanId vlanID);

IX_ETH_DB_PUBLIC 
IxEthDBStatus ixEthDBPortVlanMembershipRangeAdd(IxEthDBPortId portID, IxEthDBVlanId vlanIDMin, IxEthDBVlanId vlanIDMax);

IX_ETH_DB_PUBLIC 
IxEthDBStatus ixEthDBPortVlanMembershipRemove(IxEthDBPortId portID, IxEthDBVlanId vlanID);

IX_ETH_DB_PUBLIC 
IxEthDBStatus ixEthDBPortVlanMembershipRangeRemove(IxEthDBPortId portID, IxEthDBVlanId vlanIDMin, IxEthDBVlanId vlanIDMax);

IX_ETH_DB_PUBLIC 
IxEthDBStatus ixEthDBPortVlanMembershipSet(IxEthDBPortId portID, IxEthDBVlanSet vlanSet);

IX_ETH_DB_PUBLIC 
IxEthDBStatus ixEthDBPortVlanMembershipGet(IxEthDBPortId portID, IxEthDBVlanSet vlanSet);

IX_ETH_DB_PUBLIC 
IxEthDBStatus ixEthDBAcceptableFrameTypeSet(IxEthDBPortId portID, IxEthDBFrameFilter frameFilter);

IX_ETH_DB_PUBLIC 
IxEthDBStatus ixEthDBAcceptableFrameTypeGet(IxEthDBPortId portID, IxEthDBFrameFilter *frameFilter);

IX_ETH_DB_PUBLIC 
IxEthDBStatus ixEthDBPriorityMappingTableSet(IxEthDBPortId portID, IxEthDBPriorityTable priorityTable);

IX_ETH_DB_PUBLIC 
IxEthDBStatus ixEthDBPriorityMappingTableGet(IxEthDBPortId portID, IxEthDBPriorityTable priorityTable);

IX_ETH_DB_PUBLIC 
IxEthDBStatus ixEthDBPriorityMappingClassSet(IxEthDBPortId portID, IxEthDBPriority userPriority, IxEthDBPriority trafficClass);

IX_ETH_DB_PUBLIC 
IxEthDBStatus ixEthDBPriorityMappingClassGet(IxEthDBPortId portID, IxEthDBPriority userPriority, IxEthDBPriority *trafficClass);

IX_ETH_DB_PUBLIC 
IxEthDBStatus ixEthDBEgressVlanEntryTaggingEnabledSet(IxEthDBPortId portID, IxEthDBVlanId vlanID, BOOL enabled);

IX_ETH_DB_PUBLIC 
IxEthDBStatus ixEthDBEgressVlanEntryTaggingEnabledGet(IxEthDBPortId portID, IxEthDBVlanId vlanID, BOOL *enabled);

IX_ETH_DB_PUBLIC 
IxEthDBStatus ixEthDBEgressVlanRangeTaggingEnabledSet(IxEthDBPortId portID, IxEthDBVlanId vlanIDMin, IxEthDBVlanId vlanIDMax, BOOL enabled);

IX_ETH_DB_PUBLIC 
IxEthDBStatus ixEthDBEgressVlanTaggingEnabledSet(IxEthDBPortId portID, IxEthDBVlanSet vlanSet);

IX_ETH_DB_PUBLIC 
IxEthDBStatus ixEthDBEgressVlanTaggingEnabledGet(IxEthDBPortId portID, IxEthDBVlanSet vlanSet);

IX_ETH_DB_PUBLIC 
IxEthDBStatus ixEthDBIngressVlanTaggingEnabledSet(IxEthDBPortId portID, IxEthDBTaggingAction taggingAction);

IX_ETH_DB_PUBLIC 
IxEthDBStatus ixEthDBIngressVlanTaggingEnabledGet(IxEthDBPortId portID, IxEthDBTaggingAction *taggingAction);

IX_ETH_DB_PUBLIC 
IxEthDBStatus ixEthDBVlanPortExtractionEnable(IxEthDBPortId portID, BOOL enable);

IX_ETH_DB_PUBLIC 
IxEthDBStatus ixEthDBFeatureCapabilityGet(IxEthDBPortId portID, IxEthDBFeature *featureSet);

IX_ETH_DB_PUBLIC 
IxEthDBStatus ixEthDBFeatureEnable(IxEthDBPortId portID, IxEthDBFeature feature, BOOL enabled);

IX_ETH_DB_PUBLIC 
IxEthDBStatus ixEthDBFeatureStatusGet(IxEthDBPortId portID, IxEthDBFeature feature, BOOL *present, BOOL *enabled);

IX_ETH_DB_PUBLIC 
IxEthDBStatus ixEthDBFeaturePropertyGet(IxEthDBPortId portID, IxEthDBFeature feature, IxEthDBProperty property, IxEthDBPropertyType *type, void *value);

IX_ETH_DB_PUBLIC 
IxEthDBStatus ixEthDBFeaturePropertySet(IxEthDBPortId portID, IxEthDBFeature feature, IxEthDBProperty property, void *value);

IX_ETH_DB_PUBLIC 
IxEthDBStatus ixEthDBDatabaseClear(IxEthDBPortId portID, IxEthDBRecordType recordType);

IX_ETH_DB_PUBLIC 
IxEthDBStatus ixEthDBWiFiStationEntryAdd(IxEthDBPortId portID, IxEthDBMacAddr *macAddr);

IX_ETH_DB_PUBLIC 
IxEthDBStatus ixEthDBWiFiAccessPointEntryAdd(IxEthDBPortId portID, IxEthDBMacAddr *macAddr, IxEthDBMacAddr *gatewayMacAddr);

IX_ETH_DB_PUBLIC 
IxEthDBStatus ixEthDBWiFiEntryRemove(IxEthDBPortId portID, IxEthDBMacAddr *macAddr);

IX_ETH_DB_PUBLIC 
IxEthDBStatus ixEthDBWiFiConversionTableDownload(IxEthDBPortId portID);

IX_ETH_DB_PUBLIC 
IxEthDBStatus ixEthDBWiFiFrameControlSet(IxEthDBPortId portID, UINT16 frameControl);

IX_ETH_DB_PUBLIC 
IxEthDBStatus ixEthDBWiFiDurationIDSet(IxEthDBPortId portID, UINT16 durationID);

IX_ETH_DB_PUBLIC 
IxEthDBStatus ixEthDBWiFiBBSIDSet(IxEthDBPortId portID, IxEthDBMacAddr *bbsid);

IX_ETH_DB_PUBLIC 
IxEthDBStatus ixEthDBSpanningTreeBlockingStateSet(IxEthDBPortId portID, BOOL blocked);

IX_ETH_DB_PUBLIC 
IxEthDBStatus ixEthDBSpanningTreeBlockingStateGet(IxEthDBPortId portID, BOOL *blocked);

IX_ETH_DB_PUBLIC 
IxEthDBStatus ixEthDBFirewallModeSet(IxEthDBPortId portID, IxEthDBFirewallMode mode);

IX_ETH_DB_PUBLIC 
IxEthDBStatus ixEthDBFirewallInvalidAddressFilterEnable(IxEthDBPortId portID, BOOL enable);

IX_ETH_DB_PUBLIC 
IxEthDBStatus ixEthDBFirewallEntryAdd(IxEthDBPortId portID, IxEthDBMacAddr *macAddr);

IX_ETH_DB_PUBLIC 
IxEthDBStatus ixEthDBFirewallEntryRemove(IxEthDBPortId portID, IxEthDBMacAddr *macAddr);

IX_ETH_DB_PUBLIC 
IxEthDBStatus ixEthDBFirewallTableDownload(IxEthDBPortId portID);

IX_ETH_DB_PUBLIC 
IxEthDBStatus ixEthDBUserFieldSet(IxEthDBRecordType recordType, IxEthDBMacAddr *macAddr, IxEthDBPortId portID, IxEthDBVlanId vlanID, void *field);

IX_ETH_DB_PUBLIC 
IxEthDBStatus ixEthDBUserFieldGet(IxEthDBRecordType recordType, IxEthDBMacAddr *macAddr, IxEthDBPortId portId, IxEthDBVlanId vlanID, void **field);


#endif /* IxEthDB_H */
