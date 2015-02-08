


#ifndef __CONFIG_GEN860T_H
#define __CONFIG_H

#define CONFIG_MPC860
#define CONFIG_GEN860T

#if !defined(CONFIG_SC)
#define CONFIG_IDENT_STRING		" B2"
#else
#define CONFIG_IDENT_STRING		" SC"
#endif

#if !defined(CONFIG_SC)
#define	CONFIG_8xx_GCLK_FREQ		66600000
#else
#define	CONFIG_8xx_GCLK_FREQ		48000000
#endif

#define	CONFIG_8xx_CONS_SMC1
#define CONFIG_BAUDRATE			38400

#define CONFIG_SYS_BAUDRATE_TABLE		{ 9600,		\
					  19200,	\
					  38400,	\
					  57600,	\
					  115200,	\
					}

#undef	 CONFIG_SYS_CONSOLE_INFO_QUIET

#define CONFIG_BOOTDELAY				5

#define	CONFIG_CLOCKS_IN_MHZ

#define CONFIG_PREBOOT		\
	"echo;echo"

#undef	CONFIG_BOOTARGS
#define CONFIG_BOOTCOMMAND	\
	"bootp;" \
	"setenv bootargs root=/dev/nfs rw nfsroot=${serverip}:${rootpath} " \
	"ip=${ipaddr}:${serverip}:${gatewayip}:${netmask}:${hostname}::off; " \
	"bootm"

#undef	CONFIG_LOADS_ECHO
#define	CONFIG_SYS_LOADS_BAUD_CHANGE

#define	CONFIG_SYS_TFTP_LOADADDR				0x01000000

#undef	CONFIG_WATCHDOG

#define CONFIG_PANIC_HANG

#define	CONFIG_STATUS_LED

#define CONFIG_SYS_RESET_ADDRESS				((ulong) -1)

#define CONFIG_BOOTP_SUBNETMASK
#define CONFIG_BOOTP_GATEWAY
#define CONFIG_BOOTP_HOSTNAME
#define CONFIG_BOOTP_BOOTPATH
#define CONFIG_BOOTP_BOOTFILESIZE


#define CONFIG_FEC_ENET
#define CONFIG_SYS_DISCOVER_PHY
#define CONFIG_MII
#define CONFIG_MII_INIT			1
#define CONFIG_PHY_ADDR			0

#define CONFIG_ETHADDR					9a:52:63:15:85:25
#define CONFIG_SERVERIP					10.0.4.201
#define CONFIG_IPADDR					10.0.4.111

#define CONFIG_SYS_I2C_EEPROM_ADDR				0x50
#define CONFIG_SYS_EEPROM_PAGE_WRITE_BITS		6		/* 64 byte pages		*/
#define CONFIG_SYS_EEPROM_PAGE_WRITE_DELAY_MS	12		/* 10 mS w/ 20% margin	*/
#define	CONFIG_SYS_I2C_EEPROM_ADDR_LEN			2		/* need 16 bit address	*/
#define CONFIG_ENV_EEPROM_SIZE				(32 * 1024)

#define CONFIG_HARD_I2C		1				/* CPM based I2C			*/
#undef	CONFIG_SOFT_I2C						/* Bit-banged I2C			*/

#ifdef CONFIG_HARD_I2C
#define	CONFIG_SYS_I2C_SPEED		100000			/* clock speed in Hz		*/
#define CONFIG_SYS_I2C_SLAVE		0xFE			/* I2C slave address		*/
#endif

#ifdef CONFIG_SOFT_I2C
#define PB_SCL				0x00000020		/* PB 26					*/
#define PB_SDA				0x00000010		/* PB 27					*/
#define I2C_INIT			(immr->im_cpm.cp_pbdir |=  PB_SCL)
#define I2C_ACTIVE			(immr->im_cpm.cp_pbdir |=  PB_SDA)
#define I2C_TRISTATE		(immr->im_cpm.cp_pbdir &= ~PB_SDA)
#define I2C_READ			((immr->im_cpm.cp_pbdat & PB_SDA) != 0)
#define I2C_SDA(bit)		if(bit) immr->im_cpm.cp_pbdat |=  PB_SDA; \
								else    immr->im_cpm.cp_pbdat &= ~PB_SDA
#define I2C_SCL(bit)		if(bit) immr->im_cpm.cp_pbdat |=  PB_SCL; \
								else    immr->im_cpm.cp_pbdat &= ~PB_SCL
#define I2C_DELAY			udelay(5)		/* 1/4 I2C clock duration	*/
#endif

