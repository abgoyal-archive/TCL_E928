


#ifndef __CONFIG_H
#define __CONFIG_H

#undef	CCM_80MHz			/* define for 80 MHz CPU only */


#define CONFIG_MPC860           1   /* This is a MPC860 CPU ... */
#define CONFIG_CCM              1   /* on a Card Controller Module  */
#define CONFIG_MISC_INIT_R	    /* Call misc_init_r() */
#define CONFIG_RESET_PHY_R	1   /* Call reset_phy() */

#define CONFIG_8xx_CONS_SMC1    1   /* Console is on SMC1       */
#undef  CONFIG_8xx_CONS_SMC2
#undef  CONFIG_8xx_CONS_NONE

/*  ENVIRONMENT */

#define CONFIG_BAUDRATE         19200         /* console baudrate in bps    */
#define CONFIG_BOOTDELAY        2             /* autoboot after 2 seconds   */

#define CONFIG_IPADDR           192.168.0.42
#define CONFIG_NETMASK          255.255.255.0
#define CONFIG_GATEWAYIP        0.0.0.0
#define CONFIG_SERVERIP         192.168.0.254

#define CONFIG_HOSTNAME         CCM

#define CONFIG_LOADADDR         40180000

#undef	CONFIG_BOOTARGS

#define CONFIG_BOOTCOMMAND      "setenv bootargs " \
				"mem=${mem} " \
				"root=/dev/ram rw ip=${ipaddr}:${serverip}:${gatewayip}:${netmask}:${hostname}::off " \
				"wt_8xx=timeout:3600; " \
				"bootm"

#define CONFIG_LOADS_ECHO	1	/* echo on for serial download	*/
#undef	CONFIG_SYS_LOADS_BAUD_CHANGE	/* don't allow baudrate change	*/

#define	CONFIG_WATCHDOG		1	/* watchdog enabled		*/

#undef	CONFIG_STATUS_LED		/* Status LED disabled		*/

#define	CONFIG_PRAM		512	/* reserve 512kB "protected RAM"*/

#define	CONFIG_RTC_MPC8xx		/* use internal RTC of MPC8xx	*/

#define	CONFIG_SPI			/* enable SPI driver		*/
#define	CONFIG_SPI_X			/* 16 bit EEPROM addressing	*/

#define CONFIG_SYS_SPI_INIT_OFFSET		0xB00

#define CONFIG_SYS_EEPROM_PAGE_WRITE_BITS	5	/* 32-byte page size	*/


#define CONFIG_MAC_PARTITION		/* nod used yet			*/
#define CONFIG_DOS_PARTITION

#define CONFIG_BOOTP_SUBNETMASK
#define CONFIG_BOOTP_GATEWAY
#define CONFIG_BOOTP_HOSTNAME
#define CONFIG_BOOTP_BOOTPATH
#define CONFIG_BOOTP_BOOTFILESIZE


#include <config_cmd_default.h>

#define CONFIG_CMD_BSP
#define CONFIG_CMD_DHCP
#define CONFIG_CMD_DATE
#define CONFIG_CMD_EEPROM
#define CONFIG_CMD_NFS
#define CONFIG_CMD_SNTP


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

#define CONFIG_SYS_MEMTEST_START	0x00100000	/* memtest works on	*/
#define CONFIG_SYS_MEMTEST_END		0x00F00000	/* 1 ... 15MB in DRAM	*/

#define	CONFIG_SYS_LOAD_ADDR		0x00100000	/* default load address	*/

/* Ethernet hardware configuration done using port pins */
#define CONFIG_SYS_PA_ETH_RESET	0x0200		/* PA  6	*/
#define CONFIG_SYS_PA_ETH_MDDIS	0x4000		/* PA  1	*/
#define CONFIG_SYS_PB_ETH_POWERDOWN	0x00000800	/* PB 20	*/
#define CONFIG_SYS_PB_ETH_CFG1		0x00000400	/* PB 21	*/
#define CONFIG_SYS_PB_ETH_CFG2		0x00000200	/* PB 22	*/
#define CONFIG_SYS_PB_ETH_CFG3		0x00000100	/* PB 23	*/

#define CONFIG_SYS_ETH_MDDIS_VALUE	0
#define CONFIG_SYS_ETH_CFG1_VALUE	1
#define CONFIG_SYS_ETH_CFG2_VALUE	1
#define CONFIG_SYS_ETH_CFG3_VALUE	1

