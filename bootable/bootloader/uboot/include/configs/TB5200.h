

#ifndef __CONFIG_H
#define __CONFIG_H


#define CONFIG_MPC5xxx		1	/* This is an MPC5xxx CPU */
#define CONFIG_MPC5200		1	/* (more precisely an MPC5200 CPU) */
#define CONFIG_TQM5200		1	/* ... on TQM5200 module */
#define CONFIG_TB5200		1	/* ... on a TB5200 base board */

#define CONFIG_SYS_MPC5XXX_CLKIN	33000000 /* ... running at 33.000000MHz */

#define BOOTFLAG_COLD		0x01	/* Normal Power-On: Boot from FLASH  */
#define BOOTFLAG_WARM		0x02	/* Software reboot	     */

#define CONFIG_HIGH_BATS	1	/* High BATs supported */

#define CONFIG_PSC_CONSOLE	1	/* default console is on PSC1 */
#define CONFIG_SERIAL_MULTI	1	/* support multiple consoles */
#define CONFIG_PSC_CONSOLE2	6	/* second console is on PSC6 */
#define CONFIG_BAUDRATE		115200	/* ... at 115200 bps */
#define CONFIG_SYS_BAUDRATE_TABLE	{ 9600, 19200, 38400, 57600, 115200, 230400 }

#if 1
#define CONFIG_VIDEO
#define CONFIG_VIDEO_SM501
#define CONFIG_VIDEO_SM501_32BPP
#define CONFIG_CFB_CONSOLE
#define CONFIG_VIDEO_LOGO
#define CONFIG_VGA_AS_SINGLE_DEVICE
#define CONFIG_CONSOLE_EXTRA_INFO
#define CONFIG_VIDEO_SW_CURSOR
#define CONFIG_SPLASH_SCREEN
#define CONFIG_SYS_CONSOLE_IS_IN_ENV
#endif

/* Partitions */
#define CONFIG_MAC_PARTITION
#define CONFIG_DOS_PARTITION
#define CONFIG_ISO_PARTITION

/* USB */
#define CONFIG_USB_OHCI
#define CONFIG_USB_STORAGE

/* POST support */
#define CONFIG_POST		(CONFIG_SYS_POST_MEMORY   | \
				 CONFIG_SYS_POST_CPU	   | \
				 CONFIG_SYS_POST_I2C)

#ifdef CONFIG_POST
/* preserve space for the post_word at end of on-chip SRAM */
#define MPC5XXX_SRAM_POST_SIZE MPC5XXX_SRAM_SIZE-4
#endif


#define CONFIG_BOOTP_BOOTFILESIZE
#define CONFIG_BOOTP_BOOTPATH
#define CONFIG_BOOTP_GATEWAY
#define CONFIG_BOOTP_HOSTNAME


#include <config_cmd_default.h>

#define CONFIG_CMD_ASKENV
#define CONFIG_CMD_DATE
#define CONFIG_CMD_DHCP
#define CONFIG_CMD_ECHO
#define CONFIG_CMD_EEPROM
#define CONFIG_CMD_EXT2
#define CONFIG_CMD_FAT
#define CONFIG_CMD_I2C
#define CONFIG_CMD_IDE
#define CONFIG_CMD_JFFS2
#define CONFIG_CMD_MII
#define CONFIG_CMD_NFS
#define CONFIG_CMD_PING
#define CONFIG_CMD_REGINFO
#define CONFIG_CMD_SNTP
#define CONFIG_CMD_BSP
#define CONFIG_CMD_USB

#ifdef CONFIG_VIDEO
#define CONFIG_CMD_BMP
#endif

#ifdef CONFIG_POST
#define CONFIG__CMD_DIAG
#endif


#define	CONFIG_TIMESTAMP		/* display image timestamps */

#if (TEXT_BASE == 0xFC000000)		/* Boot low */
#   define CONFIG_SYS_LOWBOOT		1
#endif

#define CONFIG_BOOTDELAY	5	/* autoboot after 5 seconds */

#define CONFIG_PREBOOT	"echo;" \
	"echo Type \\\"run flash_nfs\\\" to mount root filesystem over NFS;" \
	"echo"

#undef	CONFIG_BOOTARGS

