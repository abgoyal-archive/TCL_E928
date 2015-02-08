
#ifndef _GPIO_DEFS_H_
#define _GPIO_DEFS_H_

#ifndef CONFIG_SOC_DA8XX
#define DAVINCI_GPIO_BINTEN	0x01C67008
#define DAVINCI_GPIO_BANK01	0x01C67010
#define DAVINCI_GPIO_BANK23	0x01C67038
#define DAVINCI_GPIO_BANK45	0x01C67060
#define DAVINCI_GPIO_BANK67	0x01C67088

#else /* CONFIG_SOC_DA8XX */
#define DAVINCI_GPIO_BINTEN	0x01E26008
#define DAVINCI_GPIO_BANK01	0x01E26010
#define DAVINCI_GPIO_BANK23	0x01E26038
#define DAVINCI_GPIO_BANK45	0x01E26060
#define DAVINCI_GPIO_BANK67	0x01E26088
#endif /* CONFIG_SOC_DA8XX */

struct davinci_gpio {
	unsigned int dir;
	unsigned int out_data;
	unsigned int set_data;
	unsigned int clr_data;
	unsigned int in_data;
	unsigned int set_rising;
	unsigned int clr_rising;
	unsigned int set_falling;
	unsigned int clr_falling;
	unsigned int intstat;
};

struct davinci_gpio_bank {
	int num_gpio;
	unsigned int irq_num;
	unsigned int irq_mask;
	unsigned long *in_use;
	unsigned long base;
};

#define davinci_gpio_bank01 ((struct davinci_gpio *)DAVINCI_GPIO_BANK01)
#define davinci_gpio_bank23 ((struct davinci_gpio *)DAVINCI_GPIO_BANK23)
#define davinci_gpio_bank45 ((struct davinci_gpio *)DAVINCI_GPIO_BANK45)
#define davinci_gpio_bank67 ((struct davinci_gpio *)DAVINCI_GPIO_BANK67)

#endif
