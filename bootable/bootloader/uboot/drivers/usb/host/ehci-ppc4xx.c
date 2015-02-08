
#include <common.h>
#include <usb.h>

#include "ehci.h"
#include "ehci-core.h"

int ehci_hcd_init(void)
{
	hccr = (struct ehci_hccr *)(CONFIG_SYS_PPC4XX_USB_ADDR);
	hcor = (struct ehci_hcor *)((uint32_t) hccr +
		HC_LENGTH(ehci_readl(&hccr->cr_capbase)));
	usb_dev_init();
	return 0;
}

int ehci_hcd_stop(void)
{
	return 0;
}
