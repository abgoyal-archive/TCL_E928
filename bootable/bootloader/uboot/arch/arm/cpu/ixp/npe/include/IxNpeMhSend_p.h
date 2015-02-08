


#ifndef IXNPEMHSEND_P_H
#define IXNPEMHSEND_P_H

#include "IxNpeMh.h"
#include "IxOsalTypes.h"




IX_STATUS ixNpeMhSendMessageSend (
    IxNpeMhNpeId npeId,
    IxNpeMhMessage message,
    UINT32 maxSendRetries);


IX_STATUS ixNpeMhSendMessageWithResponseSend (
    IxNpeMhNpeId npeId,
    IxNpeMhMessage message,
    IxNpeMhMessageId solicitedMessageId,
    IxNpeMhCallback solicitedCallback,
    UINT32 maxSendRetries);


void ixNpeMhSendShow (
    IxNpeMhNpeId npeId);


void ixNpeMhSendShowReset (
    IxNpeMhNpeId npeId);

#endif /* IXNPEMHSEND_P_H */

