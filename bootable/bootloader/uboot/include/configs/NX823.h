


#ifndef __CONFIG_H
#define __CONFIG_H


#define CONFIG_MPC823		1	/* This is a MPC823 CPU	    */
#define CONFIG_NX823		1	/* ...on a NEXUS 823  module	*/

/*#define  CONFIG_VIDEO		1 */

#define CONFIG_8xx_GCLK_FREQ	MPC8XX_SPEED
#define CONFIG_8xx_CONS_SMC1	1	/* Console is on SMC1	    */
#undef	CONFIG_8xx_CONS_SMC2
#undef	CONFIG_8xx_CONS_NONE
#define CONFIG_BAUDRATE 57600	/* console baudrate = 115kbps	*/
#define CONFIG_BOOTDELAY	2	/* autoboot after 2 seconds */
#define CONFIG_BOOTARGS		"ramdisk_size=8000 "\
				"root=/dev/nfs rw nfsroot=10.77.77.250:/ppcroot "\
				"nfsaddrs=10.77.77.20:10.77.77.250"
#define CONFIG_BOOTCOMMAND	"bootm 400e0000"

#define CONFIG_LOADS_ECHO	1	/* echo on for serial download	*/
#undef	CONFIG_SYS_LOADS_BAUD_CHANGE		/* don't allow baudrate change	*/
#undef	CONFIG_WATCHDOG			/* watchdog disabled, for now	    */
#define CONFIG_SOURCE

#define CONFIG_BOOTP_SUBNETMASK
#define CONFIG_BOOTP_GATEWAY
#define CONFIG_BOOTP_HOSTNAME
#define CONFIG_BOOTP_BOOTPATH
#define CONFIG_BOOTP_BOOTFILESIZE


#include <config_cmd_default.h>

#define CONFIG_CMD_SOURCE


/* call various generic functions */
#define CONFIG_MISC_INIT_R

#define CONFIG_SYS_LONGHELP			/* undef to save memory	    */
#define CONFIG_SYS_PROMPT		"=> "	/* Monitor Command Prompt   */
#if defined(CONFIG_CMD_KGDB)
#define CONFIG_SYS_CBSIZE		1024	/* Console I/O Buffer Size  */
#else
#define CONFIG_SYS_CBSIZE		256	/* Console I/O Buffer Size  */
#endif
#define CONFIG_SYS_PBSIZE (CONFIG_SYS_CBSIZE+sizeof(CONFIG_SYS_PROMPT)+16)	/* Print Buffer Size */
#define CONFIG_SYS_MAXARGS		16	/* max number of command args	*/
#define CONFIG_SYS_BARGSIZE	CONFIG_SYS_CBSIZE	/* Boot Argument Buffer Size	*/

#define CONFIG_SYS_MEMTEST_START	0x0400000	/* memtest works on */
#define CONFIG_SYS_MEMTEST_END		0x0C00000	/* 4 ... 12 MB in DRAM	*/

#define CONFIG_SYS_LOAD_ADDR		0x100000	/* default load address */

#define CONFIG_SYS_HZ			1000	/* decrementer freq: 1 ms ticks */

#define CONFIG_SYS_BAUDRATE_TABLE	{ 9600, 19200, 38400, 57600, 115200 }

#define CONFIG_SYS_IMMR		0xFFF00000

#define CONFIG_SYS_INIT_RAM_ADDR	CONFIG_SYS_IMMR
#define CONFIG_SYS_INIT_RAM_END	0x2F00	/* End of used area in DPRAM	*/
#define CONFIG_SYS_GBL_DATA_SIZE	64	/* size in bytes reserved for initial data */
#define CONFIG_SYS_GBL_DATA_OFFSET	(CONFIG_SYS_INIT_RAM_END - CONFIG_SYS_GBL_DATA_SIZE)
#define CONFIG_SYS_INIT_SP_OFFSET	CONFIG_SYS_GBL_DATA_OFFSET

#define CONFIG_SYS_SDRAM_BASE		0x00000000
#define CONFIG_SYS_FLASH_BASE		0x40000000
#define CONFIG_SYS_MONITOR_LEN		(128 << 10)	/* Reserve 128 kB for Monitor	*/
#define CONFIG_SYS_MONITOR_BASE	CONFIG_SYS_FLASH_BASE
#define CONFIG_SYS_MALLOC_LEN		(128 << 10)	/* Reserve 128 kB for malloc()	*/

#define CONFIG_SYS_BOOTMAPSZ		(8 << 20)	/* Initial Memory map for Linux */

#define CONFIG_SYS_MAX_FLASH_BANKS	1	/* max number of memory banks	    */
#define CONFIG_SYS_MAX_FLASH_SECT	128	/* max number of sectors on one chip	*/

#define CONFIG_SYS_FLASH_ERASE_TOUT	120000	/* Timeout for Flash Erase (in ms)  */
#define CONFIG_SYS_FLASH_WRITE_TOUT	500	/* Timeout for Flash Write (in ms)  */

