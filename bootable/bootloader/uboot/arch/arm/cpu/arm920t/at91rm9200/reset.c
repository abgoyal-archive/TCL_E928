

#include <common.h>
#include <asm/arch/hardware.h>

void board_reset(void) __attribute__((__weak__));

void reset_cpu (ulong ignored)
{

#if defined(CONFIG_AT91RM9200_USART)
	/*shutdown the console to avoid strange chars during reset */
	serial_exit();
#endif

	if (board_reset)
		board_reset();

	/* this is the way Linux does it */

	/* FIXME:
	 * These defines should be moved into
	 * include/asm-arm/arch-at91rm9200/AT91RM9200.h
	 * as soon as the whitespace fix gets applied.
	 */
	#define AT91C_ST_RSTEN (0x1 << 16)
	#define AT91C_ST_EXTEN (0x1 << 17)
	#define AT91C_ST_WDRST (0x1 <<  0)
	#define ST_WDMR *((unsigned long *)0xfffffd08)	/* watchdog mode register */
	#define ST_CR *((unsigned long *)0xfffffd00)	/* system clock control register */

	ST_WDMR = AT91C_ST_RSTEN | AT91C_ST_EXTEN | 1 ;
	ST_CR = AT91C_ST_WDRST;

	while (1);
	/* Never reached */
}
