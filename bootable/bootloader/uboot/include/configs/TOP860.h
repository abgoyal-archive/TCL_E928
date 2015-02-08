

#ifndef __CONFIG_H
#define __CONFIG_H


#define CONFIG_MPC860	1	/* This is a MPC860 CPU		*/
#define CONFIG_MPC860T	1	/* even better... an FEC!	*/
#define CONFIG_TOP860	1	/* ...on a TOP860 module	*/
#undef	CONFIG_WATCHDOG			/* watchdog disabled		*/
#define	CONFIG_IDENT_STRING " EMK TOP860"

#define	CONFIG_SYSCLK	49152000
#define	CONFIG_SYS_XTAL		32768
#define	CONFIG_EBDF		1
#define	CONFIG_COM		3
#define	CONFIG_RTC_MPC8xx

#define CONFIG_SYS_IMMR		0xFFF00000	/* Internal Memory Mapped Register */
#define	CONFIG_SYS_FLASH_BASE	0x80000000	/* FLASH in final mapping */
#define	CONFIG_SYS_DRAM_BASE	0x00000000	/* DRAM in final mapping */
#define	CONFIG_SYS_FLASH_MAX	0x00400000	/* max FLASH to expect */
#define	CONFIG_SYS_DRAM_MAX	0x01000000	/* max DRAM to expect */

#define	CONFIG_SYS_MF			(CONFIG_SYSCLK/CONFIG_SYS_XTAL)
#define	CONFIG_SYS_CPUCLOCK	CONFIG_SYSCLK
#define	CONFIG_SYS_BRGCLOCK	CONFIG_SYSCLK
#define	CONFIG_SYS_BUSCLOCK	(CONFIG_SYSCLK >> CONFIG_EBDF)
#define CONFIG_SYS_HZ			1000	/* decrementer freq: 1 ms ticks */
#define	CONFIG_8xx_GCLK_FREQ	CONFIG_SYSCLK

#define CONFIG_SYS_MAX_FLASH_BANKS	1	/* max number of memory banks		*/
#define CONFIG_SYS_MAX_FLASH_SECT	128	/* max number of sectors on one chip	*/

#define CONFIG_SYS_FLASH_ERASE_TOUT	120000	/* Timeout for Flash Erase (in ms)	*/
#define CONFIG_SYS_FLASH_WRITE_TOUT	500	/* Timeout for Flash Write (in ms)	*/

#define	CONFIG_SYS_FLASH_CFI

#define	CONFIG_8xx_CONS_SMC1	1	/* Console is on SMC1		*/
#undef	CONFIG_8xx_CONS_SMC2
#define CONFIG_BAUDRATE		9600

#define CONFIG_SYS_MATCH_PARTIAL_CMD


#include <config_cmd_default.h>

#define CONFIG_CMD_ASKENV
#define CONFIG_CMD_DHCP
#define CONFIG_CMD_I2C
#define CONFIG_CMD_EEPROM
#define CONFIG_CMD_REGINFO
#define CONFIG_CMD_IMMAP
#define CONFIG_CMD_ELF
#define CONFIG_CMD_DATE
#define CONFIG_CMD_MII
#define CONFIG_CMD_BEDBUG


#define	CONFIG_SOURCE			1
#define	CONFIG_SYS_LOADS_BAUD_CHANGE	1
#undef	CONFIG_LOADS_ECHO			/* NO echo on for serial download	*/


#define CONFIG_SYS_LONGHELP			/* undef to save memory		*/
#define CONFIG_SYS_PROMPT	"=> "		/* Monitor Command Prompt	*/

#undef	CONFIG_SYS_HUSH_PARSER			/* Hush parse for U-Boot	*/

#ifdef	CONFIG_SYS_HUSH_PARSER
 #define CONFIG_SYS_PROMPT_HUSH_PS2	"> "
#endif

#if defined(CONFIG_CMD_KGDB)
 #define CONFIG_SYS_CBSIZE	1024		/* Console I/O Buffer Size	*/
#else
 #define CONFIG_SYS_CBSIZE	256		/* Console I/O Buffer Size	*/
#endif

