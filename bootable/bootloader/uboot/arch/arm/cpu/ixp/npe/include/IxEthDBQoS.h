


#ifndef IxEthDBQoS_H
#define IxEthDBQoS_H

#define IX_ETH_DB_QUEUE_UNAVAILABLE  (0)

#ifndef IX_IEEE802_1Q_QOS_PRIORITY_COUNT
#define IX_IEEE802_1Q_QOS_PRIORITY_COUNT (8)
#endif

static const
UINT8 ixEthDBQueueAssignments[][IX_IEEE802_1Q_QOS_PRIORITY_COUNT] = 
{
    { 4, 5, 6, 7, IX_ETH_DB_QUEUE_UNAVAILABLE, IX_ETH_DB_QUEUE_UNAVAILABLE, IX_ETH_DB_QUEUE_UNAVAILABLE, IX_ETH_DB_QUEUE_UNAVAILABLE },
    { 15, 16, 17, 18, IX_ETH_DB_QUEUE_UNAVAILABLE, IX_ETH_DB_QUEUE_UNAVAILABLE, IX_ETH_DB_QUEUE_UNAVAILABLE, IX_ETH_DB_QUEUE_UNAVAILABLE },
    { 11, 23, 26, IX_ETH_DB_QUEUE_UNAVAILABLE, IX_ETH_DB_QUEUE_UNAVAILABLE, IX_ETH_DB_QUEUE_UNAVAILABLE, IX_ETH_DB_QUEUE_UNAVAILABLE,  IX_ETH_DB_QUEUE_UNAVAILABLE },
    { 4, 5, 6, 7, 8, 9, 10, 11 }
    /* add here all other cases of queue configuration structures and update ixEthDBTrafficClassDefinitions to use them */
};

#define IX_ETH_DB_NPE_A_FUNCTIONALITY_ID_INDEX    (0)

#define IX_ETH_DB_TRAFFIC_CLASS_COUNT_INDEX       (1)

#define IX_ETH_DB_QUEUE_ASSIGNMENT_INDEX          (2)

static const
UINT8 ixEthDBTrafficClassDefinitions[][3] = 
{
    /* NPE A functionality ID | traffic class count | queue assignment index (points to the queue enumeration in ixEthDBQueueAssignments) */
    {            0x00,                      4,                    0 }, /* default case - DO NOT REMOVE */
    {            0x04,                      4,                    1 }, /* NPE A image ID 0.4.0.0 */
    {            0x09,                      3,                    2 }, /* NPE A image ID 0.9.0.0 */
    {            0x80,                      8,                    3 }, /* NPE A image ID 10.80.02.0 */
    {            0x81,                      8,                    3 }, /* NPE A image ID 10.81.02.0 */
    {            0x82,                      8,                    3 }  /* NPE A image ID 10.82.02.0 */
};

static const
UINT8 ixEthIEEE802_1QUserPriorityToTrafficClassMapping[IX_IEEE802_1Q_QOS_PRIORITY_COUNT][IX_IEEE802_1Q_QOS_PRIORITY_COUNT] = 
 {
     { 0, 0, 0, 0, 0, 0, 0, 0 }, /* 1 traffic class available */
     { 0, 0, 0, 0, 1, 1, 1, 1 }, /* 2 traffic classes available */
     { 0, 0, 0, 0, 1, 1, 2, 2 }, /* 3 traffic classes available */
     { 1, 0, 0, 1, 2, 2, 3, 3 }, /* 4 traffic classes available */
     { 1, 0, 0, 1, 2, 3, 4, 4 }, /* 5 traffic classes available */
     { 1, 0, 0, 2, 3, 4, 5, 5 }, /* 6 traffic classes available */
     { 1, 0, 0, 2, 3, 4, 5, 6 }, /* 7 traffic classes available */
     { 2, 0, 1, 3, 4, 5, 6, 7 }  /* 8 traffic classes available */
 };

#endif /* IxEthDBQoS_H */

