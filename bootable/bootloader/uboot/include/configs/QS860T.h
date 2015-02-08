


#ifndef __CONFIG_H
#define __CONFIG_H

/* various debug settings */
#undef CONFIG_SYS_DEVICE_NULLDEV		/* null device */
#undef CONFIG_SILENT_CONSOLE		/* silent console */
#undef CONFIG_SYS_CONSOLE_INFO_QUIET		/* silent console ? */
#undef DEBUG_FLASH			/* debug flash code */
#undef FLASH_DEBUG			/* debug fash code */
#undef DEBUG_ENV			/* debug environment code */

#define CONFIG_SYS_DIRECT_FLASH_TFTP	1	/* allow direct tftp to flash */
#define CONFIG_ENV_OVERWRITE	1	/* allow overwrite MAC address */



#define CONFIG_MPC860		1	/* This is a MPC860 CPU */
#define CONFIG_QS860T		1	/* ...on a QS860T module */

#define CONFIG_FEC_ENET		1	/* FEC 10/100BaseT ethernet */
#define CONFIG_MII
#define FEC_INTERRUPT		SIU_LEVEL1
#undef CONFIG_SCC1_ENET			/* SCC1 10BaseT ethernet */
#define CONFIG_SYS_DISCOVER_PHY

#undef CONFIG_8xx_CONS_SMC1
#define CONFIG_8xx_CONS_SMC2	1	/* Console is on SMC */
#undef CONFIG_8xx_CONS_NONE

#define CONFIG_BAUDRATE		38400	/* console baudrate = 38.4kbps */

#define CONFIG_BOOTDELAY	5	/* autoboot after 5 seconds */

/* Pass clocks to Linux 2.4.18 in Hz */
#undef CONFIG_CLOCKS_IN_MHZ		/* clocks passsed to Linux in MHz */

#define CONFIG_PREBOOT		"echo;" \
	"echo 'Type \\\"run flash_nfs\\\" to mount root filesystem over NFS';" \
	"echo"

#undef CONFIG_BOOTARGS
/* TODO compare against CADM860 */
#define CONFIG_BOOTCOMMAND	"bootp; " \
	"setenv bootargs root=/dev/nfs rw nfsroot=${serverip}:${rootpath} " \
	"ip=${ipaddr}:${serverip}:${gatewayip}:${netmask}:${hostname}::off; " \
	"bootm"

#define CONFIG_LOADS_ECHO	1	/* echo on for serial download */
#undef CONFIG_SYS_LOADS_BAUD_CHANGE		/* don't allow baudrate change */

#undef CONFIG_WATCHDOG			/* watchdog disabled */

#undef CONFIG_STATUS_LED		/* Status LED disabled */

#undef CONFIG_CAN_DRIVER		/* CAN Driver support disabled */

#define CONFIG_BOOTP_SUBNETMASK
#define CONFIG_BOOTP_GATEWAY
#define CONFIG_BOOTP_HOSTNAME
#define CONFIG_BOOTP_BOOTPATH
#define CONFIG_BOOTP_BOOTFILESIZE


#define CONFIG_MAC_PARTITION
#define CONFIG_DOS_PARTITION

#define CONFIG_RTC_MPC8xx	/* use internal RTC of MPC8xx */


#include <config_cmd_default.h>

#define CONFIG_CMD_REGINFO
#define CONFIG_CMD_IMMAP
#define CONFIG_CMD_ASKENV
#define CONFIG_CMD_NET
#define CONFIG_CMD_DHCP
#define CONFIG_CMD_DATE


/* TODO */
#if 0
/* Look at these */
CONFIG_IPADDR
CONFIG_SERVERIP
CONFIG_I2C
CONFIG_SPI
#endif

#define CONFIG_ENV_IS_IN_NVRAM	1
#define CONFIG_ENV_SIZE		0x00001000	/* We use only the last 4K for PPCBoot */
#define CONFIG_ENV_ADDR		0xD100E000

