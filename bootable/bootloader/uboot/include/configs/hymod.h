


#ifndef __CONFIG_H
#define __CONFIG_H


#define CONFIG_MPC8260		1	/* This is an MPC8260 CPU	*/
#define CONFIG_HYMOD		1	/* ...on a Hymod board		*/
#define CONFIG_CPM2		1	/* Has a CPM2 */

#define	CONFIG_MISC_INIT_F	1	/* Use misc_init_f()		*/

#define CONFIG_BOARD_POSTCLK_INIT	/* have board_postclk_init() function */

#undef	CONFIG_CONS_ON_SMC		/* define if console on SMC */
#define	CONFIG_CONS_ON_SCC		/* define if console on SCC */
#undef	CONFIG_CONS_NONE		/* define if console on something else*/
#define	CONFIG_CONS_INDEX	1	/* which serial channel for console */
#define	CONFIG_CONS_USE_EXTC		/* SMC/SCC use ext clock not brg_clk */
#define	CONFIG_CONS_EXTC_RATE	3686400	/* SMC/SCC ext clk rate in Hz */
#define	CONFIG_CONS_EXTC_PINSEL	0	/* pin select 0=CLK3/CLK9,1=CLK5/CLK15*/

#undef	CONFIG_ETHER_ON_SCC		/* define if ether on SCC	*/
#define	CONFIG_ETHER_ON_FCC		/* define if ether on FCC	*/
#undef	CONFIG_ETHER_NONE		/* define if ether on something else */
#define CONFIG_ETHER_INDEX	1	/* which channel for ether	*/
#define CONFIG_ETHER_LOOPBACK_TEST	/* add ether external loopback test */

#ifdef CONFIG_ETHER_ON_FCC

#if (CONFIG_ETHER_INDEX == 1)

# define CONFIG_SYS_CMXFCR_MASK	(CMXFCR_FC1|CMXFCR_RF1CS_MSK|CMXFCR_TF1CS_MSK)
# define CONFIG_SYS_CMXFCR_VALUE	(CMXFCR_RF1CS_CLK10|CMXFCR_TF1CS_CLK11)
# define CONFIG_SYS_CPMFCR_RAMTYPE	0
# define CONFIG_SYS_FCC_PSMR		(FCC_PSMR_FDE|FCC_PSMR_LPB)

# define MDIO_PORT		0		/* Port A */
# define MDIO_DECLARE		volatile ioport_t *iop = ioport_addr ( \
					(immap_t *) CONFIG_SYS_IMMR, MDIO_PORT )
# define MDC_DECLARE		MDIO_DECLARE

# define MDIO_DATA_PINMASK	0x00040000	/* Pin 13 */
# define MDIO_CLCK_PINMASK	0x00080000	/* Pin 12 */

#elif (CONFIG_ETHER_INDEX == 2)

# define CONFIG_SYS_CMXFCR_MASK	(CMXFCR_FC2|CMXFCR_RF2CS_MSK|CMXFCR_TF2CS_MSK)
# define CONFIG_SYS_CMXFCR_VALUE	(CMXFCR_RF2CS_CLK13|CMXFCR_TF2CS_CLK14)
# define CONFIG_SYS_CPMFCR_RAMTYPE	0
# define CONFIG_SYS_FCC_PSMR		(FCC_PSMR_FDE|FCC_PSMR_LPB)

# define MDIO_PORT		0		/* Port A */
# define MDIO_DECLARE		volatile ioport_t *iop = ioport_addr ( \
					(immap_t *) CONFIG_SYS_IMMR, MDIO_PORT )
# define MDC_DECLARE		MDIO_DECLARE

# define MDIO_DATA_PINMASK	0x00000040	/* Pin 25 */
# define MDIO_CLCK_PINMASK	0x00000080	/* Pin 24 */

#elif (CONFIG_ETHER_INDEX == 3)

# define CONFIG_SYS_CMXFCR_MASK	(CMXFCR_FC3|CMXFCR_RF3CS_MSK|CMXFCR_TF3CS_MSK)
# define CONFIG_SYS_CMXFCR_VALUE	(CMXFCR_RF3CS_CLK15|CMXFCR_TF3CS_CLK16)
# define CONFIG_SYS_CPMFCR_RAMTYPE	0
# define CONFIG_SYS_FCC_PSMR		(FCC_PSMR_FDE|FCC_PSMR_LPB)

