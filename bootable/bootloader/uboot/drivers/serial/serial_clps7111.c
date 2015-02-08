

#include <common.h>
#include <clps7111.h>

DECLARE_GLOBAL_DATA_PTR;

void serial_setbrg (void)
{
	unsigned int reg = 0;

	switch (gd->baudrate) {
	case   1200:	reg = 191;	break;
	case   9600:	reg =  23;	break;
	case  19200:	reg =  11;	break;
	case  38400:	reg =   5;	break;
	case  57600:	reg =   3;	break;
	case 115200:	reg =   1;	break;
	default:	hang ();	break;
	}

	/* init serial serial 1,2 */
	IO_SYSCON1 = SYSCON1_UART1EN;
	IO_SYSCON2 = SYSCON2_UART2EN;

	reg |= UBRLCR_WRDLEN8;

	IO_UBRLCR1 = reg;
	IO_UBRLCR2 = reg;
}


int serial_init (void)
{
	serial_setbrg ();

	return (0);
}


void serial_putc (const char c)
{
	int tmo;

	/* If \n, also do \r */
	if (c == '\n')
		serial_putc ('\r');

	tmo = get_timer (0) + 1 * CONFIG_SYS_HZ;
	while (IO_SYSFLG1 & SYSFLG1_UTXFF)
		if (get_timer (0) > tmo)
			break;

	IO_UARTDR1 = c;
}

int serial_tstc (void)
{
	return !(IO_SYSFLG1 & SYSFLG1_URXFE);
}

int serial_getc (void)
{
	while (IO_SYSFLG1 & SYSFLG1_URXFE);

	return IO_UARTDR1 & 0xff;
}

void
serial_puts (const char *s)
{
	while (*s) {
		serial_putc (*s++);
	}
}
