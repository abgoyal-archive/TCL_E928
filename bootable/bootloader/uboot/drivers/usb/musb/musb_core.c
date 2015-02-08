

#include <common.h>

#include "musb_core.h"
struct musb_regs *musbr;

void musb_start(void)
{
#if defined(CONFIG_MUSB_HCD)
	u8 devctl;
#endif

	/* disable all interrupts */
	writew(0, &musbr->intrtxe);
	writew(0, &musbr->intrrxe);
	writeb(0, &musbr->intrusbe);
	writeb(0, &musbr->testmode);

	/* put into basic highspeed mode and start session */
	writeb(MUSB_POWER_HSENAB, &musbr->power);
#if defined(CONFIG_MUSB_HCD)
	devctl = readb(&musbr->devctl);
	writeb(devctl | MUSB_DEVCTL_SESSION, &musbr->devctl);
#endif
}

#ifdef MUSB_NO_DYNAMIC_FIFO
# define config_fifo(dir, idx, addr)
#else
# define config_fifo(dir, idx, addr) \
	do { \
		writeb(idx, &musbr->dir##fifosz); \
		writew(fifoaddr >> 3, &musbr->dir##fifoadd); \
	} while (0)
#endif

void musb_configure_ep(struct musb_epinfo *epinfo, u8 cnt)
{
	u16 csr;
	u16 fifoaddr = 64; /* First 64 bytes of FIFO reserved for EP0 */
	u32 fifosize;
	u8  idx;

	while (cnt--) {
		/* prepare fifosize to write to register */
		fifosize = epinfo->epsize >> 3;
		idx = ffs(fifosize) - 1;

		writeb(epinfo->epnum, &musbr->index);
		if (epinfo->epdir) {
			/* Configure fifo size and fifo base address */
			config_fifo(tx, idx, fifoaddr);

			csr = readw(&musbr->txcsr);
#if defined(CONFIG_MUSB_HCD)
			/* clear the data toggle bit */
			writew(csr | MUSB_TXCSR_CLRDATATOG, &musbr->txcsr);
#endif
			/* Flush fifo if required */
			if (csr & MUSB_TXCSR_TXPKTRDY)
				writew(csr | MUSB_TXCSR_FLUSHFIFO,
					&musbr->txcsr);
		} else {
			/* Configure fifo size and fifo base address */
			config_fifo(rx, idx, fifoaddr);

			csr = readw(&musbr->rxcsr);
#if defined(CONFIG_MUSB_HCD)
			/* clear the data toggle bit */
			writew(csr | MUSB_RXCSR_CLRDATATOG, &musbr->rxcsr);
#endif
			/* Flush fifo if required */
			if (csr & MUSB_RXCSR_RXPKTRDY)
				writew(csr | MUSB_RXCSR_FLUSHFIFO,
					&musbr->rxcsr);
		}
		fifoaddr += epinfo->epsize;
		epinfo++;
	}
}

__attribute__((weak))
void write_fifo(u8 ep, u32 length, void *fifo_data)
{
	u8  *data = (u8 *)fifo_data;

	/* select the endpoint index */
	writeb(ep, &musbr->index);

	/* write the data to the fifo */
	while (length--)
		writeb(*data++, &musbr->fifox[ep]);
}

__attribute__((weak))
void read_fifo(u8 ep, u32 length, void *fifo_data)
{
	u8  *data = (u8 *)fifo_data;

	/* select the endpoint index */
	writeb(ep, &musbr->index);

	/* read the data to the fifo */
	while (length--)
		*data++ = readb(&musbr->fifox[ep]);
}
