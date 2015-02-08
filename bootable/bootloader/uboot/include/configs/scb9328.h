

#ifndef __CONFIG_H
#define __CONFIG_H

#define CONFIG_ARM920T		1     /* this is an ARM920T CPU	    */
#define CONFIG_IMX		1     /* in a Motorola MC9328MXL Chip */
#define CONFIG_SCB9328		1     /* on a scb9328tronix board */
#undef	CONFIG_USE_IRQ		      /* don't need use IRQ/FIQ	   */

#define CONFIG_IMX_SERIAL
#define CONFIG_IMX_SERIAL1


#define CONFIG_BOOTP_BOOTFILESIZE
#define CONFIG_BOOTP_BOOTPATH
#define CONFIG_BOOTP_GATEWAY
#define CONFIG_BOOTP_HOSTNAME


#include <config_cmd_default.h>

#define CONFIG_CMD_NET
#define CONFIG_CMD_PING
#define CONFIG_CMD_DHCP

#undef CONFIG_CMD_CONSOLE
#undef CONFIG_CMD_LOADS
#undef CONFIG_CMD_SOURCE


#define CONFIG_BOOTDELAY   -1
#define CONFIG_BOOTARGS	   "console=ttySMX0,115200n8 root=/dev/mtdblock3 rootfstype=jffs2 mtdparts=scb9328_flash:128k(U-boot)ro,128k(U-boot_env),1m(kernel),4m(root),4m(fs) eval_board=evk9328"
#define CONFIG_BOOTCOMMAND "bootm 10040000"
#define CONFIG_SHOW_BOOT_PROGRESS
#define CONFIG_ETHADDR		80:81:82:83:84:85
#define CONFIG_NETMASK		255.255.255.0
#define CONFIG_IPADDR		10.10.10.9
#define CONFIG_SERVERIP		10.10.10.10

#define CONFIG_SYS_LONGHELP				      /* undef saves memory  */
#define CONFIG_SYS_PROMPT		"scb9328> "	      /* prompt string	     */
#define CONFIG_SYS_CBSIZE		256		      /* console I/O buffer  */
#define CONFIG_SYS_PBSIZE (CONFIG_SYS_CBSIZE+sizeof(CONFIG_SYS_PROMPT)+16) /* print buffer size   */
#define CONFIG_SYS_MAXARGS		16		      /* max command args    */
#define CONFIG_SYS_BARGSIZE		CONFIG_SYS_CBSIZE	      /* boot args buf size  */

#define CONFIG_SYS_MEMTEST_START	0x08100000	      /* memtest test area   */
#define CONFIG_SYS_MEMTEST_END		0x08F00000

#define CONFIG_SYS_HZ			3686400	     /* incrementer freq: 3.6864 MHz */
#define CONFIG_SYS_CPUSPEED		0x141	     /* core clock - register value  */

#define CONFIG_SYS_BAUDRATE_TABLE	{ 9600, 19200, 38400, 57600, 115200 }
#define CONFIG_BAUDRATE 115200
#define CONFIG_CMDLINE_TAG	     1	 /* send commandline to Kernel	     */
#define CONFIG_SETUP_MEMORY_TAGS     1	 /* send memory definition to kernel */
#define CONFIG_INITRD_TAG	     1	 /* send initrd params		     */
#undef	CONFIG_VFD			 /* do not send framebuffer setup    */


#define CONFIG_SYS_MALLOC_LEN		(CONFIG_ENV_SIZE + (128<<10) )


#define CONFIG_SYS_GBL_DATA_SIZE	128	/* size in bytes reserved for initial data */

#define CONFIG_STACKSIZE	(120<<10)      /* stack size		     */

#ifdef CONFIG_USE_IRQ
#define CONFIG_STACKSIZE_IRQ	(4<<10)	       /* IRQ stack		     */
#define CONFIG_STACKSIZE_FIQ	(4<<10)	       /* FIQ stack		     */
#endif


#define PRECHARGE_CMD 0x910a8200
#define AUTOREFRESH_CMD 0xa10a8200

/* SH FIXME */
#define CONFIG_NR_DRAM_BANKS	1		/* we have 1 bank of SDRAM */
#define SCB9328_SDRAM_1		0x08000000	/* SDRAM bank #1	   */
#define SCB9328_SDRAM_1_SIZE	0x01000000	/* 16 MB		   */





/* #define SCB9328_FLASH_32M */

/* 32MB */
#ifdef SCB9328_FLASH_32M
#define CONFIG_SYS_MAX_FLASH_BANKS		1	/* FLASH banks count (not chip count)*/
#define CONFIG_SYS_MAX_FLASH_SECT		256	/* number of sector in FLASH bank    */
#define SCB9328_FLASH_BUS_WIDTH		2	/* we use 16 bit FLASH memory...     */
#define SCB9328_FLASH_INTERLEAVE	1	/* ... made of 1 chip		     */
#define SCB9328_FLASH_BANK_SIZE	 0x02000000	/* size of one flash bank	     */
#define SCB9328_FLASH_SECT_SIZE	 0x00020000	/* size of erase sector		     */
#define SCB9328_FLASH_BASE	 0x10000000	/* location of flash memory	     */
#define SCB9328_FLASH_UNLOCK		1	/* perform hw unlock first	     */
#else