#define CONFIG_SYS_PBSIZE (CONFIG_SYS_CBSIZE+sizeof(CONFIG_SYS_PROMPT)+16) /* Print Buffer Size */
#define CONFIG_SYS_MAXARGS	16		/* max number of command args	*/
#define CONFIG_SYS_BARGSIZE	CONFIG_SYS_CBSIZE	/* Boot Argument Buffer Size	*/

#define CONFIG_SYS_MEMTEST_START	0x0400000	/* memtest works on	*/
#define CONFIG_SYS_MEMTEST_END		0x0C00000	/* 4 ... 12 MB in DRAM	*/

#define	CONFIG_SOFT_I2C
#define CONFIG_ENV_IS_IN_EEPROM	1	/* turn on EEPROM env feature */
#define CONFIG_ENV_OFFSET		0x1000
#define CONFIG_ENV_SIZE		0x0700
#define CONFIG_SYS_I2C_EEPROM_ADDR 0x57
#define CONFIG_SYS_FACT_OFFSET		0x1800
#define CONFIG_SYS_FACT_SIZE		0x0800
#define CONFIG_SYS_I2C_FACT_ADDR	0x57
#define CONFIG_SYS_EEPROM_PAGE_WRITE_BITS 3
#define CONFIG_SYS_I2C_EEPROM_ADDR_LEN 2
#define CONFIG_SYS_EEPROM_SIZE 0x2000
#define	CONFIG_SYS_I2C_SPEED	100000
#define	CONFIG_SYS_I2C_SLAVE	0xFE
#define	CONFIG_SYS_EEPROM_PAGE_WRITE_DELAY_MS 12
#define CONFIG_ENV_OVERWRITE
#define CONFIG_MISC_INIT_R

#if defined (CONFIG_SOFT_I2C)
#define	SDA	0x00010
#define	SCL	0x00020
#define __I2C_DIR	immr->im_cpm.cp_pbdir
#define __I2C_DAT	immr->im_cpm.cp_pbdat
#define __I2C_PAR	immr->im_cpm.cp_pbpar
#define	__I2C_ODR	immr->im_cpm.cp_pbodr
#define	I2C_INIT	{ __I2C_PAR &= ~(SDA|SCL);	\
			  __I2C_ODR &= ~(SDA|SCL);	\
			  __I2C_DAT |= (SDA|SCL);	\
			  __I2C_DIR|=(SDA|SCL);	}
#define	I2C_READ	((__I2C_DAT & SDA) ? 1 : 0)
#define	I2C_SDA(x)	{ if (x) __I2C_DAT |= SDA; else __I2C_DAT &= ~SDA; }
#define	I2C_SCL(x)	{ if (x) __I2C_DAT |= SCL; else __I2C_DAT &= ~SCL; }
#define	I2C_DELAY	{ udelay(5); }
#define	I2C_ACTIVE	{ __I2C_DIR |= SDA; }
#define	I2C_TRISTATE	{ __I2C_DIR &= ~SDA; }
#endif

#define CONFIG_SYS_BAUDRATE_TABLE	{ 9600, 19200, 38400, 57600, 115200, 230400 }

#define	CONFIG_NET_MULTI	1	/* the only way to get the FEC in */
#define CONFIG_FEC_ENET		1	/* Ethernet only via FEC	*/
#define	FEC_ENET		1	/* eth.c needs it that way... */
#define CONFIG_SYS_DISCOVER_PHY	1
#define CONFIG_MII		1
#define CONFIG_MII_INIT		1
#define CONFIG_PHY_ADDR		31

#define CONFIG_SYS_MONITOR_LEN		(256 << 10)	/* Reserve 256 kB for Monitor	*/
#define CONFIG_SYS_MONITOR_BASE	TEXT_BASE
#define CONFIG_SYS_MALLOC_LEN		(128 << 10)	/* Reserve 128 kB for malloc()	*/

#define CONFIG_SYS_SDRAM_BASE		0x00000000
#define CONFIG_SYS_FLASH_BASE		0x80000000

