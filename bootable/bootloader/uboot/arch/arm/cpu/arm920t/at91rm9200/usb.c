

#include <common.h>

#if defined(CONFIG_USB_OHCI_NEW) && defined(CONFIG_SYS_USB_OHCI_CPU_INIT)
# ifdef CONFIG_AT91RM9200

#include <asm/arch/hardware.h>

int usb_cpu_init(void)
{
	/* Enable USB host clock. */
	*AT91C_PMC_SCER = AT91C_PMC_UHP;	/* 48MHz clock enabled for UHP */
	*AT91C_PMC_PCER = 1 << AT91C_ID_UHP;	/* Peripheral Clock Enable Register */
	return 0;
}

int usb_cpu_stop(void)
{
	/* Initialization failed */
	*AT91C_PMC_PCDR = 1 << AT91C_ID_UHP;	/* Peripheral Clock Disable Register */
	*AT91C_PMC_SCDR = AT91C_PMC_UHP;	/* 48MHz clock disabled for UHP */
	return 0;
}

int usb_cpu_init_fail(void)
{
	return usb_cpu_stop();
}

# endif /* CONFIG_AT91RM9200 */
#endif /* defined(CONFIG_USB_OHCI) && defined(CONFIG_SYS_USB_OHCI_CPU_INIT) */
