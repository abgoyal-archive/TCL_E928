


#ifndef IXNPEMHMACROS_P_H
#define IXNPEMHMACROS_P_H

/* if we are running as a unit test */
#ifdef IX_UNIT_TEST
#undef NDEBUG
#endif /* #ifdef IX_UNIT_TEST */

#include "IxOsal.h"


#define IX_NPEMH_SHOW_TEXT_WIDTH (40) /**< text width for stats display */
#define IX_NPEMH_SHOW_STAT_WIDTH (10) /**< stat width for stats display */


#define IX_NPEMH_SHOW(TEXT, STAT) \
    ixOsalLog (IX_OSAL_LOG_LVL_USER, IX_OSAL_LOG_DEV_STDOUT, \
               "%-40s: %10d\n", (int) TEXT, (int) STAT, 0, 0, 0, 0)



typedef enum
{
    IX_NPEMH_TRACE_OFF     = IX_OSAL_LOG_LVL_NONE,    /**< no trace */
    IX_NPEMH_WARNING       = IX_OSAL_LOG_LVL_WARNING, /**< warning */
    IX_NPEMH_DEBUG         = IX_OSAL_LOG_LVL_MESSAGE, /**< debug */
    IX_NPEMH_FN_ENTRY_EXIT = IX_OSAL_LOG_LVL_DEBUG3   /**< function entry/exit */
} IxNpeMhTraceTypes;

#ifdef IX_UNIT_TEST
#define IX_NPEMH_TRACE_LEVEL (IX_NPEMH_FN_ENTRY_EXIT) /**< trace level */
#else
#define IX_NPEMH_TRACE_LEVEL (IX_NPEMH_TRACE_OFF) /**< trace level */
#endif


#define IX_NPEMH_TRACE0(LEVEL, STR) \
    IX_NPEMH_TRACE6(LEVEL, STR, 0, 0, 0, 0, 0, 0)


#define IX_NPEMH_TRACE1(LEVEL, STR, ARG1) \
    IX_NPEMH_TRACE6(LEVEL, STR, ARG1, 0, 0, 0, 0, 0)


#define IX_NPEMH_TRACE2(LEVEL, STR, ARG1, ARG2) \
    IX_NPEMH_TRACE6(LEVEL, STR, ARG1, ARG2, 0, 0, 0, 0)


#define IX_NPEMH_TRACE3(LEVEL, STR, ARG1, ARG2, ARG3) \
    IX_NPEMH_TRACE6(LEVEL, STR, ARG1, ARG2, ARG3, 0, 0, 0)


#define IX_NPEMH_TRACE4(LEVEL, STR, ARG1, ARG2, ARG3, ARG4) \
    IX_NPEMH_TRACE6(LEVEL, STR, ARG1, ARG2, ARG3, ARG4, 0, 0)


#define IX_NPEMH_TRACE5(LEVEL, STR, ARG1, ARG2, ARG3, ARG4, ARG5) \
    IX_NPEMH_TRACE6(LEVEL, STR, ARG1, ARG2, ARG3, ARG4, ARG5, 0)


#define IX_NPEMH_TRACE6(LEVEL, STR, ARG1, ARG2, ARG3, ARG4, ARG5, ARG6) \
{ \
    if (LEVEL <= IX_NPEMH_TRACE_LEVEL) \
    { \
        (void) ixOsalLog (LEVEL, IX_OSAL_LOG_DEV_STDOUT, (STR), \
                          (int)(ARG1), (int)(ARG2), (int)(ARG3), \
                          (int)(ARG4), (int)(ARG5), (int)(ARG6)); \
    } \
}


#define IX_NPEMH_ERROR_REPORT(STR) \
{ \
    (void) ixOsalLog (IX_OSAL_LOG_LVL_ERROR, IX_OSAL_LOG_DEV_STDERR, \
		      (STR), 0, 0, 0, 0, 0, 0); \
}

/* if we are running on XScale, i.e. real environment */
#if CPU==XSCALE


#define IX_NPEMH_REGISTER_READ(registerAddress, value) \
{ \
    *value = IX_OSAL_READ_LONG(registerAddress); \
}


#define IX_NPEMH_REGISTER_READ_BITS(registerAddress, value, mask) \
{ \
    *value = (IX_OSAL_READ_LONG(registerAddress) & mask); \
}


#define IX_NPEMH_REGISTER_WRITE(registerAddress, value) \
{ \
    IX_OSAL_WRITE_LONG(registerAddress, value); \
}


#define IX_NPEMH_REGISTER_WRITE_BITS(registerAddress, value, mask) \
{ \
    UINT32 orig = IX_OSAL_READ_LONG(registerAddress); \
    orig &= (~mask); \
    orig |= (value & mask); \
    IX_OSAL_WRITE_LONG(registerAddress, orig); \
}


/* if we are running as a unit test */
#else /* #if CPU==XSCALE */

#include "IxNpeMhTestRegister.h"


#define IX_NPEMH_REGISTER_READ(registerAddress, value) \
{ \
    ixNpeMhTestRegisterRead (registerAddress, value); \
}


#define IX_NPEMH_REGISTER_READ_BITS(registerAddress, value, mask) \
{ \
    ixNpeMhTestRegisterReadBits (registerAddress, value, mask); \
}


#define IX_NPEMH_REGISTER_WRITE(registerAddress, value) \
{ \
    ixNpeMhTestRegisterWrite (registerAddress, value); \
}


#define IX_NPEMH_REGISTER_WRITE_BITS(registerAddress, value, mask) \
{ \
    ixNpeMhTestRegisterWriteBits (registerAddress, value, mask); \
}

#endif /* #if CPU==XSCALE */

#endif /* IXNPEMHMACROS_P_H */

