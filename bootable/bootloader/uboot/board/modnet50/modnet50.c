

#include <common.h>

DECLARE_GLOBAL_DATA_PTR;


int board_init (void)
{
	/* address for the kernel command line */
	gd->bd->bi_boot_params = 0x800;
	return 0;
}

int dram_init (void)
{
	gd->bd->bi_dram[0].start = PHYS_SDRAM_1;
	gd->bd->bi_dram[0].size = PHYS_SDRAM_1_SIZE;
	if (CONFIG_NR_DRAM_BANKS == 2) {
		gd->bd->bi_dram[1].start = PHYS_SDRAM_2;
		gd->bd->bi_dram[1].size = PHYS_SDRAM_2_SIZE;
	}
	return (0);
}
