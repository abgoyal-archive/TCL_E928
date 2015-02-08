

#include "IxEthDB_p.h"

/* forward prototypes */
IX_ETH_DB_PUBLIC
MacTreeNode *ixEthDBGatewaySelect(MacTreeNode *stations);

IX_ETH_DB_PUBLIC
IxEthDBStatus ixEthDBWiFiBBSIDSet(IxEthDBPortId portID, IxEthDBMacAddr *bbsid)
{
    IxNpeMhMessage message;
    IX_STATUS result;
    
    IX_ETH_DB_CHECK_PORT(portID);
    
    IX_ETH_DB_CHECK_SINGLE_NPE(portID);
    
    IX_ETH_DB_CHECK_FEATURE(portID, IX_ETH_DB_WIFI_HEADER_CONVERSION);
 
    IX_ETH_DB_CHECK_REFERENCE(bbsid);
    
    memcpy(ixEthDBPortInfo[portID].bbsid, bbsid, sizeof (IxEthDBMacAddr));

    FILL_SETBBSID_MSG(message, portID, bbsid);

    IX_ETHDB_SEND_NPE_MSG(IX_ETH_DB_PORT_ID_TO_NPE(portID), message, result);
    
    return result;
}

IX_ETH_DB_PRIVATE
IxEthDBStatus ixEthDBWiFiFrameControlDurationIDUpdate(IxEthDBPortId portID)
{
    IxNpeMhMessage message;
    IX_STATUS result;

    FILL_SETFRAMECONTROLDURATIONID(message, portID, ixEthDBPortInfo[portID].frameControlDurationID);
    
    IX_ETHDB_SEND_NPE_MSG(IX_ETH_DB_PORT_ID_TO_NPE(portID), message, result);
    
    return result;
}

IX_ETH_DB_PUBLIC
IxEthDBStatus ixEthDBWiFiDurationIDSet(IxEthDBPortId portID, UINT16 durationID)
{
    IX_ETH_DB_CHECK_PORT(portID);
    
    IX_ETH_DB_CHECK_SINGLE_NPE(portID);
    
    IX_ETH_DB_CHECK_FEATURE(portID, IX_ETH_DB_WIFI_HEADER_CONVERSION);

    ixEthDBPortInfo[portID].frameControlDurationID = (ixEthDBPortInfo[portID].frameControlDurationID & 0xFFFF0000) | durationID;
    
    return ixEthDBWiFiFrameControlDurationIDUpdate(portID);
}

IX_ETH_DB_PUBLIC
IxEthDBStatus ixEthDBWiFiFrameControlSet(IxEthDBPortId portID, UINT16 frameControl)
{
    IX_ETH_DB_CHECK_PORT(portID);
    
    IX_ETH_DB_CHECK_SINGLE_NPE(portID);
    
    IX_ETH_DB_CHECK_FEATURE(portID, IX_ETH_DB_WIFI_HEADER_CONVERSION);

    ixEthDBPortInfo[portID].frameControlDurationID = (ixEthDBPortInfo[portID].frameControlDurationID & 0xFFFF) | (frameControl << 16); 
    
    return ixEthDBWiFiFrameControlDurationIDUpdate(portID);
}

IX_ETH_DB_PUBLIC
IxEthDBStatus ixEthDBWiFiEntryRemove(IxEthDBPortId portID, IxEthDBMacAddr *macAddr)
{
    MacDescriptor recordTemplate;
    
    IX_ETH_DB_CHECK_PORT(portID);
    
    IX_ETH_DB_CHECK_SINGLE_NPE(portID);
    
    IX_ETH_DB_CHECK_REFERENCE(macAddr);
    
    IX_ETH_DB_CHECK_FEATURE(portID, IX_ETH_DB_WIFI_HEADER_CONVERSION);
    
    memcpy(recordTemplate.macAddress, macAddr, sizeof (IxEthDBMacAddr));
    
    recordTemplate.type   = IX_ETH_DB_WIFI_RECORD;
    recordTemplate.portID = portID;
    
    return ixEthDBRemove(&recordTemplate, NULL);
}

IX_ETH_DB_PRIVATE
IxEthDBStatus ixEthDBWiFiEntryAdd(IxEthDBPortId portID, IxEthDBMacAddr *macAddr, IxEthDBMacAddr *gatewayMacAddr)
{
    MacDescriptor recordTemplate;

    IX_ETH_DB_CHECK_PORT(portID);

    IX_ETH_DB_CHECK_SINGLE_NPE(portID);

    IX_ETH_DB_CHECK_REFERENCE(macAddr);
    
    IX_ETH_DB_CHECK_FEATURE(portID, IX_ETH_DB_WIFI_HEADER_CONVERSION);

    memcpy(recordTemplate.macAddress, macAddr, sizeof (IxEthDBMacAddr));
    
    recordTemplate.type   = IX_ETH_DB_WIFI_RECORD;
    recordTemplate.portID = portID;
    
    if (gatewayMacAddr != NULL)
    {
        memcpy(recordTemplate.recordData.wifiData.gwMacAddress, gatewayMacAddr, sizeof (IxEthDBMacAddr));
        
        recordTemplate.recordData.wifiData.type = IX_ETH_DB_WIFI_AP_TO_AP;
    }
    else
    {
        memset(recordTemplate.recordData.wifiData.gwMacAddress, 0, sizeof (IxEthDBMacAddr));

        recordTemplate.recordData.wifiData.type = IX_ETH_DB_WIFI_AP_TO_STA;
    }
    
    return ixEthDBAdd(&recordTemplate, NULL);
}

