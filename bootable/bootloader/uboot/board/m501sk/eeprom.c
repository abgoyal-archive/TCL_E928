

#include <common.h>
#include <i2c.h>
#ifdef CONFIG_SYS_EEPROM_AT24C16
#undef DEBUG

void eeprom_init(void)
{
#if defined(CONFIG_HARD_I2C) || defined(CONFIG_SOFT_I2C)
	i2c_init(CONFIG_SYS_I2C_SPEED, CONFIG_SYS_I2C_SLAVE);
#endif
}

int eeprom_read(unsigned dev_addr, unsigned offset, uchar *buffer,
			unsigned cnt)
{
	int page, count = 0, i = 0;
	page = offset / 0x100;
	i = offset % 0x100;

	while (count < cnt) {
		if (i2c_read(dev_addr|page, i++, 1, buffer+count++, 1) != 0)
			return 1;
		if (i > 0xff) {
			page++;
			i = 0;
		}
	}

	return 0;
}

int eeprom_write(unsigned dev_addr, unsigned offset, uchar *buffer,
			unsigned cnt)
{
	int page, i = 0, count = 0;

	page = offset / 0x100;
	i = offset % 0x100;

	while (count < cnt) {
		if (i2c_write(dev_addr|page, i++, 1, buffer+count++, 1) != 0)
			return 1;
		if (i > 0xff) {
			page++;
			i = 0;
		}
	}

#if defined(CONFIG_SYS_EEPROM_PAGE_WRITE_DELAY_MS)
	udelay(CONFIG_SYS_EEPROM_PAGE_WRITE_DELAY_MS * 1000);
#endif

	return 0;
}

#ifndef CONFIG_SPI
int eeprom_probe(unsigned dev_addr, unsigned offset)
{
	unsigned char chip;

	/* Probe the chip address */
#if CONFIG_SYS_I2C_EEPROM_ADDR_LEN == 1 && !defined(CONFIG_SPI_X)
	chip = offset >> 8; /* block number */
#else
	chip = offset >> 16; /* block number */
#endif /* CONFIG_SYS_I2C_EEPROM_ADDR_LEN, CONFIG_SPI_X */

	chip |= dev_addr; /* insert device address */
	return (i2c_probe(chip));
}
#endif
#endif