/* PUMA configuration */
#define CONFIG_SYS_PC_PUMA_PROG	0x0200		/* PC  6        */
#define CONFIG_SYS_PC_PUMA_DONE	0x0008		/* PC 12	*/
#define CONFIG_SYS_PC_PUMA_INIT	0x0004		/* PC 13	*/

#define	CONFIG_SYS_HZ		1000		/* decrementer freq: 1 ms ticks	*/

#define CONFIG_SYS_BAUDRATE_TABLE	{ 9600, 19200, 38400, 57600, 115200 }

#define CONFIG_SYS_IMMR		0xF0000000

#define CONFIG_SYS_INIT_RAM_ADDR	CONFIG_SYS_IMMR
#define	CONFIG_SYS_INIT_RAM_END	0x2F00	/* End of used area in DPRAM	*/
#define	CONFIG_SYS_GBL_DATA_SIZE	64  /* size in bytes reserved for initial data */
#define CONFIG_SYS_GBL_DATA_OFFSET	(CONFIG_SYS_INIT_RAM_END - CONFIG_SYS_GBL_DATA_SIZE)
#define	CONFIG_SYS_INIT_SP_OFFSET	CONFIG_SYS_GBL_DATA_OFFSET

#define	CONFIG_SYS_RESET_ADDRESS	0xFEFFFFFF

#define	CONFIG_SYS_SDRAM_BASE		0x00000000
#define CONFIG_SYS_FLASH_BASE		0x40000000
#if defined(DEBUG)
#define	CONFIG_SYS_MONITOR_LEN		(256 << 10)	/* Reserve 256 kB for Monitor	*/
#else
#define	CONFIG_SYS_MONITOR_LEN		(192 << 10)	/* Reserve 192 kB for Monitor	*/
#endif
#define CONFIG_SYS_MONITOR_BASE	CONFIG_SYS_FLASH_BASE
#define	CONFIG_SYS_MALLOC_LEN		(128 << 10)	/* Reserve 128 kB for malloc()	*/

#define	CONFIG_SYS_BOOTMAPSZ		(8 << 20)	/* Initial Memory map for Linux	*/

#define CONFIG_SYS_MAX_FLASH_BANKS	2	/* max number of memory banks		*/
#define CONFIG_SYS_MAX_FLASH_SECT	67	/* max number of sectors on one chip	*/

#define CONFIG_SYS_FLASH_ERASE_TOUT	120000	/* Timeout for Flash Erase (in ms)	*/
#define CONFIG_SYS_FLASH_WRITE_TOUT	500	/* Timeout for Flash Write (in ms)	*/

#if 1
/* Start port with environment in flash; switch to SPI EEPROM later */
#define	CONFIG_ENV_IS_IN_FLASH	1
#define	CONFIG_ENV_OFFSET		0x8000	/*   Offset   of Environment Sector	*/
#define	CONFIG_ENV_SIZE		0x4000	/* Total Size of Environment Sector	*/

/* Address and size of Redundant Environment Sector	*/
#define CONFIG_ENV_OFFSET_REDUND	(CONFIG_ENV_OFFSET+CONFIG_ENV_SIZE)
#define CONFIG_ENV_SIZE_REDUND	(CONFIG_ENV_SIZE)
#else
/* Final version: environment in EEPROM */
#define CONFIG_ENV_IS_IN_EEPROM	1
#define CONFIG_ENV_OFFSET		2048
#define CONFIG_ENV_SIZE		2048
#endif

#define CONFIG_SYS_HWINFO_OFFSET	0x0003FFC0	/* offset of HW Info block */
#define CONFIG_SYS_HWINFO_SIZE		0x00000040	/* size   of HW Info block */
#define CONFIG_SYS_HWINFO_MAGIC	0x54514D38	/* 'TQM8' */

#define CONFIG_SYS_CACHELINE_SIZE	16	/* For all MPC8xx CPUs			*/
#define CONFIG_SYS_CACHELINE_SHIFT	4	/* log base 2 of the above value	*/

#if defined(CONFIG_WATCHDOG)
#define CONFIG_SYS_SYPCR	(SYPCR_SWTC | SYPCR_BMT | SYPCR_BME | SYPCR_SWF | \
			 SYPCR_SWE  | SYPCR_SWRI| SYPCR_SWP)