#define CONFIG_SYS_INIT_RAM_ADDR	CONFIG_SYS_IMMR
#define CONFIG_SYS_INIT_RAM_END	0x2f00	/* End of used area in DPRAM	*/
#define CONFIG_SYS_GBL_DATA_SIZE	64  /* size in bytes reserved for initial data */
#define CONFIG_SYS_GBL_DATA_OFFSET	(CONFIG_SYS_INIT_RAM_END - CONFIG_SYS_GBL_DATA_SIZE)
#define CONFIG_SYS_INIT_VPD_SIZE	256 /* size in bytes reserved for vpd buffer */
#define CONFIG_SYS_INIT_VPD_OFFSET	(CONFIG_SYS_GBL_DATA_OFFSET - CONFIG_SYS_INIT_VPD_SIZE)
#define CONFIG_SYS_INIT_SP_OFFSET	(CONFIG_SYS_INIT_VPD_OFFSET-8)

#define CONFIG_SYS_CACHELINE_SIZE	16	/* For all MPC8xx CPUs			*/
#if defined(CONFIG_CMD_KGDB)
#define CONFIG_SYS_CACHELINE_SHIFT	4	/* log base 2 of the above value	*/
#endif

#define FEC_INTERRUPT	SIU_LEVEL1	/* FEC interrupt */

#define BOOTFLAG_COLD	0x01		/* Normal Power-On: Boot from FLASH	*/
#define BOOTFLAG_WARM	0x02		/* Software reboot			*/

#define CONFIG_SYS_DER 0					/* used in start.S */

#define CONFIG_SYS_PLPRCR	(PLPRCR_TEXPS | ((CONFIG_SYS_MF-1)<<20))

#if defined (CONFIG_WATCHDOG)
 #define CONFIG_SYS_SYPCR	(SYPCR_SWTC | SYPCR_BMT | SYPCR_BME | SYPCR_SWF | \
					 SYPCR_SWE  | SYPCR_SWRI| SYPCR_SWP)
#else
 #define CONFIG_SYS_SYPCR	(SYPCR_SWTC | SYPCR_BMT | SYPCR_BME | SYPCR_SWF)
#endif

#define CONFIG_SYS_SIUMCR	(SIUMCR_MLRC11)

#define CONFIG_SYS_TBSCR	(TBSCR_REFA | TBSCR_REFB | TBSCR_TBF)

#define CONFIG_SYS_PISCR	(PISCR_PS | PISCR_PITF | PISCR_PTE)

#define SCCR_MASK	0
#ifdef CONFIG_EBDF
 #define CONFIG_SYS_SCCR	(SCCR_COM11 | SCCR_TBS | SCCR_EBDF01)
#else
 #define CONFIG_SYS_SCCR	(SCCR_COM11 | SCCR_TBS)
#endif

/* FLASH timing: CSNT=1 ACS=10 BIH=1 SCY=4 SETA=0 TLRX=1 EHTR=1	*/
#define CONFIG_SYS_OR_TIMING_FLASH	(OR_CSNT_SAM  | OR_ACS_DIV4 | OR_BI | OR_SCY_4_CLK | OR_TRLX | OR_EHTR)
#define CONFIG_SYS_OR0_PRELIM	(-CONFIG_SYS_FLASH_MAX | CONFIG_SYS_OR_TIMING_FLASH)
#define CONFIG_SYS_BR0_PRELIM	(CONFIG_SYS_FLASH_BASE | BR_PS_16 | BR_V )

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

#define CONFIG_BOOTP_SUBNETMASK
#define CONFIG_BOOTP_GATEWAY
#define CONFIG_BOOTP_HOSTNAME
#define CONFIG_BOOTP_BOOTPATH
#define CONFIG_BOOTP_BOOTFILESIZE


#define CONFIG_ETHADDR					9a:52:63:15:85:25
#define CONFIG_SERVERIP					10.0.4.200
#define CONFIG_IPADDR					10.0.4.111

#define CONFIG_SYS_LOAD_ADDR		0x00100000	/* default load address */
#define	CONFIG_SYS_TFTP_LOADADDR	0x00100000

#define CONFIG_SYS_BOOTMAPSZ		(8 << 20)	/* Initial Memory map for Linux */

#endif	/* __CONFIG_H */
