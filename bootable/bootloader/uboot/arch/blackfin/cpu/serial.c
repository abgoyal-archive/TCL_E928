


#include <common.h>
#include <watchdog.h>
#include <asm/blackfin.h>
#include <asm/mach-common/bits/uart.h>

#ifdef CONFIG_UART_CONSOLE

#include "serial.h"

#ifdef CONFIG_DEBUG_SERIAL
uint16_t cached_lsr[256];
uint16_t cached_rbr[256];
size_t cache_count;

static uint16_t uart_lsr_save;
static uint16_t uart_lsr_read(void)
{
	uint16_t lsr = bfin_read16(&pUART->lsr);
	uart_lsr_save |= (lsr & (OE|PE|FE|BI));
	return lsr | uart_lsr_save;
}
/* Just do the clear for everyone since it can't hurt. */
static void uart_lsr_clear(void)
{
	uart_lsr_save = 0;
	bfin_write16(&pUART->lsr, bfin_read16(&pUART->lsr) | -1);
}
#else
static uint16_t uart_lsr_read(void)
{
	return bfin_read16(&pUART->lsr);
}
static void uart_lsr_clear(void)
{
	bfin_write16(&pUART->lsr, bfin_read16(&pUART->lsr) | -1);
}
#endif

/* Symbol for our assembly to call. */
void serial_set_baud(uint32_t baud)
{
	serial_early_set_baud(baud);
}

void serial_setbrg(void)
{
	DECLARE_GLOBAL_DATA_PTR;
	serial_set_baud(gd->baudrate);
}

/* Symbol for our assembly to call. */
void serial_initialize(void)
{
	serial_early_init();
}

/* Symbol for common u-boot code to call. */
int serial_init(void)
{
	serial_initialize();
	serial_setbrg();
	uart_lsr_clear();
#ifdef CONFIG_DEBUG_SERIAL
	cache_count = 0;
	memset(cached_lsr, 0x00, sizeof(cached_lsr));
	memset(cached_rbr, 0x00, sizeof(cached_rbr));
#endif
	return 0;
}

void serial_putc(const char c)
{
	/* send a \r for compatibility */
	if (c == '\n')
		serial_putc('\r');

	WATCHDOG_RESET();

	/* wait for the hardware fifo to clear up */
	while (!(uart_lsr_read() & THRE))
		continue;

	/* queue the character for transmission */
	bfin_write16(&pUART->thr, c);
	SSYNC();

	WATCHDOG_RESET();
}

int serial_tstc(void)
{
	WATCHDOG_RESET();
	return (uart_lsr_read() & DR) ? 1 : 0;
}

int serial_getc(void)
{
	uint16_t uart_rbr_val;

	/* wait for data ! */
	while (!serial_tstc())
		continue;

	/* grab the new byte */
	uart_rbr_val = bfin_read16(&pUART->rbr);

#ifdef CONFIG_DEBUG_SERIAL
	/* grab & clear the LSR */
	uint16_t uart_lsr_val = uart_lsr_read();

	cached_lsr[cache_count] = uart_lsr_val;
	cached_rbr[cache_count] = uart_rbr_val;
	cache_count = (cache_count + 1) % ARRAY_SIZE(cached_lsr);

	if (uart_lsr_val & (OE|PE|FE|BI)) {
		uint16_t dll, dlh;
		printf("\n[SERIAL ERROR]\n");
		ACCESS_LATCH();
		dll = bfin_read16(&pUART->dll);
		dlh = bfin_read16(&pUART->dlh);
		ACCESS_PORT_IER();
		printf("\tDLL=0x%x DLH=0x%x\n", dll, dlh);
		do {
			--cache_count;
			printf("\t%3i: RBR=0x%02x LSR=0x%02x\n", cache_count,
				cached_rbr[cache_count], cached_lsr[cache_count]);
		} while (cache_count > 0);
		return -1;
	}
#endif
	uart_lsr_clear();

	return uart_rbr_val;
}

void serial_puts(const char *s)
{
	while (*s)
		serial_putc(*s++);
}

#endif
