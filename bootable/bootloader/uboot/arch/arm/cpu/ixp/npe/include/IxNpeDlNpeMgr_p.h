



#ifndef IXNPEDLNPEMGR_P_H
#define IXNPEDLNPEMGR_P_H


#include "IxNpeDl.h"
#include "IxOsalTypes.h"




void
ixNpeDlNpeMgrInit (void);



IX_STATUS ixNpeDlNpeMgrUninit (void);


IX_STATUS
ixNpeDlNpeMgrImageLoad (IxNpeDlNpeId npeId, UINT32 *imageCodePtr,
			  BOOL verify);


IX_STATUS
ixNpeDlNpeMgrNpeReset (IxNpeDlNpeId npeId);


IX_STATUS
ixNpeDlNpeMgrNpeStart (IxNpeDlNpeId npeId);


IX_STATUS
ixNpeDlNpeMgrNpeStop (IxNpeDlNpeId npeId);


void
ixNpeDlNpeMgrStatsShow (void);


void
ixNpeDlNpeMgrStatsReset (void);


#endif /* IXNPEDLIMAGEMGR_P_H */

