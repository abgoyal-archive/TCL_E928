


#ifndef __CONFIG_H
#define __CONFIG_H


#define CONFIG_MPC8260		1	/* This is an MPC8260 CPU   */
#define CONFIG_IPHASE4539	1	/* ...on a Interphase 4539 PMC */

#define CONFIG_CPM2		1	/* Has a CPM2 */

#define	CONFIG_CONS_ON_SMC		/* define if console on SMC */
#undef	CONFIG_CONS_ON_SCC		/* define if console on SCC */
#undef	CONFIG_CONS_NONE		/* define if console on something else */
#define CONFIG_CONS_INDEX	1	/* which serial channel for console */

#undef	CONFIG_ETHER_ON_SCC		/* define if ether on SCC   */
#define CONFIG_ETHER_ON_FCC		/* define if ether on FCC   */
#undef	CONFIG_ETHER_NONE		/* define if ether on something else */
#define CONFIG_ETHER_INDEX	3	/* which channel for ether  */

#if defined(CONFIG_ETHER_ON_FCC) && (CONFIG_ETHER_INDEX == 3)

# define CONFIG_SYS_CMXFCR_MASK	(CMXFCR_FC3 | CMXFCR_RF3CS_MSK | CMXFCR_TF3CS_MSK)
# define CONFIG_SYS_CMXFCR_VALUE	(CMXFCR_RF3CS_CLK14 | CMXFCR_TF3CS_CLK16)
# define CONFIG_SYS_CPMFCR_RAMTYPE	0
# define CONFIG_SYS_FCC_PSMR		(FCC_PSMR_FDE|FCC_PSMR_LPB)

#endif	/* CONFIG_ETHER_ON_FCC, CONFIG_ETHER_INDEX */

/* other options */

#define CONFIG_8260_CLKIN	66666666	/* in Hz */
#define CONFIG_BAUDRATE		19200

#define CONFIG_BOOTP_SUBNETMASK
#define CONFIG_BOOTP_GATEWAY
#define CONFIG_BOOTP_HOSTNAME
#define CONFIG_BOOTP_BOOTPATH
#define CONFIG_BOOTP_BOOTFILESIZE

#undef  CONFIG_HARD_I2C			/* I2C with hardware support	*/
#define CONFIG_SOFT_I2C		1	/* I2C bit-banged		*/
#define CONFIG_SYS_I2C_SPEED		400000	/* I2C speed and slave address	*/
#define CONFIG_SYS_I2C_SLAVE		0x7F

#ifdef CONFIG_SOFT_I2C
#define I2C_PORT	3		/* Port A=0, B=1, C=2, D=3 */
#define I2C_ACTIVE	(iop->pdir |=  0x00010000)
#define I2C_TRISTATE	(iop->pdir &= ~0x00010000)
#define I2C_READ	((iop->pdat & 0x00010000) != 0)
#define I2C_SDA(bit)	if(bit) iop->pdat |=  0x00010000; \
			else    iop->pdat &= ~0x00010000
#define I2C_SCL(bit)	if(bit) iop->pdat |=  0x00020000; \
			else    iop->pdat &= ~0x00020000
#define I2C_DELAY	udelay(5)	/* 1/4 I2C clock duration */
#endif /* CONFIG_SOFT_I2C */


#include <config_cmd_default.h>


#define CONFIG_BOOTDELAY	5	/* autoboot after 5 seconds */
#define CONFIG_BOOTCOMMAND	"bootm 100000"	/* autoboot command */
#define CONFIG_BOOTARGS		"root=/dev/ram rw"

#if defined(CONFIG_CMD_KGDB)
#undef	CONFIG_KGDB_ON_SMC		/* define if kgdb on SMC */
#define CONFIG_KGDB_ON_SCC		/* define if kgdb on SCC */
#undef	CONFIG_KGDB_NONE		/* define if kgdb on something else */
#define CONFIG_KGDB_INDEX	2	/* which serial channel for kgdb */
#define CONFIG_KGDB_BAUDRATE	115200	/* speed to run kgdb serial port at */
#endif

#undef	CONFIG_WATCHDOG			/* disable platform specific watchdog */

#define CONFIG_SYS_LONGHELP			/* undef to save memory		*/
#define CONFIG_SYS_PROMPT	"=> "		/* Monitor Command Prompt	*/
#if defined(CONFIG_CMD_KGDB)
#define CONFIG_SYS_CBSIZE	1024		/* Console I/O Buffer Size	*/
#else
#define CONFIG_SYS_CBSIZE	256		/* Console I/O Buffer Size	*/
#endif
#define CONFIG_SYS_PBSIZE (CONFIG_SYS_CBSIZE+sizeof(CONFIG_SYS_PROMPT)+16)  /* Print Buffer Size */
#define CONFIG_SYS_MAXARGS	16		/* max number of command args	*/
#define CONFIG_SYS_BARGSIZE	CONFIG_SYS_CBSIZE	/* Boot Argument Buffer Size	*/

#define CONFIG_SYS_MEMTEST_START	0x00100000	/* memtest works on	*/
#define CONFIG_SYS_MEMTEST_END		0x00F00000	/* 1 ... 15 MB in DRAM	*/

#define CONFIG_CLOCKS_IN_MHZ	1	/* clocks passed to Linux in MHz */
					/* for versions < 2.4.5-pre5	 */

#define CONFIG_SYS_LOAD_ADDR		0x100000	/* default load address	*/

#define CONFIG_SYS_HZ			1000	/* decrementer freq: 1 ms ticks	*/

#define CONFIG_SYS_BAUDRATE_TABLE	{ 9600, 19200, 38400, 57600, 115200 }

#define CONFIG_SYS_RESET_ADDRESS	0x04400000

#define CONFIG_MISC_INIT_R	1	/* We need misc_init_r()	*/

