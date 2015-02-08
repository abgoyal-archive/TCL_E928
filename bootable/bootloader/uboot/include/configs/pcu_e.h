


#ifndef __CONFIG_H
#define __CONFIG_H

#define	PCU_E_WITH_SWAPPED_CS	1


#define CONFIG_MPC860		1	/* This is a MPC860T CPU	*/
#define CONFIG_MPC860T		1
#define CONFIG_PCU_E		1	/* ...on a PCU E board		*/

#define CONFIG_MISC_INIT_R	1	/* Call misc_init_r()		*/
#define CONFIG_RESET_PHY_R	1	/* Call reset_phy()		*/

#define	CONFIG_8xx_CONS_SMC1	1	/* Console is on SMC1		*/

#define CONFIG_BAUDRATE		9600
#if 0
#define CONFIG_BOOTDELAY	-1	/* autoboot disabled		*/
#else
#define CONFIG_BOOTDELAY	5	/* autoboot after 5 seconds	*/
#endif

#define	CONFIG_CLOCKS_IN_MHZ	1	/* clocks passsed to Linux in MHz */

#undef	CONFIG_BOOTARGS
#define CONFIG_BOOTCOMMAND							\
	"bootp;"								\
	"setenv bootargs root=/dev/nfs rw nfsroot=${serverip}:${rootpath} "	\
	"ip=${ipaddr}:${serverip}:${gatewayip}:${netmask}:${hostname}::off;"	\
	"bootm"

#define CONFIG_LOADS_ECHO	1	/* echo on for serial download	*/
#undef	CONFIG_SYS_LOADS_BAUD_CHANGE		/* don't allow baudrate change	*/

#undef	CONFIG_WATCHDOG			/* watchdog disabled		*/

#define	CONFIG_STATUS_LED	1	/* Status LED enabled		*/

#define	CONFIG_PRAM		2048	/* reserve 2 MB "protected RAM"	*/

#define	CONFIG_RTC_MPC8xx		/* use internal RTC of MPC8xx	*/

#define	CONFIG_SPI			/* enable SPI driver		*/
#define	CONFIG_SPI_X			/* 16 bit EEPROM addressing	*/

#define CONFIG_HARD_I2C		1	/* I2C with hardware support	*/
#define CONFIG_SYS_I2C_SPEED		400000	/* I2C speed and slave address	*/
#define CONFIG_SYS_I2C_SLAVE		0x7F


#define CONFIG_SYS_SPI_INIT_OFFSET		0xB00


#include <config_cmd_default.h>
#define CONFIG_CMD_BSP
#define CONFIG_CMD_DATE
#define CONFIG_CMD_DHCP
#define CONFIG_CMD_EEPROM
#define CONFIG_CMD_NFS
#define CONFIG_CMD_SNTP


#define CONFIG_BOOTP_SUBNETMASK
#define CONFIG_BOOTP_HOSTNAME
#define CONFIG_BOOTP_BOOTPATH
#define CONFIG_BOOTP_BOOTFILESIZE


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

#define	CONFIG_SYS_PIO_MODE		0	/* IDE interface in PIO Mode 0	*/

/* Ethernet hardware configuration done using port pins */
#define CONFIG_SYS_PB_ETH_RESET	0x00000020		/* PB 26	*/
#if PCU_E_WITH_SWAPPED_CS /* XXX */
#define CONFIG_SYS_PA_ETH_MDDIS	0x4000			/* PA  1	*/
#define CONFIG_SYS_PB_ETH_POWERDOWN	0x00000800		/* PB 20	*/
#define CONFIG_SYS_PB_ETH_CFG1		0x00000400		/* PB 21	*/
#define CONFIG_SYS_PB_ETH_CFG2		0x00000200		/* PB 22	*/
#define CONFIG_SYS_PB_ETH_CFG3		0x00000100		/* PB 23	*/
#else /* XXX */
#define CONFIG_SYS_PB_ETH_MDDIS	0x00000010		/* PB 27	*/
#define CONFIG_SYS_PB_ETH_POWERDOWN	0x00000100		/* PB 23	*/
#define CONFIG_SYS_PB_ETH_CFG1		0x00000200		/* PB 22	*/
#define CONFIG_SYS_PB_ETH_CFG2		0x00000400		/* PB 21	*/
#define CONFIG_SYS_PB_ETH_CFG3		0x00000800		/* PB 20	*/
#endif /* XXX */

