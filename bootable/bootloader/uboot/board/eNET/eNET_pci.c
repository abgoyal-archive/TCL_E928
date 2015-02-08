
#include <common.h>
#include <pci.h>
#include <asm/pci.h>
#include <asm/ic/pci.h>

static void pci_enet_fixup_irq(struct pci_controller *hose, pci_dev_t dev)
{
	/* a configurable lists of IRQs to steal when we need one */
	static int irq_list[] = {
		CONFIG_SYS_FIRST_PCI_IRQ,
		CONFIG_SYS_SECOND_PCI_IRQ,
		CONFIG_SYS_THIRD_PCI_IRQ,
		CONFIG_SYS_FORTH_PCI_IRQ
	};
	static int next_irq_index=0;

	uchar tmp_pin;
	int pin;

	pci_hose_read_config_byte(hose, dev, PCI_INTERRUPT_PIN, &tmp_pin);
	pin = tmp_pin;

	pin -= 1; /* PCI config space use 1-based numbering */
	if (pin == -1) {
		return; /* device use no irq */
	}

	/* map device number +  pin to a pin on the sc520 */
	switch (PCI_DEV(dev)) {
	case 12:	/* First Ethernet Chip */
		pin += SC520_PCI_INTA;
		break;

	case 13:	/* Second Ethernet Chip */
		pin += SC520_PCI_INTB;
		break;

	default:
		return;
	}

	pin &= 3; /* wrap around */

	if (sc520_pci_ints[pin] == -1) {
		/* re-route one interrupt for us */
		if (next_irq_index > 3) {
			return;
		}
		if (pci_sc520_set_irq(pin, irq_list[next_irq_index])) {
			return;
		}
		next_irq_index++;
	}

	if (-1 != sc520_pci_ints[pin]) {
	pci_hose_write_config_byte(hose, dev, PCI_INTERRUPT_LINE,
					   sc520_pci_ints[pin]);
	}
	printf("fixup_irq: device %d pin %c irq %d\n",
	       PCI_DEV(dev), 'A' + pin, sc520_pci_ints[pin]);
}

static struct pci_controller enet_hose = {
	fixup_irq: pci_enet_fixup_irq,
};

void pci_init_board(void)
{
	pci_sc520_init(&enet_hose);
}

int pci_set_regions(struct pci_controller *hose)
{
	/* System memory space */
	pci_set_region(hose->regions + 0,
		       SC520_PCI_MEMORY_BUS,
		       SC520_PCI_MEMORY_PHYS,
		       SC520_PCI_MEMORY_SIZE,
		       PCI_REGION_MEM | PCI_REGION_SYS_MEMORY);

	/* ISA/PCI memory space */
	pci_set_region(hose->regions + 1,
		       SC520_ISA_MEM_BUS,
		       SC520_ISA_MEM_PHYS,
		       SC520_ISA_MEM_SIZE,
		       PCI_REGION_MEM);

	/* PCI I/O space */
	pci_set_region(hose->regions + 2,
		       SC520_PCI_IO_BUS,
		       SC520_PCI_IO_PHYS,
		       SC520_PCI_IO_SIZE,
		       PCI_REGION_IO);

	/* ISA/PCI I/O space */
	pci_set_region(hose->regions + 3,
		       SC520_ISA_IO_BUS,
		       SC520_ISA_IO_PHYS,
		       SC520_ISA_IO_SIZE,
		       PCI_REGION_IO);

	return 4;
}
