

#include <common.h>

#include <asm/hardware.h>
#include "s3c4510b_uart.h"

DECLARE_GLOBAL_DATA_PTR;

static UART    *uart;

static int serial_flush_input(void)
{
	volatile u32 tmp;

	/* keep on reading as long as the receiver is not empty */
	while( uart->m_stat.bf.rxReady) {
		tmp = uart->m_rx;
	}

	return 0;
}


static int serial_flush_output(void)
{
	/* wait until the transmitter is no longer busy */
	while( !uart->m_stat.bf.txBufEmpty);

	return 0;
}


void serial_setbrg (void)
{
	UART_LINE_CTRL ulctrl;
	UART_CTRL      uctrl;
	UART_BAUD_DIV  ubd;

	serial_flush_output();
	serial_flush_input();

	/* control register */
	uctrl.ui = 0x0;
	uctrl.bf.rxMode = 0x1;
	uctrl.bf.rxIrq = 0x0;
	uctrl.bf.txMode = 0x1;
	uctrl.bf.DSR = 0x0;
	uctrl.bf.sendBreak = 0x0;
	uctrl.bf.loopBack = 0x0;
	uart->m_ctrl.ui = uctrl.ui;

	/* line control register */
	ulctrl.ui  = 0x0;
	ulctrl.bf.wordLen   = 0x3; /* 8 bit data */
	ulctrl.bf.nStop     = 0x0; /* 1 stop bit */
	ulctrl.bf.parity    = 0x0; /* no parity */
	ulctrl.bf.clk       = 0x0; /* internal clock */
	ulctrl.bf.infra_red = 0x0; /* no infra_red */
	uart->m_lineCtrl.ui = ulctrl.ui;

	ubd.ui = 0x0;

	/* see table on page 10-15 in SAMSUNG S3C4510B manual */
	/* get correct divisor */
	switch(gd->baudrate) {
	case   1200:	ubd.bf.cnt0 = 1301;	break;
	case   2400:	ubd.bf.cnt0 =  650;	break;
	case   4800:	ubd.bf.cnt0 =  324;	break;
	case   9600:	ubd.bf.cnt0 =  162;	break;
	case  19200:	ubd.bf.cnt0 =   80;	break;
	case  38400:	ubd.bf.cnt0 =   40;	break;
	case  57600:	ubd.bf.cnt0 =   26;	break;
	case 115200:	ubd.bf.cnt0 =   13;	break;
	}

	uart->m_baudDiv.ui = ubd.ui;
	uart->m_baudCnt = 0x0;
	uart->m_baudClk = 0x0;

}


int serial_init (void)
{

#if   CONFIG_SERIAL1 == 1
	uart = (UART *)UART0_BASE;
#elif CONFIG_SERIAL1 == 2
	uart = (UART *)UART1_BASE;
#else
#error CONFIG_SERIAL1 not equal to 1 or 2
#endif

	serial_setbrg ();

	return (0);
}


void serial_putc (const char c)
{
	/* wait for room in the transmit FIFO */
	while( !uart->m_stat.bf.txBufEmpty);

	uart->m_tx = c;

	/*
		to be polite with serial console add a line feed
		to the carriage return character
	*/
	if (c=='\n')
		serial_putc('\r');
}

int serial_tstc (void)
{
	return uart->m_stat.bf.rxReady;
}

int serial_getc (void)
{
	int rv;

	for(;;) {
		rv = serial_tstc();

		if (rv) {
			return uart->m_rx & 0xFF;
		}
	}
}

void serial_puts (const char *s)
{
	while (*s) {
		serial_putc (*s++);
	}

	/* busy wait for tx complete */
	while ( !uart->m_stat.bf.txComplete);

	/* clear break */
	uart->m_ctrl.bf.sendBreak = 0;

}
