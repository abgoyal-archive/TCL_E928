


#ifndef __CONFIG_H
#define __CONFIG_H

#undef CONFIG_SYS_RAMBOOT


#define CONFIG_MPC8260		1	/* This is a MPC8260 CPU	*/
#define CONFIG_PM828		1	/* ...on a PM828 module */
#define CONFIG_CPM2		1	/* Has a CPM2 */

#undef CONFIG_DB_CR826_J30x_ON		/* J30x jumpers on D.B. carrier */

#define CONFIG_BOOTDELAY	5	/* autoboot after 5 seconds	*/

#define CONFIG_PREBOOT	"echo;echo Type \\\"run flash_nfs\\\" to mount root filesystem over NFS;echo"

#undef	CONFIG_BOOTARGS
#define CONFIG_BOOTCOMMAND							\
	"bootp;"								\
	"setenv bootargs root=/dev/nfs rw nfsroot=${serverip}:${rootpath} "	\
	"ip=${ipaddr}:${serverip}:${gatewayip}:${netmask}:${hostname}::off;"	\
	"bootm"

/* enable I2C and select the hardware/software driver */
#undef	CONFIG_HARD_I2C
#define CONFIG_SOFT_I2C		1	/* I2C bit-banged		*/
# define CONFIG_SYS_I2C_SPEED		50000
# define CONFIG_SYS_I2C_SLAVE		0xFE
#define I2C_PORT	3		/* Port A=0, B=1, C=2, D=3 */
#define I2C_ACTIVE	(iop->pdir |=  0x00010000)
#define I2C_TRISTATE	(iop->pdir &= ~0x00010000)
#define I2C_READ	((iop->pdat & 0x00010000) != 0)
#define I2C_SDA(bit)	if(bit) iop->pdat |=  0x00010000; \
			else	iop->pdat &= ~0x00010000
#define I2C_SCL(bit)	if(bit) iop->pdat |=  0x00020000; \
			else	iop->pdat &= ~0x00020000
#define I2C_DELAY	udelay(5)	/* 1/4 I2C clock duration */


#define CONFIG_RTC_PCF8563
#define CONFIG_SYS_I2C_RTC_ADDR	0x51

#define CONFIG_CONS_ON_SMC		/* define if console on SMC */
#undef	CONFIG_CONS_ON_SCC		/* define if console on SCC */
#undef	CONFIG_CONS_NONE		/* define if console on something else*/
#define CONFIG_CONS_INDEX	2	/* which serial channel for console */

#define CONFIG_NET_MULTI
#undef	CONFIG_ETHER_NONE		/* define if ether on something else */

#undef	CONFIG_ETHER_ON_SCC		/* define if ether on SCC	*/
#define CONFIG_ETHER_INDEX    1		/* which SCC channel for ethernet */

#define CONFIG_ETHER_ON_FCC		/* define if ether on FCC	*/
#define CONFIG_ETHER_ON_FCC1
# define CONFIG_SYS_CMXFCR_MASK1	(CMXFCR_FC1|CMXFCR_RF1CS_MSK|CMXFCR_TF1CS_MSK)
#ifndef CONFIG_DB_CR826_J30x_ON
# define CONFIG_SYS_CMXFCR_VALUE1	(CMXFCR_RF1CS_CLK11|CMXFCR_TF1CS_CLK10)
#else
# define CONFIG_SYS_CMXFCR_VALUE1	(CMXFCR_RF1CS_CLK11|CMXFCR_TF1CS_CLK12)
#endif
#define CONFIG_ETHER_ON_FCC2
# define CONFIG_SYS_CMXFCR_MASK2	(CMXFCR_FC2|CMXFCR_RF2CS_MSK|CMXFCR_TF2CS_MSK)
# define CONFIG_SYS_CMXFCR_VALUE2	(CMXFCR_RF2CS_CLK13|CMXFCR_TF2CS_CLK14)
# define CONFIG_SYS_CPMFCR_RAMTYPE	0
# define CONFIG_SYS_FCC_PSMR		(FCC_PSMR_FDE|FCC_PSMR_LPB)

/* system clock rate (CLKIN) - equal to the 60x and local bus speed */
#define CONFIG_8260_CLKIN	100000000	/* in Hz */

#if defined(CONFIG_CONS_NONE) || defined(CONFIG_CONS_USE_EXTC)
#define CONFIG_BAUDRATE		230400
#else
#define CONFIG_BAUDRATE		9600
#endif

#define CONFIG_LOADS_ECHO	1	/* echo on for serial download	*/
#undef	CONFIG_SYS_LOADS_BAUD_CHANGE		/* don't allow baudrate change	*/

#undef	CONFIG_WATCHDOG			/* watchdog disabled		*/

