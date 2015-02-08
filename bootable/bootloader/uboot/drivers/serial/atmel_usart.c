
#include <common.h>
#ifndef CONFIG_AT91_LEGACY
#define CONFIG_AT91_LEGACY
#warning Please update to use C structur SoC access !
#endif
#include <watchdog.h>

#include <asm/io.h>
#include <asm/arch/clk.h>
#include <asm/arch/memory-map.h>

#if defined(CONFIG_USART0)
# define USART_ID	0
# define USART_BASE	USART0_BASE
#elif defined(CONFIG_USART1)
# define USART_ID	1
# define USART_BASE	USART1_BASE
#elif defined(CONFIG_USART2)
# define USART_ID	2
# define USART_BASE	USART2_BASE
#elif defined(CONFIG_USART3)
# define USART_ID	3
# define USART_BASE	USART3_BASE
#endif

#include "atmel_usart.h"

DECLARE_GLOBAL_DATA_PTR;

void serial_setbrg(void)
{
	unsigned long divisor;
	unsigned long usart_hz;

	/*
	 *              Master Clock
	 * Baud Rate = --------------
	 *                16 * CD
	 */
	usart_hz = get_usart_clk_rate(USART_ID);
	divisor = (usart_hz / 16 + gd->baudrate / 2) / gd->baudrate;
	usart3_writel(BRGR, USART3_BF(CD, divisor));
}

int serial_init(void)
{
	usart3_writel(CR, USART3_BIT(RSTRX) | USART3_BIT(RSTTX));

	serial_setbrg();

	usart3_writel(CR, USART3_BIT(RXEN) | USART3_BIT(TXEN));
	usart3_writel(MR, (USART3_BF(USART_MODE, USART3_USART_MODE_NORMAL)
			   | USART3_BF(USCLKS, USART3_USCLKS_MCK)
			   | USART3_BF(CHRL, USART3_CHRL_8)
			   | USART3_BF(PAR, USART3_PAR_NONE)
			   | USART3_BF(NBSTOP, USART3_NBSTOP_1)));

	return 0;
}

void serial_putc(char c)
{
	if (c == '\n')
		serial_putc('\r');

	while (!(usart3_readl(CSR) & USART3_BIT(TXRDY))) ;
	usart3_writel(THR, c);
}

void serial_puts(const char *s)
{
	while (*s)
		serial_putc(*s++);
}

int serial_getc(void)
{
	while (!(usart3_readl(CSR) & USART3_BIT(RXRDY)))
		 WATCHDOG_RESET();
	return usart3_readl(RHR);
}

int serial_tstc(void)
{
	return (usart3_readl(CSR) & USART3_BIT(RXRDY)) != 0;
}
