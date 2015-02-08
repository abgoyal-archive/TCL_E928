

#ifndef __ASM_ARCH_MX31_H
#define __ASM_ARCH_MX31_H

extern u32 mx31_get_ipg_clk(void);
#define imx_get_uartclk mx31_get_ipg_clk
extern void mx31_gpio_mux(unsigned long mode);

enum mx31_gpio_direction {
	MX31_GPIO_DIRECTION_IN,
	MX31_GPIO_DIRECTION_OUT,
};

#ifdef CONFIG_MX31_GPIO
extern int mx31_gpio_direction(unsigned int gpio,
			       enum mx31_gpio_direction direction);
extern void mx31_gpio_set(unsigned int gpio, unsigned int value);
extern int mx31_gpio_get(unsigned int gpio);
#else
static inline int mx31_gpio_direction(unsigned int gpio,
				      enum mx31_gpio_direction direction)
{
	return 1;
}
static inline int mx31_gpio_get(unsigned int gpio)
{
	return 1;
}
static inline void mx31_gpio_set(unsigned int gpio, unsigned int value)
{
}
#endif

void mx31_uart1_hw_init(void);
void mx31_spi2_hw_init(void);

#endif /* __ASM_ARCH_MX31_H */