#define CONFIG_ENV_OVERWRITE

#if !defined(CONFIG_SC)
#define CONFIG_RTC_DS1337
#define CONFIG_SYS_I2C_RTC_ADDR				0x68

#else
#define	CONFIG_RTC_MPC8xx
#endif

#define CONFIG_POST			  ( CONFIG_SYS_POST_CACHE		| \
								CONFIG_SYS_POST_MEMORY		| \
								CONFIG_SYS_POST_CPU		| \
								CONFIG_SYS_POST_UART		| \
								CONFIG_SYS_POST_SPR )


#include <config_cmd_default.h>

#define CONFIG_CMD_ASKENV
#define CONFIG_CMD_DHCP
#define CONFIG_CMD_I2C
#define CONFIG_CMD_EEPROM
#define CONFIG_CMD_REGINFO
#define CONFIG_CMD_IMMAP
#define CONFIG_CMD_ELF
#define CONFIG_CMD_DATE
#define CONFIG_CMD_FPGA
#define CONFIG_CMD_MII
#define CONFIG_CMD_BEDBUG

#ifdef CONFIG_POST
#define CONFIG_CMD_DIAG
#endif

#undef  CONFIG_IDE_PCMCIA
#undef  CONFIG_IDE_LED
#undef  CONFIG_IDE_RESET

#define CONFIG_MISC_INIT_R

#define CONFIG_LAST_STAGE_INIT

#define CONFIG_FPGA_COUNT		1
#define CONFIG_FPGA
#define CONFIG_FPGA_XILINX
#define CONFIG_FPGA_VIRTEX2
#define CONFIG_SYS_FPGA_PROG_FEEDBACK

#define	CONFIG_SYS_LONGHELP
#if !defined(CONFIG_SC)
#define	CONFIG_SYS_PROMPT			"B2> "
#else
#define	CONFIG_SYS_PROMPT			"SC> "
#endif


#define	CONFIG_SYS_HUSH_PARSER
#define	CONFIG_SYS_PROMPT_HUSH_PS2	"> "

#if defined(CONFIG_CMD_KGDB)
#define	CONFIG_SYS_CBSIZE			1024
#else
#define	CONFIG_SYS_CBSIZE			256
#endif

#define	CONFIG_SYS_PBSIZE (CONFIG_SYS_CBSIZE + sizeof(CONFIG_SYS_PROMPT) + 16)

#define	CONFIG_SYS_MAXARGS			16

#define CONFIG_SYS_BARGSIZE		CONFIG_SYS_CBSIZE

#define CONFIG_SYS_MEMTEST_START	0x0100000
#define CONFIG_SYS_MEMTEST_END		(CONFIG_SYS_MEMTEST_START  + (128 * 1024))

#define	CONFIG_SYS_ALT_MEMTEST

#define	CONFIG_SYS_LOAD_ADDR		0x01000000

#define	CONFIG_SYS_HZ				1000


#define CONFIG_SYS_IMMR			0xFF000000

#define SDRAM_BASE			0x00000000
#define SDRAM_SIZE			(64 * 1024 * 1024)

#define FLASH_BASE			0x40000000
#define FLASH_SIZE			(16 * 1024 * 1024)

#define DOC_BASE			0x50000000
#define DOC_SIZE			(32 * 1024)

#define FPGA_BASE			0x60000000
#define FPGA_SIZE			(64 * 1024 * 1024)

#define SELECTMAP_BASE		0x70000000
#define SELECTMAP_SIZE		(32 * 1024)

#define M1553_BASE			0x80000000
#define M1553_SIZE			(64 * 1024)

#define CONFIG_SYS_INIT_RAM_ADDR		CONFIG_SYS_IMMR
#define	CONFIG_SYS_INIT_RAM_END		0x2F00	/* End of used area in DPRAM		*/
#define	CONFIG_SYS_INIT_DATA_SIZE		64	/* # bytes reserved for initial data*/
#define CONFIG_SYS_GBL_DATA_OFFSET		(CONFIG_SYS_INIT_RAM_END - CONFIG_SYS_INIT_DATA_SIZE)
#define	CONFIG_SYS_INIT_SP_OFFSET		CONFIG_SYS_GBL_DATA_OFFSET

#define	CONFIG_SYS_SDRAM_BASE			SDRAM_BASE

#define CONFIG_SYS_FLASH_BASE			FLASH_BASE
#define CONFIG_SYS_FLASH_SIZE			FLASH_SIZE
#define CONFIG_SYS_FLASH_SECT_SIZE		(128 * 1024)
#define CONFIG_SYS_MAX_FLASH_BANKS		1
#define CONFIG_SYS_MAX_FLASH_SECT		128

