

#include <common.h>
#include <netdev.h>
#include <asm/arch/pxa-regs.h>

DECLARE_GLOBAL_DATA_PTR;


int board_init (void)
{
	/* memory and cpu-speed are setup before relocation */
	/* so we do _nothing_ here */

	gd->bd->bi_arch_number = MACH_TYPE_LOGODL;
	gd->bd->bi_boot_params = 0x08000100;
	gd->bd->bi_baudrate = CONFIG_BAUDRATE;

	(*((volatile short*)0x14800000)) = 0xff; /* power on eth0 */
	(*((volatile short*)0x14000000)) = 0xff; /* power on uart */

	return 0;
}



int dram_init (void)
{
	gd->bd->bi_dram[0].start = PHYS_SDRAM_1;
	gd->bd->bi_dram[0].size = PHYS_SDRAM_1_SIZE;

	return 0;
}



void logodl_set_led(int led, int state)
{
	switch(led) {

	case 0:
		if (state==1) {
			CONFIG_SYS_LED_A_CR = CONFIG_SYS_LED_A_BIT;
		} else if (state==0) {
			CONFIG_SYS_LED_A_SR = CONFIG_SYS_LED_A_BIT;
		}
		break;

	case 1:
		if (state==1) {
			CONFIG_SYS_LED_B_CR = CONFIG_SYS_LED_B_BIT;
		} else if (state==0) {
			CONFIG_SYS_LED_B_SR = CONFIG_SYS_LED_B_BIT;
		}
		break;
	}

	return;
}



void show_boot_progress (int status)
{
	if (status < -32) status = -1;  /* let things compatible */
	/*
	  switch(status) {
	  case  1: logodl_set_led(0,1); break;
	  case  5: logodl_set_led(1,1); break;
	  case 15: logodl_set_led(2,1); break;
	  }
	*/
	logodl_set_led(0, (status & 1)==1);
	logodl_set_led(1, (status & 2)==2);

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
