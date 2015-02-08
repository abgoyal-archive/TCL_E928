


#ifndef __CONFIG_H
#define __CONFIG_H


#define CONFIG_405EP		1	/* This is a PPC405 CPU		*/
#define CONFIG_4xx		1	/* ...member of PPC4xx family	*/
#define CONFIG_G2000		1	/* ...on a PLU405 board		*/

#define CONFIG_BOARD_EARLY_INIT_F 1	/* call board_early_init_f()	*/
#define CONFIG_MISC_INIT_R	1	/* call misc_init_r()		*/

#define CONFIG_SYS_CLK_FREQ     33333333 /* external frequency to pll   */

#if 0 /* test-only */
#define CONFIG_BAUDRATE		115200
#else
#define CONFIG_BAUDRATE		9600
#endif

#define CONFIG_PREBOOT

#undef	CONFIG_BOOTARGS

#define	CONFIG_EXTRA_ENV_SETTINGS					\
	"nfsargs=setenv bootargs root=/dev/nfs rw "			\
		"nfsroot=${serverip}:${rootpath}\0"			\
	"ramargs=setenv bootargs root=/dev/ram rw\0"			\
	"addip=setenv bootargs ${bootargs} "				\
		"ip=${ipaddr}:${serverip}:${gatewayip}:${netmask}"	\
		":${hostname}:${netdev}:off\0"				\
	"addmisc=setenv bootargs ${bootargs} "				\
		"console=ttyS0,${baudrate} "				\
		"panic=1\0"						\
	"flash_nfs=run nfsargs addip addmisc;"				\
		"bootm ${kernel_addr}\0"				\
	"flash_self=run ramargs addip addmisc;"				\
		"bootm ${kernel_addr} ${ramdisk_addr}\0"		\
	"net_nfs=tftp 200000 ${bootfile};"				\
		"run nfsargs addip addmisc;bootm\0"			\
	"rootpath=/opt/eldk/ppc_4xx\0"					\
	"bootfile=/tftpboot/g2000/pImage\0"				\
	"kernel_addr=ff800000\0"				        \
	"ramdisk_addr=ff900000\0"				        \
	"pciconfighost=yes\0"				                \
	""
#define CONFIG_BOOTCOMMAND	"run net_nfs"

#define CONFIG_SYS_LOADS_BAUD_CHANGE	1	/* allow baudrate change	*/

#define CONFIG_NET_MULTI	1

#define CONFIG_PPC4xx_EMAC
#define CONFIG_MII		1	/* MII PHY management		*/
#define CONFIG_PHY_ADDR		0	/* PHY address			*/
#define CONFIG_PHY1_ADDR	1	/* PHY address			*/

#if 0 /* test-only */
#define CONFIG_PHY_CLK_FREQ	EMAC_STACR_CLK_66MHZ /* 66 MHz OPB clock*/
#endif


#define CONFIG_BOOTP_BOOTFILESIZE
#define CONFIG_BOOTP_BOOTPATH
#define CONFIG_BOOTP_GATEWAY
#define CONFIG_BOOTP_HOSTNAME


#include <config_cmd_default.h>

#define CONFIG_CMD_DHCP
#define CONFIG_CMD_PCI
#define CONFIG_CMD_IRQ
#define CONFIG_CMD_ELF
#define CONFIG_CMD_DATE
#define CONFIG_CMD_I2C
#define CONFIG_CMD_MII
#define CONFIG_CMD_PING
#define CONFIG_CMD_BSP
#define CONFIG_CMD_EEPROM


#undef	CONFIG_WATCHDOG			/* watchdog disabled		*/

#if 0 /* test-only */
#define CONFIG_SDRAM_BANK0	1	/* init onboard SDRAM bank 0	*/
#endif

#define CONFIG_SYS_LONGHELP			/* undef to save memory		*/
#define CONFIG_SYS_PROMPT	"=> "		/* Monitor Command Prompt	*/

#undef	CONFIG_SYS_HUSH_PARSER			/* use "hush" command parser	*/
#ifdef	CONFIG_SYS_HUSH_PARSER
#define CONFIG_SYS_PROMPT_HUSH_PS2	"> "
#endif

