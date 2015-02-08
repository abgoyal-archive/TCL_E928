
#ifndef __CONFIG_H
#define __CONFIG_H

#define CONFIG_ARM925T	1		/* This is an arm925t CPU	*/
#define CONFIG_OMAP	1		/* in a TI OMAP core	*/
#define CONFIG_OMAP1510 1		/* which is in a 1510 (helen) */
#define CONFIG_OMAP_SX1 1		/*	a SX1 Board  */

/* input clock of PLL */
#define CONFIG_SYS_CLK_FREQ	12000000	/* the SX1 has 12MHz input clock */

#undef CONFIG_USE_IRQ			/* we don't need IRQ/FIQ stuff */

#define CONFIG_MISC_INIT_R

#define CONFIG_CMDLINE_TAG	 1	/* enable passing of ATAGs	*/
#define CONFIG_SETUP_MEMORY_TAGS 1
#define CONFIG_INITRD_TAG	 1

#define CONFIG_SYS_MALLOC_LEN		(CONFIG_ENV_SIZE + 128*1024)
#define CONFIG_SYS_GBL_DATA_SIZE	128	/* size in bytes reserved for initial data */


#define CONFIG_SYS_NS16550
#define CONFIG_SYS_NS16550_SERIAL
#define CONFIG_SYS_NS16550_REG_SIZE	(-4)
#define CONFIG_SYS_NS16550_CLK		(CONFIG_SYS_CLK_FREQ)	/* can be 12M/32Khz or 48Mhz  */
#define CONFIG_SYS_NS16550_COM1	0xfffb0000		/* uart1, bluetooth uart on helen */

#define CONFIG_SERIAL1		1	/* we use SERIAL 1 on SX1 */

#define CONFIG_USB_DEVICE	1
#define CONFIG_USB_TTY		1

#define CONFIG_USBD_VENDORID		0x1234
#define CONFIG_USBD_PRODUCTID		0x5678
#define CONFIG_USBD_MANUFACTURER	"Siemens"
#define CONFIG_USBD_PRODUCT_NAME	"SX1"

#define CONFIG_HARD_I2C
#define CONFIG_SYS_I2C_SPEED		100000
#define CONFIG_SYS_I2C_SLAVE		1
#define CONFIG_DRIVER_OMAP1510_I2C

#define CONFIG_ENV_OVERWRITE

#define CONFIG_ENV_OVERWRITE
#define CONFIG_CONS_INDEX	1
#define CONFIG_BAUDRATE		115200
#define CONFIG_SYS_BAUDRATE_TABLE	{ 9600, 19200, 38400, 57600, 115200 }


#define CONFIG_BOOTP_BOOTFILESIZE
#define CONFIG_BOOTP_BOOTPATH
#define CONFIG_BOOTP_GATEWAY
#define CONFIG_BOOTP_HOSTNAME


#include <config_cmd_default.h>

#define CONFIG_CMD_I2C

#undef CONFIG_CMD_NET


#include <configs/omap1510.h>

#define CONFIG_BOOTARGS		"mem=16M console=ttyS0,115200n8 root=/dev/mtdblock3 rw"
#ifdef CONFIG_STDOUT_USBTTY
#define CONFIG_PREBOOT		"setenv stdout usbtty;setenv stdin usbtty"
#endif

#define CONFIG_SYS_LONGHELP				/* undef to save memory		*/
#define CONFIG_SYS_PROMPT		"SX1# " /* Monitor Command Prompt	*/
#define CONFIG_SYS_CBSIZE		256		/* Console I/O Buffer Size	*/
#define CONFIG_SYS_PBSIZE (CONFIG_SYS_CBSIZE+sizeof(CONFIG_SYS_PROMPT)+16) /* Print Buffer Size */
#define CONFIG_SYS_MAXARGS		16		/* max number of command args	*/
#define CONFIG_SYS_BARGSIZE		CONFIG_SYS_CBSIZE	/* Boot Argument Buffer Size	*/

