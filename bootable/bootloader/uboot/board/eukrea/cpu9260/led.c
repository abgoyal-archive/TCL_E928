

#include <common.h>
#include <status_led.h>
#include <asm/arch/at91sam9260.h>
#include <asm/arch/at91_pmc.h>
#include <asm/arch/gpio.h>
#include <asm/arch/io.h>

static unsigned int saved_state[4] = {STATUS_LED_OFF, STATUS_LED_OFF,
		STATUS_LED_OFF, STATUS_LED_OFF};

void coloured_LED_init(void)
{
	/* Enable clock */
	at91_sys_write(AT91_PMC_PCER, 1 << AT91SAM9260_ID_PIOC);

	at91_set_gpio_output(CONFIG_RED_LED, 1);
	at91_set_gpio_output(CONFIG_GREEN_LED, 1);
	at91_set_gpio_output(CONFIG_YELLOW_LED, 1);
	at91_set_gpio_output(CONFIG_BLUE_LED, 1);

	at91_set_gpio_value(CONFIG_RED_LED, 1);
	at91_set_gpio_value(CONFIG_GREEN_LED, 1);
	at91_set_gpio_value(CONFIG_YELLOW_LED, 1);
	at91_set_gpio_value(CONFIG_BLUE_LED, 1);
}

void red_LED_off(void)
{
	at91_set_gpio_value(CONFIG_RED_LED, 1);
	saved_state[STATUS_LED_RED] = STATUS_LED_OFF;
}

void green_LED_off(void)
{
	at91_set_gpio_value(CONFIG_GREEN_LED, 1);
	saved_state[STATUS_LED_GREEN] = STATUS_LED_OFF;
}

void yellow_LED_off(void)
{
	at91_set_gpio_value(CONFIG_YELLOW_LED, 1);
	saved_state[STATUS_LED_YELLOW] = STATUS_LED_OFF;
}

void blue_LED_off(void)
{
	at91_set_gpio_value(CONFIG_BLUE_LED, 1);
	saved_state[STATUS_LED_BLUE] = STATUS_LED_OFF;
}

void red_LED_on(void)
{
	at91_set_gpio_value(CONFIG_RED_LED, 0);
	saved_state[STATUS_LED_RED] = STATUS_LED_ON;
}

void green_LED_on(void)
{
	at91_set_gpio_value(CONFIG_GREEN_LED, 0);
	saved_state[STATUS_LED_GREEN] = STATUS_LED_ON;
}

void yellow_LED_on(void)
{
	at91_set_gpio_value(CONFIG_YELLOW_LED, 0);
	saved_state[STATUS_LED_YELLOW] = STATUS_LED_ON;
}

void blue_LED_on(void)
{
	at91_set_gpio_value(CONFIG_BLUE_LED, 0);
	saved_state[STATUS_LED_BLUE] = STATUS_LED_ON;
}

void __led_init(led_id_t mask, int state)
{
	__led_set(mask, state);
}

void __led_toggle(led_id_t mask)
{
	if (STATUS_LED_BLUE == mask) {
		if (STATUS_LED_ON == saved_state[STATUS_LED_BLUE])
			blue_LED_off();
		else
			blue_LED_on();
	} else if (STATUS_LED_RED == mask) {
		if (STATUS_LED_ON == saved_state[STATUS_LED_RED])
			red_LED_off();
		else
			red_LED_on();
	} else if (STATUS_LED_GREEN == mask) {
		if (STATUS_LED_ON == saved_state[STATUS_LED_GREEN])
			green_LED_off();
		else
			green_LED_on();
	} else if (STATUS_LED_YELLOW == mask) {
		if (STATUS_LED_ON == saved_state[STATUS_LED_YELLOW])
			yellow_LED_off();
		else
			yellow_LED_on();
	}
}

void __led_set(led_id_t mask, int state)
{
	if (STATUS_LED_BLUE == mask) {
		if (STATUS_LED_ON == state)
			blue_LED_on();
		else
			blue_LED_off();
	} else if (STATUS_LED_RED == mask) {
		if (STATUS_LED_ON == state)
			red_LED_on();
		else
			red_LED_off();
	} else if (STATUS_LED_GREEN == mask) {
		if (STATUS_LED_ON == state)
			green_LED_on();
		else
			green_LED_off();
	} else if (STATUS_LED_YELLOW == mask) {
		if (STATUS_LED_ON == state)
			yellow_LED_on();
		else
			yellow_LED_off();
	}
}