#define CONFIG_SYS_FLASH_ERASE_TOUT	(CONFIG_SYS_MAX_FLASH_SECT * 5000)
#define CONFIG_SYS_FLASH_WRITE_TOUT	(CONFIG_SYS_MAX_FLASH_SECT * 128 * 1024 * 1)

#define	CONFIG_SYS_DIRECT_FLASH_TFTP

#define CONFIG_SYS_MAX_UBOOT_SECTS		4
#define	CONFIG_SYS_MONITOR_LEN			(CONFIG_SYS_MAX_UBOOT_SECTS * CONFIG_SYS_FLASH_SECT_SIZE)
#define CONFIG_SYS_MONITOR_BASE		CONFIG_SYS_FLASH_BASE

#undef	CONFIG_ENV_IS_IN_FLASH
#define CONFIG_ENV_IS_IN_EEPROM

#if defined(CONFIG_ENV_IS_IN_EEPROM)
#define CONFIG_ENV_SIZE			(2 * 1024)
#define CONFIG_ENV_OFFSET			(CONFIG_ENV_EEPROM_SIZE - (8 * 1024))
#else
#define CONFIG_ENV_SIZE			0x1000
#define CONFIG_ENV_SECT_SIZE		CONFIG_SYS_FLASH_SECT_SIZE

#define CONFIG_ENV_OFFSET			0x060000
#endif

#define	CONFIG_SYS_MALLOC_LEN		(128 * 1024)

#define	CONFIG_SYS_BOOTMAPSZ		(8 * 1024 * 1024)

#define CONFIG_SYS_CACHELINE_SIZE		16	/* For all MPC8xx CPUs				*/
#if defined(CONFIG_CMD_KGDB)
#define CONFIG_SYS_CACHELINE_SHIFT		4	/* log base 2 of above value		*/
#endif

#if defined(CONFIG_WATCHDOG)
#define CONFIG_SYS_SYPCR	( SYPCR_SWTC	| \
					  SYPCR_BMT	| \
					  SYPCR_BME	| \
					  SYPCR_SWF	| \
					  SYPCR_SWE	| \
					  SYPCR_SWRI	| \
					  SYPCR_SWP		  \
					)
#else
#define CONFIG_SYS_SYPCR	( SYPCR_SWTC	| \
					  SYPCR_BMT	| \
					  SYPCR_BME	| \
					  SYPCR_SWF	| \
					  SYPCR_SWP		  \
					)
#endif

#define CONFIG_SYS_SIUMCR	( SIUMCR_DBGC11 | \
					  SIUMCR_DBPC11 | \
					  SIUMCR_MLRC11	| \
					  SIUMCR_GB5E	  \
					)

#define CONFIG_SYS_TBSCR	( TBSCR_REFA | \
					  TBSCR_REFB | \
					  TBSCR_TBF	   \
					)

#define CONFIG_SYS_RTCSC	( RTCSC_SEC	| \
					  RTCSC_ALR | \
					  RTCSC_RTF | \
					  RTCSC_RTE	  \
					)

#define CONFIG_SYS_PISCR	( PISCR_PS		| \
					  PISCR_PITF	  \
					)

#define CONFIG_SYS_PLPRCR	( ((0x1 << PLPRCR_MF_SHIFT) & PLPRCR_MF_MSK)	| \
					  PLPRCR_SPLSS	| \
					  PLPRCR_TEXPS	| \
					  PLPRCR_TMIST	  \
					)

#define SCCR_MASK   SCCR_EBDF11

#if !defined(CONFIG_SC)
#define CONFIG_SYS_SCCR	( SCCR_TBS			|	/* timebase = GCLK/2	*/ \
					  SCCR_COM00		|	/* full strength CLKOUT	*/ \
					  SCCR_DFSYNC00	|	/* SYNCLK / 1 (normal)	*/ \
					  SCCR_DFBRG00		|	/* BRGCLK / 1 (normal)	*/ \
					  SCCR_DFNL000		| \
					  SCCR_DFNH000		  \
					)
#else
#define CONFIG_SYS_SCCR	( SCCR_TBS			|	/* timebase = GCLK/2	*/ \
					  SCCR_COM00		|	/* full strength CLKOUT	*/ \
					  SCCR_DFSYNC00	|	/* SYNCLK / 1 (normal)	*/ \
					  SCCR_DFBRG00		|	/* BRGCLK / 1 (normal)	*/ \
					  SCCR_DFNL000		| \
					  SCCR_DFNH000		| \
					  SCCR_RTDIV		| \
					  SCCR_RTSEL		  \
					)
