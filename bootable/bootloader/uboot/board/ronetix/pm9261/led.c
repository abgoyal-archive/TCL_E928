

#include <common.h>
#include <asm/arch/at91sam9261.h>
#include <asm/arch/at91_pmc.h>
#include <asm/arch/at91_pio.h>
#include <asm/arch/io.h>

void coloured_LED_init(void)
{
	at91_pmc_t	*pmc	= (at91_pmc_t *) AT91_PMC_BASE;

	/* Enable clock */
	writel(1 << AT91SAM9261_ID_PIOC, &pmc->pcer);

	at91_set_pio_output(CONFIG_RED_LED, 1);
	at91_set_pio_output(CONFIG_GREEN_LED, 1);
	at91_set_pio_output(CONFIG_YELLOW_LED, 1);

	at91_set_pio_value(CONFIG_RED_LED, 0);
	at91_set_pio_value(CONFIG_GREEN_LED, 1);
	at91_set_pio_value(CONFIG_YELLOW_LED, 1);
}
