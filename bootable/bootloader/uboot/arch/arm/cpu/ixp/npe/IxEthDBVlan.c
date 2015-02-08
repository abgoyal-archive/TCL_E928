

#include "IxEthDB.h"
#include "IxEthDB_p.h"

/* forward prototypes */
IX_ETH_DB_PUBLIC
IxEthDBStatus ixEthDBUpdateTrafficClass(IxEthDBPortId portID, UINT32 classIndex);
IX_ETH_DB_PUBLIC
IxEthDBStatus ixEthDBVlanTableGet(IxEthDBPortId portID, IxEthDBVlanSet portVlanTable, IxEthDBVlanSet vlanSet);

/* contants used by various functions as "action" parameter */
#define ADD_VLAN    (0x1)
#define REMOVE_VLAN (0x2)

IX_ETH_DB_PRIVATE
void ixEthDBLocalVlanMembershipChange(UINT32 vlanID, IxEthDBVlanSet table, UINT32 action)
{
    UINT32 setOffset;
    
    /* add/remove VID to membership table */
    setOffset = VLAN_SET_OFFSET(vlanID); /* we need 9 bits to index the 512 byte membership array */

    if (action == ADD_VLAN)
    {
        table[setOffset] |= 1 << VLAN_SET_MASK(vlanID);
    }
    else if (action == REMOVE_VLAN)
    {
        table[setOffset] &= ~(1 << VLAN_SET_MASK(vlanID));
    }
}

IX_ETH_DB_PRIVATE
IxEthDBStatus ixEthDBVlanTableEntryUpdate(IxEthDBPortId portID, UINT32 setOffset)
{
    PortInfo *portInfo = &ixEthDBPortInfo[portID];
    IxNpeMhMessage message;
    IX_STATUS result;
        
    FILL_SETPORTVLANTABLEENTRY_MSG(message, IX_ETH_DB_PORT_ID_TO_NPE_LOGICAL_ID(portID), 
        2 * setOffset, 
        portInfo->vlanMembership[setOffset], 
        portInfo->transmitTaggingInfo[setOffset]);
    
    IX_ETHDB_SEND_NPE_MSG(IX_ETH_DB_PORT_ID_TO_NPE(portID), message, result);
    
    return result;
}

IX_ETH_DB_PRIVATE
IxEthDBStatus ixEthDBVlanTableRangeUpdate(IxEthDBPortId portID)
{
    PortInfo *portInfo    = &ixEthDBPortInfo[portID];
    UINT8 *vlanUpdateZone = (UINT8 *) portInfo->updateMethod.vlanUpdateZone;
    IxNpeMhMessage message;
    UINT32 setIndex;
    IX_STATUS result;

    /* copy membership info and transmit tagging into into exchange area */
    for (setIndex = 0 ; setIndex < sizeof (portInfo->vlanMembership) ; setIndex++)
    {
        /* membership and TTI data are interleaved */
        vlanUpdateZone[setIndex * 2]     = portInfo->vlanMembership[setIndex];
        vlanUpdateZone[setIndex * 2 + 1] = portInfo->transmitTaggingInfo[setIndex];
    }

    IX_OSAL_CACHE_FLUSH(vlanUpdateZone, FULL_VLAN_BYTE_SIZE);
    
    /* build NPE message */
    FILL_SETPORTVLANTABLERANGE_MSG(message, IX_ETH_DB_PORT_ID_TO_NPE_LOGICAL_ID(portID), 0, 0, 
        IX_OSAL_MMU_VIRT_TO_PHYS(vlanUpdateZone));

    /* send message */    
    IX_ETHDB_SEND_NPE_MSG(IX_ETH_DB_PORT_ID_TO_NPE(portID), message, result);

    return result;
}

