


/* ------------------------------------------------------------------------- */


#ifndef __CONFIG_H
#define __CONFIG_H


#define CONFIG_PCIPPC2		1	/* this is a PCIPPC2 board	*/

#define CONFIG_BOARD_EARLY_INIT_F 1
#define CONFIG_MISC_INIT_R	1

#define CONFIG_CONS_INDEX	1
#define CONFIG_BAUDRATE		9600
#define CONFIG_SYS_BAUDRATE_TABLE	{ 9600, 19200, 38400, 57600, 115200 }

#define CONFIG_PREBOOT		""
#define CONFIG_BOOTDELAY	5

#define CONFIG_BOOTP_SUBNETMASK
#define CONFIG_BOOTP_GATEWAY
#define CONFIG_BOOTP_HOSTNAME
#define CONFIG_BOOTP_BOOTPATH
#define CONFIG_BOOTP_BOOTFILESIZE

#define CONFIG_MAC_PARTITION
#define CONFIG_DOS_PARTITION


#include <config_cmd_default.h>

#define CONFIG_CMD_ASKENV
#define CONFIG_CMD_BSP
#define CONFIG_CMD_DATE
#define CONFIG_CMD_DHCP
#define CONFIG_CMD_ELF
#define CONFIG_CMD_NFS
#define CONFIG_CMD_PCI
#define CONFIG_CMD_SNTP

#define CONFIG_PCI		1
#define CONFIG_PCI_PNP		1	/* PCI plug-and-play */

#define CONFIG_SYS_LONGHELP			/* undef to save memory		*/
#define CONFIG_SYS_PROMPT	"=> "		/* Monitor Command Prompt	*/

#define	CONFIG_SYS_HUSH_PARSER		1	/* use "hush" command parser	*/
#ifdef	CONFIG_SYS_HUSH_PARSER
#define	CONFIG_SYS_PROMPT_HUSH_PS2	"> "
#endif
#define CONFIG_SYS_CBSIZE	256		/* Console I/O Buffer Size	*/

#define CONFIG_SYS_PBSIZE	(CONFIG_SYS_CBSIZE + sizeof(CONFIG_SYS_PROMPT) + 16)

#define	CONFIG_SYS_MAXARGS	64		/* max number of command args	*/
#define CONFIG_SYS_BARGSIZE	CONFIG_SYS_CBSIZE	/* Boot Argument Buffer Size	*/
#define CONFIG_SYS_LOAD_ADDR	0x00100000	/* Default load address		*/

#define CONFIG_SYS_SDRAM_BASE	    0x00000000
#define CONFIG_SYS_FLASH_BASE	    0xFFF00000
#define CONFIG_SYS_FLASH_MAX_SIZE  0x00100000
#define CONFIG_SYS_MAX_RAM_SIZE    0x20000000  /* 512Mb			*/

#define CONFIG_SYS_RESET_ADDRESS   0xFFF00100

#define CONFIG_SYS_MONITOR_BASE    TEXT_BASE

#define CONFIG_SYS_MONITOR_LEN	    (256 << 10) /* Reserve 256 kB for Monitor	*/
#define CONFIG_SYS_MALLOC_LEN	    (128 << 10) /* Reserve 128 kB for malloc()	*/

#if CONFIG_SYS_MONITOR_BASE >= CONFIG_SYS_SDRAM_BASE && \
    CONFIG_SYS_MONITOR_BASE < CONFIG_SYS_SDRAM_BASE + CONFIG_SYS_MAX_RAM_SIZE
#define CONFIG_SYS_RAMBOOT
#else
#undef CONFIG_SYS_RAMBOOT
#endif

#define CONFIG_SYS_MEMTEST_START   0x00004000	/* memtest works on		*/
#define CONFIG_SYS_MEMTEST_END	    0x02000000	/* 0 ... 32 MB in DRAM		*/


#define CONFIG_SYS_GBL_DATA_SIZE    128

#define CONFIG_SYS_INIT_RAM_ADDR     0x40000000
#define CONFIG_SYS_INIT_RAM_END      0x8000
#define CONFIG_SYS_GBL_DATA_OFFSET  (CONFIG_SYS_INIT_RAM_END - CONFIG_SYS_GBL_DATA_SIZE)
#define CONFIG_SYS_INIT_SP_OFFSET    CONFIG_SYS_GBL_DATA_OFFSET

#define CONFIG_SYS_INIT_RAM_LOCK

#define CONFIG_SYS_SCONSOLE_ADDR     CONFIG_SYS_INIT_RAM_ADDR
#define CONFIG_SYS_SCONSOLE_SIZE     0x0002000