#else
#define CONFIG_SYS_SYPCR	(SYPCR_SWTC | SYPCR_BMT | SYPCR_BME | SYPCR_SWF | \
						  SYPCR_SWP)
#endif

#define CONFIG_SYS_SIUMCR	(SIUMCR_DBGC11 | SIUMCR_DBPC00 | SIUMCR_MLRC01)

#define CONFIG_SYS_TBSCR	(TBSCR_REFA | TBSCR_REFB | TBSCR_TBF)

#define CONFIG_SYS_RTCSC	(RTCSC_SEC | RTCSC_ALR | RTCSC_RTF| RTCSC_RTE)

#define CONFIG_SYS_PISCR	(PISCR_PS | PISCR_PITF)

#ifdef	CCM_80MHz	/* for 80 MHz, we use a 16 MHz clock * 5 */
#define CONFIG_SYS_PLPRCR							\
		( (5-1)<<PLPRCR_MF_SHIFT | PLPRCR_TEXPS | PLPRCR_TMIST )
#else			/* up to 50 MHz we use a 1:1 clock */
#define CONFIG_SYS_PLPRCR	(PLPRCR_SPLSS | PLPRCR_TEXPS | PLPRCR_TMIST)
#endif	/* CCM_80MHz */

#define SCCR_MASK	SCCR_EBDF11
#ifdef	CCM_80MHz	/* for 80 MHz, we use a 16 MHz clock * 5 */
#define CONFIG_SYS_SCCR	(/* SCCR_TBS  | */ \
			 SCCR_COM00   | SCCR_DFSYNC00 | SCCR_DFBRG00  | \
			 SCCR_DFNL000 | SCCR_DFNH000  | SCCR_DFLCD000 | \
			 SCCR_DFALCD00)
#else			/* up to 50 MHz we use a 1:1 clock */
#define CONFIG_SYS_SCCR	(SCCR_TBS     | \
			 SCCR_COM00   | SCCR_DFSYNC00 | SCCR_DFBRG00  | \
			 SCCR_DFNL000 | SCCR_DFNH000  | SCCR_DFLCD000 | \
			 SCCR_DFALCD00)
#endif	/* CCM_80MHz */

#define CONFIG_SYS_CPM_INTERRUPT	13	/* SIU_LEVEL6	*/

#define CONFIG_SYS_DER	0


#define FLASH_BASE0_PRELIM	0x40000000	/* FLASH bank #0	*/
#define FLASH_BASE1_PRELIM	0x60000000	/* FLASH bank #0	*/

#define CONFIG_SYS_REMAP_OR_AM		0x80000000	/* OR addr mask */
#define CONFIG_SYS_PRELIM_OR_AM	0xE0000000	/* OR addr mask */

/* FLASH timing: ACS = 11, TRLX = 0, CSNT = 1, SCY = 5, EHTR = 1	*/
#define CONFIG_SYS_OR_TIMING_FLASH	(OR_CSNT_SAM  | OR_ACS_DIV2 | OR_BI | \
				 OR_SCY_5_CLK | OR_EHTR)

#define CONFIG_SYS_OR0_REMAP	(CONFIG_SYS_REMAP_OR_AM  | CONFIG_SYS_OR_TIMING_FLASH)
#define CONFIG_SYS_OR0_PRELIM	(CONFIG_SYS_PRELIM_OR_AM | CONFIG_SYS_OR_TIMING_FLASH)
#define CONFIG_SYS_BR0_PRELIM	((FLASH_BASE0_PRELIM & BR_BA_MSK) | BR_V )

#define CONFIG_SYS_OR1_REMAP	CONFIG_SYS_OR0_REMAP
#define CONFIG_SYS_OR1_PRELIM	CONFIG_SYS_OR0_PRELIM
#define CONFIG_SYS_BR1_PRELIM	((FLASH_BASE1_PRELIM & BR_BA_MSK) | BR_V )

#define SDRAM_BASE2_PRELIM	0x00000000	/* SDRAM bank #0	*/
#define SDRAM_BASE3_PRELIM	0x20000000	/* SDRAM bank #1	*/
#define	SDRAM_MAX_SIZE		0x04000000	/* max 64 MB per bank	*/

/* SDRAM timing: Multiplexed addresses, GPL5 output to GPL5_A (don't care)	*/
#define CONFIG_SYS_OR_TIMING_SDRAM	0x00000A00

