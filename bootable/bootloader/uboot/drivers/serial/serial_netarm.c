

#include <common.h>
#include <asm/hardware.h>

DECLARE_GLOBAL_DATA_PTR;

#define PORTA	(*(volatile unsigned int *)(NETARM_GEN_MODULE_BASE + NETARM_GEN_PORTA))
#if !defined(CONFIG_NETARM_NS7520)
#define PORTB	(*(volatile unsigned int *)(NETARM_GEN_MODULE_BASE + NETARM_GEN_PORTB))
#else
#define PORTC	(*(volatile unsigned int *)(NETARM_GEN_MODULE_BASE + NETARM_GEN_PORTC))
#endif

/* wait until transmitter is ready for another character */
#define TXWAITRDY(registers)							\
{										\
	ulong tmo = get_timer(0) + 1 * CONFIG_SYS_HZ;					\
	while (((registers)->status_a & NETARM_SER_STATA_TX_RDY) == 0 )	{	\
		if (get_timer(0) > tmo)						\
			break;							\
	}									\
}


#ifndef CONFIG_UART1_CONSOLE
volatile netarm_serial_channel_t *serial_reg_ch1 = get_serial_channel(0);
volatile netarm_serial_channel_t *serial_reg_ch2 = get_serial_channel(1);
#else
volatile netarm_serial_channel_t *serial_reg_ch1 = get_serial_channel(1);
volatile netarm_serial_channel_t *serial_reg_ch2 = get_serial_channel(0);
#endif

extern void _netarm_led_FAIL1(void);

void serial_setbrg (void)
{
	/* set 0 ... make sure pins are configured for serial */
#if !defined(CONFIG_NETARM_NS7520)
	PORTA = PORTB =
		NETARM_GEN_PORT_MODE (0xef) | NETARM_GEN_PORT_DIR (0xe0);
#else
	PORTA = NETARM_GEN_PORT_MODE (0xef) | NETARM_GEN_PORT_DIR (0xe0);
	PORTC = NETARM_GEN_PORT_CSF (0xef) | NETARM_GEN_PORT_MODE (0xef) | NETARM_GEN_PORT_DIR (0xe0);
#endif

	/* first turn em off */
	serial_reg_ch1->ctrl_a = serial_reg_ch2->ctrl_a = 0;

	/* clear match register, we don't need it */
	serial_reg_ch1->rx_match = serial_reg_ch2->rx_match = 0;

	/* setup bit rate generator and rx buffer gap timer (1 byte only) */
	if ((gd->baudrate >= MIN_BAUD_RATE)
	    && (gd->baudrate <= MAX_BAUD_RATE)) {
		serial_reg_ch1->bitrate = serial_reg_ch2->bitrate =
			NETARM_SER_BR_X16 (gd->baudrate);
		serial_reg_ch1->rx_buf_timer = serial_reg_ch2->rx_buf_timer =
			0;
		serial_reg_ch1->rx_char_timer = serial_reg_ch2->rx_char_timer =
			NETARM_SER_RXGAP (gd->baudrate);
	} else {
		hang ();
	}

	/* setup port mode */
	serial_reg_ch1->ctrl_b = serial_reg_ch2->ctrl_b =
		( NETARM_SER_CTLB_RCGT_EN |
		  NETARM_SER_CTLB_UART_MODE);
	serial_reg_ch1->ctrl_a = serial_reg_ch2->ctrl_a =
		( NETARM_SER_CTLA_ENABLE |
		  NETARM_SER_CTLA_P_NONE |
		  /* see errata */
		  NETARM_SER_CTLA_2STOP |
		  NETARM_SER_CTLA_8BITS |
		  NETARM_SER_CTLA_DTR_EN |
		  NETARM_SER_CTLA_RTS_EN);
}


int serial_init (void)
{
	serial_setbrg ();
	return 0;
}


void serial_putc (const char c)
{
	volatile unsigned char *fifo;

	/* If \n, also do \r */
	if (c == '\n')
		serial_putc ('\r');

	fifo = (volatile unsigned char *) &(serial_reg_ch1->fifo);
	TXWAITRDY (serial_reg_ch1);
	*fifo = c;
}

int serial_tstc(void)
{
	return serial_reg_ch1->status_a & NETARM_SER_STATA_RX_RDY;
}

int serial_getc (void)
{
	unsigned int ch_uint;
	volatile unsigned int *fifo;
	volatile unsigned char *fifo_char = NULL;
	int buf_count = 0;

	while (!(serial_reg_ch1->status_a & NETARM_SER_STATA_RX_RDY))
		/* NOP */ ;

	fifo = (volatile unsigned int *) &(serial_reg_ch1->fifo);
	fifo_char = (unsigned char *) &ch_uint;
	ch_uint = *fifo;

	buf_count = NETARM_SER_STATA_RXFDB (serial_reg_ch1->status_a);
	switch (buf_count) {
	case NETARM_SER_STATA_RXFDB_4BYTES:
		buf_count = 4;
		break;
	case NETARM_SER_STATA_RXFDB_3BYTES:
		buf_count = 3;
		break;
	case NETARM_SER_STATA_RXFDB_2BYTES:
		buf_count = 2;
		break;
	case NETARM_SER_STATA_RXFDB_1BYTES:
		buf_count = 1;
		break;
	default:
		/* panic, be never here */
		break;
	}

	serial_reg_ch1->status_a |= NETARM_SER_STATA_RX_CLOSED;

	return ch_uint & 0xff;
}

void serial_puts (const char *s)
{
	while (*s) {
		serial_putc (*s++);
	}
}
