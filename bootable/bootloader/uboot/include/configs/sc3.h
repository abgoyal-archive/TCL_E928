

#ifndef __CONFIG_H
#define __CONFIG_H

#undef USE_VGA_GRAPHICS


#define CONFIG_SC3	1
#define CONFIG_4xx	1
#define CONFIG_405GP	1

#define CONFIG_BOARD_EARLY_INIT_F	1
#define CONFIG_MISC_INIT_R		1	/* Call misc_init_r() */

#define IDE_USES_ISA_EMULATION

#define CONFIG_SERIAL_MULTI
#undef CONFIG_SERIAL_SOFTWARE_FIFO
#if CONFIG_SERIAL_SOFTWARE_FIFO
 #define CONFIG_POWER_DOWN
#endif

#define CONFIG_SYS_CLK_FREQ	33333333

#define CONFIG_BAUDRATE		115200
#define CONFIG_BOOTDELAY	3 /* autoboot after 3 seconds	      */

#define CONFIG_PREBOOT	"echo;"	\
	"echo Type \\\"run flash_nfs\\\" to mount root filesystem over NFS;" \
	"echo"

#undef	CONFIG_BOOTARGS

#define	CONFIG_EXTRA_ENV_SETTINGS					\
	"netdev=eth0\0"							\
	"nfsargs=setenv bootargs root=/dev/nfs rw "			\
		"nfsroot=${serverip}:${rootpath}\0"			\
	"ramargs=setenv bootargs root=/dev/ram rw\0"			\
	"nand_args=setenv bootargs root=/dev/mtdblock5 rw"		\
		"rootfstype=jffs2\0"					\
	"addip=setenv bootargs ${bootargs} "				\
		"ip=${ipaddr}:${serverip}:${gatewayip}:${netmask}"	\
		":${hostname}:${netdev}:off panic=1\0"			\
	"addcons=setenv bootargs ${bootargs} "				\
		"console=ttyS0,${baudrate}\0"				\
	"flash_nfs=run nfsargs addip addcons;"				\
		"bootm ${kernel_addr}\0"				\
	"flash_nand=run nand_args addip addcons;bootm ${kernel_addr}\0"	\
	"net_nfs=tftp 200000 ${bootfile};run nfsargs addip addcons;"	\
		"bootm\0"						\
	"rootpath=/opt/eldk/ppc_4xx\0"					\
	"bootfile=/tftpboot/sc3/uImage\0"				\
	"u-boot=/tftpboot/sc3/u-boot.bin\0"				\
	"setup=tftp 200000 /tftpboot/sc3/setup.img;source 200000\0"	\
	"kernel_addr=FFE08000\0"					\
	""
#undef CONFIG_BOOTCOMMAND

#define CONFIG_SILENT_CONSOLE	1	/* enable silent startup */
#define CONFIG_SYS_DEVICE_NULLDEV	1	/* include nulldev device	*/

#if 1	/* feel free to disable for development */
#define CONFIG_AUTOBOOT_KEYED		/* Enable password protection	*/
#define CONFIG_AUTOBOOT_PROMPT		\
	"\nSC3 - booting... stop with ENTER\n"
#define CONFIG_AUTOBOOT_DELAY_STR	"\r"	/* 1st "password"	*/
#define CONFIG_AUTOBOOT_DELAY_STR2	"\n"	/* 1st "password"	*/
#endif

#define CONFIG_BOOTCOMMAND	"bootp;dcache on;bootm"

#ifdef USE_VGA_GRAPHICS
 #define CONFIG_BOOTARGS	"root=/dev/nfs rw ip=bootp nfsroot=/tftpboot/solidcard3re"
#else
 #define CONFIG_BOOTARGS	"console=ttyS0,115200 root=/dev/nfs rw ip=bootp"
#endif
#undef CONFIG_ISP1161_PRESENT

#undef CONFIG_LOADS_ECHO   /* no echo on for serial download	*/
#define CONFIG_SYS_LOADS_BAUD_CHANGE	1	/* allow baudrate change	*/

#define CONFIG_NET_MULTI
/* #define CONFIG_EEPRO100_SROM_WRITE */
/* #define CONFIG_SHOW_MAC */
#define CONFIG_EEPRO100

#define CONFIG_PPC4xx_EMAC
#define CONFIG_MII 1			/* add 405GP MII PHY management		*/
#define CONFIG_PHY_ADDR 1	/* the connected Phy defaults to address 1 */

#define CONFIG_BOOTP_BOOTFILESIZE
#define CONFIG_BOOTP_BOOTPATH
#define CONFIG_BOOTP_GATEWAY
#define CONFIG_BOOTP_HOSTNAME


#include <config_cmd_default.h>


