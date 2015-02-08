
/* ide.c - ide support functions */


#include <common.h>
#if defined(CONFIG_CMD_IDE)
#include <ata.h>
#include <ide.h>
#include <pci.h>

extern ulong ide_bus_offset[CONFIG_SYS_IDE_MAXBUS];

int ide_preinit (void)
{
	int status;
	pci_dev_t devbusfn;
	int l;

	status = 1;
	if (CPCI750_SLAVE_TEST != 0)
		return status;
	for (l = 0; l < CONFIG_SYS_IDE_MAXBUS; l++) {
		ide_bus_offset[l] = -ATA_STATUS;
	}
	devbusfn = pci_find_device (0x1103, 0x0004, 0);
	if (devbusfn == -1)
	        devbusfn = pci_find_device (0x1095, 0x3114, 0);
	if (devbusfn != -1) {
		ulong *ide_bus_offset_ptr;

		status = 0;

		ide_bus_offset_ptr = &ide_bus_offset[0];
		pci_read_config_dword (devbusfn, PCI_BASE_ADDRESS_0,
				       (u32 *)ide_bus_offset_ptr);
		ide_bus_offset[0] &= 0xfffffffe;
		ide_bus_offset[0] += CONFIG_SYS_PCI0_IO_SPACE;
		ide_bus_offset_ptr = &ide_bus_offset[1];
		pci_read_config_dword (devbusfn, PCI_BASE_ADDRESS_2,
				       (u32 *)ide_bus_offset_ptr);
		ide_bus_offset[1] &= 0xfffffffe;
		ide_bus_offset[1] += CONFIG_SYS_PCI0_IO_SPACE;
	}
	return status;
}

void ide_set_reset (int flag) {
	return;
}

#endif /* of CONFIG_CMDS_IDE */
