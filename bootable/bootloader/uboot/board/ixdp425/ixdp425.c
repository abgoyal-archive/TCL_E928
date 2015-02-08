

#include <common.h>
#include <command.h>
#include <malloc.h>
#include <netdev.h>
#include <asm/arch/ixp425.h>

DECLARE_GLOBAL_DATA_PTR;

int board_init (void)
{
	/* arch number of IXDP */
	gd->bd->bi_arch_number = MACH_TYPE_IXDP425;

	/* adress of boot parameters */
	gd->bd->bi_boot_params = 0x00000100;

#ifdef CONFIG_IXDPG425
	/* arch number of IXDP */
	gd->bd->bi_arch_number = MACH_TYPE_IXDPG425;

	/*
	 * Get realtek RTL8305 switch and SLIC out of reset
	 */
	GPIO_OUTPUT_SET(CONFIG_SYS_GPIO_SWITCH_RESET_N);
	GPIO_OUTPUT_ENABLE(CONFIG_SYS_GPIO_SWITCH_RESET_N);
	GPIO_OUTPUT_SET(CONFIG_SYS_GPIO_SLIC_RESET_N);
	GPIO_OUTPUT_ENABLE(CONFIG_SYS_GPIO_SLIC_RESET_N);

	/*
	 * Setup GPIO's for PCI INTA & INTB
	 */
	GPIO_OUTPUT_DISABLE(CONFIG_SYS_GPIO_PCI_INTA_N);
	GPIO_INT_ACT_LOW_SET(CONFIG_SYS_GPIO_PCI_INTA_N);
	GPIO_OUTPUT_DISABLE(CONFIG_SYS_GPIO_PCI_INTB_N);
	GPIO_INT_ACT_LOW_SET(CONFIG_SYS_GPIO_PCI_INTB_N);

	/*
	 * Setup GPIO's for 33MHz clock output
	 */
	*IXP425_GPIO_GPCLKR = 0x01FF01FF;
	GPIO_OUTPUT_ENABLE(CONFIG_SYS_GPIO_PCI_CLK);
	GPIO_OUTPUT_ENABLE(CONFIG_SYS_GPIO_EXTBUS_CLK);
#endif

	return 0;
}

int checkboard(void)
{
	char *s = getenv("serial#");

#ifdef CONFIG_IXDPG425
	puts("Board: IXDPG425 - Intel Network Gateway Reference Platform");
#else
	puts("Board: IXDP425 - Intel Development Platform");
#endif

	if (s != NULL) {
		puts(", serial# ");
		puts(s);
	}
	putc('\n');

	return (0);
}

int dram_init (void)
{
	gd->bd->bi_dram[0].start = PHYS_SDRAM_1;
	gd->bd->bi_dram[0].size  = PHYS_SDRAM_1_SIZE;

	return (0);
}

#if defined(CONFIG_CMD_PCI) || defined(CONFIG_PCI)
extern struct pci_controller hose;
extern void pci_ixp_init(struct pci_controller * hose);

void pci_init_board(void)
{
	extern void pci_ixp_init (struct pci_controller *hose);

	pci_ixp_init(&hose);
}
#endif

int board_eth_init(bd_t *bis)
{
	return pci_eth_init(bis);
}