#define CONFIG_SYS_DBAT0L	      (CONFIG_SYS_SDRAM_BASE | BATL_PP_10 | BATL_MEMCOHERENCE)
#define CONFIG_SYS_DBAT0U	      (CONFIG_SYS_SDRAM_BASE | \
			       BATU_BL_256M | BATU_VS | BATU_VP)
#define CONFIG_SYS_DBAT1L	      ((CONFIG_SYS_SDRAM_BASE + 0x10000000) | \
			       BATL_PP_10 | BATL_MEMCOHERENCE)
#define CONFIG_SYS_DBAT1U	      ((CONFIG_SYS_SDRAM_BASE + 0x10000000) | \
			       BATU_BL_256M | BATU_VS | BATU_VP)

#define CONFIG_SYS_DBAT2L	      (CONFIG_SYS_INIT_RAM_ADDR | \
			       BATL_PP_10 | BATL_MEMCOHERENCE)
#define CONFIG_SYS_DBAT2U	      (CONFIG_SYS_INIT_RAM_ADDR | \
			       BATU_BL_128K | BATU_VS | BATU_VP)

#define CONFIG_SYS_DBAT3L	      (0xf0000000 | BATL_PP_10 | BATL_CACHEINHIBIT)
#define CONFIG_SYS_DBAT3U	      (0xf0000000 | BATU_BL_256M | BATU_VS | BATU_VP)

#define CONFIG_SYS_IBAT0L	      CONFIG_SYS_DBAT0L
#define CONFIG_SYS_IBAT0U	      CONFIG_SYS_DBAT0U
#define CONFIG_SYS_IBAT1L	      CONFIG_SYS_DBAT1L
#define CONFIG_SYS_IBAT1U	      CONFIG_SYS_DBAT1U
#define CONFIG_SYS_IBAT2L	      CONFIG_SYS_DBAT2L
#define CONFIG_SYS_IBAT2U	      CONFIG_SYS_DBAT2U
#define CONFIG_SYS_IBAT3L	      CONFIG_SYS_DBAT3L
#define CONFIG_SYS_IBAT3U	      CONFIG_SYS_DBAT3U

#define CONFIG_SYS_HZ		      1000
#define CONFIG_SYS_BUS_HZ            100000000 /* bus speed - 100 mhz          */
#define CONFIG_SYS_CPU_CLK	      300000000
#define CONFIG_SYS_BUS_CLK	      100000000

#define CONFIG_SYS_BOOTMAPSZ	      (8 << 20)	/* Initial Memory map for Linux */

#define CONFIG_SYS_MAX_FLASH_BANKS	1	/* Max number of flash banks		*/
#define CONFIG_SYS_MAX_FLASH_SECT	16	/* Max number of sectors in one bank	*/

#define CONFIG_SYS_FLASH_ERASE_TOUT	120000	/* Timeout for Flash Erase (in ms)	*/
#define CONFIG_SYS_FLASH_WRITE_TOUT	1000	/* Timeout for Flash Write (in ms)	*/

#define CONFIG_ENV_IS_IN_FLASH	1
#define CONFIG_ENV_ADDR		(CONFIG_SYS_FLASH_BASE + 0x70000)
#define CONFIG_ENV_SIZE		0x1000	/* Size of the Environment		*/
#define CONFIG_ENV_SECT_SIZE	0x10000 /* Size of the Environment Sector	*/

#define CONFIG_SYS_CACHELINE_SIZE	32
#if defined(CONFIG_CMD_KGDB)
#  define CONFIG_SYS_CACHELINE_SHIFT	5	/* log base 2 of the above value	*/
#endif

#undef CONFIG_SYS_L2
#define L2_INIT   (L2CR_L2SIZ_2M | L2CR_L2CLK_3 | L2CR_L2RAM_BURST | \
		   L2CR_L2OH_5 | L2CR_L2CTL | L2CR_L2WT)
#define L2_ENABLE (L2_INIT | L2CR_L2E)

#define BOOTFLAG_COLD		0x01	/* Normal Power-On: Boot from FLASH	*/
#define BOOTFLAG_WARM		0x02	/* Software reboot			*/

#define CONFIG_RTC_MK48T59

#define CONFIG_WATCHDOG

#define CONFIG_NET_MULTI			/* Multi ethernet cards support */

#define CONFIG_EEPRO100
#define CONFIG_SYS_RX_ETH_BUFFER	8               /* use 8 rx buffer on eepro100  */
#define CONFIG_TULIP

#endif	/* __CONFIG_H */