#if defined(CONFIG_TQM5200_B)
#define CONFIG_EXTRA_ENV_SETTINGS					\
	"netdev=eth0\0"							\
	"rootpath=/opt/eldk/ppc_6xx\0"					\
	"ramargs=setenv bootargs root=/dev/ram rw\0"			\
	"nfsargs=setenv bootargs root=/dev/nfs rw "			\
		"nfsroot=${serverip}:${rootpath}\0"			\
	"addip=setenv bootargs ${bootargs} "				\
		"ip=${ipaddr}:${serverip}:${gatewayip}:${netmask}"	\
		":${hostname}:${netdev}:off panic=1\0"			\
	"flash_self=run ramargs addip;"					\
		"bootm ${kernel_addr} ${ramdisk_addr}\0"		\
	"flash_nfs=run nfsargs addip;"					\
		"bootm ${kernel_addr}\0"				\
	"net_nfs=tftp 200000 ${bootfile};run nfsargs addip;bootm\0"	\
	"bootfile=/tftpboot/tqm5200/uImage\0"				\
	"load=tftp 200000 ${u-boot}\0"					\
	"u-boot=/tftpboot/tqm5200/u-boot.bin\0"				\
	"update=protect off FC000000 FC07FFFF;"				\
		"erase FC000000 FC07FFFF;"				\
		"cp.b 200000 FC000000 ${filesize};"			\
		"protect on FC000000 FC07FFFF\0"			\
	""
#else
#define CONFIG_EXTRA_ENV_SETTINGS					\
	"netdev=eth0\0"							\
	"rootpath=/opt/eldk/ppc_6xx\0"					\
	"ramargs=setenv bootargs root=/dev/ram rw\0"			\
	"nfsargs=setenv bootargs root=/dev/nfs rw "			\
		"nfsroot=${serverip}:${rootpath}\0"			\
	"addip=setenv bootargs ${bootargs} "				\
		"ip=${ipaddr}:${serverip}:${gatewayip}:${netmask}"	\
		":${hostname}:${netdev}:off panic=1\0"			\
	"flash_self=run ramargs addip;"					\
		"bootm ${kernel_addr} ${ramdisk_addr}\0"		\
	"flash_nfs=run nfsargs addip;"					\
		"bootm ${kernel_addr}\0"				\
	"net_nfs=tftp 200000 ${bootfile};run nfsargs addip;bootm\0"	\
	"bootfile=/tftpboot/tqm5200/uImage\0"				\
	"load=tftp 200000 $(u-boot)\0"					\
	"u-boot=/tftpboot/tqm5200/u-boot.bin\0"				\
	"update=protect off FC000000 FC05FFFF;"				\
		"erase FC000000 FC05FFFF;"				\
		"cp.b 200000 FC000000 ${filesize};"			\
		"protect on FC000000 FC05FFFF\0"			\
	""
#endif /* CONFIG_TQM5200_B */

#define CONFIG_BOOTCOMMAND	"run net_nfs"

#define CONFIG_SYS_IPBCLK_EQUALS_XLBCLK		/* define for 133MHz speed */

#if defined(CONFIG_SYS_IPBCLK_EQUALS_XLBCLK)
#define CONFIG_SYS_PCICLK_EQUALS_IPBCLK_DIV2		/* define for 66MHz speed */
#endif

#define CONFIG_HARD_I2C		1	/* I2C with hardware support */
#define CONFIG_SYS_I2C_MODULE		2	/* Select I2C module #2 */

#define CONFIG_SYS_I2C_SPEED		100000 /* 100 kHz */
#define CONFIG_SYS_I2C_SLAVE		0x7F

#define CONFIG_SYS_I2C_EEPROM_ADDR		0x50	/* 1010000x */
#define CONFIG_SYS_I2C_EEPROM_ADDR_LEN		2
#define CONFIG_SYS_EEPROM_PAGE_WRITE_BITS	5	/* =32 Bytes per write */
#define CONFIG_SYS_EEPROM_PAGE_WRITE_DELAY_MS	20

/* List of I2C addresses to be verified by POST */
#undef I2C_ADDR_LIST
#define I2C_ADDR_LIST	{	CONFIG_SYS_I2C_EEPROM_ADDR,	\
				CONFIG_SYS_I2C_RTC_ADDR,	\
				CONFIG_SYS_I2C_SLAVE }

#define CONFIG_SYS_FLASH_BASE		TEXT_BASE /* 0xFC000000 */

/* use CFI flash driver */
#define CONFIG_SYS_FLASH_CFI		1	/* Flash is CFI conformant */
#define CONFIG_FLASH_CFI_DRIVER	1	/* Use the common driver */
#define CONFIG_SYS_FLASH_BANKS_LIST	{ CONFIG_SYS_BOOTCS_START }
#define CONFIG_SYS_FLASH_EMPTY_INFO
#define CONFIG_SYS_FLASH_SIZE		0x04000000 /* 64 MByte */
#define CONFIG_SYS_MAX_FLASH_SECT	512	/* max num of sects on one chip */
#define CONFIG_SYS_FLASH_USE_BUFFER_WRITE	1

