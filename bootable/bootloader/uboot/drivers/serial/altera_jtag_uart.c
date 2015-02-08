

#include <common.h>
#include <watchdog.h>
#include <asm/io.h>
#include <nios2-io.h>

DECLARE_GLOBAL_DATA_PTR;

static nios_jtag_t *jtag = (nios_jtag_t *)CONFIG_SYS_NIOS_CONSOLE;

void serial_setbrg( void ){ return; }
int serial_init( void ) { return(0);}

void serial_putc (char c)
{
	while (1) {
		unsigned st = readl(&jtag->control);
		if (NIOS_JTAG_WSPACE(st))
			break;
#ifdef CONFIG_ALTERA_JTAG_UART_BYPASS
		if (!(st & NIOS_JTAG_AC)) /* no connection */
			return;
#endif
		WATCHDOG_RESET();
	}
	writel ((unsigned char)c, &jtag->data);
}

void serial_puts (const char *s)
{
	while (*s != 0)
		serial_putc (*s++);
}

int serial_tstc (void)
{
	return ( readl (&jtag->control) & NIOS_JTAG_RRDY);
}

int serial_getc (void)
{
	int c;
	unsigned val;

	while (1) {
		WATCHDOG_RESET ();
		val = readl (&jtag->data);
		if (val & NIOS_JTAG_RVALID)
			break;
	}
	c = val & 0x0ff;
	return (c);
}
