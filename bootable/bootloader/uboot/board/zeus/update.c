

#include <config.h>
#include <common.h>
#include <command.h>
#include <asm/processor.h>
#include <asm/io.h>
#include <asm/gpio.h>
#include <i2c.h>

#if defined(CONFIG_ZEUS)

u8 buf_zeus_ce[] = {
/*00    01    02    03    04    05    06    07 */
  0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/*08    09    0a    0b    0c    0d    0e    0f */
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/*10    11    12    13    14    15    16    17 */
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/*18    19    1a    1b    1c    1d    1e    1f */
  0x00, 0xc0, 0x50, 0x12, 0x72, 0x3e, 0x00, 0x00 };

u8 buf_zeus_pe[] = {

/*00    01    02    03    04    05    06    07 */
  0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/*08    09    0a    0b    0c    0d    0e    0f */
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/*10    11    12    13    14    15    16    17 */
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/*18    19    1a    1b    1c    1d    1e    1f */
  0x00, 0x60, 0x68, 0x2d, 0x42, 0xbe, 0x00, 0x00 };

static int update_boot_eeprom(void)
{
	u32 len = 0x20;
	u8 chip = CONFIG_SYS_I2C_EEPROM_ADDR;
	u8 *pbuf;
	u8 base;
	int i;

	if (in_be32((void *)GPIO0_IR) & GPIO_VAL(CONFIG_SYS_GPIO_ZEUS_PE)) {
		pbuf = buf_zeus_pe;
		base = 0x40;
	} else {
		pbuf = buf_zeus_ce;
		base = 0x00;
	}

	for (i = 0; i < len; i++, base++) {
		if (i2c_write(chip, base, 1, &pbuf[i], 1) != 0) {
			printf("i2c_write fail\n");
			return 1;
		}
		udelay(11000);
	}

	return 0;
}

int do_update_boot_eeprom(cmd_tbl_t* cmdtp, int flag, int argc, char* argv[])
{
	return update_boot_eeprom();
}

U_BOOT_CMD (
	update_boot_eeprom, 1, 1, do_update_boot_eeprom,
	"update boot eeprom content",
	""
);

#endif