#define CONFIG_SYS_LONGHELP				/* undef to save memory */
#define CONFIG_SYS_PROMPT		"=> "		/* Monitor Command Prompt */

#define CONFIG_SYS_HUSH_PARSER		1		/* use "hush" command parser */
#define CONFIG_SYS_PROMPT_HUSH_PS2	"> "

#if defined(CONFIG_CMD_KGDB)
#define CONFIG_SYS_CBSIZE		1024		/* Console I/O Buffer Size */
#else
#define CONFIG_SYS_CBSIZE		256		/* Console I/O Buffer Size */
#endif
#define CONFIG_SYS_PBSIZE		(CONFIG_SYS_CBSIZE+sizeof(CONFIG_SYS_PROMPT)+16) /* Print Buffer Size */
#define CONFIG_SYS_MAXARGS		16		/* max number of command args */
#define CONFIG_SYS_BARGSIZE		CONFIG_SYS_CBSIZE	/* Boot Argument Buffer Size */

/* TODO - size? */
#define CONFIG_SYS_MEMTEST_START	0x0400000	/* memtest works */
#define CONFIG_SYS_MEMTEST_END		0x0C00000	/* 4 ... 12 MB in DRAM */

#define CONFIG_SYS_LOAD_ADDR		0x100000	/* default load address */

#define CONFIG_SYS_HZ			1000		/* decrementer freq: 1 ms ticks */

#define CONFIG_SYS_BAUDRATE_TABLE	{ 9600, 19200, 38400, 57600, 115200 }

#define CONFIG_SYS_IMMR		0xF0000000

#define CONFIG_SYS_INIT_RAM_ADDR	CONFIG_SYS_IMMR
#define CONFIG_SYS_INIT_RAM_END	0x2F00		/* End of used area in DPRAM */
#define CONFIG_SYS_GBL_DATA_SIZE	64		/* size in bytes reserved for initial data */
#define CONFIG_SYS_GBL_DATA_OFFSET	(CONFIG_SYS_INIT_RAM_END - CONFIG_SYS_GBL_DATA_SIZE)
#define CONFIG_SYS_INIT_SP_OFFSET	CONFIG_SYS_GBL_DATA_OFFSET

#define CONFIG_SYS_SDRAM_BASE		0x00000000
#define CONFIG_SYS_FLASH_BASE		0xFFF00000

#define CONFIG_SYS_MONITOR_LEN		(192 << 10)	/* Reserve 192 kB for Monitor */
#define CONFIG_SYS_MONITOR_BASE	CONFIG_SYS_FLASH_BASE
#define CONFIG_SYS_MALLOC_LEN		(128 << 10)	/* Reserve 128 kB for malloc() */

#define CONFIG_SYS_BOOTMAPSZ		(8 << 20)	/* Initial Memory map for Linux */

/* TODO flash parameters */
#define CONFIG_SYS_FLASH_16BIT		1		/* 16-bit wide flash memory */
#define CONFIG_SYS_MAX_FLASH_BANKS	1		/* max number of memory banks */
#define CONFIG_SYS_MAX_FLASH_SECT	64		/* max number of sectors on one chip */

#define CONFIG_SYS_FLASH_ERASE_TOUT	120000		/* Timeout for Flash Erase (in ms) */
#define CONFIG_SYS_FLASH_WRITE_TOUT	500		/* Timeout for Flash Write (in ms) */

#undef	CONFIG_ENV_IS_IN_FLASH

#define CONFIG_SYS_CACHELINE_SIZE	16		/* For all MPC8xx CPUs */
#if defined(CONFIG_CMD_KGDB)
#define CONFIG_SYS_CACHELINE_SHIFT	4		/* log base 2 of the above value */
#endif

#if defined(CONFIG_WATCHDOG)
#define CONFIG_SYS_SYPCR	(0xFFFFFF88 | SYPCR_SWE | SYPCR_SWRI)
#else
#define CONFIG_SYS_SYPCR	0xFFFFFF88
#endif

#define CONFIG_SYS_SIUMCR	0x00620000

