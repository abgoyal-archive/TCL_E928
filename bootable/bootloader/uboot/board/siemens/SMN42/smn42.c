

#include <common.h>
#include <clps7111.h>

DECLARE_GLOBAL_DATA_PTR;


int board_init (void)
{
	/* arch number MACH_TYPE_ARMADILLO - not official*/
	gd->bd->bi_arch_number = 83;

	/* location of boot parameters */
	gd->bd->bi_boot_params = PHYS_SDRAM_1 + 0x00000100;

	return 0;
}

int dram_init (void)
{
	gd->bd->bi_dram[0].start = PHYS_SDRAM_1;
	gd->bd->bi_dram[0].size = PHYS_SDRAM_1_SIZE;

	return (0);
}