#if defined(CONFIG_CMD_KGDB)
#define CONFIG_SYS_CBSIZE	1024		/* Console I/O Buffer Size	*/
#else
#define CONFIG_SYS_CBSIZE	256		/* Console I/O Buffer Size	*/
#endif
#define CONFIG_SYS_PBSIZE (CONFIG_SYS_CBSIZE+sizeof(CONFIG_SYS_PROMPT)+16) /* Print Buffer Size */
#define CONFIG_SYS_MAXARGS	16		/* max number of command args	*/
#define CONFIG_SYS_BARGSIZE	CONFIG_SYS_CBSIZE	/* Boot Argument Buffer Size	*/

#define CONFIG_SYS_DEVICE_NULLDEV	1	/* include nulldev device	*/

#define CONFIG_SYS_CONSOLE_INFO_QUIET	1	/* don't print console @ startup*/

#define CONFIG_AUTO_COMPLETE	1       /* add autocompletion support   */

#define CONFIG_SYS_MEMTEST_START	0x0400000	/* memtest works on	*/
#define CONFIG_SYS_MEMTEST_END		0x0C00000	/* 4 ... 12 MB in DRAM	*/

#undef	CONFIG_SYS_EXT_SERIAL_CLOCK	       /* no external serial clock used */
#define CONFIG_SYS_BASE_BAUD	    691200
#undef	CONFIG_UART1_CONSOLE		/* define for uart1 as console	*/

/* The following table includes the supported baudrates */
#define CONFIG_SYS_BAUDRATE_TABLE	\
	{ 300, 600, 1200, 2400, 4800, 9600, 19200, 38400,     \
	 57600, 115200, 230400, 460800, 921600 }

#define CONFIG_SYS_LOAD_ADDR	0x100000	/* default load address */
#define CONFIG_SYS_EXTBDINFO	1		/* To use extended board_into (bd_t) */

#define CONFIG_SYS_HZ		1000		/* decrementer freq: 1 ms ticks */

#define CONFIG_ZERO_BOOTDELAY_CHECK	/* check for keypress on bootdelay==0 */
#define CONFIG_BOOTDELAY	3	/* autoboot after 3 seconds	*/

#define CONFIG_VERSION_VARIABLE 1	/* include version env variable */

#define CONFIG_SYS_RX_ETH_BUFFER	16	/* use 16 rx buffer on 405 emac */

/*----------------------------------------------------------------------------*/
/* adding Ethernet setting:  FTS OUI 00:11:0B */
/*----------------------------------------------------------------------------*/
#define CONFIG_ETHADDR          00:11:0B:00:00:01
#define CONFIG_HAS_ETH1
#define CONFIG_ETH1ADDR         00:11:0B:00:00:02
#define CONFIG_IPADDR		10.48.8.178
#define CONFIG_IP1ADDR		10.48.8.188
#define CONFIG_NETMASK		255.255.255.128
#define CONFIG_SERVERIP		10.48.8.138

#define CONFIG_RTC_DS1337
#define CONFIG_SYS_I2C_RTC_ADDR	0x68

#if 0 /* test-only */
#define CONFIG_SYS_MAX_NAND_DEVICE	1	/* Max number of NAND devices		*/

#define CONFIG_SYS_NAND_CE  (0x80000000 >> 1)	/* our CE is GPIO1 */
#define CONFIG_SYS_NAND_CLE (0x80000000 >> 2)	/* our CLE is GPIO2 */
#define CONFIG_SYS_NAND_ALE (0x80000000 >> 3)	/* our ALE is GPIO3 */
#define CONFIG_SYS_NAND_RDY (0x80000000 >> 4)	/* our RDY is GPIO4 */

#endif

#define PCI_HOST_ADAPTER 0              /* configure as pci adapter     */
#define PCI_HOST_FORCE  1               /* configure as pci host        */
#define PCI_HOST_AUTO   2               /* detected via arbiter enable  */

#define CONFIG_PCI			/* include pci support	        */
#define CONFIG_PCI_HOST	PCI_HOST_HOST   /* select pci host function     */
#define CONFIG_PCI_PNP			/* do pci plug-and-play         */
					/* resource configuration       */

#define CONFIG_PCI_SCAN_SHOW            /* print pci devices @ startup  */

#define CONFIG_PCI_CONFIG_HOST_BRIDGE 1 /* don't skip host bridge config*/

