

#include <common.h>
#include <asm/processor.h>

int checkboard(void)
{
	puts("BOARD: SH7750/SH7750S/SH7750R Solution Engine\n");
	return 0;
}

int board_init(void)
{
	return 0;
}

int dram_init (void)
{
	DECLARE_GLOBAL_DATA_PTR;

	gd->bd->bi_memstart = CONFIG_SYS_SDRAM_BASE;
	gd->bd->bi_memsize = CONFIG_SYS_SDRAM_SIZE;
	printf("DRAM:  %dMB\n", CONFIG_SYS_SDRAM_SIZE / (1024 * 1024));
	return 0;
}

int board_late_init(void)
{
	return 0;
}
