


#ifndef __CONFIG_H
#define __CONFIG_H


#define CONFIG_MPC8260		1	/* This is an MPC8260 CPU	*/
#define CONFIG_COGENT		1	/* using Cogent Modular Architecture */
#define CONFIG_CPM2		1	/* Has a CPM2 */

#define	CONFIG_MISC_INIT_F	1	/* Use misc_init_f()		*/
#define	CONFIG_MISC_INIT_R		/* Use misc_init_r()		*/

/* Cogent Modular Architecture options */
#define CONFIG_CMA282		1	/* ...on a CMA282 CPU module	*/
#define CONFIG_CMA111		1	/* ...on a CMA111 motherboard	*/

#define	CONFIG_CONS_ON_SMC		/* define if console on SMC */
#undef	CONFIG_CONS_ON_SCC		/* define if console on SCC */
#undef	CONFIG_CONS_NONE		/* define if console on something else*/
#define CONFIG_CONS_INDEX	1	/* which serial channel for console */
#undef	CONFIG_CONS_USE_EXTC		/* SMC/SCC use ext clock not brg_clk */
#define	CONFIG_CONS_EXTC_RATE	3686400	/* SMC/SCC ext clk rate in Hz */
#define	CONFIG_CONS_EXTC_PINSEL	0	/* pin select 0=CLK3/CLK9,1=CLK5/CLK15*/

#undef	CONFIG_ETHER_ON_SCC		/* define if ether on SCC	*/
#undef	CONFIG_ETHER_ON_FCC		/* define if ether on FCC	*/
#define	CONFIG_ETHER_NONE		/* define if ether on something else */
#define CONFIG_ETHER_INDEX	1	/* which channel for ether	*/

/* system clock rate (CLKIN) - equal to the 60x and local bus speed */
#define CONFIG_8260_CLKIN	66666666	/* in Hz */

#if defined(CONFIG_CONS_NONE) || defined(CONFIG_CONS_USE_EXTC)
#define CONFIG_BAUDRATE		230400
#else
#define CONFIG_BAUDRATE		9600
#endif


#define CONFIG_BOOTP_BOOTFILESIZE
#define CONFIG_BOOTP_BOOTPATH
#define CONFIG_BOOTP_GATEWAY
#define CONFIG_BOOTP_HOSTNAME


#include <config_cmd_default.h>

#define CONFIG_CMD_KGDB

#undef CONFIG_CMD_NET


#ifdef DEBUG
#define CONFIG_BOOTDELAY	-1	/* autoboot disabled		*/
#else
#define CONFIG_BOOTDELAY	5	/* autoboot after 5 seconds	*/
#endif
#define CONFIG_BOOTCOMMAND	"bootm 04080000 04200000" /* autoboot command*/

#define CONFIG_BOOTARGS		"root=/dev/ram rw"

#if defined(CONFIG_CMD_KGDB)
#define	CONFIG_KGDB_ON_SMC		/* define if kgdb on SMC */
#undef	CONFIG_KGDB_ON_SCC		/* define if kgdb on SCC */
#undef	CONFIG_KGDB_NONE		/* define if kgdb on something else */
#define CONFIG_KGDB_INDEX	2	/* which serial channel for kgdb */
#define	CONFIG_KGDB_USE_EXTC		/* SMC/SCC use ext clock not brg_clk */
#define	CONFIG_KGDB_EXTC_RATE	3686400	/* serial ext clk rate in Hz */
#define	CONFIG_KGDB_EXTC_PINSEL	0	/* pin select 0=CLK3/CLK9,1=CLK5/CLK15*/
# if defined(CONFIG_KGDB_NONE) || defined(CONFIG_KGDB_USE_EXTC)
#define CONFIG_KGDB_BAUDRATE	230400	/* speed to run kgdb serial port at */
# else
#define CONFIG_KGDB_BAUDRATE	9600	/* speed to run kgdb serial port at */
# endif
#endif

