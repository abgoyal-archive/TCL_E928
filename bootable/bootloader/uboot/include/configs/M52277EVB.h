


#ifndef _M52277EVB_H
#define _M52277EVB_H

#define CONFIG_MCF5227x		/* define processor family */
#define CONFIG_M52277		/* define processor type */
#define CONFIG_M52277EVB	/* M52277EVB board */

#define CONFIG_MCFUART
#define CONFIG_SYS_UART_PORT		(0)
#define CONFIG_BAUDRATE			115200
#define CONFIG_SYS_BAUDRATE_TABLE	{ 9600 , 19200 , 38400 , 57600, 115200 }

#undef CONFIG_WATCHDOG

#define CONFIG_TIMESTAMP	/* Print image info with timestamp */

#define CONFIG_BOOTP_BOOTFILESIZE
#define CONFIG_BOOTP_BOOTPATH
#define CONFIG_BOOTP_GATEWAY
#define CONFIG_BOOTP_HOSTNAME

/* Command line configuration */
#include <config_cmd_default.h>

#define CONFIG_CMD_CACHE
#define CONFIG_CMD_DATE
#define CONFIG_CMD_ELF
#define CONFIG_CMD_FLASH
#define CONFIG_CMD_I2C
#define CONFIG_CMD_JFFS2
#define CONFIG_CMD_LOADB
#define CONFIG_CMD_LOADS
#define CONFIG_CMD_MEMORY
#define CONFIG_CMD_MISC
#undef CONFIG_CMD_NET
#define CONFIG_CMD_REGINFO
#undef CONFIG_CMD_USB
#undef CONFIG_CMD_BMP
#define CONFIG_CMD_SPI
#define CONFIG_CMD_SF

#define CONFIG_HOSTNAME			M52277EVB
#define CONFIG_SYS_UBOOT_END		0x3FFFF
#define	CONFIG_SYS_LOAD_ADDR2		0x40010007
#ifdef CONFIG_SYS_STMICRO_BOOT
/* ST Micro serial flash */
#define CONFIG_EXTRA_ENV_SETTINGS		\
	"inpclk=" MK_STR(CONFIG_SYS_INPUT_CLKSRC) "\0"	\
	"loadaddr=0x40010000\0"			\
	"uboot=u-boot.bin\0"			\
	"load=loadb ${loadaddr} ${baudrate};"	\
	"loadb " MK_STR(CONFIG_SYS_LOAD_ADDR2) " ${baudrate} \0"	\
	"upd=run load; run prog\0"		\
	"prog=sf probe 0:2 10000 1;"		\
	"sf erase 0 30000;"			\
	"sf write ${loadaddr} 0 30000;"		\
	"save\0"				\
	""
#endif
#ifdef CONFIG_SYS_SPANSION_BOOT
#define CONFIG_EXTRA_ENV_SETTINGS		\
	"inpclk=" MK_STR(CONFIG_SYS_INPUT_CLKSRC) "\0"	\
	"loadaddr=0x40010000\0"			\
	"uboot=u-boot.bin\0"			\
	"load=loadb ${loadaddr} ${baudrate}\0"	\
	"upd=run load; run prog\0"		\
	"prog=prot off " MK_STR(CONFIG_SYS_FLASH_BASE)	\
	" " MK_STR(CONFIG_SYS_UBOOT_END) ";"		\
	"era " MK_STR(CONFIG_SYS_FLASH_BASE) " "	\
	MK_STR(CONFIG_SYS_UBOOT_END) ";"		\
	"cp.b ${loadaddr} " MK_STR(CONFIG_SYS_FLASH_BASE)	\
	" ${filesize}; save\0"			\
	"updsbf=run loadsbf; run progsbf\0"	\
	"loadsbf=loadb ${loadaddr} ${baudrate};"	\
	"loadb " MK_STR(CONFIG_SYS_LOAD_ADDR2) " ${baudrate} \0"	\
	"progsbf=sf probe 0:2 10000 1;"		\
	"sf erase 0 30000;"			\
	"sf write ${loadaddr} 0 30000;"		\
	""
#endif

#define CONFIG_BOOTDELAY		3	/* autoboot after 3 seconds */
/* LCD */
#ifdef CONFIG_CMD_BMP
#define CONFIG_LCD
#define CONFIG_SPLASH_SCREEN
#define CONFIG_LCD_LOGO
#define CONFIG_SHARP_LQ035Q7DH06
#endif

/* USB */
#ifdef CONFIG_CMD_USB
#define CONFIG_USB_EHCI
#define CONFIG_USB_STORAGE
#define CONFIG_DOS_PARTITION
#define CONFIG_MAC_PARTITION
#define CONFIG_ISO_PARTITION
#define CONFIG_SYS_USB_EHCI_REGS_BASE	0xFC0B0000
#define CONFIG_SYS_USB_EHCI_CPU_INIT
#endif

