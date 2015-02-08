

#include <common.h>
#include <usb.h>

#include "ehci.h"
#include "ehci-core.h"

int vct_ehci_hcd_init(u32 *hccr, u32 *hcor);

int ehci_hcd_init(void)
{
	int ret;
	u32 vct_hccr;
	u32 vct_hcor;

	/*
	 * Init VCT specific stuff
	 */
	ret = vct_ehci_hcd_init(&vct_hccr, &vct_hcor);
	if (ret)
		return ret;

	hccr = (struct ehci_hccr *)vct_hccr;
	hcor = (struct ehci_hcor *)vct_hcor;

	return 0;
}

int ehci_hcd_stop(void)
{
	return 0;
}
