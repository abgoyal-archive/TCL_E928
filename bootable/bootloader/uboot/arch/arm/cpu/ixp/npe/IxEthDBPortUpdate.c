

#include "IxEthDB_p.h"

/* forward prototype declarations */
IX_ETH_DB_PRIVATE MacTreeNode* ixEthDBTreeInsert(MacTreeNode *searchTree, MacDescriptor *descriptor);
IX_ETH_DB_PRIVATE void ixEthDBCreateTrees(IxEthDBPortMap updatePorts);
IX_ETH_DB_PRIVATE MacTreeNode* ixEthDBTreeRebalance(MacTreeNode *searchTree);
IX_ETH_DB_PRIVATE void ixEthDBRebalanceTreeToVine(MacTreeNode *root, UINT32 *size);
IX_ETH_DB_PRIVATE void ixEthDBRebalanceVineToTree(MacTreeNode *root, UINT32 size);
IX_ETH_DB_PRIVATE void ixEthDBRebalanceCompression(MacTreeNode *root, UINT32 count);
IX_ETH_DB_PRIVATE UINT32 ixEthDBRebalanceLog2Floor(UINT32 x);

extern HashTable dbHashtable;

IX_ETH_DB_PUBLIC
UINT32 ixEthDBUpdateTypeRegister(BOOL *typeArray)
{
    typeArray[IX_ETH_DB_FILTERING_RECORD]      = TRUE;
    typeArray[IX_ETH_DB_FILTERING_VLAN_RECORD] = TRUE;

    return 2;
}

IX_ETH_DB_PUBLIC
void ixEthDBUpdatePortLearningTrees(IxEthDBPortMap triggerPorts)
{
    IxEthDBPortMap updatePorts;
    UINT32 portIndex;
    
    ixEthDBUpdateLock();
    
    SET_EMPTY_DEPENDENCY_MAP(updatePorts);
    
    for (portIndex = 0 ; portIndex < IX_ETH_DB_NUMBER_OF_PORTS ; portIndex++)
    {
        PortInfo *port   = &ixEthDBPortInfo[portIndex];
        BOOL mapsCollide;
        
        MAPS_COLLIDE(mapsCollide, triggerPorts, port->dependencyPortMap);

        if (mapsCollide                                   /* do triggers influence this port? */
            && !IS_PORT_INCLUDED(portIndex, updatePorts)  /* and it's not already in the update list */
            && port->updateMethod.updateEnabled)          /* and we're allowed to update it */
        {
            IX_ETH_DB_UPDATE_TRACE("DB: (Update) Adding port %d to update set\n", portIndex);

            JOIN_PORT_TO_MAP(updatePorts, portIndex);
        }
        else
        {
            IX_ETH_DB_UPDATE_TRACE("DB: (Update) Didn't add port %d to update set, reasons follow:\n", portIndex);

            if (!mapsCollide)
            {
                IX_ETH_DB_UPDATE_TRACE("\tMaps don't collide on port %d\n", portIndex);
            }

            if (IS_PORT_INCLUDED(portIndex, updatePorts))
            {
                IX_ETH_DB_UPDATE_TRACE("\tPort %d is already in the update set\n", portIndex);
            }

            if (!port->updateMethod.updateEnabled)
            {
                IX_ETH_DB_UPDATE_TRACE("\tPort %d doesn't have updateEnabled set\n", portIndex);
            }
        }
    }
    
    IX_ETH_DB_UPDATE_TRACE("DB: (Update) Updating port set\n");

    ixEthDBCreateTrees(updatePorts);
        
    ixEthDBUpdateUnlock();
}

