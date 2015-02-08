


#include "IxEthDB_p.h"

IX_ETH_DB_PUBLIC
IxEthDBStatus ixEthDBFirewallUpdate(IxEthDBPortId portID, void *address, UINT32 epDelta)
{
    IxNpeMhMessage message;
    IX_STATUS result;
    
    UINT32 mode        = 0;    
    PortInfo *portInfo = &ixEthDBPortInfo[portID];

    mode = (portInfo->srcAddressFilterEnabled != FALSE) << 1 | (portInfo->firewallMode == IX_ETH_DB_FIREWALL_WHITE_LIST);

    FILL_SETFIREWALLMODE_MSG(message, 
        IX_ETH_DB_PORT_ID_TO_NPE_LOGICAL_ID(portID), 
        epDelta, 
        mode, 
        IX_OSAL_MMU_VIRT_TO_PHYS(address));

    IX_ETHDB_SEND_NPE_MSG(IX_ETH_DB_PORT_ID_TO_NPE(portID), message, result);
    
    return result;
}

IX_ETH_DB_PUBLIC 
IxEthDBStatus ixEthDBFirewallModeSet(IxEthDBPortId portID, IxEthDBFirewallMode mode)
{
    IX_ETH_DB_CHECK_PORT(portID);
    
    IX_ETH_DB_CHECK_SINGLE_NPE(portID);
     
    IX_ETH_DB_CHECK_FEATURE(portID, IX_ETH_DB_FIREWALL);
    
    if (mode != IX_ETH_DB_FIREWALL_WHITE_LIST
        && mode != IX_ETH_DB_FIREWALL_BLACK_LIST)
    {
        return IX_ETH_DB_INVALID_ARG;
    }    
    
    ixEthDBPortInfo[portID].firewallMode = mode;
    
    return ixEthDBFirewallTableDownload(portID);
}

IX_ETH_DB_PUBLIC 
IxEthDBStatus ixEthDBFirewallInvalidAddressFilterEnable(IxEthDBPortId portID, BOOL enable)
{
    IX_ETH_DB_CHECK_PORT(portID);
    
    IX_ETH_DB_CHECK_SINGLE_NPE(portID);
    
    IX_ETH_DB_CHECK_FEATURE(portID, IX_ETH_DB_FIREWALL);

    ixEthDBPortInfo[portID].srcAddressFilterEnabled = enable;
    
    return ixEthDBFirewallTableDownload(portID);
}

IX_ETH_DB_PUBLIC 
IxEthDBStatus ixEthDBFirewallEntryAdd(IxEthDBPortId portID, IxEthDBMacAddr *macAddr)
{
    MacDescriptor recordTemplate;

    IX_ETH_DB_CHECK_PORT(portID);

    IX_ETH_DB_CHECK_SINGLE_NPE(portID);

    IX_ETH_DB_CHECK_REFERENCE(macAddr);

    IX_ETH_DB_CHECK_FEATURE(portID, IX_ETH_DB_FIREWALL);
    
    memcpy(recordTemplate.macAddress, macAddr, sizeof (IxEthDBMacAddr));
    
    recordTemplate.type   = IX_ETH_DB_FIREWALL_RECORD;
    recordTemplate.portID = portID;
    
    return ixEthDBAdd(&recordTemplate, NULL);
}

IX_ETH_DB_PUBLIC 
IxEthDBStatus ixEthDBFirewallEntryRemove(IxEthDBPortId portID, IxEthDBMacAddr *macAddr)
{
    MacDescriptor recordTemplate;
    
    IX_ETH_DB_CHECK_PORT(portID);

    IX_ETH_DB_CHECK_SINGLE_NPE(portID);

    IX_ETH_DB_CHECK_REFERENCE(macAddr);

    IX_ETH_DB_CHECK_FEATURE(portID, IX_ETH_DB_FIREWALL);
    
    memcpy(recordTemplate.macAddress, macAddr, sizeof (IxEthDBMacAddr));
    
    recordTemplate.type   = IX_ETH_DB_FIREWALL_RECORD;
    recordTemplate.portID = portID;
    
    return ixEthDBRemove(&recordTemplate, NULL);
}

IX_ETH_DB_PUBLIC 
IxEthDBStatus ixEthDBFirewallTableDownload(IxEthDBPortId portID)
{
    IxEthDBPortMap query;
    IxEthDBStatus result;
    
    IX_ETH_DB_CHECK_PORT(portID);

    IX_ETH_DB_CHECK_SINGLE_NPE(portID);

    IX_ETH_DB_CHECK_FEATURE(portID, IX_ETH_DB_FIREWALL);
    
    SET_DEPENDENCY_MAP(query, portID);

    ixEthDBUpdateLock();
    
    ixEthDBPortInfo[portID].updateMethod.searchTree = ixEthDBQuery(NULL, query, IX_ETH_DB_FIREWALL_RECORD, MAX_FW_SIZE);
    
    result = ixEthDBNPEUpdateHandler(portID, IX_ETH_DB_FIREWALL_RECORD);

    ixEthDBUpdateUnlock();

    return result;
}
