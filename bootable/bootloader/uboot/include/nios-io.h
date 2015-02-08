


#ifndef __NIOSIO_H__
#define __NIOSIO_H__

typedef volatile struct nios_uart_t {
	unsigned	rxdata;		/* Rx data reg */
	unsigned	txdata;		/* Tx data reg */
	unsigned	status;		/* Status reg */
	unsigned	control;	/* Control reg */
	unsigned	divisor;	/* Baud rate divisor reg */
	unsigned	endofpacket;	/* End-of-packet reg */
}nios_uart_t;

/* status register */
#define NIOS_UART_PE		(1 << 0)	/* parity error */
#define NIOS_UART_FE		(1 << 1)	/* frame error */
#define NIOS_UART_BRK		(1 << 2)	/* break detect */
#define NIOS_UART_ROE		(1 << 3)	/* rx overrun */
#define NIOS_UART_TOE		(1 << 4)	/* tx overrun */
#define NIOS_UART_TMT		(1 << 5)	/* tx empty */
#define NIOS_UART_TRDY		(1 << 6)	/* tx ready */
#define NIOS_UART_RRDY		(1 << 7)	/* rx ready */
#define NIOS_UART_E		(1 << 8)	/* exception */
#define NIOS_UART_DCTS		(1 << 10)	/* cts change */
#define NIOS_UART_CTS		(1 << 11)	/* cts */
#define NIOS_UART_EOP		(1 << 12)	/* eop detected */

/* control register */
#define NIOS_UART_IPE		(1 << 0)	/* parity error int ena*/
#define NIOS_UART_IFE		(1 << 1)	/* frame error int ena */
#define NIOS_UART_IBRK		(1 << 2)	/* break detect int ena */
#define NIOS_UART_IROE		(1 << 3)	/* rx overrun int ena */
#define NIOS_UART_ITOE		(1 << 4)	/* tx overrun int ena */
#define NIOS_UART_ITMT		(1 << 5)	/* tx empty int ena */
#define NIOS_UART_ITRDY		(1 << 6)	/* tx ready int ena */
#define NIOS_UART_IRRDY		(1 << 7)	/* rx ready int ena */
#define NIOS_UART_IE		(1 << 8)	/* exception int ena */
#define NIOS_UART_TBRK		(1 << 9)	/* transmit break */
#define NIOS_UART_IDCTS		(1 << 10)	/* cts change int ena */
#define NIOS_UART_RTS		(1 << 11)	/* rts */
#define NIOS_UART_IEOP		(1 << 12)	/* eop detected int ena */


typedef volatile struct nios_timer_t {
	unsigned	status;			/* Timer status reg */
	unsigned	control;		/* Timer control reg */
	unsigned	periodl;		/* Timeout period low */
	unsigned	periodh;		/* Timeout period high */
	unsigned	snapl;			/* Snapshot low */
	unsigned	snaph;			/* Snapshot high */
}nios_timer_t;

/* status register */
#define NIOS_TIMER_TO		(1 << 0)	/* Timeout */
#define NIOS_TIMER_RUN		(1 << 1)	/* Timer running */

/* control register */
#define NIOS_TIMER_ITO		(1 << 0)	/* Timeout int ena */
#define NIOS_TIMER_CONT		(1 << 1)	/* Continuous mode */
#define NIOS_TIMER_START	(1 << 2)	/* Start timer */
#define NIOS_TIMER_STOP		(1 << 3)	/* Stop timer */


typedef volatile struct nios_pio_t {
	unsigned int	data;		/* Data value at each PIO in/out */
	unsigned int	direction;	/* Data direct. for each PIO bit */
	unsigned int	interruptmask;	/* Per-bit IRQ enable/disable */
	unsigned int	edgecapture;	/* Per-bit sync. edge detect & hold */
}nios_pio_t;

/* direction register */
#define NIOS_PIO_OUT		(1)		/* PIO bit is output */
#define NIOS_PIO_IN		(0)		/* PIO bit is input */


typedef volatile struct nios_spi_t {
	unsigned	rxdata;		/* Rx data reg */
	unsigned	txdata;		/* Tx data reg */
	unsigned	status;		/* Status reg */
	unsigned	control;	/* Control reg */
	unsigned	reserved;	/* (master only) */
	unsigned	slaveselect;	/* SPI slave select mask (master only) */
}nios_spi_t;

/* status register */
#define NIOS_SPI_ROE		(1 << 3)	/* rx overrun */
#define NIOS_SPI_TOE		(1 << 4)	/* tx overrun */
#define NIOS_SPI_TMT		(1 << 5)	/* tx empty */
#define NIOS_SPI_TRDY		(1 << 6)	/* tx ready */
#define NIOS_SPI_RRDY		(1 << 7)	/* rx ready */
#define NIOS_SPI_E		(1 << 8)	/* exception */

/* control register */
#define NIOS_SPI_IROE		(1 << 3)	/* rx overrun int ena */
#define NIOS_SPI_ITOE		(1 << 4)	/* tx overrun int ena */
#define NIOS_SPI_ITRDY		(1 << 6)	/* tx ready int ena */
#define NIOS_SPI_IRRDY		(1 << 7)	/* rx ready int ena */
#define NIOS_SPI_IE		(1 << 8)	/* exception int ena */
#define NIOS_SPI_SSO		(1 << 10)	/* override SS_n output */

typedef volatile struct nios_asmi_t {
	unsigned	rxdata;		/* Rx data reg */
	unsigned	txdata;		/* Tx data reg */
	unsigned	status;		/* Status reg */
	unsigned	control;	/* Control reg */
	unsigned	reserved;
	unsigned	slavesel;	/* Slave select */
	unsigned	endofpacket;	/* End-of-packet reg */
}nios_asmi_t;

/* status register */
#define NIOS_ASMI_ROE		(1 << 3)	/* rx overrun */
#define NIOS_ASMI_TOE		(1 << 4)	/* tx overrun */
#define NIOS_ASMI_TMT		(1 << 5)	/* tx empty */
#define NIOS_ASMI_TRDY		(1 << 6)	/* tx ready */
#define NIOS_ASMI_RRDY		(1 << 7)	/* rx ready */
#define NIOS_ASMI_E		(1 << 8)	/* exception */
#define NIOS_ASMI_EOP		(1 << 9)	/* eop detected */

/* control register */
#define NIOS_ASMI_IROE		(1 << 3)	/* rx overrun int ena */
#define NIOS_ASMI_ITOE		(1 << 4)	/* tx overrun int ena */
#define NIOS_ASMI_ITRDY		(1 << 6)	/* tx ready int ena */
#define NIOS_ASMI_IRRDY		(1 << 7)	/* rx ready int ena */
#define NIOS_ASMI_IE		(1 << 8)	/* exception int ena */
#define NIOS_ASMI_IEOP		(1 << 9)	/* rx eop int ena */
#define NIOS_ASMI_SSO		(1 << 10)	/* slave select enable */

typedef volatile struct nios_jtag_t {
	unsigned short	rxcntl;			/* Rx data/cntl reg */
	unsigned short	txcntl;			/* Tx data/cntl reg */
	unsigned short	errcntl;		/* Err dta/cntl reg */
}nios_jtag_t;

/* status register */
#define NIOS_JTAG_TRDY		(1 << 8)	/* tx ready bit */
#define NIOS_JTAG_RRDY		(1 << 8)	/* rx ready bit */

#endif /* __NIOSIO_H__ */
