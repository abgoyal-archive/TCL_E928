

#include <common.h>
#include <i2c.h>
#include <net.h>
#include <asm/arch/hardware.h>
#include <asm/io.h>
#include "misc.h"

DECLARE_GLOBAL_DATA_PTR;

int dram_init(void)
{
	gd->bd->bi_dram[0].start = PHYS_SDRAM_1;
	gd->bd->bi_dram[0].size = PHYS_SDRAM_1_SIZE;

	return(0);
}

#ifdef CONFIG_DRIVER_TI_EMAC

int dvevm_read_mac_address(uint8_t *buf)
{
#ifdef CONFIG_SYS_I2C_EEPROM_ADDR
	/* Read MAC address. */
	if (i2c_read(CONFIG_SYS_I2C_EEPROM_ADDR, 0x7F00, CONFIG_SYS_I2C_EEPROM_ADDR_LEN,
		     (uint8_t *) &buf[0], 6))
		goto i2cerr;

	/* Check that MAC address is valid. */
	if (!is_valid_ether_addr(buf))
		goto err;

	return 1; /* Found */

i2cerr:
	printf("Read from EEPROM @ 0x%02x failed\n", CONFIG_SYS_I2C_EEPROM_ADDR);
err:
#endif /* CONFIG_SYS_I2C_EEPROM_ADDR */

	return 0;
}

void dv_configure_mac_address(uint8_t *rom_enetaddr)
{
	int i;
	u_int8_t env_enetaddr[6];
	char *tmp = getenv("ethaddr");
	char *end;

	/* Read Ethernet MAC address from the U-Boot environment.
	 * If it is not defined, env_enetaddr[] will be cleared. */
	for (i = 0; i < 6; i++) {
		env_enetaddr[i] = tmp ? simple_strtoul(tmp, &end, 16) : 0;
		if (tmp)
			tmp = (*end) ? end+1 : end;
	}

	/* Check if EEPROM and U-Boot environment MAC addresses match. */
	if (memcmp(env_enetaddr, "\0\0\0\0\0\0", 6) != 0 &&
	    memcmp(env_enetaddr, rom_enetaddr, 6) != 0) {
		printf("Warning: MAC addresses don't match:\n");
		printf("  EEPROM MAC address: %pM\n", rom_enetaddr);
		printf("     \"ethaddr\" value: %pM\n", env_enetaddr) ;
		debug("### Using MAC address from environment\n");
	}
	if (!tmp) {
		char ethaddr[20];

		/* There is no MAC address in the environment, so we initialize
		 * it from the value in the EEPROM. */
		sprintf(ethaddr, "%pM", rom_enetaddr) ;
		debug("### Setting environment from EEPROM MAC address = \"%s\"\n",
		      ethaddr);
		setenv("ethaddr", ethaddr);
	}
}

#endif	/* DAVINCI_EMAC */

int davinci_configure_pin_mux(const struct pinmux_config *pins,
			      const int n_pins)
{
	int i;

	/* check for invalid pinmux values */
	for (i = 0; i < n_pins; i++) {
		if (pins[i].field >= PIN_MUX_NUM_FIELDS ||
		    (pins[i].value & ~PIN_MUX_FIELD_MASK) != 0)
			return -1;
	}

	/* configure the pinmuxes */
	for (i = 0; i < n_pins; i++) {
		const int offset = pins[i].field * PIN_MUX_FIELD_SIZE;
		const unsigned int value = pins[i].value << offset;
		const unsigned int mask = PIN_MUX_FIELD_MASK << offset;
		const dv_reg *mux = pins[i].mux;

		writel(value | (readl(mux) & (~mask)), mux);
	}

	return 0;
}

int davinci_configure_pin_mux_items(const struct pinmux_resource *item,
				    const int n_items)
{
	int i;

	for (i = 0; i < n_items; i++) {
		if (davinci_configure_pin_mux(item[i].pins,
					      item[i].n_pins) != 0)
			return -1;
	}

	return 0;
}
