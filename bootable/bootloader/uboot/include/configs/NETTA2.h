


#ifndef __CONFIG_H
#define __CONFIG_H

#if !defined(CONFIG_NETTA2_VERSION) || CONFIG_NETTA2_VERSION > 2
#error Unsupported CONFIG_NETTA2 version
#endif


#define CONFIG_MPC870		1	/* This is a MPC885 CPU		*/
#define CONFIG_NETTA2		1	/* ...on a NetTA2 board		*/

#define	CONFIG_8xx_CONS_SMC1	1	/* Console is on SMC1		*/
#undef	CONFIG_8xx_CONS_SMC2
#undef	CONFIG_8xx_CONS_NONE

#define CONFIG_BAUDRATE		115200	/* console baudrate = 115kbps	*/

/* #define CONFIG_XIN		 10000000 */
#define CONFIG_XIN		 50000000
/* #define MPC8XX_HZ		120000000 */
#define MPC8XX_HZ		 66666666

#define CONFIG_8xx_GCLK_FREQ	MPC8XX_HZ

#if 0
#define CONFIG_BOOTDELAY	-1	/* autoboot disabled		*/
#else
#define CONFIG_BOOTDELAY	5	/* autoboot after 5 seconds	*/
#endif

#undef	CONFIG_CLOCKS_IN_MHZ	/* clocks NOT passsed to Linux in MHz */

#define CONFIG_PREBOOT	"echo;"

#undef	CONFIG_BOOTARGS
#define CONFIG_BOOTCOMMAND							\
	"tftpboot; "								\
	"setenv bootargs root=/dev/nfs rw nfsroot=${serverip}:${rootpath} "	\
	"ip=${ipaddr}:${serverip}:${gatewayip}:${netmask}:${hostname}::off; "	\
	"bootm"

#define CONFIG_SOURCE
#define CONFIG_LOADS_ECHO	0	/* echo off for serial download	*/
#undef	CONFIG_SYS_LOADS_BAUD_CHANGE		/* don't allow baudrate change	*/

#undef	CONFIG_WATCHDOG			/* watchdog disabled		*/

#undef	CONFIG_CAN_DRIVER		/* CAN Driver support disabled	*/

#define	CONFIG_STATUS_LED	1	/* Status LED enabled		*/
#define CONFIG_BOARD_SPECIFIC_LED	/* version has board specific leds */

#define CONFIG_BOOTP_SUBNETMASK
#define CONFIG_BOOTP_GATEWAY
#define CONFIG_BOOTP_HOSTNAME
#define CONFIG_BOOTP_BOOTPATH
#define CONFIG_BOOTP_BOOTFILESIZE
#define CONFIG_BOOTP_NISDOMAIN


#undef CONFIG_MAC_PARTITION
#undef CONFIG_DOS_PARTITION

#define	CONFIG_RTC_MPC8xx		/* use internal RTC of MPC8xx	*/

#define	CONFIG_NET_MULTI	1	/* the only way to get the FEC in */
#define	FEC_ENET		1	/* eth.c needs it that way... */
#undef CONFIG_SYS_DISCOVER_PHY
#define CONFIG_MII		1
#define CONFIG_MII_INIT		1
#define CONFIG_RMII		1	/* use RMII interface */

#define CONFIG_ETHER_ON_FEC1	1
#define CONFIG_FEC1_PHY		8	/* phy address of FEC */
#define CONFIG_FEC1_PHY_NORXERR 1

#define CONFIG_ETHER_ON_FEC2	1
#define CONFIG_FEC2_PHY		4
#define CONFIG_FEC2_PHY_NORXERR 1

#define CONFIG_ENV_OVERWRITE	1	/* allow modification of vendor params */


#include <config_cmd_default.h>

#define CONFIG_CMD_DHCP
#define CONFIG_CMD_PING
#define CONFIG_CMD_MII
#define CONFIG_CMD_CDP


#define CONFIG_BOARD_EARLY_INIT_F	1
#define CONFIG_MISC_INIT_R

#define	CONFIG_SYS_LONGHELP			/* undef to save memory		*/
#define	CONFIG_SYS_PROMPT	"=> "		/* Monitor Command Prompt	*/

#define CONFIG_SYS_HUSH_PARSER	1
#define CONFIG_SYS_PROMPT_HUSH_PS2	"> "

