
#include <common.h>
#include <usb.h>

#include "ehci.h"
#include "ehci-core.h"
int ehci_hcd_init(void)
{
	hccr = (struct ehci_hccr *)(0xcd000100);
	hcor = (struct ehci_hcor *)((uint32_t) hccr
			+ HC_LENGTH(ehci_readl(&hccr->cr_capbase)));

	printf("IXP4XX init hccr %x and hcor %x hc_length %d\n",
		(uint32_t)hccr, (uint32_t)hcor,
		(uint32_t)HC_LENGTH(ehci_readl(&hccr->cr_capbase)));
	return 0;
}

int ehci_hcd_stop(void)
{
	return 0;
}
