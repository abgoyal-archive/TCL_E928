

#include "IxEthDB_p.h"

/* list of database hashtables */
IX_ETH_DB_PUBLIC HashTable dbHashtable;
IX_ETH_DB_PUBLIC MatchFunction matchFunctions[IX_ETH_DB_MAX_KEY_INDEX + 1];
IX_ETH_DB_PUBLIC BOOL ixEthDBPortUpdateRequired[IX_ETH_DB_MAX_RECORD_TYPE_INDEX + 1];
IX_ETH_DB_PUBLIC UINT32 ixEthDBKeyType[IX_ETH_DB_MAX_RECORD_TYPE_INDEX + 1];

/* private initialization flag */
IX_ETH_DB_PRIVATE BOOL ethDBInitializationComplete = FALSE;

IX_ETH_DB_PUBLIC
IxEthDBStatus ixEthDBInit(void)
{
    IxEthDBStatus result;

    if (ethDBInitializationComplete)
    {
        /* redundant */
        return IX_ETH_DB_SUCCESS;
    }

    /* trap an invalid port definition structure */
    IX_ETH_DB_PORTS_ASSERTION;

    /* memory management */
    ixEthDBInitMemoryPools();

    /* register hashing search methods */
    ixEthDBMatchMethodsRegister(matchFunctions);

    /* register type-based automatic port updates */
    ixEthDBUpdateTypeRegister(ixEthDBPortUpdateRequired);

    /* register record to key type mappings */
    ixEthDBKeyTypeRegister(ixEthDBKeyType);

    /* hash table */
    ixEthDBInitHash(&dbHashtable, NUM_BUCKETS, ixEthDBEntryXORHash, matchFunctions, (FreeFunction) ixEthDBFreeMacDescriptor);

    /* NPE update zones */
    ixEthDBNPEUpdateAreasInit();

    /* register record serialization methods */
    ixEthDBRecordSerializeMethodsRegister();

    /* start the event processor */
    result = ixEthDBEventProcessorInit();

    /* scan NPE features */
    if (result == IX_ETH_DB_SUCCESS)
    {
        ixEthDBFeatureCapabilityScan();
    }

    ethDBInitializationComplete = TRUE;

    return result;
}

IX_ETH_DB_PUBLIC
IxEthDBStatus ixEthDBUnload(void)
{
    IxEthDBPortId portIndex;

    if (!ethDBInitializationComplete)
    {
        /* redundant */
        return IX_ETH_DB_SUCCESS;
    }

    /* check if any ports are enabled */
    for (portIndex = 0 ; portIndex < IX_ETH_DB_NUMBER_OF_PORTS ; portIndex++)
    {
        if (ixEthDBPortInfo[portIndex].enabled)
        {
            return IX_ETH_DB_BUSY;
        }
    }

    /* free port resources */
    for (portIndex = 0 ; portIndex < IX_ETH_DB_NUMBER_OF_PORTS ; portIndex++)
    {
        if (ixEthDBPortDefinitions[portIndex].type == IX_ETH_NPE)
        {
            ixOsalMutexDestroy(&ixEthDBPortInfo[portIndex].npeAckLock);
        }

        ixEthDBPortInfo[portIndex].initialized = FALSE;
    }

    /* shutdown event processor */
    ixEthDBStopLearningFunction();

    /* deallocate NPE update zones */
    ixEthDBNPEUpdateAreasUnload();

    ethDBInitializationComplete = FALSE;

    return IX_ETH_DB_SUCCESS;
}

IX_ETH_DB_PUBLIC
IxEthDBStatus ixEthDBAdd(MacDescriptor *newRecordTemplate, IxEthDBPortMap updateTrigger)
{
    IxEthDBStatus result;
    MacDescriptor *newDescriptor;
    IxEthDBPortId originalPortID;
    HashNode *node = NULL;

    BUSY_RETRY(ixEthDBSearchHashEntry(&dbHashtable, ixEthDBKeyType[newRecordTemplate->type], newRecordTemplate, &node));

    TEST_FIXTURE_INCREMENT_DB_CORE_ACCESS_COUNTER;

    if (node == NULL)
    {
        /* not found, create a new one */
        newDescriptor = ixEthDBAllocMacDescriptor();

        if (newDescriptor == NULL)
        {
            return IX_ETH_DB_NOMEM; /* no memory */
        }

        /* old port does not exist, avoid unnecessary updates */
        originalPortID = newRecordTemplate->portID;
    }
    else
    {
        /* a node with the same key exists, will update node */
        newDescriptor = (MacDescriptor *) node->data;

        /* save original port id */
        originalPortID = newDescriptor->portID;
    }

    /* copy/update fields into new record */
    memcpy(newDescriptor->macAddress, newRecordTemplate->macAddress, sizeof (IxEthDBMacAddr));
    memcpy(&newDescriptor->recordData, &newRecordTemplate->recordData, sizeof (IxEthDBRecordData));

    newDescriptor->type   = newRecordTemplate->type;
    newDescriptor->portID = newRecordTemplate->portID;
    newDescriptor->user   = newRecordTemplate->user;

    if (node == NULL)
    {
        /* new record, insert into hashtable */
        BUSY_RETRY_WITH_RESULT(ixEthDBAddHashEntry(&dbHashtable, newDescriptor), result);

        if (result != IX_ETH_DB_SUCCESS)
        {
            ixEthDBFreeMacDescriptor(newDescriptor);

            return result; /* insertion failed */
        }
    }

    if (node != NULL)
    {
        /* release access */
        ixEthDBReleaseHashNode(node);
    }

    /* trigger add/remove update if required by type */
    if (updateTrigger != NULL &&
        ixEthDBPortUpdateRequired[newRecordTemplate->type])
    {
        /* add new port to update list */
        JOIN_PORT_TO_MAP(updateTrigger, newRecordTemplate->portID);

        /* check if record has moved, we'll need to update the old port as well */
        if (originalPortID != newDescriptor->portID)
        {
            JOIN_PORT_TO_MAP(updateTrigger, originalPortID);
        }
    }

    return IX_ETH_DB_SUCCESS;
}

