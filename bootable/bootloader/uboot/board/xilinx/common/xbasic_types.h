
/*****************************************************************************/

#ifndef XBASIC_TYPES_H		/* prevent circular inclusions */
#define XBASIC_TYPES_H		/* by using protection macros */

/***************************** Include Files *********************************/

/************************** Constant Definitions *****************************/

#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

#ifndef NULL
#define NULL 0
#endif
/** Null */

#define XCOMPONENT_IS_READY	0x11111111	/* component has been initialized */
#define XCOMPONENT_IS_STARTED	0x22222222	/* component has been started */

#define XTEST_PASSED	0
#define XTEST_FAILED	1

#define XASSERT_NONE	 0
#define XASSERT_OCCURRED 1

extern unsigned int XAssertStatus;
extern void XAssert(char *, int);

/**************************** Type Definitions *******************************/

#include <linux/types.h>

typedef struct {
	u32 Upper;
	u32 Lower;
} Xuint64;

/*@}*/

typedef void (*XInterruptHandler) (void *InstancePtr);

typedef void (*XAssertCallback) (char *FilenamePtr, int LineNumber);

/***************** Macros (Inline Functions) Definitions *********************/

/*****************************************************************************/
#define XUINT64_MSW(x) ((x).Upper)

/*****************************************************************************/
#define XUINT64_LSW(x) ((x).Lower)

#ifndef NDEBUG

/*****************************************************************************/
#define XASSERT_VOID(expression)			\
{							\
	if (expression) {				\
		XAssertStatus = XASSERT_NONE;		\
	} else {					\
		XAssert(__FILE__, __LINE__);		\
		XAssertStatus = XASSERT_OCCURRED;	\
		return;					\
	}						\
}

/*****************************************************************************/
#define XASSERT_NONVOID(expression)		   \
{						   \
	if (expression) {			   \
		XAssertStatus = XASSERT_NONE;	   \
	} else {				   \
		XAssert(__FILE__, __LINE__);	   \
		XAssertStatus = XASSERT_OCCURRED;  \
		return 0;			   \
	}					   \
}

/*****************************************************************************/
#define XASSERT_VOID_ALWAYS()			   \
{						   \
	XAssert(__FILE__, __LINE__);		   \
	XAssertStatus = XASSERT_OCCURRED;	   \
	return;					   \
}

/*****************************************************************************/
#define XASSERT_NONVOID_ALWAYS()		   \
{						   \
	XAssert(__FILE__, __LINE__);		   \
	XAssertStatus = XASSERT_OCCURRED;	   \
	return 0;				   \
}

#else

#define XASSERT_VOID(expression)
#define XASSERT_VOID_ALWAYS()
#define XASSERT_NONVOID(expression)
#define XASSERT_NONVOID_ALWAYS()
#endif

/************************** Function Prototypes ******************************/

void XAssertSetCallback(XAssertCallback Routine);
void XNullHandler(void *NullParameter);

#endif	/* end of protection macro */
