

#include <common.h>
#include <netdev.h>
#include <clps7111.h>

DECLARE_GLOBAL_DATA_PTR;

/* ------------------------------------------------------------------------- */



int board_init (void)
{
	/* Activate LED flasher */
	IO_LEDFLSH = 0x40;

	/* arch number of EP7111 */
	gd->bd->bi_arch_number = MACH_TYPE_EDB7211;

	/* location of boot parameters for EP7111 */
	gd->bd->bi_boot_params = 0xc0020100;

	return 0;
}

int dram_init (void)
{
	gd->bd->bi_dram[0].start = PHYS_SDRAM_1;
	gd->bd->bi_dram[0].size = PHYS_SDRAM_1_SIZE;
	gd->bd->bi_dram[1].start = PHYS_SDRAM_2;
	gd->bd->bi_dram[1].size = PHYS_SDRAM_2_SIZE;

	return (0);
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
