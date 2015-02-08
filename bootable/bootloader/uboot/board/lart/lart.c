

#include <common.h>
#include <netdev.h>

DECLARE_GLOBAL_DATA_PTR;

/* ------------------------------------------------------------------------- */



int board_init (void)
{
	/* memory and cpu-speed are setup before relocation */
	/* so we do _nothing_ here */

	/* arch number of LART-Board */
	gd->bd->bi_arch_number = MACH_TYPE_LART;

	/* adress of boot parameters */
	gd->bd->bi_boot_params = 0xc0000100;

	return 0;
}

int dram_init (void)
{
	bd_t *bd = gd->bd;

	bd->bi_dram[0].start = PHYS_SDRAM_1;
	bd->bi_dram[0].size = PHYS_SDRAM_1_SIZE;
	bd->bi_dram[1].start = PHYS_SDRAM_2;
	bd->bi_dram[1].size = PHYS_SDRAM_2_SIZE;
	bd->bi_dram[2].start = PHYS_SDRAM_3;
	bd->bi_dram[2].size = PHYS_SDRAM_3_SIZE;
	bd->bi_dram[3].start = PHYS_SDRAM_4;
	bd->bi_dram[3].size = PHYS_SDRAM_4_SIZE;

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
