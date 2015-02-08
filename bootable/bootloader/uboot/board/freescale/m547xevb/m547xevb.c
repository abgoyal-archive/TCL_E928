

#include <config.h>
#include <common.h>
#include <pci.h>
#include <asm/immap.h>

DECLARE_GLOBAL_DATA_PTR;

int checkboard(void)
{
	puts("Board: ");
	puts("Freescale FireEngine 5475 EVB\n");
	return 0;
};

phys_size_t initdram(int board_type)
{
	volatile siu_t *siu = (siu_t *) (MMAP_SIU);
	volatile sdram_t *sdram = (volatile sdram_t *)(MMAP_SDRAM);
	u32 dramsize, i;
#ifdef CONFIG_SYS_DRAMSZ1
	u32 temp;
#endif

	siu->drv = CONFIG_SYS_SDRAM_DRVSTRENGTH;

	dramsize = CONFIG_SYS_DRAMSZ * 0x100000;
	for (i = 0x13; i < 0x20; i++) {
		if (dramsize == (1 << i))
			break;
	}
	i--;
	siu->cs0cfg = (CONFIG_SYS_SDRAM_BASE | i);

#ifdef CONFIG_SYS_DRAMSZ1
	temp = CONFIG_SYS_DRAMSZ1 * 0x100000;
	for (i = 0x13; i < 0x20; i++) {
		if (temp == (1 << i))
			break;
	}
	i--;
	dramsize += temp;
	siu->cs1cfg = ((CONFIG_SYS_SDRAM_BASE + temp) | i);
#endif

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

	sdram->ctrl = (CONFIG_SYS_SDRAM_CTRL & ~0x80000000) | 0x10000F00;

	udelay(100);

	return dramsize;
};

int testdram(void)
{
	/* TODO: XXX XXX XXX */
	printf("DRAM test not implemented!\n");

	return (0);
}

#if defined(CONFIG_PCI)
static struct pci_controller hose;
extern void pci_mcf547x_8x_init(struct pci_controller *hose);

void pci_init_board(void)
{
	pci_mcf547x_8x_init(&hose);
}
#endif				/* CONFIG_PCI */
