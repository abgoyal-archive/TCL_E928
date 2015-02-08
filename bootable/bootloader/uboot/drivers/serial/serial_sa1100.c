

#include <common.h>
#include <SA-1100.h>

DECLARE_GLOBAL_DATA_PTR;

void serial_setbrg (void)
{
	unsigned int reg = 0;

	if (gd->baudrate == 1200)
		reg = 191;
	else if (gd->baudrate == 9600)
		reg = 23;
	else if (gd->baudrate == 19200)
		reg = 11;
	else if (gd->baudrate == 38400)
		reg = 5;
	else if (gd->baudrate == 57600)
		reg = 3;
	else if (gd->baudrate == 115200)
		reg = 1;
	else
		hang ();

#ifdef CONFIG_SERIAL1
	/* SA1110 uart function */
	Ser1SDCR0 |= SDCR0_SUS;

	/* Wait until port is ready ... */
	while(Ser1UTSR1 & UTSR1_TBY) {}

	/* init serial serial 1 */
	Ser1UTCR3 = 0x00;
	Ser1UTSR0 = 0xff;
	Ser1UTCR0 = ( UTCR0_1StpBit | UTCR0_8BitData );
	Ser1UTCR1 = 0;
	Ser1UTCR2 = (u32)reg;
	Ser1UTCR3 = ( UTCR3_RXE | UTCR3_TXE );
#elif defined(CONFIG_SERIAL3)
	/* Wait until port is ready ... */
	while (Ser3UTSR1 & UTSR1_TBY) {
	}

	/* init serial serial 3 */
	Ser3UTCR3 = 0x00;
	Ser3UTSR0 = 0xff;
	Ser3UTCR0 = (UTCR0_1StpBit | UTCR0_8BitData);
	Ser3UTCR1 = 0;
	Ser3UTCR2 = (u32) reg;
	Ser3UTCR3 = (UTCR3_RXE | UTCR3_TXE);
#else
#error "Bad: you didn't configured serial ..."
#endif
}


int serial_init (void)
{
	serial_setbrg ();

	return (0);
}


void serial_putc (const char c)
{
#ifdef CONFIG_SERIAL1
	/* wait for room in the tx FIFO on SERIAL1 */
	while ((Ser1UTSR0 & UTSR0_TFS) == 0);

	Ser1UTDR = c;
#elif defined(CONFIG_SERIAL3)
	/* wait for room in the tx FIFO on SERIAL3 */
	while ((Ser3UTSR0 & UTSR0_TFS) == 0);

	Ser3UTDR = c;
#endif

	/* If \n, also do \r */
	if (c == '\n')
		serial_putc ('\r');
}

int serial_tstc (void)
{
#ifdef CONFIG_SERIAL1
	return Ser1UTSR1 & UTSR1_RNE;
#elif defined(CONFIG_SERIAL3)
	return Ser3UTSR1 & UTSR1_RNE;
#endif
}

int serial_getc (void)
{
#ifdef CONFIG_SERIAL1
	while (!(Ser1UTSR1 & UTSR1_RNE));

	return (char) Ser1UTDR & 0xff;
#elif defined(CONFIG_SERIAL3)
	while (!(Ser3UTSR1 & UTSR1_RNE));

	return (char) Ser3UTDR & 0xff;
#endif
}

void
serial_puts (const char *s)
{
	while (*s) {
		serial_putc (*s++);
	}
}
