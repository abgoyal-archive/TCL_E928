

#include <common.h>
#include <asm/hardware.h>

DECLARE_GLOBAL_DATA_PTR;

static int serial_flush_input(void)
{
	volatile u32 tmp;

	/* keep on reading as long as the receiver is not empty */
	while(UTRSTAT0&0x01) {
		tmp = REGB(URXH0);
	}

	return 0;
}


static int serial_flush_output(void)
{
	/* wait until the transmitter is no longer busy */
	while(!(UTRSTAT0 & 0x02)) {
	}

	return 0;
}


void serial_setbrg (void)
{
	u32 divisor = 0;

	/* get correct divisor */
	switch(gd->baudrate) {

	case 1200:
#if CONFIG_S3C44B0_CLOCK_SPEED==66
		divisor = 3124;
#elif CONFIG_S3C44B0_CLOCK_SPEED==75
		divisor = 3905;
#else
# error CONFIG_S3C44B0_CLOCK_SPEED undefined
#endif
		break;

	case 9600:
#if CONFIG_S3C44B0_CLOCK_SPEED==66
		divisor = 390;
#elif CONFIG_S3C44B0_CLOCK_SPEED==75
		divisor = 487;
#else
# error CONFIG_S3C44B0_CLOCK_SPEED undefined
#endif
		break;

	case 19200:
#if CONFIG_S3C44B0_CLOCK_SPEED==66
		divisor = 194;
#elif CONFIG_S3C44B0_CLOCK_SPEED==75
		divisor = 243;
#else
# error CONFIG_S3C44B0_CLOCK_SPEED undefined
#endif
		break;

	case 38400:
#if CONFIG_S3C44B0_CLOCK_SPEED==66
		divisor = 97;
#elif CONFIG_S3C44B0_CLOCK_SPEED==75
		divisor = 121;
#else
# error CONFIG_S3C44B0_CLOCK_SPEED undefined
#endif	/* break; */

	case 57600:
#if CONFIG_S3C44B0_CLOCK_SPEED==66
		divisor = 64;
#elif CONFIG_S3C44B0_CLOCK_SPEED==75
		divisor = 80;
#else
# error CONFIG_S3C44B0_CLOCK_SPEED undefined
#endif	/* break; */

	case 115200:
#if CONFIG_S3C44B0_CLOCK_SPEED==66
		divisor = 32;
#elif CONFIG_S3C44B0_CLOCK_SPEED==75
		divisor = 40;
#else
# error CONFIG_S3C44B0_CLOCK_SPEED undefined
#endif	/* break; */
	}

	serial_flush_output();
	serial_flush_input();
	UFCON0 = 0x0;
	ULCON0 = 0x03;
	UCON0 = 0x05;
	UBRDIV0 = divisor;

	UFCON1 = 0x0;
	ULCON1 = 0x03;
	UCON1 = 0x05;
	UBRDIV1 = divisor;

	for(divisor=0; divisor<100; divisor++) {
		/* NOP */
	}
}


int serial_init (void)
{
	serial_setbrg ();

	return (0);
}


void serial_putc (const char c)
{
	/* wait for room in the transmit FIFO */
	while(!(UTRSTAT0 & 0x02));

	UTXH0 = (unsigned char)c;

	/*
		to be polite with serial console add a line feed
		to the carriage return character
	*/
	if (c=='\n')
		serial_putc('\r');
}

int serial_tstc (void)
{
	return (UTRSTAT0 & 0x01);
}

int serial_getc (void)
{
	int rv;

	for(;;) {
		rv = serial_tstc();

		if(rv > 0)
			return URXH0;
	}
}

void
serial_puts (const char *s)
{
	while (*s) {
		serial_putc (*s++);
	}
}
