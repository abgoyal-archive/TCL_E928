

#ifndef XBUF_DESCRIPTOR_H	/* prevent circular inclusions */
#define XBUF_DESCRIPTOR_H	/* by using protection macros */

/***************************** Include Files *********************************/

#include "xbasic_types.h"
#include "xdma_channel_i.h"

/************************** Constant Definitions *****************************/


#define XBD_DEVICE_STATUS_OFFSET    0
#define XBD_CONTROL_OFFSET	    1
#define XBD_SOURCE_OFFSET	    2
#define XBD_DESTINATION_OFFSET	    3
#define XBD_LENGTH_OFFSET	    4
#define XBD_STATUS_OFFSET	    5
#define XBD_NEXT_PTR_OFFSET	    6
#define XBD_ID_OFFSET		    7
#define XBD_FLAGS_OFFSET	    8
#define XBD_RQSTED_LENGTH_OFFSET    9

#define XBD_SIZE_IN_WORDS	    10


#define XBD_FLAGS_LOCKED_MASK	    1UL

/**************************** Type Definitions *******************************/

typedef u32 XBufDescriptor[XBD_SIZE_IN_WORDS];

/***************** Macros (Inline Functions) Definitions *********************/


#define XBufDescriptor_Initialize(InstancePtr)			\
{								\
    (*((u32 *)InstancePtr + XBD_CONTROL_OFFSET) = 0);	    \
    (*((u32 *)InstancePtr + XBD_SOURCE_OFFSET) = 0);	    \
    (*((u32 *)InstancePtr + XBD_DESTINATION_OFFSET) = 0);   \
    (*((u32 *)InstancePtr + XBD_LENGTH_OFFSET) = 0);	    \
    (*((u32 *)InstancePtr + XBD_STATUS_OFFSET) = 0);	    \
    (*((u32 *)InstancePtr + XBD_DEVICE_STATUS_OFFSET) = 0); \
    (*((u32 *)InstancePtr + XBD_NEXT_PTR_OFFSET) = 0);	    \
    (*((u32 *)InstancePtr + XBD_ID_OFFSET) = 0);	    \
    (*((u32 *)InstancePtr + XBD_FLAGS_OFFSET) = 0);	    \
    (*((u32 *)InstancePtr + XBD_RQSTED_LENGTH_OFFSET) = 0); \
}

#define XBufDescriptor_GetControl(InstancePtr)	 \
    (u32)(*((u32 *)InstancePtr + XBD_CONTROL_OFFSET))

#define XBufDescriptor_SetControl(InstancePtr, Control)	 \
    (*((u32 *)InstancePtr + XBD_CONTROL_OFFSET) = (u32)Control)

#define XBufDescriptor_IsLastControl(InstancePtr) \
    (u32)(*((u32 *)InstancePtr + XBD_CONTROL_OFFSET) & \
	       XDC_CONTROL_LAST_BD_MASK)

#define XBufDescriptor_SetLast(InstancePtr) \
    (*((u32 *)InstancePtr + XBD_CONTROL_OFFSET) |= XDC_CONTROL_LAST_BD_MASK)

#define XBufDescriptor_GetSrcAddress(InstancePtr) \
    ((u32 *)(*((u32 *)InstancePtr + XBD_SOURCE_OFFSET)))

#define XBufDescriptor_SetSrcAddress(InstancePtr, Source) \
    (*((u32 *)InstancePtr + XBD_SOURCE_OFFSET) = (u32)Source)

#define XBufDescriptor_GetDestAddress(InstancePtr) \
    ((u32 *)(*((u32 *)InstancePtr + XBD_DESTINATION_OFFSET)))

#define XBufDescriptor_SetDestAddress(InstancePtr, Destination) \
    (*((u32 *)InstancePtr + XBD_DESTINATION_OFFSET) = (u32)Destination)

#define XBufDescriptor_GetLength(InstancePtr)				\
    (u32)(*((u32 *)InstancePtr + XBD_RQSTED_LENGTH_OFFSET) -	\
	      *((u32 *)InstancePtr + XBD_LENGTH_OFFSET))

#define XBufDescriptor_SetLength(InstancePtr, Length)			    \
{									    \
    (*((u32 *)InstancePtr + XBD_LENGTH_OFFSET) = (u32)(Length));    \
    (*((u32 *)InstancePtr + XBD_RQSTED_LENGTH_OFFSET) = (u32)(Length));\
}

#define XBufDescriptor_GetStatus(InstancePtr)	 \
    (u32)(*((u32 *)InstancePtr + XBD_STATUS_OFFSET))

#define XBufDescriptor_SetStatus(InstancePtr, Status)	 \
    (*((u32 *)InstancePtr + XBD_STATUS_OFFSET) = (u32)Status)

#define XBufDescriptor_IsLastStatus(InstancePtr) \
    (u32)(*((u32 *)InstancePtr + XBD_STATUS_OFFSET) & \
	       XDC_STATUS_LAST_BD_MASK)

#define XBufDescriptor_GetDeviceStatus(InstancePtr) \
    ((u32)(*((u32 *)InstancePtr + XBD_DEVICE_STATUS_OFFSET)))

#define XBufDescriptor_SetDeviceStatus(InstancePtr, Status) \
    (*((u32 *)InstancePtr + XBD_DEVICE_STATUS_OFFSET) = (u32)Status)

#define XBufDescriptor_GetNextPtr(InstancePtr) \
    (XBufDescriptor *)(*((u32 *)InstancePtr + XBD_NEXT_PTR_OFFSET))

#define XBufDescriptor_SetNextPtr(InstancePtr, NextPtr) \
    (*((u32 *)InstancePtr + XBD_NEXT_PTR_OFFSET) = (u32)NextPtr)

#define XBufDescriptor_GetId(InstancePtr) \
    (u32)(*((u32 *)InstancePtr + XBD_ID_OFFSET))

#define XBufDescriptor_SetId(InstancePtr, Id) \
    (*((u32 *)InstancePtr + XBD_ID_OFFSET) = (u32)Id)

#define XBufDescriptor_GetFlags(InstancePtr) \
    (u32)(*((u32 *)InstancePtr + XBD_FLAGS_OFFSET))

#define XBufDescriptor_SetFlags(InstancePtr, Flags) \
    (*((u32 *)InstancePtr + XBD_FLAGS_OFFSET) = (u32)Flags)

#define XBufDescriptor_Lock(InstancePtr) \
    (*((u32 *)InstancePtr + XBD_FLAGS_OFFSET) |= XBD_FLAGS_LOCKED_MASK)

#define XBufDescriptor_Unlock(InstancePtr) \
    (*((u32 *)InstancePtr + XBD_FLAGS_OFFSET) &= ~XBD_FLAGS_LOCKED_MASK)

#define XBufDescriptor_IsLocked(InstancePtr) \
    (*((u32 *)InstancePtr + XBD_FLAGS_OFFSET) & XBD_FLAGS_LOCKED_MASK)

/************************** Function Prototypes ******************************/


#endif				/* end of protection macro */
