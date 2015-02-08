

#include <common.h>
#include <netdev.h>

DECLARE_GLOBAL_DATA_PTR;

int board_init(void)
{
	*((volatile unsigned char *) VOICEBLUE_LED_REG) = 0xaa;

	/* arch number of VoiceBlue board */
	gd->bd->bi_arch_number = MACH_TYPE_VOICEBLUE;

	/* adress of boot parameters */
	gd->bd->bi_boot_params = 0x10000100;

	return 0;
}

int dram_init(void)
{
	*((volatile unsigned short *) VOICEBLUE_LED_REG) = 0xff;

	/* Take the Ethernet controller out of reset and wait
	 * for the EEPROM load to complete. */
	*((volatile unsigned short *) GPIO_DATA_OUTPUT_REG) |= 0x80;
	udelay(10);	/* doesn't work before timer_init call */
	*((volatile unsigned short *) GPIO_DATA_OUTPUT_REG) &= ~0x80;
	udelay(500);

	gd->bd->bi_dram[0].start = PHYS_SDRAM_1;
	gd->bd->bi_dram[0].size = PHYS_SDRAM_1_SIZE;

	return 0;
}

int misc_init_r(void)
{
	*((volatile unsigned short *) VOICEBLUE_LED_REG) = 0x55;

	return 0;
}

int board_late_init(void)
{
	*((volatile unsigned char *) VOICEBLUE_LED_REG) = 0x00;

	return 0;
}

#ifdef CONFIG_CMD_NET
int board_eth_init(bd_t *bis)
{
	int rc = 0;
#ifdef CONFIG_SMC91111
	rc = smc91111_initialize(0, CONFIG_SMC91111_BASE);
#endif
	return rc;
}
#endif
