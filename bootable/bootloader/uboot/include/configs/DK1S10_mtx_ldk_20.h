

#ifndef __CONFIG_DK1S10_MTX_LDK_20_H
#define __CONFIG_DK1S10_MTX_LDK_20_H


/* CPU core */
#define	CONFIG_SYS_NIOS_CPU_CLK	75000000	/* NIOS CPU clock	*/
#define	CONFIG_SYS_NIOS_CPU_ICACHE	(0)		/* instruction cache	*/
#define	CONFIG_SYS_NIOS_CPU_DCACHE	(0)		/* data cache		*/
#define	CONFIG_SYS_NIOS_CPU_REG_NUMS	512		/* number of register	*/
#define	CONFIG_SYS_NIOS_CPU_MUL	0		/* 16x16 MUL:	no(0)	*/
						/*		yes(1)	*/
#define	CONFIG_SYS_NIOS_CPU_MSTEP	1		/* 16x16 MSTEP:	no(0)	*/
						/*		yes(1)	*/
#define	CONFIG_SYS_NIOS_CPU_STACK	0x02000000	/* stack top	addr	*/
#define	CONFIG_SYS_NIOS_CPU_VEC_BASE	0x01000000	/* IRQ vectors	addr	*/
#define	CONFIG_SYS_NIOS_CPU_VEC_SIZE	256		/*		size	*/
#define	CONFIG_SYS_NIOS_CPU_VEC_NUMS	64		/*		numbers	*/
#define	CONFIG_SYS_NIOS_CPU_RST_VECT	0x00000000	/* RESET vector	addr	*/
#define	CONFIG_SYS_NIOS_CPU_DBG_CORE	0		/* CPU debug:	no(0)	*/
						/*		yes(1)	*/

#define	CONFIG_SYS_NIOS_CPU_EXES_OFFS	0x0C

/* on-chip extensions */
#undef	CONFIG_SYS_NIOS_CPU_RAM_BASE			/* on chip RAM	addr	*/
#undef	CONFIG_SYS_NIOS_CPU_RAM_SIZE			/* 64 KB	size	*/

#define	CONFIG_SYS_NIOS_CPU_ROM_BASE	0x00000000	/* on chip ROM	addr	*/
#define	CONFIG_SYS_NIOS_CPU_ROM_SIZE	(2 * 1024)	/*  2 KB	size	*/

#undef	CONFIG_SYS_NIOS_CPU_OCI_BASE			/* OCI core	addr	*/
#undef	CONFIG_SYS_NIOS_CPU_OCI_SIZE			/*		size	*/

/* timer */
#define	CONFIG_SYS_NIOS_CPU_TIMER_NUMS	1		/* number of timer	*/

#define	CONFIG_SYS_NIOS_CPU_TIMER0	0x00000840	/* TIMER0	addr	*/
#define	CONFIG_SYS_NIOS_CPU_TIMER0_IRQ	16		/*		IRQ	*/
#define	CONFIG_SYS_NIOS_CPU_TIMER0_PER	1000		/*  periode	usec	*/
#define	CONFIG_SYS_NIOS_CPU_TIMER0_AR	0		/*  always run:	no(0)	*/
						/*		yes(1)	*/
#define	CONFIG_SYS_NIOS_CPU_TIMER0_FP	0		/*  fixed per:	no(0)	*/
						/*		yes(1)	*/
#define	CONFIG_SYS_NIOS_CPU_TIMER0_SS	1		/*  snaphot:	no(0)	*/
						/*		yes(1)	*/

/* serial i/o */
#define	CONFIG_SYS_NIOS_CPU_UART_NUMS	2		/* number of uarts	*/

#define	CONFIG_SYS_NIOS_CPU_UART0	0x00000800	/* UART0	addr	*/
#define	CONFIG_SYS_NIOS_CPU_UART0_IRQ	17		/*		IRQ	*/
#define	CONFIG_SYS_NIOS_CPU_UART0_BR	115200		/*  baudrate	var(0)	*/
#define	CONFIG_SYS_NIOS_CPU_UART0_DB	8		/*  data bit		*/
#define	CONFIG_SYS_NIOS_CPU_UART0_SB	2		/*  stop bit		*/
#define	CONFIG_SYS_NIOS_CPU_UART0_PA	0		/*  parity	none(0)	*/
						/*		odd(1)	*/
						/*		even(2)	*/
#define	CONFIG_SYS_NIOS_CPU_UART0_HS	0		/*  handshake:	no(0)	*/
						/*		crts(1)	*/
#define	CONFIG_SYS_NIOS_CPU_UART0_EOP	0		/*  eop reg:	no(0)	*/
						/*		yes(1)	*/

#define	CONFIG_SYS_NIOS_CPU_UART1	0x000008a0	/* UART1	addr	*/
#define	CONFIG_SYS_NIOS_CPU_UART1_IRQ	18		/*		IRQ	*/
#define	CONFIG_SYS_NIOS_CPU_UART1_BR	115200		/*  baudrate	var(0)	*/
#define	CONFIG_SYS_NIOS_CPU_UART1_DB	8		/*  data bit		*/
#define	CONFIG_SYS_NIOS_CPU_UART1_SB	1		/*  stop bit		*/
#define	CONFIG_SYS_NIOS_CPU_UART1_PA	0		/*  parity	none(0)	*/
						/*		odd(1)	*/
						/*		even(2)	*/
#define	CONFIG_SYS_NIOS_CPU_UART1_HS	0		/*  handshake:	no(0)	*/
						/*		crts(1)	*/
#define	CONFIG_SYS_NIOS_CPU_UART1_EOP	0		/*  eop reg:	no(0)	*/
						/*		yes(1)	*/

