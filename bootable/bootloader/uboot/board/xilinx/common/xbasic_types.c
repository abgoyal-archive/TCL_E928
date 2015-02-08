
/*****************************************************************************/

/***************************** Include Files *********************************/

#include "xbasic_types.h"

/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Variable Definitions *****************************/

unsigned int XAssertStatus;

u32 XWaitInAssert = TRUE;

/* The callback function to be invoked when an assert is taken */
static XAssertCallback XAssertCallbackRoutine = (XAssertCallback) NULL;

/************************** Function Prototypes ******************************/

/*****************************************************************************/
void
XAssert(char *File, int Line)
{
	/* if the callback has been set then invoke it */
	if (XAssertCallbackRoutine != NULL) {
		(*XAssertCallbackRoutine) (File, Line);
	}

	/* if specified, wait indefinitely such that the assert will show up
	 * in testing
	 */
	while (XWaitInAssert) {
	}
}

/*****************************************************************************/
void
XAssertSetCallback(XAssertCallback Routine)
{
	XAssertCallbackRoutine = Routine;
}

/*****************************************************************************/
void
XNullHandler(void *NullParameter)
{
}
