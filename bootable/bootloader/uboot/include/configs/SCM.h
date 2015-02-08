


#ifndef __CONFIG_H
#define __CONFIG_H


#define CONFIG_MPC8260		1	/* This is a MPC8260 CPU		*/
#define CONFIG_TQM8260		200	/* ...on a TQM8260 module Rev.200	*/
#define CONFIG_SCM              1	/* ...on a System Controller Module	*/
#define CONFIG_CPM2		1	/* Has a CPM2 */

#if (CONFIG_TQM8260 <= 100)
#  error "TQM8260 module revison not supported"
#endif

/* We use a TQM8260 module with a 300MHz CPU */
#define CONFIG_300MHz

/* Define 60x busmode only if your TQM8260 has L2 cache! */
#ifdef CONFIG_L2_CACHE
#  define CONFIG_BUSMODE_60x	1	/* bus mode: 60x			*/
#else
#  undef  CONFIG_BUSMODE_60x		/* bus mode: 8260			*/
#endif

/* The board with 300MHz CPU doesn't have L2 cache, but works in 60x bus mode */
#ifdef CONFIG_300MHz
#  define CONFIG_BUSMODE_60x
#endif

#define CONFIG_82xx_CONS_SMC1	1	/* console on SMC1			*/

#define CONFIG_BOOTDELAY	5	/* autoboot after 5 seconds	*/

#define	CONFIG_CLOCKS_IN_MHZ	1	/* clocks passsed to Linux in MHz */

#define CONFIG_PREBOOT	"echo;echo Type \\\"run flash_nfs\\\" to mount root filesystem over NFS;echo"

#undef	CONFIG_BOOTARGS
#define CONFIG_BOOTCOMMAND							\
	"bootp; "								\
	"setenv bootargs root=/dev/nfs rw nfsroot=${serverip}:${rootpath} "	\
	"ip=${ipaddr}:${serverip}:${gatewayip}:${netmask}:${hostname}::off; "	\
	"bootm"

/* enable I2C and select the hardware/software driver */
#undef  CONFIG_HARD_I2C			/* I2C with hardware support	*/
#define CONFIG_SOFT_I2C		1	/* I2C bit-banged		*/
#define CONFIG_SYS_I2C_SPEED		400000	/* I2C speed and slave address	*/
#define CONFIG_SYS_I2C_SLAVE		0x7F


#define I2C_PORT	3		/* Port A=0, B=1, C=2, D=3 */
#define I2C_ACTIVE	(iop->pdir |=  0x00010000)
#define I2C_TRISTATE	(iop->pdir &= ~0x00010000)
#define I2C_READ	((iop->pdat & 0x00010000) != 0)
#define I2C_SDA(bit)	if(bit) iop->pdat |=  0x00010000; \
			else    iop->pdat &= ~0x00010000
#define I2C_SCL(bit)	if(bit) iop->pdat |=  0x00020000; \
			else    iop->pdat &= ~0x00020000
#define I2C_DELAY	udelay(5)	/* 1/4 I2C clock duration */

#define CONFIG_SYS_I2C_EEPROM_ADDR	0x50
#define CONFIG_SYS_I2C_EEPROM_ADDR_LEN 2
#define CONFIG_SYS_EEPROM_PAGE_WRITE_BITS	4
#define CONFIG_SYS_EEPROM_PAGE_WRITE_DELAY_MS	10	/* and takes up to 10 msec */

#define CONFIG_I2C_X

#define CONFIG_CONS_ON_SMC		/* define if console on SMC */
#undef  CONFIG_CONS_ON_SCC		/* define if console on SCC */
#undef  CONFIG_CONS_NONE		/* define if console on something else*/
#ifdef CONFIG_82xx_CONS_SMC1
#define CONFIG_CONS_INDEX	1	/* which serial channel for console */
#endif
#ifdef CONFIG_82xx_CONS_SMC2
#define CONFIG_CONS_INDEX	2	/* which serial channel for console */
#endif

#undef  CONFIG_CONS_USE_EXTC		/* SMC/SCC use ext clock not brg_clk */
#define CONFIG_CONS_EXTC_RATE	3686400	/* SMC/SCC ext clk rate in Hz */
#define CONFIG_CONS_EXTC_PINSEL	0	/* pin select 0=CLK3/CLK9 */