# define MDIO_PORT		0		/* Port A */
# define MDIO_DECLARE		volatile ioport_t *iop = ioport_addr ( \
					(immap_t *) CONFIG_SYS_IMMR, MDIO_PORT )
# define MDC_DECLARE		MDIO_DECLARE

# define MDIO_DATA_PINMASK	0x00000100	/* Pin 23 */
# define MDIO_CLCK_PINMASK	0x00000200	/* Pin 22 */

#endif	/* CONFIG_ETHER_INDEX */

#define CONFIG_MII			/* MII PHY management	*/
#define CONFIG_BITBANGMII		/* bit-bang MII PHY management	*/

#define MDIO_ACTIVE	(iop->pdir |=  MDIO_DATA_PINMASK)
#define MDIO_TRISTATE	(iop->pdir &= ~MDIO_DATA_PINMASK)
#define MDIO_READ	((iop->pdat &  MDIO_DATA_PINMASK) != 0)

#define MDIO(bit)	if(bit) iop->pdat |=  MDIO_DATA_PINMASK; \
			else	iop->pdat &= ~MDIO_DATA_PINMASK

#define MDC(bit)	if(bit) iop->pdat |=  MDIO_CLCK_PINMASK; \
			else	iop->pdat &= ~MDIO_CLCK_PINMASK

#define MIIDELAY	udelay(1)

#endif	/* CONFIG_ETHER_ON_FCC */


/* other options */
#define CONFIG_HARD_I2C		1	/* To enable I2C hardware support	*/
#define CONFIG_DTT_ADM1021	1	/* ADM1021 temp sensor support */

/* system clock rate (CLKIN) - equal to the 60x and local bus speed */
#ifdef DEBUG
#define CONFIG_8260_CLKIN	33333333	/* in Hz */
#else
#define CONFIG_8260_CLKIN	66666666	/* in Hz */
#endif

#if defined(CONFIG_CONS_USE_EXTC)
#define CONFIG_BAUDRATE		115200
#else
#define CONFIG_BAUDRATE		9600
#endif

/* default ip addresses - these will be overridden */
#define CONFIG_IPADDR		192.168.1.1	/* hymod "boot" address */
#define CONFIG_SERVERIP		192.168.1.254	/* hymod "server" address */

#define CONFIG_LAST_STAGE_INIT

#define CONFIG_BOOTP_BOOTFILESIZE
#define CONFIG_BOOTP_BOOTPATH
#define CONFIG_BOOTP_GATEWAY
#define CONFIG_BOOTP_HOSTNAME


#include <config_cmd_default.h>

#define CONFIG_CMD_ASKENV
#define CONFIG_CMD_BSP
#define CONFIG_CMD_CACHE
#define CONFIG_CMD_CDP
#define CONFIG_CMD_DATE
#define CONFIG_CMD_DHCP
#define CONFIG_CMD_DIAG
#define CONFIG_CMD_DTT
#define CONFIG_CMD_EEPROM
#define CONFIG_CMD_ELF
#define CONFIG_CMD_FAT
#define CONFIG_CMD_I2C
#define CONFIG_CMD_IMMAP
#define CONFIG_CMD_IRQ
#define CONFIG_CMD_KGDB
#define CONFIG_CMD_MII
#define CONFIG_CMD_PING
#define CONFIG_CMD_PORTIO
#define CONFIG_CMD_REGINFO
#define CONFIG_CMD_SAVES
#define CONFIG_CMD_SDRAM
#define CONFIG_CMD_SNTP

#undef CONFIG_CMD_FPGA
#undef CONFIG_CMD_XIMG

#ifdef DEBUG
#define CONFIG_BOOTDELAY	-1	/* autoboot disabled		*/
#else
#define CONFIG_BOOTDELAY	5	/* autoboot after 5 seconds	*/
#define CONFIG_BOOT_RETRY_TIME 30	/* retry autoboot after 30 secs	*/
#define CONFIG_BOOT_RETRY_MIN	1	/* can go down to 1 second timeout */
#define CONFIG_AUTOBOOT_KEYED
#define CONFIG_AUTOBOOT_PROMPT		"Autobooting in %d seconds, " \
					"press <SPACE> to stop\n", bootdelay
#define CONFIG_AUTOBOOT_STOP_STR	" "
#undef CONFIG_AUTOBOOT_DELAY_STR
#define DEBUG_BOOTKEYS		0
#endif