#define CONFIG_SYS_PCI_SUBSYS_VENDORID 0x12FE  /* PCI Vendor ID: esd gmbh      */
#define CONFIG_SYS_PCI_SUBSYS_DEVICEID 0x0405  /* PCI Device ID: CPCI-405      */
#define CONFIG_SYS_PCI_CLASSCODE       0x0b20  /* PCI Class Code: Processor/PPC*/
#define CONFIG_SYS_PCI_PTM1LA  0x00000000      /* point to sdram               */
#define CONFIG_SYS_PCI_PTM1MS  0xfc000001      /* 64MB, enable hard-wired to 1 */
#define CONFIG_SYS_PCI_PTM1PCI 0x00000000      /* Host: use this pci address   */
#define CONFIG_SYS_PCI_PTM2LA  0xffc00000      /* point to flash               */
#define CONFIG_SYS_PCI_PTM2MS  0xffc00001      /* 4MB, enable                  */
#define CONFIG_SYS_PCI_PTM2PCI 0x04000000      /* Host: use this pci address   */

#define CONFIG_SYS_BOOTMAPSZ		(8 << 20)	/* Initial Memory map for Linux */

#if 0 /* APC405 */
#define CONFIG_SYS_FLASH_CFI		1	/* Flash is CFI conformant		*/
#define CONFIG_SYS_MAX_FLASH_SECT	128	/* max number of sectors on one chip	*/
#define CONFIG_SYS_MAX_FLASH_BANKS	2	/* max number of memory banks		*/
#undef CONFIG_SYS_FLASH_PROTECTION		/* don't use hardware protection	*/
#define CONFIG_SYS_FLASH_USE_BUFFER_WRITE 1	/* use buffered writes (20x faster)	*/
#define CONFIG_SYS_FLASH_BASE		0xFE000000 /* test-only...*/
#define CONFIG_SYS_FLASH_INCREMENT	0x01000000 /* test-only */
#else /* G2000 */
#define CONFIG_SYS_FLASH_CFI		1	/* Flash is CFI conformant		*/
#define CONFIG_SYS_MAX_FLASH_SECT	128	/* max number of sectors on one chip	*/
#define CONFIG_SYS_MAX_FLASH_BANKS	1	/* max number of memory banks		*/
#undef CONFIG_SYS_FLASH_PROTECTION		/* don't use hardware protection	*/
#define CONFIG_SYS_FLASH_USE_BUFFER_WRITE 1	/* use buffered writes (20x faster)	*/
#define CONFIG_SYS_FLASH_BASE		0xFF800000 /* test-only...*/
#define CONFIG_SYS_FLASH_INCREMENT	0x01000000 /* test-only */
#endif

#define CONFIG_SYS_FLASH_EMPTY_INFO            /* print 'E' for empty sector on flinfo */

#define CONFIG_SYS_JFFS2_FIRST_BANK    0           /* use for JFFS2 */
#define CONFIG_SYS_JFFS2_NUM_BANKS     1           /* ! second bank contains u-boot    */

#define CONFIG_SYS_SDRAM_BASE		0x00000000
#define CONFIG_SYS_MONITOR_BASE	0xFFFC0000
#define CONFIG_SYS_MONITOR_LEN		(256 * 1024)	/* Reserve 256 kB for Monitor	*/
#define CONFIG_SYS_MALLOC_LEN		(256 * 1024)	/* Reserve 256 kB for malloc()	*/

#if 1 /* test-only */
#define CONFIG_ENV_IS_IN_EEPROM	1	/* use EEPROM for environment vars */
#define CONFIG_ENV_OFFSET		0x100	/* environment starts at the beginning of the EEPROM */
#define CONFIG_ENV_SIZE		0x700	/* 2048 bytes may be used for env vars*/
				   /* total size of a CAT24WC16 is 2048 bytes */

#else	/* DEFAULT: environment in flash, using redundand flash sectors */

#define CONFIG_ENV_IS_IN_FLASH	1	/* use FLASH for environment vars */
#define CONFIG_ENV_ADDR		0xFFFA0000 /* environment starts before u-boot */
#define CONFIG_ENV_SECT_SIZE	0x20000	/* 128k bytes may be used for env vars*/

#endif

#define CONFIG_HARD_I2C			/* I2c with hardware support */
#define CONFIG_PPC4XX_I2C		/* use PPC4xx driver		*/
#define CONFIG_SYS_I2C_SPEED		400000	/* I2C speed and slave address */
#define CONFIG_SYS_I2C_SLAVE		0x7F

#define CONFIG_SYS_I2C_EEPROM_ADDR	0x50	/* EEPROM CAT24WC08		*/
/* CAT24WC08/16... */
#define CONFIG_SYS_I2C_EEPROM_ADDR_LEN 1	/* Bytes of address		*/
/* mask of address bits that overflow into the "EEPROM chip address"	*/
#define CONFIG_SYS_I2C_EEPROM_ADDR_OVERFLOW	0x07
#define CONFIG_SYS_EEPROM_PAGE_WRITE_BITS 4	/* The Catalyst CAT24WC08 has	*/
					/* 16 byte page write mode using*/
					/* last 4 bits of the address	*/
