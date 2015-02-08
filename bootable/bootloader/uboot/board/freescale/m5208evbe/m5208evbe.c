

#include <config.h>
#include <common.h>
#include <asm/immap.h>

DECLARE_GLOBAL_DATA_PTR;

int checkboard(void)
{
	puts("Board: ");
	puts("Freescale M5208EVBe\n");
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
#ifdef CONFIG_SYS_SDRAM_BASE1
	sdram->cs1 = (CONFIG_SYS_SDRAM_BASE | i);
#endif
	sdram->cfg1 = CONFIG_SYS_SDRAM_CFG1;
	sdram->cfg2 = CONFIG_SYS_SDRAM_CFG2;

	udelay(500);

	/* Issue PALL */
	sdram->ctrl = (CONFIG_SYS_SDRAM_CTRL | 2);
	asm("nop");

	/* Perform two refresh cycles */
	sdram->ctrl = CONFIG_SYS_SDRAM_CTRL | 4;
	sdram->ctrl = CONFIG_SYS_SDRAM_CTRL | 4;
	asm("nop");

	/* Issue LEMR */
	sdram->mode = CONFIG_SYS_SDRAM_MODE;
	asm("nop");
	sdram->mode = CONFIG_SYS_SDRAM_EMOD;
	asm("nop");

	sdram->ctrl = (CONFIG_SYS_SDRAM_CTRL | 2);
	asm("nop");

	sdram->ctrl = (CONFIG_SYS_SDRAM_CTRL & ~0x80000000) | 0x10000F00;
	asm("nop");

	udelay(100);

	return dramsize;
};

int testdram(void)
{
	/* TODO: XXX XXX XXX */
	printf("DRAM test not implemented!\n");

	return (0);
}
