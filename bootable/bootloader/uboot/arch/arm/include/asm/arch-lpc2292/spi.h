

#ifndef SPI_H
#define SPI_H

#include <config.h>
#include <common.h>
#include <asm/errno.h>
#include <asm/arch/hardware.h>

#define SPIF 0x80

#define spi_lock() disable_interrupts();
#define spi_unlock() enable_interrupts();

extern unsigned long spi_flags;
extern unsigned char spi_idle;

int spi_init(void);

static inline unsigned char spi_read(void)
{
	unsigned char b;

	PUT8(S0SPDR, spi_idle);
	while (!(GET8(S0SPSR) & SPIF));
	b = GET8(S0SPDR);

	return b;
}

static inline void spi_write(unsigned char b)
{
	PUT8(S0SPDR, b);
	while (!(GET8(S0SPSR) & SPIF));
	GET8(S0SPDR);		/* this will clear the SPIF bit */
}

static inline void spi_set_clock(unsigned char clk_value)
{
	PUT8(S0SPCCR, clk_value);
}

static inline void spi_set_cfg(unsigned char phase,
			       unsigned char polarity,
			       unsigned char lsbf)
{
	unsigned char v = 0x20;	/* master bit set */

	if (phase)
		v |= 0x08;			/* set phase bit */
	if (polarity) {
		v |= 0x10;			/* set polarity bit */
		spi_idle = 0xFF;
	} else {
		spi_idle = 0x00;
	}
	if (lsbf)
		v |= 0x40;			/* set lsbf bit */

	PUT8(S0SPCR, v);
}
#endif /* SPI_H */
