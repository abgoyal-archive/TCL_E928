


#ifndef __CONFIG_H
#define __CONFIG_H


#define CONFIG_MPC823		1	/* This is a MPC823 CPU		*/
#define CONFIG_FLAGADM		1	/* ...on a FLAGA DM	*/
#define CONFIG_8xx_GCLK_FREQ 48000000	/*48MHz*/

#undef	CONFIG_8xx_CONS_SMC1		/* Console is on SMC1		*/
#define CONFIG_8xx_CONS_SMC2	1
#undef	CONFIG_8xx_CONS_NONE

#define CONFIG_BAUDRATE		115200	/* console baudrate = 115kbps	*/
#define CONFIG_BOOTDELAY	3	/* autoboot after 5 seconds	*/

#undef	CONFIG_CLOCKS_IN_MHZ

#if 0
#define CONFIG_BOOTARGS		"root=/dev/nfs rw ip=bootp"
#define CONFIG_BOOTCOMMAND							\
   "setenv bootargs root=/dev/ram ip=off panic=1;"     \
   "bootm 40040000 400e0000"
#else
#define CONFIG_BOOTARGS		"root=/dev/nfs rw ip=bootp panic=1"
#define CONFIG_BOOTCOMMAND	"bootp 0x400000; bootm 0x400000"
#endif /* 0|1*/

#define CONFIG_LOADS_ECHO	1	/* echo on for serial download	*/
#undef	CONFIG_SYS_LOADS_BAUD_CHANGE		/* don't allow baudrate change	*/

/*#define	CONFIG_WATCHDOG*/	/* watchdog enabled		*/
#undef	CONFIG_WATCHDOG			/* watchdog disabled		*/

#define CONFIG_BOOTP_SUBNETMASK
#define CONFIG_BOOTP_GATEWAY
#define CONFIG_BOOTP_HOSTNAME
#define CONFIG_BOOTP_BOOTPATH
#define CONFIG_BOOTP_BOOTFILESIZE



#define CONFIG_CMD_BDI
#define CONFIG_CMD_IMI
#define CONFIG_CMD_CACHE
#define CONFIG_CMD_MEMORY
#define CONFIG_CMD_FLASH
#define CONFIG_CMD_LOADB
#define CONFIG_CMD_LOADS
#define CONFIG_CMD_SAVEENV
#define CONFIG_CMD_REGINFO
#define CONFIG_CMD_IMMAP
#define CONFIG_CMD_NET


#define CONFIG_SYS_LONGHELP			/* undef to save memory		*/
#define CONFIG_SYS_PROMPT	"EEG> "		/* Monitor Command Prompt	*/
#if defined(CONFIG_CMD_KGDB)
#define CONFIG_SYS_CBSIZE	1024		/* Console I/O Buffer Size	*/
#else
#define CONFIG_SYS_CBSIZE	256		/* Console I/O Buffer Size	*/
#endif
#define CONFIG_SYS_PBSIZE (CONFIG_SYS_CBSIZE+sizeof(CONFIG_SYS_PROMPT)+16) /* Print Buffer Size */
#define CONFIG_SYS_MAXARGS	16		/* max number of command args	*/
#define CONFIG_SYS_BARGSIZE	CONFIG_SYS_CBSIZE	/* Boot Argument Buffer Size	*/

#define CONFIG_SYS_MEMTEST_START	0x0100000	/* memtest works on	*/
#define CONFIG_SYS_MEMTEST_END		0x0f00000	/* 1 ... 15 MB in DRAM	*/

#define CONFIG_SYS_LOAD_ADDR		0x40040000	/* default load address */

#define CONFIG_SYS_HZ		1000		/* decrementer freq: 1 ms ticks */

#define CONFIG_SYS_BAUDRATE_TABLE	{ 9600, 19200, 38400, 57600, 115200 }

#define CONFIG_SYS_IMMR		0xFF000000

#define CONFIG_SYS_INIT_RAM_ADDR	CONFIG_SYS_IMMR
#define CONFIG_SYS_INIT_RAM_END	0x2F00	/* End of used area in DPRAM	*/
#define CONFIG_SYS_GBL_DATA_SIZE	64  /* size in bytes reserved for initial data */
#define CONFIG_SYS_GBL_DATA_OFFSET	(CONFIG_SYS_INIT_RAM_END - CONFIG_SYS_GBL_DATA_SIZE)
#define CONFIG_SYS_INIT_SP_OFFSET	CONFIG_SYS_GBL_DATA_OFFSET

#define CONFIG_SYS_SDRAM_BASE		0x00000000
#define CONFIG_SYS_FLASH_BASE		0x40000000
#define CONFIG_SYS_MONITOR_LEN		(128 << 10)	/* Reserve 128 kB for Monitor	*/
#define CONFIG_SYS_MONITOR_BASE	CONFIG_SYS_FLASH_BASE
#define CONFIG_SYS_MALLOC_LEN		(128 << 10)	/* Reserve 128 kB for malloc()	*/

#define CONFIG_SYS_BOOTMAPSZ		(8 << 20)	/* Initial Memory map for Linux */

#define CONFIG_SYS_MAX_FLASH_BANKS	1	/* max number of memory banks		*/
#define CONFIG_SYS_MAX_FLASH_SECT	71	/* max number of sectors on one chip	*/

