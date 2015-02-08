

#include <common.h>
#include <netdev.h>

DECLARE_GLOBAL_DATA_PTR;

#ifdef CONFIG_SHOW_BOOT_PROGRESS
# define SHOW_BOOT_PROGRESS(arg)        show_boot_progress(arg)
#else
# define SHOW_BOOT_PROGRESS(arg)
#endif

int board_init (void)
{
	gd->bd->bi_arch_number = MACH_TYPE_SCB9328;
	gd->bd->bi_boot_params = 0x08000100;

	return 0;
}

int dram_init (void)
{
#if ( CONFIG_NR_DRAM_BANKS > 0 )
	gd->bd->bi_dram[0].start = SCB9328_SDRAM_1;
	gd->bd->bi_dram[0].size = SCB9328_SDRAM_1_SIZE;
#endif
#if ( CONFIG_NR_DRAM_BANKS > 1 )
	gd->bd->bi_dram[1].start = SCB9328_SDRAM_2;
	gd->bd->bi_dram[1].size = SCB9328_SDRAM_2_SIZE;
#endif
#if ( CONFIG_NR_DRAM_BANKS > 2 )
	gd->bd->bi_dram[2].start = SCB9328_SDRAM_3;
	gd->bd->bi_dram[2].size = SCB9328_SDRAM_3_SIZE;
#endif
#if ( CONFIG_NR_DRAM_BANKS > 3 )
	gd->bd->bi_dram[3].start = SCB9328_SDRAM_4;
	gd->bd->bi_dram[3].size = SCB9328_SDRAM_4_SIZE;
#endif
	return 0;
}


void show_boot_progress (int status)
{
	return;
}

#ifdef CONFIG_DRIVER_DM9000
int board_eth_init(bd_t *bis)
{
	return dm9000_initialize(bis);
}
#endif