/* 16MB */
#define CONFIG_SYS_MAX_FLASH_BANKS		1	/* FLASH banks count (not chip count)*/
#define CONFIG_SYS_MAX_FLASH_SECT		128	/* number of sector in FLASH bank    */
#define SCB9328_FLASH_BUS_WIDTH		2	/* we use 16 bit FLASH memory...     */
#define SCB9328_FLASH_INTERLEAVE	1	/* ... made of 1 chip		     */
#define SCB9328_FLASH_BANK_SIZE	 0x01000000	/* size of one flash bank	     */
#define SCB9328_FLASH_SECT_SIZE	 0x00020000	/* size of erase sector		     */
#define SCB9328_FLASH_BASE	 0x10000000	/* location of flash memory	     */
#define SCB9328_FLASH_UNLOCK		1	/* perform hw unlock first	     */
#endif /* SCB9328_FLASH_32M */

#undef	CONFIG_SYS_FLASH_CFI

#define CONFIG_SYS_FLASH_ERASE_TOUT	(2*CONFIG_SYS_HZ)    /* timeout for Erase operation */
#define CONFIG_SYS_FLASH_WRITE_TOUT	(2*CONFIG_SYS_HZ)    /* timeout for Write operation */

#define CONFIG_SYS_FLASH_BASE		SCB9328_FLASH_BASE

#define CONFIG_SYS_JFFS2_FIRST_BANK		0
#define CONFIG_SYS_JFFS2_FIRST_SECTOR		5
#define CONFIG_SYS_JFFS2_NUM_BANKS		1



#define CONFIG_SYS_GPR_A_VAL		0x00800000
#define CONFIG_SYS_GIUS_A_VAL		0x0043fffe

#define CONFIG_SYS_MONITOR_BASE	0x10000000
#define CONFIG_SYS_MONITOR_LEN		0x20000		/* 128b ( 1 flash sector )  */
#define CONFIG_ENV_IS_IN_FLASH	1
#define CONFIG_ENV_ADDR		0x10020000	/* absolute address for now  */
#define CONFIG_ENV_SIZE		0x20000

#define	 CONFIG_ENV_OVERWRITE  1		/* env is not writable now   */


#define CONFIG_SYS_CS0U_VAL 0x000F2000
#define CONFIG_SYS_CS0L_VAL 0x11110d01
#define CONFIG_SYS_CS1U_VAL 0x000F0a00
#define CONFIG_SYS_CS1L_VAL 0x11110601
#define CONFIG_SYS_CS2U_VAL 0x0
#define CONFIG_SYS_CS2L_VAL 0x0

#define CONFIG_SYS_CS3U_VAL 0x000FFFFF
#define CONFIG_SYS_CS3L_VAL 0x00000303

#define CONFIG_SYS_CS4U_VAL 0x000F0a00
#define CONFIG_SYS_CS4L_VAL 0x11110301



#define CONFIG_SYS_CS5U_VAL 0x00008400
#define CONFIG_SYS_CS5L_VAL 0x00000D03

#define CONFIG_NET_MULTI		1
#define CONFIG_DRIVER_DM9000		1
#define CONFIG_DM9000_BASE		0x16000000
#define DM9000_IO			CONFIG_DM9000_BASE
#define DM9000_DATA			(CONFIG_DM9000_BASE+4)


#define CPU200

#ifdef CPU200
#define CONFIG_SYS_MPCTL0_VAL 0x00321431
#else
#define CONFIG_SYS_MPCTL0_VAL 0x040e200e
#endif

/* #define BUS64 */
#define BUS72

#ifdef BUS72
#define CONFIG_SYS_SPCTL0_VAL 0x04002400
#endif

#ifdef BUS96
#define CONFIG_SYS_SPCTL0_VAL 0x04001800
#endif

#ifdef BUS64
#define CONFIG_SYS_SPCTL0_VAL 0x08001800
#endif


#ifdef BUS64
#define CONFIG_SYS_CSCR_VAL 0x2f030003
#endif

#ifdef BUS72
#define CONFIG_SYS_CSCR_VAL 0x2f030403
#endif

#define CONFIG_SYS_LOAD_ADDR 0x08400000

#define MHZ16QUARZINUSE

#ifdef MHZ16QUARZINUSE
#define CONFIG_SYSPLL_CLK_FREQ 16000000
#else
#define CONFIG_SYSPLL_CLK_FREQ 16780000
#endif

#define CONFIG_SYS_CLK_FREQ 16780000

/* FMCR Bit 0 becomes 0 to make CS3 CS3 :P */
#define CONFIG_SYS_FMCR_VAL 0x00000001


#ifdef BUS96
#define CONFIG_SYS_PCDR_VAL 0x000b00b5
#endif

#ifdef BUS64
#define CONFIG_SYS_PCDR_VAL 0x000b00b3
#endif

#ifdef BUS72
#define CONFIG_SYS_PCDR_VAL 0x000b00b8
#endif

#endif	/* __CONFIG_H */