#define CONFIG_BOOTP_SUBNETMASK
#define CONFIG_BOOTP_GATEWAY
#define CONFIG_BOOTP_HOSTNAME
#define CONFIG_BOOTP_BOOTPATH
#define CONFIG_BOOTP_BOOTFILESIZE


#include <config_cmd_default.h>

#define CONFIG_CMD_BEDBUG
#define CONFIG_CMD_DATE
#define CONFIG_CMD_DHCP
#define CONFIG_CMD_EEPROM
#define CONFIG_CMD_I2C
#define CONFIG_CMD_NFS
#define CONFIG_CMD_SNTP

#ifdef CONFIG_PCI
#define CONFIG_CMD_PCI
#endif

#define CONFIG_SYS_LONGHELP			/* undef to save memory		*/
#define CONFIG_SYS_PROMPT	"=> "		/* Monitor Command Prompt	*/
#if defined(CONFIG_CMD_KGDB)
#define CONFIG_SYS_CBSIZE	1024		/* Console I/O Buffer Size	*/
#else
#define CONFIG_SYS_CBSIZE	256		/* Console I/O Buffer Size	*/
#endif
#define CONFIG_SYS_PBSIZE (CONFIG_SYS_CBSIZE+sizeof(CONFIG_SYS_PROMPT)+16) /* Print Buffer Size */
#define CONFIG_SYS_MAXARGS	16		/* max number of command args	*/
#define CONFIG_SYS_BARGSIZE	CONFIG_SYS_CBSIZE	/* Boot Argument Buffer Size	*/

#define CONFIG_SYS_MEMTEST_START	0x0400000	/* memtest works on	*/
#define CONFIG_SYS_MEMTEST_END 0x0C00000	/* 4 ... 12 MB in DRAM	*/

#define CONFIG_SYS_LOAD_ADDR	0x100000	/* default load address */

#define CONFIG_SYS_HZ		1000		/* decrementer freq: 1 ms ticks */

#define CONFIG_SYS_BAUDRATE_TABLE	{ 9600, 19200, 38400, 57600, 115200 }

#define CONFIG_SYS_RESET_ADDRESS 0xFDFFFFFC	/* "bad" address		*/

#define CONFIG_SYS_BOOTMAPSZ	     (8 << 20)	     /* Initial Memory map for Linux */


#define CONFIG_SYS_BOOTROM_BASE	0xFF800000
#define CONFIG_SYS_BOOTROM_SIZE	0x00080000
#define CONFIG_SYS_FLASH0_BASE		0x40000000
#define CONFIG_SYS_FLASH0_SIZE		0x02000000
#define CONFIG_SYS_DOC_BASE		0xFF800000
#define CONFIG_SYS_DOC_SIZE		0x00100000


#define CONFIG_SYS_FLASH_SIZE CONFIG_SYS_FLASH0_SIZE

#define CONFIG_SYS_MAX_FLASH_BANKS	1	/* max num of memory banks	*/
#define CONFIG_SYS_MAX_FLASH_SECT	135	/* max num of sects on one chip */

#define CONFIG_SYS_FLASH_ERASE_TOUT	240000	/* Flash Erase Timeout (in ms)	*/
#define CONFIG_SYS_FLASH_WRITE_TOUT	500	/* Flash Write Timeout (in ms)	*/

#if 0
/* Start port with environment in flash; switch to EEPROM later */
#define CONFIG_ENV_IS_IN_FLASH	1
#define CONFIG_ENV_ADDR		(CONFIG_SYS_FLASH_BASE+0x40000)
#define CONFIG_ENV_SIZE		0x40000
#define CONFIG_ENV_SECT_SIZE	0x40000
#else
/* Final version: environment in EEPROM */
#define CONFIG_ENV_IS_IN_EEPROM	1
#define CONFIG_SYS_I2C_EEPROM_ADDR	0x58
#define CONFIG_SYS_I2C_EEPROM_ADDR_LEN 1
#define CONFIG_SYS_EEPROM_PAGE_WRITE_BITS	4
#define CONFIG_SYS_EEPROM_PAGE_WRITE_DELAY_MS	10	/* and takes up to 10 msec */
#define CONFIG_ENV_OFFSET		512
#define CONFIG_ENV_SIZE		(2048 - 512)
#endif

#if defined(CONFIG_BOOT_ROM)
#define CONFIG_SYS_HRCW_MASTER		(HRCW_BPS01 | HRCW_CIP | HRCW_ISB100 | HRCW_BMS)
#else
#define CONFIG_SYS_HRCW_MASTER		(HRCW_CIP | HRCW_ISB100 | HRCW_BMS)
#endif