#if defined(CONFIG_CMD_KGDB)
#undef	CONFIG_KGDB_ON_SMC		/* define if kgdb on SMC */
#define	CONFIG_KGDB_ON_SCC		/* define if kgdb on SCC */
#undef	CONFIG_KGDB_NONE		/* define if kgdb on something else */
#define CONFIG_KGDB_INDEX	2	/* which serial channel for kgdb */
#define	CONFIG_KGDB_USE_EXTC		/* SMC/SCC use ext clock not brg_clk */
#define	CONFIG_KGDB_EXTC_RATE	3686400	/* serial ext clk rate in Hz */
#define	CONFIG_KGDB_EXTC_PINSEL	0	/* pin select 0=CLK3/CLK9,1=CLK5/CLK15*/
# if defined(CONFIG_KGDB_USE_EXTC)
#define CONFIG_KGDB_BAUDRATE	115200	/* speed to run kgdb serial port at */
# else
#define CONFIG_KGDB_BAUDRATE	9600	/* speed to run kgdb serial port at */
# endif
#endif

#undef	CONFIG_WATCHDOG			/* disable platform specific watchdog */

#define CONFIG_RTC_PCF8563		/* use Philips PCF8563 RTC	*/

#undef	CONFIG_SYS_HYMOD_DBLEDS			/* walk mezz board LEDs */

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
#define CONFIG_SYS_MEMTEST_END		0x03c00000	/* 4 ... 60 MB in DRAM	*/

#define	CONFIG_SYS_LOAD_ADDR		0x100000	/* default load address	*/

#define	CONFIG_SYS_HZ		1000		/* decrementer freq: 1 ms ticks	*/

#define CONFIG_SYS_BAUDRATE_TABLE	{ 9600, 19200, 38400, 57600, 115200, 230400 }

#define	CONFIG_SYS_I2C_SPEED		50000
#define	CONFIG_SYS_I2C_SLAVE		0x7e

/* these are for the ST M24C02 2kbit serial i2c eeprom */
#define CONFIG_SYS_I2C_EEPROM_ADDR	0x50		/* base address */
#define CONFIG_SYS_I2C_EEPROM_ADDR_LEN	1		/* bytes of address */
/* mask of address bits that overflow into the "EEPROM chip address"    */
#define CONFIG_SYS_I2C_EEPROM_ADDR_OVERFLOW	0x07

#define CONFIG_SYS_EEPROM_PAGE_WRITE_BITS	4	/* 16 byte write page size */
#define CONFIG_SYS_EEPROM_PAGE_WRITE_DELAY_MS	10	/* and takes up to 10 msec */

#define CONFIG_SYS_I2C_MULTI_EEPROMS	1		/* hymod has two eeproms */

#define CONFIG_SYS_I2C_RTC_ADDR	0x51	/* philips PCF8563 RTC address */

#if 0
#define CONFIG_DTT_SENSORS		{ 0, 1 }
#else
#define CONFIG_DTT_SENSORS		{ 0 }
#endif

#define CONFIG_SYS_DTT_ADM1021		{ { 0x2a, 0x02, 0, 1, 0, 85, 0, } }


#ifdef DEBUG
#define CONFIG_SYS_HRCW_MASTER	(HRCW_BPS11|HRCW_CIP|HRCW_L2CPC01|HRCW_DPPC10|\
			 HRCW_ISB100|HRCW_BMS|HRCW_MMR11|HRCW_APPC10|\
			 HRCW_MODCK_H0010)
#else
#define CONFIG_SYS_HRCW_MASTER	(HRCW_BPS11|HRCW_CIP|HRCW_L2CPC01|HRCW_DPPC10|\
			 HRCW_ISB100|HRCW_BMS|HRCW_MMR11|HRCW_APPC10|\
			 HRCW_MODCK_H0101)
#endif
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

#define	CONFIG_SYS_SDRAM_BASE		0x00000000
#define CONFIG_SYS_FLASH_BASE		TEXT_BASE
#define	CONFIG_SYS_MONITOR_BASE	TEXT_BASE
#define CONFIG_SYS_FPGA_BASE		0x80000000
#define	CONFIG_SYS_MONITOR_LEN		(512 << 10)	/* Reserve 512 kB for Monitor*/
#define	CONFIG_SYS_MALLOC_LEN		(128 << 10)	/* Reserve 128 kB for malloc()*/