#define CONFIG_SYS_MEMTEST_START	0x10000000	/* memtest works on	*/
#define CONFIG_SYS_MEMTEST_END		0x12000000	/* 32 MB in DRAM	*/

#define CONFIG_SYS_LOAD_ADDR		0x10000000	/* default load address */

#define CONFIG_SYS_TIMERBASE	OMAP1510_TIMER1_BASE	/* use timer 1 */
#define CONFIG_SYS_PTV		2	/* Divisor: 2^(PTV+1) => 8 */
#define CONFIG_SYS_HZ		1000

#define CONFIG_STACKSIZE	(128*1024)	/* regular stack */
#ifdef CONFIG_USE_IRQ
#define CONFIG_STACKSIZE_IRQ	(4*1024)	/* IRQ stack */
#define CONFIG_STACKSIZE_FIQ	(4*1024)	/* FIQ stack */
#endif

#define CONFIG_NR_DRAM_BANKS	1	   /* we have 1 bank of DRAM */
#define PHYS_SDRAM_1		0x10000000 /* SDRAM Bank #1 */
#define PHYS_SDRAM_1_SIZE	0x02000000 /* 32 MB */

#define PHYS_FLASH_1		0x00000000 /* Flash Bank #1 */
#define PHYS_FLASH_2		0x04000000 /* Flash Bank #2 */

#define CONFIG_SYS_FLASH_BASE		PHYS_FLASH_1

#define CONFIG_SYS_MAX_FLASH_BANKS	2	/* max number of memory banks */
#define PHYS_FLASH_SECT_SIZE	(128*1024) /* Size of a sector (128kB) */
#define CONFIG_SYS_MAX_FLASH_SECT	(256)	/* max number of sectors on one chip */
#define CONFIG_ENV_ADDR	(CONFIG_SYS_FLASH_BASE + PHYS_FLASH_SECT_SIZE) /* addr of environment */
#define CONFIG_SYS_MONITOR_BASE	CONFIG_SYS_FLASH_BASE	/* Monitor at beginning of flash */
#define CONFIG_SYS_MONITOR_LEN		PHYS_FLASH_SECT_SIZE	/* Reserve 1 sector */
#define CONFIG_SYS_FLASH_BANKS_LIST	{ CONFIG_SYS_FLASH_BASE, PHYS_FLASH_2 }

#define CONFIG_SYS_FLASH_CFI		1	/* Flash memory is CFI compliant */
#define CONFIG_FLASH_CFI_DRIVER	1	/* Use drivers/mtd/cfi_flash.c */
#define CONFIG_SYS_FLASH_USE_BUFFER_WRITE 1	/* Use buffered writes (~10x faster) */
#define CONFIG_SYS_FLASH_PROTECTION	1	/* Use hardware sector protection */

/* timeout values are in ticks */
#define CONFIG_SYS_FLASH_ERASE_TOUT	(20*CONFIG_SYS_HZ) /* Timeout for Flash Erase */
#define CONFIG_SYS_FLASH_WRITE_TOUT	(20*CONFIG_SYS_HZ) /* Timeout for Flash Write */

#define CONFIG_ENV_IS_IN_FLASH	1
#define CONFIG_ENV_SECT_SIZE	PHYS_FLASH_SECT_SIZE
#define CONFIG_ENV_SIZE		CONFIG_ENV_SECT_SIZE /* Total Size of Environment Sector */
#define CONFIG_ENV_OFFSET	( CONFIG_SYS_MONITOR_BASE + CONFIG_SYS_MONITOR_LEN ) /* Environment after Monitor */

/* Address and size of Redundant Environment Sector	*/
#define CONFIG_ENV_SIZE_REDUND	0x20000
#define CONFIG_ENV_OFFSET_REDUND	0x40000

#endif	/* __CONFIG_H */