IX_ETH_DB_PRIVATE
IxEthDBStatus ixEthDBPortVlanMembershipChange(IxEthDBPortId portID, IxEthDBVlanId vlanID, IxEthDBVlanSet table, UINT32 action)
{
    /* change VLAN in local membership table */
    ixEthDBLocalVlanMembershipChange(vlanID, table, action);
    
    /* send updated entry to NPE */
    return ixEthDBVlanTableEntryUpdate(portID, VLAN_SET_OFFSET(vlanID));
}

IX_ETH_DB_PUBLIC 
IxEthDBStatus ixEthDBPortVlanTagSet(IxEthDBPortId portID, IxEthDBVlanTag vlanTag)
{
    IxNpeMhMessage message;
    IX_STATUS result;
    
    IX_ETH_DB_CHECK_PORT(portID);
    
    IX_ETH_DB_CHECK_SINGLE_NPE(portID);
 
    IX_ETH_DB_CHECK_VLAN_TAG(vlanTag);
    
    IX_ETH_DB_CHECK_FEATURE(portID, IX_ETH_DB_VLAN_QOS);
        
    /* add VLAN ID to local membership table */
    ixEthDBPortVlanMembershipChange(portID, 
        vlanTag & IX_ETH_DB_802_1Q_VLAN_MASK, 
        ixEthDBPortInfo[portID].vlanMembership, 
        ADD_VLAN);
        
    /* set tag in portInfo */
    ixEthDBPortInfo[portID].vlanTag = vlanTag;
    
    /* build VLAN_SetDefaultRxVID message */
    FILL_SETDEFAULTRXVID_MSG(message, 
        IX_ETH_DB_PORT_ID_TO_NPE_LOGICAL_ID(portID), 
        IX_IEEE802_1Q_VLAN_TPID, 
        vlanTag);
    
    IX_ETHDB_SEND_NPE_MSG(IX_ETH_DB_PORT_ID_TO_NPE(portID), message, result);
    
    return result;
}

IX_ETH_DB_PUBLIC 
IxEthDBStatus ixEthDBPortVlanTagGet(IxEthDBPortId portID, IxEthDBVlanTag *vlanTag)
{
    IX_ETH_DB_CHECK_PORT(portID);
    
    IX_ETH_DB_CHECK_SINGLE_NPE(portID);
    
    IX_ETH_DB_CHECK_FEATURE(portID, IX_ETH_DB_VLAN_QOS);
    
    IX_ETH_DB_CHECK_REFERENCE(vlanTag);
    
    *vlanTag = ixEthDBPortInfo[portID].vlanTag;
    
    return IX_ETH_DB_SUCCESS;
}

IX_ETH_DB_PUBLIC 
IxEthDBStatus ixEthDBVlanTagSet(IxEthDBMacAddr *macAddr, IxEthDBVlanTag vlanTag)
{
    HashNode *searchResult;
    MacDescriptor *descriptor;
    
    IX_ETH_DB_CHECK_REFERENCE(macAddr);
    
    IX_ETH_DB_CHECK_VLAN_TAG(vlanTag);
    
    searchResult = ixEthDBSearch(macAddr, IX_ETH_DB_ALL_FILTERING_RECORDS);
    
    if (searchResult == NULL)
    {
        return IX_ETH_DB_NO_SUCH_ADDR;
    }
    
    descriptor = (MacDescriptor *) searchResult->data;
    
    /* set record type to VLAN if not already set */
    descriptor->type = IX_ETH_DB_FILTERING_VLAN_RECORD;
    
    /* add vlan tag */
    descriptor->recordData.filteringVlanData.ieee802_1qTag = vlanTag;
    
    /* transaction completed */
    ixEthDBReleaseHashNode(searchResult);
    
    return IX_ETH_DB_SUCCESS;
}

