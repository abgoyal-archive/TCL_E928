

#ifndef __CONFIG_H
#define __CONFIG_H

#undef  CONFIG_SKIP_LOWLEVEL_INIT
#define CONFIG_SKIP_RELOCATE_UBOOT	1

#define CONFIG_SA1110		1	/* This is an SA1100 CPU	*/
#define CONFIG_GCPLUS		1	/* on an ADS GCPlus Board      */

#undef CONFIG_USE_IRQ			/* we don't need IRQ/FIQ stuff */
/* we will never enable dcache, because we have to setup MMU first */
#define CONFIG_SYS_NO_DCACHE

#define CONFIG_CMDLINE_TAG	 1	/* enable passing of ATAGs	*/
#define CONFIG_SETUP_MEMORY_TAGS 1
#define CONFIG_INITRD_TAG	 1

#define CONFIG_SYS_MALLOC_LEN          (CONFIG_ENV_SIZE + 128*1024)
#define CONFIG_SYS_GBL_DATA_SIZE       128     /* size rsrvd for initial data */


#define CONFIG_NET_MULTI
#define CONFIG_LAN91C96	/* we have an SMC9194 on-board */
#define CONFIG_LAN91C96_BASE	0x100e0000

#define CONFIG_SA1100_SERIAL
#define CONFIG_SERIAL3          1	/* we use SERIAL 3 on ADS GCPlus */

/* allow to overwrite serial and ethaddr */
#define CONFIG_ENV_OVERWRITE

#define CONFIG_BAUDRATE		38400


#include <config_cmd_default.h>

#define CONFIG_CMD_DHCP


#define CONFIG_BOOTP_SUBNETMASK
#define CONFIG_BOOTP_GATEWAY
#define CONFIG_BOOTP_HOSTNAME
#define CONFIG_BOOTP_BOOTPATH


#define CONFIG_BOOTDELAY	3
#define CONFIG_BOOTARGS		"console=ttySA0,38400n8 mtdparts=sa1100-flash:1m@0(zImage),3m@1m(ramdisk.gz),12m@4m(userfs) root=/dev/nfs ip=bootp"
#define CONFIG_BOOTCOMMAND	"bootp;tftp;bootm"
#define CONFIG_SYS_AUTOLOAD            "n"             /* No autoload */

#if defined(CONFIG_CMD_KGDB)
#define CONFIG_KGDB_BAUDRATE	38400		/* speed to run kgdb serial port */
#define CONFIG_KGDB_SER_INDEX	2		/* which serial port to use */
#endif

#define	CONFIG_SYS_LONGHELP				/* undef to save memory		*/
#define	CONFIG_SYS_PROMPT		"ADS GCPlus # "	/* Monitor Command Prompt	*/
#define	CONFIG_SYS_CBSIZE		256		/* Console I/O Buffer Size	*/
#define	CONFIG_SYS_PBSIZE (CONFIG_SYS_CBSIZE+sizeof(CONFIG_SYS_PROMPT)+16) /* Print Buffer Size */
#define	CONFIG_SYS_MAXARGS		16		/* max number of command args	*/
#define CONFIG_SYS_BARGSIZE		CONFIG_SYS_CBSIZE	/* Boot Argument Buffer Size	*/

#define CONFIG_SYS_MEMTEST_START	0xc0400000	/* memtest works on	*/
#define CONFIG_SYS_MEMTEST_END		0xc0800000	/* 4 ... 8 MB in DRAM	*/

#define	CONFIG_SYS_LOAD_ADDR		0xc0000000	/* default load address	*/

#define	CONFIG_SYS_HZ			3686400		/* incrementer freq: 3.6864 MHz */
#define CONFIG_SYS_CPUSPEED		0x0a		/* set core clock to 206MHz */

						/* valid baudrates */
#define CONFIG_SYS_BAUDRATE_TABLE	{ 9600, 19200, 38400, 57600, 115200 }

#define CONFIG_STACKSIZE	(128*1024)	/* regular stack */
#ifdef CONFIG_USE_IRQ
#define CONFIG_STACKSIZE_IRQ	(4*1024)	/* IRQ stack */
#define CONFIG_STACKSIZE_FIQ	(4*1024)	/* FIQ stack */
#endif

#define CONFIG_NR_DRAM_BANKS	2	   /* we have 2 banks of DRAM */
#define PHYS_SDRAM_1		0xc0000000 /* SDRAM Bank #1 */
#define PHYS_SDRAM_1_SIZE	0x01000000 /* 16 MB */
#define PHYS_SDRAM_2		0xc8000000 /* SDRAM Bank #2 */
#define PHYS_SDRAM_2_SIZE	0x01000000 /* 16 MB */


#define PHYS_FLASH_1		0x08000000 /* Flash Bank #1 */
#define PHYS_FLASH_SIZE		0x00800000 /* 8 MB */
#define PHYS_FLASH_BANK_SIZE    0x01000000 /* 16 MB Banks */
#define PHYS_FLASH_SECT_SIZE    0x00040000 /* 256 KB sectors (x2) */

#define CONFIG_SYS_FLASH_BASE		PHYS_FLASH_1

#if	1
#define CONFIG_SYS_MAX_FLASH_BANKS	1	/* max number of memory banks */
#define CONFIG_SYS_MAX_FLASH_SECT	128	/* max number of sectors on one chip */

/* timeout values are in ticks */
#define CONFIG_SYS_FLASH_ERASE_TOUT	(2*CONFIG_SYS_HZ) /* Timeout for Flash Erase */
#define CONFIG_SYS_FLASH_WRITE_TOUT	(2*CONFIG_SYS_HZ) /* Timeout for Flash Write */
#else
/* REVISIT: This doesn't work on ADS GCPlus just yet: */
#define CONFIG_SYS_FLASH_CFI           1       /* flash is CFI conformant      */
#define CONFIG_FLASH_CFI_DRIVER    1       /* use common cfi driver        */
#define CONFIG_SYS_FLASH_USE_BUFFER_WRITE 1    /* use buffered writes (20x faster) */
#define CONFIG_SYS_MAX_FLASH_BANKS     1       /* max # of memory banks        */
#define CONFIG_SYS_FLASH_INCREMENT     0       /* there is only one bank       */
#define CONFIG_SYS_MAX_FLASH_SECT      128     /* max # of sectors on one chip */
/*#define CONFIG_SYS_FLASH_PROTECTION    1       /--* hardware flash protection    */
#define CONFIG_SYS_FLASH_BANKS_LIST    { CONFIG_SYS_FLASH_BASE }
#endif

#define	CONFIG_ENV_IS_IN_FLASH	1
#define CONFIG_ENV_ADDR		(PHYS_FLASH_1 + PHYS_FLASH_SECT_SIZE)	/* Addr of Environment Sector	*/
#define CONFIG_ENV_SIZE		PHYS_FLASH_SECT_SIZE

#endif	/* __CONFIG_H */