IX_ETH_DB_PRIVATE
void ixEthDBCreateTrees(IxEthDBPortMap updatePorts)
{
    UINT32 portIndex;
    BOOL result;
    BOOL portsLeft = TRUE;

    while (portsLeft)
    {
        /* get port with minimal dependency map and NULL search tree */
        UINT32 minPortIndex = MAX_PORT_SIZE;
        UINT32 minimalSize  = MAX_PORT_SIZE;

        for (portIndex = 0 ; portIndex < IX_ETH_DB_NUMBER_OF_PORTS ; portIndex++)
        {
            UINT32 size;
            PortInfo *port = &ixEthDBPortInfo[portIndex];

            /* generate trees only for ports that need them */
            if (!port->updateMethod.searchTreePendingWrite && IS_PORT_INCLUDED(portIndex, updatePorts))
            {
                GET_MAP_SIZE(port->dependencyPortMap, size);
                
                IX_ETH_DB_UPDATE_TRACE("DB: (Update) Dependency map for port %d: size %d\n",
                    portIndex, size);

                if (size < minimalSize)
                {
                    minPortIndex = portIndex;
                    minimalSize  = size;
                }
            }
            else
            {
                IX_ETH_DB_UPDATE_TRACE("DB: (Update) Skipped port %d from tree diff (%s)\n", portIndex,
                    port->updateMethod.searchTreePendingWrite ? "pending write access" : "ignored by query");
            }            
        }

        /* if a port was found than minimalSize is not MAX_PORT_SIZE */
        if (minimalSize != MAX_PORT_SIZE)
        {
            /* minPortIndex is the port we seek */
            PortInfo *port = &ixEthDBPortInfo[minPortIndex];

            IxEthDBPortMap query;
            MacTreeNode *baseTree;

            /* now try to find a port with minimal map difference */
            PortInfo *minimalDiffPort = NULL;
            UINT32 minimalDiff        = MAX_PORT_SIZE;
            
            IX_ETH_DB_UPDATE_TRACE("DB: (Update) Minimal size port is %d\n", minPortIndex);

            for (portIndex = 0 ; portIndex < IX_ETH_DB_NUMBER_OF_PORTS ; portIndex++)
            {   
                PortInfo *diffPort = &ixEthDBPortInfo[portIndex];
                BOOL mapIsSubset;
                
                IS_MAP_SUBSET(mapIsSubset, diffPort->dependencyPortMap, port->dependencyPortMap);
                

                if (portIndex != minPortIndex
                    && diffPort->updateMethod.searchTree != NULL
                    && mapIsSubset)
                {
                    /* compute size and pick only minimal size difference */
                    UINT32 diffPortSize;
                    UINT32 sizeDifference;

                    GET_MAP_SIZE(diffPort->dependencyPortMap, diffPortSize);
                     
                    IX_ETH_DB_UPDATE_TRACE("DB: (Update) Checking port %d for differences...\n", portIndex);

                    sizeDifference = minimalSize - diffPortSize;

                    if (sizeDifference < minimalDiff)
                    {
                        minimalDiffPort = diffPort;
                        minimalDiff     = sizeDifference;
                        
                        IX_ETH_DB_UPDATE_TRACE("DB: (Update) Minimal difference 0x%x was found on port %d\n",
                            minimalDiff, portIndex);
                    }
                }
            }

            /* check if filtering is enabled on this port */
            if ((port->featureStatus & IX_ETH_DB_FILTERING) != 0)
            {
                /* if minimalDiff is not MAX_PORT_SIZE minimalDiffPort points to the most similar port */
                if (minimalDiff != MAX_PORT_SIZE)
                {
                    baseTree = ixEthDBCloneMacTreeNode(minimalDiffPort->updateMethod.searchTree);
                    DIFF_MAPS(query, port->dependencyPortMap , minimalDiffPort->dependencyPortMap);
                    
                    IX_ETH_DB_UPDATE_TRACE("DB: (Update) Found minimal diff, extending tree %d on query\n",
                        minimalDiffPort->portID);
                }
                else /* .. otherwise no similar port was found, build tree from scratch */
                {
                    baseTree = NULL;
                    
                    COPY_DEPENDENCY_MAP(query, port->dependencyPortMap);
                    
                    IX_ETH_DB_UPDATE_TRACE("DB: (Update) No similar diff, creating tree from query\n");
                }

                IS_EMPTY_DEPENDENCY_MAP(result, query);
                
                if (!result) /* otherwise we don't need anything more on top of the cloned tree */
                {
                    IX_ETH_DB_UPDATE_TRACE("DB: (Update) Adding query tree to port %d\n", minPortIndex);
                        
                    /* build learning tree */
                    port->updateMethod.searchTree = ixEthDBQuery(baseTree, query, IX_ETH_DB_ALL_FILTERING_RECORDS, MAX_ELT_SIZE);
                }
                else
                {
                    IX_ETH_DB_UPDATE_TRACE("DB: (Update) Query is empty, assuming identical nearest tree\n");
                      
                    port->updateMethod.searchTree = baseTree;
                }
            }
            else
            {
                /* filtering is not enabled, will download an empty tree */
                if (port->updateMethod.searchTree != NULL)
                {
                    ixEthDBFreeMacTreeNode(port->updateMethod.searchTree);
                }

                port->updateMethod.searchTree = NULL;
            }

            /* mark tree as valid */
            port->updateMethod.searchTreePendingWrite = TRUE;
        }
        else
        {
            portsLeft = FALSE;

            IX_ETH_DB_UPDATE_TRACE("DB: (Update) No trees to create this round\n");            
        }
    }
    
    for (portIndex = 0 ; portIndex < IX_ETH_DB_NUMBER_OF_PORTS ; portIndex++)
    {
        PortInfo *updatePort = &ixEthDBPortInfo[portIndex];

        if (updatePort->updateMethod.searchTreePendingWrite)
        {
            IX_ETH_DB_UPDATE_TRACE("DB: (PortUpdate) Starting procedure to upload new search tree (%snull) into NPE %d\n", 
                updatePort->updateMethod.searchTree != NULL ? "not " : "",
                portIndex);

            updatePort->updateMethod.updateHandler(portIndex, IX_ETH_DB_FILTERING_RECORD);
        }
    }
}

