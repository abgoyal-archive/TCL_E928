


#ifndef IXNPEDLMACROS_P_H
#define IXNPEDLMACROS_P_H


#if (CPU != XSCALE)
/* To support IxNpeDl unit tests... */
#include <stdio.h>
#include "test/IxNpeDlTestReg.h"

#else   
#include "IxOsal.h"

#endif



typedef enum
{
    IX_NPEDL_TRACE_OFF,     /**< no trace */
    IX_NPEDL_DEBUG,         /**< debug */
    IX_NPEDL_FN_ENTRY_EXIT  /**< function entry/exit */
} IxNpeDlTraceTypes;



/* Implementation of the following macros for use with IxNpeDl unit test code */
#if (CPU != XSCALE)


#define IX_NPEDL_TRACE_LEVEL IX_NPEDL_FN_ENTRY_EXIT

#define IX_NPEDL_ERROR_REPORT(STR) printf ("IxNpeDl ERROR: %s\n", (STR));

#define IX_NPEDL_WARNING_REPORT(STR) printf ("IxNpeDl WARNING: %s\n", (STR));

#define IX_NPEDL_TRACE0(LEVEL, STR) \
{ \
    if (LEVEL <= IX_NPEDL_TRACE_LEVEL) \
    { \
        printf ("IxNpeDl TRACE: "); \
        printf ((STR)); \
        printf ("\n"); \
    } \
}

 /**
 * @def IX_NPEDL_TRACE1
 *
 * @brief Mechanism for tracing debug for the IxNpeDl component, with 1 argument
 *
 * @param unsigned [in] LEVEL - one of IxNpeDlTraceTypes enumerated values
 * @param char* [in] STR - Trace string
 * @param argType [in] ARG1 - Argument to trace
 *
 * This macro simply prints the trace string passed, if the level is supported.
 * Intended for use with IxNpeDl unit test code.
 *
 * @return none
 */
#define IX_NPEDL_TRACE1(LEVEL, STR, ARG1) \
{ \
    if (LEVEL <= IX_NPEDL_TRACE_LEVEL) \
    { \
        printf ("IxNpeDl TRACE: "); \
        printf (STR, ARG1); \
        printf ("\n"); \
    } \
}

#define IX_NPEDL_TRACE2(LEVEL, STR, ARG1, ARG2) \
{ \
    if (LEVEL <= IX_NPEDL_TRACE_LEVEL) \
    { \
        printf ("IxNpeDl TRACE: "); \
        printf (STR, ARG1, ARG2); \
        printf ("\n"); \
    } \
}


#define IX_NPEDL_REG_WRITE(base, offset, value) \
{ \
    ixNpeDlTestRegWrite (base, offset, value); \
}


#define IX_NPEDL_REG_READ(base, offset, value) \
{ \
    ixNpeDlTestRegRead (base, offset, value); \
}


/* Implementation of the following macros when integrated with IxOsal */
#else  /* #if (CPU != XSCALE) */


#define IX_NPEDL_TRACE_LEVEL IX_NPEDL_DEBUG


#define IX_NPEDL_ERROR_REPORT(STR) \
    ixOsalLog (IX_OSAL_LOG_LVL_ERROR, IX_OSAL_LOG_DEV_STDERR, STR, 0, 0, 0, 0, 0, 0);

#define IX_NPEDL_WARNING_REPORT(STR) \
    ixOsalLog (IX_OSAL_LOG_LVL_WARNING, IX_OSAL_LOG_DEV_STDOUT, STR, 0, 0, 0, 0, 0, 0);


#define IX_NPEDL_TRACE0(LEVEL, STR) \
{ \
    if (LEVEL <= IX_NPEDL_TRACE_LEVEL) \
    { \
        if (LEVEL == IX_NPEDL_FN_ENTRY_EXIT) \
        { \
            ixOsalLog (IX_OSAL_LOG_LVL_DEBUG3, IX_OSAL_LOG_DEV_STDOUT, STR, 0, 0, 0, 0, 0, 0); \
        } \
        else if (LEVEL == IX_NPEDL_DEBUG) \
        { \
            ixOsalLog (IX_OSAL_LOG_LVL_MESSAGE, IX_OSAL_LOG_DEV_STDOUT, STR, 0, 0, 0, 0, 0, 0); \
        } \
    } \
}

#define IX_NPEDL_TRACE1(LEVEL, STR, ARG1) \
{ \
    if (LEVEL <= IX_NPEDL_TRACE_LEVEL) \
    { \
        if (LEVEL == IX_NPEDL_FN_ENTRY_EXIT) \
        { \
            ixOsalLog (IX_OSAL_LOG_LVL_DEBUG3, IX_OSAL_LOG_DEV_STDOUT, STR, ARG1, 0, 0, 0, 0, 0); \
        } \
        else if (LEVEL == IX_NPEDL_DEBUG) \
        { \
            ixOsalLog (IX_OSAL_LOG_LVL_MESSAGE, IX_OSAL_LOG_DEV_STDOUT, STR, ARG1, 0, 0, 0, 0, 0); \
        } \
    } \
}

#define IX_NPEDL_TRACE2(LEVEL, STR, ARG1, ARG2) \
{ \
    if (LEVEL <= IX_NPEDL_TRACE_LEVEL) \
    { \
        if (LEVEL == IX_NPEDL_FN_ENTRY_EXIT) \
        { \
            ixOsalLog (IX_OSAL_LOG_LVL_DEBUG3, IX_OSAL_LOG_DEV_STDOUT, STR, ARG1, ARG2, 0, 0, 0, 0); \
        } \
        else if (LEVEL == IX_NPEDL_DEBUG) \
        { \
            ixOsalLog (IX_OSAL_LOG_LVL_MESSAGE, IX_OSAL_LOG_DEV_STDOUT, STR, ARG1, ARG2, 0, 0, 0, 0); \
        } \
    } \
}

#define IX_NPEDL_REG_WRITE(base, offset, value) \
    IX_OSAL_WRITE_LONG(((base) + (offset)), (value))



#define IX_NPEDL_REG_READ(base, offset, value) \
    *(value) = IX_OSAL_READ_LONG(((base) + (offset)))

#endif  /* #if (CPU != XSCALE) */

#endif /* IXNPEDLMACROS_P_H */

