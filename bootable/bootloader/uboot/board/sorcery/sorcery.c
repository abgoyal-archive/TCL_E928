

#include <common.h>
#include <mpc8220.h>
#include <asm/processor.h>
#include <asm/mmu.h>
#include <pci.h>
#include <netdev.h>

phys_size_t initdram (int board_type)
{
	ulong size;

	size = dramSetup ();

	return get_ram_size(CONFIG_SYS_SDRAM_BASE, size);
}

int checkboard (void)
{
	puts ("Board: Sorcery-C MPC8220\n");

	return 0;
}

#if defined(CONFIG_PCI)
static struct pci_controller hose;

#endif /* CONFIG_PCI */

void pci_init_board (void)
{
#ifdef CONFIG_PCI
	extern void pci_mpc8220_init (struct pci_controller *hose);
	pci_mpc8220_init (&hose);
#endif /* CONFIG_PCI */
}

int board_eth_init(bd_t *bis)
{
	/* Initialize built-in FEC first */
	cpu_eth_init(bis);
	return pci_eth_init(bis);
}