#undef	CONFIG_ETHER_ON_SCC		/* define if ether on SCC       */
#define	CONFIG_ETHER_ON_FCC		/* define if ether on FCC       */
#undef	CONFIG_ETHER_NONE		/* define if ether on something else */
#define	CONFIG_ETHER_INDEX    1		/* which SCC/FCC channel for ethernet */

#if defined(CONFIG_ETHER_ON_FCC) && (CONFIG_ETHER_INDEX == 1)

# define CONFIG_SYS_CMXFCR_MASK	(CMXFCR_FC1|CMXFCR_RF1CS_MSK|CMXFCR_TF1CS_MSK)
# define CONFIG_SYS_CMXFCR_VALUE	(CMXFCR_RF1CS_CLK12|CMXFCR_TF1CS_CLK11)
# define CONFIG_SYS_CPMFCR_RAMTYPE	0
# define CONFIG_SYS_FCC_PSMR		(FCC_PSMR_FDE|FCC_PSMR_LPB)

#elif defined(CONFIG_ETHER_ON_FCC) && (CONFIG_ETHER_INDEX == 3)

# define CONFIG_SYS_CMXFCR_MASK	(CMXFCR_FC3|CMXFCR_RF3CS_MSK|CMXFCR_TF3CS_MSK)
# define CONFIG_SYS_CMXFCR_VALUE	(CMXFCR_RF3CS_CLK15|CMXFCR_TF3CS_CLK16)
# define CONFIG_SYS_CPMFCR_RAMTYPE	0
# define CONFIG_SYS_FCC_PSMR		(FCC_PSMR_FDE|FCC_PSMR_LPB)

#endif /* CONFIG_ETHER_ON_FCC, CONFIG_ETHER_INDEX */


/* system clock rate (CLKIN) - equal to the 60x and local bus speed */
#ifndef CONFIG_300MHz
#define CONFIG_8260_CLKIN	66666666	/* in Hz */
#else
#define CONFIG_8260_CLKIN	83333000	/* in Hz */
#endif

#if defined(CONFIG_CONS_NONE) || defined(CONFIG_CONS_USE_EXTC)
#define CONFIG_BAUDRATE		230400
#else
#define CONFIG_BAUDRATE		115200
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

#define CONFIG_CMD_DHCP
#define CONFIG_CMD_I2C
#define CONFIG_CMD_EEPROM
#define CONFIG_CMD_BSP


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

#define CONFIG_SYS_MEMTEST_START 0x0400000	/* memtest works on		*/
#define CONFIG_SYS_MEMTEST_END	0x0C00000	/* 4 ... 12 MB in DRAM		*/

#define	CONFIG_SYS_LOAD_ADDR	0x100000	/* default load address		*/

#define	CONFIG_SYS_HZ		1000		/* decrementer freq: 1 ms ticks	*/

#define CONFIG_SYS_BAUDRATE_TABLE	{ 9600, 19200, 38400, 57600, 115200 }

#define	CONFIG_SYS_RESET_ADDRESS 0xFFFFFFFC	/* "bad" address		*/

#define CONFIG_MISC_INIT_R		/* have misc_init_r() function	*/

#define CONFIG_SYS_BOOTMAPSZ        (8 << 20)       /* Initial Memory map for Linux */


#define CONFIG_SYS_FLASH0_BASE 0x40000000
#define CONFIG_SYS_FLASH1_BASE 0x60000000
#define CONFIG_SYS_FLASH0_SIZE 32
#define CONFIG_SYS_FLASH1_SIZE 32

#define CONFIG_SYS_FLASH_SIZE CONFIG_SYS_FLASH0_SIZE

#define CONFIG_SYS_MAX_FLASH_BANKS	1	/* max num of memory banks      */
#define CONFIG_SYS_MAX_FLASH_SECT	128	/* max num of sects on one chip */

#define CONFIG_SYS_FLASH_ERASE_TOUT	240000	/* Flash Erase Timeout (in ms)  */
#define CONFIG_SYS_FLASH_WRITE_TOUT	500	/* Flash Write Timeout (in ms)  */