#define CONFIG_CMD_CACHE
#define CONFIG_CMD_DATE
#define CONFIG_CMD_DHCP
#define CONFIG_CMD_ELF
#define CONFIG_CMD_I2C
#define CONFIG_CMD_IDE
#define CONFIG_CMD_IRQ
#define CONFIG_CMD_JFFS2
#define CONFIG_CMD_MII
#define CONFIG_CMD_NAND
#define CONFIG_CMD_NET
#define CONFIG_CMD_PCI
#define CONFIG_CMD_PING
#define CONFIG_CMD_SOURCE


#undef CONFIG_WATCHDOG			/* watchdog disabled		*/

#define CONFIG_SYS_LONGHELP	1		/* undef to save memory		*/
#define CONFIG_SYS_PROMPT	"SC3> "	/* Monitor Command Prompt	*/
#define	CONFIG_SYS_CBSIZE	256		/* Console I/O Buffer Size	*/

#define CONFIG_SYS_PBSIZE (CONFIG_SYS_CBSIZE+sizeof(CONFIG_SYS_PROMPT)+16) /* Print Buffer Size */

#define CONFIG_SYS_MAXARGS	16		/* max number of command args	*/
#define CONFIG_SYS_BARGSIZE	CONFIG_SYS_CBSIZE	/* Boot Argument Buffer Size	*/

#define CONFIG_SYS_MEMTEST_START	0x0400000	/* memtest works on	*/
#define CONFIG_SYS_MEMTEST_END		0x0C00000	/* 4 ... 12 MB in DRAM	*/

#undef	CONFIG_SYS_EXT_SERIAL_CLOCK		/* external serial clock */
#undef	CONFIG_SYS_405_UART_ERRATA_59		/* 405GP/CR Rev. D silicon */
#define CONFIG_SYS_BASE_BAUD		921600	/* internal clock */

/* The following table includes the supported baudrates */
#define CONFIG_SYS_BAUDRATE_TABLE  \
    {300, 600, 1200, 2400, 4800, 9600, 19200, 38400, 57600, 115200, 230400}

#define CONFIG_SYS_LOAD_ADDR		0x1000000	/* default load address */
#define CONFIG_SYS_EXTBDINFO		1	/* To use extended board_into (bd_t) */

#define	CONFIG_SYS_HZ			1000	/* decrementer freq: 1 ms ticks	*/

#define  CONFIG_HARD_I2C		/* I2C with hardware support	*/
#undef	CONFIG_SOFT_I2C			/* I2C bit-banged		*/
#define CONFIG_PPC4XX_I2C		/* use PPC4xx driver		*/

#define I2C_INIT
#define I2C_ACTIVE 0
#define I2C_TRISTATE 0

#define CONFIG_SYS_I2C_SPEED		100000	/* use the standard 100kHz speed */
#define CONFIG_SYS_I2C_SLAVE		0x7F		/* mask valid bits */

#define CONFIG_RTC_DS1337
#define CONFIG_SYS_I2C_RTC_ADDR 0x68

#define PCI_HOST_ADAPTER 0		/* configure ar pci adapter	*/
#define PCI_HOST_FORCE	1		/* configure as pci host	*/
#define PCI_HOST_AUTO	2		/* detected via arbiter enable	*/

#define CONFIG_PCI			/* include pci support		*/
#define CONFIG_PCI_HOST	PCI_HOST_FORCE	/* select pci host function	*/
#define CONFIG_PCI_PNP			/* do pci plug-and-play		*/
					/* resource configuration	*/

/* If you want to see, whats connected to your PCI bus */
/* #define CONFIG_PCI_SCAN_SHOW */

#define CONFIG_SYS_PCI_SUBSYS_VENDORID 0x0000	/* PCI Vendor ID: to-do!!!	*/
#define CONFIG_SYS_PCI_SUBSYS_DEVICEID 0x0000	/* PCI Device ID: to-do!!!	*/
#define CONFIG_SYS_PCI_PTM1LA	0x00000000	/* point to sdram		*/
#define CONFIG_SYS_PCI_PTM1MS	0x80000001	/* 2GB, enable hard-wired to 1	*/
#define CONFIG_SYS_PCI_PTM1PCI 0x00000000	/* Host: use this pci address	*/
#define CONFIG_SYS_PCI_PTM2LA	0x00000000	/* disabled			*/
#define CONFIG_SYS_PCI_PTM2MS	0x00000000	/* disabled			*/
#define CONFIG_SYS_PCI_PTM2PCI 0x04000000	/* Host: use this pci address	*/

#if !defined(CONFIG_CMD_IDE)

