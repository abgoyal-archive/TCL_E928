

#ifndef IX_OSAL_ASSERT_H
#define IX_OSAL_ASSERT_H


#include "IxOsalOsAssert.h"

#define IX_OSAL_ASSERT(c) IX_OSAL_OS_ASSERT(c)


#ifdef IX_OSAL_ENSURE_ON
#define IX_OSAL_ENSURE(c, str) do { \
if (!(c)) ixOsalLog (IX_OSAL_LOG_LVL_MESSAGE, IX_OSAL_LOG_DEV_STDOUT, str, \
0, 0, 0, 0, 0, 0); } while (0)

#else
#define IX_OSAL_ENSURE(c, str)
#endif


#endif /* IX_OSAL_ASSERT_H */