#define CONFIG_SYS_ETH_MDDIS_VALUE	0
#define CONFIG_SYS_ETH_CFG1_VALUE	1
#define CONFIG_SYS_ETH_CFG2_VALUE	1
#define CONFIG_SYS_ETH_CFG3_VALUE	1

/* PUMA configuration */
#if PCU_E_WITH_SWAPPED_CS /* XXX */
#define CONFIG_SYS_PB_PUMA_PROG	0x00000010		/* PB 27	*/
#else /* XXX */
#define CONFIG_SYS_PA_PUMA_PROG	0x4000			/* PA  1	*/
#endif /* XXX */
#define CONFIG_SYS_PC_PUMA_DONE	0x0008			/* PC 12	*/
#define CONFIG_SYS_PC_PUMA_INIT	0x0004			/* PC 13	*/

#define	CONFIG_SYS_HZ		1000		/* decrementer freq: 1 ms ticks	*/

#define CONFIG_SYS_BAUDRATE_TABLE	{ 9600, 19200, 38400, 57600, 115200 }

#define CONFIG_SYS_IMMR		0xFE000000

#define CONFIG_SYS_INIT_RAM_ADDR	CONFIG_SYS_IMMR
#define	CONFIG_SYS_INIT_RAM_END	0x2F00	/* End of used area in DPRAM	*/
#define	CONFIG_SYS_GBL_DATA_SIZE	64  /* size in bytes reserved for initial data */
#define CONFIG_SYS_GBL_DATA_OFFSET	(CONFIG_SYS_INIT_RAM_END - CONFIG_SYS_GBL_DATA_SIZE)
#define	CONFIG_SYS_INIT_SP_OFFSET	CONFIG_SYS_GBL_DATA_OFFSET

#define	CONFIG_SYS_RESET_ADDRESS	0xFEFFFFFF

#define	CONFIG_SYS_SDRAM_BASE		0x00000000
/* this is an ugly hack needed because of the silly non-constant address map */
#define CONFIG_SYS_FLASH_BASE		(0-flash_info[0].size-flash_info[1].size)

#if defined(DEBUG)
#define	CONFIG_SYS_MONITOR_LEN		(256 << 10)	/* Reserve 256 kB for Monitor	*/
#else
#define	CONFIG_SYS_MONITOR_LEN		(192 << 10)	/* Reserve 192 kB for Monitor	*/
#endif
#define CONFIG_SYS_MONITOR_BASE	TEXT_BASE
#define	CONFIG_SYS_MALLOC_LEN		(128 << 10)	/* Reserve 128 kB for malloc()	*/

#define	CONFIG_SYS_BOOTMAPSZ		(8 << 20)	/* Initial Memory map for Linux	*/
#define CONFIG_SYS_MAX_FLASH_BANKS	2	/* max number of memory banks		*/
#define CONFIG_SYS_MAX_FLASH_SECT	160	/* max number of sectors on one chip	*/

#define CONFIG_SYS_FLASH_ERASE_TOUT	180000	/* Timeout for Flash Erase (in ms)	*/
#define CONFIG_SYS_FLASH_WRITE_TOUT	1000	/* Timeout for Flash Write (in ms)	*/

#if 0
/* Start port with environment in flash; switch to SPI EEPROM later */
#define	CONFIG_ENV_IS_IN_FLASH	1
#define CONFIG_ENV_SIZE		0x2000	/* Total Size of Environment		*/
#define CONFIG_ENV_ADDR	    0xFFFFE000	/* Address    of Environment Sector	*/
#define CONFIG_ENV_SECT_SIZE	0x2000	/* use the top-most 8k boot sector	*/
#else
/* Final version: environment in EEPROM */
#define CONFIG_ENV_IS_IN_EEPROM	1
#define CONFIG_SYS_I2C_EEPROM_ADDR	0
#define CONFIG_SYS_I2C_EEPROM_ADDR_LEN	2
#define CONFIG_ENV_OFFSET		1024
#define CONFIG_ENV_SIZE		1024
#endif