#if !defined(CONFIG_SYS_LOWBOOT)
#define CONFIG_ENV_ADDR		(CONFIG_SYS_FLASH_BASE + 0x00760000 + 0x00800000)
#else	/* CONFIG_SYS_LOWBOOT */
#if defined(CONFIG_TQM5200_B)
#define CONFIG_ENV_ADDR		(CONFIG_SYS_FLASH_BASE + 0x00080000)
#else
#define CONFIG_ENV_ADDR		(CONFIG_SYS_FLASH_BASE + 0x00060000)
#endif /* CONFIG_TQM5200_B */
#endif	/* CONFIG_SYS_LOWBOOT */
#define CONFIG_SYS_MAX_FLASH_BANKS	1	/* max num of flash banks
					   (= chip selects) */

/* Dynamic MTD partition support */
#define CONFIG_CMD_MTDPARTS
#define CONFIG_MTD_DEVICE		/* needed for mtdparts commands */
#define CONFIG_FLASH_CFI_MTD
#define MTDIDS_DEFAULT		"nor0=TQM5200-0"
#if defined(CONFIG_TQM5200_B)
#define MTDPARTS_DEFAULT	"mtdparts=TQM5200-0:768k(firmware),"	\
						"1280k(kernel),"	\
						"2m(initrd),"		\
						"4m(small-fs),"		\
						"16m(big-fs),"		\
						"8m(misc)"
#else
#define MTDPARTS_DEFAULT	"mtdparts=TQM5200-0:640k(firmware),"	\
						"1408k(kernel),"	\
						"2m(initrd),"		\
						"4m(small-fs),"		\
						"16m(big-fs),"		\
						"8m(misc)"
#endif /* CONFIG_TQM5200_B */

#define CONFIG_ENV_IS_IN_FLASH	1
#define CONFIG_ENV_SIZE		0x10000
#if defined(CONFIG_TQM5200_B)
#define CONFIG_ENV_SECT_SIZE	0x40000
#else
#define CONFIG_ENV_SECT_SIZE	0x20000
#define CONFIG_ENV_ADDR_REDUND	(CONFIG_ENV_ADDR + CONFIG_ENV_SECT_SIZE)
#define CONFIG_ENV_SIZE_REDUND	(CONFIG_ENV_SIZE)
#endif /* CONFIG_TQM5200_B */

#define CONFIG_SYS_MBAR		0xF0000000
#define CONFIG_SYS_SDRAM_BASE		0x00000000
#define CONFIG_SYS_DEFAULT_MBAR	0x80000000

/* Use ON-Chip SRAM until RAM will be available */
#define CONFIG_SYS_INIT_RAM_ADDR	MPC5XXX_SRAM
#ifdef CONFIG_POST
/* preserve space for the post_word at end of on-chip SRAM */
#define CONFIG_SYS_INIT_RAM_END	MPC5XXX_SRAM_POST_SIZE
#else
#define CONFIG_SYS_INIT_RAM_END	MPC5XXX_SRAM_SIZE
#endif


#define CONFIG_SYS_GBL_DATA_SIZE	128	/* size in bytes reserved for initial data */
#define CONFIG_SYS_GBL_DATA_OFFSET	(CONFIG_SYS_INIT_RAM_END - CONFIG_SYS_GBL_DATA_SIZE)
#define CONFIG_SYS_INIT_SP_OFFSET	CONFIG_SYS_GBL_DATA_OFFSET

#define CONFIG_SYS_MONITOR_BASE	TEXT_BASE
#if (CONFIG_SYS_MONITOR_BASE < CONFIG_SYS_FLASH_BASE)
#   define CONFIG_SYS_RAMBOOT		1
#endif

#if defined(CONFIG_TQM5200_B)
#define CONFIG_SYS_MONITOR_LEN		(512 << 10)	/* Reserve 512 kB for Monitor	*/
#else
#define CONFIG_SYS_MONITOR_LEN		(384 << 10)	/* Reserve 384 kB for Monitor	*/
#endif /* CONFIG_TQM5200_B */
#define CONFIG_SYS_MALLOC_LEN		(1024 << 10)	/* Reserve 1024 kB for malloc()	*/
#define CONFIG_SYS_BOOTMAPSZ		(8 << 20)	/* Initial Memory map for Linux */

#define CONFIG_MPC5xxx_FEC	1
#define CONFIG_MPC5xxx_FEC_MII100
/* #define CONFIG_MPC5xxx_FEC_MII10 */
#define CONFIG_PHY_ADDR		0x00

#define CONFIG_SYS_GPS_PORT_CONFIG	0x81500114

#define CONFIG_RTC_M41T11	1
#define CONFIG_SYS_I2C_RTC_ADDR	0x68
#define CONFIG_SYS_M41T11_BASE_YEAR	1900    /* because Linux uses the same base
					   year */

