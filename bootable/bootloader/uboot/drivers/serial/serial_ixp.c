

#include <common.h>
#include <asm/arch/ixp425.h>

#define SERIAL_CLOCK 921600

DECLARE_GLOBAL_DATA_PTR;

void serial_setbrg (void)
{
	unsigned int quot = 0;
	int uart = CONFIG_SYS_IXP425_CONSOLE;

	if ((gd->baudrate <= SERIAL_CLOCK) && (SERIAL_CLOCK % gd->baudrate == 0))
		quot = SERIAL_CLOCK / gd->baudrate;
	else
		hang ();

	IER(uart) = 0;					/* Disable for now */
	FCR(uart) = 0;					/* No fifos enabled */

	/* set baud rate */
	LCR(uart) = LCR_WLS0 | LCR_WLS1 | LCR_DLAB;
	DLL(uart) = quot & 0xff;
	DLH(uart) = quot >> 8;
	LCR(uart) = LCR_WLS0 | LCR_WLS1;
#ifdef CONFIG_SERIAL_RTS_ACTIVE
	MCR(uart) = MCR_RTS;				/* set RTS active */
#else
	MCR(uart) = 0;					/* set RTS inactive */
#endif
	IER(uart) = IER_UUE;
}

int serial_init (void)
{
	serial_setbrg ();

	return (0);
}


void serial_putc (const char c)
{
	/* wait for room in the tx FIFO on UART */
	while ((LSR(CONFIG_SYS_IXP425_CONSOLE) & LSR_TEMT) == 0);

	THR(CONFIG_SYS_IXP425_CONSOLE) = c;

	/* If \n, also do \r */
	if (c == '\n')
		serial_putc ('\r');
}

int serial_tstc (void)
{
	return LSR(CONFIG_SYS_IXP425_CONSOLE) & LSR_DR;
}

int serial_getc (void)
{
	while (!(LSR(CONFIG_SYS_IXP425_CONSOLE) & LSR_DR));

	return (char) RBR(CONFIG_SYS_IXP425_CONSOLE) & 0xff;
}

void
serial_puts (const char *s)
{
	while (*s) {
		serial_putc (*s++);
	}
}