IX_ETH_DB_PUBLIC 
IxEthDBStatus ixEthDBVlanTagGet(IxEthDBMacAddr *macAddr, IxEthDBVlanTag *vlanTag)
{
    HashNode *searchResult;
    MacDescriptor *descriptor;
    
    IX_ETH_DB_CHECK_REFERENCE(macAddr);
    
    IX_ETH_DB_CHECK_REFERENCE(vlanTag);
    
    searchResult = ixEthDBSearch(macAddr, IX_ETH_DB_FILTERING_VLAN_RECORD);
    
    if (searchResult == NULL)
    {
        return IX_ETH_DB_NO_SUCH_ADDR;
    }
    
    descriptor = (MacDescriptor *) searchResult->data;
        
    /* get vlan tag */
    *vlanTag = descriptor->recordData.filteringVlanData.ieee802_1qTag;
    
    /* transaction completed */
    ixEthDBReleaseHashNode(searchResult);
    
    return IX_ETH_DB_SUCCESS;
}

IX_ETH_DB_PUBLIC 
IxEthDBStatus ixEthDBPortVlanMembershipAdd(IxEthDBPortId portID, IxEthDBVlanId vlanID)
{
    IX_ETH_DB_CHECK_PORT(portID);

    IX_ETH_DB_CHECK_SINGLE_NPE(portID);

    IX_ETH_DB_CHECK_VLAN_ID(vlanID);

    IX_ETH_DB_CHECK_FEATURE(portID, IX_ETH_DB_VLAN_QOS);

    return ixEthDBPortVlanMembershipChange(portID, vlanID, ixEthDBPortInfo[portID].vlanMembership, ADD_VLAN);
}

IX_ETH_DB_PUBLIC 
IxEthDBStatus ixEthDBPortVlanMembershipRemove(IxEthDBPortId portID, IxEthDBVlanId vlanID)
{
    IX_ETH_DB_CHECK_PORT(portID);

    IX_ETH_DB_CHECK_SINGLE_NPE(portID);

    IX_ETH_DB_CHECK_FEATURE(portID, IX_ETH_DB_VLAN_QOS);

    IX_ETH_DB_CHECK_VLAN_ID(vlanID);

    /* for safety isolate only the VLAN ID in the tag (the lower 12 bits) */
    vlanID = vlanID & IX_ETH_DB_802_1Q_VLAN_MASK;
    
    /* check we're not asked to remove the default port VID */
    if (vlanID == IX_ETH_DB_GET_VLAN_ID(ixEthDBPortInfo[portID].vlanTag))
    {
        return IX_ETH_DB_NO_PERMISSION;
    }
    
    return ixEthDBPortVlanMembershipChange(portID, vlanID, ixEthDBPortInfo[portID].vlanMembership, REMOVE_VLAN);
}

IX_ETH_DB_PRIVATE
IxEthDBStatus ixEthDBPortVlanMembershipRangeChange(IxEthDBPortId portID, IxEthDBVlanId vlanIDMin, IxEthDBVlanId vlanIDMax, IxEthDBVlanSet table, UINT32 action)
{
    UINT32 setOffsetMin, setOffsetMax;
    
    IX_ETH_DB_CHECK_PORT(portID);
    
    IX_ETH_DB_CHECK_SINGLE_NPE(portID);
    
    IX_ETH_DB_CHECK_FEATURE(portID, IX_ETH_DB_VLAN_QOS);
    
    IX_ETH_DB_CHECK_VLAN_ID(vlanIDMin);
    
    IX_ETH_DB_CHECK_VLAN_ID(vlanIDMax);
    
    /* for safety isolate only the VLAN ID in the tags (the lower 12 bits) */
    vlanIDMin = vlanIDMin & IX_ETH_DB_802_1Q_VLAN_MASK;
    vlanIDMax = vlanIDMax & IX_ETH_DB_802_1Q_VLAN_MASK;
    
    /* is this a range? */
    if (vlanIDMax < vlanIDMin)
    {
        return IX_ETH_DB_INVALID_VLAN;
    }
    
    /* check that we're not specifically asked to remove the default port VID */
    if (action == REMOVE_VLAN && vlanIDMax == vlanIDMin && IX_ETH_DB_GET_VLAN_ID(ixEthDBPortInfo[portID].vlanTag) == vlanIDMin)
    {
        return IX_ETH_DB_NO_PERMISSION;
    }
    
    /* compute set offsets */
    setOffsetMin = VLAN_SET_OFFSET(vlanIDMin);
    setOffsetMax = VLAN_SET_OFFSET(vlanIDMax);

    /* change VLAN range */
    for (; vlanIDMin <= vlanIDMax ; vlanIDMin++)
    {
        /* change vlan in local membership table */
        ixEthDBLocalVlanMembershipChange(vlanIDMin, table, action);
    }

    /* if the range is within one set (max 8 VLANs in one table byte) we can just update that entry in the NPE */
    if (setOffsetMin == setOffsetMax)
    {
        /* send updated entry to NPE */
        return ixEthDBVlanTableEntryUpdate(portID, setOffsetMin);
    }
    else
    {
        /* update a zone of the membership/transmit tag info table */
        return ixEthDBVlanTableRangeUpdate(portID);
    }
}

