


#ifndef IxOsalTypes_H
#define IxOsalTypes_H

#include <config.h>
#include <common.h>

#define __ixp42X			/* sr: U-Boot needs this define */
#define IXP425_EXP_CFG_BASE	0xC4000000
#define diag_printf		debug

#undef SIMSPARCSOLARIS
#define SIMSPARCSOLARIS		0xaffe	/* sr: U-Boot gets confused with this solaris define */

#include "IxOsalOsTypes.h"

typedef UINT32 IX_STATUS;

typedef volatile UINT32 VUINT32;

typedef volatile INT32 VINT32;


#ifndef NUMELEMS
#define NUMELEMS(x) (sizeof(x) / sizeof((x)[0]))
#endif


#define IX_OSAL_BILLION (1000000000)

#ifndef TRUE
#define TRUE       1L
#endif

#if TRUE != 1
#error TRUE is not defined to 1
#endif

#ifndef FALSE
#define FALSE      0L
#endif

#if FALSE != 0
#error FALSE is not defined to 0
#endif

#ifndef NULL
#define NULL       0L
#endif

#ifndef IX_SUCCESS
#define IX_SUCCESS 0L /**< #defined as 0L */
#endif

#ifndef IX_FAIL
#define IX_FAIL    1L /**< #defined as 1L */
#endif


#ifndef PRIVATE
#ifdef IX_PRIVATE_OFF
#define PRIVATE			/* nothing */
#else
#define PRIVATE static	/**< #defined as static, except for debug builds */
#endif /* IX_PRIVATE_OFF */
#endif /* PRIVATE */


#ifndef IX_OSAL_INLINE
#define IX_OSAL_INLINE __inline
#endif /* IX_OSAL_INLINE */


#ifndef __inline__
#define __inline__	IX_OSAL_INLINE
#endif


/* Each OS can define its own PUBLIC, otherwise it will be empty. */
#ifndef PUBLIC
#define PUBLIC
#endif /* PUBLIC */


#ifndef IX_OSAL_INLINE_EXTERN
#define IX_OSAL_INLINE_EXTERN IX_OSAL_INLINE extern
#endif

typedef enum
{
    IX_OSAL_LOG_DEV_STDOUT = 0,	       /**< standard output (implemented by default) */
    IX_OSAL_LOG_DEV_STDERR = 1,	       /**< standard error (implemented */
    IX_OSAL_LOG_DEV_HEX_DISPLAY = 2,   /**< hexadecimal display (not implemented) */
    IX_OSAL_LOG_DEV_ASCII_DISPLAY = 3  /**< ASCII-capable display (not implemented) */
} IxOsalLogDevice;


#define IX_OSAL_LOG_ERROR (-1)

typedef enum
{
    IX_OSAL_LOG_LVL_NONE = 0,	 /**<No trace level */
    IX_OSAL_LOG_LVL_USER = 1,	 /**<Set trace level to user */
    IX_OSAL_LOG_LVL_FATAL = 2,	 /**<Set trace level to fatal */
    IX_OSAL_LOG_LVL_ERROR = 3,	 /**<Set trace level to error */
    IX_OSAL_LOG_LVL_WARNING = 4, /**<Set trace level to warning */
    IX_OSAL_LOG_LVL_MESSAGE = 5, /**<Set trace level to message */
    IX_OSAL_LOG_LVL_DEBUG1 = 6,	 /**<Set trace level to debug1 */
    IX_OSAL_LOG_LVL_DEBUG2 = 7,	 /**<Set trace level to debug2 */
    IX_OSAL_LOG_LVL_DEBUG3 = 8,	 /**<Set trace level to debug3 */
    IX_OSAL_LOG_LVL_ALL	/**<Set trace level to all */
} IxOsalLogLevel;


typedef void (*IxOsalVoidFnVoidPtr) (void *);

typedef void (*IxOsalVoidFnPtr) (void);


typedef struct
{
    UINT32 secs;		/**< seconds */
    UINT32 nsecs;		/**< nanoseconds */
} IxOsalTimeval;


typedef UINT32 IxOsalTimer;


#define IX_OSAL_WAIT_FOREVER IX_OSAL_OS_WAIT_FOREVER

#define IX_OSAL_WAIT_NONE    IX_OSAL_OS_WAIT_NONE


typedef IxOsalOsMutex IxOsalMutex;

typedef IxOsalOsFastMutex IxOsalFastMutex;

typedef IxOsalOsThread IxOsalThread;

typedef IxOsalOsSemaphore IxOsalSemaphore;

typedef IxOsalOsMessageQueue IxOsalMessageQueue;


typedef struct
{
    char *name;        /**< name */
    UINT32 stackSize;  /**< stack size */
    UINT32 priority;   /**< priority */
} IxOsalThreadAttr;

#define IX_OSAL_THREAD_DEFAULT_STACK_SIZE (IX_OSAL_OS_THREAD_DEFAULT_STACK_SIZE)

#define IX_OSAL_THREAD_MAX_STACK_SIZE (IX_OSAL_OS_THREAD_MAX_STACK_SIZE)

#define IX_OSAL_DEFAULT_THREAD_PRIORITY (IX_OSAL_OS_DEFAULT_THREAD_PRIORITY)

#define IX_OSAL_MAX_THREAD_PRIORITY (IX_OSAL_OS_MAX_THREAD_PRIORITY)



#endif /* IxOsalTypes_H */