#define CONFIG_SYS_LONGHELP			/* undef to save memory	    */
#define CONFIG_SYS_PROMPT		"=> "	/* Monitor Command Prompt   */
#define CONFIG_CMDLINE_EDITING	1	/* add command line history */
#if defined(CONFIG_CMD_KGDB)
#define CONFIG_SYS_CBSIZE		1024	/* Console I/O Buffer Size  */
#else
#define CONFIG_SYS_CBSIZE		256	/* Console I/O Buffer Size  */
#endif
#define CONFIG_SYS_PBSIZE (CONFIG_SYS_CBSIZE+sizeof(CONFIG_SYS_PROMPT)+16) /* Print Buffer Size */
#define CONFIG_SYS_MAXARGS		16	/* max number of command args	*/
#define CONFIG_SYS_BARGSIZE		CONFIG_SYS_CBSIZE	/* Boot Argument Buffer Size	*/

#define CONFIG_SYS_CACHELINE_SIZE	32	/* For MPC5xxx CPUs */
#if defined(CONFIG_CMD_KGDB)
#  define CONFIG_SYS_CACHELINE_SHIFT	5	/* log base 2 of the above value */
#endif

/* Enable an alternate, more extensive memory test */
#define CONFIG_SYS_ALT_MEMTEST

#define CONFIG_SYS_MEMTEST_START	0x00100000	/* memtest works on */
#define CONFIG_SYS_MEMTEST_END		0x00f00000	/* 1 ... 15 MB in DRAM	*/

#define CONFIG_SYS_LOAD_ADDR		0x100000	/* default load address */

#define CONFIG_SYS_HZ			1000	/* decrementer freq: 1 ms ticks */

#define CONFIG_LOOPW

#define CONFIG_SYS_HID0_INIT		HID0_ICE | HID0_ICFI
#define CONFIG_SYS_HID0_FINAL		HID0_ICE

#define CONFIG_SYS_BOOTCS_START	CONFIG_SYS_FLASH_BASE
#define CONFIG_SYS_BOOTCS_SIZE		CONFIG_SYS_FLASH_SIZE
#ifdef CONFIG_SYS_PCICLK_EQUALS_IPBCLK_DIV2
#define CONFIG_SYS_BOOTCS_CFG		0x0008DF30 /* for pci_clk  = 66 MHz */
#else
#define CONFIG_SYS_BOOTCS_CFG		0x0004DF30 /* for pci_clk = 33 MHz */
#endif
#define CONFIG_SYS_CS0_START		CONFIG_SYS_FLASH_BASE
#define CONFIG_SYS_CS0_SIZE		CONFIG_SYS_FLASH_SIZE

#define CONFIG_LAST_STAGE_INIT

#define CONFIG_SYS_CS2_START		0xE5000000
#define CONFIG_SYS_CS2_SIZE		0x100000	/* 1 MByte */
#define CONFIG_SYS_CS2_CFG		0x0004D930

#define SM501_FB_BASE		0xE0000000
#define CONFIG_SYS_CS1_START		(SM501_FB_BASE)
#define CONFIG_SYS_CS1_SIZE		0x4000000	/* 64 MByte */
#define CONFIG_SYS_CS1_CFG		0x8F48FF70
#define SM501_MMIO_BASE		CONFIG_SYS_CS1_START + 0x03E00000

#define CONFIG_SYS_CS_BURST		0x00000000
#define CONFIG_SYS_CS_DEADCYCLE	0x33333311	/* 1 dead cycle for flash and SM501 */

#define CONFIG_SYS_RESET_ADDRESS	0xff000000

#define CONFIG_USB_CLOCK	0x0001BBBB
#define CONFIG_USB_CONFIG	0x00001000


#undef	CONFIG_IDE_8xx_PCCARD		/* Use IDE with PC Card Adapter */

#undef	CONFIG_IDE_8xx_DIRECT		/* Direct IDE	 not supported	*/
#undef	CONFIG_IDE_LED			/* LED	 for ide not supported	*/

#define CONFIG_IDE_RESET		/* reset for ide supported	*/
#define CONFIG_IDE_PREINIT

#define CONFIG_SYS_IDE_MAXBUS		1	/* max. 1 IDE bus		*/
#define CONFIG_SYS_IDE_MAXDEVICE	2	/* max. 2 drives per IDE bus	*/

#define CONFIG_SYS_ATA_IDE0_OFFSET	0x0000

#define CONFIG_SYS_ATA_BASE_ADDR	MPC5XXX_ATA

/* Offset for data I/O			*/
#define CONFIG_SYS_ATA_DATA_OFFSET	(0x0060)

/* Offset for normal register accesses	*/
#define CONFIG_SYS_ATA_REG_OFFSET	(CONFIG_SYS_ATA_DATA_OFFSET)

/* Offset for alternate registers	*/
#define CONFIG_SYS_ATA_ALT_OFFSET	(0x005C)

/* Interval between registers						     */
#define CONFIG_SYS_ATA_STRIDE		4

#endif /* __CONFIG_H */
