

#ifndef IxOsal_H
#define IxOsal_H

/* Basic types */
#include "IxOsalTypes.h"

/* Include assert */
#include "IxOsalAssert.h"


#include "IxOsalConfig.h"

#include "IxOsalUtilitySymbols.h"

/* OS-specific header */
#include "IxOsalOs.h"






PUBLIC IX_STATUS ixOsalIrqBind (UINT32 irqLevel,
				IxOsalVoidFnVoidPtr irqHandler,
				void *parameter);

PUBLIC IX_STATUS ixOsalIrqUnbind (UINT32 irqLevel);


PUBLIC UINT32 ixOsalIrqLock (void);

PUBLIC void ixOsalIrqUnlock (UINT32 irqEnable);

PUBLIC UINT32 ixOsalIrqLevelSet (UINT32 irqLevel);

PUBLIC void ixOsalIrqEnable (UINT32 irqLevel);

PUBLIC void ixOsalIrqDisable (UINT32 irqLevel);



PUBLIC void *ixOsalMemAlloc (UINT32 size);

PUBLIC void ixOsalMemFree (void *ptr);

PUBLIC void *ixOsalMemCopy (void *dest, void *src, UINT32 count);

PUBLIC void *ixOsalMemSet (void *ptr, UINT8 filler, UINT32 count);

PUBLIC void *ixOsalCacheDmaMalloc (UINT32 size);

/* Macros for ixOsalCacheDmaMalloc*/
#define IX_OSAL_CACHE_DMA_MALLOC(size) ixOsalCacheDmaMalloc(size)

PUBLIC void ixOsalCacheDmaFree (void *ptr);

#define IX_OSAL_CACHE_DMA_FREE(ptr)		ixOsalCacheDmaFree(ptr)

#define IX_OSAL_MMU_PHYS_TO_VIRT(physAddr) \
    IX_OSAL_OS_MMU_PHYS_TO_VIRT(physAddr)


#define IX_OSAL_MMU_VIRT_TO_PHYS(virtAddr)  \
    IX_OSAL_OS_MMU_VIRT_TO_PHYS(virtAddr)



#define IX_OSAL_CACHE_FLUSH(addr, size)  IX_OSAL_OS_CACHE_FLUSH(addr, size)



#define IX_OSAL_CACHE_INVALIDATE(addr, size)  IX_OSAL_OS_CACHE_INVALIDATE(addr, size)



PUBLIC IX_STATUS ixOsalThreadCreate (IxOsalThread * thread,
				     IxOsalThreadAttr * threadAttr,
				     IxOsalVoidFnVoidPtr startRoutine,
				     void *arg);

PUBLIC IX_STATUS ixOsalThreadStart (IxOsalThread * thread);

PUBLIC IX_STATUS ixOsalThreadKill (IxOsalThread * thread);

PUBLIC void ixOsalThreadExit (void);

PUBLIC IX_STATUS ixOsalThreadPrioritySet (IxOsalThread * thread,
					  UINT32 priority);

PUBLIC IX_STATUS ixOsalThreadSuspend (IxOsalThread * thread);

PUBLIC IX_STATUS ixOsalThreadResume (IxOsalThread * thread);



PUBLIC IX_STATUS ixOsalMessageQueueCreate (IxOsalMessageQueue * queue,
					   UINT32 msgCount, UINT32 msgLen);

PUBLIC IX_STATUS ixOsalMessageQueueDelete (IxOsalMessageQueue * queue);

PUBLIC IX_STATUS ixOsalMessageQueueSend (IxOsalMessageQueue * queue,
					 UINT8 * message);

PUBLIC IX_STATUS ixOsalMessageQueueReceive (IxOsalMessageQueue * queue,
					    UINT8 * message);



PUBLIC IX_STATUS ixOsalMutexInit (IxOsalMutex * mutex);

PUBLIC IX_STATUS ixOsalMutexLock (IxOsalMutex * mutex, INT32 timeout);

PUBLIC IX_STATUS ixOsalMutexUnlock (IxOsalMutex * mutex);

PUBLIC IX_STATUS ixOsalMutexTryLock (IxOsalMutex * mutex);

PUBLIC IX_STATUS ixOsalMutexDestroy (IxOsalMutex * mutex);

PUBLIC IX_STATUS ixOsalFastMutexInit (IxOsalFastMutex * mutex);

PUBLIC IX_STATUS ixOsalFastMutexTryLock (IxOsalFastMutex * mutex);

PUBLIC IX_STATUS ixOsalFastMutexUnlock (IxOsalFastMutex * mutex);

PUBLIC IX_STATUS ixOsalFastMutexDestroy (IxOsalFastMutex * mutex);

