

#include <common.h>

#if defined(CONFIG_USB_OHCI_NEW) && defined(CONFIG_SYS_USB_OHCI_CPU_INIT)

#include <asm/arch/hardware.h>
#include <asm/arch/io.h>
#include <asm/arch/at91_pmc.h>
#include <asm/arch/clk.h>

int usb_cpu_init(void)
{
	at91_pmc_t *pmc	= (at91_pmc_t *)AT91_PMC_BASE;

#if defined(CONFIG_AT91CAP9) || defined(CONFIG_AT91SAM9260) || \
    defined(CONFIG_AT91SAM9263) || defined(CONFIG_AT91SAM9G20) || \
    defined(CONFIG_AT91SAM9261)
	/* Enable PLLB */
	writel(get_pllb_init(), &pmc->pllbr);
	while ((readl(&pmc->sr) & AT91_PMC_LOCKB) != AT91_PMC_LOCKB)
		;
#endif

	/* Enable USB host clock. */
	writel(1 << AT91_ID_UHP, &pmc->pcer);
#ifdef CONFIG_AT91SAM9261
	writel(AT91_PMC_UHP | AT91_PMC_HCK0, &pmc->scer);
#else
	writel(AT91_PMC_UHP, &pmc->scer);
#endif

	return 0;
}

int usb_cpu_stop(void)
{
	at91_pmc_t *pmc	= (at91_pmc_t *)AT91_PMC_BASE;

	/* Disable USB host clock. */
	writel(1 << AT91_ID_UHP, &pmc->pcdr);
#ifdef CONFIG_AT91SAM9261
	writel(AT91_PMC_UHP | AT91_PMC_HCK0, &pmc->scdr);
#else
	writel(AT91_PMC_UHP, &pmc->scdr);
#endif

#if defined(CONFIG_AT91CAP9) || defined(CONFIG_AT91SAM9260) || \
    defined(CONFIG_AT91SAM9263) || defined(CONFIG_AT91SAM9G20)
	/* Disable PLLB */
	writel(0, &pmc->pllbr);
	while ((readl(&pmc->sr) & AT91_PMC_LOCKB) != 0)
		;
#endif

	return 0;
}

int usb_cpu_init_fail(void)
{
	return usb_cpu_stop();
}

#endif /* defined(CONFIG_USB_OHCI) && defined(CONFIG_SYS_USB_OHCI_CPU_INIT) */
