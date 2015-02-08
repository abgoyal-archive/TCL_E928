



#ifndef _PCI_I386_H_
#define _PCI_I386_H_	1

void pci_setup_type1(struct pci_controller* hose, u32 cfg_addr, u32 cfg_data);
int pci_enable_legacy_video_ports(struct pci_controller* hose);
int pci_shadow_rom(pci_dev_t dev, unsigned char *dest);
void pci_remove_rom_window(struct pci_controller* hose, u32 addr);
u32 pci_get_rom_window(struct pci_controller* hose, int size);
#endif
