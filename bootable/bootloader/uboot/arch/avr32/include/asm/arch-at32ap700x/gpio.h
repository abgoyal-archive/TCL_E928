
#ifndef __ASM_AVR32_ARCH_GPIO_H__
#define __ASM_AVR32_ARCH_GPIO_H__

#include <asm/arch/chip-features.h>
#include <asm/arch/memory-map.h>

#define NR_GPIO_CONTROLLERS	5

#define GPIO_PIOA_BASE	(0)
#define GPIO_PIOB_BASE	(GPIO_PIOA_BASE + 32)
#define GPIO_PIOC_BASE	(GPIO_PIOB_BASE + 32)
#define GPIO_PIOD_BASE	(GPIO_PIOC_BASE + 32)
#define GPIO_PIOE_BASE	(GPIO_PIOD_BASE + 32)
#define GPIO_PIN_PA(x)	(GPIO_PIOA_BASE + (x))
#define GPIO_PIN_PB(x)	(GPIO_PIOB_BASE + (x))
#define GPIO_PIN_PC(x)	(GPIO_PIOC_BASE + (x))
#define GPIO_PIN_PD(x)	(GPIO_PIOD_BASE + (x))
#define GPIO_PIN_PE(x)	(GPIO_PIOE_BASE + (x))

static inline void *pio_pin_to_port(unsigned int pin)
{
	switch (pin >> 5) {
	case 0:
		return (void *)PIOA_BASE;
	case 1:
		return (void *)PIOB_BASE;
	case 2:
		return (void *)PIOC_BASE;
	case 3:
		return (void *)PIOD_BASE;
	case 4:
		return (void *)PIOE_BASE;
	default:
		return NULL;
	}
}

#include <asm/arch-common/portmux-pio.h>

#endif /* __ASM_AVR32_ARCH_GPIO_H__ */