/* Realtime clock */
#define CONFIG_MCFRTC
#undef RTC_DEBUG
#define CONFIG_SYS_RTC_OSCILLATOR	(32 * CONFIG_SYS_HZ)

/* Timer */
#define CONFIG_MCFTMR
#undef CONFIG_MCFPIT

/* I2c */
#define CONFIG_FSL_I2C
#define CONFIG_HARD_I2C		/* I2C with hardware support */
#undef	CONFIG_SOFT_I2C		/* I2C bit-banged               */
#define CONFIG_SYS_I2C_SPEED		80000	/* I2C speed and slave address  */
#define CONFIG_SYS_I2C_SLAVE		0x7F
#define CONFIG_SYS_I2C_OFFSET		0x58000
#define CONFIG_SYS_IMMR			CONFIG_SYS_MBAR

/* DSPI and Serial Flash */
#define CONFIG_CF_SPI
#define CONFIG_CF_DSPI
#define CONFIG_HARD_SPI
#define CONFIG_SYS_SBFHDR_SIZE		0x7
#ifdef CONFIG_CMD_SPI
#	define CONFIG_SYS_DSPI_CS2
#	define CONFIG_SPI_FLASH
#	define CONFIG_SPI_FLASH_STMICRO

#	define CONFIG_SYS_DSPI_CTAR0	(DSPI_CTAR_TRSZ(7) | \
					 DSPI_CTAR_PCSSCK_1CLK | \
					 DSPI_CTAR_PASC(0) | \
					 DSPI_CTAR_PDT(0) | \
					 DSPI_CTAR_CSSCK(0) | \
					 DSPI_CTAR_ASC(0) | \
					 DSPI_CTAR_DT(1))
#endif

/* Input, PCI, Flexbus, and VCO */
#define CONFIG_EXTRA_CLOCK

#define CONFIG_SYS_INPUT_CLKSRC	16000000

#define CONFIG_PRAM		2048	/* 2048 KB */

#define CONFIG_SYS_PROMPT	"-> "
#define CONFIG_SYS_LONGHELP		/* undef to save memory */

#if defined(CONFIG_CMD_KGDB)
#define CONFIG_SYS_CBSIZE	1024	/* Console I/O Buffer Size */
#else
#define CONFIG_SYS_CBSIZE	256	/* Console I/O Buffer Size */
#endif
#define CONFIG_SYS_PBSIZE	(CONFIG_SYS_CBSIZE+sizeof(CONFIG_SYS_PROMPT)+16)	/* Print Buffer Size */
#define CONFIG_SYS_MAXARGS	16	/* max number of command args */
#define CONFIG_SYS_BARGSIZE	CONFIG_SYS_CBSIZE	/* Boot Argument Buffer Size    */

#define CONFIG_SYS_LOAD_ADDR	(CONFIG_SYS_SDRAM_BASE + 0x10000)

#define CONFIG_SYS_HZ		1000

#define CONFIG_SYS_MBAR		0xFC000000


#define CONFIG_SYS_INIT_RAM_ADDR	0x80000000
#define CONFIG_SYS_INIT_RAM_END		0x8000	/* End of used area in internal SRAM */
#define CONFIG_SYS_INIT_RAM_CTRL	0x221
#define CONFIG_SYS_GBL_DATA_SIZE	128	/* size in bytes reserved for initial data */
#define CONFIG_SYS_GBL_DATA_OFFSET	((CONFIG_SYS_INIT_RAM_END - CONFIG_SYS_GBL_DATA_SIZE) - 32)
#define CONFIG_SYS_INIT_SP_OFFSET	(CONFIG_SYS_GBL_DATA_OFFSET - 32)
#define CONFIG_SYS_SBFHDR_DATA_OFFSET	(CONFIG_SYS_INIT_RAM_END - 32)

#define CONFIG_SYS_SDRAM_BASE		0x40000000
#define CONFIG_SYS_SDRAM_SIZE		64	/* SDRAM size in MB */
#define CONFIG_SYS_SDRAM_CFG1		0x43711630
#define CONFIG_SYS_SDRAM_CFG2		0x56670000
#define CONFIG_SYS_SDRAM_CTRL		0xE1092000
#define CONFIG_SYS_SDRAM_EMOD		0x81810000
#define CONFIG_SYS_SDRAM_MODE		0x00CD0000
#define CONFIG_SYS_SDRAM_DRV_STRENGTH	0x00

#define CONFIG_SYS_MEMTEST_START	CONFIG_SYS_SDRAM_BASE + 0x400
#define CONFIG_SYS_MEMTEST_END		((CONFIG_SYS_SDRAM_SIZE - 3) << 20)

