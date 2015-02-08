

#include <common.h>

#include <asm/arch/s3c6400.h>

#ifdef CONFIG_SERIAL1
#define UART_NR	S3C64XX_UART0

#elif defined(CONFIG_SERIAL2)
#define UART_NR	S3C64XX_UART1

#elif defined(CONFIG_SERIAL3)
#define UART_NR	S3C64XX_UART2

#else
#error "Bad: you didn't configure serial ..."
#endif

#define barrier() asm volatile("" ::: "memory")

static const int udivslot[] = {
	0,
	0x0080,
	0x0808,
	0x0888,
	0x2222,
	0x4924,
	0x4a52,
	0x54aa,
	0x5555,
	0xd555,
	0xd5d5,
	0xddd5,
	0xdddd,
	0xdfdd,
	0xdfdf,
	0xffdf,
};

void serial_setbrg(void)
{
	DECLARE_GLOBAL_DATA_PTR;
	s3c64xx_uart *const uart = s3c64xx_get_base_uart(UART_NR);
	u32 pclk = get_PCLK();
	u32 baudrate = gd->baudrate;
	int i;

	i = (pclk / baudrate) % 16;

	uart->UBRDIV = pclk / baudrate / 16 - 1;
	uart->UDIVSLOT = udivslot[i];

	for (i = 0; i < 100; i++)
		barrier();
}

int serial_init(void)
{
	s3c64xx_uart *const uart = s3c64xx_get_base_uart(UART_NR);

	/* reset and enable FIFOs, set triggers to the maximum */
	uart->UFCON = 0xff;
	uart->UMCON = 0;
	/* 8N1 */
	uart->ULCON = 3;
	/* No interrupts, no DMA, pure polling */
	uart->UCON = 5;

	serial_setbrg();

	return 0;
}

int serial_getc(void)
{
	s3c64xx_uart *const uart = s3c64xx_get_base_uart(UART_NR);

	/* wait for character to arrive */
	while (!(uart->UTRSTAT & 0x1));

	return uart->URXH & 0xff;
}

#ifdef CONFIG_MODEM_SUPPORT
static int be_quiet;
void disable_putc(void)
{
	be_quiet = 1;
}

void enable_putc(void)
{
	be_quiet = 0;
}
#endif


void serial_putc(const char c)
{
	s3c64xx_uart *const uart = s3c64xx_get_base_uart(UART_NR);

#ifdef CONFIG_MODEM_SUPPORT
	if (be_quiet)
		return;
#endif

	/* wait for room in the tx FIFO */
	while (!(uart->UTRSTAT & 0x2));

	uart->UTXH = c;

	/* If \n, also do \r */
	if (c == '\n')
		serial_putc('\r');
}

int serial_tstc(void)
{
	s3c64xx_uart *const uart = s3c64xx_get_base_uart(UART_NR);

	return uart->UTRSTAT & 0x1;
}

void serial_puts(const char *s)
{
	while (*s)
		serial_putc(*s++);
}
