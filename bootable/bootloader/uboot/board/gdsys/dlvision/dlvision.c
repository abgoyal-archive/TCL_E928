

#include <common.h>
#include <command.h>
#include <asm/processor.h>
#include <asm/io.h>
#include <asm/gpio.h>

enum {
	HWTYPE_DLVISION_CPU = 0,
	HWTYPE_DLVISION_CON = 1,
};

#define HWREV_100	6

int board_early_init_f(void)
{
	mtdcr(UIC0SR, 0xFFFFFFFF);	/* clear all ints */
	mtdcr(UIC0ER, 0x00000000);	/* disable all ints */
	mtdcr(UIC0CR, 0x00000000);	/* set all to be non-critical */
	mtdcr(UIC0PR, 0xFFFFFF80);	/* set int polarities */
	mtdcr(UIC0TR, 0x10000000);	/* set int trigger levels */
	mtdcr(UIC0VCR, 0x00000001);	/* set vect base=0,INT0 highest prio */
	mtdcr(UIC0SR, 0xFFFFFFFF);	/* clear all ints */

	/*
	 * EBC Configuration Register: set ready timeout to 512 ebc-clks
	 * -> ca. 15 us
	 */
	mtebc(EBC0_CFG, 0xa8400000);	/* ebc always driven */

	/*
	 * setup io-latches
	 */
	out_le16((void *)CONFIG_SYS_LATCH_BASE, 0x00f0);
	out_le16((void *)(CONFIG_SYS_LATCH_BASE + 0x100), 0x0002);
	out_le16((void *)(CONFIG_SYS_LATCH_BASE + 0x200), 0x0000);
	return 0;
}

int misc_init_r(void)
{
	/*
	 * set "startup-finished"-gpios
	 */
	gpio_write_bit(21, 0);
	gpio_write_bit(22, 1);

	return 0;
}

int checkboard(void)
{
	char *s = getenv("serial#");
	u8 channel2_msr = in_8((void *)CONFIG_UART_BASE + 0x26);
	u8 channel3_msr = in_8((void *)CONFIG_UART_BASE + 0x36);
	u8 channel7_msr = in_8((void *)CONFIG_UART_BASE + 0x76);
	u8 unit_type;
	u8 local_con;
	u8 audio;
	u8 hardware_version;

	printf("Board: ");

	unit_type = (channel2_msr & 0x80) ? 0x01 : 0x00;
	local_con = (channel2_msr & 0x20) ? 0x01 : 0x00;
	audio = (channel3_msr & 0x20) ? 0x01 : 0x00;
	hardware_version =
		  ((channel7_msr & 0x20) ? 0x01 : 0x00)
		| ((channel7_msr & 0x80) ? 0x02 : 0x00)
		| ((channel7_msr & 0x40) ? 0x04 : 0x00);

	switch (unit_type) {
	case HWTYPE_DLVISION_CON:
		printf("DL-Vision-CON");
		break;

	case HWTYPE_DLVISION_CPU:
		printf("DL-Vision-CPU");
		break;

	default:
		printf("UnitType %d, unsupported", unit_type);
		break;
	}

	if (s != NULL) {
		puts(", serial# ");
		puts(s);
	}
	puts("\n       ");

	switch (hardware_version) {
	case HWREV_100:
		printf("HW-Ver 1.00");
		break;

	default:
		printf("HW-Ver %d, unsupported",
		       hardware_version);
		break;
	}

	if (local_con)
		printf(", local console");

	if (audio)
		printf(", audio support");

	puts("\n");

	return 0;
}