IX_ETH_DB_PUBLIC 
IxEthDBStatus ixEthDBPortVlanMembershipRangeAdd(IxEthDBPortId portID, IxEthDBVlanId vlanIDMin, IxEthDBVlanId vlanIDMax)
{
    IX_ETH_DB_CHECK_PORT(portID);

    IX_ETH_DB_CHECK_SINGLE_NPE(portID);

    return ixEthDBPortVlanMembershipRangeChange(portID, vlanIDMin, vlanIDMax, ixEthDBPortInfo[portID].vlanMembership, ADD_VLAN);
}

IX_ETH_DB_PUBLIC 
IxEthDBStatus ixEthDBPortVlanMembershipRangeRemove(IxEthDBPortId portID, IxEthDBVlanId vlanIDMin, IxEthDBVlanId vlanIDMax)
{
    IX_ETH_DB_CHECK_PORT(portID);

    IX_ETH_DB_CHECK_SINGLE_NPE(portID);

    return ixEthDBPortVlanMembershipRangeChange(portID, vlanIDMin, vlanIDMax, ixEthDBPortInfo[portID].vlanMembership, REMOVE_VLAN);
}

IX_ETH_DB_PUBLIC
IxEthDBStatus ixEthDBPortVlanTableSet(IxEthDBPortId portID, IxEthDBVlanSet portVlanTable, IxEthDBVlanSet vlanSet)
{
    IX_ETH_DB_CHECK_PORT(portID);
    
    IX_ETH_DB_CHECK_SINGLE_NPE(portID);
    
    IX_ETH_DB_CHECK_FEATURE(portID, IX_ETH_DB_VLAN_QOS);
    
    IX_ETH_DB_CHECK_REFERENCE(vlanSet);

    memcpy(portVlanTable, vlanSet, sizeof (IxEthDBVlanSet));
    
    return ixEthDBVlanTableRangeUpdate(portID);
}

IX_ETH_DB_PUBLIC
IxEthDBStatus ixEthDBVlanTableGet(IxEthDBPortId portID, IxEthDBVlanSet portVlanTable, IxEthDBVlanSet vlanSet)
{
    IX_ETH_DB_CHECK_PORT(portID);
    
    IX_ETH_DB_CHECK_SINGLE_NPE(portID);
    
    IX_ETH_DB_CHECK_FEATURE(portID, IX_ETH_DB_VLAN_QOS);
    
    IX_ETH_DB_CHECK_REFERENCE(vlanSet);
    
    memcpy(vlanSet, portVlanTable, sizeof (IxEthDBVlanSet));
    
    return IX_ETH_DB_SUCCESS;
}

IX_ETH_DB_PUBLIC 
IxEthDBStatus ixEthDBPortVlanMembershipSet(IxEthDBPortId portID, IxEthDBVlanSet vlanSet)
{
    IxEthDBVlanId vlanID;

    IX_ETH_DB_CHECK_PORT(portID);
    
    IX_ETH_DB_CHECK_SINGLE_NPE(portID);

    IX_ETH_DB_CHECK_REFERENCE(vlanSet);

    /* set the bit corresponding to the PVID just in case */
    vlanID = IX_ETH_DB_GET_VLAN_ID(ixEthDBPortInfo[portID].vlanTag);
    vlanSet[VLAN_SET_OFFSET(vlanID)] |= 1 << VLAN_SET_MASK(vlanID);
    
    return ixEthDBPortVlanTableSet(portID, ixEthDBPortInfo[portID].vlanMembership, vlanSet);
}

