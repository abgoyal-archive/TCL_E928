

#include <common.h>

#if defined(CONFIG_USB_OHCI_NEW) && defined(CONFIG_SYS_USB_OHCI_CPU_INIT)
# if defined(CONFIG_CPU_MONAHANS) || defined(CONFIG_PXA27X)

#include <asm/arch/pxa-regs.h>
#include <usb.h>

int usb_cpu_init(void)
{
#if defined(CONFIG_CPU_MONAHANS)
	/* Enable USB host clock. */
	CKENA |= (CKENA_2_USBHOST |  CKENA_20_UDC);
	udelay(100);
#endif
#if defined(CONFIG_PXA27X)
	/* Enable USB host clock. */
	CKEN |= CKEN10_USBHOST;
#endif

#if defined(CONFIG_CPU_MONAHANS)
	/* Configure Port 2 for Host (USB Client Registers) */
	UP2OCR = 0x3000c;
#endif

	UHCHR |= UHCHR_FHR;
	wait_ms(11);
	UHCHR &= ~UHCHR_FHR;

	UHCHR |= UHCHR_FSBIR;
	while (UHCHR & UHCHR_FSBIR)
		udelay(1);

#if defined(CONFIG_CPU_MONAHANS)
	UHCHR &= ~UHCHR_SSEP0;
#endif
#if defined(CONFIG_PXA27X)
	UHCHR &= ~UHCHR_SSEP2;
#endif
	UHCHR &= ~UHCHR_SSEP1;
	UHCHR &= ~UHCHR_SSE;

	return 0;
}

int usb_cpu_stop(void)
{
	UHCHR |= UHCHR_FHR;
	udelay(11);
	UHCHR &= ~UHCHR_FHR;

	UHCCOMS |= 1;
	udelay(10);

#if defined(CONFIG_CPU_MONAHANS)
	UHCHR |= UHCHR_SSEP0;
#endif
#if defined(CONFIG_PXA27X)
	UHCHR |= UHCHR_SSEP2;
#endif
	UHCHR |= UHCHR_SSEP1;
	UHCHR |= UHCHR_SSE;

	return 0;
}

int usb_cpu_init_fail(void)
{
	UHCHR |= UHCHR_FHR;
	udelay(11);
	UHCHR &= ~UHCHR_FHR;

	UHCCOMS |= 1;
	udelay(10);

#if defined(CONFIG_CPU_MONAHANS)
	UHCHR |= UHCHR_SSEP0;
#endif
#if defined(CONFIG_PXA27X)
	UHCHR |= UHCHR_SSEP2;
#endif
	UHCHR |= UHCHR_SSEP1;
	UHCHR |= UHCHR_SSE;

	return 0;
}

# endif /* defined(CONFIG_CPU_MONAHANS) || defined(CONFIG_PXA27X) */
#endif /* defined(CONFIG_USB_OHCI) && defined(CONFIG_SYS_USB_OHCI_CPU_INIT) */
