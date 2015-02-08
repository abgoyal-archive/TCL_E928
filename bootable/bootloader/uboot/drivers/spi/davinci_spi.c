
#include <common.h>
#include <spi.h>
#include <malloc.h>
#include <asm/io.h>
#include <asm/arch/hardware.h>
#include "davinci_spi.h"

void spi_init()
{
	/* do nothing */
}

struct spi_slave *spi_setup_slave(unsigned int bus, unsigned int cs,
			unsigned int max_hz, unsigned int mode)
{
	struct davinci_spi_slave	*ds;

	if (!spi_cs_is_valid(bus, cs))
		return NULL;

	ds = malloc(sizeof(*ds));
	if (!ds)
		return NULL;

	ds->slave.bus = bus;
	ds->slave.cs = cs;
	ds->regs = (struct davinci_spi_regs *)CONFIG_SYS_SPI_BASE;
	ds->freq = max_hz;

	return &ds->slave;
}

void spi_free_slave(struct spi_slave *slave)
{
	struct davinci_spi_slave *ds = to_davinci_spi(slave);

	free(ds);
}

int spi_claim_bus(struct spi_slave *slave)
{
	struct davinci_spi_slave *ds = to_davinci_spi(slave);
	unsigned int scalar, data1_reg_val = 0;

	/* Enable the SPI hardware */
	writel(SPIGCR0_SPIRST_MASK, &ds->regs->gcr0);
	udelay(1000);
	writel(SPIGCR0_SPIENA_MASK, &ds->regs->gcr0);

	/* Set master mode, powered up and not activated */
	writel(SPIGCR1_MASTER_MASK | SPIGCR1_CLKMOD_MASK, &ds->regs->gcr1);

	/* CS, CLK, SIMO and SOMI are functional pins */
	writel((SPIPC0_EN0FUN_MASK | SPIPC0_CLKFUN_MASK |
		SPIPC0_DOFUN_MASK | SPIPC0_DIFUN_MASK), &ds->regs->pc0);

	/* setup format */
	scalar = ((CONFIG_SYS_SPI_CLK / ds->freq) - 1) & 0xFF;

	/*
	 * Use following format:
	 *   character length = 8,
	 *   clock signal delayed by half clk cycle,
	 *   clock low in idle state - Mode 0,
	 *   MSB shifted out first
	 */
	writel(8 | (scalar << SPIFMT_PRESCALE_SHIFT) |
		(1 << SPIFMT_PHASE_SHIFT), &ds->regs->fmt0);

	/* hold cs active at end of transfer until explicitly de-asserted */
	data1_reg_val = (1 << SPIDAT1_CSHOLD_SHIFT) |
			(slave->cs << SPIDAT1_CSNR_SHIFT);
	writel(data1_reg_val, &ds->regs->dat1);

	/*
	 * Including a minor delay. No science here. Should be good even with
	 * no delay
	 */
	writel((50 << SPI_C2TDELAY_SHIFT) |
		(50 << SPI_T2CDELAY_SHIFT), &ds->regs->delay);

	/* default chip select register */
	writel(SPIDEF_CSDEF0_MASK, &ds->regs->def);

	/* no interrupts */
	writel(0, &ds->regs->int0);
	writel(0, &ds->regs->lvl);

	/* enable SPI */
	writel((readl(&ds->regs->gcr1) | SPIGCR1_SPIENA_MASK), &ds->regs->gcr1);

	return 0;
}

void spi_release_bus(struct spi_slave *slave)
{
	struct davinci_spi_slave *ds = to_davinci_spi(slave);

	/* Disable the SPI hardware */
	writel(SPIGCR0_SPIRST_MASK, &ds->regs->gcr0);
}

int spi_xfer(struct spi_slave *slave, unsigned int bitlen,
		const void *dout, void *din, unsigned long flags)
{
	struct davinci_spi_slave *ds = to_davinci_spi(slave);
	unsigned int	len, data1_reg_val = readl(&ds->regs->dat1);
	int		ret, i;
	const u8	*txp = dout; /* dout can be NULL for read operation */
	u8		*rxp = din;  /* din can be NULL for write operation */

	ret = 0;

	if (bitlen == 0)
		/* Finish any previously submitted transfers */
		goto out;

	/*
	 * It's not clear how non-8-bit-aligned transfers are supposed to be
	 * represented as a stream of bytes...this is a limitation of
	 * the current SPI interface - here we terminate on receiving such a
	 * transfer request.
	 */
	if (bitlen % 8) {
		/* Errors always terminate an ongoing transfer */
		flags |= SPI_XFER_END;
		goto out;
	}

	len = bitlen / 8;

	/* do an empty read to clear the current contents */
	readl(&ds->regs->buf);

	/* keep writing and reading 1 byte until done */
	for (i = 0; i < len; i++) {
		/* wait till TXFULL is asserted */
		while (readl(&ds->regs->buf) & SPIBUF_TXFULL_MASK);

		/* write the data */
		data1_reg_val &= ~0xFFFF;
		if (txp) {
			data1_reg_val |= *txp;
			txp++;
		}

		/*
		 * Write to DAT1 is required to keep the serial transfer going.
		 * We just terminate when we reach the end.
		 */
		if ((i == (len - 1)) && (flags & SPI_XFER_END)) {
			/* clear CS hold */
			writel(data1_reg_val &
				~(1 << SPIDAT1_CSHOLD_SHIFT), &ds->regs->dat1);
		} else {
			/* enable CS hold */
			data1_reg_val |= ((1 << SPIDAT1_CSHOLD_SHIFT) |
					(slave->cs << SPIDAT1_CSNR_SHIFT));
			writel(data1_reg_val, &ds->regs->dat1);
		}

		/* read the data - wait for data availability */
		while (readl(&ds->regs->buf) & SPIBUF_RXEMPTY_MASK);

		if (rxp) {
			*rxp = readl(&ds->regs->buf) & 0xFF;
			rxp++;
		} else {
			/* simply drop the read character */
			readl(&ds->regs->buf);
		}
	}
	return 0;

out:
	if (flags & SPI_XFER_END) {
		writel(data1_reg_val &
			~(1 << SPIDAT1_CSHOLD_SHIFT), &ds->regs->dat1);
	}
	return 0;
}

int spi_cs_is_valid(unsigned int bus, unsigned int cs)
{
	return bus == 0 && cs == 0;
}

void spi_cs_activate(struct spi_slave *slave)
{
	/* do nothing */
}

void spi_cs_deactivate(struct spi_slave *slave)
{
	/* do nothing */
}
