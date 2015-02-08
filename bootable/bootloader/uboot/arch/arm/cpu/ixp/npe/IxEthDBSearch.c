

#include "IxEthDB_p.h"

extern HashTable dbHashtable;

IX_ETH_DB_PUBLIC
BOOL ixEthDBAddressRecordMatch(void *untypedReference, void *untypedEntry)
{
    MacDescriptor *entry     = (MacDescriptor *) untypedEntry;
    MacDescriptor *reference = (MacDescriptor *) untypedReference;
    
    /* check accepted record types */
    if ((entry->type & reference->type) == 0) return FALSE;
       
    return (ixEthDBAddressCompare((UINT8 *) entry->macAddress, (UINT8 *) reference->macAddress) == 0);
}

IX_ETH_DB_PUBLIC
BOOL ixEthDBVlanRecordMatch(void *untypedReference, void *untypedEntry)
{
    MacDescriptor *entry     = (MacDescriptor *) untypedEntry;
    MacDescriptor *reference = (MacDescriptor *) untypedReference;
    
    /* check accepted record types */
    if ((entry->type & reference->type) == 0) return FALSE;
    
    return (IX_ETH_DB_GET_VLAN_ID(entry->recordData.filteringVlanData.ieee802_1qTag) ==
        IX_ETH_DB_GET_VLAN_ID(reference->recordData.filteringVlanData.ieee802_1qTag)) &&
        (ixEthDBAddressCompare(entry->macAddress, reference->macAddress) == 0);
}

IX_ETH_DB_PUBLIC
BOOL ixEthDBPortRecordMatch(void *untypedReference, void *untypedEntry)
{
    MacDescriptor *entry     = (MacDescriptor *) untypedEntry;
    MacDescriptor *reference = (MacDescriptor *) untypedReference;
    
    /* check accepted record types */
    if ((entry->type & reference->type) == 0) return FALSE;
    
    return (entry->portID == reference->portID) &&
        (ixEthDBAddressCompare(entry->macAddress, reference->macAddress) == 0);
}

IX_ETH_DB_PUBLIC
BOOL ixEthDBNullMatch(void *reference, void *entry)
{
    /* display an error message */

    ixOsalLog(IX_OSAL_LOG_LVL_WARNING, IX_OSAL_LOG_DEV_STDOUT, "DB: (Search) The NullMatch function was called, wrong key type?\n", 0, 0, 0, 0, 0, 0);


    return FALSE;
}

IX_ETH_DB_PUBLIC
UINT32 ixEthDBMatchMethodsRegister(MatchFunction *matchFunctions)
{
    UINT32 i;
    
    /* safety first */
    for ( i = 0 ; i < IX_ETH_DB_MAX_KEY_INDEX + 1 ; i++)
    {
        matchFunctions[i] = ixEthDBNullMatch;
    }
    
    /* register MAC search method */
    matchFunctions[IX_ETH_DB_MAC_KEY] = ixEthDBAddressRecordMatch;
    
    /* register MAC/PortID search method */
    matchFunctions[IX_ETH_DB_MAC_PORT_KEY] = ixEthDBPortRecordMatch;
    
    /* register MAC/VLAN ID search method */
    matchFunctions[IX_ETH_DB_MAC_VLAN_KEY] = ixEthDBVlanRecordMatch;
    
    return 3; /* three methods */
}

IX_ETH_DB_PUBLIC
HashNode* ixEthDBSearch(IxEthDBMacAddr *macAddress, IxEthDBRecordType typeFilter)
{
    HashNode *searchResult = NULL;
    MacDescriptor reference;
    
    TEST_FIXTURE_INCREMENT_DB_CORE_ACCESS_COUNTER;

    if (macAddress == NULL)
    {
        return NULL;
    }

    /* fill search fields */
    memcpy(reference.macAddress, macAddress, sizeof (IxEthDBMacAddr));
    
    /* set acceptable record types */
    reference.type = typeFilter;
    
    BUSY_RETRY(ixEthDBSearchHashEntry(&dbHashtable, IX_ETH_DB_MAC_KEY, &reference, &searchResult));

    return searchResult;
}

IX_ETH_DB_PUBLIC
IxEthDBStatus ixEthDBPeek(IxEthDBMacAddr *macAddress, IxEthDBRecordType typeFilter)
{
    MacDescriptor reference;
    IxEthDBStatus result;
    
    TEST_FIXTURE_INCREMENT_DB_CORE_ACCESS_COUNTER;

    if (macAddress == NULL)
    {
        return IX_ETH_DB_INVALID_ARG;
    }

    /* fill search fields */
    memcpy(reference.macAddress, macAddress, sizeof (IxEthDBMacAddr));
    
    /* set acceptable record types */
    reference.type = typeFilter;
    
    result = ixEthDBPeekHashEntry(&dbHashtable, IX_ETH_DB_MAC_KEY, &reference);

    return result;
}

IX_ETH_DB_PUBLIC
HashNode* ixEthDBPortSearch(IxEthDBMacAddr *macAddress, IxEthDBPortId portID, IxEthDBRecordType typeFilter)
{
    HashNode *searchResult = NULL;
    MacDescriptor reference;
    
    if (macAddress == NULL)
    {
        return NULL;
    }
    
    /* fill search fields */
    memcpy(reference.macAddress, macAddress, sizeof (IxEthDBMacAddr));
    reference.portID = portID;
    
    /* set acceptable record types */
    reference.type = typeFilter;

    BUSY_RETRY(ixEthDBSearchHashEntry(&dbHashtable, IX_ETH_DB_MAC_PORT_KEY, &reference, &searchResult));

    return searchResult;
}

IX_ETH_DB_PUBLIC
HashNode* ixEthDBVlanSearch(IxEthDBMacAddr *macAddress, IxEthDBVlanId vlanID, IxEthDBRecordType typeFilter)
{
    HashNode *searchResult = NULL;
    MacDescriptor reference;
    
    if (macAddress == NULL)
    {
        return NULL;
    }
    
    /* fill search fields */
    memcpy(reference.macAddress, macAddress, sizeof (IxEthDBMacAddr));
    reference.recordData.filteringVlanData.ieee802_1qTag = 
            IX_ETH_DB_SET_VLAN_ID(reference.recordData.filteringVlanData.ieee802_1qTag, vlanID);
    
    /* set acceptable record types */
    reference.type = typeFilter;

    BUSY_RETRY(ixEthDBSearchHashEntry(&dbHashtable, IX_ETH_DB_MAC_VLAN_KEY, &reference, &searchResult));

    return searchResult;
}