#undef	CONFIG_IDE_LED			/* no led for ide supported	*/
#undef	CONFIG_IDE_RESET		/* no reset for ide supported	*/

#else
#define CONFIG_START_IDE	1	/* check, if use IDE */

#undef	CONFIG_IDE_8xx_DIRECT		/* no pcmcia interface required */
#undef	CONFIG_IDE_LED			/* no led for ide supported	*/
#undef	CONFIG_IDE_RESET		/* no reset for ide supported	*/

#define	CONFIG_ATAPI
#define	CONFIG_DOS_PARTITION
#define	CONFIG_SYS_IDE_MAXDEVICE	(CONFIG_SYS_IDE_MAXBUS*1) /* max. 1 drives per IDE bus */

#ifndef IDE_USES_ISA_EMULATION

/* New and faster access */
#define	CONFIG_SYS_ATA_BASE_ADDR		0x7A000000	/* start of ISA IO emulation */

/* How many IDE busses are available */
#define	CONFIG_SYS_IDE_MAXBUS		1

/* What IDE ports are available */
#define	CONFIG_SYS_ATA_IDE0_OFFSET	0x000		/* first is available */
#undef	CONFIG_SYS_ATA_IDE1_OFFSET			/* second not available */

#define CONFIG_SYS_ATA_DATA_OFFSET	0x0000	/* Offset for data I/O */

#define	CONFIG_SYS_ATA_REG_OFFSET	0x0000	/* Offset for normal register accesses	*/

#define CONFIG_SYS_ATA_ALT_OFFSET	0x008		/* Offset for alternate registers	*/

#else /* IDE_USES_ISA_EMULATION */

#define	CONFIG_SYS_ATA_BASE_ADDR		0x79000000	/* start of ISA IO emulation */

/* How many IDE busses are available */
#define	CONFIG_SYS_IDE_MAXBUS		1

/* What IDE ports are available */
#define	CONFIG_SYS_ATA_IDE0_OFFSET	0x01F0	/* first is available */
#undef	CONFIG_SYS_ATA_IDE1_OFFSET				/* second not available */

#define CONFIG_SYS_ATA_DATA_OFFSET	0x0000	/* Offset for data I/O */

#define	CONFIG_SYS_ATA_REG_OFFSET	0x0000	/* Offset for normal register accesses	*/

#define CONFIG_SYS_ATA_ALT_OFFSET	0x03F0		/* Offset for alternate registers	*/

#endif /* IDE_USES_ISA_EMULATION */

#endif


#define CONFIG_SYS_SDRAM_BASE		0x00000000
#define CONFIG_SYS_FLASH_BASE		0xFFE00000
#define CONFIG_SYS_MONITOR_BASE	0xFFFC0000     /* placed last 256k */
#define CONFIG_SYS_MONITOR_LEN		(224 * 1024)	/* Reserve 224 KiB for Monitor	*/
#define CONFIG_SYS_MALLOC_LEN		(128 * 1024)	/* Reserve 128 KiB for malloc()	*/

#define CONFIG_SYS_BOOTMAPSZ		(8 << 20)	/* Initial Memory map for Linux */
#define CONFIG_SYS_MAX_FLASH_BANKS	2	/* max number of memory banks		*/
#define CONFIG_SYS_MAX_FLASH_SECT	256	/* max number of sectors on one chip	*/

#define CONFIG_SYS_FLASH_CFI			/* flash is CFI compat.	*/
#define CONFIG_FLASH_CFI_DRIVER		/* Use common CFI driver*/
#define CONFIG_SYS_FLASH_EMPTY_INFO		/* print 'E' for empty sector	*/
#define CONFIG_SYS_FLASH_QUIET_TEST	1	/* don't warn upon unknown flash*/
#define CONFIG_SYS_FLASH_ERASE_TOUT	120000	/* Timeout for Flash Erase (in ms)	*/
#define CONFIG_SYS_FLASH_WRITE_TOUT	500	/* Timeout for Flash Write (in ms)	*/
#define CONFIG_SYS_WRITE_SWAPPED_DATA		/* swap Databytes between reading/writing */

#define CONFIG_ENV_IS_IN_FLASH	1
#ifdef CONFIG_ENV_IS_IN_FLASH
#define CONFIG_ENV_OFFSET		0x00000000  /* Offset of Environment Sector in bottom type */
#define CONFIG_ENV_SIZE		0x4000	    /* Total Size of Environment Sector	*/
#define CONFIG_ENV_SECT_SIZE	0x4000	    /* see README - env sector total size	*/

/* Address and size of Redundant Environment Sector	*/
#define CONFIG_ENV_OFFSET_REDUND	(CONFIG_ENV_OFFSET+CONFIG_ENV_SIZE)
#define CONFIG_ENV_SIZE_REDUND	(CONFIG_ENV_SIZE)

