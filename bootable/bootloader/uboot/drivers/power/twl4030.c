

#include <twl4030.h>

void twl4030_power_reset_init(void)
{
	u8 val = 0;
	if (twl4030_i2c_read_u8(TWL4030_CHIP_PM_MASTER, &val,
				TWL4030_PM_MASTER_P1_SW_EVENTS)) {
		printf("Error:TWL4030: failed to read the power register\n");
		printf("Could not initialize hardware reset\n");
	} else {
		val |= TWL4030_PM_MASTER_SW_EVENTS_STOPON_PWRON;
		if (twl4030_i2c_write_u8(TWL4030_CHIP_PM_MASTER, val,
					 TWL4030_PM_MASTER_P1_SW_EVENTS)) {
			printf("Error:TWL4030: failed to write the power register\n");
			printf("Could not initialize hardware reset\n");
		}
	}
}


#define DEV_GRP_P1		0x20
#define VAUX3_VSEL_28		0x03
#define DEV_GRP_ALL		0xE0
#define VPLL2_VSEL_18		0x05
#define VDAC_VSEL_18		0x03

void twl4030_power_init(void)
{
	unsigned char byte;

	/* set VAUX3 to 2.8V */
	byte = DEV_GRP_P1;
	twl4030_i2c_write_u8(TWL4030_CHIP_PM_RECEIVER, byte,
			     TWL4030_PM_RECEIVER_VAUX3_DEV_GRP);
	byte = VAUX3_VSEL_28;
	twl4030_i2c_write_u8(TWL4030_CHIP_PM_RECEIVER, byte,
			     TWL4030_PM_RECEIVER_VAUX3_DEDICATED);

	/* set VPLL2 to 1.8V */
	byte = DEV_GRP_ALL;
	twl4030_i2c_write_u8(TWL4030_CHIP_PM_RECEIVER, byte,
			     TWL4030_PM_RECEIVER_VPLL2_DEV_GRP);
	byte = VPLL2_VSEL_18;
	twl4030_i2c_write_u8(TWL4030_CHIP_PM_RECEIVER, byte,
			     TWL4030_PM_RECEIVER_VPLL2_DEDICATED);

	/* set VDAC to 1.8V */
	byte = DEV_GRP_P1;
	twl4030_i2c_write_u8(TWL4030_CHIP_PM_RECEIVER, byte,
			     TWL4030_PM_RECEIVER_VDAC_DEV_GRP);
	byte = VDAC_VSEL_18;
	twl4030_i2c_write_u8(TWL4030_CHIP_PM_RECEIVER, byte,
			     TWL4030_PM_RECEIVER_VDAC_DEDICATED);
}

#define VMMC1_VSEL_30		0x02

void twl4030_power_mmc_init(void)
{
	unsigned char byte;

	byte = DEV_GRP_P1;
	twl4030_i2c_write_u8(TWL4030_CHIP_PM_RECEIVER, byte,
			     TWL4030_PM_RECEIVER_VMMC1_DEV_GRP);

	/* 3 Volts */
	byte = VMMC1_VSEL_30;
	twl4030_i2c_write_u8(TWL4030_CHIP_PM_RECEIVER, byte,
			     TWL4030_PM_RECEIVER_VMMC1_DEDICATED);
}
