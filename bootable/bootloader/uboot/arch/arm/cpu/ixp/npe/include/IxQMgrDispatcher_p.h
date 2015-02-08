

#ifndef IXQMGRDISPATCHER_P_H
#define IXQMGRDISPATCHER_P_H

#include "IxQMgr.h"

typedef struct
{
    unsigned callbackCnt;       /* Call count of callback                    */
    unsigned priorityChangeCnt; /* Priority change count                     */
    unsigned intNoCallbackCnt;  /* Interrupt fired but no callback set count */
    unsigned intLostCallbackCnt;  /* Interrupt lost and detected ;  SCR541   */
    BOOL notificationEnabled;    /* Interrupt enabled for this queue         */
    IxQMgrSourceId srcSel;       /* interrupt source                         */
    unsigned enableCount;        /* num times notif enabled by LLP           */
    unsigned disableCount;       /* num of times notif disabled by LLP       */
} IxQMgrDispatcherQStats;

typedef struct
 {
    unsigned loopRunCnt;       /* ixQMgrDispatcherLoopRun count */

    IxQMgrDispatcherQStats queueStats[IX_QMGR_MAX_NUM_QUEUES];

} IxQMgrDispatcherStats;

void
ixQMgrDispatcherInit (void);

IxQMgrDispatcherStats*
ixQMgrDispatcherStatsGet (void);

unsigned int
ixQMgrCountLeadingZeros(unsigned int value);

#endif/*IXQMGRDISPATCHER_P_H*/


