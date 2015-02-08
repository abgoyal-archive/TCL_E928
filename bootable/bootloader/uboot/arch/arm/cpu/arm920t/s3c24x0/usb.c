

#include <common.h>

#if defined(CONFIG_USB_OHCI_NEW) && \
    defined(CONFIG_SYS_USB_OHCI_CPU_INIT) && \
    defined(CONFIG_S3C24X0)

#include <asm/arch/s3c24x0_cpu.h>
#include <asm/io.h>

int usb_cpu_init(void)
{
	struct s3c24x0_clock_power *clk_power = s3c24x0_get_base_clock_power();
	struct s3c24x0_gpio *gpio = s3c24x0_get_base_gpio();

	/*
	 * Set the 48 MHz UPLL clocking. Values are taken from
	 * "PLL value selection guide", 6-23, s3c2400_UM.pdf.
	 */
	writel((40 << 12) + (1 << 4) + 2, &clk_power->UPLLCON);
	/* 1 = use pads related USB for USB host */
	writel(readl(&gpio->MISCCR) | 0x8, &gpio->MISCCR);

	/*
	 * Enable USB host clock.
	 */
	writel(readl(&clk_power->CLKCON) | (1 << 4), &clk_power->CLKCON);

	return 0;
}

int usb_cpu_stop(void)
{
	struct s3c24x0_clock_power *clk_power = s3c24x0_get_base_clock_power();
	/* may not want to do this */
	writel(readl(&clk_power->CLKCON) & ~(1 << 4), &clk_power->CLKCON);
	return 0;
}

int usb_cpu_init_fail(void)
{
	struct s3c24x0_clock_power *clk_power = s3c24x0_get_base_clock_power();
	writel(readl(&clk_power->CLKCON) & ~(1 << 4), &clk_power->CLKCON);
	return 0;
}

#endif /* defined(CONFIG_USB_OHCI_NEW) && \
	   defined(CONFIG_SYS_USB_OHCI_CPU_INIT) && \
	   defined(CONFIG_S3C24X0) */
