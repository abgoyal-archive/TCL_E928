

#include <common.h>
#include <asm/arch/hardware.h>
#include <asm/arch/at91_pmc.h>
#include <asm/arch/at91_pio.h>
#include <asm/arch/gpio.h>
#include <asm/arch/io.h>

void coloured_LED_init(void)
{
	/* Enable clock */
	at91_pmc_t	*pmc	= (at91_pmc_t *) AT91_PMC_BASE;

	writel(1 << AT91SAM9263_ID_PIOB | 1 << AT91SAM9263_ID_PIOCDE,
		&pmc->pcer);

	at91_set_pio_output(CONFIG_RED_LED, 1);
	at91_set_pio_output(CONFIG_GREEN_LED, 1);
	at91_set_pio_output(CONFIG_YELLOW_LED, 1);

	at91_set_pio_value(CONFIG_RED_LED, 0);
	at91_set_pio_value(CONFIG_GREEN_LED, 1);
	at91_set_pio_value(CONFIG_YELLOW_LED, 1);
}