/* parallel i/o */
#define	CONFIG_SYS_NIOS_CPU_PIO_NUMS	2		/* number of parports	*/

#define	CONFIG_SYS_NIOS_CPU_PIO0	0x00000860	/* PIO0		addr	*/
#undef	CONFIG_SYS_NIOS_CPU_PIO0_IRQ			/*		w/o IRQ	*/
#define	CONFIG_SYS_NIOS_CPU_PIO0_BITS	1		/*  number  of  bits	*/
#define	CONFIG_SYS_NIOS_CPU_PIO0_TYPE	1		/*  io type:	tris(0)	*/
						/*		out(1)	*/
						/*		in(2)	*/
#define	CONFIG_SYS_NIOS_CPU_PIO0_CAP	0		/*  capture:	no(0)	*/
						/*		yes(1)	*/
#define	CONFIG_SYS_NIOS_CPU_PIO0_EDGE	0		/*  edge type:	none(0)	*/
						/*		fall(1)	*/
						/*		rise(2)	*/
						/*		any(3)	*/
#define	CONFIG_SYS_NIOS_CPU_PIO0_ITYPE	0		/*  IRQ type:	none(0)	*/
						/*		level(1)*/
						/*		edge(2)	*/

#define	CONFIG_SYS_NIOS_CPU_PIO1	0x00000870	/* PIO1		addr	*/
#undef	CONFIG_SYS_NIOS_CPU_PIO1_IRQ			/*		w/o IRQ	*/
#define	CONFIG_SYS_NIOS_CPU_PIO1_BITS	4		/*  number  of  bits	*/
#define	CONFIG_SYS_NIOS_CPU_PIO1_TYPE	2		/*  io type:	tris(0)	*/
						/*		out(1)	*/
						/*		in(2)	*/
#define	CONFIG_SYS_NIOS_CPU_PIO1_CAP	0		/*  capture:	no(0)	*/
						/*		yes(1)	*/
#define	CONFIG_SYS_NIOS_CPU_PIO1_EDGE	0		/*  edge type:	none(0)	*/
						/*		fall(1)	*/
						/*		rise(2)	*/
						/*		any(3)	*/
#define	CONFIG_SYS_NIOS_CPU_PIO1_ITYPE	0		/*  IRQ type:	none(0)	*/
						/*		level(1)*/
						/*		edge(2)	*/

/* IDE i/f */
#define	CONFIG_SYS_NIOS_CPU_IDE_NUMS	1		/* number of IDE contr.	*/
#define	CONFIG_SYS_NIOS_CPU_IDE0	0x00000900	/* IDE0		addr	*/
#define	CONFIG_SYS_NIOS_CPU_IDE0_IRQ	25		/*		IRQ	*/

/* memory accessibility */
#undef	CONFIG_SYS_NIOS_CPU_SRAM_BASE			/* board SRAM	addr	*/
#undef	CONFIG_SYS_NIOS_CPU_SRAM_SIZE			/*  1 MB	size	*/

#define	CONFIG_SYS_NIOS_CPU_SDRAM_BASE	0x01000000	/* board SDRAM	addr	*/
#define	CONFIG_SYS_NIOS_CPU_SDRAM_SIZE	(16*1024*1024)	/* 16 MB	size	*/

#define	CONFIG_SYS_NIOS_CPU_FLASH_BASE	0x00800000	/* board Flash	addr	*/
#define	CONFIG_SYS_NIOS_CPU_FLASH_SIZE	(8*1024*1024)	/*  8 MB	size	*/

/* LAN */
#define	CONFIG_SYS_NIOS_CPU_LAN_NUMS	1		/* number of LAN i/f	*/

#define	CONFIG_SYS_NIOS_CPU_LAN0_BASE	0x00010000	/* LAN0		addr	*/
#define	CONFIG_SYS_NIOS_CPU_LAN0_OFFS	0x0300		/*		offset	*/
#define	CONFIG_SYS_NIOS_CPU_LAN0_IRQ	20		/*		IRQ	*/
#define	CONFIG_SYS_NIOS_CPU_LAN0_BUSW	32		/*	        buswidth*/
#define	CONFIG_SYS_NIOS_CPU_LAN0_TYPE	0		/*	smc91111(0)	*/
						/*	cs8900(1)	*/
						/* ex:	openmac(2)	*/
						/* ex:	alteramac(3)	*/

/* symbolic redefinition (undef, if not present) */
#define	CONFIG_SYS_NIOS_CPU_TICK_TIMER		0	/* TIMER0: tick (needed)*/
#undef	CONFIG_SYS_NIOS_CPU_USER_TIMER			/* TIMERx: users choice	*/

#define	CONFIG_SYS_NIOS_CPU_CFPOWER_PIO	0	/* PIO0: CF power/sw.	*/
#define	CONFIG_SYS_NIOS_CPU_BUTTON_PIO		1	/* PIO1: buttons	*/
#undef	CONFIG_SYS_NIOS_CPU_LCD_PIO			/* PIOx: ASCII LCD	*/
#undef	CONFIG_SYS_NIOS_CPU_LED_PIO			/* PIOx: LED bar	*/
#undef	CONFIG_SYS_NIOS_CPU_SEVENSEG_PIO		/* PIOx: 7-seg. display	*/
#undef	CONFIG_SYS_NIOS_CPU_RECONF_PIO			/* PIOx: reconf pin	*/
#undef	CONFIG_SYS_NIOS_CPU_CFPRESENT_PIO		/* PIOx: CF present IRQ	*/
#undef	CONFIG_SYS_NIOS_CPU_CFATASEL_PIO		/* PIOx: CF ATA select	*/

#endif	/* __CONFIG_DK1S10_MTX_LDK_20_H */
