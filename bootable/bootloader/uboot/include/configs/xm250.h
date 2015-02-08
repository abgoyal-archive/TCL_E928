

#ifndef __CONFIG_H
#define __CONFIG_H

#define CONFIG_PXA250	       1	/* This is an PXA250 CPU	*/
#define CONFIG_XM250	       1	/* on a MicroSys XM250 Board	*/
#undef CONFIG_USE_IRQ			/* we don't need IRQ/FIQ stuff	*/

/* we will never enable dcache, because we have to setup MMU first */
#define CONFIG_SYS_NO_DCACHE

#define CONFIG_SYS_MALLOC_LEN		(256*1024)
#define CONFIG_SYS_GBL_DATA_SIZE	128	/* size in bytes reserved for initial data */

#define CONFIG_NET_MULTI
#define CONFIG_SMC91111
#define CONFIG_SMC91111_BASE		0x04000300
#undef	CONFIG_SMC91111_EXT_PHY
#define CONFIG_SMC_USE_32_BIT
#undef	CONFIG_SHOW_ACTIVITY
#define CONFIG_NET_RETRY_COUNT		10	   /* # of retries		*/

#define CONFIG_HARD_I2C			1
#define CONFIG_SYS_I2C_SPEED			50000
#define CONFIG_SYS_I2C_SLAVE			0xfe

#define CONFIG_RTC_PCF8563		1
#define CONFIG_SYS_I2C_RTC_ADDR		0x51

#define CONFIG_SYS_I2C_EEPROM_ADDR		0x58	/* A0 = 0 (hardwired)		*/
#define CONFIG_SYS_EEPROM_PAGE_WRITE_BITS	4	/* 4 bits = 16 octets		*/
#define CONFIG_SYS_EEPROM_PAGE_WRITE_DELAY_MS	10	/* between stop and start	*/
#define CONFIG_SYS_I2C_EEPROM_ADDR_LEN		1	/* length of address		*/
#define CONFIG_SYS_EEPROM_SIZE			2048	/* size in bytes		*/
#undef	CONFIG_SYS_I2C_INIT_BOARD			/* board has no own init	*/

#define CONFIG_PXA_SERIAL
#define CONFIG_FFUART	       1       /* we use FFUART */

/* allow to overwrite serial and ethaddr */
#define CONFIG_ENV_OVERWRITE

#define CONFIG_BAUDRATE		115200


#define CONFIG_BOOTP_BOOTFILESIZE
#define CONFIG_BOOTP_BOOTPATH
#define CONFIG_BOOTP_GATEWAY
#define CONFIG_BOOTP_HOSTNAME


#include <config_cmd_default.h>

#define CONFIG_CMD_ELF
#define CONFIG_CMD_EEPROM
#define CONFIG_CMD_DATE
#define CONFIG_CMD_I2C


#define CONFIG_BOOTDELAY	3

#define CONFIG_SYS_LONGHELP				/* undef to save memory		*/
#define CONFIG_SYS_PROMPT		"=> "		/* Monitor Command Prompt	*/
#define CONFIG_SYS_CBSIZE		256		/* Console I/O Buffer Size	*/
#define CONFIG_SYS_PBSIZE (CONFIG_SYS_CBSIZE+sizeof(CONFIG_SYS_PROMPT)+16) /* Print Buffer Size */
#define CONFIG_SYS_MAXARGS		16		/* max number of command args	*/
#define CONFIG_SYS_BARGSIZE		CONFIG_SYS_CBSIZE	/* Boot Argument Buffer Size	*/

#define CONFIG_SYS_MEMTEST_START	0xa0400000	/* memtest works on		*/
#define CONFIG_SYS_MEMTEST_END		0xa0800000	/* 4 ... 8 MB in DRAM		*/

#define CONFIG_SYS_LOAD_ADDR		0xa3000000	/* default load address */

#define CONFIG_SYS_HZ			1000
#define CONFIG_SYS_CPUSPEED		0x161		/* set core clock to 400/400/100 MHz */

						/* valid baudrates */

#define CONFIG_SYS_BAUDRATE_TABLE	{ 9600, 19200, 38400, 57600, 115200 }

#define CONFIG_CMDLINE_TAG	 1	 /* send commandline to Kernel		*/
#define CONFIG_SETUP_MEMORY_TAGS 1	 /* send memory definition to kernel	*/
#define	CONFIG_INITRD_TAG	 1	 /* do not send initrd params		*/
#undef	CONFIG_VFD			 /* do not send framebuffer setup	*/

#define CONFIG_STACKSIZE	(128*1024)	/* regular stack */
#ifdef CONFIG_USE_IRQ
#define CONFIG_STACKSIZE_IRQ	(4*1024)	/* IRQ stack */
#define CONFIG_STACKSIZE_FIQ	(4*1024)	/* FIQ stack */
#endif

#define CONFIG_NR_DRAM_BANKS	4
#define PHYS_SDRAM_1		0xa0000000 /* SDRAM Bank #1	*/
#define PHYS_SDRAM_1_SIZE	0x04000000 /* 64 MB		*/
#define PHYS_SDRAM_2		0xa4000000 /* SDRAM Bank #2	*/
#define PHYS_SDRAM_2_SIZE	0x00000000 /* 0 MB		*/
#define PHYS_SDRAM_3		0xa8000000 /* SDRAM Bank #3	*/
#define PHYS_SDRAM_3_SIZE	0x00000000 /* 0 MB		*/
#define PHYS_SDRAM_4		0xac000000 /* SDRAM Bank #4	*/
#define PHYS_SDRAM_4_SIZE	0x00000000 /* 0 MB		*/

