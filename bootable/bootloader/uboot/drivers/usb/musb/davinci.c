

#include <common.h>
#include <asm/io.h>
#include "davinci.h"
#include <asm/arch/hardware.h>

/* MUSB platform configuration */
struct musb_config musb_cfg = {
	(struct	musb_regs *)MENTOR_USB0_BASE,
	DAVINCI_USB_TIMEOUT,
	0
};

/* MUSB module register overlay */
struct davinci_usb_regs *dregs;

static u8 phy_on(void)
{
	u32 timeout;
#ifdef DAVINCI_DM365EVM
	u32 val;
#endif
	/* Wait until the USB phy is turned on */
#ifdef DAVINCI_DM365EVM
	writel(USBPHY_PHY24MHZ | USBPHY_SESNDEN |
			USBPHY_VBDTCTEN, USBPHY_CTL_PADDR);
#else
	writel(USBPHY_SESNDEN | USBPHY_VBDTCTEN, USBPHY_CTL_PADDR);
#endif
	timeout = musb_cfg.timeout;

#ifdef DAVINCI_DM365EVM
	/* Set the ownership of GIO33 to USB */
	val = readl(PINMUX4);
	val &= ~(PINMUX4_USBDRVBUS_BITCLEAR);
	val |= PINMUX4_USBDRVBUS_BITSET;
	writel(val, PINMUX4);
#endif
	while (timeout--)
		if (readl(USBPHY_CTL_PADDR) & USBPHY_PHYCLKGD)
			return 1;

	/* USB phy was not turned on */
	return 0;
}

static void phy_off(void)
{
	/* powerdown the on-chip PHY and its oscillator */
	writel(USBPHY_OSCPDWN | USBPHY_PHYPDWN, USBPHY_CTL_PADDR);
}

int musb_platform_init(void)
{
	u32  revision;

	/* enable USB VBUS */
#ifndef DAVINCI_DM365EVM
	enable_vbus();
#endif
	/* start the on-chip USB phy and its pll */
	if (!phy_on())
		return -1;

	/* reset the controller */
	dregs = (struct davinci_usb_regs *)DAVINCI_USB0_BASE;
	writel(1, &dregs->ctrlr);
	udelay(5000);

	/* Returns zero if e.g. not clocked */
	revision = readl(&dregs->version);
	if (!revision)
		return -1;

	/* Disable all interrupts */
	writel(DAVINCI_USB_USBINT_MASK | DAVINCI_USB_RXINT_MASK |
			DAVINCI_USB_TXINT_MASK , &dregs->intmsksetr);
	return 0;
}

void musb_platform_deinit(void)
{
	/* Turn of the phy */
	phy_off();

	/* flush any interrupts */
	writel(DAVINCI_USB_USBINT_MASK | DAVINCI_USB_TXINT_MASK |
			DAVINCI_USB_RXINT_MASK , &dregs->intclrr);
}
