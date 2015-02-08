

#ifndef IXQMGRLOG_P_H
#define IXQMGRLOG_P_H

#include "IxOsal.h"


#define IX_QMGR_LOG0(string) do\
{\
    ixOsalLog(IX_OSAL_LOG_LVL_USER, IX_OSAL_LOG_DEV_STDOUT, string, 0, 0, 0, 0, 0, 0);\
}while(0);

#define IX_QMGR_LOG1(string, arg1) do\
{\
    ixOsalLog(IX_OSAL_LOG_LVL_USER, IX_OSAL_LOG_DEV_STDOUT, string, (int)arg1, 0, 0, 0, 0, 0);\
}while(0);

#define IX_QMGR_LOG2(string, arg1, arg2) do\
{\
    ixOsalLog(IX_OSAL_LOG_LVL_USER, IX_OSAL_LOG_DEV_STDOUT, string, (int)arg1, (int)arg2, 0, 0, 0, 0);\
}while(0);

#define IX_QMGR_LOG3(string, arg1, arg2, arg3) do\
{\
    ixOsalLog(IX_OSAL_LOG_LVL_USER, IX_OSAL_LOG_DEV_STDOUT, string, (int)arg1, (int)arg2, (int)arg3, 0, 0, 0);\
}while(0);

#define IX_QMGR_LOG6(string, arg1, arg2, arg3, arg4, arg5, arg6) do\
{\
    ixOsalLog(IX_OSAL_LOG_LVL_USER, IX_OSAL_LOG_DEV_STDOUT, string, (int)arg1, (int)arg2, (int)arg3, (int)arg4, (int)arg5, (int)arg6); \
}while(0);

#define IX_QMGR_LOG_WARNING0(string) do\
{\
    ixOsalLog(IX_OSAL_LOG_LVL_WARNING, IX_OSAL_LOG_DEV_STDOUT, string, 0, 0, 0, 0, 0, 0);\
}while(0);

#define IX_QMGR_LOG_WARNING1(string, arg1) do\
{\
    ixOsalLog(IX_OSAL_LOG_LVL_WARNING, IX_OSAL_LOG_DEV_STDOUT, string, (int)arg1, 0, 0, 0, 0, 0);\
}while(0);

#define IX_QMGR_LOG_WARNING2(string, arg1, arg2) do\
{\
    ixOsalLog(IX_OSAL_LOG_LVL_WARNING, IX_OSAL_LOG_DEV_STDOUT, string, (int)arg1, (int)arg2, 0, 0, 0, 0);\
}while(0);

#define IX_QMGR_LOG_ERROR0(string) do\
{\
    ixOsalLog(IX_OSAL_LOG_LVL_ERROR, IX_OSAL_LOG_DEV_STDERR, string, 0, 0, 0, 0, 0, 0);\
}while(0);

#define IX_QMGR_LOG_ERROR1(string, arg1) do\
{\
    ixOsalLog(IX_OSAL_LOG_LVL_ERROR, IX_OSAL_LOG_DEV_STDERR, string, (int)arg1, 0, 0, 0, 0, 0);\
}while(0);

#define IX_QMGR_LOG_ERROR2(string, arg1, arg2) do\
{\
    ixOsalLog(IX_OSAL_LOG_LVL_ERROR, IX_OSAL_LOG_DEV_STDERR, string, (int)arg1, (int)arg2, 0, 0, 0, 0);\
}while(0);

#define IX_QMGR_LOG_ERROR3(string, arg1, arg2, arg3) do\
{\
    ixOsalLog(IX_OSAL_LOG_LVL_ERROR, IX_OSAL_LOG_DEV_STDERR, string, (int)arg1, (int)arg2, (int)arg3, 0, 0, 0);\
}while(0);
#endif /* IX_QMGRLOG_P_H */