#if 0
/* Start port with environment in flash; switch to EEPROM later */
#define CONFIG_ENV_IS_IN_FLASH	1
#define CONFIG_ENV_ADDR		(CONFIG_SYS_FLASH_BASE+0x40000)
#define CONFIG_ENV_SIZE		0x40000
#define CONFIG_ENV_SECT_SIZE	0x40000
#else
/* Final version: environment in EEPROM */
#define CONFIG_ENV_IS_IN_EEPROM	1
#define CONFIG_ENV_OFFSET		0
#define CONFIG_ENV_SIZE		2048
#endif

#define CONFIG_SYS_HWINFO_OFFSET	0x0003FFC0	/* offset of HW Info block */
#define CONFIG_SYS_HWINFO_SIZE		0x00000040	/* size   of HW Info block */
#define CONFIG_SYS_HWINFO_MAGIC	0x54514D38	/* 'TQM8' */

#if defined(CONFIG_266MHz)
#define CONFIG_SYS_HRCW_MASTER		(HRCW_CIP | HRCW_ISB111 | HRCW_BMS | \
							      HRCW_MODCK_H0111)
#elif defined(CONFIG_300MHz)
#define CONFIG_SYS_HRCW_MASTER		(HRCW_CIP | HRCW_ISB111 | HRCW_BMS | \
							      HRCW_MODCK_H0110)
#else
#define CONFIG_SYS_HRCW_MASTER		(HRCW_CIP | HRCW_ISB111 | HRCW_BMS)
#endif

/* no slaves so just fill with zeros */
#define CONFIG_SYS_HRCW_SLAVE1		0
#define CONFIG_SYS_HRCW_SLAVE2		0
#define CONFIG_SYS_HRCW_SLAVE3		0
#define CONFIG_SYS_HRCW_SLAVE4		0
#define CONFIG_SYS_HRCW_SLAVE5		0
#define CONFIG_SYS_HRCW_SLAVE6		0
#define CONFIG_SYS_HRCW_SLAVE7		0

#define CONFIG_SYS_IMMR		0xFFF00000

#define CONFIG_SYS_INIT_RAM_ADDR	CONFIG_SYS_IMMR
#define CONFIG_SYS_INIT_RAM_END	0x4000  /* End of used area in DPRAM    */
#define CONFIG_SYS_GBL_DATA_SIZE	128 /* size in bytes reserved for initial data*/
#define CONFIG_SYS_GBL_DATA_OFFSET	(CONFIG_SYS_INIT_RAM_END - CONFIG_SYS_GBL_DATA_SIZE)
#define CONFIG_SYS_INIT_SP_OFFSET	CONFIG_SYS_GBL_DATA_OFFSET

#define CONFIG_SYS_SDRAM_BASE		0x00000000
#define CONFIG_SYS_FLASH_BASE		CONFIG_SYS_FLASH0_BASE
#define CONFIG_SYS_MONITOR_BASE	TEXT_BASE
#define CONFIG_SYS_MONITOR_LEN		(256 << 10)	/* Reserve 256 kB for Monitor */
#define CONFIG_SYS_MALLOC_LEN		(128 << 10)	/* Reserve 128 kB for malloc()*/

#define BOOTFLAG_COLD		0x01	/* Normal Power-On: Boot from FLASH*/
#define BOOTFLAG_WARM		0x02	/* Software reboot                 */


#define CONFIG_SYS_HWINFO_OFFSET	0x0003FFC0	/* offset of HW Info block */
#define CONFIG_SYS_HWINFO_SIZE		0x00000040	/* size   of HW Info block */
#define CONFIG_SYS_HWINFO_MAGIC	0x54514D38	/* 'TQM8' */

#define CONFIG_SYS_CACHELINE_SIZE      32      /* For MPC8260 CPU              */
#if defined(CONFIG_CMD_KGDB)
# define CONFIG_SYS_CACHELINE_SHIFT	5	/* log base 2 of the above value */
#endif

#define CONFIG_SYS_HID0_INIT   (HID0_ICE|HID0_DCE|HID0_ICFI|HID0_DCI|\
				HID0_IFEM|HID0_ABE)
#define CONFIG_SYS_HID0_FINAL  (HID0_IFEM|HID0_ABE)
#define CONFIG_SYS_HID2        0

#define CONFIG_SYS_RMR         RMR_CSRE

