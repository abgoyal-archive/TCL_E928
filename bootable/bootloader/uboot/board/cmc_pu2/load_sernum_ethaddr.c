

/* #define DEBUG */

#include <common.h>
#include <net.h>

#define I2C_CHIP	0x50	/* I2C bus address of onboard EEPROM */
#define I2C_ALEN	1	/* length of EEPROM addresses in bytes */
#define I2C_OFFSET	0x0	/* start address of manufacturere data block
				 * in EEPROM */

/* 64 Byte manufacturer data block in EEPROM */
struct manufacturer_data {
	unsigned int	serial_number;	/* serial number (0...999999) */
	unsigned short	hardware;	/* hardware version (e.g. V1.02) */
	unsigned short	manuf_date;	/* manufacture date (e.g. 25/02) */
	unsigned char	name[20];	/* device name (in CHIP.INI) */
	unsigned char	macadr[6];	/* MAC address */
	signed char	a_kal[4];	/* calibration value for U */
	signed char	i_kal[4];	/* calibration value for I */
	unsigned char	reserve[18];	/* reserved */
	unsigned short	save_nr;	/* save count */
	unsigned short	chksum;		/* checksum */
};


int i2c_read (unsigned char chip, unsigned int addr, int alen,
	      unsigned char *buffer, int len);


int misc_init_r(void)
{
	struct manufacturer_data data;
	char  serial [9];
	unsigned short chksum;
	unsigned char *p;
	unsigned short i;

#if !defined(CONFIG_HARD_I2C) && !defined(CONFIG_SOFT_I2C)
#error you must define some I2C support (CONFIG_HARD_I2C or CONFIG_SOFT_I2C)
#endif
	if (i2c_read(I2C_CHIP, I2C_OFFSET, I2C_ALEN, (unsigned char *)&data,
		     sizeof(data)) != 0) {
		puts ("Error reading manufacturer data from EEPROM\n");
		return -1;
	}

	/* check if manufacturer data block is valid  */
	p = (unsigned char *)&data;
	chksum = 0;
	for (i = 0; i < (sizeof(data) - sizeof(data.chksum)); i++)
		chksum += *p++;

	debug ("checksum of manufacturer data block: %#.4x\n", chksum);

	if (chksum != data.chksum) {
		puts ("Error: manufacturer data block has invalid checksum\n");
		return -1;
	}

	/* copy serial number */
	sprintf (serial, "%d", data.serial_number);

	/* set serial# and ethaddr if not yet defined */
	if (getenv("serial#") == NULL) {
		setenv ("serial#", serial);
	}

	if (getenv("ethaddr") == NULL) {
		eth_setenv_enetaddr("ethaddr", data.macadr);
	}

	return 0;
}
