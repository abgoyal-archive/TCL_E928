

#include <config.h>
#include <asm/io.h>

#define RX_FIFO_OFFSET		0 /* receive FIFO, read only */
#define TX_FIFO_OFFSET		4 /* transmit FIFO, write only */
#define STATUS_REG_OFFSET	8 /* status register, read only */

#define SR_TX_FIFO_FULL		0x08 /* transmit FIFO full */
#define SR_RX_FIFO_VALID_DATA	0x01 /* data in receive FIFO */
#define SR_RX_FIFO_FULL		0x02 /* receive FIFO full */

#define UARTLITE_STATUS		(CONFIG_SERIAL_BASE + STATUS_REG_OFFSET)
#define UARTLITE_TX_FIFO	(CONFIG_SERIAL_BASE + TX_FIFO_OFFSET)
#define UARTLITE_RX_FIFO	(CONFIG_SERIAL_BASE + RX_FIFO_OFFSET)

int serial_init(void)
{
	/* FIXME: Nothing for now. We should initialize fifo, etc */
	return 0;
}

void serial_setbrg(void)
{
	/* FIXME: what's this for? */
}

void serial_putc(const char c)
{
	if (c == '\n')
		serial_putc('\r');
	while (in_be32((u32 *) UARTLITE_STATUS) & SR_TX_FIFO_FULL);
	out_be32((u32 *) UARTLITE_TX_FIFO, (unsigned char) (c & 0xff));
}

void serial_puts(const char * s)
{
	while (*s) {
		serial_putc(*s++);
	}
}

int serial_getc(void)
{
	while (!(in_be32((u32 *) UARTLITE_STATUS) & SR_RX_FIFO_VALID_DATA));
	return in_be32((u32 *) UARTLITE_RX_FIFO) & 0xff;
}

int serial_tstc(void)
{
	return (in_be32((u32 *) UARTLITE_STATUS) & SR_RX_FIFO_VALID_DATA);
}
