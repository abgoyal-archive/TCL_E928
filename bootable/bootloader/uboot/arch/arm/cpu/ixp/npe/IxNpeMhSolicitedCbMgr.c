
#ifndef IXNPEMHCONFIG_P_H
#	define IXNPEMHSOLICITEDCBMGR_C
#else
#	error "Error, IxNpeMhConfig_p.h should not be included before this definition."
#endif




#include "IxOsal.h"

#include "IxNpeMhMacros_p.h"
#include "IxNpeMhSolicitedCbMgr_p.h"
#include "IxNpeMhConfig_p.h"



typedef struct IxNpeMhSolicitedCallbackListEntry
{
    /** message ID */
    IxNpeMhMessageId messageId;

    /** callback function pointer */
    IxNpeMhCallback callback;

    /** pointer to next entry in the list */
    struct IxNpeMhSolicitedCallbackListEntry *next;
} IxNpeMhSolicitedCallbackListEntry;


typedef struct
{
    /** pointer to the head of the free list */
    IxNpeMhSolicitedCallbackListEntry *freeHead;

    /** pointer to the head of the callback list */
    IxNpeMhSolicitedCallbackListEntry *callbackHead;

    /** pointer to the tail of the callback list */
    IxNpeMhSolicitedCallbackListEntry *callbackTail;

    /** array of entries - the first entry is used as a dummy entry to */
    /* avoid the scenario of having an empty list, hence '+ 1' */
    IxNpeMhSolicitedCallbackListEntry entries[IX_NPEMH_MAX_CALLBACKS + 1];
} IxNpeMhSolicitedCallbackList;


typedef struct
{
    UINT32 saves;     /**< callback list saves */
    UINT32 retrieves; /**< callback list retrieves */
} IxNpeMhSolicitedCbMgrStats;


PRIVATE IxNpeMhSolicitedCallbackList
ixNpeMhSolicitedCbMgrCallbackLists[IX_NPEMH_NUM_NPES];

PRIVATE IxNpeMhSolicitedCbMgrStats
ixNpeMhSolicitedCbMgrStats[IX_NPEMH_NUM_NPES];




void ixNpeMhSolicitedCbMgrInitialize (void)
{
    IxNpeMhNpeId npeId;
    UINT32 localIndex;
    IxNpeMhSolicitedCallbackList *list = NULL;

    IX_NPEMH_TRACE0 (IX_NPEMH_FN_ENTRY_EXIT, "Entering "
                     "ixNpeMhSolicitedCbMgrInitialize\n");

    /* for each NPE ... */
    for (npeId = 0; npeId < IX_NPEMH_NUM_NPES; npeId++)
    {
        /* initialise a pointer to the list for convenience */
        list = &ixNpeMhSolicitedCbMgrCallbackLists[npeId];

        /* for each entry in the list, after the dummy entry ... */
        for (localIndex = 1; localIndex <= IX_NPEMH_MAX_CALLBACKS; localIndex++)
        {
            /* initialise the entry */
            list->entries[localIndex].messageId = 0x00;
            list->entries[localIndex].callback = NULL;

            /* if this entry is before the last entry */
            if (localIndex < IX_NPEMH_MAX_CALLBACKS)
            {
                /* chain this entry to the following entry */
                list->entries[localIndex].next = &(list->entries[localIndex + 1]);
            }
            else /* this entry is the last entry */
            {
                /* the last entry isn't chained to anything */
                list->entries[localIndex].next = NULL;
            }
        }

        /* set the free list pointer to point to the first real entry */
        /* (all real entries begin chained together on the free list) */
        list->freeHead = &(list->entries[1]);

        /* set the callback list pointers to point to the dummy entry */
        /* (the callback list is initially empty) */
        list->callbackHead = &(list->entries[0]);
        list->callbackTail = &(list->entries[0]);
    }

    IX_NPEMH_TRACE0 (IX_NPEMH_FN_ENTRY_EXIT, "Exiting "
                     "ixNpeMhSolicitedCbMgrInitialize\n");
}


