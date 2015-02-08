

#include <twl4030.h>

void twl4030_led_init(unsigned char ledon_mask)
{
	/* LEDs need to have corresponding PWMs enabled */
	if (ledon_mask & TWL4030_LED_LEDEN_LEDAON)
		ledon_mask |= TWL4030_LED_LEDEN_LEDAPWM;
	if (ledon_mask & TWL4030_LED_LEDEN_LEDBON)
		ledon_mask |= TWL4030_LED_LEDEN_LEDBPWM;

	twl4030_i2c_write_u8(TWL4030_CHIP_LED, ledon_mask,
			     TWL4030_LED_LEDEN);

}