#if defined(CONFIG_CMD_KGDB)
#define	CONFIG_SYS_CBSIZE	1024		/* Console I/O Buffer Size	*/
#else
#define	CONFIG_SYS_CBSIZE	256		/* Console I/O Buffer Size	*/
#endif
#define	CONFIG_SYS_PBSIZE (CONFIG_SYS_CBSIZE+sizeof(CONFIG_SYS_PROMPT)+16) /* Print Buffer Size */
#define	CONFIG_SYS_MAXARGS	16		/* max number of command args	*/
#define CONFIG_SYS_BARGSIZE	CONFIG_SYS_CBSIZE	/* Boot Argument Buffer Size	*/

#define CONFIG_SYS_MEMTEST_START	0x0300000	/* memtest works on	*/
#define CONFIG_SYS_MEMTEST_END		0x0700000	/* 3 ... 7 MB in DRAM	*/

#define	CONFIG_SYS_LOAD_ADDR		0x100000	/* default load address	*/

#define	CONFIG_SYS_HZ		1000		/* decrementer freq: 1 ms ticks	*/

#define CONFIG_SYS_BAUDRATE_TABLE	{ 9600, 19200, 38400, 57600, 115200 }

#define CONFIG_SYS_IMMR		0xFF000000

#define CONFIG_SYS_INIT_RAM_ADDR	CONFIG_SYS_IMMR
#define	CONFIG_SYS_INIT_RAM_END	0x3000	/* End of used area in DPRAM	*/
#define	CONFIG_SYS_GBL_DATA_SIZE	64  /* size in bytes reserved for initial data */
#define CONFIG_SYS_GBL_DATA_OFFSET	(CONFIG_SYS_INIT_RAM_END - CONFIG_SYS_GBL_DATA_SIZE)
#define	CONFIG_SYS_INIT_SP_OFFSET	CONFIG_SYS_GBL_DATA_OFFSET

#define	CONFIG_SYS_SDRAM_BASE		0x00000000
#define CONFIG_SYS_FLASH_BASE		0x40000000
#if defined(DEBUG)
#define	CONFIG_SYS_MONITOR_LEN		(256 << 10)	/* Reserve 256 kB for Monitor	*/
#else
#define	CONFIG_SYS_MONITOR_LEN		(192 << 10)	/* Reserve 192 kB for Monitor	*/
#endif
#define CONFIG_SYS_MONITOR_BASE	CONFIG_SYS_FLASH_BASE
#define	CONFIG_SYS_MALLOC_LEN		(128 << 10)	/* Reserve 128 kB for malloc()	*/
#if CONFIG_NETTA2_VERSION == 2
#define CONFIG_SYS_FLASH_BASE4		0x40080000
#endif

#define CONFIG_SYS_RESET_ADDRESS   0x80000000

#define	CONFIG_SYS_BOOTMAPSZ		(8 << 20)	/* Initial Memory map for Linux	*/

#if CONFIG_NETTA2_VERSION == 1
#define CONFIG_SYS_MAX_FLASH_BANKS	1	/* max number of memory banks		*/
#elif CONFIG_NETTA2_VERSION == 2
#define CONFIG_SYS_MAX_FLASH_BANKS	2	/* max number of memory banks		*/
#endif
#define CONFIG_SYS_MAX_FLASH_SECT	8	/* max number of sectors on one chip	*/

#define CONFIG_SYS_FLASH_ERASE_TOUT	120000	/* Timeout for Flash Erase (in ms)	*/
#define CONFIG_SYS_FLASH_WRITE_TOUT	500	/* Timeout for Flash Write (in ms)	*/

#define	CONFIG_ENV_IS_IN_FLASH	1
#define CONFIG_ENV_SECT_SIZE	0x10000

#define	CONFIG_ENV_ADDR		(CONFIG_SYS_FLASH_BASE + 0x60000)
#define CONFIG_ENV_OFFSET		0
#define	CONFIG_ENV_SIZE		0x4000

#define CONFIG_ENV_ADDR_REDUND	(CONFIG_SYS_FLASH_BASE + 0x70000)
#define CONFIG_ENV_OFFSET_REDUND	0
#define CONFIG_ENV_SIZE_REDUND	CONFIG_ENV_SIZE

#define CONFIG_SYS_CACHELINE_SIZE	16	/* For all MPC8xx CPUs			*/
#if defined(CONFIG_CMD_KGDB)
#define CONFIG_SYS_CACHELINE_SHIFT	4	/* log base 2 of the above value	*/
#endif

#if defined(CONFIG_WATCHDOG)
#define CONFIG_SYS_SYPCR	(SYPCR_SWTC | SYPCR_BMT | SYPCR_BME | SYPCR_SWF | \
			 SYPCR_SWE  | SYPCR_SWRI| SYPCR_SWP)
#else
#define CONFIG_SYS_SYPCR	(SYPCR_SWTC | SYPCR_BMT | SYPCR_BME | SYPCR_SWF | SYPCR_SWP)
#endif

