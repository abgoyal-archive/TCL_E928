

#include <common.h>
#include <asm/immap.h>

#define PERIOD		13	/* system bus period in ns */
#define SDRAM_TREFI	7800	/* in ns */

int checkboard(void)
{
	puts("Board: ");
	puts("Freescale MCF5275 EVB\n");
	return 0;
};

phys_size_t initdram(int board_type)
{
	volatile sdramctrl_t *sdp = (sdramctrl_t *)(MMAP_SDRAM);
	volatile gpio_t *gpio_reg = (gpio_t *)(MMAP_GPIO);

	gpio_reg->par_sdram = 0x3FF; /* Enable SDRAM */

	/* Set up chip select */
	sdp->sdbar0 = CONFIG_SYS_SDRAM_BASE;
	sdp->sdbmr0 = MCF_SDRAMC_SDMRn_BAM_32M | MCF_SDRAMC_SDMRn_V;

	/* Set up timing */
	sdp->sdcfg1 = 0x83711630;
	sdp->sdcfg2 = 0x46770000;

	/* Enable clock */
	sdp->sdcr = MCF_SDRAMC_SDCR_MODE_EN | MCF_SDRAMC_SDCR_CKE;

	/* Set precharge */
	sdp->sdcr |= MCF_SDRAMC_SDCR_IPALL;

	/* Dummy write to start SDRAM */
	*((volatile unsigned long *)CONFIG_SYS_SDRAM_BASE) = 0xa5a59696;

	/* Send LEMR */
	sdp->sdmr = MCF_SDRAMC_SDMR_BNKAD_LEMR
			| MCF_SDRAMC_SDMR_AD(0x0)
			| MCF_SDRAMC_SDMR_CMD;
	*((volatile unsigned long *)CONFIG_SYS_SDRAM_BASE) = 0xa5a59696;

	/* Send LMR */
	sdp->sdmr = 0x058d0000;
	*((volatile unsigned long *)CONFIG_SYS_SDRAM_BASE) = 0xa5a59696;

	/* Stop sending commands */
	sdp->sdmr &= ~(MCF_SDRAMC_SDMR_CMD);

	/* Set precharge */
	sdp->sdcr |= MCF_SDRAMC_SDCR_IPALL;
	*((volatile unsigned long *)CONFIG_SYS_SDRAM_BASE) = 0xa5a59696;

	/* Stop manual precharge, send 2 IREF */
	sdp->sdcr &= ~(MCF_SDRAMC_SDCR_IPALL);
	sdp->sdcr |= MCF_SDRAMC_SDCR_IREF;
	*((volatile unsigned long *)CONFIG_SYS_SDRAM_BASE) = 0xa5a59696;
	*((volatile unsigned long *)CONFIG_SYS_SDRAM_BASE) = 0xa5a59696;

	/* Write mode register, clear reset DLL */
	sdp->sdmr = 0x018d0000;
	*((volatile unsigned long *)CONFIG_SYS_SDRAM_BASE) = 0xa5a59696;

	/* Stop sending commands */
	sdp->sdmr &= ~(MCF_SDRAMC_SDMR_CMD);
	sdp->sdcr &= ~(MCF_SDRAMC_SDCR_MODE_EN);

	/* Turn on auto refresh, lock SDMR */
	sdp->sdcr =
		MCF_SDRAMC_SDCR_CKE
		| MCF_SDRAMC_SDCR_REF
		| MCF_SDRAMC_SDCR_MUX(1)
		/* 1 added to round up */
		| MCF_SDRAMC_SDCR_RCNT((SDRAM_TREFI/(PERIOD*64)) - 1 + 1)
		| MCF_SDRAMC_SDCR_DQS_OE(0x3);

	return CONFIG_SYS_SDRAM_SIZE * 1024 * 1024;
};

int testdram(void)
{
	/* TODO: XXX XXX XXX */
	printf("DRAM test not implemented!\n");

	return (0);
}