IX_ETH_DB_PUBLIC
IxEthDBStatus ixEthDBNPEUpdateHandler(IxEthDBPortId portID, IxEthDBRecordType type)
{
    UINT32 epDelta, blockCount;
    IxNpeMhMessage message;
    UINT32 treeSize = 0;
    PortInfo *port = &ixEthDBPortInfo[portID];

    /* size selection and type check */
    if (type == IX_ETH_DB_FILTERING_RECORD || type == IX_ETH_DB_WIFI_RECORD)
    {
        treeSize = FULL_ELT_BYTE_SIZE;
    }
    else if (type == IX_ETH_DB_FIREWALL_RECORD)
    {
        treeSize = FULL_FW_BYTE_SIZE;
    }
    else
    {
        return IX_ETH_DB_INVALID_ARG;
    }
    
    /* serialize tree into memory */
    ixEthDBNPETreeWrite(type, treeSize, port->updateMethod.npeUpdateZone, port->updateMethod.searchTree, &epDelta, &blockCount);

    /* free internal copy */
    if (port->updateMethod.searchTree != NULL)
    {
        ixEthDBFreeMacTreeNode(port->updateMethod.searchTree);
    }

    /* forget last used search tree */
    port->updateMethod.searchTree             = NULL;
    port->updateMethod.searchTreePendingWrite = FALSE;

    /* dependending on the update type we do different things */
    if (type == IX_ETH_DB_FILTERING_RECORD || type == IX_ETH_DB_WIFI_RECORD)
    {
        IX_STATUS result;

        FILL_SETMACADDRESSDATABASE_MSG(message, IX_ETH_DB_PORT_ID_TO_NPE_LOGICAL_ID(portID), 
            epDelta, blockCount, 
            IX_OSAL_MMU_VIRT_TO_PHYS(port->updateMethod.npeUpdateZone));

        IX_ETHDB_SEND_NPE_MSG(IX_ETH_DB_PORT_ID_TO_NPE(portID), message, result);

        if (result == IX_SUCCESS)
	{
            IX_ETH_DB_UPDATE_TRACE("DB: (PortUpdate) Finished downloading NPE tree on port %d\n", portID);
        }
        else
        {
            ixEthDBPortInfo[portID].agingEnabled                = FALSE;
            ixEthDBPortInfo[portID].updateMethod.updateEnabled  = FALSE;
            ixEthDBPortInfo[portID].updateMethod.userControlled = TRUE;

            ERROR_LOG("EthDB: (PortUpdate) disabling aging and updates on port %d (assumed dead)\n", portID);

            ixEthDBDatabaseClear(portID, IX_ETH_DB_ALL_RECORD_TYPES);

            return IX_ETH_DB_FAIL;
        }

	return IX_ETH_DB_SUCCESS;
    }
    else if (type == IX_ETH_DB_FIREWALL_RECORD)
    {
        return ixEthDBFirewallUpdate(portID, port->updateMethod.npeUpdateZone, epDelta);
    }
    
    return IX_ETH_DB_INVALID_ARG;
}

