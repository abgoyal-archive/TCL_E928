

#ifndef __LPD7A400_H_
#define __LPD7A400_H_

#define CONFIG_LPD7A400		/* Logic LH7A400 SDK */

#undef CONFIG_USE_IRQ

#include <configs/lpd7a400-10.h>

#define CONFIG_CMDLINE_TAG		1	/* enable passing of ATAGs	*/
#define CONFIG_SETUP_MEMORY_TAGS	1
#define CONFIG_INITRD_TAG		1

#define CONFIG_SYS_MALLOC_LEN		(CONFIG_ENV_SIZE + 128*1024)
#define CONFIG_SYS_GBL_DATA_SIZE	128	/* size in bytes reserved for initial data */

#define CONFIG_LH7A40X_SERIAL
#define CONFIG_CONSOLE_UART2	/* UART2 LH7A40x for console */

/* allow to overwrite serial and ethaddr */
#define CONFIG_ENV_OVERWRITE

#define CONFIG_BAUDRATE		115200
#define CONFIG_IPADDR		192.168.1.100
#define CONFIG_NETMASK		255.255.1.0
#define CONFIG_SERVERIP		192.168.1.1

#define	CONFIG_TIMESTAMP	1	/* Print timestamp info for images */


#define CONFIG_BOOTP_BOOTFILESIZE
#define CONFIG_BOOTP_BOOTPATH
#define CONFIG_BOOTP_GATEWAY
#define CONFIG_BOOTP_HOSTNAME


#include <config_cmd_default.h>

#ifndef USE_920T_MMU
    #define CONFIG_CMD_PING
    #undef CONFIG_CMD_CACHE
#else
    #define CONFIG_CMD_DATE
#endif


#define CONFIG_BOOTDELAY	3

#if defined(CONFIG_CMD_KGDB)
#define CONFIG_KGDB_BAUDRATE	115200		/* speed to run kgdb serial port */
/* what's this ? it's not used anywhere */
#define CONFIG_KGDB_SER_INDEX	1		/* which serial port to use */
#endif

#define	CONFIG_SYS_LONGHELP				/* undef to save memory		*/
#define	CONFIG_SYS_PROMPT		"LPD7A400> "	/* Monitor Command Prompt	*/
#define	CONFIG_SYS_CBSIZE		256		/* Console I/O Buffer Size	*/
#define	CONFIG_SYS_PBSIZE (CONFIG_SYS_CBSIZE+sizeof(CONFIG_SYS_PROMPT)+16) /* Print Buffer Size */
#define	CONFIG_SYS_MAXARGS		16		/* max number of command args	*/
#define CONFIG_SYS_BARGSIZE		CONFIG_SYS_CBSIZE	/* Boot Argument Buffer Size	*/

#define CONFIG_SYS_MEMTEST_START	0xc0300000	/* memtest works on	*/
#define CONFIG_SYS_MEMTEST_END		0xc0500000	/* 2 MB in DRAM	*/

#define	CONFIG_SYS_LOAD_ADDR		0xc0f00000	/* default load address	*/

/* valid baudrates */
#define CONFIG_SYS_BAUDRATE_TABLE	{ 9600, 19200, 38400, 57600, 115200 }

/* size and location of u-boot in flash */
#define CONFIG_SYS_MONITOR_BASE	CONFIG_SYS_FLASH_BASE
#define CONFIG_SYS_MONITOR_LEN		(256<<10)

#define	CONFIG_ENV_IS_IN_FLASH	1

/* Address and size of Primary Environment Sector	*/
#define CONFIG_ENV_ADDR		(CONFIG_SYS_FLASH_BASE + 0xFC0000)
#define CONFIG_ENV_SIZE		0x40000

#endif  /* __LPD7A400_H_ */
