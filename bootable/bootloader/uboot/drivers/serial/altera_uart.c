


#include <common.h>
#include <watchdog.h>
#include <asm/io.h>
#include <nios2-io.h>

DECLARE_GLOBAL_DATA_PTR;


static nios_uart_t *uart = (nios_uart_t *) CONFIG_SYS_NIOS_CONSOLE;

#if defined(CONFIG_SYS_NIOS_FIXEDBAUD)

void serial_setbrg (void){ return; }
int serial_init (void) { return (0);}

#else

void serial_setbrg (void)
{
	unsigned div;

	div = (CONFIG_SYS_CLK_FREQ/gd->baudrate)-1;
	writel (div, &uart->divisor);
	return;
}

int serial_init (void)
{
	serial_setbrg ();
	return (0);
}

#endif /* CONFIG_SYS_NIOS_FIXEDBAUD */

void serial_putc (char c)
{
	if (c == '\n')
		serial_putc ('\r');
	while ((readl (&uart->status) & NIOS_UART_TRDY) == 0)
		WATCHDOG_RESET ();
	writel ((unsigned char)c, &uart->txdata);
}

void serial_puts (const char *s)
{
	while (*s != 0) {
		serial_putc (*s++);
	}
}

int serial_tstc (void)
{
	return (readl (&uart->status) & NIOS_UART_RRDY);
}

int serial_getc (void)
{
	while (serial_tstc () == 0)
		WATCHDOG_RESET ();
	return (readl (&uart->rxdata) & 0x00ff );
}