IX_ETH_DB_PUBLIC
MacTreeNode* ixEthDBQuery(MacTreeNode *searchTree, IxEthDBPortMap query, IxEthDBRecordType recordFilter, UINT32 maxEntries)
{
    HashIterator iterator;
    UINT32 entryCount = 0;

    /* browse database */
    BUSY_RETRY(ixEthDBInitHashIterator(&dbHashtable, &iterator));

    while (IS_ITERATOR_VALID(&iterator))
    {
        MacDescriptor *descriptor = (MacDescriptor *) iterator.node->data;

        IX_ETH_DB_UPDATE_TRACE("DB: (PortUpdate) querying [%s]:%d on port map ... ", 
            mac2string(descriptor->macAddress), 
            descriptor->portID);

	if ((descriptor->type & recordFilter) != 0 
            && IS_PORT_INCLUDED(descriptor->portID, query))
	{
            MacDescriptor *descriptorClone = ixEthDBCloneMacDescriptor(descriptor);

            IX_ETH_DB_UPDATE_TRACE("match\n");

            if (descriptorClone != NULL)
            {
                /* add descriptor to tree */
                searchTree = ixEthDBTreeInsert(searchTree, descriptorClone);

                entryCount++;
            }
        }
        else
        {
            IX_ETH_DB_UPDATE_TRACE("no match\n");
        }

        if (entryCount < maxEntries)
        {
            /* advance to the next record */
	        BUSY_RETRY(ixEthDBIncrementHashIterator(&dbHashtable, &iterator));
        }
        else
        {
            /* the NPE won't accept more entries so we can stop now */
            ixEthDBReleaseHashIterator(&iterator);

            IX_ETH_DB_UPDATE_TRACE("DB: (PortUpdate) number of elements reached maximum supported by port\n");

            break;
        }
    }

    IX_ETH_DB_UPDATE_TRACE("DB: (PortUpdate) query inserted %d records in the search tree\n", entryCount);

    return ixEthDBTreeRebalance(searchTree);
}