#endif
/* let us changing anything in our environment */
#define CONFIG_ENV_OVERWRITE

#define CONFIG_SYS_MAX_NAND_DEVICE	1
#define CONFIG_SYS_NAND_BASE		0x77D00000

#define CONFIG_JFFS2_NAND 1			/* jffs2 on nand support */

/* No command line, one static partition */
#undef	CONFIG_CMD_MTDPARTS
#define CONFIG_JFFS2_DEV		"nand0"
#define CONFIG_JFFS2_PART_SIZE		0x01000000
#define CONFIG_JFFS2_PART_OFFSET	0x00000000


#define FLASH_BASE0_PRELIM	CONFIG_SYS_FLASH_BASE
#define FLASH_BASE1_PRELIM	0


#define CONFIG_SYS_TEMP_STACK_OCM	1
#define CONFIG_SYS_OCM_DATA_ADDR	0xF8000000
#define CONFIG_SYS_OCM_DATA_SIZE	0x1000


#undef CONFIG_SYS_INIT_DCACHE_CS
/* Where the internal SRAM starts */
#define CONFIG_SYS_INIT_RAM_ADDR	CONFIG_SYS_OCM_DATA_ADDR
/* Where the internal SRAM ends (only offset) */
#define CONFIG_SYS_INIT_RAM_END	0x0F00

/* size in bytes reserved for initial data */
#define CONFIG_SYS_GBL_DATA_SIZE     64
#define CONFIG_SYS_GBL_DATA_OFFSET   (CONFIG_SYS_INIT_RAM_END - CONFIG_SYS_GBL_DATA_SIZE)
/* Initial value of the stack pointern in internal SRAM */
#define CONFIG_SYS_INIT_SP_OFFSET    CONFIG_SYS_GBL_DATA_OFFSET

#define BOOTFLAG_COLD	0x01		/* Normal Power-On: Boot from FLASH	*/
#define BOOTFLAG_WARM	0x02		/* Software reboot			*/

/* ################################################################################### */
/* These defines will be used in arch/powerpc/cpu/ppc4xx/cpu_init.c to setup external chip selects  */
/* They are currently undefined cause they are initiaized in board/solidcard3/init.S   */

/* This chip select accesses the boot device */
/* It depends on boot select switch if this device is 16 or 8 bit */

#undef CONFIG_SYS_EBC_PB0AP
#undef CONFIG_SYS_EBC_PB0CR

#undef CONFIG_SYS_EBC_PB1AP
#undef CONFIG_SYS_EBC_PB1CR

#undef CONFIG_SYS_EBC_PB2AP
#undef CONFIG_SYS_EBC_PB2CR

#undef CONFIG_SYS_EBC_PB3AP
#undef CONFIG_SYS_EBC_PB3CR

#undef CONFIG_SYS_EBC_PB4AP
#undef CONFIG_SYS_EBC_PB4CR

#undef CONFIG_SYS_EBC_PB5AP
#undef CONFIG_SYS_EBC_PB5CR

#undef CONFIG_SYS_EBC_PB6AP
#undef CONFIG_SYS_EBC_PB6CR

#undef CONFIG_SYS_EBC_PB7AP
#undef CONFIG_SYS_EBC_PB7CR

#define CONFIG_SYS_EBC_CFG    0xb84ef000

#define CONFIG_SDRAM_BANK0	/* use the standard SDRAM initialization */
#undef CONFIG_SPD_EEPROM

/* #define SC3_DEBUGOUT */
#undef SC3_DEBUGOUT


#define CONFIG_SYS_ISA_MEM_BASE_ADDRESS 0x78000000
#define CONFIG_SYS_ISA_IO_BASE_ADDRESS  0xE8000000
/*#define CONFIG_SYS_ISA_IO_BASE_ADDRESS  0x79000000 */


#ifdef USE_VGA_GRAPHICS
#define CONFIG_VIDEO		/* To enable video controller support */
#define CONFIG_VIDEO_CT69000
#define CONFIG_CFB_CONSOLE
/* #define CONFIG_VIDEO_LOGO */
#define CONFIG_VGA_AS_SINGLE_DEVICE
#define CONFIG_VIDEO_SW_CURSOR
/* #define CONFIG_VIDEO_HW_CURSOR */
#define CONFIG_VIDEO_ONBOARD	/* Video controller is on-board */

#define VIDEO_HW_RECTFILL
#define VIDEO_HW_BITBLT

#endif

#define CONFIG_SC3_VERSION "r1.4"

#define POST_OUT(x) (*((volatile unsigned char*)(0x79000080))=x)

#endif	/* __CONFIG_H */
