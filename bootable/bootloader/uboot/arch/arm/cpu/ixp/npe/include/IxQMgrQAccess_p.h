

#ifndef IXQMGRQACCESS_P_H
#define IXQMGRQACCESS_P_H

#include "IxQMgr.h"

extern volatile UINT32 * ixQMgrAqmIfQueAccRegAddr[]; 

void
ixQMgrQAccessInit (void);

IX_STATUS
ixQMgrQReadMWordsMinus1 (IxQMgrQId qId,
                         UINT32 *entry);

extern __inline__ UINT32 ixQMgrQAccessPop(IxQMgrQId qId);

extern __inline__ UINT32 ixQMgrQAccessPop(IxQMgrQId qId)
{
  return *(ixQMgrAqmIfQueAccRegAddr[qId]);
}

extern __inline__ void ixQMgrQAccessPush(IxQMgrQId qId, UINT32 entry);

extern __inline__ void ixQMgrQAccessPush(IxQMgrQId qId, UINT32 entry)
{
  *(ixQMgrAqmIfQueAccRegAddr[qId]) = entry;
}

#endif/*IXQMGRQACCESS_P_H*/
