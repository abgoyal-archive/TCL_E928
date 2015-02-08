


#ifndef IXNPEMHRECEIVE_P_H
#define IXNPEMHRECEIVE_P_H

#include "IxNpeMh.h"
#include "IxOsalTypes.h"




void ixNpeMhReceiveInitialize (void);


IX_STATUS ixNpeMhReceiveMessagesReceive (
    IxNpeMhNpeId npeId);


void ixNpeMhReceiveShow (
    IxNpeMhNpeId npeId);


void ixNpeMhReceiveShowReset (
    IxNpeMhNpeId npeId);

#endif /* IXNPEMHRECEIVE_P_H */