#ifdef	CONFIG_BUSMODE_60x
#define CONFIG_SYS_BCR         (BCR_EBM|BCR_L2C|BCR_LETM|\
			 BCR_NPQM0|BCR_NPQM1|BCR_NPQM2)	/* 60x mode  */
#else
#define BCR_APD01	0x10000000
#define CONFIG_SYS_BCR		(BCR_APD01|BCR_ETM|BCR_LETM)	/* 8260 mode */
#endif

#if 0
#define CONFIG_SYS_SIUMCR      (SIUMCR_DPPC10|SIUMCR_APPC10)
#else
#define CONFIG_SYS_SIUMCR      (SIUMCR_DPPC00|SIUMCR_APPC10)
#endif


#if defined(CONFIG_WATCHDOG)
#define CONFIG_SYS_SYPCR       (SYPCR_SWTC|SYPCR_BMT|SYPCR_PBME|SYPCR_LBME|\
			 SYPCR_SWRI|SYPCR_SWP|SYPCR_SWE)
#else
#define CONFIG_SYS_SYPCR       (SYPCR_SWTC|SYPCR_BMT|SYPCR_PBME|SYPCR_LBME|\
			 SYPCR_SWRI|SYPCR_SWP)
#endif /* CONFIG_WATCHDOG */

#define CONFIG_SYS_TMCNTSC     (TMCNTSC_SEC|TMCNTSC_ALR|TMCNTSC_TCF|TMCNTSC_TCE)

#define CONFIG_SYS_PISCR       (PISCR_PS|PISCR_PTF|PISCR_PTE)

#define CONFIG_SYS_SCCR        0

#define CONFIG_SYS_RCCR        0


	/* Initialize SDRAM on local bus
	 */
#define CONFIG_SYS_INIT_LOCAL_SDRAM

#define SDRAM_MAX_SIZE	0x08000000	/* max. 128 MB		*/

#define CONFIG_SYS_GLOBAL_SDRAM_LIMIT	(512<<20)	/* less than 512 MB */
#define CONFIG_SYS_LOCAL_SDRAM_LIMIT	(128<<20)	/* less than 128 MB */

#define CONFIG_SYS_MPTPR       0x4000

#define CONFIG_SYS_MRS_OFFS	0x00000110


#define CONFIG_SYS_BR0_PRELIM  ((CONFIG_SYS_FLASH_BASE & BRx_BA_MSK)  |\
			 BRx_PS_64                      |\
			 BRx_MS_GPCM_P                  |\
			 BRx_V)

#define CONFIG_SYS_OR0_PRELIM  (MEG_TO_AM(CONFIG_SYS_FLASH_SIZE)      |\
			 ORxG_CSNT                      |\
			 ORxG_ACS_DIV1                  |\
			 ORxG_SCY_3_CLK                 |\
			 ORxG_EHTR                      |\
			 ORxG_TRLX)

	/* SDRAM on TQM8260 can have either 8 or 9 columns.
	 * The number affects configuration values.
	 */

#define CONFIG_SYS_PSRT        0x20
#define CONFIG_SYS_LSRT        0x20
#ifndef CONFIG_SYS_RAMBOOT
#define CONFIG_SYS_BR1_PRELIM  ((CONFIG_SYS_SDRAM_BASE & BRx_BA_MSK)  |\
			 BRx_PS_64                      |\
			 BRx_MS_SDRAM_P                 |\
			 BRx_V)

#define CONFIG_SYS_OR1_PRELIM	CONFIG_SYS_OR1_8COL


	/* SDRAM initialization values for 8-column chips
	 */
#define CONFIG_SYS_OR1_8COL    ((~(CONFIG_SYS_GLOBAL_SDRAM_LIMIT-1) & ORxS_SDAM_MSK) |\
			 ORxS_BPD_4                     |\
			 ORxS_ROWST_PBI1_A7             |\
			 ORxS_NUMR_12)

#define CONFIG_SYS_PSDMR_8COL  (PSDMR_PBI                      |\
			 PSDMR_SDAM_A15_IS_A5           |\
			 PSDMR_BSMA_A12_A14             |\
			 PSDMR_SDA10_PBI1_A8            |\
			 PSDMR_RFRC_7_CLK               |\
			 PSDMR_PRETOACT_2W              |\
			 PSDMR_ACTTORW_2W               |\
			 PSDMR_LDOTOPRE_1C              |\
			 PSDMR_WRC_2C                   |\
			 PSDMR_EAMUX                    |\
			 PSDMR_CL_2)

	/* SDRAM initialization values for 9-column chips
	 */
