

#include <common.h>
#include <netdev.h>
#include <asm/arch/pxa-regs.h>
#include <asm/mach-types.h>

DECLARE_GLOBAL_DATA_PTR;

#ifdef CONFIG_SHOW_BOOT_PROGRESS
# define SHOW_BOOT_PROGRESS(arg)        show_boot_progress(arg)
#else
# define SHOW_BOOT_PROGRESS(arg)
#endif

int i2c_init_board(void)
{
	int i, icr;

	/* disable I2C controller first, otherwhise it thinks we want to    */
	/* talk to the slave port...                                        */
	icr = ICR; ICR &= ~(ICR_SCLE | ICR_IUE);

	/* set gpio pin low _before_ we change direction to output          */
	GPCR(70) = GPIO_bit(70);

	/* now toggle between output=low and high-impedance                 */
	for (i = 0; i < 20; i++) {
		GPDR(70) |= GPIO_bit(70);  /* output */
		udelay(10);
		GPDR(70) &= ~GPIO_bit(70); /* input  */
		udelay(10);
	}

	ICR = icr;

	return 0;
}



int misc_init_r(void)
{
	char *str;

	/* determine if the software update key is pressed during startup   */
	if (GPLR0 & 0x00000800) {
		printf("using bootcmd_normal (sw-update button not pressed)\n");
		str = getenv("bootcmd_normal");
	} else {
		printf("using bootcmd_update (sw-update button pressed)\n");
		str = getenv("bootcmd_update");
	}

	setenv("bootcmd",str);

	return 0;
}



int board_init (void)
{
	/* memory and cpu-speed are setup before relocation */
	/* so we do _nothing_ here */

	gd->bd->bi_arch_number = MACH_TYPE_INNOKOM;
	gd->bd->bi_boot_params = 0xa0000100;
	gd->bd->bi_baudrate = CONFIG_BAUDRATE;

	return 0;
}



int dram_init (void)
{
	gd->bd->bi_dram[0].start = PHYS_SDRAM_1;
	gd->bd->bi_dram[0].size = PHYS_SDRAM_1_SIZE;

	return 0;
}



void innokom_set_led(int led, int state)
{
	switch(led) {
	}

	return;
}



void show_boot_progress (int status)
{
	switch(status) {
	}

	return;
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
