


#ifndef __CONFIG_H
#define __CONFIG_H


#define CONFIG_MPC860		1	/* This is an MPC860 CPU	*/
#define CONFIG_COGENT		1	/* using Cogent Modular Architecture */

#define	CONFIG_MISC_INIT_F	1	/* Use misc_init_f()		*/
#define	CONFIG_MISC_INIT_R		/* Use misc_init_r()		*/

/* Cogent Modular Architecture options */
#define CONFIG_CMA286_60_OLD	1	/* ...on an old CMA286-60 CPU module */
#define CONFIG_CMA102		1	/* ...on a CMA102 motherboard	*/
#define CONFIG_CMA302		1	/* ...with a CMA302 flash I/O module */

/* serial console configuration */
#undef	CONFIG_8xx_CONS_SMC1
#undef	CONFIG_8xx_CONS_SMC2
#define CONFIG_8xx_CONS_NONE	/* not on 8xx serial ports (eg on cogent m/b) */

#if defined(CONFIG_CMA286_60_OLD)
#define CONFIG_8xx_GCLK_FREQ	33333000 /* define if cant use get_gclk_freq */
#endif

#define CONFIG_BAUDRATE		230400

#define CONFIG_HARD_I2C		/* I2C with hardware support */
#define CONFIG_SYS_I2C_SPEED		400000  /* I2C speed and slave address */
#define CONFIG_SYS_I2C_SLAVE		0x7F


#define CONFIG_BOOTP_BOOTFILESIZE
#define CONFIG_BOOTP_BOOTPATH
#define CONFIG_BOOTP_GATEWAY
#define CONFIG_BOOTP_HOSTNAME


#include <config_cmd_default.h>

#define CONFIG_CMD_KGDB
#define CONFIG_CMD_I2C

#undef CONFIG_CMD_NET


#if 0
#define CONFIG_BOOTDELAY	-1	/* autoboot disabled		*/
#else
#define CONFIG_BOOTDELAY	5	/* autoboot after 5 seconds	*/
#endif
#define CONFIG_BOOTCOMMAND	"bootm 04080000 04200000" /* autoboot command*/

#define CONFIG_BOOTARGS		"root=/dev/ram rw"

#if defined(CONFIG_CMD_KGDB)
#undef	CONFIG_KGDB_ON_SMC		/* define if kgdb on SMC */
#undef	CONFIG_KGDB_ON_SCC		/* define if kgdb on SCC */
#define	CONFIG_KGDB_NONE		/* define if kgdb on something else */
#define CONFIG_KGDB_INDEX	2	/* which SMC/SCC channel for kgdb */
#define CONFIG_KGDB_BAUDRATE	230400	/* speed to run kgdb serial port */
#endif

#define CONFIG_WATCHDOG			/* turn on platform specific watchdog */

#define	CONFIG_SYS_LONGHELP			/* undef to save memory		*/
#define	CONFIG_SYS_PROMPT	"=> "		/* Monitor Command Prompt	*/
#if defined(CONFIG_CMD_KGDB)
#define	CONFIG_SYS_CBSIZE	1024		/* Console I/O Buffer Size	*/
#else
#define	CONFIG_SYS_CBSIZE	256		/* Console I/O Buffer Size	*/
#endif
#define	CONFIG_SYS_PBSIZE (CONFIG_SYS_CBSIZE+sizeof(CONFIG_SYS_PROMPT)+16) /* Print Buffer Size */
#define	CONFIG_SYS_MAXARGS	16		/* max number of command args	*/
#define CONFIG_SYS_BARGSIZE	CONFIG_SYS_CBSIZE	/* Boot Argument Buffer Size	*/

#define CONFIG_SYS_MEMTEST_START	0x00400000	/* memtest works on	*/
#define CONFIG_SYS_MEMTEST_END		0x01c00000	/* 4 ... 28 MB in DRAM	*/

#define	CONFIG_SYS_LOAD_ADDR		0x100000	/* default load address	*/

#define	CONFIG_SYS_HZ		1000		/* decrementer freq: 1 ms ticks	*/

#define CONFIG_SYS_BAUDRATE_TABLE	{ 9600, 19200, 38400, 57600, 115200, 230400 }

#define CONFIG_SYS_ALLOC_DPRAM


#define CONFIG_SYS_CMA_MB_BASE		0x00000000	/* base of m/b address space */

#include <configs/cogent_common.h>