#ifndef	CONFIG_CAN_DRIVER
#define CONFIG_SYS_SIUMCR	(SIUMCR_DBGC00 | SIUMCR_DBPC00 | SIUMCR_MLRC01 | SIUMCR_FRC)
#else	/* we must activate GPL5 in the SIUMCR for CAN */
#define CONFIG_SYS_SIUMCR	(SIUMCR_DBGC11 | SIUMCR_DBPC00 | SIUMCR_MLRC01 | SIUMCR_FRC)
#endif	/* CONFIG_CAN_DRIVER */

#define CONFIG_SYS_TBSCR	(TBSCR_REFA | TBSCR_REFB | TBSCR_TBF)

#define CONFIG_SYS_RTCSC	(RTCSC_SEC | RTCSC_ALR | RTCSC_RTF| RTCSC_RTE)

#define CONFIG_SYS_PISCR	(PISCR_PS | PISCR_PITF)


#if CONFIG_XIN == 10000000

#if MPC8XX_HZ == 120000000
#define CONFIG_SYS_PLPRCR	((0 << PLPRCR_MFN_SHIFT) | (0 << PLPRCR_MFD_SHIFT) | \
			 (0 << PLPRCR_S_SHIFT) | (12 << PLPRCR_MFI_SHIFT) | (0 << PLPRCR_PDF_SHIFT) | \
			 PLPRCR_TEXPS)
#elif MPC8XX_HZ == 100000000
#define CONFIG_SYS_PLPRCR	((0 << PLPRCR_MFN_SHIFT) | (0 << PLPRCR_MFD_SHIFT) | \
			 (0 << PLPRCR_S_SHIFT) | (10 << PLPRCR_MFI_SHIFT) | (0 << PLPRCR_PDF_SHIFT) | \
			 PLPRCR_TEXPS)
#elif MPC8XX_HZ == 50000000
#define CONFIG_SYS_PLPRCR	((0 << PLPRCR_MFN_SHIFT) | (0 << PLPRCR_MFD_SHIFT) | \
			 (1 << PLPRCR_S_SHIFT) | (8 << PLPRCR_MFI_SHIFT) | (3 << PLPRCR_PDF_SHIFT) | \
			 PLPRCR_TEXPS)
#elif MPC8XX_HZ == 25000000
#define CONFIG_SYS_PLPRCR	((0 << PLPRCR_MFN_SHIFT) | (0 << PLPRCR_MFD_SHIFT) | \
			 (2 << PLPRCR_S_SHIFT) | (8 << PLPRCR_MFI_SHIFT) | (3 << PLPRCR_PDF_SHIFT) | \
			 PLPRCR_TEXPS)
#elif MPC8XX_HZ == 40000000
#define CONFIG_SYS_PLPRCR	((0 << PLPRCR_MFN_SHIFT) | (0 << PLPRCR_MFD_SHIFT) | \
			 (1 << PLPRCR_S_SHIFT) | (8 << PLPRCR_MFI_SHIFT) | (4 << PLPRCR_PDF_SHIFT) | \
			 PLPRCR_TEXPS)
#elif MPC8XX_HZ == 75000000
#define CONFIG_SYS_PLPRCR	((0 << PLPRCR_MFN_SHIFT) | (0 << PLPRCR_MFD_SHIFT) | \
			 (1 << PLPRCR_S_SHIFT) | (15 << PLPRCR_MFI_SHIFT) | (0 << PLPRCR_PDF_SHIFT) | \
			 PLPRCR_TEXPS)
#else
#error unsupported CPU freq for XIN = 10MHz
#endif

#elif CONFIG_XIN == 50000000

#if MPC8XX_HZ == 120000000
#define CONFIG_SYS_PLPRCR	((0 << PLPRCR_MFN_SHIFT) | (0 << PLPRCR_MFD_SHIFT) | \
			 (0 << PLPRCR_S_SHIFT) | (12 << PLPRCR_MFI_SHIFT) | (4 << PLPRCR_PDF_SHIFT) | \
			 PLPRCR_TEXPS)
#elif MPC8XX_HZ == 100000000
#define CONFIG_SYS_PLPRCR	((0 << PLPRCR_MFN_SHIFT) | (0 << PLPRCR_MFD_SHIFT) | \
			 (0 << PLPRCR_S_SHIFT) | (6 << PLPRCR_MFI_SHIFT) | (2 << PLPRCR_PDF_SHIFT) | \
			 PLPRCR_TEXPS)