#define CONFIG_SYS_OR1_9COL    ((~(CONFIG_SYS_GLOBAL_SDRAM_LIMIT-1) & ORxS_SDAM_MSK) |\
			 ORxS_BPD_4                     |\
			 ORxS_ROWST_PBI1_A5             |\
			 ORxS_NUMR_13)

#define CONFIG_SYS_PSDMR_9COL  (PSDMR_PBI                      |\
			 PSDMR_SDAM_A16_IS_A5           |\
			 PSDMR_BSMA_A12_A14             |\
			 PSDMR_SDA10_PBI1_A7            |\
			 PSDMR_RFRC_7_CLK               |\
			 PSDMR_PRETOACT_2W              |\
			 PSDMR_ACTTORW_2W               |\
			 PSDMR_LDOTOPRE_1C              |\
			 PSDMR_WRC_2C                   |\
			 PSDMR_EAMUX                    |\
			 PSDMR_CL_2)

#ifdef CONFIG_SYS_INIT_LOCAL_SDRAM
#define CONFIG_SYS_BR2_PRELIM  ((SDRAM_BASE2_PRELIM & BRx_BA_MSK) |\
			 BRx_PS_32                      |\
			 BRx_MS_SDRAM_L                 |\
			 BRx_V)

#define CONFIG_SYS_OR2_PRELIM	CONFIG_SYS_OR2_8COL

#define SDRAM_BASE2_PRELIM	0x80000000

	/* SDRAM initialization values for 8-column chips
	 */
#define CONFIG_SYS_OR2_8COL    ((~(CONFIG_SYS_LOCAL_SDRAM_LIMIT-1) & ORxS_SDAM_MSK) |\
			 ORxS_BPD_4                     |\
			 ORxS_ROWST_PBI1_A8             |\
			 ORxS_NUMR_12)

#define CONFIG_SYS_LSDMR_8COL  (PSDMR_PBI                      |\
			 PSDMR_SDAM_A15_IS_A5           |\
			 PSDMR_BSMA_A13_A15             |\
			 PSDMR_SDA10_PBI1_A9            |\
			 PSDMR_RFRC_7_CLK               |\
			 PSDMR_PRETOACT_2W              |\
			 PSDMR_ACTTORW_2W               |\
			 PSDMR_BL                       |\
			 PSDMR_LDOTOPRE_1C              |\
			 PSDMR_WRC_2C                   |\
			 PSDMR_CL_2)

	/* SDRAM initialization values for 9-column chips
	 */
#define CONFIG_SYS_OR2_9COL    ((~(CONFIG_SYS_LOCAL_SDRAM_LIMIT-1) & ORxS_SDAM_MSK) |\
			 ORxS_BPD_4                     |\
			 ORxS_ROWST_PBI1_A6             |\
			 ORxS_NUMR_13)

#define CONFIG_SYS_LSDMR_9COL  (PSDMR_PBI                      |\
			 PSDMR_SDAM_A16_IS_A5           |\
			 PSDMR_BSMA_A13_A15             |\
			 PSDMR_SDA10_PBI1_A8            |\
			 PSDMR_RFRC_7_CLK               |\
			 PSDMR_PRETOACT_2W              |\
			 PSDMR_ACTTORW_2W               |\
			 PSDMR_BL                       |\
			 PSDMR_LDOTOPRE_1C              |\
			 PSDMR_WRC_2C                   |\
			 PSDMR_CL_2)

#endif /* CONFIG_SYS_INIT_LOCAL_SDRAM */

#endif /* CONFIG_SYS_RAMBOOT */

#define CONFIG_SYS_CAN0_BASE		0xc0000000
#define CONFIG_SYS_CAN1_BASE		0xc0008000
#define CONFIG_SYS_FIOX_BASE		0xc0010000
#define CONFIG_SYS_FDOHM_BASE		0xc0018000
#define CONFIG_SYS_EXTPROM_BASE	0xc2000000