#undef	CONFIG_WATCHDOG			/* disable platform specific watchdog */

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


#define CONFIG_SYS_CMA_MB_BASE		0x00000000	/* base of m/b address space */

#include <configs/cogent_common.h>

#ifdef CONFIG_CONS_NONE
#define CONFIG_SYS_CMA_CONS_SERIAL	/* use Cogent motherboard serial for console */
#endif
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

#define CONFIG_SYS_HRCW_MASTER	(HRCW_EBM|HRCW_BPS10|HRCW_L2CPC10|HRCW_DPPC11|\
			 HRCW_ISB100|HRCW_MMR11|HRCW_MODCK_H0101)
/* no slaves so just duplicate the master hrcw */
#define CONFIG_SYS_HRCW_SLAVE1	CONFIG_SYS_HRCW_MASTER
#define CONFIG_SYS_HRCW_SLAVE2	CONFIG_SYS_HRCW_MASTER
#define CONFIG_SYS_HRCW_SLAVE3	CONFIG_SYS_HRCW_MASTER
#define CONFIG_SYS_HRCW_SLAVE4	CONFIG_SYS_HRCW_MASTER
#define CONFIG_SYS_HRCW_SLAVE5	CONFIG_SYS_HRCW_MASTER
#define CONFIG_SYS_HRCW_SLAVE6	CONFIG_SYS_HRCW_MASTER
#define CONFIG_SYS_HRCW_SLAVE7	CONFIG_SYS_HRCW_MASTER

#define CONFIG_SYS_IMMR		0xF0000000

#define CONFIG_SYS_INIT_RAM_ADDR	CONFIG_SYS_IMMR
#define	CONFIG_SYS_INIT_RAM_END	0x4000	/* End of used area in DPRAM	*/
#define	CONFIG_SYS_GBL_DATA_SIZE	128  /* size in bytes reserved for initial data */
#define CONFIG_SYS_GBL_DATA_OFFSET	(CONFIG_SYS_INIT_RAM_END - CONFIG_SYS_GBL_DATA_SIZE)
#define	CONFIG_SYS_INIT_SP_OFFSET	CONFIG_SYS_GBL_DATA_OFFSET

#define	CONFIG_SYS_SDRAM_BASE		CMA_MB_RAM_BASE
#ifdef CONFIG_CMA302
#define CONFIG_SYS_FLASH_BASE		CMA_MB_SLOT2_BASE	/* cma302 in slot 2 */
#else
#define CONFIG_SYS_FLASH_BASE		CMA_MB_FLASH_BASE	/* flash on m/b */
#endif
#define	CONFIG_SYS_MONITOR_BASE	TEXT_BASE
#define	CONFIG_SYS_MONITOR_LEN		(256 << 10)	/* Reserve 256 kB for Monitor	*/
#define	CONFIG_SYS_MALLOC_LEN		(128 << 10)	/* Reserve 128 kB for malloc()*/

#define	CONFIG_SYS_BOOTMAPSZ		(8 << 20)	/* Initial Mem map for Linux*/

#define CONFIG_SYS_MAX_FLASH_BANKS	2	/* max num of memory banks	*/
#define CONFIG_SYS_MAX_FLASH_SECT	67	/* max num of sects on one chip	*/

#define CONFIG_SYS_FLASH_ERASE_TOUT	120000	/* Flash Erase Timeout (in ms)	*/
#define CONFIG_SYS_FLASH_WRITE_TOUT	500	/* Flash Write Timeout (in ms)	*/

#define	CONFIG_ENV_IS_IN_FLASH	1
#define CONFIG_ENV_ADDR		CONFIG_SYS_FLASH_BASE /* Addr of Environment Sector */
#ifdef CONFIG_CMA302
#define	CONFIG_ENV_SIZE		0x1000	/* Total Size of Environment Sector */
#define CONFIG_ENV_SECT_SIZE	(512*1024) /* see README - env sect real size */
#else
#define	CONFIG_ENV_SIZE		0x4000	/* Total Size of Environment Sector */
#endif

