


#ifndef IXATMSCH_H
#define IXATMSCH_H

#include "IxOsalTypes.h"
#include "IxAtmTypes.h"


/* Return codes */

#define IX_ATMSCH_RET_NOT_ADMITTED 2

#define IX_ATMSCH_RET_QUEUE_FULL 3

#define IX_ATMSCH_RET_QUEUE_EMPTY 4


PUBLIC IX_STATUS
ixAtmSchInit(void);

PUBLIC IX_STATUS
ixAtmSchPortModelInitialize( IxAtmLogicalPort port,
                                       unsigned int portRate,
                                       unsigned int minCellsToSchedule);

PUBLIC IX_STATUS
ixAtmSchPortRateModify( IxAtmLogicalPort port,
                        unsigned int portRate);


PUBLIC IX_STATUS
ixAtmSchVcModelSetup( IxAtmLogicalPort port,
                      IxAtmTrafficDescriptor *trafficDesc,
                      IxAtmSchedulerVcId *vcId);

PUBLIC IX_STATUS
ixAtmSchVcConnIdSet( IxAtmLogicalPort port,
                     IxAtmSchedulerVcId vcId,
                     IxAtmConnId vcUserConnId);

PUBLIC IX_STATUS
ixAtmSchVcModelRemove( IxAtmLogicalPort port,
                       IxAtmSchedulerVcId vcId);

PUBLIC IX_STATUS
ixAtmSchVcQueueUpdate( IxAtmLogicalPort port,
                       IxAtmSchedulerVcId vcId,
                       unsigned int numberOfCells);

PUBLIC IX_STATUS
ixAtmSchVcQueueClear( IxAtmLogicalPort port,
                      IxAtmSchedulerVcId vcId);

PUBLIC IX_STATUS
ixAtmSchTableUpdate( IxAtmLogicalPort port,
                     unsigned int maxCells,
                     IxAtmScheduleTable **rettable);

PUBLIC void
ixAtmSchShow(void);

PUBLIC void
ixAtmSchStatsClear(void);

#endif
/* IXATMSCH_H */

/** @} */