#define CONFIG_SYS_CACHELINE_SIZE	16	/* For all MPC8xx CPUs			*/
#define CONFIG_SYS_CACHELINE_SHIFT	4	/* log base 2 of the above value	*/
#define CONFIG_SYS_DELAYED_ICACHE	1	/* enable ICache not before
						 * running in RAM.
						 */

#if defined(CONFIG_WATCHDOG)
#define CONFIG_SYS_SYPCR	(SYPCR_SWTC | SYPCR_BMT | SYPCR_BME | SYPCR_SWF | \
			 SYPCR_SWE  | SYPCR_SWRI| SYPCR_SWP)
#else
#define CONFIG_SYS_SYPCR	(SYPCR_SWTC | SYPCR_BMT | SYPCR_BME | SYPCR_SWF | SYPCR_SWP)
#endif

/* => 0x70600200 */
#define CONFIG_SYS_SIUMCR	(SIUMCR_EARP7 | SIUMCR_DBGC11 | SIUMCR_AEME)

#define CONFIG_SYS_TBSCR	(TBSCR_REFA | TBSCR_REFB | TBSCR_TBF)

#define CONFIG_SYS_PISCR	(PISCR_PS | PISCR_PITF)

/* 0x00004080 */
#define	CONFIG_SYS_PLPRCR_MF	0	/* (0+1) * 50 = 50 MHz Clock */
#define CONFIG_SYS_PLPRCR							\
		(	(CONFIG_SYS_PLPRCR_MF << PLPRCR_MF_SHIFT) |		\
			PLPRCR_SPLSS | PLPRCR_TEXPS | PLPRCR_TMIST |	\
			/*PLPRCR_CSRC|*/ PLPRCR_LPM_NORMAL |		\
			PLPRCR_CSR    /*| PLPRCR_LOLRE|PLPRCR_FIOPD*/	\
		)

#define	CONFIG_8xx_GCLK_FREQ	((CONFIG_SYS_PLPRCR_MF+1)*50000000)

#define SCCR_MASK	SCCR_EBDF11
/* 0x01800000 */
#define CONFIG_SYS_SCCR	(SCCR_COM00	| /*SCCR_TBS|*/		\
			 SCCR_RTDIV	|   SCCR_RTSEL	  |	\
			 /*SCCR_CRQEN|*/  /*SCCR_PRQEN|*/	\
			 SCCR_EBDF00 |   SCCR_DFSYNC00 |	\
			 SCCR_DFBRG00	|   SCCR_DFNL000  |	\
			 SCCR_DFNH000	|   SCCR_DFLCD100 |	\
			 SCCR_DFALCD01)

/* 0x00C3 => 0x0003 */
#define CONFIG_SYS_RTCSC	(RTCSC_SEC | RTCSC_ALR | RTCSC_RTF| RTCSC_RTE)


#define CONFIG_SYS_RCCR 0x0000

#define CONFIG_SYS_RMDS 0

#define CONFIG_SYS_CPM_INTERRUPT	13	/* SIU_LEVEL6	*/

#define CONFIG_SYS_DER	0


#define FLASH_BASE0_PRELIM	0xFF800000	/* FLASH bank #0	*/
#if PCU_E_WITH_SWAPPED_CS /* XXX */
#define FLASH_BASE6_PRELIM	0xFF000000	/* FLASH bank #1	*/
#else /* XXX */
#define FLASH_BASE1_PRELIM	0xFF000000	/* FLASH bank #1	*/
#endif /* XXX */

#define CONFIG_SYS_REMAP_OR_AM		0xFF800000	/* OR addr mask */
#define CONFIG_SYS_PRELIM_OR_AM	0xFF800000	/* OR addr mask */

/* FLASH timing: CSNT = 0, ACS = 00, SCY = 8, EHTR = 1			*/
#define CONFIG_SYS_OR_TIMING_FLASH	(OR_SCY_8_CLK | OR_EHTR)

#define CONFIG_SYS_OR0_REMAP	( CONFIG_SYS_REMAP_OR_AM | OR_ACS_DIV1 | OR_BI | \
				CONFIG_SYS_OR_TIMING_FLASH)
#define CONFIG_SYS_OR0_PRELIM	(CONFIG_SYS_PRELIM_OR_AM | OR_ACS_DIV1 | OR_BI | \
				CONFIG_SYS_OR_TIMING_FLASH)