#define CONFIG_SYS_CAN_SIZE		0x00000100
#define CONFIG_SYS_FIOX_SIZE		0x00000020
#define CONFIG_SYS_FDOHM_SIZE		0x00002000
#define CONFIG_SYS_EXTPROM_BANK_SIZE	0x01000000

#define EXT_EEPROM_MAX_FLASH_BANKS	0x02

#define CONFIG_SYS_CAN0_BR3   ((CONFIG_SYS_CAN0_BASE & BRx_BA_MSK)	|\
			BRx_PS_8			|\
			BRx_MS_UPMA			|\
			BRx_V)

#define CONFIG_SYS_CAN0_OR3   (P2SZ_TO_AM(CONFIG_SYS_CAN_SIZE)	|\
			ORxU_BI				|\
			ORxU_EHTR_4IDLE)

#define CONFIG_SYS_CAN1_BR4   ((CONFIG_SYS_CAN1_BASE & BRx_BA_MSK)	|\
			BRx_PS_8			|\
			BRx_MS_UPMA			|\
			BRx_V)

#define CONFIG_SYS_CAN1_OR4   (P2SZ_TO_AM(CONFIG_SYS_CAN_SIZE)	|\
			ORxU_BI				|\
			ORxU_EHTR_4IDLE)

#define CONFIG_SYS_EXTPROM_BR5 ((CONFIG_SYS_EXTPROM_BASE & BRx_BA_MSK)|\
			BRx_PS_32			|\
			BRx_MS_GPCM_P			|\
			BRx_V)

#define CONFIG_SYS_EXTPROM_OR5 (P2SZ_TO_AM(CONFIG_SYS_EXTPROM_BANK_SIZE)|\
			ORxG_CSNT			|\
			ORxG_ACS_DIV4			|\
			ORxG_SCY_5_CLK			|\
			ORxG_TRLX)

#define CONFIG_SYS_EXTPROM_BR6 (((CONFIG_SYS_EXTPROM_BASE + \
			CONFIG_SYS_EXTPROM_BANK_SIZE) & BRx_BA_MSK)|\
			BRx_PS_32			|\
			BRx_MS_GPCM_P			|\
			BRx_V)

#define CONFIG_SYS_EXTPROM_OR6 (P2SZ_TO_AM(CONFIG_SYS_EXTPROM_BANK_SIZE)|\
			ORxG_CSNT			|\
			ORxG_ACS_DIV4			|\
			ORxG_SCY_5_CLK			|\
			ORxG_TRLX)

#define CONFIG_SYS_FIOX_BR7   ((CONFIG_SYS_FIOX_BASE & BRx_BA_MSK)	|\
			BRx_PS_32			|\
			BRx_MS_GPCM_P			|\
			BRx_V)

#define CONFIG_SYS_FIOX_OR7   (P2SZ_TO_AM(CONFIG_SYS_FIOX_SIZE)	|\
			ORxG_ACS_DIV4			|\
			ORxG_SCY_5_CLK			|\
			ORxG_TRLX)

#define CONFIG_SYS_FDOHM_BR8  ((CONFIG_SYS_FDOHM_BASE & BRx_BA_MSK)	|\
			BRx_PS_16			|\
			BRx_MS_GPCM_P			|\
			BRx_V)

#define CONFIG_SYS_FDOHM_OR8  (P2SZ_TO_AM(CONFIG_SYS_FDOHM_SIZE)	|\
			ORxG_ACS_DIV4			|\
			ORxG_SCY_5_CLK			|\
			ORxG_TRLX)


/* FPGA configuration */
#define CONFIG_SYS_PD_FIOX_PROG	(1 << (31- 5))	/* PD  5 */
#define CONFIG_SYS_PD_FIOX_DONE	(1 << (31-28))	/* PD 28 */
#define CONFIG_SYS_PD_FIOX_INIT	(1 << (31-29))	/* PD 29 */

#define CONFIG_SYS_PD_FDOHM_PROG	(1 << (31- 4))	/* PD  4 */
#define CONFIG_SYS_PD_FDOHM_DONE	(1 << (31-26))	/* PD 26 */
#define CONFIG_SYS_PD_FDOHM_INIT	(1 << (31-27))	/* PD 27 */


#endif	/* __CONFIG_H */
