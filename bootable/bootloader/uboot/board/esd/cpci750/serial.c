


/* supports the MPSC */

#include <common.h>
#include <command.h>
#include "../../Marvell/include/memory.h"
#include "serial.h"

#include "mpsc.h"

DECLARE_GLOBAL_DATA_PTR;

int serial_init (void)
{
	mpsc_init (gd->baudrate);

	return (0);
}

void serial_putc (const char c)
{
	if (c == '\n')
		mpsc_putchar ('\r');

	mpsc_putchar (c);
}

int serial_getc (void)
{
	return mpsc_getchar ();
}

int serial_tstc (void)
{
	return mpsc_test_char ();
}

void serial_setbrg (void)
{
	galbrg_set_baudrate (CONFIG_MPSC_PORT, gd->baudrate);
}


void serial_puts (const char *s)
{
	while (*s) {
		serial_putc (*s++);
	}
}

#if defined(CONFIG_CMD_KGDB)
void kgdb_serial_init (void)
{
}

void putDebugChar (int c)
{
	serial_putc (c);
}

void putDebugStr (const char *str)
{
	serial_puts (str);
}

int getDebugChar (void)
{
	return serial_getc ();
}

void kgdb_interruptible (int yes)
{
	return;
}
#endif
