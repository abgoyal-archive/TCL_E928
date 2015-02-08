

#ifndef __OS_SUPPORT_H_
#define __OS_SUPPORT_H_

#include "compiler.h"

#ifdef __MINGW32__
#include "mingw_support.h"
#endif

#ifdef __APPLE__
#include "getline.h"
#endif

#endif /* __OS_SUPPORT_H_ */