#define CONFIG_SYS_CMA_CONS_SERIAL	/* use Cogent motherboard serial for console */
#define CONFIG_CONS_INDEX	1
#define CONFIG_SYS_CMA_LCD_HEARTBEAT	/* define for sec rotator in lcd corner */
#define CONFIG_SHOW_ACTIVITY
#if (CMA_MB_CAPS & CMA_MB_CAP_FLASH)
#define CMA_MB_FLASH_EXEC_BASE	CMA_MB_FLLOW_EXEC_BASE
#define CMA_MB_FLASH_EXEC_SIZE	CMA_MB_FLLOW_EXEC_SIZE
#define CMA_MB_FLASH_RDWR_BASE	CMA_MB_FLLOW_RDWR_BASE
#define CMA_MB_FLASH_RDWR_SIZE	CMA_MB_FLLOW_RDWR_SIZE
#endif
#define CMA_MB_FLASH_BASE	CMA_MB_FLASH_EXEC_BASE
#define CMA_MB_FLASH_SIZE	CMA_MB_FLASH_EXEC_SIZE

#define CONFIG_SYS_IMMR		0xFF000000

#define CONFIG_SYS_INIT_RAM_ADDR	CONFIG_SYS_IMMR
#define	CONFIG_SYS_INIT_RAM_END	0x2F00	/* End of used area in DPRAM	*/
#define	CONFIG_SYS_GBL_DATA_SIZE	64  /* size in bytes reserved for initial data */
#define CONFIG_SYS_GBL_DATA_OFFSET	(CONFIG_SYS_INIT_RAM_END - CONFIG_SYS_GBL_DATA_SIZE)
#define	CONFIG_SYS_INIT_SP_OFFSET	CONFIG_SYS_GBL_DATA_OFFSET

#define	CONFIG_SYS_SDRAM_BASE		CMA_MB_RAM_BASE
#ifdef CONFIG_CMA302
#define CONFIG_SYS_FLASH_BASE		CMA_MB_SLOT2_BASE	/* cma302 in slot 2 */
#else
#define CONFIG_SYS_FLASH_BASE		CMA_MB_FLASH_BASE	/* flash on m/b */
#endif
#define	CONFIG_SYS_MONITOR_BASE	TEXT_BASE
#define	CONFIG_SYS_MONITOR_LEN		(128 << 10)	/* Reserve 128 kB for Monitor	*/
#define	CONFIG_SYS_MALLOC_LEN		(128 << 10)	/* Reserve 128 kB for malloc()	*/

#define	CONFIG_SYS_BOOTMAPSZ		(8 << 20)	/* Initial Memory map for Linux	*/
#define CONFIG_SYS_MAX_FLASH_BANKS	2	/* max number of memory banks		*/
#define CONFIG_SYS_MAX_FLASH_SECT	67	/* max number of sectors on one chip	*/

#define CONFIG_SYS_FLASH_ERASE_TOUT	120000	/* Timeout for Flash Erase (in ms)	*/
#define CONFIG_SYS_FLASH_WRITE_TOUT	500	/* Timeout for Flash Write (in ms)	*/

#define	CONFIG_ENV_IS_IN_FLASH	1
#define CONFIG_ENV_ADDR		CONFIG_SYS_FLASH_BASE /* Addr of Environment Sector */
#ifdef CONFIG_CMA302
#define	CONFIG_ENV_SIZE		0x1000	/* Total Size of Environment Sector	*/
#define CONFIG_ENV_SECT_SIZE	(512*1024) /* see README - env sect real size */
#else
#define	CONFIG_ENV_SIZE		0x4000	/* Total Size of Environment Sector	*/
#endif
#define CONFIG_SYS_CACHELINE_SIZE	16	/* For all MPC8xx CPUs			*/
#if defined(CONFIG_CMD_KGDB)
#define CONFIG_SYS_CACHELINE_SHIFT	4	/* log base 2 of the above value	*/
#endif


#if defined(CONFIG_WATCHDOG)
#define CONFIG_SYS_SYPCR	(SYPCR_SWTC | SYPCR_BMT | SYPCR_BME | SYPCR_SWF | \
			 SYPCR_SWE  | SYPCR_SWRI| SYPCR_SWP)
#else
#define CONFIG_SYS_SYPCR	(SYPCR_SWTC | SYPCR_BMT | SYPCR_BME | SYPCR_SWF | SYPCR_SWP)
#endif	/* CONFIG_WATCHDOG */

#define CONFIG_SYS_SIUMCR	(SIUMCR_DBGC00 | SIUMCR_DBPC00 | SIUMCR_MLRC01)

#define CONFIG_SYS_TBSCR	(TBSCR_REFA | TBSCR_REFB | TBSCR_TBF)

#define CONFIG_SYS_PISCR	(PISCR_PS | PISCR_PITF)

#define CONFIG_SYS_PLPRCR	(PLPRCR_SPLSS | PLPRCR_TEXPS | PLPRCR_TMIST)

