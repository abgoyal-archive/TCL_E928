

#include <common.h>
#include "ns16550.h"

DECLARE_GLOBAL_DATA_PTR;

#if CONFIG_CONS_INDEX == 1
static struct NS16550 *console =
		(struct NS16550 *) (CONFIG_SYS_EUMB_ADDR + 0x4500);
#elif CONFIG_CONS_INDEX == 2
static struct NS16550 *console =
		(struct NS16550 *) (CONFIG_SYS_EUMB_ADDR + 0x4500);
#else
#error no valid console defined
#endif

extern ulong get_bus_freq (ulong);

int serial_init (void)
{
	int clock_divisor = gd->bus_clk / 16 / gd->baudrate;

	NS16550_init (CONFIG_CONS_INDEX - 1, clock_divisor);

	return (0);
}

void serial_putc (const char c)
{
	if (c == '\n') {
		serial_putc ('\r');
	}
	NS16550_putc (console, c);
}

void serial_puts (const char *s)
{
	while (*s) {
		serial_putc (*s++);
	}
}


int serial_getc (void)
{
	return NS16550_getc (console);
}

int serial_tstc (void)
{
	return NS16550_tstc (console);
}

void serial_setbrg (void)
{
	int clock_divisor = get_bus_freq (0) / 16 / gd->baudrate;

	NS16550_reinit (console, clock_divisor);
}
