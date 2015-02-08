

#include <common.h>
#include <asm/io.h>
#include <asm/arch/hardware.h>
#include <asm/arch/at91_st.h>

void board_reset(void) __attribute__((__weak__));

void reset_cpu(ulong ignored)
{
	at91_st_t *st = (at91_st_t *) AT91_ST_BASE;
#if defined(CONFIG_AT91RM9200_USART)
	/*shutdown the console to avoid strange chars during reset */
	serial_exit();
#endif

	if (board_reset)
		board_reset();

	/* Reset the cpu by setting up the watchdog timer */
	writel(AT91_ST_WDMR_RSTEN | AT91_ST_WDMR_EXTEN | AT91_ST_WDMR_WDV(2),
		&st->wdmr);
	writel(AT91_ST_CR_WDRST, &st->cr);
	/* and let it timeout */
	while (1)
		;
	/* Never reached */
}
