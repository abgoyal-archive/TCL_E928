


#ifndef IxTimerCtrl_H
#define IxTimerCtrl_H


#include "IxTypes.h"
/* #include "Ossl.h" */


#define IX_TIMERCTRL_NO_FREE_TIMERS 2


#define IX_TIMERCTRL_PARAM_ERROR 3

 

typedef void (*IxTimerCtrlTimerCallback)(void *userParam);


typedef enum 
{
    IxTimerCtrlAdslPurpose,
   /* Insert new purposes above this line only
    */
   IxTimerCtrlMaxPurpose
}
IxTimerCtrlPurpose;



PUBLIC IX_STATUS 
ixTimerCtrlSchedule(IxTimerCtrlTimerCallback func, 
                       void *userParam, 
                       IxTimerCtrlPurpose purpose,
	               UINT32 relativeTime,
                       unsigned *timerId );


PUBLIC IX_STATUS 
ixTimerCtrlScheduleRepeating(IxTimerCtrlTimerCallback func, 
                                void *param, 
                                IxTimerCtrlPurpose purpose,
			        UINT32 interval,
                                unsigned *timerId );

PUBLIC IX_STATUS
ixTimerCtrlCancel (unsigned id);

PUBLIC IX_STATUS
ixTimerCtrlInit(void);


PUBLIC void
ixTimerCtrlShow( void );

#endif  /* IXTIMERCTRL_H */