#define CONFIG_ENV_IS_IN_FLASH	1
#define xEMBED
#ifdef	EMBED
#define CONFIG_ENV_SIZE		0x200	/* FIXME How big when embedded?? */
#define CONFIG_ENV_ADDR		CONFIG_SYS_MONITOR_BASE
#else
#define CONFIG_ENV_ADDR		0x40020000	/* absolute address for now   */
#define CONFIG_ENV_SIZE		0x20000 /* 8K ouch, this may later be */
#endif

#define CONFIG_SYS_FLASH_SN_BASE	0x4001fff0	/* programmer automagically puts    */
#define CONFIG_SYS_FLASH_SN_SECTOR	0x40000000	/* a serial number here		    */
#define CONFIG_SYS_FLASH_SN_BYTES	8

#define CONFIG_SYS_CACHELINE_SIZE	16	/* For all MPC8xx CPUs		*/
#if defined(CONFIG_CMD_KGDB)
#define CONFIG_SYS_CACHELINE_SHIFT	4	/* log base 2 of the above value    */
#endif

#if defined(CONFIG_WATCHDOG)
#define CONFIG_SYS_SYPCR	(SYPCR_SWTC | SYPCR_BMT | SYPCR_BME | SYPCR_SWF | \
			 SYPCR_SWE  | SYPCR_SWP)
#else
#define CONFIG_SYS_SYPCR	(SYPCR_SWTC | SYPCR_BMT | SYPCR_BME | SYPCR_SWF | SYPCR_SWP)
#endif

#define CONFIG_SYS_SIUMCR	(SIUMCR_DBGC00 | SIUMCR_DBPC00)

#define CONFIG_SYS_TBSCR	(TBSCR_REFA | TBSCR_REFB | TBSCR_TBF)

#define CONFIG_SYS_RTCSC	(RTCSC_SEC | RTCSC_ALR | RTCSC_RTF| RTCSC_RTE)

#define CONFIG_SYS_PISCR	(PISCR_PS | PISCR_PITF)

#define MPC8XX_SPEED	66666666L
#define MPC8XX_XIN	32768	/* 32.768 kHz crystal */
#define MPC8XX_FACT		(MPC8XX_SPEED/MPC8XX_XIN)
#define CONFIG_SYS_PLPRCR_MF  ((MPC8XX_FACT-1) << PLPRCR_MF_SHIFT)
#define CONFIG_SYS_PLPRCR		(CONFIG_SYS_PLPRCR_MF | PLPRCR_TEXPS | PLPRCR_TMIST)

#define SCCR_MASK	SCCR_EBDF11
#define CONFIG_SYS_SCCR	(SCCR_TBS     | \
			 SCCR_COM00   | SCCR_DFSYNC00 | SCCR_DFBRG00  | \
			 SCCR_DFNL000 | SCCR_DFNH000  | SCCR_DFLCD000 | \
			 SCCR_DFALCD00)

#define CONFIG_SYS_DER		0


#define FLASH_BASE0_PRELIM	0x40000000	/* FLASH bank #0    */

#define CONFIG_SYS_REMAP_OR_AM		0x80000000	/* OR addr mask */
#define CONFIG_SYS_PRELIM_OR_AM	0xE0000000	/* OR addr mask */

/* FLASH timing: ACS = 00, TRLX = 0, CSNT = 1, SCY = 8, EHTR = 0	*/
#define CONFIG_SYS_OR_TIMING_FLASH	(OR_CSNT_SAM  | OR_ACS_DIV1 | OR_BI | \
				 OR_SCY_8_CLK )

#define CONFIG_SYS_OR0_REMAP	(CONFIG_SYS_REMAP_OR_AM  | CONFIG_SYS_OR_TIMING_FLASH)
#define CONFIG_SYS_OR0_PRELIM	(CONFIG_SYS_PRELIM_OR_AM | CONFIG_SYS_OR_TIMING_FLASH)
#define CONFIG_SYS_BR0_PRELIM	((FLASH_BASE0_PRELIM & BR_BA_MSK) | BR_PS_16 | BR_V )

#define SDRAM_BASE1_PRELIM	0x00000000	/* SDRAM bank #0    */
#define SDRAM_BASE2_PRELIM	0x20000000	/* SDRAM bank #1    */
#define SDRAM_MAX_SIZE		0x04000000	/* max 64 MB per bank	*/

/* SDRAM timing: Multiplexed addresses, drive GPL5 high on first cycle */
#define CONFIG_SYS_OR_TIMING_SDRAM	(OR_G5LS | OR_CSNT_SAM)

#define CONFIG_SYS_OR1_PRELIM	(CONFIG_SYS_PRELIM_OR_AM | CONFIG_SYS_OR_TIMING_SDRAM )
#define CONFIG_SYS_BR1_PRELIM	((SDRAM_BASE1_PRELIM & BR_BA_MSK) | BR_MS_UPMA | BR_V )
#define CONFIG_SYS_OR2_PRELIM	CONFIG_SYS_OR1_PRELIM
#define CONFIG_SYS_BR2_PRELIM	((SDRAM_BASE2_PRELIM & BR_BA_MSK) | BR_MS_UPMA | BR_V )

