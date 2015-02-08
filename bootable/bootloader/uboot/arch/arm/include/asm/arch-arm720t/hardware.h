
#ifndef __ARM7_HW_H
#define __ARM7_HW_H


#if defined(CONFIG_NETARM)
#include <asm/arch-arm720t/netarm_registers.h>
#elif defined(CONFIG_IMPA7)
/* include IMPA7 specific hardware file if there was one */
#elif defined(CONFIG_EP7312)
/* include EP7312 specific hardware file if there was one */
#elif defined(CONFIG_ARMADILLO)
/* include armadillo specific hardware file if there was one */
#elif defined(CONFIG_INTEGRATOR) && defined(CONFIG_ARCH_INTEGRATOR)
/* include IntegratorCP/CM720T specific hardware file if there was one */
#else
#error No hardware file defined for this configuration
#endif

#endif /* __ARM7_HW_H */
