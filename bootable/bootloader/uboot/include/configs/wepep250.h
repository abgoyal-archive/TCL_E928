

#ifndef __CONFIG_H
#define __CONFIG_H

#define CONFIG_PXA250          1        /* this is an PXA250 CPU     */
#define CONFIG_WEPEP250        1        /* config for wepep250 board */
#undef  CONFIG_USE_IRQ                  /* don't need use IRQ/FIQ    */

/* we will never enable dcache, because we have to setup MMU first */
#define CONFIG_SYS_NO_DCACHE

#define CONFIG_PXA_SERIAL
#define CONFIG_BTUART          1       /* BTUART is default on WEP dev board */
#define CONFIG_BAUDRATE   115200


#define CONFIG_BOOTP_BOOTFILESIZE
#define CONFIG_BOOTP_BOOTPATH
#define CONFIG_BOOTP_GATEWAY
#define CONFIG_BOOTP_HOSTNAME


#include <config_cmd_default.h>

#undef CONFIG_CMD_CONSOLE
#undef CONFIG_CMD_LOADS
#undef CONFIG_CMD_NET
#undef CONFIG_CMD_SOURCE


#define CONFIG_BOOTDELAY   -1
#define CONFIG_BOOTARGS    "root=/dev/mtdblock2 mem=32m console=ttyS01,115200n8"
#define CONFIG_BOOTCOMMAND "bootm 40000"


#define CONFIG_SYS_LONGHELP                                  /* undef saves memory  */
#define CONFIG_SYS_PROMPT              "WEP> "               /* prompt string       */
#define CONFIG_SYS_CBSIZE              256                   /* console I/O buffer  */
#define CONFIG_SYS_PBSIZE (CONFIG_SYS_CBSIZE+sizeof(CONFIG_SYS_PROMPT)+16) /* print buffer size   */
#define CONFIG_SYS_MAXARGS             16                    /* max command args    */
#define CONFIG_SYS_BARGSIZE            CONFIG_SYS_CBSIZE            /* boot args buf size  */

#define CONFIG_SYS_MEMTEST_START       0xa0400000            /* memtest test area   */
#define CONFIG_SYS_MEMTEST_END         0xa0800000

#define CONFIG_SYS_HZ			1000
#define CONFIG_SYS_CPUSPEED            0x141        /* core clock - register value  */

#define CONFIG_SYS_BAUDRATE_TABLE      { 9600, 19200, 38400, 57600, 115200 }

#define CONFIG_CMDLINE_TAG           1   /* send commandline to Kernel       */
#define CONFIG_SETUP_MEMORY_TAGS     1   /* send memory definition to kernel */
#undef  CONFIG_INITRD_TAG                /* do not send initrd params        */
#undef  CONFIG_VFD                       /* do not send framebuffer setup    */


#define CONFIG_SYS_MALLOC_LEN	  (CONFIG_ENV_SIZE + (128<<10) )
#define CONFIG_SYS_GBL_DATA_SIZE	128	/* size in bytes reserved for initial data */

#define CONFIG_STACKSIZE        (120<<10)      /* stack size */

#ifdef CONFIG_USE_IRQ
#define CONFIG_STACKSIZE_IRQ    (4<<10)        /* IRQ stack  */
#define CONFIG_STACKSIZE_FIQ    (4<<10)        /* FIQ stack  */
#endif

#define CONFIG_NR_DRAM_BANKS    1                /* we have 1 bank of SDRAM */
#define WEP_SDRAM_1            0xa0000000        /* SDRAM bank #1           */
#define WEP_SDRAM_1_SIZE       0x02000000        /* 32 MB ( 2 chip )        */
#define WEP_SDRAM_2            0xa2000000        /* SDRAM bank #2           */
#define WEP_SDRAM_2_SIZE       0x00000000        /* 0 MB                    */
#define WEP_SDRAM_3            0xa8000000        /* SDRAM bank #3           */
#define WEP_SDRAM_3_SIZE       0x00000000        /* 0 MB                    */
#define WEP_SDRAM_4            0xac000000        /* SDRAM bank #4           */
#define WEP_SDRAM_4_SIZE       0x00000000        /* 0 MB                    */

#define CONFIG_SYS_DRAM_BASE           0xa0000000
#define CONFIG_SYS_DRAM_SIZE           0x02000000

/* Uncomment used SDRAM chip */
#define WEP_SDRAM_K4S281633
/*#define WEP_SDRAM_K4S561633*/


#define CONFIG_SYS_MAX_FLASH_BANKS	1	/* FLASH banks count (not chip count)*/
#define CONFIG_SYS_MAX_FLASH_SECT	128	/* number of sector in FLASH bank    */
#define WEP_FLASH_BUS_WIDTH	4	/* we use 32 bit FLASH memory...     */
#define WEP_FLASH_INTERLEAVE	2	/* ... made of 2 chips */
#define WEP_FLASH_BANK_SIZE  0x2000000  /* size of one flash bank*/
#define WEP_FLASH_SECT_SIZE  0x0040000  /* size of erase sector */
#define WEP_FLASH_BASE       0x0000000  /* location of flash memory */
#define WEP_FLASH_UNLOCK        1       /* perform hw unlock first */


#undef  CONFIG_SYS_FLASH_CFI

#define CONFIG_SYS_FLASH_ERASE_TOUT    (2*CONFIG_SYS_HZ)    /* timeout for Erase operation */
#define CONFIG_SYS_FLASH_WRITE_TOUT    (2*CONFIG_SYS_HZ)    /* timeout for Write operation */

#define CONFIG_SYS_FLASH_BASE          WEP_FLASH_BASE

#define CONFIG_SYS_JFFS2_FIRST_BANK		0
#define CONFIG_SYS_JFFS2_FIRST_SECTOR		5
#define CONFIG_SYS_JFFS2_NUM_BANKS		1


#define CONFIG_SYS_MONITOR_BASE	PHYS_FLASH_1
#define CONFIG_SYS_MONITOR_LEN		0x20000		/* 128kb ( 1 flash sector )  */
#define CONFIG_ENV_IS_IN_FLASH	1
#define CONFIG_ENV_ADDR		0x20000	        /* absolute address for now  */
#define CONFIG_ENV_SIZE		0x2000

#undef  CONFIG_ENV_OVERWRITE                    /* env is not writable now   */

#define CONFIG_SYS_LOAD_ADDR        0x40000

#endif  /* __CONFIG_H */
