

#include <common.h>
#include <config.h>
#include <command.h>

#include <dtt.h>
#include <i2c.h>

int do_dtt (cmd_tbl_t * cmdtp, int flag, int argc, char *argv[])
{
	int i;
	unsigned char sensors[] = CONFIG_DTT_SENSORS;
	int old_bus;

	/* switch to correct I2C bus */
	old_bus = I2C_GET_BUS();
	I2C_SET_BUS(CONFIG_SYS_DTT_BUS_NUM);

	/*
	 * Loop through sensors, read
	 * temperature, and output it.
	 */
	for (i = 0; i < sizeof (sensors); i++)
		printf ("DTT%d: %i C\n", i + 1, dtt_get_temp (sensors[i]));

	/* switch back to original I2C bus */
	I2C_SET_BUS(old_bus);

	return 0;
}	/* do_dtt() */

/***************************************************/

U_BOOT_CMD(
	  dtt,	1,	1,	do_dtt,
	  "Read temperature from Digital Thermometer and Thermostat",
	  ""
);