#define	CONFIG_SYS_BOOTMAPSZ		(8 << 20)	/* Initial Mem map for Linux*/

#define CONFIG_SYS_MAX_FLASH_BANKS	2	/* max num of memory banks	*/
#define CONFIG_SYS_MAX_FLASH_SECT	67	/* max num of sects on one chip	*/

#define CONFIG_SYS_FLASH_ERASE_TOUT	120000	/* Flash Erase Timeout (in ms)	*/
#define CONFIG_SYS_FLASH_WRITE_TOUT	500	/* Flash Write Timeout (in ms)	*/

#define	CONFIG_ENV_IS_IN_FLASH	1
#define	CONFIG_ENV_SIZE		0x40000	/* Total Size of Environment Sector */
#define CONFIG_ENV_SECT_SIZE	0x40000	/* see README - env sect real size */
#define	CONFIG_ENV_ADDR	(CONFIG_SYS_FLASH_BASE+CONFIG_SYS_MONITOR_LEN-CONFIG_ENV_SECT_SIZE)
#define	CONFIG_SYS_USE_PPCENV			/* Environment embedded in sect .ppcenv */

#define CONFIG_SYS_CACHELINE_SIZE	32	/* For MPC8260 CPU		*/
#if defined(CONFIG_CMD_KGDB)
#define CONFIG_SYS_CACHELINE_SHIFT	5	/* log base 2 of the above value*/
#endif

#define CONFIG_SYS_HID0_INIT	(HID0_ICE|HID0_DCE|HID0_ICFI|HID0_DCI|\
				HID0_IFEM|HID0_ABE)
#ifdef DEBUG
#define CONFIG_SYS_HID0_FINAL	0
#else
#define CONFIG_SYS_HID0_FINAL	(HID0_ICE|HID0_IFEM|HID0_ABE)
#endif
#define CONFIG_SYS_HID2	0

#ifdef DEBUG
#define CONFIG_SYS_RMR		0
#else
#define CONFIG_SYS_RMR		RMR_CSRE
#endif

#define CONFIG_SYS_BCR		(BCR_ETM)

#define CONFIG_SYS_SIUMCR	(SIUMCR_DPPC10|SIUMCR_L2CPC01|\
			 SIUMCR_APPC10|SIUMCR_MMR11)

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



/* 32 bit, read-write, GPCM on 60x bus */
#define	CONFIG_SYS_BR0_PRELIM	((CONFIG_SYS_FLASH_BASE&BRx_BA_MSK)|\
				BRx_PS_32|BRx_MS_GPCM_P|BRx_V)
/* up to 32 Mb */
#define	CONFIG_SYS_OR0_PRELIM	(MEG_TO_AM(32)|ORxG_CSNT|ORxG_ACS_DIV2|ORxG_SCY_10_CLK)


#define CONFIG_SYS_SDRAM_SIZE	64

/* 64 bit, read-write, SDRAM on 60x bus */
#define	CONFIG_SYS_BR2_PRELIM	((CONFIG_SYS_SDRAM_BASE&BRx_BA_MSK)|\
				BRx_PS_64|BRx_MS_SDRAM_P|BRx_V)
/* 64 Mb, 4 int banks per dev, row start addr bit = A6, 12 row addr lines */
#define	CONFIG_SYS_OR2_PRELIM	(MEG_TO_AM(CONFIG_SYS_SDRAM_SIZE)|\
				ORxS_BPD_4|ORxS_ROWST_PBI1_A6|ORxS_NUMR_12)


#define CONFIG_SYS_PSDMR	(PSDMR_PBI|PSDMR_SDAM_A16_IS_A5|\
				PSDMR_BSMA_A14_A16|PSDMR_SDA10_PBI1_A7|\
				PSDMR_RFRC_6_CLK|PSDMR_PRETOACT_2W|\
				PSDMR_ACTTORW_2W|PSDMR_LDOTOPRE_1C|\
				PSDMR_WRC_1C|PSDMR_CL_2)


#ifdef DEBUG
#define CONFIG_SYS_PSRT	39
#define CONFIG_SYS_MPTPR	MPTPR_PTP_DIV8
#else
#define CONFIG_SYS_PSRT	31
#define CONFIG_SYS_MPTPR	MPTPR_PTP_DIV32
#endif