#elif MPC8XX_HZ ==  66666666
#define CONFIG_SYS_PLPRCR	((0 << PLPRCR_MFN_SHIFT) | (0 << PLPRCR_MFD_SHIFT) | \
			 (1 << PLPRCR_S_SHIFT) | (8 << PLPRCR_MFI_SHIFT) | (2 << PLPRCR_PDF_SHIFT) | \
			 PLPRCR_TEXPS)
#else
#error unsupported CPU freq for XIN = 50MHz
#endif

#else

#error unsupported XIN freq
#endif



#define SCCR_MASK	SCCR_EBDF11
#if MPC8XX_HZ > 66666666
#define CONFIG_SYS_SCCR	(/* SCCR_TBS     | */ SCCR_CRQEN | \
			 SCCR_COM00   | SCCR_DFSYNC00 | SCCR_DFBRG00  | \
			 SCCR_DFNL000 | SCCR_DFNH000  | SCCR_DFLCD000 | \
			 SCCR_DFALCD00 | SCCR_EBDF01)
#else
#define CONFIG_SYS_SCCR	(/* SCCR_TBS     | */ SCCR_CRQEN | \
			 SCCR_COM00   | SCCR_DFSYNC00 | SCCR_DFBRG00  | \
			 SCCR_DFNL000 | SCCR_DFNH000  | SCCR_DFLCD000 | \
			 SCCR_DFALCD00)
#endif

/*#define	CONFIG_SYS_DER	0x2002000F*/
#define CONFIG_SYS_DER	0


#define FLASH_BASE0_PRELIM	0x40000000	/* FLASH bank #0	*/

#define CONFIG_SYS_REMAP_OR_AM		0x80000000	/* OR addr mask */
#define CONFIG_SYS_PRELIM_OR_AM	0xE0000000	/* OR addr mask */

/* FLASH timing: ACS = 11, TRLX = 0, CSNT = 1, SCY = 5, EHTR = 1	*/
#define CONFIG_SYS_OR_TIMING_FLASH	(OR_CSNT_SAM  | OR_BI | OR_SCY_5_CLK | OR_TRLX)

#define CONFIG_SYS_OR0_REMAP	(CONFIG_SYS_REMAP_OR_AM  | CONFIG_SYS_OR_TIMING_FLASH)
#define CONFIG_SYS_OR0_PRELIM	(CONFIG_SYS_PRELIM_OR_AM | CONFIG_SYS_OR_TIMING_FLASH)
#define CONFIG_SYS_BR0_PRELIM	((FLASH_BASE0_PRELIM & BR_BA_MSK) | BR_PS_8 | BR_V )

#if CONFIG_NETTA2_VERSION == 2

#define FLASH_BASE4_PRELIM	0x40080000	/* FLASH bank #1	*/

#define CONFIG_SYS_OR4_REMAP	(CONFIG_SYS_REMAP_OR_AM  | CONFIG_SYS_OR_TIMING_FLASH)
#define CONFIG_SYS_OR4_PRELIM	(CONFIG_SYS_PRELIM_OR_AM | CONFIG_SYS_OR_TIMING_FLASH)
#define CONFIG_SYS_BR4_PRELIM	((FLASH_BASE4_PRELIM & BR_BA_MSK) | BR_PS_8 | BR_V )

#endif

#define SDRAM_BASE3_PRELIM	0x00000000	/* SDRAM bank #0	*/
#define	SDRAM_MAX_SIZE		(256 << 20)	/* max 256MB per bank	*/

/* SDRAM timing: Multiplexed addresses, GPL5 output to GPL5_A (don't care)	*/
#define CONFIG_SYS_OR_TIMING_SDRAM	(OR_CSNT_SAM | OR_G5LS)

#define CONFIG_SYS_OR3_PRELIM	((0xFFFFFFFFLU & ~(SDRAM_MAX_SIZE - 1)) | CONFIG_SYS_OR_TIMING_SDRAM)
#define CONFIG_SYS_BR3_PRELIM	((SDRAM_BASE3_PRELIM & BR_BA_MSK) | BR_MS_UPMB | BR_PS_32 | BR_V)



#define CONFIG_SYS_MAMR_PTA		 234

#define CONFIG_SYS_MPTPR_2BK_4K	MPTPR_PTP_DIV16		/* setting for 2 banks	*/
#define CONFIG_SYS_MPTPR_1BK_4K	MPTPR_PTP_DIV32		/* setting for 1 bank	*/

/* refresh rate 7.8 us (= 64 ms / 8K = 31.2 / quad bursts) for 256 MBit		*/
#define CONFIG_SYS_MPTPR_2BK_8K	MPTPR_PTP_DIV8		/* setting for 2 banks	*/
#define CONFIG_SYS_MPTPR_1BK_8K	MPTPR_PTP_DIV16		/* setting for 1 bank	*/