#define CONFIG_SYS_TBSCR	0x00C3

#define CONFIG_SYS_RTCSC	(RTCSC_SEC | RTCSC_ALR | RTCSC_RTF| RTCSC_RTE)

#define CONFIG_SYS_PISCR	0x0082

#define CONFIG_SYS_PLPRCR	0x0090D000

#define SCCR_MASK	SCCR_EBDF11
#define CONFIG_SYS_SCCR	0x02000000


#define CONFIG_SYS_DER			0x0082400F



#define CONFIG_SYS_PRELIM_OR_AM
#define CONFIG_SYS_OR_TIMING_FLASH

#define FLASH_BASE0_PRELIM	0xFFF00001
#define CONFIG_SYS_OR0_PRELIM		0xFFF80D42
#define CONFIG_SYS_BR0_PRELIM		0xFFF00401



#define FLASH_BASE1_PRELIM	0xD0000000
#define CONFIG_SYS_OR1_PRELIM		0xFF800D42
#define CONFIG_SYS_BR1_PRELIM		0xD0000801
/* #define CONFIG_SYS_OR1		0xFF800D42 */
/* #define CONFIG_SYS_BR1		0xD0000801 */


#define SDRAM_BASE		0x00000000	/* SDRAM bank */
#define SDRAM_PRELIM_OR_AM	0xF8000000	/* map max. 128 MB */

/* SDRAM timing */
#define SDRAM_TIMING		0x00000A00

/* For boards with 16M of SDRAM */
#define SDRAM_16M_MAX_SIZE	0x01000000	/* max 16MB SDRAM */
#define CONFIG_SYS_16M_MBMR		0x18802114	/* Mem Periodic Timer Prescaler */

/* For boards with 64M of SDRAM */
#define SDRAM_64M_MAX_SIZE	0x04000000	/* max 64MB SDRAM */
/* TODO - determine real value */
#define CONFIG_SYS_64M_MBMR		0x18802114	/* Mem Period Timer Prescaler */

#define CONFIG_SYS_OR2			(SDRAM_PRELIM_OR_AM | SDRAM_TIMING)
#define CONFIG_SYS_BR2			(SDRAM_BASE | 0x000000C1)



#define CONFIG_SYS_OR3_PRELIM		0xFFC00DF6
#define CONFIG_SYS_BR3_PRELIM		0xD1000401
/* #define CONFIG_SYS_OR3		0xFFC00DF6 */
/* #define CONFIG_SYS_BR3		0xD1000401 */



#define CONFIG_SYS_OR4_PRELIM		0xFF000000
#define CONFIG_SYS_BR4_PRELIM		0xE0000000
/* #define CONFIG_SYS_OR4		0xFF000000 */
/* #define CONFIG_SYS_BR4		0xE0000000 */



#define CONFIG_SYS_OR5_PRELIM		0xFF000000
#define CONFIG_SYS_BR5_PRELIM		0xE4000000
/* #define CONFIG_SYS_OR5		0xFF000000 */
/* #define CONFIG_SYS_BR5		0xE4000000 */



#define CONFIG_SYS_OR6_PRELIM		0xFF000000
#define CONFIG_SYS_BR6_PRELIM		0xE8000000
/* #define CONFIG_SYS_OR6		0xFF000000 */
/* #define CONFIG_SYS_BR6		0xE8000000 */



#define CONFIG_SYS_OR7_PRELIM		0xFF000000
#define CONFIG_SYS_BR7_PRELIM		0xE8000000
/* #define CONFIG_SYS_OR7		0xFF000000 */
/* #define CONFIG_SYS_BR7		0xE8000000 */


#define BOOTFLAG_COLD		0x01	/* Normal Power-On: Boot from FLASH */
#define BOOTFLAG_WARM		0x02	/* Software reboot */

#if defined(CONFIG_SCC1_ENET) && defined(CONFIG_FEC_ENET)
#error Both CONFIG_SCC1_ENET and CONFIG_FEC_ENET configured
#endif

#endif /* __CONFIG_H */