#define CONFIG_SYS_BOOTMAPSZ		(8 << 20) /* Initial Memory map for Linux */

#define CONFIG_SYS_SDRAM_BASE		0x00000000
#define CONFIG_SYS_FLASH_BASE		0xFF800000

#define CONFIG_SYS_MONITOR_BASE	TEXT_BASE
#define CONFIG_SYS_MONITOR_LEN		(256 << 10)     /* Reserve 256 kB for Monitor  */
#define CONFIG_SYS_MALLOC_LEN		(128 << 10)	/* Reserve 128 kB for malloc() */

#define CONFIG_SYS_MAX_FLASH_BANKS	1	/* max num of memory banks	*/
#define CONFIG_SYS_MAX_FLASH_SECT	64	/* max num of sects on one chip */
#define CONFIG_SYS_MAX_FLASH_SIZE	(CONFIG_SYS_MAX_FLASH_SECT * 0x10000)	/* 4 MB */

#define CONFIG_SYS_FLASH_ERASE_TOUT	2400000	/* Flash Erase Timeout (in ms)	*/
#define CONFIG_SYS_FLASH_WRITE_TOUT	500	/* Flash Write Timeout (in ms)	*/

/* Environment in FLASH, there is little space left in Serial EEPROM */
#define CONFIG_ENV_IS_IN_FLASH	1
#define CONFIG_ENV_SECT_SIZE	0x10000 /* We use one complete sector	*/
#define CONFIG_ENV_ADDR		(CONFIG_SYS_FLASH_BASE + 0x10000) /* 2. sector */


#define CONFIG_SYS_HRCW_MASTER ( ( HRCW_BPS01 | HRCW_EBM )		|\
			  ( HRCW_L2CPC10 | HRCW_ISB110 )	|\
			  ( HRCW_MMR11 | HRCW_APPC10 )		|\
			  ( HRCW_CS10PC01 | HRCW_MODCK_H0101 )	 \
			) /* 0x14863245 */

/* no slaves */
#define CONFIG_SYS_HRCW_SLAVE1 0
#define CONFIG_SYS_HRCW_SLAVE2 0
#define CONFIG_SYS_HRCW_SLAVE3 0
#define CONFIG_SYS_HRCW_SLAVE4 0
#define CONFIG_SYS_HRCW_SLAVE5 0
#define CONFIG_SYS_HRCW_SLAVE6 0
#define CONFIG_SYS_HRCW_SLAVE7 0

#define CONFIG_SYS_IMMR		0xFF000000 /* We keep original value */

#define CONFIG_SYS_INIT_RAM_ADDR	CONFIG_SYS_IMMR
#define CONFIG_SYS_INIT_RAM_END	0x4000	/* End of used area in DPRAM	*/
#define CONFIG_SYS_GBL_DATA_SIZE	128	/* size in bytes reserved for initial data */
#define CONFIG_SYS_GBL_DATA_OFFSET	(CONFIG_SYS_INIT_RAM_END - CONFIG_SYS_GBL_DATA_SIZE)
#define CONFIG_SYS_INIT_SP_OFFSET	CONFIG_SYS_GBL_DATA_OFFSET

#define BOOTFLAG_COLD	0x01	  /* Normal Power-On: Boot from FLASH	*/
#define BOOTFLAG_WARM	0x02	  /* Software reboot			*/


#define CONFIG_SYS_CACHELINE_SIZE	32     /* For MPC8260 CPU		*/
#if defined(CONFIG_CMD_KGDB)
# define CONFIG_SYS_CACHELINE_SHIFT	5      /* log base 2 of the above value */
#endif

#define CONFIG_SYS_HID0_INIT	(HID0_ICE|HID0_DCE|HID0_ICFI|HID0_DCI|\
			 HID0_IFEM|HID0_ABE)
#define CONFIG_SYS_HID0_FINAL	(HID0_IFEM|HID0_ABE)
#define CONFIG_SYS_HID2	0

#define CONFIG_SYS_RMR		RMR_CSRE

#define CONFIG_SYS_BCR		0xA01C0000

#define CONFIG_SYS_SIUMCR	0X4205C000

#if defined (CONFIG_WATCHDOG)
#define CONFIG_SYS_SYPCR	(SYPCR_SWTC|SYPCR_BMT|SYPCR_PBME|SYPCR_LBME|\
			 SYPCR_SWRI|SYPCR_SWP|SYPCR_SWE)
#else
#define CONFIG_SYS_SYPCR	(SYPCR_SWTC|SYPCR_BMT|SYPCR_PBME|SYPCR_LBME|\
			 SYPCR_SWRI|SYPCR_SWP)
#endif /* CONFIG_WATCHDOG */

#define CONFIG_SYS_TMCNTSC	(TMCNTSC_SEC|TMCNTSC_ALR|TMCNTSC_TCF|TMCNTSC_TCE)

#define CONFIG_SYS_PISCR	(PISCR_PS|PISCR_PTF|PISCR_PTE)

#define CONFIG_SYS_SCCR	0

#define CONFIG_SYS_RCCR	0


#define CONFIG_SYS_BR0_PRELIM	((CONFIG_SYS_FLASH_BASE & BRx_BA_MSK) | 0x0801)
#define CONFIG_SYS_OR0_PRELIM	0xFF800882
#define CONFIG_SYS_BR1_PRELIM	((CONFIG_SYS_SDRAM_BASE & BRx_BA_MSK) | 0x0041)
#define CONFIG_SYS_OR1_PRELIM	0xF8002CD0

#define CONFIG_SYS_PSDMR	0x404A241A
#define CONFIG_SYS_MPTPR	0x00007400
#define CONFIG_SYS_PSRT	0x00000007

#endif /* __CONFIG_H */