#define CONFIG_SYS_CACHELINE_SIZE	32	/* For MPC8260 CPU		*/
#if defined(CONFIG_CMD_KGDB)
# define CONFIG_SYS_CACHELINE_SHIFT	5	/* log base 2 of the above value*/
#endif

#define CONFIG_SYS_HID0_INIT	(HID0_ICE|HID0_DCE|HID0_ICFI|HID0_DCI|\
				HID0_IFEM|HID0_ABE)
#define CONFIG_SYS_HID0_FINAL	(HID0_ICE|HID0_IFEM|HID0_ABE)
#define CONFIG_SYS_HID2	0

#define CONFIG_SYS_RMR		RMR_CSRE

#define CONFIG_SYS_BCR		BCR_EBM

#define CONFIG_SYS_SIUMCR	(SIUMCR_DPPC11|SIUMCR_L2CPC10|SIUMCR_MMR11)

#if defined(CONFIG_WATCHDOG)
#define CONFIG_SYS_SYPCR	(SYPCR_SWTC|SYPCR_BMT|SYPCR_PBME|SYPCR_LBME|\
			 SYPCR_SWRI|SYPCR_SWP|SYPCR_SWE)
#else
#define CONFIG_SYS_SYPCR	(SYPCR_SWTC|SYPCR_BMT|SYPCR_PBME|SYPCR_LBME|\
			 SYPCR_SWRI|SYPCR_SWP)
#endif /* CONFIG_WATCHDOG */

#define CONFIG_SYS_TMCNTSC	(TMCNTSC_SEC|TMCNTSC_ALR|TMCNTSC_TCF|TMCNTSC_TCE)

#define CONFIG_SYS_PISCR	(PISCR_PS|PISCR_PTF|PISCR_PTE)

#define CONFIG_SYS_SCCR	(SCCR_DFBRG01)

#define CONFIG_SYS_RCCR	0

#if defined(CONFIG_CMA282)


#define CONFIG_SYS_CMA_CS0_BASE	TEXT_BASE	/* EPROM */
#define CONFIG_SYS_CMA_CS0_SIZE	(1 << 20)
#if 0
#define CONFIG_SYS_CMA_CS2_BASE	0x10000000	/* Local Bus SDRAM */
#define CONFIG_SYS_CMA_CS2_SIZE	(16 << 20)
#endif


/* base address = CONFIG_SYS_CMA_CS0_BASE, 16-bit, no parity, r/o, gpcm (60x bus) */
#define CONFIG_SYS_BR0_PRELIM	((CONFIG_SYS_CMA_CS0_BASE&BRx_BA_MSK)|BRx_PS_16|BRx_WP|BRx_V)
/* mask size CONFIG_SYS_CMA_CS0_SIZE, csneg 1/4 early, adr-to-cs 1/2, 10-wait states */
#define CONFIG_SYS_OR0_PRELIM	(P2SZ_TO_AM(CONFIG_SYS_CMA_CS0_SIZE)|\
				ORxG_CSNT|ORxG_ACS_DIV2|ORxG_SCY_10_CLK)


#if 0
/* base address = CONFIG_SYS_CMA_CS2_BASE, 32-bit, no parity, ??? */
#define CONFIG_SYS_BR0_PRELIM	((CONFIG_SYS_CMA_CS2_BASE&BRx_BA_MSK)|BRx_PS_32|/*???*/|BRx_V)
/* mask size CONFIG_SYS_CMA_CS2_SIZE, CS time normal, ??? */
#define CONFIG_SYS_OR2_PRELIM	((~(CONFIG_SYS_CMA_CS2_SIZE-1)&ORx_AM_MSK)|/*???*/)
#endif

#endif

#define	BOOTFLAG_COLD	0x01		/* Normal Power-On: Boot from FLASH*/
#define BOOTFLAG_WARM	0x02		/* Software reboot		*/

#endif	/* __CONFIG_H */
