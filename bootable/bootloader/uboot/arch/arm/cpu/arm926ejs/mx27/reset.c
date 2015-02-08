

#include <common.h>
#include <asm/io.h>
#include <asm/arch/imx-regs.h>

void reset_cpu (ulong ignored)
{
	struct wdog_regs *regs = (struct wdog_regs *)IMX_WDT_BASE;
	/* Disable watchdog and set Time-Out field to 0 */
	writel(0x00000000, &regs->wcr);

	/* Write Service Sequence */
	writel(0x00005555, &regs->wsr);
	writel(0x0000AAAA, &regs->wsr);

	/* Enable watchdog */
	writel(WCR_WDE, &regs->wcr);

	while (1);
	/*NOTREACHED*/
}
