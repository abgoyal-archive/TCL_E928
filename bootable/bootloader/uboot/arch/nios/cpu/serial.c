


#include <common.h>
#include <watchdog.h>
#include <nios-io.h>

DECLARE_GLOBAL_DATA_PTR;

#if defined(CONFIG_CONSOLE_JTAG)

static nios_jtag_t *jtag = (nios_jtag_t *)CONFIG_SYS_NIOS_CONSOLE;

void serial_setbrg( void ){ return; }
int serial_init( void ) { return(0);}

void serial_putc (char c)
{
	while ((jtag->txcntl & NIOS_JTAG_TRDY) != 0)
		WATCHDOG_RESET ();
	jtag->txcntl = NIOS_JTAG_TRDY | (unsigned char)c;
}

void serial_puts (const char *s)
{
	while (*s != 0)
		serial_putc (*s++);
}

int serial_tstc (void)
{
	return (jtag->rxcntl & NIOS_JTAG_RRDY);
}

int serial_getc (void)
{
	int c;
	while (serial_tstc() == 0)
		WATCHDOG_RESET ();
	c = jtag->rxcntl & 0x0ff;
	jtag->rxcntl = 0;
	return (c);
}

#else

static nios_uart_t *uart = (nios_uart_t *)CONFIG_SYS_NIOS_CONSOLE;

#if defined(CONFIG_SYS_NIOS_FIXEDBAUD)

void serial_setbrg (void){ return; }
int serial_init (void) { return (0);}

#else

void serial_setbrg (void)
{
	unsigned div;

	div = (CONFIG_SYS_CLK_FREQ/gd->baudrate)-1;
	uart->divisor = div;
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
	while ((uart->status & NIOS_UART_TRDY) == 0)
		WATCHDOG_RESET ();
	uart->txdata = (unsigned char)c;
}

void serial_puts (const char *s)
{
	while (*s != 0) {
		serial_putc (*s++);
	}
}

int serial_tstc (void)
{
	return (uart->status & NIOS_UART_RRDY);
}

int serial_getc (void)
{
	while (serial_tstc () == 0)
		WATCHDOG_RESET ();
	return( uart->rxdata & 0x00ff );
}

#endif /* CONFIG_JTAG_CONSOLE */