/* 8 column SDRAM */
#define CONFIG_SYS_MAMR_8COL	((CONFIG_SYS_MAMR_PTA << MAMR_PTA_SHIFT)  | MAMR_PTAE	    |	\
			 MAMR_AMA_TYPE_0 | MAMR_DSA_1_CYCL | MAMR_G0CLA_A11 |	\
			 MAMR_RLFA_1X	 | MAMR_WLFA_1X	   | MAMR_TLFA_4X)

/* 9 column SDRAM */
#define CONFIG_SYS_MAMR_9COL	((CONFIG_SYS_MAMR_PTA << MAMR_PTA_SHIFT)  | MAMR_PTAE	    |	\
			 MAMR_AMA_TYPE_1 | MAMR_DSA_1_CYCL | MAMR_G0CLA_A10 |	\
			 MAMR_RLFA_1X	 | MAMR_WLFA_1X	   | MAMR_TLFA_4X)

#define	BOOTFLAG_COLD	0x01		/* Normal Power-On: Boot from FLASH	*/
#define BOOTFLAG_WARM	0x02		/* Software reboot			*/

#define CONFIG_LAST_STAGE_INIT		/* needed to reset the damn phys */

/****************************************************************/

#define DSP_SIZE	0x00010000	/* 64K */
#define NAND_SIZE	0x00010000	/* 64K */

#define DSP_BASE	0xF1000000
#define NAND_BASE	0xF1010000

/*****************************************************************************/

#define CONFIG_SYS_DIRECT_FLASH_TFTP

/*****************************************************************************/

#if CONFIG_NETTA2_VERSION == 1
#define STATUS_LED_BIT		0x00000008		/* bit 28 */
#elif CONFIG_NETTA2_VERSION == 2
#define STATUS_LED_BIT		0x00000080		/* bit 24 */
#endif

#define STATUS_LED_PERIOD	(CONFIG_SYS_HZ / 2)
#define STATUS_LED_STATE	STATUS_LED_BLINKING

#define STATUS_LED_ACTIVE	0		/* LED on for bit == 0	*/
#define STATUS_LED_BOOT		0		/* LED 0 used for boot status */

#ifndef __ASSEMBLY__

/* LEDs */

/* led_id_t is unsigned int mask */
typedef unsigned int led_id_t;

#define __led_toggle(_msk) \
	do { \
		((volatile immap_t *)CONFIG_SYS_IMMR)->im_cpm.cp_pedat ^= (_msk); \
	} while(0)

#define __led_set(_msk, _st) \
	do { \
		if ((_st)) \
			((volatile immap_t *)CONFIG_SYS_IMMR)->im_cpm.cp_pedat |= (_msk); \
		else \
			((volatile immap_t *)CONFIG_SYS_IMMR)->im_cpm.cp_pedat &= ~(_msk); \
	} while(0)

#define __led_init(msk, st) __led_set(msk, st)

#endif


#define CONFIG_SYS_CONSOLE_IS_IN_ENV		1
#define CONFIG_SYS_CONSOLE_OVERWRITE_ROUTINE	1
#define CONFIG_SYS_CONSOLE_ENV_OVERWRITE	1

/*************************************************************************************************/

/* use board specific hardware */
#undef	CONFIG_WATCHDOG			/* watchdog disabled		*/
#define CONFIG_HW_WATCHDOG

/*************************************************************************************************/

#define CONFIG_CDP_DEVICE_ID		20
#define CONFIG_CDP_DEVICE_ID_PREFIX	"NT"	/* netta2 */
#define CONFIG_CDP_PORT_ID		"eth%d"
#define CONFIG_CDP_CAPABILITIES		0x00000010
#define CONFIG_CDP_VERSION		"u-boot" " " U_BOOT_DATE " " U_BOOT_TIME
#define CONFIG_CDP_PLATFORM		"Intracom NetTA2"
#define CONFIG_CDP_TRIGGER		0x20020001
#define CONFIG_CDP_POWER_CONSUMPTION	4300	/* 90 mA @ 48V */
#define CONFIG_CDP_APPLIANCE_VLAN_TYPE	0x01	/* ipphone ? */

/*************************************************************************************************/

#define CONFIG_AUTO_COMPLETE	1

/*************************************************************************************************/

#define CONFIG_CRC32_VERIFY	1

/*************************************************************************************************/

#define CONFIG_HUSH_OLD_PARSER_COMPATIBLE	1

/*************************************************************************************************/
#endif	/* __CONFIG_H */
