

#ifndef IXQMGRQCFG_P_H
#define IXQMGRQCFG_P_H

#include "IxQMgr.h"

typedef struct
{
    unsigned wmSetCnt;    

    struct
    {
	char *qName;
	BOOL isConfigured;	
	unsigned int qSizeInWords;
	unsigned int qEntrySizeInWords;
	unsigned int ne;
	unsigned int nf;
	unsigned int numEntries;
	UINT32 baseAddress;
	UINT32 readPtr;
	UINT32 writePtr;
    } qStats[IX_QMGR_MAX_NUM_QUEUES];

} IxQMgrQCfgStats;

void
ixQMgrQCfgInit (void);

void
ixQMgrQCfgUninit (void);

IxQMgrQSizeInWords
ixQMgrQSizeInWordsGet (IxQMgrQId qId);

IxQMgrQEntrySizeInWords
ixQMgrQEntrySizeInWordsGet (IxQMgrQId qId);

IxQMgrQCfgStats*
ixQMgrQCfgStatsGet (void);

IxQMgrQCfgStats*
ixQMgrQCfgQStatsGet (IxQMgrQId qId);

BOOL
ixQMgrQIsConfigured(IxQMgrQId qId);
 
#endif /* IX_QMGRQCFG_P_H */
