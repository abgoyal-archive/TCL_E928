
#ifndef __ASM_ARCH_HARDWARE_H
#define __ASM_ARCH_HARDWARE_H


#if defined(CONFIG_LPC2292)
#include <asm/arch-lpc2292/lpc2292_registers.h>
#else
#error No hardware file defined for this configuration
#endif

#endif /* __ASM_ARCH_HARDWARE_H */
