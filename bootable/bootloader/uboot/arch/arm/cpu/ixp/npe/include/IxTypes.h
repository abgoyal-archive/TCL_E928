


#ifndef IxTypes_H

#ifndef __doxygen_HIDE

#define IxTypes_H

#endif /* __doxygen_HIDE */


/* WR51880: Undefined data types workaround for backward compatibility */
#ifdef __linux
#ifndef __INCvxTypesOldh
typedef int (*FUNCPTR)(void);
typedef int STATUS;
#define OK (0)
#define ERROR (-1)
#endif
#endif

#include "IxOsalBackward.h"

#endif /* IxTypes_H */