/* 16 bit, bank valid */
#define CONFIG_SYS_BR0_PRELIM	((FLASH_BASE0_PRELIM & BR_BA_MSK) | BR_PS_16 | BR_V )

#if PCU_E_WITH_SWAPPED_CS /* XXX */
#define CONFIG_SYS_OR6_REMAP	CONFIG_SYS_OR0_REMAP
#define CONFIG_SYS_OR6_PRELIM	CONFIG_SYS_OR0_PRELIM
#define CONFIG_SYS_BR6_PRELIM	((FLASH_BASE6_PRELIM & BR_BA_MSK) | BR_PS_16 | BR_V )
#else /* XXX */
#define CONFIG_SYS_OR1_REMAP	CONFIG_SYS_OR0_REMAP
#define CONFIG_SYS_OR1_PRELIM	CONFIG_SYS_OR0_PRELIM
#define CONFIG_SYS_BR1_PRELIM	((FLASH_BASE1_PRELIM & BR_BA_MSK) | BR_PS_16 | BR_V )
#endif /* XXX */

#if PCU_E_WITH_SWAPPED_CS /* XXX */
#define SDRAM_BASE5_PRELIM	0x00000000	/* SDRAM bank */
#else /* XXX */
#define SDRAM_BASE2_PRELIM	0x00000000	/* SDRAM bank */
#endif /* XXX */
#define SDRAM_PRELIM_OR_AM	0xF8000000	/* map 128 MB (>SDRAM_MAX_SIZE!) */
#define SDRAM_TIMING		OR_CSNT_SAM	/* SDRAM-Timing */

#define SDRAM_MAX_SIZE		0x04000000	/* max 64 MB SDRAM */

#if PCU_E_WITH_SWAPPED_CS /* XXX */
#define CONFIG_SYS_OR5_PRELIM	(SDRAM_PRELIM_OR_AM | SDRAM_TIMING )
#define CONFIG_SYS_BR5_PRELIM	((SDRAM_BASE5_PRELIM & BR_BA_MSK) | BR_MS_UPMA | BR_V )
#else /* XXX */
#define CONFIG_SYS_OR2_PRELIM	(SDRAM_PRELIM_OR_AM | SDRAM_TIMING )
#define CONFIG_SYS_BR2_PRELIM	((SDRAM_BASE2_PRELIM & BR_BA_MSK) | BR_MS_UPMA | BR_V )
#endif /* XXX */

#define CAN_CTRLR_BASE		0x10000000	/* CAN Controller */
#define CAN_CTRLR_OR_AM		0xFFFF8000	/* 32 kB */
#define CAN_CTRLR_TIMING	(OR_BI | OR_SCY_8_CLK | OR_SETA | OR_EHTR)

#if PCU_E_WITH_SWAPPED_CS /* XXX */
#define CONFIG_SYS_BR4_PRELIM		((CAN_CTRLR_BASE & BR_BA_MSK) | BR_PS_8 | BR_V)
#define CONFIG_SYS_OR4_PRELIM		(CAN_CTRLR_OR_AM | CAN_CTRLR_TIMING)
#else /* XXX */
#define CONFIG_SYS_BR3_PRELIM		((CAN_CTRLR_BASE & BR_BA_MSK) | BR_PS_8 | BR_V)
#define CONFIG_SYS_OR3_PRELIM		(CAN_CTRLR_OR_AM | CAN_CTRLR_TIMING)
#endif /* XXX */

#define PUMA_CONF_BASE		0x10100000	/* PUMA Config */
#define PUMA_CONF_OR_AM		0xFFFF8000	/* 32 kB */
#define	PUMA_CONF_LOAD_TIMING	(OR_ACS_DIV2	 | OR_SCY_3_CLK)
#define PUMA_CONF_READ_TIMING	(OR_G5LA | OR_BI | OR_SCY_3_CLK)

#define PUMA_CONF_BR_LOAD	((PUMA_CONF_BASE & BR_BA_MSK) | \
					BR_PS_16 | BR_MS_UPMB | BR_V)
#define PUMA_CONF_OR_LOAD	(PUMA_CONF_OR_AM | PUMA_CONF_LOAD_TIMING)