IX_ETH_DB_PRIVATE
MacTreeNode* ixEthDBTreeInsert(MacTreeNode *searchTree, MacDescriptor *descriptor)
{
    MacTreeNode *currentNode    = searchTree;
    MacTreeNode *insertLocation = NULL;
    MacTreeNode *newNode;
    INT32 insertPosition = RIGHT;

    if (descriptor == NULL)
    {
        return searchTree;
    }

    /* create a new node */
    newNode = ixEthDBAllocMacTreeNode();

    if (newNode == NULL)
    {
        /* out of memory */
        ERROR_LOG("Warning: ixEthDBAllocMacTreeNode returned NULL in file %s:%d (out of memory?)\n", __FILE__, __LINE__);

        ixEthDBFreeMacDescriptor(descriptor);

        return NULL;
    }

    /* populate node */
    newNode->descriptor = descriptor;

    /* an empty initial tree is a special case */
    if (searchTree == NULL)
    {
        return newNode;
    }

    /* get insertion location */
    while (insertLocation == NULL)
    {
        MacTreeNode *nextNode;

        /* compare given key with current node key */
        insertPosition = ixEthDBAddressCompare(descriptor->macAddress, currentNode->descriptor->macAddress);

        /* navigate down */
        if (insertPosition == RIGHT)
        {
            nextNode = currentNode->right;
        }
        else if (insertPosition == LEFT)
        {
            nextNode = currentNode->left;
        }
        else
        {
            /* error, duplicate key */
            ERROR_LOG("Warning: trapped insertion of a duplicate MAC address in an NPE search tree\n");

            /* this will free the MAC descriptor as well */
            ixEthDBFreeMacTreeNode(newNode);

            return searchTree;
        }

        /* when we can no longer dive through the tree we found the insertion place */
        if (nextNode != NULL)
        {
            currentNode = nextNode;
        }
        else
        {
            insertLocation = currentNode;
        }
    }

    /* insert node */
    if (insertPosition == RIGHT)
    {
        insertLocation->right = newNode;
    }
    else
    {
        insertLocation->left = newNode;
    }

    return searchTree;
}

IX_ETH_DB_PRIVATE
MacTreeNode* ixEthDBTreeRebalance(MacTreeNode *searchTree)
{
    MacTreeNode *pseudoRoot = ixEthDBAllocMacTreeNode();
    UINT32 size;

    if (pseudoRoot == NULL)
    {
        /* out of memory */
        return NULL;
    }

    pseudoRoot->right = searchTree;

    ixEthDBRebalanceTreeToVine(pseudoRoot, &size);
    ixEthDBRebalanceVineToTree(pseudoRoot, size);

    searchTree = pseudoRoot->right;

    /* remove pseudoRoot right branch, otherwise it will free the entire tree */
    pseudoRoot->right = NULL;

    ixEthDBFreeMacTreeNode(pseudoRoot);

    return searchTree;
}

IX_ETH_DB_PRIVATE
void ixEthDBRebalanceTreeToVine(MacTreeNode *root, UINT32 *size)
{
    MacTreeNode *vineTail  = root;
    MacTreeNode *remainder = vineTail->right;
    MacTreeNode *tempPtr;

    *size = 0;

    while (remainder != NULL)
    {
        if (remainder->left == NULL)
        {
            /* move tail down one */
            vineTail  = remainder;
            remainder = remainder->right;
            (*size)++;
        }
        else
        {
            /* rotate around remainder */
            tempPtr         = remainder->left;
            remainder->left = tempPtr->right;
            tempPtr->right  = remainder;
            remainder       = tempPtr;
            vineTail->right = tempPtr;
        }
    }
}

IX_ETH_DB_PRIVATE
void ixEthDBRebalanceVineToTree(MacTreeNode *root, UINT32 size)
{
    UINT32 leafCount = size + 1 - (1 << ixEthDBRebalanceLog2Floor(size + 1));

    ixEthDBRebalanceCompression(root, leafCount);

    size = size - leafCount;

    while (size > 1)
    {
        ixEthDBRebalanceCompression(root, size / 2);

        size /= 2;
    }
}

IX_ETH_DB_PRIVATE
void ixEthDBRebalanceCompression(MacTreeNode *root, UINT32 count)
{
    MacTreeNode *scanner = root;
    MacTreeNode *child;
    UINT32 local_index;

    for (local_index = 0 ; local_index < count ; local_index++)
    {
        child          = scanner->right;
        scanner->right = child->right;
        scanner        = scanner->right;
        child->right   = scanner->left;
        scanner->left  = child;
    }
}

IX_ETH_DB_PRIVATE
UINT32 ixEthDBRebalanceLog2Floor(UINT32 x)
{
    UINT32 log = 0;
    UINT32 val = 1;

    while (val < x)
    {
        log++;
        val <<= 1;
    }

    return val == x ? log : log - 1;
}

