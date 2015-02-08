


#ifndef IXNPEMH_H
#define IXNPEMH_H

#include "IxOsalTypes.h"


#define IX_NPEMH_MIN_MESSAGE_ID (0x00) /**< minimum valid message ID */
#define IX_NPEMH_MAX_MESSAGE_ID (0xFF) /**< maximum valid message ID */

#define IX_NPEMH_SEND_RETRIES_DEFAULT (3) /**< default msg send retries */


#define IX_NPEMH_CRITICAL_NPE_ERR        2


typedef enum
{
    IX_NPEMH_NPEID_NPEA = 0, /**< ID for NPE-A */
    IX_NPEMH_NPEID_NPEB,     /**< ID for NPE-B */
    IX_NPEMH_NPEID_NPEC,     /**< ID for NPE-C */
    IX_NPEMH_NUM_NPES        /**< Number of NPEs */
} IxNpeMhNpeId;


typedef enum
{
    IX_NPEMH_NPEINTERRUPTS_NO = 0, /**< Don't use NPE interrupts */
    IX_NPEMH_NPEINTERRUPTS_YES     /**< Do use NPE interrupts */
} IxNpeMhNpeInterrupts;


typedef struct
{
    UINT32 data[2]; /**< the actual data of the message */
} IxNpeMhMessage;

/** message ID */
typedef UINT32 IxNpeMhMessageId;


typedef void (*IxNpeMhCallback) (IxNpeMhNpeId, IxNpeMhMessage);



PUBLIC IX_STATUS ixNpeMhInitialize (
    IxNpeMhNpeInterrupts npeInterrupts);


PUBLIC IX_STATUS ixNpeMhUnload (void);


PUBLIC IX_STATUS ixNpeMhUnsolicitedCallbackRegister (
    IxNpeMhNpeId npeId,
    IxNpeMhMessageId messageId,
    IxNpeMhCallback unsolicitedCallback);


PUBLIC IX_STATUS ixNpeMhUnsolicitedCallbackForRangeRegister (
    IxNpeMhNpeId npeId,
    IxNpeMhMessageId minMessageId,
    IxNpeMhMessageId maxMessageId,
    IxNpeMhCallback unsolicitedCallback);


PUBLIC IX_STATUS ixNpeMhMessageSend (
    IxNpeMhNpeId npeId,
    IxNpeMhMessage message,
    UINT32 maxSendRetries);


PUBLIC IX_STATUS ixNpeMhMessageWithResponseSend (
    IxNpeMhNpeId npeId,
    IxNpeMhMessage message,
    IxNpeMhMessageId solicitedMessageId,
    IxNpeMhCallback solicitedCallback,
    UINT32 maxSendRetries);


PUBLIC IX_STATUS ixNpeMhMessagesReceive (
    IxNpeMhNpeId npeId);


PUBLIC IX_STATUS ixNpeMhShow (
    IxNpeMhNpeId npeId);


PUBLIC IX_STATUS ixNpeMhShowReset (
    IxNpeMhNpeId npeId);

#endif /* IXNPEMH_H */

