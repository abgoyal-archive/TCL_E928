



#ifndef IXNPEDLNPEMGRUTILS_P_H
#define IXNPEDLNPEMGRUTILS_P_H


#include "IxNpeDl.h"
#include "IxOsalTypes.h"
#include "IxNpeDlNpeMgrEcRegisters_p.h"



IX_STATUS
ixNpeDlNpeMgrInsMemWrite (UINT32 npeBaseAddress, UINT32 insMemAddress,
			  UINT32 insMemData, BOOL verify);


IX_STATUS
ixNpeDlNpeMgrDataMemWrite (UINT32 npeBaseAddress, UINT32 dataMemAddress,
			   UINT32 dataMemData, BOOL verify);


void
ixNpeDlNpeMgrExecAccRegWrite (UINT32 npeBaseAddress, UINT32 regAddress,
			      UINT32 regData);


UINT32
ixNpeDlNpeMgrExecAccRegRead (UINT32 npeBaseAddress, UINT32 regAddress);


void
ixNpeDlNpeMgrCommandIssue (UINT32 npeBaseAddress, UINT32 command);


void
ixNpeDlNpeMgrDebugInstructionPreExec (UINT32 npeBaseAddress);


IX_STATUS
ixNpeDlNpeMgrDebugInstructionExec (UINT32 npeBaseAddress,
				   UINT32 npeInstruction,
				   UINT32 ctxtNum, UINT32 ldur);


void
ixNpeDlNpeMgrDebugInstructionPostExec (UINT32 npeBaseAddress);


IX_STATUS
ixNpeDlNpeMgrPhysicalRegWrite (UINT32 npeBaseAddress, UINT32 regAddr,
			       UINT32 regValue, BOOL verify);


IX_STATUS
ixNpeDlNpeMgrCtxtRegWrite (UINT32 npeBaseAddress, UINT32 ctxtNum,
			   IxNpeDlCtxtRegNum ctxtReg, UINT32 ctxtRegVal,
			   BOOL verify);


void
ixNpeDlNpeMgrUtilsStatsShow (void);


void
ixNpeDlNpeMgrUtilsStatsReset (void);


#endif  /* IXNPEDLNPEMGRUTILS_P_H */