/* IO and memory mapped stuff */
#define NX823_IO_OR_AM		0xFFFF0000	/* mask for IO addresses */
#define NX823_IO_BASE		0xFF000000	/* start of IO	*/
#define GPOUT_OFFSET		(3<<16)
#define QUART_OFFSET		(4<<16)
#define VIDAC_OFFSET		(5<<16)
#define CPLD_OFFSET		(6<<16)
#define SED1386_OFFSET		(7<<16)

#define GPOUT_BASE	(NX823_IO_BASE + GPOUT_OFFSET)
#define GPOUT_TIMING	(OR_CSNT_SAM | OR_TRLX | OR_BI)
#define CONFIG_SYS_OR3_PRELIM	(NX823_IO_OR_AM | GPOUT_TIMING)
#define CONFIG_SYS_BR3_PRELIM	(GPOUT_BASE | BR_V)

#define QUART_BASE	(NX823_IO_BASE + QUART_OFFSET)
#define QUART_TIMING	(OR_ACS_DIV4 | OR_SCY_3_CLK | OR_CSNT_SAM | OR_TRLX)
#define CONFIG_SYS_OR4_PRELIM	(NX823_IO_OR_AM | QUART_TIMING | OR_BI)
#define CONFIG_SYS_BR4_PRELIM	(QUART_BASE | BR_PS_8 | BR_V)

#define VIDAC_BASE	(NX823_IO_BASE + VIDAC_OFFSET)
#define VIDAC_TIMING	(OR_ACS_DIV4 | OR_SCY_3_CLK | OR_CSNT_SAM | OR_EHTR)
#define CONFIG_SYS_OR5_PRELIM	(NX823_IO_OR_AM | VIDAC_TIMING | OR_BI)
#define CONFIG_SYS_BR5_PRELIM	(VIDAC_BASE | BR_PS_8 | BR_V)

#define CPLD_BASE	(NX823_IO_BASE + CPLD_OFFSET)
#define CPLD_TIMING	(OR_ACS_DIV4 | OR_SCY_3_CLK | OR_CSNT_SAM | OR_EHTR)
#define CONFIG_SYS_OR6_PRELIM	(NX823_IO_OR_AM | CPLD_TIMING | OR_BI)
#define CONFIG_SYS_BR6_PRELIM	(CPLD_BASE | BR_PS_8 | BR_V )

#define SED1386_BASE	0xF7000000
#define CONFIG_SYS_OR7_PRELIM	(0xFF000000 | OR_BI | OR_SETA)
#define CONFIG_SYS_BR7_PRELIM	(SED1386_BASE | BR_PS_16 | BR_V )


/* periodic timer for refresh */
#define CONFIG_SYS_MAMR_PTA	97		/* start with divider for 100 MHz   */

/* refresh rate 15.6 us (= 64 ms / 4K = 62.4 / quad bursts) for <= 128 MBit	*/
#define CONFIG_SYS_MPTPR_2BK_4K	MPTPR_PTP_DIV16 /* setting for 2 banks	*/
#define CONFIG_SYS_MPTPR_1BK_4K	MPTPR_PTP_DIV32 /* setting for 1 bank	*/

/* refresh rate 7.8 us (= 64 ms / 8K = 31.2 / quad bursts) for 256 MBit		*/
#define CONFIG_SYS_MPTPR_2BK_8K	MPTPR_PTP_DIV8	/* setting for 2 banks	*/
#define CONFIG_SYS_MPTPR_1BK_8K	MPTPR_PTP_DIV16 /* setting for 1 bank	*/


/* 8 column SDRAM */
#define CONFIG_SYS_MAMR_8COL	((CONFIG_SYS_MAMR_PTA << MAMR_PTA_SHIFT)  | MAMR_PTAE	    |	\
			 MAMR_AMA_TYPE_0 | MAMR_DSA_1_CYCL | MAMR_G0CLA_A11 |	\
			 MAMR_RLFA_1X	 | MAMR_WLFA_1X	   | MAMR_TLFA_4X)
/* 9 column SDRAM */
#define CONFIG_SYS_MAMR_9COL	((CONFIG_SYS_MAMR_PTA << MAMR_PTA_SHIFT)  | MAMR_PTAE	    |	\
			 MAMR_AMA_TYPE_1 | MAMR_DSA_1_CYCL | MAMR_G0CLA_A10 |	\
			 MAMR_RLFA_1X	 | MAMR_WLFA_1X	   | MAMR_TLFA_4X)


#define BOOTFLAG_COLD	0x01	/* Normal Power-On: Boot from FLASH */
#define BOOTFLAG_WARM	0x02	/* Software reboot	    */

#define CONFIG_ENV_OVERWRITE	/* allow changes to ethaddr (for now)	*/
#define CONFIG_ETHADDR		00:10:20:30:40:50
#define CONFIG_IPADDR		10.77.77.20
#define CONFIG_SERVERIP		10.77.77.250

#endif /* __CONFIG_H */
