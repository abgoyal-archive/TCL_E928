

#include <common.h>
#include <netdev.h>
#include <nios-io.h>
#include <spi.h>

#if	defined(CONFIG_HW_WATCHDOG)
extern void ssv_wd_pio_init(void);	/* comes from ../common/wd_pio.c
					   included by ./misc.c */
#endif

void _default_hdlr (void)
{
	printf ("default_hdlr\n");
}

int board_early_init_f (void)
{
#if	defined(CONFIG_HW_WATCHDOG)
	ssv_wd_pio_init();
#endif
	return 0;
}

int checkboard (void)
{
	puts (	"Board: SSV DilNetPC ADNP/ESC1"
#if	defined(CONFIG_DNPEVA2)
		" on DNP/EVA2"
#endif
		"\n");
#if     defined(CONFIG_NIOS_BASE_32)
	puts ("Conf.: SSV Base 32 (nios_32)\n");
#endif

	return 0;
}

phys_size_t initdram (int board_type)
{
	return (0);
}

#if defined(CONFIG_CMD_SPI) && CONFIG_NIOS_SPI

#define	SPI_RTC_CS_MASK	0x00000001

int spi_cs_is_valid(unsigned int bus, unsigned int cs)
{
	return bus == 0 && cs == 0;
}

void spi_cs_activate(struct spi_slave *slave)
{
	nios_spi_t *spi = (nios_spi_t *)CONFIG_SYS_NIOS_SPIBASE;

	spi->slaveselect = SPI_RTC_CS_MASK;	/* activate (1) */
}

void spi_cs_deactivate(struct spi_slave *slave)
{
	nios_spi_t *spi = (nios_spi_t *)CONFIG_SYS_NIOS_SPIBASE;

	spi->slaveselect = 0;			/* deactivate (0) */
}

#endif

#ifdef CONFIG_CMD_NET
int board_eth_init(bd_t *bis)
{
	int rc = 0;
#ifdef CONFIG_CS8900
	rc = cs8900_initialize(0, CONFIG_CS8900_BASE);
#endif
	return rc;
}
#endif
