


#ifndef __CONFIG_H
#define __CONFIG_H

#define CONFIG_MCU25		1		/* Board is MCU25	*/
#define CONFIG_4xx		1		/* ... PPC4xx family	*/
#define CONFIG_405GP 1
#define CONFIG_4xx   1
#define CONFIG_HOSTNAME		mcu25

#include "netstal-common.h"

#define CONFIG_SYS_CLK_FREQ	33333333	/* external freq to pll	*/

#define CONFIG_BOARD_EARLY_INIT_F 1		/* Call board_early_init_f */
#define CONFIG_MISC_INIT_R	1		/* Call misc_init_r	*/

#define CONFIG_SYS_MONITOR_LEN		(320 * 1024) /* Reserve 320 kB for Monitor */
#define CONFIG_SYS_MALLOC_LEN		(256 * 1024) /* Reserve 256 kB for malloc() */


#define CONFIG_SYS_SDRAM_BASE		0x00000000	/* _must_ be 0		*/
#define CONFIG_SYS_FLASH_BASE		0xfff80000	/* start of FLASH	*/
#define CONFIG_SYS_MONITOR_BASE	TEXT_BASE

/* ... with on-chip memory here (4KBytes) */
#define CONFIG_SYS_OCM_DATA_ADDR	0xF4000000
#define CONFIG_SYS_OCM_DATA_SIZE	0x00001000
/* Do not set up locked dcache as init ram. */
#undef CONFIG_SYS_INIT_DCACHE_CS

/* Use the On-Chip-Memory (OCM) as a temporary stack for the startup code. */
#define CONFIG_SYS_TEMP_STACK_OCM	1

#define CONFIG_SYS_INIT_RAM_ADDR	CONFIG_SYS_OCM_DATA_ADDR	/* OCM		*/
#define CONFIG_SYS_INIT_RAM_END	CONFIG_SYS_OCM_DATA_SIZE
#define CONFIG_SYS_GBL_DATA_SIZE	256		/* num bytes initial data */
#define CONFIG_SYS_GBL_DATA_OFFSET	(CONFIG_SYS_INIT_RAM_END - CONFIG_SYS_GBL_DATA_SIZE)
#define CONFIG_SYS_INIT_SP_OFFSET	CONFIG_SYS_POST_WORD_ADDR

/* needed to be able to define CONFIG_SERIAL_SOFTWARE_FIFO */
#undef	CONFIG_SYS_405_UART_ERRATA_59	       /* 405GP/CR Rev. D silicon */
#define CONFIG_SYS_BASE_BAUD	    691200

#undef CONFIG_SERIAL_SOFTWARE_FIFO

/* Set console baudrate to 9600 */
#define CONFIG_BAUDRATE		9600


/* Use common CFI driver */
#define CONFIG_SYS_FLASH_CFI
#define CONFIG_FLASH_CFI_DRIVER
/* board provides its own flash_init code */
#define CONFIG_FLASH_CFI_LEGACY		1
#define CONFIG_SYS_FLASH_CFI_WIDTH		FLASH_CFI_8BIT
#define CONFIG_SYS_FLASH_LEGACY_512Kx8 1

/* print 'E' for empty sector on flinfo */
#define CONFIG_SYS_FLASH_EMPTY_INFO

#define CONFIG_SYS_MAX_FLASH_BANKS	1	/* max number of memory banks */
#define CONFIG_SYS_MAX_FLASH_SECT	8	/* max number of sectors on one chip */


#undef	CONFIG_ENV_IS_IN_NVRAM
#define CONFIG_ENV_IS_IN_FLASH
#undef  CONFIG_ENV_IS_NOWHERE

#ifdef  CONFIG_ENV_IS_IN_EEPROM
/* Put the environment after the SDRAM configuration */
#define PROM_SIZE	2048
#define CONFIG_ENV_OFFSET	 512
#define CONFIG_ENV_SIZE	(PROM_SIZE-CONFIG_ENV_OFFSET)
#endif

#ifdef CONFIG_ENV_IS_IN_FLASH
/* Put the environment in Flash */
#define CONFIG_ENV_SECT_SIZE	0x10000 /* size of one complete sector */
#define CONFIG_ENV_ADDR		((-CONFIG_SYS_MONITOR_LEN)-CONFIG_ENV_SECT_SIZE)
#define	CONFIG_ENV_SIZE		8*1024	/* 8 KB Environment Sector */

/* Address and size of Redundant Environment Sector	*/
#define CONFIG_ENV_ADDR_REDUND	(CONFIG_ENV_ADDR-CONFIG_ENV_SECT_SIZE)
#define CONFIG_ENV_SIZE_REDUND	(CONFIG_ENV_SIZE)
#endif

#define CONFIG_SYS_SPD_BUS_NUM		0

/* Setup some board specific values for the default environment variables */
#define CONFIG_IPADDR		172.25.1.25

#define	CONFIG_EXTRA_ENV_SETTINGS					\
	CONFIG_NETSTAL_DEF_ENV						\
	CONFIG_NETSTAL_DEF_ENV_POWERPC					\
	""

#define CONFIG_BOOTP_BOOTFILESIZE
#define CONFIG_BOOTP_BOOTPATH
#define CONFIG_BOOTP_GATEWAY
#define CONFIG_BOOTP_HOSTNAME

#include <config_cmd_default.h>

