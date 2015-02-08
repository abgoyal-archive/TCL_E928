


#ifndef IXNPEMHUNSOLICITEDCBMGR_P_H
#define IXNPEMHUNSOLICITEDCBMGR_P_H

#include "IxNpeMh.h"
#include "IxOsalTypes.h"




void ixNpeMhUnsolicitedCbMgrInitialize (void);


void ixNpeMhUnsolicitedCbMgrCallbackSave (
    IxNpeMhNpeId npeId,
    IxNpeMhMessageId unsolicitedMessageId,
    IxNpeMhCallback unsolicitedCallback);


void ixNpeMhUnsolicitedCbMgrCallbackRetrieve (
    IxNpeMhNpeId npeId,
    IxNpeMhMessageId unsolicitedMessageId,
    IxNpeMhCallback *unsolicitedCallback);


void ixNpeMhUnsolicitedCbMgrShow (
    IxNpeMhNpeId npeId);


void ixNpeMhUnsolicitedCbMgrShowReset (
    IxNpeMhNpeId npeId);

#endif /* IXNPEMHUNSOLICITEDCBMGR_P_H */