IX_ETH_DB_PUBLIC 
IxEthDBStatus ixEthDBPortVlanMembershipGet(IxEthDBPortId portID, IxEthDBVlanSet vlanSet)
{
    IX_ETH_DB_CHECK_PORT(portID);
    
    IX_ETH_DB_CHECK_SINGLE_NPE(portID);
    
    return ixEthDBVlanTableGet(portID, ixEthDBPortInfo[portID].vlanMembership, vlanSet);
}

IX_ETH_DB_PUBLIC 
IxEthDBStatus ixEthDBEgressVlanEntryTaggingEnabledSet(IxEthDBPortId portID, IxEthDBVlanId vlanID, BOOL enabled)
{
    IX_ETH_DB_CHECK_PORT(portID);
    
    IX_ETH_DB_CHECK_SINGLE_NPE(portID);

    IX_ETH_DB_CHECK_VLAN_ID(vlanID);

    IX_ETH_DB_CHECK_FEATURE(portID, IX_ETH_DB_VLAN_QOS);

    return ixEthDBPortVlanMembershipChange(portID, vlanID, ixEthDBPortInfo[portID].transmitTaggingInfo, enabled? ADD_VLAN : REMOVE_VLAN);
}

IX_ETH_DB_PUBLIC 
IxEthDBStatus ixEthDBEgressVlanEntryTaggingEnabledGet(IxEthDBPortId portID, IxEthDBVlanId vlanID, BOOL *enabled)
{
    IX_ETH_DB_CHECK_PORT(portID);
    
    IX_ETH_DB_CHECK_SINGLE_NPE(portID);
    
    IX_ETH_DB_CHECK_FEATURE(portID, IX_ETH_DB_VLAN_QOS);
    
    IX_ETH_DB_CHECK_REFERENCE(enabled);

    IX_ETH_DB_CHECK_VLAN_ID(vlanID);
    
    *enabled = ((ixEthDBPortInfo[portID].transmitTaggingInfo[VLAN_SET_OFFSET(vlanID)] & (1 << VLAN_SET_MASK(vlanID))) != 0);
    
    return IX_ETH_DB_SUCCESS;
}

IX_ETH_DB_PUBLIC 
IxEthDBStatus ixEthDBEgressVlanRangeTaggingEnabledSet(IxEthDBPortId portID, IxEthDBVlanId vlanIDMin, IxEthDBVlanId vlanIDMax, BOOL enabled)
{
    IX_ETH_DB_CHECK_PORT(portID);
    
    IX_ETH_DB_CHECK_SINGLE_NPE(portID);
    
    return ixEthDBPortVlanMembershipRangeChange(portID, vlanIDMin, vlanIDMax, ixEthDBPortInfo[portID].transmitTaggingInfo, enabled? ADD_VLAN : REMOVE_VLAN);
}

IX_ETH_DB_PUBLIC 
IxEthDBStatus ixEthDBEgressVlanTaggingEnabledSet(IxEthDBPortId portID, IxEthDBVlanSet vlanSet)
{
    IxEthDBVlanId vlanID;

    IX_ETH_DB_CHECK_PORT(portID);
    
    IX_ETH_DB_CHECK_SINGLE_NPE(portID);

    IX_ETH_DB_CHECK_REFERENCE(vlanSet);

    /* set the PVID bit just in case */
    vlanID = IX_ETH_DB_GET_VLAN_ID(ixEthDBPortInfo[portID].vlanTag);
    vlanSet[VLAN_SET_OFFSET(vlanID)] |= 1 << VLAN_SET_MASK(vlanID);
    
    return ixEthDBPortVlanTableSet(portID, ixEthDBPortInfo[portID].transmitTaggingInfo, vlanSet);
}