#define CONFIG_CMD_ASKENV
#define CONFIG_CMD_CACHE
#define CONFIG_CMD_DHCP
#define CONFIG_CMD_DIAG
#define CONFIG_CMD_EEPROM
#define CONFIG_CMD_ELF
#define CONFIG_CMD_FLASH
#define CONFIG_CMD_I2C
#define CONFIG_CMD_IMMAP
#define CONFIG_CMD_IRQ
#define CONFIG_CMD_MII
#define CONFIG_CMD_NET
#define CONFIG_CMD_PING
#define CONFIG_CMD_REGINFO
#define CONFIG_CMD_SDRAM

/* SPD EEPROM (sdram speed config) disabled */
#define CONFIG_SPD_EEPROM          1
#define SPD_EEPROM_ADDRESS      0x50

/* POST support */
#define CONFIG_POST		(CONFIG_SYS_POST_MEMORY   | \
				 CONFIG_SYS_POST_CPU	   | \
				 CONFIG_SYS_POST_UART	   | \
				 CONFIG_SYS_POST_I2C	   | \
				 CONFIG_SYS_POST_CACHE	   | \
				 CONFIG_SYS_POST_ETHER	   | \
				 CONFIG_SYS_POST_SPR)

#define CONFIG_SYS_POST_UART_TABLE	{UART0_BASE}
#define CONFIG_SYS_POST_WORD_ADDR	(CONFIG_SYS_GBL_DATA_OFFSET - 0x4)
#undef  CONFIG_LOGBUFFER
#define CONFIG_SYS_POST_CACHE_ADDR	0x00800000 /* free virtual address	*/
#define CONFIG_SYS_CONSOLE_IS_IN_ENV /* Otherwise it catches logbuffer as output */

#define CONFIG_SYS_LONGHELP			/* undef to save memory		*/
#define CONFIG_SYS_PROMPT	"=> "		/* Monitor Command Prompt	*/
#if defined(CONFIG_CMD_KGDB)
	#define CONFIG_SYS_CBSIZE	1024		/* Console I/O Buffer Size */
#else
	#define CONFIG_SYS_CBSIZE	256		/* Console I/O Buffer Size */
#endif
#define CONFIG_SYS_PBSIZE (CONFIG_SYS_CBSIZE+sizeof(CONFIG_SYS_PROMPT)+16) /* Print Buffer Size */
#define CONFIG_SYS_MAXARGS	16		/* max number of command args	*/
#define CONFIG_SYS_BARGSIZE	CONFIG_SYS_CBSIZE	/* Boot Argument Buffer Size	*/

#define CONFIG_SYS_MEMTEST_START	0x0400000	/* memtest works on	*/
#define CONFIG_SYS_MEMTEST_END		0x0C00000	/* 4 ... 12 MB in DRAM	*/


#define CONFIG_SYS_LOAD_ADDR		0x100000	/* default load address */


#define CONFIG_SYS_EBC_CFG            0x98400000

/* Memory Bank 0 (Flash Bank 0) initialization	*/
#define CONFIG_SYS_EBC_PB0AP		0x02005400
#define CONFIG_SYS_EBC_PB0CR		0xFFF18000  /* BAS=0xFFF,BS=1MB,BU=R/W,BW=8bit*/

#define CONFIG_SYS_EBC_PB1AP		0x03041200
#define CONFIG_SYS_EBC_PB1CR		0x7009A000  /* BAS=,BS=MB,BU=R/W,BW=bit	*/

#define CONFIG_SYS_EBC_PB2AP		0x01845200u  /* BAS=,BS=MB,BU=R/W,BW=bit */
#define CONFIG_SYS_EBC_PB2CR		0x7A09A000u

#define CONFIG_SYS_EBC_PB3AP		0x01845200u  /* BAS=,BS=MB,BU=R/W,BW=bit */
#define CONFIG_SYS_EBC_PB3CR		0x7B09A000u

#define CONFIG_SYS_EBC_PB4AP		0x01845200u  /* BAS=,BS=MB,BU=R/W,BW=bit */
#define CONFIG_SYS_EBC_PB4CR		0x7C09A000u

#define CONFIG_SYS_EBC_PB5AP		0x00800200u
#define CONFIG_SYS_EBC_PB5CR		0x7D81A000u

#define CONFIG_SYS_EBC_PB6AP		0x01040200u
#define CONFIG_SYS_EBC_PB6CR		0x7D91A000u

#define CONFIG_SYS_GPIO0_OR		0x087FFFFF  /* GPIO value */
#define CONFIG_SYS_GPIO0_TCR		0x7FFF8000  /* GPIO value */
#define CONFIG_SYS_GPIO0_ODR		0xFFFF0000  /* GPIO value */
#define CONFIG_SYS_BOOTMAPSZ		(8 << 20) /* Initial Memory map for Linux */


#define FLASH_BASE0_PRELIM	CONFIG_SYS_FLASH_BASE	/* FLASH bank #0	*/
#define FLASH_BASE1_PRELIM	0		/* FLASH bank #1	*/


/* Configuration Port location */
#define CONFIG_PORT_ADDR	0xF0000500

#define CONFIG_SYS_HUSH_PARSER                 /* use "hush" command parser    */
#ifdef  CONFIG_SYS_HUSH_PARSER
#define CONFIG_SYS_PROMPT_HUSH_PS2	"> "
#endif

#if defined(CONFIG_CMD_KGDB)
#define CONFIG_KGDB_BAUDRATE	230400	/* speed to run kgdb serial port */
#define CONFIG_KGDB_SER_INDEX	2	    /* which serial port to use */
#endif

#endif	/* __CONFIG_H */