#define CONFIG_SYS_FLASH_ERASE_TOUT	8000	/* Timeout for Flash Erase (in ms)	*/
#define CONFIG_SYS_FLASH_WRITE_TOUT	500	/* Timeout for Flash Write (in ms)	*/

#define CONFIG_ENV_IS_IN_FLASH	1
#define CONFIG_ENV_OFFSET		0x20000 /*   Offset   of Environment Sector	*/
#define CONFIG_ENV_SIZE		0x20000 /* Total Size of Environment Sector	*/

#define CONFIG_SYS_CACHELINE_SIZE	16	/* For all MPC8xx CPUs			*/
#if defined(CONFIG_CMD_KGDB)
#define CONFIG_SYS_CACHELINE_SHIFT	4	/* log base 2 of the above value	*/
#endif
#define CONFIG_SYS_DELAYED_ICACHE	1	/* enable ICache not before
						 * running in RAM.
						 */

#ifdef CONFIG_WATCHDOG
#define CONFIG_SYS_SYPCR (SYPCR_SWTC | SYPCR_SWF | SYPCR_SWE | SYPCR_SWRI | SYPCR_SWP)
#else
#define CONFIG_SYS_SYPCR	(SYPCR_SWTC | SYPCR_BMT | SYPCR_BME | SYPCR_SWF)
#endif

#define CONFIG_SYS_PRE_SIUMCR (SIUMCR_DBGC11 | SIUMCR_MPRE | \
							SIUMCR_MLRC01 | SIUMCR_GB5E)
#define CONFIG_SYS_SIUMCR (CONFIG_SYS_PRE_SIUMCR | SIUMCR_DLK)

#define CONFIG_SYS_TBSCR	(TBSCR_REFA | TBSCR_REFB | TBSCR_TBF)

#define CONFIG_SYS_RTCSC	(RTCSC_SEC | RTCSC_ALR | RTCSC_RTF| RTCSC_RTE)

#define CONFIG_SYS_PISCR	(PISCR_PS | PISCR_PITF)

#define CONFIG_SYS_PLPRCR	(0x00b00000 | PLPRCR_SPLSS | PLPRCR_TEXPS | PLPRCR_TMIST)

#define SCCR_MASK	SCCR_EBDF11
#define CONFIG_SYS_SCCR	( SCCR_COM00   | SCCR_DFSYNC00 | SCCR_DFBRG00  | \
			 SCCR_DFNL000 | SCCR_DFNH000  | SCCR_DFLCD000 | \
			 SCCR_DFALCD00)

#define CONFIG_SYS_DER 0


#define CONFIG_SYS_FLASH_PROTECTION 0

#define FLASH_BASE0		0x40000000	/* FLASH bank #0	*/

#define CONFIG_SYS_OR_AM		0xff000000	/* OR addr mask */
#define CONFIG_SYS_OR_ATM		0x00006000

/* FLASH timing: ACS = 10, TRLX = 1, CSNT = 1, SCY = 3, EHTR = 1	*/
#define CONFIG_SYS_OR_TIMING_FLASH	(OR_CSNT_SAM  | OR_ACS_DIV4 | OR_BI | \
				 OR_SCY_3_CLK | OR_TRLX | OR_EHTR )

#define CONFIG_SYS_OR0_PRELIM	(CONFIG_SYS_OR_AM | CONFIG_SYS_OR_ATM | CONFIG_SYS_OR_TIMING_FLASH)
#define CONFIG_SYS_BR0_PRELIM	((FLASH_BASE0 & BR_BA_MSK) | BR_PS_16 | BR_V )

#define SDRAM_BASE2			0x00000000	/* SDRAM bank #0	*/
#define SDRAM_MAX_SIZE		0x04000000	/* max 64 MB per bank	*/

/* SDRAM timing: Multiplexed addresses, GPL5 output to GPL5_A (don't care)	*/
#define CONFIG_SYS_OR_TIMING_SDRAM	( 0x00000800 )

#define CONFIG_SYS_OR2_PRELIM	(CONFIG_SYS_OR_AM | CONFIG_SYS_OR_TIMING_SDRAM)
#define CONFIG_SYS_BR2_PRELIM	((SDRAM_BASE2 & BR_BA_MSK) | BR_MS_UPMA | BR_V )

#define CONFIG_SYS_BR2			CONFIG_SYS_BR2_PRELIM
#define CONFIG_SYS_OR2			CONFIG_SYS_OR2_PRELIM

#define CONFIG_SYS_MAMR_48_SDR (CONFIG_SYS_MAMR_PTA |	 MAMR_WLFA_1X | MAMR_RLFA_1X  \
					| MAMR_G0CLA_A11)


/* periodic timer for refresh */
#define CONFIG_SYS_MAMR_PTA	0x0F000000

#define DSP_BASE 0x80000000

#define CONFIG_SYS_OR4 ( OR_AM_MSK | OR_CSNT_SAM | OR_BI | OR_G5LS)
#define CONFIG_SYS_BR4 ( (DSP_BASE & BR_BA_MSK) | BR_PS_16 | BR_MS_UPMB | BR_V )

#define BOOTFLAG_COLD	0x01		/* Normal Power-On: Boot from FLASH	*/
#define BOOTFLAG_WARM	0x02		/* Software reboot			*/

#endif	/* __CONFIG_H */