IX_ETH_DB_PUBLIC 
IxEthDBStatus ixEthDBEgressVlanTaggingEnabledGet(IxEthDBPortId portID, IxEthDBVlanSet vlanSet)
{
    IX_ETH_DB_CHECK_PORT(portID);
    
    IX_ETH_DB_CHECK_SINGLE_NPE(portID);
    
    return ixEthDBVlanTableGet(portID, ixEthDBPortInfo[portID].transmitTaggingInfo, vlanSet);
}

IX_ETH_DB_PRIVATE
IxEthDBStatus ixEthDBIngressVlanModeUpdate(IxEthDBPortId portID)
{
    PortInfo *portInfo = &ixEthDBPortInfo[portID];
    IxNpeMhMessage message;
    IX_STATUS result;

    FILL_SETRXTAGMODE_MSG(message, portID, portInfo->npeFrameFilter, portInfo->npeTaggingAction);
    IX_ETHDB_SEND_NPE_MSG(IX_ETH_DB_PORT_ID_TO_NPE(portID), message, result);

    return result;
}

IX_ETH_DB_PUBLIC 
IxEthDBStatus ixEthDBIngressVlanTaggingEnabledSet(IxEthDBPortId portID, IxEthDBTaggingAction taggingAction)
{
    PortInfo *portInfo;
    
    IX_ETH_DB_CHECK_PORT(portID);
    
    IX_ETH_DB_CHECK_SINGLE_NPE(portID);
    
    IX_ETH_DB_CHECK_FEATURE(portID, IX_ETH_DB_VLAN_QOS);
    
    portInfo = &ixEthDBPortInfo[portID];
    
    if (taggingAction == IX_ETH_DB_PASS_THROUGH)
    {
        portInfo->npeTaggingAction = 0x00;
    }
    else if (taggingAction == IX_ETH_DB_ADD_TAG)
    {
        portInfo->npeTaggingAction = 0x02;
    }
    else if (taggingAction == IX_ETH_DB_REMOVE_TAG)
    {
        portInfo->npeTaggingAction = 0x01;
    }
    else
    {
        return IX_ETH_DB_INVALID_ARG;
    }
    
    portInfo->taggingAction = taggingAction;
    
    return ixEthDBIngressVlanModeUpdate(portID);
}

IX_ETH_DB_PUBLIC 
IxEthDBStatus ixEthDBIngressVlanTaggingEnabledGet(IxEthDBPortId portID, IxEthDBTaggingAction *taggingAction)
{
    IX_ETH_DB_CHECK_PORT(portID);
    
    IX_ETH_DB_CHECK_SINGLE_NPE(portID);
    
    IX_ETH_DB_CHECK_FEATURE(portID, IX_ETH_DB_VLAN_QOS);

    IX_ETH_DB_CHECK_REFERENCE(taggingAction);
    
    *taggingAction = ixEthDBPortInfo[portID].taggingAction;
    
    return IX_ETH_DB_SUCCESS;
}

