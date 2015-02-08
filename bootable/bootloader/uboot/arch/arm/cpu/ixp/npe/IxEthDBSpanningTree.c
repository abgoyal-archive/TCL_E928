


#include "IxEthDB_p.h"

IX_ETH_DB_PUBLIC 
IxEthDBStatus ixEthDBSpanningTreeBlockingStateSet(IxEthDBPortId portID, BOOL blocked)
{
    IxNpeMhMessage message;
    IX_STATUS result;
    
    IX_ETH_DB_CHECK_PORT(portID);
    
    IX_ETH_DB_CHECK_SINGLE_NPE(portID);
 
    IX_ETH_DB_CHECK_FEATURE(portID, IX_ETH_DB_SPANNING_TREE_PROTOCOL);
    
    ixEthDBPortInfo[portID].stpBlocked = blocked;

    FILL_SETBLOCKINGSTATE_MSG(message, portID, blocked);
    
    IX_ETHDB_SEND_NPE_MSG(IX_ETH_DB_PORT_ID_TO_NPE(portID), message, result);
    
    return result;
}

IX_ETH_DB_PUBLIC 
IxEthDBStatus ixEthDBSpanningTreeBlockingStateGet(IxEthDBPortId portID, BOOL *blocked)
{
    IX_ETH_DB_CHECK_PORT(portID);
    
    IX_ETH_DB_CHECK_SINGLE_NPE(portID);
 
    IX_ETH_DB_CHECK_FEATURE(portID, IX_ETH_DB_SPANNING_TREE_PROTOCOL);
    
    IX_ETH_DB_CHECK_REFERENCE(blocked);
    
    *blocked = ixEthDBPortInfo[portID].stpBlocked;
    
    return IX_ETH_DB_SUCCESS;
}
