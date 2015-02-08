

#ifndef __CONFIG_H
#define __CONFIG_H

#define CONFIG_SYS_MEMTEST_START	0x100000
#define CONFIG_SYS_MEMTEST_END		0x10000000
#define CONFIG_SYS_HZ			1000
#define CONFIG_SYS_HZ_CLOCK		1000000	/* Timer 1 is clocked at 1Mhz */
#define CONFIG_SYS_TIMERBASE		0x13000100

#define CONFIG_CMDLINE_TAG		1	/* enable passing of ATAGs  */
#define CONFIG_SETUP_MEMORY_TAGS	1
#define CONFIG_MISC_INIT_R		1	/* call misc_init_r during start up */
#define CONFIG_SYS_MALLOC_LEN		(CONFIG_ENV_SIZE + 128*1024)
#define CONFIG_SYS_GBL_DATA_SIZE	128	/* size in bytes reserved for initial data */

#define CONFIG_NET_MULTI
#define CONFIG_SMC91111
#define CONFIG_SMC_USE_32_BIT
#define CONFIG_SMC91111_BASE    0xC8000000
#undef CONFIG_SMC91111_EXT_PHY

#define CONFIG_PL011_SERIAL
#define CONFIG_PL011_CLOCK	14745600
#define CONFIG_PL01x_PORTS	{ (void *)CONFIG_SYS_SERIAL0, (void *)CONFIG_SYS_SERIAL1 }
#define CONFIG_CONS_INDEX	0
#define CONFIG_BAUDRATE		38400
#define CONFIG_SYS_BAUDRATE_TABLE	{ 9600, 19200, 38400, 57600, 115200 }
#define CONFIG_SYS_SERIAL0		0x16000000
#define CONFIG_SYS_SERIAL1		0x17000000


#define CONFIG_BOOTP_BOOTFILESIZE
#define CONFIG_BOOTP_BOOTPATH
#define CONFIG_BOOTP_GATEWAY
#define CONFIG_BOOTP_HOSTNAME


#define CONFIG_CMD_BDI
#define CONFIG_CMD_DHCP
#define CONFIG_CMD_SAVEENV
#define CONFIG_CMD_FLASH
#define CONFIG_CMD_IMI
#define CONFIG_CMD_MEMORY
#define CONFIG_CMD_NET
#define CONFIG_CMD_PING


#if 0
#define CONFIG_BOOTDELAY	2
#define CONFIG_BOOTARGS	"root=/dev/nfs nfsroot=<IP address>:/<exported rootfs>  mem=128M ip=dhcp netdev=27,0,0xfc800000,0xfc800010,eth0 video=clcdfb:0"
#define CONFIG_BOOTCOMMAND "bootp ; bootm"
#endif
#define CONFIG_BOOTDELAY	2
#define CONFIG_BOOTARGS	"root=/dev/mtdblock2 mem=128M ip=dhcp netdev=27,0,0xfc800000,0xfc800010,eth0 video=clcdfb:0 console=ttyAMA0"
#define CONFIG_BOOTCOMMAND "cp 0x24080000 0x7fc0 0x100000; bootm"

#define CONFIG_SYS_LONGHELP				/* undef to save memory */
#define CONFIG_SYS_PROMPT	"Integrator-CP # "	/* Monitor Command Prompt */
#define CONFIG_SYS_CBSIZE	256			/* Console I/O Buffer Size*/
/* Print Buffer Size */
#define CONFIG_SYS_PBSIZE	(CONFIG_SYS_CBSIZE+sizeof(CONFIG_SYS_PROMPT)+16)
#define CONFIG_SYS_MAXARGS	16			/* max number of command args */
#define CONFIG_SYS_BARGSIZE	CONFIG_SYS_CBSIZE		/* Boot Argument Buffer Size*/

#define CONFIG_SYS_LOAD_ADDR	0x7fc0	/* default load address */

#define CONFIG_STACKSIZE	(128*1024)	/* regular stack */
#ifdef CONFIG_USE_IRQ
#define CONFIG_STACKSIZE_IRQ	(4*1024)	/* IRQ stack */
#define CONFIG_STACKSIZE_FIQ	(4*1024)	/* FIQ stack */
#endif

#define CONFIG_NR_DRAM_BANKS	1		/* we have 1 bank of DRAM */
#define PHYS_SDRAM_1		0x00000000	/* SDRAM Bank #1 */
#define PHYS_SDRAM_1_SIZE	0x08000000	/* 128 MB */

#define CONFIG_SYS_FLASH_BASE		0x24000000
#define CONFIG_SYS_FLASH_CFI		1
#define CONFIG_FLASH_CFI_DRIVER		1
#define CONFIG_SYS_MAX_FLASH_SECT	64
#define CONFIG_SYS_MAX_FLASH_BANKS	1		/* max number of memory banks */
#define PHYS_FLASH_SIZE			0x01000000	/* 16MB */
#define CONFIG_SYS_FLASH_ERASE_TOUT	(2*CONFIG_SYS_HZ)	/* Timeout for Flash Erase */
#define CONFIG_SYS_FLASH_WRITE_TOUT	(2*CONFIG_SYS_HZ)	/* Timeout for Flash Write */

#define CONFIG_SYS_MONITOR_LEN		0x00100000
#define CONFIG_ENV_IS_IN_FLASH	1

#if ( PHYS_FLASH_SIZE == 0x04000000 )

#define CONFIG_ENV_ADDR		0x27F00000
#define CONFIG_SYS_MONITOR_BASE	0x27F40000

#elif (PHYS_FLASH_SIZE == 0x02000000 )

#define CONFIG_ENV_ADDR		0x25F00000
#define CONFIG_SYS_MONITOR_BASE	0x25F40000

#else

#define CONFIG_ENV_ADDR		0x24F00000
#define CONFIG_SYS_MONITOR_BASE	0x27F40000

#endif

#define CONFIG_ENV_SECT_SIZE	0x40000		/* 256KB */
#define CONFIG_ENV_SIZE		8192		/* 8KB */
#define CPCR_BASE		0xCB000000	/* CP Registers*/
#define OS_FLASHPROG		0x00000004	/* Flash register*/
#define CPMASK_EXTRABANK	0x8
#define CPMASK_FLASHSIZE	0x4
#define CPMASK_FLWREN		0x2
#define CPMASK_FLVPPEN		0x1



#include "armcoremodule.h"


#endif /* __CONFIG_H */
