

#include <common.h>
#include <pci.h>
#include <usb.h>

#include "ehci.h"
#include "ehci-core.h"

#ifdef CONFIG_PCI_EHCI_DEVICE
static struct pci_device_id ehci_pci_ids[] = {
	/* Please add supported PCI EHCI controller ids here */
	{0x1033, 0x00E0},
	{0, 0}
};
#endif

int ehci_hcd_init(void)
{
	pci_dev_t pdev;
	uint32_t addr;

	pdev = pci_find_devices(ehci_pci_ids, CONFIG_PCI_EHCI_DEVICE);
	if (pdev == -1) {
		printf("EHCI host controller not found\n");
		return -1;
	}

	pci_read_config_dword(pdev, PCI_BASE_ADDRESS_0, &addr);
	hccr = (struct ehci_hccr *)addr;
	hcor = (struct ehci_hcor *)((uint32_t) hccr +
			HC_LENGTH(ehci_readl(&hccr->cr_capbase)));

	return 0;
}

int ehci_hcd_stop(void)
{
	return 0;
}
