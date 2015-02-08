

#ifndef __CONFIG_H
#define __CONFIG_H

/* allow to overwrite serial and ethaddr */
#define CONFIG_ENV_OVERWRITE


#define CONFIG_ARM926EJS	   1	     /* This is an arm926ejs CPU core  */
#define CONFIG_OMAP		   1	     /* in a TI OMAP core    */
#define CONFIG_OMAP730		   1	     /* which is in a 730  */
#define CONFIG_P2_OMAP730	   1	     /*	 a Perseus 2 Board  */


#define CONFIG_SYS_CLK_FREQ	   13000000

#undef CONFIG_USE_IRQ			     /* we don't need IRQ/FIQ stuff */

#define CONFIG_MISC_INIT_R

#define CONFIG_CMDLINE_TAG	   1	     /* enable passing of ATAGs	 */
#define CONFIG_SETUP_MEMORY_TAGS   1


#define CONFIG_SYS_MALLOC_LEN		   (CONFIG_ENV_SIZE + 128*1024)
#define CONFIG_SYS_GBL_DATA_SIZE	   128	     /* size in bytes reserved for initial data */


#define CONFIG_NET_MULTI
#define CONFIG_LAN91C96
#define CONFIG_LAN91C96_BASE	   0x04000300
#define CONFIG_LAN91C96_EXT_PHY


#define CONFIG_SYS_NS16550
#define CONFIG_SYS_NS16550_SERIAL
#define CONFIG_SYS_NS16550_REG_SIZE	   (1)
#define CONFIG_SYS_NS16550_CLK		   (48000000)	  /* can be 12M/32Khz or 48Mhz */
#define CONFIG_SYS_NS16550_COM1	   0xfffb0000	  /* uart1, bluetooth uart
						   * on perseus */


#define CONFIG_SERIAL1		   1	     /* we use SERIAL 1 on OMAP730 Perseus 2 */

#define CONFIG_CONS_INDEX	   1
#define CONFIG_BAUDRATE		   115200
#define CONFIG_SYS_BAUDRATE_TABLE	   { 9600, 19200, 38400, 57600, 115200 }


#include <config_cmd_default.h>

#define CONFIG_CMD_DHCP


#define CONFIG_BOOTP_SUBNETMASK
#define CONFIG_BOOTP_GATEWAY
#define CONFIG_BOOTP_HOSTNAME
#define CONFIG_BOOTP_BOOTPATH


#include <configs/omap730.h>
#include <configs/h2_p2_dbg_board.h>

#define CONFIG_BOOTDELAY	   3
#define CONFIG_BOOTARGS		   "mem=32M console=ttyS0,115200n8 noinitrd root=/dev/nfs rw ip=bootp"

#define CONFIG_LOADADDR		   0x10000000

#define CONFIG_ETHADDR
#define CONFIG_NETMASK		   255.255.255.0
#define CONFIG_IPADDR		   192.168.0.23
#define CONFIG_SERVERIP		   192.150.0.100
#define CONFIG_BOOTFILE		   "uImage"  /* File to load */

#if defined(CONFIG_CMD_KGDB)
#define CONFIG_KGDB_BAUDRATE	   115200    /* Speed to run kgdb serial port */
#define CONFIG_KGDB_SER_INDEX	   1	     /* Which serial port to use */
#endif


#define CONFIG_SYS_LONGHELP				       /* undef to save memory	   */
#define CONFIG_SYS_PROMPT		   "OMAP730 P2 # "     /* Monitor Command Prompt   */
#define CONFIG_SYS_CBSIZE		   256		       /* Console I/O Buffer Size  */
/* Print Buffer Size */
#define CONFIG_SYS_PBSIZE		   (CONFIG_SYS_CBSIZE+sizeof(CONFIG_SYS_PROMPT)+16)
#define CONFIG_SYS_MAXARGS		   16		       /* max number of command args   */
#define CONFIG_SYS_BARGSIZE		   CONFIG_SYS_CBSIZE	       /* Boot Argument Buffer Size    */

#define CONFIG_SYS_MEMTEST_START	   0x10000000	       /* memtest works on */
#define CONFIG_SYS_MEMTEST_END		   0x12000000	       /* 32 MB in DRAM	   */

#define CONFIG_SYS_LOAD_ADDR		   0x10000000	       /* default load address */

#define CONFIG_SYS_TIMERBASE		0xFFFEC500	/* use timer 1 */
#define CONFIG_SYS_PTV			7	/* 2^(PTV+1), divide by 256 */
#define CONFIG_SYS_HZ			((CONFIG_SYS_CLK_FREQ)/(2 << CONFIG_SYS_PTV))


#define CONFIG_STACKSIZE	   (128*1024)	  /* regular stack */
#ifdef CONFIG_USE_IRQ
#define CONFIG_STACKSIZE_IRQ	   (4*1024)	  /* IRQ stack */
#define CONFIG_STACKSIZE_FIQ	   (4*1024)	  /* FIQ stack */
#endif


#define CONFIG_NR_DRAM_BANKS	   1		  /* we have 1 bank of DRAM */
#define PHYS_SDRAM_1		   0x10000000	  /* SDRAM Bank #1 */
#define PHYS_SDRAM_1_SIZE	   0x02000000	  /* 32 MB */

#if defined(CONFIG_CS0_BOOT)
#define PHYS_FLASH_1		   0x0C000000
#elif defined(CONFIG_CS3_BOOT)
#define PHYS_FLASH_1		   0x00000000
#else
#error Unknown Boot Chip-Select number
#endif

#define CONFIG_SYS_FLASH_BASE		   PHYS_FLASH_1


#define CONFIG_SYS_MAX_FLASH_BANKS	   1		  /* max number of memory banks */
#define PHYS_FLASH_SIZE		   0x02000000	  /* 32MB */
#define CONFIG_SYS_MAX_FLASH_SECT	   (259)	  /* max number of sectors on one chip */
/* addr of environment */
#define CONFIG_ENV_ADDR		   (CONFIG_SYS_FLASH_BASE + 0x020000)

/* timeout values are in ticks */
#define CONFIG_SYS_FLASH_ERASE_TOUT	    (20*CONFIG_SYS_HZ)	  /* Timeout for Flash Erase */
#define CONFIG_SYS_FLASH_WRITE_TOUT	    (20*CONFIG_SYS_HZ)	  /* Timeout for Flash Write */

#define CONFIG_ENV_IS_IN_FLASH	   1
#define CONFIG_ENV_SIZE		   0x20000	  /* Total Size of Environment Sector */
#define CONFIG_ENV_OFFSET		   0x20000	  /* environment starts here  */

#endif	  /* ! __CONFIG_H */