#define PHYS_FLASH_1		0x00000000 /* Flash Bank #1	*/
#define PHYS_FLASH_2		0x04000000 /* Flash Bank #1	*/
#define PHYS_FLASH_SIZE		0x01000000 /* 16 MB		*/
#define PHYS_FLASH_BANK_SIZE	0x01000000 /* 16 MB Banks	*/
#define PHYS_FLASH_SECT_SIZE	0x00040000 /* 256 KB sectors (x2) */

#define CONFIG_SYS_DRAM_BASE		0xa0000000
#define CONFIG_SYS_DRAM_SIZE		0x04000000

#define CONFIG_SYS_FLASH_BASE		PHYS_FLASH_1

#define CONFIG_SYS_MAX_FLASH_BANKS	1     /* max number of memory banks		*/
#define CONFIG_SYS_MAX_FLASH_SECT	128   /* max number of sectors on one chip	*/

/* timeout values are in ticks */
#define CONFIG_SYS_FLASH_ERASE_TOUT	(2*CONFIG_SYS_HZ)	/* Timeout for Flash Erase	*/
#define CONFIG_SYS_FLASH_WRITE_TOUT	(2*CONFIG_SYS_HZ)	/* Timeout for Flash Write	*/
#define CONFIG_SYS_FLASH_LOCK_TOUT	(2*CONFIG_SYS_HZ)	/* Timeout for Flash Set Lock Bit */
#define CONFIG_SYS_FLASH_UNLOCK_TOUT	(2*CONFIG_SYS_HZ)	/* Timeout for Flash Clear Lock Bits */
#define CONFIG_SYS_FLASH_PROTECTION			/* "Real" (hardware) sectors protection */

#define CONFIG_ENV_IS_IN_FLASH	1
#define CONFIG_ENV_ADDR		(PHYS_FLASH_1 + 0x40000)	/* Addr of Environment Sector	*/
#define CONFIG_ENV_SIZE		0x4000
#define CONFIG_ENV_SECT_SIZE	0x40000				/* Size of the Environment Sector	*/
#define CONFIG_SYS_MONITOR_LEN		0x20000				/* 128 KiB */


/* Pin direction control */
#define CONFIG_SYS_GPDR0_VAL	    0xd3808000
#define CONFIG_SYS_GPDR1_VAL	    0xfcffab83
#define CONFIG_SYS_GPDR2_VAL	    0x0001ffff
/* Set and Clear registers */
#define CONFIG_SYS_GPSR0_VAL	    0x00008000
#define CONFIG_SYS_GPSR1_VAL	    0x00ff0002
#define CONFIG_SYS_GPSR2_VAL	    0x0001c000
#define CONFIG_SYS_GPCR0_VAL	    0x00000000
#define CONFIG_SYS_GPCR1_VAL	    0x00000000
#define CONFIG_SYS_GPCR2_VAL	    0x00000000
/* Edge detect registers (these are set by the kernel) */
#define CONFIG_SYS_GRER0_VAL	    0x00002180
#define CONFIG_SYS_GRER1_VAL	    0x00000000
#define CONFIG_SYS_GRER2_VAL	    0x00000000
#define CONFIG_SYS_GFER0_VAL	    0x000043e0
#define CONFIG_SYS_GFER1_VAL	    0x00000000
#define CONFIG_SYS_GFER2_VAL	    0x00000000
/* Alternate function registers */
#define CONFIG_SYS_GAFR0_L_VAL	    0x80000004
#define CONFIG_SYS_GAFR0_U_VAL	    0x595a8010
#define CONFIG_SYS_GAFR1_L_VAL	    0x699a9559
#define CONFIG_SYS_GAFR1_U_VAL	    0xaaa5aaaa
#define CONFIG_SYS_GAFR2_L_VAL	    0xaaaaaaaa
#define CONFIG_SYS_GAFR2_U_VAL	    0x00000002

#define CONFIG_SYS_PSSR_VAL	    0x00000030
#define CONFIG_SYS_CCCR_VAL	    0x00000161	/* 100 MHz memory, 400 MHz CPU, 400 Turbo  */
#define CONFIG_SYS_CKEN_VAL	    0x000141ec	/* FFUART and STUART enabled	*/
#define CONFIG_SYS_ICMR_VAL	    0x00000000	/* No interrupts enabled	*/


#define CONFIG_SYS_MSC0_VAL	    0x122423f0	/* FLASH   / LAN	    (cs0)/(cS1)	  */
#define CONFIG_SYS_MSC1_VAL	    0x35f4aa4c	/* USB	   / ST3+ST5	    (cs2)/(cS3)	  */
#define CONFIG_SYS_MSC2_VAL	    0x35f435fc	/* IDE	   / BCR + WatchDog (cs4)/(cS5)	  */
#define CONFIG_SYS_MDCNFG_VAL	    0x000009c9
#define CONFIG_SYS_MDMRS_VAL	    0x00220022
#define CONFIG_SYS_MDREFR_VAL	    0x000da018	/* Initial setting, individual bits set in lowlevel_init.S */

#define CONFIG_SYS_MECR_VAL	      0x00000000
#define CONFIG_SYS_MCMEM0_VAL	      0x00010504
#define CONFIG_SYS_MCMEM1_VAL	      0x00010504
#define CONFIG_SYS_MCATT0_VAL	      0x00010504
#define CONFIG_SYS_MCATT1_VAL	      0x00010504
#define CONFIG_SYS_MCIO0_VAL	      0x00004715
#define CONFIG_SYS_MCIO1_VAL	      0x00004715

/* Board specific defines */

#ifndef __ASSEMBLY__

/* global prototypes */
void led_code(int code, int color);

#endif

#endif	/* __CONFIG_H */
