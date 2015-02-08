

#ifndef XVERSION_H		/* prevent circular inclusions */
#define XVERSION_H		/* by using protection macros */

/***************************** Include Files *********************************/

#include "xbasic_types.h"
#include "xstatus.h"

/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

typedef s8 XVersion[6];

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Function Prototypes ******************************/

void XVersion_UnPack(XVersion * InstancePtr, u16 PackedVersion);

XStatus XVersion_Pack(XVersion * InstancePtr, u16 * PackedVersion);

u32 XVersion_IsEqual(XVersion * InstancePtr, XVersion * VersionPtr);

void XVersion_ToString(XVersion * InstancePtr, s8 * StringPtr);

XStatus XVersion_FromString(XVersion * InstancePtr, s8 * StringPtr);

void XVersion_Copy(XVersion * InstancePtr, XVersion * VersionPtr);

#endif				/* end of protection macro */
