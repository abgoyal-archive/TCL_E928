

#include <common.h>
#include <pci.h>
#include <usb.h>
#include <asm/io.h>
#include <usb/ehci-fsl.h>

#include "ehci.h"
#include "ehci-core.h"

int ehci_hcd_init(void)
{
	struct usb_ehci *ehci;

	ehci = (struct usb_ehci *)CONFIG_SYS_MPC8xxx_USB_ADDR;
	hccr = (struct ehci_hccr *)((uint32_t)&ehci->caplength);
	hcor = (struct ehci_hcor *)((uint32_t) hccr +
			HC_LENGTH(ehci_readl(&hccr->cr_capbase)));

	/* Set to Host mode */
	setbits_le32(&ehci->usbmode, CM_HOST);

	out_be32(&ehci->snoop1, SNOOP_SIZE_2GB);
	out_be32(&ehci->snoop2, 0x80000000 | SNOOP_SIZE_2GB);

	/* Init phy */
	if (!strcmp(getenv("usb_phy_type"), "utmi"))
		out_le32(&(hcor->or_portsc[0]), PORT_PTS_UTMI);
	else
		out_le32(&(hcor->or_portsc[0]), PORT_PTS_ULPI);

	/* Enable interface. */
	setbits_be32(&ehci->control, USB_EN);

	out_be32(&ehci->prictrl, 0x0000000c);
	out_be32(&ehci->age_cnt_limit, 0x00000040);
	out_be32(&ehci->sictrl, 0x00000001);

	in_le32(&ehci->usbmode);

	return 0;
}

int ehci_hcd_stop(void)
{
	return 0;
}