IX_ETH_DB_PUBLIC
IxEthDBStatus ixEthDBWiFiAccessPointEntryAdd(IxEthDBPortId portID, IxEthDBMacAddr *macAddr, IxEthDBMacAddr *gatewayMacAddr)
{
    IX_ETH_DB_CHECK_REFERENCE(gatewayMacAddr);

    return ixEthDBWiFiEntryAdd(portID, macAddr, gatewayMacAddr);
}

IX_ETH_DB_PUBLIC
IxEthDBStatus ixEthDBWiFiStationEntryAdd(IxEthDBPortId portID, IxEthDBMacAddr *macAddr)
{
    return ixEthDBWiFiEntryAdd(portID, macAddr, NULL);
}

IX_ETH_DB_PUBLIC
MacTreeNode *ixEthDBGatewaySelect(MacTreeNode *stations)
{
    MacTreeNodeStack *stack;
    MacTreeNode *gateways, *insertionPlace;
    UINT32 gwIndex = 1; /* skip the empty root */
    
    if (stations == NULL)
    {
        return NULL;
    }

    stack = ixOsalCacheDmaMalloc(sizeof (MacTreeNodeStack));

    if (stack == NULL)
    {
        ERROR_LOG("DB: (WiFi) failed to allocate the node stack for gateway tree linearization, out of memory?\n");
        return NULL;
    }
    
    /* initialize root node */
    gateways = insertionPlace = NULL;
        
    /* start browsing the station tree */
    NODE_STACK_INIT(stack);
    
    /* initialize stack by pushing the tree root at offset 0 */
    NODE_STACK_PUSH(stack, stations, 0);
    
    while (NODE_STACK_NONEMPTY(stack))
    {
        MacTreeNode *node;
        UINT32 offset;
       
        NODE_STACK_POP(stack, node, offset);

        /* we can store maximum 31 (32 total, 1 empty root) entries in the gateway tree */
        if (offset > (MAX_GW_SIZE - 1)) break;
        
        /* check if this record has a gateway address */
        if (node->descriptor != NULL && node->descriptor->recordData.wifiData.type == IX_ETH_DB_WIFI_AP_TO_AP)
        {
            /* found a record, create an insertion place */
            if (insertionPlace != NULL)
            {
                insertionPlace->right = ixEthDBAllocMacTreeNode();
                insertionPlace        = insertionPlace->right;
            }
            else
            {
                gateways       = ixEthDBAllocMacTreeNode();
                insertionPlace = gateways;
            }

            if (insertionPlace == NULL)
            {
                /* no nodes left, bail out with what we have */
                ixOsalCacheDmaFree(stack);
                return gateways;
            }
            
            /* clone the original record for the gateway tree */
            insertionPlace->descriptor = ixEthDBCloneMacDescriptor(node->descriptor);
            
            /* insert and update the offset in the original record */
            node->descriptor->recordData.wifiData.gwAddressIndex = gwIndex++;
        }
        
        /* browse the tree */
        if (node->left != NULL)
        {
            NODE_STACK_PUSH(stack, node->left, LEFT_CHILD_OFFSET(offset));
        }

        if (node->right != NULL)
        {
            NODE_STACK_PUSH(stack, node->right, RIGHT_CHILD_OFFSET(offset));
        }
    }
    
    ixOsalCacheDmaFree(stack);
    return gateways;    
}

IX_ETH_DB_PUBLIC
IxEthDBStatus ixEthDBWiFiConversionTableDownload(IxEthDBPortId portID)
{
    IxEthDBPortMap query;
    MacTreeNode *stations = NULL, *gateways = NULL, *gateway = NULL;
    IxNpeMhMessage message;
    PortInfo *portInfo;
    IX_STATUS result;

    IX_ETH_DB_CHECK_PORT(portID);

    IX_ETH_DB_CHECK_SINGLE_NPE(portID);
    
    IX_ETH_DB_CHECK_FEATURE(portID, IX_ETH_DB_WIFI_HEADER_CONVERSION);

    portInfo = &ixEthDBPortInfo[portID];
   
    SET_DEPENDENCY_MAP(query, portID);
    
    ixEthDBUpdateLock();

    stations = ixEthDBQuery(NULL, query, IX_ETH_DB_WIFI_RECORD, MAX_ELT_SIZE);
    gateways = ixEthDBGatewaySelect(stations);
    
    /* clean up gw area */
    memset((void *) portInfo->updateMethod.npeGwUpdateZone, FULL_GW_BYTE_SIZE, 0);

    /* write all gateways */
    gateway = gateways;

    while (gateway != NULL)
    {
        ixEthDBNPEGatewayNodeWrite((void *) (((UINT32) portInfo->updateMethod.npeGwUpdateZone) 
            + gateway->descriptor->recordData.wifiData.gwAddressIndex * ELT_ENTRY_SIZE), 
            gateway);

        gateway = gateway->right;
    }

    /* free the gateway tree */
    if (gateways != NULL)
    {
        ixEthDBFreeMacTreeNode(gateways);
    }

    FILL_SETAPMACTABLE_MSG(message, 
        IX_OSAL_MMU_VIRT_TO_PHYS(portInfo->updateMethod.npeGwUpdateZone));

    IX_ETHDB_SEND_NPE_MSG(IX_ETH_DB_PORT_ID_TO_NPE(portID), message, result);

    if (result == IX_SUCCESS)
    {
        /* update the main tree (the stations tree) */
        portInfo->updateMethod.searchTree = stations;
        
        result = ixEthDBNPEUpdateHandler(portID, IX_ETH_DB_WIFI_RECORD);
    }

    ixEthDBUpdateUnlock();

    return result;
}