/* no slaves so just fill with zeros */
#define CONFIG_SYS_HRCW_SLAVE1		0
#define CONFIG_SYS_HRCW_SLAVE2		0
#define CONFIG_SYS_HRCW_SLAVE3		0
#define CONFIG_SYS_HRCW_SLAVE4		0
#define CONFIG_SYS_HRCW_SLAVE5		0
#define CONFIG_SYS_HRCW_SLAVE6		0
#define CONFIG_SYS_HRCW_SLAVE7		0

#define CONFIG_SYS_IMMR		0xF0000000

#define CONFIG_SYS_INIT_RAM_ADDR	CONFIG_SYS_IMMR
#define CONFIG_SYS_INIT_RAM_END	0x4000	/* End of used area in DPRAM	*/
#define CONFIG_SYS_GBL_DATA_SIZE	128 /* size in bytes reserved for initial data*/
#define CONFIG_SYS_GBL_DATA_OFFSET	(CONFIG_SYS_INIT_RAM_END - CONFIG_SYS_GBL_DATA_SIZE)
#define CONFIG_SYS_INIT_SP_OFFSET	CONFIG_SYS_GBL_DATA_OFFSET

#define CONFIG_SYS_SDRAM_BASE		0x00000000
#define CONFIG_SYS_FLASH_BASE		CONFIG_SYS_FLASH0_BASE
#define CONFIG_SYS_MONITOR_BASE	TEXT_BASE
#define CONFIG_SYS_MONITOR_LEN		(256 << 10)	/* Reserve 256 kB for Monitor */
#define CONFIG_SYS_MALLOC_LEN		(128 << 10)	/* Reserve 128 kB for malloc()*/

#if (CONFIG_SYS_MONITOR_BASE < CONFIG_SYS_FLASH_BASE)
# define CONFIG_SYS_RAMBOOT
#endif

#ifdef	CONFIG_PCI
#define CONFIG_PCI_PNP
#define CONFIG_EEPRO100
#define CONFIG_SYS_RX_ETH_BUFFER	8		/* use 8 rx buffer on eepro100	*/
#endif

#define BOOTFLAG_COLD		0x01	/* Normal Power-On: Boot from FLASH*/
#define BOOTFLAG_WARM		0x02	/* Software reboot		   */


#define CONFIG_SYS_CACHELINE_SIZE	32	/* For MPC8260 CPU		*/
#if defined(CONFIG_CMD_KGDB)
#  define CONFIG_SYS_CACHELINE_SHIFT	5	/* log base 2 of the above value */
#endif

#define CONFIG_SYS_HID0_INIT	(HID0_ICE|HID0_DCE|HID0_ICFI|HID0_DCI|\
				HID0_IFEM|HID0_ABE)
#define CONFIG_SYS_HID0_FINAL	(HID0_ICE|HID0_IFEM|HID0_ABE)
#define CONFIG_SYS_HID2	0

#define CONFIG_SYS_RMR		RMR_CSRE


#define BCR_APD01	0x10000000
#define CONFIG_SYS_BCR		(BCR_APD01|BCR_ETM|BCR_LETM)	/* 8260 mode */

#if 0
#define CONFIG_SYS_SIUMCR	(SIUMCR_DPPC00|SIUMCR_APPC10|SIUMCR_CS10PC01)
#else
#define CONFIG_SYS_SIUMCR	(SIUMCR_DPPC10|SIUMCR_APPC10)
#endif


#if defined(CONFIG_WATCHDOG)
#define CONFIG_SYS_SYPCR	(SYPCR_SWTC|SYPCR_BMT|SYPCR_PBME|SYPCR_LBME|\
			 SYPCR_SWRI|SYPCR_SWP|SYPCR_SWE)
#else
#define CONFIG_SYS_SYPCR	(SYPCR_SWTC|SYPCR_BMT|SYPCR_PBME|SYPCR_LBME|\
			 SYPCR_SWRI|SYPCR_SWP)
#endif /* CONFIG_WATCHDOG */

#define CONFIG_SYS_TMCNTSC	(TMCNTSC_SEC|TMCNTSC_ALR|TMCNTSC_TCF|TMCNTSC_TCE)

#define CONFIG_SYS_PISCR	(PISCR_PS|PISCR_PTF|PISCR_PTE)

#define CONFIG_SYS_SCCR	(SCCR_DFBRG00)

#define CONFIG_SYS_RCCR	0


	/* Initialize SDRAM on local bus
	 */
#define CONFIG_SYS_INIT_LOCAL_SDRAM


#define CONFIG_SYS_MIN_AM_MASK 0xC0000000

#define CONFIG_SYS_MPTPR	0x2000
#define CONFIG_SYS_PSRT	0x16

#define CONFIG_SYS_MRS_OFFS	0x00000000