IX_ETH_DB_PUBLIC 
IxEthDBStatus ixEthDBAcceptableFrameTypeSet(IxEthDBPortId portID, IxEthDBFrameFilter frameFilter)
{
    PortInfo *portInfo;
    IxEthDBStatus result = IX_ETH_DB_SUCCESS;
        
    IX_ETH_DB_CHECK_PORT(portID);
    
    IX_ETH_DB_CHECK_SINGLE_NPE(portID);
    
    IX_ETH_DB_CHECK_FEATURE(portID, IX_ETH_DB_VLAN_QOS);
    
    /* check parameter range 
       the ORed value of the valid values is 0x7
       a value having extra bits is invalid */
    if ((frameFilter | 0x7) != 0x7 || frameFilter == 0)
    {
        return IX_ETH_DB_INVALID_ARG;
    }
    
    portInfo = &ixEthDBPortInfo[portID];
    
    portInfo->frameFilter    = frameFilter;
    portInfo->npeFrameFilter = 0; /* allow all by default */
    
    /* if accepting priority tagged but not all VLAN tagged
       set the membership table to contain only VLAN ID 0 
       hence remove vlans 1-4094 and add VLAN ID 0 */
    if (((frameFilter & IX_ETH_DB_PRIORITY_TAGGED_FRAMES) != 0)
        && ((frameFilter & IX_ETH_DB_VLAN_TAGGED_FRAMES) == 0))
    {
        result = ixEthDBPortVlanMembershipRangeChange(portID, 
            1, IX_ETH_DB_802_1Q_MAX_VLAN_ID, portInfo->vlanMembership, REMOVE_VLAN);

        if (result == IX_ETH_DB_SUCCESS)
        {
            ixEthDBLocalVlanMembershipChange(0, portInfo->vlanMembership, ADD_VLAN);
            result = ixEthDBVlanTableRangeUpdate(portID);
        }
    }
    
    /* untagged only? */
    if (frameFilter == IX_ETH_DB_UNTAGGED_FRAMES)
    {
        portInfo->npeFrameFilter = 0x01;
    }
    
    /* tagged only? */
    if ((frameFilter & IX_ETH_DB_UNTAGGED_FRAMES) == 0)
    {
        portInfo->npeFrameFilter = 0x02;
    }

    if (result == IX_ETH_DB_SUCCESS)
    {
        result = ixEthDBIngressVlanModeUpdate(portID);
    }

    return result;
}

IX_ETH_DB_PUBLIC 
IxEthDBStatus ixEthDBAcceptableFrameTypeGet(IxEthDBPortId portID, IxEthDBFrameFilter *frameFilter)
{
    IX_ETH_DB_CHECK_PORT(portID);
    
    IX_ETH_DB_CHECK_SINGLE_NPE(portID);
    
    IX_ETH_DB_CHECK_FEATURE(portID, IX_ETH_DB_VLAN_QOS);
    
    IX_ETH_DB_CHECK_REFERENCE(frameFilter);
    
    *frameFilter = ixEthDBPortInfo[portID].frameFilter;
    
    return IX_ETH_DB_SUCCESS;
}

IX_ETH_DB_PUBLIC
IxEthDBStatus ixEthDBUpdateTrafficClass(IxEthDBPortId portID, UINT32 classIndex)
{
    IxNpeMhMessage message;
    IX_STATUS result;

    UINT32 trafficClass = ixEthDBPortInfo[portID].priorityTable[classIndex];
    UINT32 aqmQueue     = ixEthDBPortInfo[portID].ixEthDBTrafficClassAQMAssignments[trafficClass];
    
    FILL_SETRXQOSENTRY(message, IX_ETH_DB_PORT_ID_TO_NPE_LOGICAL_ID(portID), classIndex, trafficClass, aqmQueue);
    
    IX_ETHDB_SEND_NPE_MSG(IX_ETH_DB_PORT_ID_TO_NPE(portID), message, result);
    
    return result;
}

IX_ETH_DB_PUBLIC 
IxEthDBStatus ixEthDBPriorityMappingTableSet(IxEthDBPortId portID, IxEthDBPriorityTable priorityTable)
{
    UINT32 classIndex;
    
    IX_ETH_DB_CHECK_PORT(portID);
    
    IX_ETH_DB_CHECK_SINGLE_NPE(portID);
    
    IX_ETH_DB_CHECK_FEATURE(portID, IX_ETH_DB_VLAN_QOS);
    
    IX_ETH_DB_CHECK_REFERENCE(priorityTable);
           
    for (classIndex = 0 ; classIndex < IX_IEEE802_1Q_QOS_PRIORITY_COUNT ; classIndex++)
    {
        /* check range */
        if (priorityTable[classIndex] >= ixEthDBPortInfo[portID].ixEthDBTrafficClassCount)
        {
            return IX_ETH_DB_INVALID_PRIORITY;
        }
    }
    
    /* set new traffic classes */
    for (classIndex = 0 ; classIndex < IX_IEEE802_1Q_QOS_PRIORITY_COUNT ; classIndex++)
    {
        ixEthDBPortInfo[portID].priorityTable[classIndex] = priorityTable[classIndex];
        
        if (ixEthDBUpdateTrafficClass(portID, classIndex) != IX_ETH_DB_SUCCESS)
        {
            return IX_ETH_DB_FAIL;
        }
    }
    
    return IX_ETH_DB_SUCCESS;
 }