#define SCCR_MASK	SCCR_EBDF11
#define CONFIG_SYS_SCCR	(SCCR_TBS     | SCCR_RTDIV    | SCCR_RTSEL    | \
			 SCCR_COM00   | SCCR_DFSYNC00 | SCCR_DFBRG00  | \
			 SCCR_DFNL000 | SCCR_DFNH000  | SCCR_DFLCD000 | \
			 SCCR_DFALCD00)

#define CONFIG_SYS_PCMCIA_MEM_ADDR	(0xE0000000)
#define CONFIG_SYS_PCMCIA_MEM_SIZE	( 64 << 20 )
#define CONFIG_SYS_PCMCIA_DMA_ADDR	(0xE4000000)
#define CONFIG_SYS_PCMCIA_DMA_SIZE	( 64 << 20 )
#define CONFIG_SYS_PCMCIA_ATTRB_ADDR	(0xE8000000)
#define CONFIG_SYS_PCMCIA_ATTRB_SIZE	( 64 << 20 )
#define CONFIG_SYS_PCMCIA_IO_ADDR	(0xEC000000)
#define CONFIG_SYS_PCMCIA_IO_SIZE	( 64 << 20 )

/*#define	CONFIG_SYS_DER	0x2002000F*/
#define CONFIG_SYS_DER	0

#if defined(CONFIG_CMA286_60_OLD)


#define CONFIG_SYS_CMA_CS0_BASE	TEXT_BASE		/* EPROM */
#define CONFIG_SYS_CMA_CS0_SIZE	(1 << 20)
#define CONFIG_SYS_CMA_CS1_BASE	CMA_MB_RAM_BASE		/* RAM + I/O SLOT 1 */
#define CONFIG_SYS_CMA_CS1_SIZE	(64 << 20)
#define CONFIG_SYS_CMA_CS2_BASE	CMA_MB_SLOT2_BASE	/* I/O SLOTS 2 + 3 */
#define CONFIG_SYS_CMA_CS2_SIZE	(64 << 20)
#define CONFIG_SYS_CMA_CS3_BASE	CMA_MB_ROMLOW_BASE	/* M/B I/O */
#define CONFIG_SYS_CMA_CS3_SIZE	(32 << 20)


/* base address = CONFIG_SYS_CMA_CS0_BASE, 16-bit, no parity, r/o, gpcm */
#define CONFIG_SYS_BR0_PRELIM	((CONFIG_SYS_CMA_CS0_BASE&BR_BA_MSK)|BR_PS_16|BR_WP|BR_V)
/* mask size CONFIG_SYS_CMA_CS0_SIZE, CS time normal, burst inhibit, 4-wait states */
#define CONFIG_SYS_OR0_PRELIM	((~(CONFIG_SYS_CMA_CS0_SIZE-1)&OR_AM_MSK)|OR_BI|OR_SCY_4_CLK)


/* base address = CONFIG_SYS_CMA_CS1_BASE, 32-bit, no parity, r/w, gpcm */
#define CONFIG_SYS_BR1_PRELIM	((CONFIG_SYS_CMA_CS1_BASE&BR_BA_MSK)|BR_V)
/* mask size CONFIG_SYS_CMA_CS1_SIZE, CS time normal, burst ok, ext xfer ack */
#define CONFIG_SYS_OR1_PRELIM	((~(CONFIG_SYS_CMA_CS1_SIZE-1)&OR_AM_MSK)|OR_SETA)


/* base address = CONFIG_SYS_CMA_CS2_BASE, 32-bit, no parity, r/w, gpcm */
#define CONFIG_SYS_BR2_PRELIM	((CONFIG_SYS_CMA_CS2_BASE&BR_BA_MSK)|BR_V)
/* mask size CONFIG_SYS_CMA_CS2_SIZE, CS time normal, burst ok, ext xfer ack */
#define CONFIG_SYS_OR2_PRELIM	((~(CONFIG_SYS_CMA_CS2_SIZE-1)&OR_AM_MSK)|OR_SETA)


/* base address = CONFIG_SYS_CMA_CS3_BASE, 32-bit, no parity, r/w, gpcm */
#define CONFIG_SYS_BR3_PRELIM	((CONFIG_SYS_CMA_CS3_BASE&BR_BA_MSK)|BR_V)
/* mask size CONFIG_SYS_CMA_CS3_SIZE, CS time normal, burst inhibit, ext xfer ack */
#define CONFIG_SYS_OR3_PRELIM	((~(CONFIG_SYS_CMA_CS3_SIZE-1)&OR_AM_MSK)|OR_BI|OR_SETA)

#endif

#define	BOOTFLAG_COLD	0x01		/* Normal Power-On: Boot from FLASH	*/
#define BOOTFLAG_WARM	0x02		/* Software reboot			*/

#endif	/* __CONFIG_H */