#endif

#define CONFIG_SYS_DER				0

#define FLASH_BASE0_PRELIM	FLASH_BASE

#define CONFIG_SYS_PRELIM_OR_AM	0xfe000000

#define CONFIG_SYS_OR_TIMING_FLASH	( OR_CSNT_SAM	| \
							  OR_ACS_DIV2	| \
							  OR_BI			| \
							  OR_SCY_2_CLK	| \
							  OR_TRLX		| \
							  OR_EHTR		  \
							)

#define CONFIG_SYS_OR0_PRELIM	( CONFIG_SYS_PRELIM_OR_AM		| \
						  CONFIG_SYS_OR_TIMING_FLASH	  \
						)

#define CONFIG_SYS_BR0_PRELIM	( (FLASH_BASE0_PRELIM & BR_BA_MSK)	| \
						  BR_MS_GPCM						| \
						  BR_PS_8							| \
						  BR_V								  \
						)

#define CONFIG_SYS_OR1_AM	0xfc000000
#define CONFIG_SYS_OR1		( (CONFIG_SYS_OR1_AM & OR_AM_MSK)	| \
					  OR_CSNT_SAM				  \
					)

#define CONFIG_SYS_BR1		( (SDRAM_BASE & BR_BA_MSK)	| \
					  BR_MS_UPMA				| \
					  BR_PS_32					| \
					  BR_V						  \
					)

#define CONFIG_SYS_MPTPR_1BK_8K	MPTPR_PTP_DIV16

#define CONFIG_SYS_MAMR_PTA	64

#define CONFIG_SYS_MAMR_8COL	( (CONFIG_SYS_MAMR_PTA << MAMR_PTA_SHIFT)	| \
						  MAMR_PTAE				| \
						  MAMR_AMA_TYPE_1			| \
						  MAMR_DSA_1_CYCL			| \
						  MAMR_G0CLA_A10			| \
						  MAMR_RLFA_1X				| \
						  MAMR_WLFA_1X				| \
						  MAMR_TLFA_4X				  \
						)

#define CONFIG_SYS_OR2_PRELIM	( (0xffff0000 & OR_AM_MSK)	| \
						  OR_CSNT_SAM				| \
						  OR_ACS_DIV2				| \
						  OR_BI						| \
						  OR_SCY_2_CLK				| \
						  OR_TRLX					| \
						  OR_EHTR					  \
						)

#define CONFIG_SYS_BR2_PRELIM	( (DOC_BASE & BR_BA_MSK)	| \
						  BR_PS_8					| \
						  BR_MS_GPCM				| \
						  BR_V						  \
						)

#define CONFIG_SYS_OR3_PRELIM	( (0xfc000000 & OR_AM_MSK)  | \
						  OR_SCY_15_CLK				| \
						  OR_BI					  \
						)

#define CONFIG_SYS_BR3_PRELIM	( (FPGA_BASE & BR_BA_MSK)	| \
						  BR_PS_32					| \
						  BR_MS_GPCM				| \
						  BR_V						  \
						)
#define CONFIG_SYS_OR4_PRELIM	( (0xffff0000 & OR_AM_MSK)	| \
						  OR_G5LS						| \
						  OR_BI							  \
						)

#define CONFIG_SYS_BR4_PRELIM	( (SELECTMAP_BASE & BR_BA_MSK)	| \
						  BR_PS_8						| \
						  BR_MS_UPMB					| \
						  BR_V							  \
						)

#define CONFIG_SYS_OR5_PRELIM	( (0xffff0000 & OR_AM_MSK)  | \
						  OR_SCY_15_CLK				| \
						  OR_EHTR					| \
						  OR_TRLX					| \
						  OR_CSNT_SAM				| \
						  OR_BI						  \
						)

#define CONFIG_SYS_BR5_PRELIM	( (M1553_BASE & BR_BA_MSK)	| \
						  BR_PS_16					| \
						  BR_MS_GPCM				| \
						  BR_V						  \
						)

#define	BOOTFLAG_COLD	0x01	/* Normal Power-On: Boot from FLASH	*/
#define BOOTFLAG_WARM	0x02	/* Software reboot					*/

#define FEC_INTERRUPT   SIU_LEVEL1

#if defined(CONFIG_SCC1_ENET) && defined(CONFIG_FEC_ENET)
#error Both CONFIG_SCC1_ENET and CONFIG_FEC_ENET configured
#endif

#endif	/* __CONFIG_GEN860T_H */