#if defined(CONFIG_BOOT_ROM)
#define CONFIG_SYS_BR0_PRELIM	((CONFIG_SYS_BOOTROM_BASE & BRx_BA_MSK)|\
			 BRx_PS_8			|\
			 BRx_MS_GPCM_P			|\
			 BRx_V)

#define CONFIG_SYS_OR0_PRELIM	(P2SZ_TO_AM(CONFIG_SYS_BOOTROM_SIZE)	|\
			 ORxG_CSNT			|\
			 ORxG_ACS_DIV1			|\
			 ORxG_SCY_5_CLK			|\
			 ORxG_EHTR			|\
			 ORxG_TRLX)

#define CONFIG_SYS_BR1_PRELIM	((CONFIG_SYS_FLASH_BASE & BRx_BA_MSK)	|\
			 BRx_PS_64			|\
			 BRx_MS_GPCM_P			|\
			 BRx_V)

#define CONFIG_SYS_OR1_PRELIM	(P2SZ_TO_AM(CONFIG_SYS_FLASH_SIZE)	|\
			 ORxG_CSNT			|\
			 ORxG_ACS_DIV1			|\
			 ORxG_SCY_5_CLK			|\
			 ORxG_EHTR			|\
			 ORxG_TRLX)

#else	/* ! CONFIG_BOOT_ROM */

#define CONFIG_SYS_BR0_PRELIM	((CONFIG_SYS_FLASH_BASE & BRx_BA_MSK)	|\
			 BRx_PS_64			|\
			 BRx_MS_GPCM_P			|\
			 BRx_V)

#define CONFIG_SYS_OR0_PRELIM	(P2SZ_TO_AM(CONFIG_SYS_FLASH_SIZE)	|\
			 ORxG_CSNT			|\
			 ORxG_ACS_DIV1			|\
			 ORxG_SCY_5_CLK			|\
			 ORxG_EHTR			|\
			 ORxG_TRLX)

#define CONFIG_SYS_BR1_PRELIM	((CONFIG_SYS_DOC_BASE & BRx_BA_MSK)	|\
			 BRx_PS_8			|\
			 BRx_MS_GPCM_P			|\
			 BRx_V)

#define CONFIG_SYS_OR1_PRELIM	(P2SZ_TO_AM(CONFIG_SYS_DOC_SIZE)	|\
			 ORxG_CSNT			|\
			 ORxG_ACS_DIV1			|\
			 ORxG_SCY_5_CLK			|\
			 ORxG_EHTR			|\
			 ORxG_TRLX)

#endif /* CONFIG_BOOT_ROM */


#ifndef CONFIG_SYS_RAMBOOT
#define CONFIG_SYS_BR2_PRELIM	((CONFIG_SYS_SDRAM_BASE & BRx_BA_MSK)	|\
			 BRx_PS_64			|\
			 BRx_MS_SDRAM_P			|\
			 BRx_V)

	/* SDRAM initialization values for 8-column chips
	 */
#define CONFIG_SYS_OR2_8COL	(CONFIG_SYS_MIN_AM_MASK		|\
			 ORxS_BPD_4			|\
			 ORxS_ROWST_PBI0_A9		|\
			 ORxS_NUMR_12)

#define CONFIG_SYS_PSDMR_8COL	(PSDMR_SDAM_A13_IS_A5		|\
			 PSDMR_BSMA_A14_A16		|\
			 PSDMR_SDA10_PBI0_A10		|\
			 PSDMR_RFRC_7_CLK		|\
			 PSDMR_PRETOACT_2W		|\
			 PSDMR_ACTTORW_2W		|\
			 PSDMR_LDOTOPRE_1C		|\
			 PSDMR_WRC_1C			|\
			 PSDMR_CL_2)

	/* SDRAM initialization values for 9-column chips
	 */
#define CONFIG_SYS_OR2_9COL	(CONFIG_SYS_MIN_AM_MASK		|\
			 ORxS_BPD_4			|\
			 ORxS_ROWST_PBI0_A7		|\
			 ORxS_NUMR_13)

#define CONFIG_SYS_PSDMR_9COL	(PSDMR_SDAM_A14_IS_A5		|\
			 PSDMR_BSMA_A13_A15		|\
			 PSDMR_SDA10_PBI0_A9		|\
			 PSDMR_RFRC_7_CLK		|\
			 PSDMR_PRETOACT_2W		|\
			 PSDMR_ACTTORW_2W		|\
			 PSDMR_LDOTOPRE_1C		|\
			 PSDMR_WRC_1C			|\
			 PSDMR_CL_2)

#define CONFIG_SYS_OR2_PRELIM	 CONFIG_SYS_OR2_9COL
#define CONFIG_SYS_PSDMR	 CONFIG_SYS_PSDMR_9COL

#endif /* CONFIG_SYS_RAMBOOT */

#endif	/* __CONFIG_H */
