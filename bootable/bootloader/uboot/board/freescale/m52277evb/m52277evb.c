

#include <common.h>
#include <asm/immap.h>

DECLARE_GLOBAL_DATA_PTR;

int checkboard(void)
{
	puts("Board: ");
	puts("Freescale M52277 EVB\n");
	return 0;
};

phys_size_t initdram(int board_type)
{
	u32 dramsize;

#ifdef CONFIG_CF_SBF
	/*
	 * Serial Boot: The dram is already initialized in start.S
	 * only require to return DRAM size
	 */
	dramsize = CONFIG_SYS_SDRAM_SIZE * 0x100000;
#else
	volatile sdramc_t *sdram = (volatile sdramc_t *)(MMAP_SDRAM);
	volatile gpio_t *gpio = (volatile gpio_t *)(MMAP_GPIO);
	u32 i;

	dramsize = CONFIG_SYS_SDRAM_SIZE * 0x100000;

	for (i = 0x13; i < 0x20; i++) {
		if (dramsize == (1 << i))
			break;
	}
	i--;

	gpio->mscr_sdram = CONFIG_SYS_SDRAM_DRV_STRENGTH;

	sdram->sdcs0 = (CONFIG_SYS_SDRAM_BASE | i);

	sdram->sdcfg1 = CONFIG_SYS_SDRAM_CFG1;
	sdram->sdcfg2 = CONFIG_SYS_SDRAM_CFG2;

	/* Issue PALL */
	sdram->sdcr = CONFIG_SYS_SDRAM_CTRL | 2;
	__asm__("nop");

	/* Issue LEMR */
	sdram->sdmr = CONFIG_SYS_SDRAM_MODE;
	__asm__("nop");
	sdram->sdmr = CONFIG_SYS_SDRAM_EMOD;
	__asm__("nop");

	udelay(1000);

	/* Issue PALL */
	sdram->sdcr = CONFIG_SYS_SDRAM_CTRL | 2;
	__asm__("nop");

	/* Perform two refresh cycles */
	sdram->sdcr = CONFIG_SYS_SDRAM_CTRL | 4;
	__asm__("nop");
	sdram->sdcr = CONFIG_SYS_SDRAM_CTRL | 4;
	__asm__("nop");

	sdram->sdcr = (CONFIG_SYS_SDRAM_CTRL & ~0x80000000) | 0x10000C00;

	udelay(100);
#endif
	return (dramsize);
};

int testdram(void)
{
	/* TODO: XXX XXX XXX */
	printf("DRAM test not implemented!\n");

	return (0);
}
