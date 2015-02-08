



#include "IxOsal.h"

#include "IxNpeMhMacros_p.h"

#include "IxNpeMhUnsolicitedCbMgr_p.h"





typedef struct
{
    /** array of entries */
    IxNpeMhCallback entries[IX_NPEMH_MAX_MESSAGE_ID + 1];
} IxNpeMhUnsolicitedCallbackTable;


typedef struct
{
    UINT32 saves;      /**< callback table saves */
    UINT32 overwrites; /**< callback table overwrites */
} IxNpeMhUnsolicitedCbMgrStats;


PRIVATE IxNpeMhUnsolicitedCallbackTable
ixNpeMhUnsolicitedCallbackTables[IX_NPEMH_NUM_NPES];

PRIVATE IxNpeMhUnsolicitedCbMgrStats
ixNpeMhUnsolicitedCbMgrStats[IX_NPEMH_NUM_NPES];




void ixNpeMhUnsolicitedCbMgrInitialize (void)
{
    IxNpeMhNpeId npeId = 0;
    IxNpeMhUnsolicitedCallbackTable *table = NULL;
    IxNpeMhMessageId messageId = 0;

    IX_NPEMH_TRACE0 (IX_NPEMH_FN_ENTRY_EXIT, "Entering "
                     "ixNpeMhUnsolicitedCbMgrInitialize\n");

    /* for each NPE ... */
    for (npeId = 0; npeId < IX_NPEMH_NUM_NPES; npeId++)
    {
        /* initialise a pointer to the table for convenience */
        table = &ixNpeMhUnsolicitedCallbackTables[npeId];

        /* for each message ID ... */
        for (messageId = IX_NPEMH_MIN_MESSAGE_ID;
             messageId <= IX_NPEMH_MAX_MESSAGE_ID; messageId++)
        {
            /* initialise the callback for this message ID to NULL */
            table->entries[messageId] = NULL;
        }
    }

    IX_NPEMH_TRACE0 (IX_NPEMH_FN_ENTRY_EXIT, "Exiting "
                     "ixNpeMhUnsolicitedCbMgrInitialize\n");
}


void ixNpeMhUnsolicitedCbMgrCallbackSave (
    IxNpeMhNpeId npeId,
    IxNpeMhMessageId unsolicitedMessageId,
    IxNpeMhCallback unsolicitedCallback)
{
    IxNpeMhUnsolicitedCallbackTable *table = NULL;

    /* initialise a pointer to the table for convenience */
    table = &ixNpeMhUnsolicitedCallbackTables[npeId];

    IX_NPEMH_TRACE0 (IX_NPEMH_FN_ENTRY_EXIT, "Entering "
                     "ixNpeMhUnsolicitedCbMgrCallbackSave\n");

    /* update statistical info */
    ixNpeMhUnsolicitedCbMgrStats[npeId].saves++;

    /* check if there is a callback already registered for this NPE and */
    /* message ID */
    if (table->entries[unsolicitedMessageId] != NULL)
    {
	/* if we are overwriting an existing callback */
	if (unsolicitedCallback != NULL)
	{
	    IX_NPEMH_TRACE2 (IX_NPEMH_DEBUG, "Unsolicited callback "
			     "overwriting existing callback for NPE ID %d "
			     "message ID 0x%02X\n", npeId, unsolicitedMessageId);
	}
	else /* if we are clearing an existing callback */
	{
	    IX_NPEMH_TRACE2 (IX_NPEMH_DEBUG, "NULL unsolicited callback "
			     "clearing existing callback for NPE ID %d "
			     "message ID 0x%02X\n", npeId, unsolicitedMessageId);
	}

        /* update statistical info */
        ixNpeMhUnsolicitedCbMgrStats[npeId].overwrites++;
    }

    /* save the callback into the table */
    table->entries[unsolicitedMessageId] = unsolicitedCallback;

    IX_NPEMH_TRACE0 (IX_NPEMH_FN_ENTRY_EXIT, "Exiting "
                     "ixNpeMhUnsolicitedCbMgrCallbackSave\n");
}


void ixNpeMhUnsolicitedCbMgrCallbackRetrieve (
    IxNpeMhNpeId npeId,
    IxNpeMhMessageId unsolicitedMessageId,
    IxNpeMhCallback *unsolicitedCallback)
{
    IxNpeMhUnsolicitedCallbackTable *table = NULL;

    /* initialise a pointer to the table for convenience */
    table = &ixNpeMhUnsolicitedCallbackTables[npeId];

    /* retrieve the callback from the table */
    *unsolicitedCallback = table->entries[unsolicitedMessageId];
}


void ixNpeMhUnsolicitedCbMgrShow (
    IxNpeMhNpeId npeId)
{
    /* show the unsolicited callback table save counter */
    IX_NPEMH_SHOW ("Unsolicited callback table saves",
                   ixNpeMhUnsolicitedCbMgrStats[npeId].saves);

    /* show the unsolicited callback table overwrite counter */
    IX_NPEMH_SHOW ("Unsolicited callback table overwrites",
                   ixNpeMhUnsolicitedCbMgrStats[npeId].overwrites);
}


void ixNpeMhUnsolicitedCbMgrShowReset (
    IxNpeMhNpeId npeId)
{
    /* reset the unsolicited callback table save counter */
    ixNpeMhUnsolicitedCbMgrStats[npeId].saves = 0;

    /* reset the unsolicited callback table overwrite counter */
    ixNpeMhUnsolicitedCbMgrStats[npeId].overwrites = 0;
}
