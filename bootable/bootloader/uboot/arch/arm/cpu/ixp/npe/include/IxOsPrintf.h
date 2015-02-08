

#include "IxTypes.h"

#ifndef IxOsPrintf_H

#ifndef __doxygen_hide
#define IxOsPrintf_H
#endif /* __doxygen_hide */

#ifdef __wince

#ifndef IX_USE_SERCONSOLE

static int
ixLogMsg(
    char *pFormat, 
    ...
    )
{    
#ifndef IN_KERNEL
    static WCHAR    pOutputString[256]; 
	static char     pNarrowStr[256];
    int             returnCnt = 0; 
    va_list ap;
    
    pOutputString[0] = 0; 
	pNarrowStr[0] = 0;	
    
    va_start(ap, pFormat);

	returnCnt = _vsnprintf(pNarrowStr, 256, pFormat, ap);

    MultiByteToWideChar(
            CP_ACP, 
            MB_PRECOMPOSED, 
            pNarrowStr, 
            -1, 
            pOutputString, 
            256
            ); 

    OutputDebugString(pOutputString);

    return returnCnt; 
#else
    return 0; 
#endif
}
#define printf ixLogMsg

#endif /* IX_USE_SERCONSOLE */

#endif /* __wince */


#endif /* IxOsPrintf_H */