#ifdef CONFIG_CF_SBF
#	define CONFIG_SYS_MONITOR_BASE	(TEXT_BASE + 0x400)
#else
#	define CONFIG_SYS_MONITOR_BASE	(CONFIG_SYS_FLASH_BASE + 0x400)
#endif
#define CONFIG_SYS_BOOTPARAMS_LEN	64*1024
#define CONFIG_SYS_MONITOR_LEN		(256 << 10)	/* Reserve 256 kB for Monitor */
#define CONFIG_SYS_MALLOC_LEN		(128 << 10)	/* Reserve 128 kB for malloc() */

/* Initial Memory map for Linux */
#define CONFIG_SYS_BOOTMAPSZ		(CONFIG_SYS_SDRAM_BASE + (CONFIG_SYS_SDRAM_SIZE << 20))
#define CONFIG_SYS_BOOTM_LEN		(CONFIG_SYS_SDRAM_SIZE << 20)

#ifdef CONFIG_CF_SBF
#	define CONFIG_ENV_IS_IN_SPI_FLASH
#	define CONFIG_ENV_SPI_CS	2
#else
#	define CONFIG_ENV_IS_IN_FLASH	1
#endif
#define CONFIG_ENV_OVERWRITE		1

#ifdef CONFIG_SYS_STMICRO_BOOT
#	define CONFIG_SYS_FLASH_BASE	CONFIG_SYS_CS0_BASE
#	define CONFIG_ENV_OFFSET	0x30000
#	define CONFIG_ENV_SIZE		0x1000
#	define CONFIG_ENV_SECT_SIZE	0x10000
#endif
#ifdef CONFIG_SYS_SPANSION_BOOT
#	define CONFIG_SYS_FLASH_BASE	CONFIG_SYS_CS0_BASE
#	define CONFIG_SYS_FLASH0_BASE	CONFIG_SYS_CS0_BASE
#	define CONFIG_ENV_ADDR		(CONFIG_SYS_FLASH_BASE + 0x8000)
#	define CONFIG_ENV_SIZE		0x1000
#	define CONFIG_ENV_SECT_SIZE	0x8000
#endif

#define CONFIG_SYS_FLASH_CFI
#ifdef CONFIG_SYS_FLASH_CFI
#	define CONFIG_FLASH_CFI_DRIVER	1
#	define CONFIG_SYS_FLASH_USE_BUFFER_WRITE	1
#	define CONFIG_FLASH_SPANSION_S29WS_N	1
#	define CONFIG_SYS_FLASH_SIZE		0x1000000	/* Max size that the board might have */
#	define CONFIG_SYS_FLASH_CFI_WIDTH	FLASH_CFI_16BIT
#	define CONFIG_SYS_MAX_FLASH_BANKS	1	/* max number of memory banks */
#	define CONFIG_SYS_MAX_FLASH_SECT	137	/* max number of sectors on one chip */
#	define CONFIG_SYS_FLASH_PROTECTION	/* "Real" (hardware) sectors protection */
#	define CONFIG_SYS_FLASH_CHECKSUM
#	define CONFIG_SYS_FLASH_BANKS_LIST	{ CONFIG_SYS_CS0_BASE }
#endif

#ifdef CONFIG_CMD_JFFS2
#	define CONFIG_JFFS2_DEV		"nor0"
#	define CONFIG_JFFS2_PART_SIZE	(0x01000000 - 0x40000)
#	define CONFIG_JFFS2_PART_OFFSET	(CONFIG_SYS_FLASH0_BASE + 0x40000)
#endif

#define CONFIG_SYS_CACHELINE_SIZE	16

#define ICACHE_STATUS			(CONFIG_SYS_INIT_RAM_ADDR + \
					 CONFIG_SYS_INIT_RAM_END - 8)
#define DCACHE_STATUS			(CONFIG_SYS_INIT_RAM_ADDR + \
					 CONFIG_SYS_INIT_RAM_END - 4)
#define CONFIG_SYS_ICACHE_INV		(CF_CACR_CINV | CF_CACR_INVI)
#define CONFIG_SYS_CACHE_ACR0		(CONFIG_SYS_SDRAM_BASE | \
					 CF_ADDRMASK(CONFIG_SYS_SDRAM_SIZE) | \
					 CF_ACR_EN | CF_ACR_SM_ALL)
#define CONFIG_SYS_CACHE_ICACR		(CF_CACR_CENB | CF_CACR_CINV | \
					 CF_CACR_DISD | CF_CACR_INVI | \
					 CF_CACR_CEIB | CF_CACR_DCM | \
					 CF_CACR_EUSP)


#ifdef CONFIG_CF_SBF
#define CONFIG_SYS_CS0_BASE		0x04000000
#define CONFIG_SYS_CS0_MASK		0x00FF0001
#define CONFIG_SYS_CS0_CTRL		0x00001FA0
#else
#define CONFIG_SYS_CS0_BASE		0x00000000
#define CONFIG_SYS_CS0_MASK		0x00FF0001
#define CONFIG_SYS_CS0_CTRL		0x00001FA0
#endif

#endif				/* _M52277EVB_H */
