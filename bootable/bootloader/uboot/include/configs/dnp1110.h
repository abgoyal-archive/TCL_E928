

#ifndef __CONFIG_H
#define __CONFIG_H

#define CONFIG_SKIP_LOWLEVEL_INIT	1
#undef  CONFIG_SKIP_RELOCATE_UBOOT

#define CONFIG_SA1110		1	/* This is an SA1110 CPU	*/
#define CONFIG_DNP1110		1	/* on an DNP/1110 Board      */

#undef CONFIG_USE_IRQ			/* we don't need IRQ/FIQ stuff */
/* we will never enable dcache, because we have to setup MMU first */
#define CONFIG_SYS_NO_DCACHE

#define CONFIG_SYS_MALLOC_LEN		(CONFIG_ENV_SIZE + 128*1024)
#define CONFIG_SYS_GBL_DATA_SIZE	128	/* size in bytes reserved for initial data */

#define CONFIG_NET_MULTI
#define CONFIG_SMC91111
#define CONFIG_SMC91111_BASE 0x20000300


#define CONFIG_SA1100_SERIAL
#define CONFIG_SERIAL1          1	/* we use SERIAL 1 */

/* allow to overwrite serial and ethaddr */
#define CONFIG_ENV_OVERWRITE

#define CONFIG_BAUDRATE		115200


#define CONFIG_BOOTP_BOOTFILESIZE
#define CONFIG_BOOTP_BOOTPATH
#define CONFIG_BOOTP_GATEWAY
#define CONFIG_BOOTP_HOSTNAME


#include <config_cmd_default.h>


#define CONFIG_BOOTDELAY	3
#define CONFIG_BOOTARGS		"root=ramfs devfs=mount console=ttySA0,115200"
#define CONFIG_ETHADDR		02:80:ad:20:31:b8
#define CONFIG_NETMASK          255.255.0.0
#define CONFIG_IPADDR		172.22.2.23
#define CONFIG_SERVERIP		172.22.2.22
#define CONFIG_BOOTFILE		"dnp1110"
#define CONFIG_BOOTCOMMAND	"tftp; bootm"

#if defined(CONFIG_CMD_KGDB)
#define CONFIG_KGDB_BAUDRATE	230400		/* speed to run kgdb serial port */
#define CONFIG_KGDB_SER_INDEX	2		/* which serial port to use */
#endif

#define	CONFIG_SYS_LONGHELP				/* undef to save memory		*/
#define	CONFIG_SYS_PROMPT		"DNP1110 # "	/* Monitor Command Prompt	*/
#define	CONFIG_SYS_CBSIZE		256		/* Console I/O Buffer Size	*/
#define	CONFIG_SYS_PBSIZE (CONFIG_SYS_CBSIZE+sizeof(CONFIG_SYS_PROMPT)+16) /* Print Buffer Size */
#define	CONFIG_SYS_MAXARGS		16		/* max number of command args	*/
#define CONFIG_SYS_BARGSIZE		CONFIG_SYS_CBSIZE	/* Boot Argument Buffer Size	*/

#define CONFIG_SYS_MEMTEST_START	0xc0400000	/* memtest works on	*/
#define CONFIG_SYS_MEMTEST_END		0xc0800000	/* 4 ... 8 MB in DRAM	*/

#define	CONFIG_SYS_LOAD_ADDR		0xc0200000	/* default load address	*/

#define	CONFIG_SYS_HZ			3686400		/* incrementer freq: 3.6864 MHz */
#define CONFIG_SYS_CPUSPEED		0x0b		/* set core clock to 220 MHz */

						/* valid baudrates */
#define CONFIG_SYS_BAUDRATE_TABLE	{ 9600, 19200, 38400, 57600, 115200 }

#define CONFIG_STACKSIZE	(128*1024)	/* regular stack */
#ifdef CONFIG_USE_IRQ
#define CONFIG_STACKSIZE_IRQ	(4*1024)	/* IRQ stack */
#define CONFIG_STACKSIZE_FIQ	(4*1024)	/* FIQ stack */
#endif

#define CONFIG_NR_DRAM_BANKS	1	   /* we have 1 banks of DRAM */
#define PHYS_SDRAM_1		0xc0000000 /* SDRAM Bank #1 */
#define PHYS_SDRAM_1_SIZE	0x02000000 /* 32 MB */


#define PHYS_FLASH_1		0x00000000 /* Flash Bank #1 */
#define PHYS_FLASH_SIZE		0x01000000 /* 16 MB */
#define PHYS_FLASH_BANK_SIZE    0x01000000 /* 32 MB Banks */
#define PHYS_FLASH_SECT_SIZE    0x00020000 /* 256 KB sectors (x2) */

#define CONFIG_SYS_FLASH_BASE		PHYS_FLASH_1

#define CONFIG_SYS_MAX_FLASH_BANKS	1		/* max number of memory banks		*/
#define CONFIG_SYS_MAX_FLASH_SECT	128		/* max number of sectors on one chip	*/

/* timeout values are in ticks */
#define CONFIG_SYS_FLASH_ERASE_TOUT	(2*CONFIG_SYS_HZ) /* Timeout for Flash Erase */
#define CONFIG_SYS_FLASH_WRITE_TOUT	(2*CONFIG_SYS_HZ) /* Timeout for Flash Write */

#define	CONFIG_ENV_IS_IN_FLASH	1
#define CONFIG_ENV_ADDR			(PHYS_FLASH_1 + 0xF80000)	/* Addr of Environment Sector	*/
#define CONFIG_ENV_SIZE			0x20000						/* Total Size of Environment Sector	*/

#endif	/* __CONFIG_H */