/* all the bank sizes must be a power of two, greater or equal to 32768 */
#define FPGA_MAIN_CFG_BASE	(CONFIG_SYS_FPGA_BASE)
#define FPGA_MAIN_CFG_SIZE	32768
#define FPGA_MAIN_REG_BASE	(FPGA_MAIN_CFG_BASE + FPGA_MAIN_CFG_SIZE)
#define FPGA_MAIN_REG_SIZE	32768
#define FPGA_MAIN_PORT_BASE	(FPGA_MAIN_REG_BASE + FPGA_MAIN_REG_SIZE)
#define FPGA_MAIN_PORT_SIZE	32768
#define FPGA_MEZZ_CFG_BASE	(FPGA_MAIN_PORT_BASE + FPGA_MAIN_PORT_SIZE)
#define FPGA_MEZZ_CFG_SIZE	32768

/* 8 bit, read-write, UPMC */
#define	CONFIG_SYS_BR3_PRELIM	(FPGA_MAIN_CFG_BASE|BRx_PS_8|BRx_MS_UPMC|BRx_V)
/* up to 32Kbyte, burst inhibit */
#define	CONFIG_SYS_OR3_PRELIM	(P2SZ_TO_AM(FPGA_MAIN_CFG_SIZE)|ORxU_BI)

/* 32 bit, read-write, GPCM */
#define	CONFIG_SYS_BR4_PRELIM	(FPGA_MAIN_REG_BASE|BRx_PS_32|BRx_MS_GPCM_L|BRx_V)
/* up to 32Kbyte */
#define	CONFIG_SYS_OR4_PRELIM	(P2SZ_TO_AM(FPGA_MAIN_REG_SIZE))

/* 32 bit, read-write, UPMB */
#define	CONFIG_SYS_BR5_PRELIM	(FPGA_MAIN_PORT_BASE|BRx_PS_32|BRx_MS_UPMB|BRx_V)
/* up to 32Kbyte */
#define	CONFIG_SYS_OR5_PRELIM	(P2SZ_TO_AM(FPGA_MAIN_PORT_SIZE)|ORxU_BI)

/* 8 bit, write-only, UPMC */
#define	CONFIG_SYS_BR6_PRELIM	(FPGA_MEZZ_CFG_BASE|BRx_PS_8|BRx_MS_UPMC|BRx_V)
/* up to 32Kbyte, burst inhibit */
#define	CONFIG_SYS_OR6_PRELIM	(P2SZ_TO_AM(FPGA_MEZZ_CFG_SIZE)|ORxU_BI)

#define CONFIG_SYS_MBMR	(MxMR_BSEL|MxMR_OP_NORM)	/* XXX - needs more */

#define CONFIG_SYS_MCMR	(MxMR_BSEL|MxMR_DSx_2_CYCL)	/* XXX - needs more */


#define FPGA_MAIN_PROG_PORT	IOPIN_PORTA
#define FPGA_MAIN_PROG_PIN	4	/* PA4 */
#define FPGA_MAIN_INIT_PORT	IOPIN_PORTA
#define FPGA_MAIN_INIT_PIN	5	/* PA5 */
#define FPGA_MAIN_DONE_PORT	IOPIN_PORTA
#define FPGA_MAIN_DONE_PIN	6	/* PA6 */

#define FPGA_MEZZ_PROG_PORT	IOPIN_PORTA
#define FPGA_MEZZ_PROG_PIN	0	/* PA0 */
#define FPGA_MEZZ_INIT_PORT	IOPIN_PORTA
#define FPGA_MEZZ_INIT_PIN	1	/* PA1 */
#define FPGA_MEZZ_DONE_PORT	IOPIN_PORTA
#define FPGA_MEZZ_DONE_PIN	2	/* PA2 */
#define FPGA_MEZZ_ENABLE_PORT	IOPIN_PORTA
#define FPGA_MEZZ_ENABLE_PIN	3	/* PA3 */

#define FPGA_MAIN_IRQ		SIU_INT_IRQ2

#define	BOOTFLAG_COLD	0x01		/* Normal Power-On: Boot from FLASH*/
#define BOOTFLAG_WARM	0x02		/* Software reboot		*/

/* No command line, one static partition, whole device */
#undef CONFIG_CMD_MTDPARTS
#define CONFIG_JFFS2_DEV		"nor0"
#define CONFIG_JFFS2_PART_SIZE		0xFFFFFFFF
#define CONFIG_JFFS2_PART_OFFSET	0x00000000

/* mtdparts command line support */

#endif	/* __CONFIG_H */
