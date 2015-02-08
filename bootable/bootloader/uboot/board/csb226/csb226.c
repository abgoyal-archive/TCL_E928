

#include <common.h>
#include <netdev.h>
#include <asm/arch/pxa-regs.h>

DECLARE_GLOBAL_DATA_PTR;

#ifdef CONFIG_SHOW_BOOT_PROGRESS
# define SHOW_BOOT_PROGRESS(arg)        show_boot_progress(arg)
#else
# define SHOW_BOOT_PROGRESS(arg)
#endif


int misc_init_r(void)
{
#if 0
	uchar *str;

	/* determine if the software update key is pressed during startup */
	/* not ported yet... */
	if (GPLR0 & 0x00000800) {
		printf("using bootcmd_normal (sw-update button not pressed)\n");
		str = getenv("bootcmd_normal");
	} else {
		printf("using bootcmd_update (sw-update button pressed)\n");
		str = getenv("bootcmd_update");
	}

	setenv("bootcmd",str);
#endif
	return 0;
}



int board_init (void)
{
	/* memory and cpu-speed are setup before relocation */
	/* so we do _nothing_ here */

	/* arch number of CSB226 board */
	gd->bd->bi_arch_number = MACH_TYPE_CSB226;

	/* adress of boot parameters */
	gd->bd->bi_boot_params = 0xa0000100;

	return 0;
}



int dram_init (void)
{
	gd->bd->bi_dram[0].start = PHYS_SDRAM_1;
	gd->bd->bi_dram[0].size = PHYS_SDRAM_1_SIZE;

	return 0;
}



void csb226_set_led(int led, int state)
{
	switch(led) {

		case 0: if (state==1) {
				GPCR0 |= CSB226_USER_LED0;
			} else if (state==0) {
				GPSR0 |= CSB226_USER_LED0;
			}
			break;

		case 1: if (state==1) {
				GPCR0 |= CSB226_USER_LED1;
			} else if (state==0) {
				GPSR0 |= CSB226_USER_LED1;
			}
			break;

		case 2: if (state==1) {
				GPCR0 |= CSB226_USER_LED2;
			} else if (state==0) {
				GPSR0 |= CSB226_USER_LED2;
			}
			break;
	}

	return;
}



void show_boot_progress (int status)
{
	switch(status) {
		case  1: csb226_set_led(0,1); break;
		case  5: csb226_set_led(1,1); break;
		case 15: csb226_set_led(2,1); break;
	}

	return;
}

#ifdef CONFIG_CMD_NET
int board_eth_init(bd_t *bis)
{
	int rc = 0;
#ifdef CONFIG_CS8900
	rc = cs8900_initialize(0, CONFIG_CS8900_BASE);
#endif
	return rc;
}
#endif
