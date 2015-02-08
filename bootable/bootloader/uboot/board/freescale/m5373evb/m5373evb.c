

#include <config.h>
#include <common.h>
#include <asm/immap.h>

DECLARE_GLOBAL_DATA_PTR;

int checkboard(void)
{
	puts("Board: ");
	puts("Freescale FireEngine 5373 EVB\n");
	return 0;
};

phys_size_t initdram(int board_type)
{
	volatile sdram_t *sdram = (volatile sdram_t *)(MMAP_SDRAM);
	u32 dramsize, i;

	dramsize = CONFIG_SYS_SDRAM_SIZE * 0x100000;

	for (i = 0x13; i < 0x20; i++) {
		if (dramsize == (1 << i))
			break;
	}
	i--;

	sdram->cs0 = (CONFIG_SYS_SDRAM_BASE | i);
	sdram->cfg1 = CONFIG_SYS_SDRAM_CFG1;
	sdram->cfg2 = CONFIG_SYS_SDRAM_CFG2;

	/* Issue PALL */
	sdram->ctrl = CONFIG_SYS_SDRAM_CTRL | 2;

	/* Issue LEMR */
	sdram->mode = CONFIG_SYS_SDRAM_EMOD;
	sdram->mode = (CONFIG_SYS_SDRAM_MODE | 0x04000000);

	udelay(500);

	/* Issue PALL */
	sdram->ctrl = (CONFIG_SYS_SDRAM_CTRL | 2);

	/* Perform two refresh cycles */
	sdram->ctrl = CONFIG_SYS_SDRAM_CTRL | 4;
	sdram->ctrl = CONFIG_SYS_SDRAM_CTRL | 4;

	sdram->mode = CONFIG_SYS_SDRAM_MODE;

	sdram->ctrl = (CONFIG_SYS_SDRAM_CTRL & ~0x80000000) | 0x10000c00;

	udelay(100);

	return dramsize;
};

int testdram(void)
{
	/* TODO: XXX XXX XXX */
	printf("DRAM test not implemented!\n");

	return (0);
}