#define CONFIG_SYS_OR2_PRELIM	(CONFIG_SYS_PRELIM_OR_AM | CONFIG_SYS_OR_TIMING_SDRAM )
#define CONFIG_SYS_BR2_PRELIM	((SDRAM_BASE2_PRELIM & BR_BA_MSK) | BR_MS_UPMA | BR_V )

#define	CONFIG_SYS_CAN_BASE		0xC0000000	/* CAN mapped at 0xC0000000	*/
#define CONFIG_SYS_CAN_OR_AM		0xFFFF8000	/* 32 kB address mask		*/
#define CONFIG_SYS_OR3_CAN		(CONFIG_SYS_CAN_OR_AM | OR_G5LA | OR_BI)
#define CONFIG_SYS_BR3_CAN		((CONFIG_SYS_CAN_BASE & BR_BA_MSK) | \
					BR_PS_8 | BR_MS_UPMB | BR_V )

#define PUMA_CONF_BASE		0x10100000	/* PUMA Config */
#define PUMA_CONF_OR_AM		0xFFFF8000	/* 32 kB */
#define	PUMA_CONF_LOAD_TIMING	(OR_ACS_DIV2	 | OR_SCY_2_CLK)
#define PUMA_CONF_READ_TIMING	(OR_G5LA | OR_BI | OR_SCY_2_CLK)

#define PUMA_CONF_BR_LOAD	((PUMA_CONF_BASE & BR_BA_MSK) | \
					BR_PS_8  | BR_MS_UPMB | BR_V)
#define PUMA_CONF_OR_LOAD	(PUMA_CONF_OR_AM | PUMA_CONF_LOAD_TIMING)

#define PUMA_CONF_BR_READ	((PUMA_CONF_BASE & BR_BA_MSK) | BR_PS_16 | BR_V)
#define PUMA_CONF_OR_READ	(PUMA_CONF_OR_AM | PUMA_CONF_READ_TIMING)

#define CONFIG_SYS_BR4_PRELIM		PUMA_CONF_BR_READ
#define CONFIG_SYS_OR4_PRELIM		PUMA_CONF_OR_READ

#define PUMA_SMA8_BASE		0x10200000	/* PUMA SMA Bus 8 Bit */
#define PUMA_SMA8_OR_AM		0xFFE00000	/* 2 MB */
#define PUMA_SMA8_TIMING	(OR_BI | OR_SCY_0_CLK | OR_EHTR)

#define CONFIG_SYS_BR5_PRELIM		((PUMA_SMA8_BASE & BR_BA_MSK) | BR_PS_8 | BR_V)
#define CONFIG_SYS_OR5_PRELIM		(PUMA_SMA8_OR_AM | PUMA_SMA8_TIMING | OR_SETA)

#define PUMA_SMA16_BASE		0x10600000	/* PUMA SMA Bus 16 Bit */
#define PUMA_SMA16_OR_AM	0xFFE00000	/* 2 MB */
#define PUMA_SMA16_TIMING	(OR_BI | OR_SCY_0_CLK | OR_EHTR)

#define CONFIG_SYS_BR6_PRELIM		((PUMA_SMA16_BASE & BR_BA_MSK) | BR_PS_16 | BR_V)
#define CONFIG_SYS_OR6_PRELIM		(PUMA_SMA16_OR_AM | PUMA_SMA16_TIMING | OR_SETA)

#define PUMA_FLASH_BASE		0x10A00000	/* PUMA external Flash */
#define PUMA_FLASH_OR_AM	0xFE000000	/* 32 MB */
#define PUMA_FLASH_TIMING	(OR_BI | OR_SCY_0_CLK | OR_EHTR)

#define CONFIG_SYS_BR7_PRELIM		((PUMA_FLASH_BASE & BR_BA_MSK) | BR_PS_16 | BR_V)
#define CONFIG_SYS_OR7_PRELIM		(PUMA_FLASH_OR_AM | PUMA_FLASH_TIMING | OR_SETA)



/* periodic timer for refresh */
#define CONFIG_SYS_MAMR_PTA	97		/* start with divider for 100 MHz	*/

/* refresh rate 15.6 us (= 64 ms / 4K = 62.4 / quad bursts) for <= 128 MBit	*/
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

#endif	/* __CONFIG_H */
