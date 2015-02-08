

#ifndef __CONFIG_H
#define __CONFIG_H

#define CONFIG_PXA250		1	/* This is an PXA255 CPU    */
#define CONFIG_XAENIAX		1	/* on a xaeniax board	    */


#define BOARD_LATE_INIT		1


#undef CONFIG_USE_IRQ			/* we don't need IRQ/FIQ stuff */

/* we will never enable dcache, because we have to setup MMU first */
#define CONFIG_SYS_NO_DCACHE

#define CONFIG_PXA_SERIAL
#define CONFIG_BTUART	       1       /* we use BTUART on XAENIAX */


/* allow to overwrite serial and ethaddr */
#define CONFIG_ENV_OVERWRITE

#define	CONFIG_TIMESTAMP		/* Print image info with timestamp */

#define CONFIG_BAUDRATE		115200

#define CONFIG_SYS_BAUDRATE_TABLE	{ 9600, 19200, 38400, 57600, 115200 } /* valid baudrates */


#define CONFIG_BOOTP_BOOTFILESIZE
#define CONFIG_BOOTP_BOOTPATH
#define CONFIG_BOOTP_GATEWAY
#define CONFIG_BOOTP_HOSTNAME


#include <config_cmd_default.h>

#define CONFIG_CMD_DHCP
#define CONFIG_CMD_DIAG
#define CONFIG_CMD_NFS
#define CONFIG_CMD_SDRAM
#define CONFIG_CMD_SNTP

#undef CONFIG_CMD_DTT


#define CONFIG_ETHADDR		08:00:3e:26:0a:5b
#define CONFIG_NETMASK		255.255.255.0
#define CONFIG_IPADDR		192.168.68.201
#define CONFIG_SERVERIP		192.168.68.62

#define CONFIG_BOOTDELAY	3
#define CONFIG_BOOTCOMMAND	"bootm 0x00100000"
#define CONFIG_BOOTARGS		"console=ttyS1,115200"
#define CONFIG_CMDLINE_TAG		1	/* enable passing of ATAGs */
#define CONFIG_SETUP_MEMORY_TAGS	1
#define CONFIG_INITRD_TAG		1

#if defined(CONFIG_CMD_KGDB)
#define CONFIG_KGDB_BAUDRATE	115200			/* speed to run kgdb serial port */
#define CONFIG_KGDB_SER_INDEX	1			/* which serial port to use */
#endif

#define CONFIG_SYS_MALLOC_LEN	    (CONFIG_ENV_SIZE + 128*1024)
#define CONFIG_SYS_GBL_DATA_SIZE	128	/* size in bytes reserved for initial data */

#define CONFIG_SYS_LONGHELP				/* undef to save memory	*/
#define CONFIG_SYS_HUSH_PARSER		1

#define CONFIG_SYS_PROMPT_HUSH_PS2	"> "

#ifdef CONFIG_SYS_HUSH_PARSER
#define CONFIG_SYS_PROMPT		"u-boot$ "	/* Monitor Command Prompt */
#else
#define CONFIG_SYS_PROMPT		"u-boot=> "	/* Monitor Command Prompt */
#endif
#define CONFIG_SYS_CBSIZE		256		/* Console I/O Buffer Size	*/
#define CONFIG_SYS_PBSIZE (CONFIG_SYS_CBSIZE+sizeof(CONFIG_SYS_PROMPT)+16) /* Print Buffer Size */
#define CONFIG_SYS_MAXARGS		16		/* max number of command args	*/
#define CONFIG_SYS_BARGSIZE		CONFIG_SYS_CBSIZE	/* Boot Argument Buffer Size	*/
#define CONFIG_SYS_DEVICE_NULLDEV	1

#define CONFIG_SYS_MEMTEST_START	0xa0400000	/* memtest works on	*/
#define CONFIG_SYS_MEMTEST_END		0xa0800000	/* 4 ... 8 MB in DRAM	*/

#define CONFIG_SYS_LOAD_ADDR		0xa1000000	/* default load address */

#define CONFIG_SYS_HZ			1000
#define CONFIG_SYS_CPUSPEED		0x141		/* set core clock to 400/200/100 MHz */

#define CONFIG_NR_DRAM_BANKS	1	   /* we have 1 banks (partition) of DRAM */
#define PHYS_SDRAM_1		0xa0000000 /* SDRAM Bank #1 */
#define PHYS_SDRAM_1_SIZE	0x04000000 /* 64 MB */
#define PHYS_SDRAM_2		0xa4000000 /* SDRAM Bank #2 */
#define PHYS_SDRAM_2_SIZE	0x00000000 /* 0 MB */
#define PHYS_SDRAM_3		0xa8000000 /* SDRAM Bank #3 */
#define PHYS_SDRAM_3_SIZE	0x00000000 /* 0 MB */
#define PHYS_SDRAM_4		0xac000000 /* SDRAM Bank #4 */
#define PHYS_SDRAM_4_SIZE	0x00000000 /* 0 MB */