PUBLIC IX_STATUS ixOsalSemaphoreInit (IxOsalSemaphore * semaphore,
				      UINT32 value);

PUBLIC IX_STATUS ixOsalSemaphorePost (IxOsalSemaphore * semaphore);

PUBLIC IX_STATUS ixOsalSemaphoreWait (IxOsalSemaphore * semaphore,
				      INT32 timeout);

PUBLIC IX_STATUS ixOsalSemaphoreTryWait (IxOsalSemaphore * semaphore);

PUBLIC IX_STATUS ixOsalSemaphoreGetValue (IxOsalSemaphore * semaphore,
					  UINT32 * value);

PUBLIC IX_STATUS ixOsalSemaphoreDestroy (IxOsalSemaphore * semaphore);

PUBLIC void ixOsalYield (void);



PUBLIC void ixOsalSleep (UINT32 milliseconds);

PUBLIC void ixOsalBusySleep (UINT32 microseconds);

PUBLIC UINT32 ixOsalTimestampGet (void);

PUBLIC UINT32 ixOsalTimestampResolutionGet (void);

PUBLIC UINT32 ixOsalSysClockRateGet (void);

PUBLIC void ixOsalTimeGet (IxOsalTimeval * tv);



PUBLIC UINT32 ixOsalTimevalToTicks (IxOsalTimeval tv);


#define IX_OSAL_TIMEVAL_TO_TICKS(tv)  ixOsalTimevalToTicks(tv)




PUBLIC void ixOsalTicksToTimeval (UINT32 ticks, IxOsalTimeval * pTv);


#define IX_OSAL_TICKS_TO_TIMEVAL(ticks, pTv)  \
    ixOsalTicksToTimeval(ticks, pTv)




#define IX_OSAL_TIMEVAL_TO_MS(tv)     ((tv.secs * 1000) + (tv.nsecs / 1000000))


#define IX_OSAL_MS_TO_TIMEVAL(milliseconds, pTv)  \
   	    ((IxOsalTimeval *) pTv)->secs = milliseconds / 1000;			  \
        ((IxOsalTimeval *) pTv)->nsecs = (milliseconds % 1000) * 1000000


#define IX_OSAL_TIME_EQ(tvA, tvB)        \
        ((tvA).secs == (tvB).secs && (tvA).nsecs == (tvB).nsecs)


#define IX_OSAL_TIME_LT(tvA,tvB) \
        ((tvA).secs  < (tvB).secs ||	\
        ((tvA).secs == (tvB).secs && (tvA).nsecs < (tvB).nsecs))


#define IX_OSAL_TIME_GT(tvA, tvB)  \
        ((tvA).secs  > (tvB).secs ||	\
        ((tvA).secs == (tvB).secs && (tvA).nsecs > (tvB).nsecs))


#define IX_OSAL_TIME_ADD(tvA, tvB)  \
        (tvA).secs += (tvB).secs;   \
        (tvA).nsecs += (tvB).nsecs; \
        if ((tvA).nsecs >= IX_OSAL_BILLION) \
    	{ \
        (tvA).secs++; \
        (tvA).nsecs -= IX_OSAL_BILLION; }


#define IX_OSAL_TIME_SUB(tvA, tvB)   \
        if ((tvA).nsecs >= (tvB).nsecs) \
        { \
          (tvA).secs -= (tvB).secs; \
          (tvA).nsecs -= (tvB).nsecs; \
        } \
        else \
        { \
          (tvA).secs -= ((tvB).secs + 1); \
          (tvA).nsecs += IX_OSAL_BILLION - (tvB).nsecs; \
        }



PUBLIC INT32 ixOsalLog (IxOsalLogLevel level,
			IxOsalLogDevice device,
			char *format,
			int arg1,
			int arg2, int arg3, int arg4, int arg5, int arg6);

PUBLIC UINT32 ixOsalLogLevelSet (UINT32 level);



PUBLIC IX_STATUS ixOsalRepeatingTimerSchedule (IxOsalTimer * timer,
					       UINT32 period,
					       UINT32 priority,
					       IxOsalVoidFnVoidPtr callback,
					       void *param);

PUBLIC IX_STATUS
ixOsalSingleShotTimerSchedule (IxOsalTimer * timer,
			       UINT32 period,
			       UINT32 priority,
			       IxOsalVoidFnVoidPtr callback, void *param);

PUBLIC IX_STATUS ixOsalTimerCancel (IxOsalTimer * timer);

PUBLIC void ixOsalTimersShow (void);



PUBLIC IX_STATUS ixOsalOsNameGet (INT8* osName, INT32 maxSize);

PUBLIC IX_STATUS ixOsalOsVersionGet(INT8* osVersion, INT32 maxSize);




#endif /* IxOsal_H */