#define CONFIG_SYS_EEPROM_PAGE_WRITE_DELAY_MS	10   /* and takes up to 10 msec */


/* Memory Bank 0 (Intel Strata Flash) initialization                            */
#define CONFIG_SYS_EBC_PB0AP   0x92015480
#define CONFIG_SYS_EBC_PB0CR   0xFF87A000          /* BAS=0xFF8,BS=08MB,BU=R/W,BW=16bit*/

/* Memory Bank 1 ( Power TAU) initialization               */
/* #define CONFIG_SYS_EBC_PB1AP           0x04041000 */
/* #define CONFIG_SYS_EBC_PB1CR           0xF0018000   */  /* BAS=0xF00,BS=1MB,BU=R/W,BW=8bit  */
#define CONFIG_SYS_EBC_PB1AP           0x00000000
#define CONFIG_SYS_EBC_PB1CR           0x00000000

/* Memory Bank 2 (Intel Flash) initialization                 */
#define CONFIG_SYS_EBC_PB2AP           0x00000000
#define CONFIG_SYS_EBC_PB2CR           0x00000000

/* Memory Bank 3 (NAND) initialization                        */
#define CONFIG_SYS_EBC_PB3AP           0x92015480
#define CONFIG_SYS_EBC_PB3CR           0xF40B8000  /*addr 0xF40, BS=32M,BU=R/W, BW=8bit */

/* Memory Bank 4 (FPGA regs) initialization                                     */
#define CONFIG_SYS_EBC_PB4AP           0x00000000
#define CONFIG_SYS_EBC_PB4CR           0x00000000  /* leave it blank  */

#define CONFIG_SYS_NAND_BASE   0xF4000000

/* use on chip memory ( OCM ) for temperary stack until sdram is tested */
#define CONFIG_SYS_TEMP_STACK_OCM	  1

/* On Chip Memory location */
#define CONFIG_SYS_OCM_DATA_ADDR	0xF8000000
#define CONFIG_SYS_OCM_DATA_SIZE	0x1000
#define CONFIG_SYS_INIT_RAM_ADDR	CONFIG_SYS_OCM_DATA_ADDR /* inside of SDRAM		*/
#define CONFIG_SYS_INIT_RAM_END	CONFIG_SYS_OCM_DATA_SIZE /* End of used area in RAM	*/

#define CONFIG_SYS_GBL_DATA_SIZE      128  /* size in bytes reserved for initial data */
#define CONFIG_SYS_GBL_DATA_OFFSET    (CONFIG_SYS_INIT_RAM_END - CONFIG_SYS_GBL_DATA_SIZE)
#define CONFIG_SYS_INIT_SP_OFFSET	CONFIG_SYS_GBL_DATA_OFFSET

#define CONFIG_SYS_GPIO0_OSRH          0x40005555
#define CONFIG_SYS_GPIO0_OSRL          0x40000110
#define CONFIG_SYS_GPIO0_ISR1H         0x00000000
#define CONFIG_SYS_GPIO0_ISR1L         0x15555445
#define CONFIG_SYS_GPIO0_TSRH          0x00000000
#define CONFIG_SYS_GPIO0_TSRL          0x00000000
#define CONFIG_SYS_GPIO0_TCR           0xF7FF8014

#define BOOTFLAG_COLD	0x01		/* Normal Power-On: Boot from FLASH	*/
#define BOOTFLAG_WARM	0x02		/* Software reboot			*/

#if 1
#define PLLMR0_DEFAULT	 PLLMR0_266_66_33_33
#define PLLMR1_DEFAULT	 PLLMR1_266_66_33_33
#endif
#if 0
#define PLLMR0_DEFAULT	 PLLMR0_266_133_66_33
#define PLLMR1_DEFAULT	 PLLMR1_266_133_66_33
#endif
#if 0
#define PLLMR0_DEFAULT	 PLLMR0_200_100_50_33
#define PLLMR1_DEFAULT	 PLLMR1_200_100_50_33
#endif
#if 0
#define PLLMR0_DEFAULT	 PLLMR0_133_66_66_33
#define PLLMR1_DEFAULT	 PLLMR1_133_66_66_33
#endif

#endif	/* __CONFIG_H */
