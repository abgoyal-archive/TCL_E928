


#ifndef IXNPEMHSOLICITEDCBMGR_P_H
#define IXNPEMHSOLICITEDCBMGR_P_H

#include "IxNpeMh.h"
#include "IxOsalTypes.h"


/** Maximum number of solicited callbacks that can be stored in the list */
#define IX_NPEMH_MAX_CALLBACKS (16)



void ixNpeMhSolicitedCbMgrInitialize (void);


IX_STATUS ixNpeMhSolicitedCbMgrCallbackSave (
    IxNpeMhNpeId npeId,
    IxNpeMhMessageId solicitedMessageId,
    IxNpeMhCallback solicitedCallback);


void ixNpeMhSolicitedCbMgrCallbackRetrieve (
    IxNpeMhNpeId npeId,
    IxNpeMhMessageId solicitedMessageId,
    IxNpeMhCallback *solicitedCallback);


void ixNpeMhSolicitedCbMgrShow (
    IxNpeMhNpeId npeId);


void ixNpeMhSolicitedCbMgrShowReset (
    IxNpeMhNpeId npeId);

#endif /* IXNPEMHSOLICITEDCBMGR_P_H */

