

#include <common.h>
#include <asm/arch/hardware.h>
#include <asm/arch/at91_rstc.h>
#include <asm/arch/io.h>

void reset_cpu(ulong ignored)
{
	at91_rstc_t *rstc = (at91_rstc_t *) AT91_RSTC_BASE;

	/* this is the way Linux does it */

	writel(AT91_RSTC_KEY | AT91_RSTC_CR_PROCRST | AT91_RSTC_CR_PERRST,
		&rstc->cr);

	while (1);
	/* Never reached */
}
