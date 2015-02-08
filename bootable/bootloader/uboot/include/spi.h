

#ifndef _SPI_H_
#define _SPI_H_

/* Controller-specific definitions: */

/* CONFIG_HARD_SPI triggers SPI bus initialization in PowerPC */
#ifdef CONFIG_MPC8XXX_SPI
# ifndef CONFIG_HARD_SPI
#  define CONFIG_HARD_SPI
# endif
#endif

/* SPI mode flags */
#define	SPI_CPHA	0x01			/* clock phase */
#define	SPI_CPOL	0x02			/* clock polarity */
#define	SPI_MODE_0	(0|0)			/* (original MicroWire) */
#define	SPI_MODE_1	(0|SPI_CPHA)
#define	SPI_MODE_2	(SPI_CPOL|0)
#define	SPI_MODE_3	(SPI_CPOL|SPI_CPHA)
#define	SPI_CS_HIGH	0x04			/* CS active high */
#define	SPI_LSB_FIRST	0x08			/* per-word bits-on-wire */
#define	SPI_3WIRE	0x10			/* SI/SO signals shared */
#define	SPI_LOOP	0x20			/* loopback mode */

/* SPI transfer flags */
#define SPI_XFER_BEGIN	0x01			/* Assert CS before transfer */
#define SPI_XFER_END	0x02			/* Deassert CS after transfer */

struct spi_slave {
	unsigned int	bus;
	unsigned int	cs;
};

void spi_init(void);

struct spi_slave *spi_setup_slave(unsigned int bus, unsigned int cs,
		unsigned int max_hz, unsigned int mode);

void spi_free_slave(struct spi_slave *slave);

int spi_claim_bus(struct spi_slave *slave);

void spi_release_bus(struct spi_slave *slave);

int  spi_xfer(struct spi_slave *slave, unsigned int bitlen, const void *dout,
		void *din, unsigned long flags);

int  spi_cs_is_valid(unsigned int bus, unsigned int cs);

void spi_cs_activate(struct spi_slave *slave);

void spi_cs_deactivate(struct spi_slave *slave);

static inline int spi_w8r8(struct spi_slave *slave, unsigned char byte)
{
	unsigned char dout[2];
	unsigned char din[2];
	int ret;

	dout[0] = byte;
	dout[1] = 0;

	ret = spi_xfer(slave, 16, dout, din, SPI_XFER_BEGIN | SPI_XFER_END);
	return ret < 0 ? ret : din[1];
}

#endif	/* _SPI_H_ */
