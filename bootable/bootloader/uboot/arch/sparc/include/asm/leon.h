

#ifndef __ASM_LEON_H__
#define __ASM_LEON_H__

#if defined(CONFIG_LEON3)

#include <asm/leon3.h>

#elif defined(CONFIG_LEON2)

#include <asm/leon2.h>

#else

#error Unknown LEON processor

#endif

/* Common stuff */

#endif