IX_STATUS ixNpeMhSolicitedCbMgrCallbackSave (
    IxNpeMhNpeId npeId,
    IxNpeMhMessageId solicitedMessageId,
    IxNpeMhCallback solicitedCallback)
{
    IxNpeMhSolicitedCallbackList *list = NULL;
    IxNpeMhSolicitedCallbackListEntry *callbackEntry = NULL;

    IX_NPEMH_TRACE0 (IX_NPEMH_FN_ENTRY_EXIT, "Entering "
                     "ixNpeMhSolicitedCbMgrCallbackSave\n");

    /* initialise a pointer to the list for convenience */
    list = &ixNpeMhSolicitedCbMgrCallbackLists[npeId];

    /* check to see if there are any entries in the free list */
    if (list->freeHead == NULL)
    {
        IX_NPEMH_ERROR_REPORT ("Solicited callback list is full\n");
        return IX_FAIL;
    }

    /* there is an entry in the free list we can use */

    /* update statistical info */
    ixNpeMhSolicitedCbMgrStats[npeId].saves++;

    /* remove a callback entry from the start of the free list */
    callbackEntry = list->freeHead;
    list->freeHead = callbackEntry->next;

    /* fill in the callback entry with the new data */
    callbackEntry->messageId = solicitedMessageId;
    callbackEntry->callback = solicitedCallback;

    /* the new callback entry will be added to the tail of the callback */
    /* list, so it isn't chained to anything */
    callbackEntry->next = NULL;

    /* chain new callback entry to the last entry of the callback list */
    list->callbackTail->next = callbackEntry;
    list->callbackTail = callbackEntry;

    IX_NPEMH_TRACE0 (IX_NPEMH_FN_ENTRY_EXIT, "Exiting "
                     "ixNpeMhSolicitedCbMgrCallbackSave\n");

    return IX_SUCCESS;
}


void ixNpeMhSolicitedCbMgrCallbackRetrieve (
    IxNpeMhNpeId npeId,
    IxNpeMhMessageId solicitedMessageId,
    IxNpeMhCallback *solicitedCallback)
{
    IxNpeMhSolicitedCallbackList *list = NULL;
    IxNpeMhSolicitedCallbackListEntry *callbackEntry = NULL;
    IxNpeMhSolicitedCallbackListEntry *previousEntry = NULL;

    /* initialise a pointer to the list for convenience */
    list = &ixNpeMhSolicitedCbMgrCallbackLists[npeId];

    /* initialise the callback entry to the first entry of the callback */
    /* list - we must skip over the dummy entry, which is the previous */
    callbackEntry = list->callbackHead->next;
    previousEntry = list->callbackHead;

    /* traverse the callback list looking for an entry with a matching */
    /* message ID.  note we also save the previous entry's pointer to */
    /* allow us to unchain the matching entry from the callback list */
    while ((callbackEntry != NULL) &&
           (callbackEntry->messageId != solicitedMessageId))
    {
        previousEntry = callbackEntry;
        callbackEntry = callbackEntry->next;
    }

    /* if we didn't find a matching callback entry */
    if (callbackEntry == NULL)
    {
        /* return a NULL callback in the outgoing parameter */
        *solicitedCallback = NULL;
    }
    else /* we found a matching callback entry */
    {
        /* update statistical info */
        ixNpeMhSolicitedCbMgrStats[npeId].retrieves++;

        /* return the callback in the outgoing parameter */
        *solicitedCallback = callbackEntry->callback;

        /* unchain callback entry by chaining previous entry to next */
        previousEntry->next = callbackEntry->next;

        /* if the callback entry is at the tail of the list */
        if (list->callbackTail == callbackEntry)
        {
            /* update the tail of the callback list */
            list->callbackTail = previousEntry;
        }

        /* re-initialise the callback entry */
        callbackEntry->messageId = 0x00;
        callbackEntry->callback = NULL;

        /* add the callback entry to the start of the free list */
        callbackEntry->next = list->freeHead;
        list->freeHead = callbackEntry;
    }
}


void ixNpeMhSolicitedCbMgrShow (
    IxNpeMhNpeId npeId)
{
    /* show the solicited callback list save counter */
    IX_NPEMH_SHOW ("Solicited callback list saves",
                   ixNpeMhSolicitedCbMgrStats[npeId].saves);

    /* show the solicited callback list retrieve counter */
    IX_NPEMH_SHOW ("Solicited callback list retrieves",
                   ixNpeMhSolicitedCbMgrStats[npeId].retrieves);
}


void ixNpeMhSolicitedCbMgrShowReset (
    IxNpeMhNpeId npeId)
{
    /* reset the solicited callback list save counter */
    ixNpeMhSolicitedCbMgrStats[npeId].saves = 0;

    /* reset the solicited callback list retrieve counter */
    ixNpeMhSolicitedCbMgrStats[npeId].retrieves = 0;
}
