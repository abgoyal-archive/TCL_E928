

#ifndef _ASM_IC_SC520_PCI_H_
#define _ASM_IC_SC520_PCI_H_ 1

/* bus mapping constants (used for PCI core initialization) */																																																 /* bus mapping constants */
#define SC520_REG_ADDR		0x00000cf8
#define SC520_REG_DATA		0x00000cfc

#define SC520_ISA_MEM_PHYS	0x00000000
#define SC520_ISA_MEM_BUS	0x00000000
#define SC520_ISA_MEM_SIZE	0x01000000

#define SC520_ISA_IO_PHYS	0x00000000
#define SC520_ISA_IO_BUS	0x00000000
#define SC520_ISA_IO_SIZE	0x00001000

#define SC520_PCI_IO_PHYS	0x00001000
#define SC520_PCI_IO_BUS	0x00001000
#define SC520_PCI_IO_SIZE	0x0000d000

/* system memory from 0x00000000 to 0x0fffffff */
#define	SC520_PCI_MEMORY_PHYS	0x00000000
#define	SC520_PCI_MEMORY_BUS	0x00000000
#define SC520_PCI_MEMORY_SIZE	0x10000000

#define SC520_PCI_MEM_PHYS	0x10000000
#define SC520_PCI_MEM_BUS	0x10000000
#define SC520_PCI_MEM_SIZE	0x17000000

/* pin number used for PCI interrupt mappings */
#define SC520_PCI_INTA 0
#define SC520_PCI_INTB 1
#define SC520_PCI_INTC 2
#define SC520_PCI_INTD 3
#define SC520_PCI_GPIRQ0 4
#define SC520_PCI_GPIRQ1 5
#define SC520_PCI_GPIRQ2 6
#define SC520_PCI_GPIRQ3 7
#define SC520_PCI_GPIRQ4 8
#define SC520_PCI_GPIRQ5 9
#define SC520_PCI_GPIRQ6 10
#define SC520_PCI_GPIRQ7 11
#define SC520_PCI_GPIRQ8 12
#define SC520_PCI_GPIRQ9 13
#define SC520_PCI_GPIRQ10 14

extern int sc520_pci_ints[];

void pci_sc520_init(struct pci_controller *hose);
int pci_set_regions(struct pci_controller *hose);
int pci_sc520_set_irq(int pci_pin, int irq);

#endif