#define PHYS_FLASH_1		0x00000000 /* Flash Bank #1 */
#define PHYS_FLASH_2		0x04000000 /* Flash Bank #2 */
#define PHYS_FLASH_SIZE		0x02000000 /* 32 MB */
#define PHYS_FLASH_BANK_SIZE	0x02000000 /* 32 MB Banks */
#define PHYS_FLASH_SECT_SIZE	0x00040000 /* 256 KB sectors (x2) */

#define CONFIG_SYS_DRAM_BASE		0xa0000000
#define CONFIG_SYS_DRAM_SIZE		0x04000000

#define CONFIG_SYS_FLASH_BASE		PHYS_FLASH_1

#define CONFIG_SYS_MAX_FLASH_BANKS	1    /* max number of memory banks		*/
#define CONFIG_SYS_MAX_FLASH_SECT	128  /* max number of sectors on one chip    */

/* timeout values are in ticks */
#define CONFIG_SYS_FLASH_ERASE_TOUT	(25*CONFIG_SYS_HZ) /* Timeout for Flash Erase */
#define CONFIG_SYS_FLASH_WRITE_TOUT	(25*CONFIG_SYS_HZ) /* Timeout for Flash Write */

/* FIXME */
#define CONFIG_ENV_IS_IN_FLASH	1
#define CONFIG_ENV_ADDR		(PHYS_FLASH_1 + 0x40000)/* Addr of Environment Sector	*/
#define CONFIG_ENV_SIZE		0x40000			/* Total Size of Environment Sector	*/

#define CONFIG_STACKSIZE	(128*1024)	/* regular stack */
#ifdef CONFIG_USE_IRQ
#define CONFIG_STACKSIZE_IRQ	(4*1024)	/* IRQ stack */
#define CONFIG_STACKSIZE_FIQ	(4*1024)	/* FIQ stack */
#endif

#define CONFIG_NET_MULTI
#define CONFIG_SMC91111		1
#define CONFIG_SMC91111_BASE		0x10000300  /* chip select 3         */
#define CONFIG_SMC_USE_32_BIT		1          /* 32 bit bus  */
#undef  CONFIG_SMC_91111_EXT_PHY		   /* we use internal phy   */
#undef  CONFIG_SHOW_ACTIVITY
#define CONFIG_NET_RETRY_COUNT		10	   /* # of retries          */


#define CONFIG_SYS_GPSR0_VAL		0x8320E420
#define CONFIG_SYS_GPSR1_VAL		0x00FFAA82
#define CONFIG_SYS_GPSR2_VAL		0x000DC000

#define CONFIG_SYS_GPCR0_VAL		0x40C31848
#define CONFIG_SYS_GPCR1_VAL		0x00000000
#define CONFIG_SYS_GPCR2_VAL		0x00020000

#define CONFIG_SYS_GPDR0_VAL		0xD3E3FC68
#define CONFIG_SYS_GPDR1_VAL		0xFCFFAB83
#define CONFIG_SYS_GPDR2_VAL		0x000FFFFF

#define CONFIG_SYS_GAFR0_L_VAL		0x80000004
#define CONFIG_SYS_GAFR0_U_VAL		0x595A801A
#define CONFIG_SYS_GAFR1_L_VAL		0x699A9559
#define CONFIG_SYS_GAFR1_U_VAL		0xAAA5AAAA
#define CONFIG_SYS_GAFR2_L_VAL		0xAAAAAAAA
#define CONFIG_SYS_GAFR2_U_VAL		0x00000256

#define CONFIG_SYS_PSSR_VAL		0x00000030

#define CONFIG_SYS_CKEN_VAL            0x00000080  /*  */
#define CONFIG_SYS_ICMR_VAL            0x00000000  /* No interrupts enabled        */


#define CONFIG_SYS_MSC0_VAL		0x000023D2

#define CONFIG_SYS_MSC1_VAL		0x1224A26C

#define CONFIG_SYS_MSC2_VAL		0x00001224

/* use the configuration above but disable partition 0 */
#define CONFIG_SYS_MDCNFG_VAL		0x00000AC9

#define CONFIG_SYS_MDREFR_VAL		0x00138018 /* mh: was 0x00118018 */

#define CONFIG_SYS_MDMRS_VAL		0x00320032

#define CONFIG_SYS_MECR_VAL		0x00000000
#define CONFIG_SYS_MCMEM0_VAL		0x00010504
#define CONFIG_SYS_MCMEM1_VAL		0x00010504
#define CONFIG_SYS_MCATT0_VAL		0x00010504
#define CONFIG_SYS_MCATT1_VAL		0x00010504
#define CONFIG_SYS_MCIO0_VAL		0x00004715
#define CONFIG_SYS_MCIO1_VAL		0x00004715


#endif	/* __CONFIG_H */