#define PUMA_CONF_BR_READ	((PUMA_CONF_BASE & BR_BA_MSK) | BR_PS_16 | BR_V)
#define PUMA_CONF_OR_READ	(PUMA_CONF_OR_AM | PUMA_CONF_READ_TIMING)

#if PCU_E_WITH_SWAPPED_CS /* XXX */
#define CONFIG_SYS_BR3_PRELIM		PUMA_CONF_BR_READ
#define CONFIG_SYS_OR3_PRELIM		PUMA_CONF_OR_READ
#else /* XXX */
#define CONFIG_SYS_BR4_PRELIM		PUMA_CONF_BR_READ
#define CONFIG_SYS_OR4_PRELIM		PUMA_CONF_OR_READ
#endif /* XXX */

#define PUMA_SMA8_BASE		0x10200000	/* PUMA SMA Bus 8 Bit */
#define PUMA_SMA8_OR_AM		0xFFE00000	/* 2 MB */
#define PUMA_SMA8_TIMING	(OR_BI | OR_SCY_0_CLK | OR_EHTR)

#if PCU_E_WITH_SWAPPED_CS /* XXX */
#define CONFIG_SYS_BR2_PRELIM		((PUMA_SMA8_BASE & BR_BA_MSK) | BR_PS_8 | BR_V)
#define CONFIG_SYS_OR2_PRELIM		(PUMA_SMA8_OR_AM | PUMA_SMA8_TIMING | OR_SETA)
#else /* XXX */
#define CONFIG_SYS_BR5_PRELIM		((PUMA_SMA8_BASE & BR_BA_MSK) | BR_PS_8 | BR_V)
#define CONFIG_SYS_OR5_PRELIM		(PUMA_SMA8_OR_AM | PUMA_SMA8_TIMING | OR_SETA)
#endif /* XXX */

#define PUMA_SMA16_BASE		0x10600000	/* PUMA SMA Bus 16 Bit */
#define PUMA_SMA16_OR_AM	0xFFE00000	/* 2 MB */
#define PUMA_SMA16_TIMING	(OR_BI | OR_SCY_0_CLK | OR_EHTR)

#if PCU_E_WITH_SWAPPED_CS /* XXX */
#define CONFIG_SYS_BR1_PRELIM		((PUMA_SMA16_BASE & BR_BA_MSK) | BR_PS_16 | BR_V)
#define CONFIG_SYS_OR1_PRELIM		(PUMA_SMA16_OR_AM | PUMA_SMA16_TIMING | OR_SETA)
#else /* XXX */
#define CONFIG_SYS_BR6_PRELIM		((PUMA_SMA16_BASE & BR_BA_MSK) | BR_PS_16 | BR_V)
#define CONFIG_SYS_OR6_PRELIM		(PUMA_SMA16_OR_AM | PUMA_SMA16_TIMING | OR_SETA)
#endif /* XXX */

#define PUMA_FLASH_BASE		0x10A00000	/* PUMA external Flash */
#define PUMA_FLASH_OR_AM	0xFE000000	/* 32 MB */
#define PUMA_FLASH_TIMING	(OR_BI | OR_SCY_0_CLK | OR_EHTR)

#define CONFIG_SYS_BR7_PRELIM		((PUMA_FLASH_BASE & BR_BA_MSK) | BR_PS_16 | BR_V)
#define CONFIG_SYS_OR7_PRELIM		(PUMA_FLASH_OR_AM | PUMA_FLASH_TIMING | OR_SETA)


/* periodic timer for refresh */
#define CONFIG_SYS_MPTPR	0x0200

/* periodic timer for refresh */
#define CONFIG_SYS_MAMR_PTA	0x30	/* = 48 */

#define CONFIG_SYS_MAMR	( (CONFIG_SYS_MAMR_PTA << MAMR_PTA_SHIFT) | \
			  MAMR_AMA_TYPE_1	| \
			  MAMR_G0CLA_A10	| \
			  MAMR_RLFA_1X		| \
			  MAMR_WLFA_1X		| \
			  MAMR_TLFA_8X		)

#define	BOOTFLAG_COLD	0x01		/* Normal Power-On: Boot from FLASH	*/
#define BOOTFLAG_WARM	0x02		/* Software reboot			*/

#endif	/* __CONFIG_H */
