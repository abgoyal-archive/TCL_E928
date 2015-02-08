

#include <common.h>

#include "ns9750_bbus.h"	/* for GPIOs */
#include "ns9750_ser.h"		/* for serial configuration */

DECLARE_GLOBAL_DATA_PTR;

#if !defined(CONFIG_CONS_INDEX)
#error "No console index specified."
#endif

#define CONSOLE CONFIG_CONS_INDEX

static unsigned int calcBitrateRegister( void );
static unsigned int calcRxCharGapRegister( void );

static char cCharsAvailable; /* Numbers of chars in unCharCache */
static unsigned int unCharCache; /* unCharCache is only valid if
				  * cCharsAvailable > 0 */


int serial_init( void )
{
	unsigned int aunGPIOTxD[] = { 0, 8, 40, 44 };
	unsigned int aunGPIORxD[] = { 1, 9, 41, 45 };

	cCharsAvailable = 0;

	/* configure TxD and RxD pins for their special function */
	set_gpio_cfg_reg_val( aunGPIOTxD[ CONSOLE ],
			      NS9750_GPIO_CFG_FUNC_0 | NS9750_GPIO_CFG_OUTPUT );
	set_gpio_cfg_reg_val( aunGPIORxD[ CONSOLE ],
			      NS9750_GPIO_CFG_FUNC_0 | NS9750_GPIO_CFG_INPUT );

	/* configure serial engine */
	*get_ser_reg_addr_channel( NS9750_SER_CTRL_A, CONSOLE ) =
		NS9750_SER_CTRL_A_CE |
		NS9750_SER_CTRL_A_STOP |
		NS9750_SER_CTRL_A_WLS_8;

	serial_setbrg();

	*get_ser_reg_addr_channel( NS9750_SER_CTRL_B, CONSOLE ) =
		NS9750_SER_CTRL_B_RCGT;

	return 0;
}


void serial_putc( const char c )
{
	if (c == '\n')
		serial_putc( '\r' );

	while (!(*get_ser_reg_addr_channel( NS9750_SER_STAT_A, CONSOLE) &
		 NS9750_SER_STAT_A_TRDY ) ) {
		/* do nothing, wait for characters in FIFO sent */
	}

	*(volatile char*) get_ser_reg_addr_channel( NS9750_SER_FIFO,
						    CONSOLE) = c;
}


void serial_puts( const char *s )
{
	while (*s) {
		serial_putc( *s++ );
	}
}


int serial_getc( void )
{
	int i;

	while (!serial_tstc() ) {
		/* do nothing, wait for incoming characters */
	}

	/*  at least one character in unCharCache */
	i = (int) (unCharCache & 0xff);

	unCharCache >>= 8;
	cCharsAvailable--;

	return i;
}


int serial_tstc( void )
{
	unsigned int unRegCache;

	if ( cCharsAvailable )
		return 1;

	unRegCache = *get_ser_reg_addr_channel( NS9750_SER_STAT_A,CONSOLE );
	if( unRegCache & NS9750_SER_STAT_A_RBC ) {
		*get_ser_reg_addr_channel( NS9750_SER_STAT_A, CONSOLE ) =
			NS9750_SER_STAT_A_RBC;
		unRegCache = *get_ser_reg_addr_channel( NS9750_SER_STAT_A,
							CONSOLE );
	}

	if ( unRegCache & NS9750_SER_STAT_A_RRDY ) {
		cCharsAvailable = (unRegCache & NS9750_SER_STAT_A_RXFDB_MA)>>20;
		if ( !cCharsAvailable )
			cCharsAvailable = 4;

		unCharCache = *get_ser_reg_addr_channel( NS9750_SER_FIFO,
							 CONSOLE );
		return 1;
	}

	/* no chars available */
	return 0;
}

void serial_setbrg( void )
{
	*get_ser_reg_addr_channel( NS9750_SER_BITRATE, CONSOLE ) =
		calcBitrateRegister();
	*get_ser_reg_addr_channel( NS9750_SER_RX_CHAR_TIMER, CONSOLE ) =
		calcRxCharGapRegister();
}


static unsigned int calcBitrateRegister( void )
{
	return ( NS9750_SER_BITRATE_EBIT |
		 NS9750_SER_BITRATE_CLKMUX_BCLK |
		 NS9750_SER_BITRATE_TMODE |
		 NS9750_SER_BITRATE_TCDR_16 |
		 NS9750_SER_BITRATE_RCDR_16 |
		 ( ( ( ( CONFIG_SYS_CLK_FREQ / 8 ) / /* BBUS clock,[1] Fig. 38 */
		       ( gd->baudrate * 16 ) ) - 1 ) &
		   NS9750_SER_BITRATE_N_MA ) );
}


static unsigned int calcRxCharGapRegister( void )
{
	return NS9750_SER_RX_CHAR_TIMER_TRUN;
}
