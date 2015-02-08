

#include <common.h>
#include <asm/arch/at91_pmc.h>
#include <asm/arch/at91_pio.h>
#include <asm/arch/gpio.h>
#include <asm/arch/io.h>

#ifdef CONFIG_RED_LED
void red_LED_on(void)
{
	at91_set_gpio_value(CONFIG_RED_LED, 1);
}

void red_LED_off(void)
{
	at91_set_gpio_value(CONFIG_RED_LED, 0);
}
#endif

#ifdef CONFIG_GREEN_LED
void green_LED_on(void)
{
	at91_set_gpio_value(CONFIG_GREEN_LED, 0);
}

void green_LED_off(void)
{
	at91_set_gpio_value(CONFIG_GREEN_LED, 1);
}
#endif

#ifdef CONFIG_YELLOW_LED
void yellow_LED_on(void)
{
	at91_set_gpio_value(CONFIG_YELLOW_LED, 0);
}

void yellow_LED_off(void)
{
	at91_set_gpio_value(CONFIG_YELLOW_LED, 1);
}
#endif