IX_ETH_DB_PUBLIC 
IxEthDBStatus ixEthDBPriorityMappingTableGet(IxEthDBPortId portID, IxEthDBPriorityTable priorityTable)
{
    IX_ETH_DB_CHECK_PORT(portID);
    
    IX_ETH_DB_CHECK_SINGLE_NPE(portID);
    
    IX_ETH_DB_CHECK_FEATURE(portID, IX_ETH_DB_VLAN_QOS);
    
    IX_ETH_DB_CHECK_REFERENCE(priorityTable);
    
    memcpy(priorityTable, ixEthDBPortInfo[portID].priorityTable, sizeof (IxEthDBPriorityTable));
    
    return IX_ETH_DB_SUCCESS;
}

IX_ETH_DB_PUBLIC 
IxEthDBStatus ixEthDBPriorityMappingClassSet(IxEthDBPortId portID, IxEthDBPriority userPriority, IxEthDBPriority trafficClass)
{
    IX_ETH_DB_CHECK_PORT(portID);
    
    IX_ETH_DB_CHECK_SINGLE_NPE(portID);
    
    IX_ETH_DB_CHECK_FEATURE(portID, IX_ETH_DB_VLAN_QOS);

    /* check ranges for userPriority and trafficClass */
    if (userPriority >= IX_IEEE802_1Q_QOS_PRIORITY_COUNT || trafficClass >= ixEthDBPortInfo[portID].ixEthDBTrafficClassCount)
    {
        return IX_ETH_DB_INVALID_PRIORITY;
    }
    
    ixEthDBPortInfo[portID].priorityTable[userPriority] = trafficClass;
    
    return ixEthDBUpdateTrafficClass(portID, userPriority);
}

IX_ETH_DB_PUBLIC 
IxEthDBStatus ixEthDBPriorityMappingClassGet(IxEthDBPortId portID, IxEthDBPriority userPriority, IxEthDBPriority *trafficClass)
{
    IX_ETH_DB_CHECK_PORT(portID);
    
    IX_ETH_DB_CHECK_SINGLE_NPE(portID);
    
    IX_ETH_DB_CHECK_FEATURE(portID, IX_ETH_DB_VLAN_QOS);
    
    IX_ETH_DB_CHECK_REFERENCE(trafficClass);
    
    /* check userPriority range */
    if (userPriority >= IX_IEEE802_1Q_QOS_PRIORITY_COUNT)
    {
        return IX_ETH_DB_INVALID_PRIORITY;
    }
    
    *trafficClass = ixEthDBPortInfo[portID].priorityTable[userPriority];
    
    return IX_ETH_DB_SUCCESS;
}

IX_ETH_DB_PUBLIC 
IxEthDBStatus ixEthDBVlanPortExtractionEnable(IxEthDBPortId portID, BOOL enable)
{
    IxNpeMhMessage message;
    IX_STATUS result;

    IX_ETH_DB_CHECK_PORT(portID);
    
    IX_ETH_DB_CHECK_SINGLE_NPE(portID);
    
    IX_ETH_DB_CHECK_FEATURE(portID, IX_ETH_DB_VLAN_QOS);

    FILL_SETPORTIDEXTRACTIONMODE(message, portID, enable);

    IX_ETHDB_SEND_NPE_MSG(IX_ETH_DB_PORT_ID_TO_NPE(portID), message, result);
    
    return result;
}