IX_ETH_DB_PUBLIC
IxEthDBStatus ixEthDBRemove(MacDescriptor *templateRecord, IxEthDBPortMap updateTrigger)
{
    IxEthDBStatus result;

    TEST_FIXTURE_INCREMENT_DB_CORE_ACCESS_COUNTER;

    BUSY_RETRY_WITH_RESULT(ixEthDBRemoveHashEntry(&dbHashtable, ixEthDBKeyType[templateRecord->type], templateRecord), result);

    if (result != IX_ETH_DB_SUCCESS)
    {
        return IX_ETH_DB_NO_SUCH_ADDR; /* not found */
    }

    /* trigger add/remove update if required by type */
    if (updateTrigger != NULL
        &&ixEthDBPortUpdateRequired[templateRecord->type])
    {
        /* add new port to update list */
        JOIN_PORT_TO_MAP(updateTrigger, templateRecord->portID);
    }

    return IX_ETH_DB_SUCCESS;
}

IX_ETH_DB_PUBLIC
UINT32 ixEthDBKeyTypeRegister(UINT32 *keyType)
{
    /* safety */
    memset(keyType, 0, sizeof (keyType));

    /* register all known record types */
    keyType[IX_ETH_DB_FILTERING_RECORD]      = IX_ETH_DB_MAC_KEY;
    keyType[IX_ETH_DB_FILTERING_VLAN_RECORD] = IX_ETH_DB_MAC_KEY;
    keyType[IX_ETH_DB_ALL_FILTERING_RECORDS] = IX_ETH_DB_MAC_KEY;
    keyType[IX_ETH_DB_WIFI_RECORD]           = IX_ETH_DB_MAC_PORT_KEY;
    keyType[IX_ETH_DB_FIREWALL_RECORD]       = IX_ETH_DB_MAC_PORT_KEY;

    return 5;
}

IX_ETH_DB_PUBLIC
IxEthDBStatus ixEthDBUserFieldSet(IxEthDBRecordType recordType, IxEthDBMacAddr *macAddr, IxEthDBPortId portID, IxEthDBVlanId vlanID, void *field)
{
    HashNode *result = NULL;

    if (macAddr == NULL)
    {
        return IX_ETH_DB_INVALID_ARG;
    }

    if (recordType == IX_ETH_DB_FILTERING_RECORD)
    {
        result = ixEthDBSearch(macAddr, recordType);
    }
    else if (recordType == IX_ETH_DB_FILTERING_VLAN_RECORD)
    {
        result = ixEthDBVlanSearch(macAddr, vlanID, recordType);
    }
    else if (recordType == IX_ETH_DB_WIFI_RECORD || recordType == IX_ETH_DB_FIREWALL_RECORD)
    {
        IX_ETH_DB_CHECK_PORT_EXISTS(portID);

        result = ixEthDBPortSearch(macAddr, portID, recordType);
    }
    else
    {
        return IX_ETH_DB_INVALID_ARG;
    }

    if (result == NULL)
    {
        return IX_ETH_DB_NO_SUCH_ADDR;
    }

    ((MacDescriptor *) result->data)->user = field;

    ixEthDBReleaseHashNode(result);

    return IX_ETH_DB_SUCCESS;
}

IX_ETH_DB_PUBLIC
IxEthDBStatus ixEthDBUserFieldGet(IxEthDBRecordType recordType, IxEthDBMacAddr *macAddr, IxEthDBPortId portID, IxEthDBVlanId vlanID, void **field)
{
    HashNode *result = NULL;

    if (macAddr == NULL || field == NULL)
    {
        return IX_ETH_DB_INVALID_ARG;
    }

    if (recordType == IX_ETH_DB_FILTERING_RECORD)
    {
        result = ixEthDBSearch(macAddr, recordType);
    }
    else if (recordType == IX_ETH_DB_FILTERING_VLAN_RECORD)
    {
        result = ixEthDBVlanSearch(macAddr, vlanID, recordType);
    }
    else if (recordType == IX_ETH_DB_WIFI_RECORD || recordType == IX_ETH_DB_FIREWALL_RECORD)
    {
        IX_ETH_DB_CHECK_PORT_EXISTS(portID);

        result = ixEthDBPortSearch(macAddr, portID, recordType);
    }
    else
    {
        return IX_ETH_DB_INVALID_ARG;
    }

    if (result == NULL)
    {
        return IX_ETH_DB_NO_SUCH_ADDR;
    }

    *field = ((MacDescriptor *) result->data)->user;

    ixEthDBReleaseHashNode(result);

    return IX_ETH_DB_SUCCESS;
}
