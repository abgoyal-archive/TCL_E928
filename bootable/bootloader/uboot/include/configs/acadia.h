


#ifndef __CONFIG_H
#define __CONFIG_H

#define CONFIG_ACADIA		1		/* Board is Acadia	*/
#define CONFIG_4xx		1		/* ... PPC4xx family	*/
#define CONFIG_405EZ		1		/* Specifc 405EZ support*/

#define CONFIG_HOSTNAME		acadia
#include "amcc-common.h"

/* Detect Acadia PLL input clock automatically via CPLD bit		*/
#define CONFIG_SYS_CLK_FREQ    ((in8(CONFIG_SYS_CPLD_BASE + 0) == 0x0c) ? \
				66666666 : 33333000)

#define CONFIG_BOARD_EARLY_INIT_F 1		/* Call board_early_init_f */
#define CONFIG_MISC_INIT_F	1		/* Call misc_init_f	*/

#define CONFIG_NO_SERIAL_EEPROM
/*#undef CONFIG_NO_SERIAL_EEPROM*/

#ifdef CONFIG_NO_SERIAL_EEPROM
/* #define PLLMR0_100_100_12 */
#define PLLMR0_200_133_66
/* #define PLLMR0_266_160_80 */
/* #define PLLMR0_333_166_83 */
#endif

#define CONFIG_SYS_FLASH_BASE		0xfe000000
#define CONFIG_SYS_CPLD_BASE		0x80000000
#define CONFIG_SYS_NAND_ADDR		0xd0000000
#define CONFIG_SYS_USB_HOST		0xef603000	/* USB OHCI 1.1 controller	*/

#define CONFIG_SYS_TEMP_STACK_OCM	1		/* OCM as init ram	*/

/* On Chip Memory location */
#define CONFIG_SYS_OCM_DATA_ADDR	0xf8000000
#define CONFIG_SYS_OCM_DATA_SIZE	0x4000			/* 16K of onchip SRAM		*/
#define CONFIG_SYS_INIT_RAM_ADDR	CONFIG_SYS_OCM_DATA_ADDR	/* inside of SRAM		*/
#define CONFIG_SYS_INIT_RAM_END	CONFIG_SYS_OCM_DATA_SIZE	/* End of used area in RAM	*/

#define CONFIG_SYS_GBL_DATA_SIZE	128			/* size for initial data	*/
#define CONFIG_SYS_GBL_DATA_OFFSET	(CONFIG_SYS_INIT_RAM_END - CONFIG_SYS_GBL_DATA_SIZE)
#define CONFIG_SYS_INIT_SP_OFFSET	CONFIG_SYS_GBL_DATA_OFFSET

#undef	CONFIG_SYS_EXT_SERIAL_CLOCK			/* external serial clock */
#define CONFIG_SYS_BASE_BAUD		691200

#if !defined(CONFIG_NAND_U_BOOT) && !defined(CONFIG_NAND_SPL)
#define CONFIG_ENV_IS_IN_FLASH     1	/* use FLASH for environment vars	*/
#else
#define CONFIG_ENV_IS_IN_NAND	1	/* use NAND for environment vars	*/
#define CONFIG_ENV_IS_EMBEDDED	1	/* use embedded environment */
#endif

#if !defined(CONFIG_NAND_U_BOOT) && !defined(CONFIG_NAND_SPL)
#define CONFIG_SYS_FLASH_CFI			/* The flash is CFI compatible	*/
#define CONFIG_FLASH_CFI_DRIVER		/* Use common CFI driver	*/

#define CONFIG_SYS_FLASH_BANKS_LIST    {CONFIG_SYS_FLASH_BASE}
#define CONFIG_SYS_MAX_FLASH_BANKS	1	/* max number of memory banks		*/
#define CONFIG_SYS_MAX_FLASH_SECT	512	/* max number of sectors on one chip	*/

#define CONFIG_SYS_FLASH_ERASE_TOUT	120000	/* Timeout for Flash Erase (in ms)	*/
#define CONFIG_SYS_FLASH_WRITE_TOUT	500	/* Timeout for Flash Write (in ms)	*/

#define CONFIG_SYS_FLASH_USE_BUFFER_WRITE 1	/* use buffered writes (20x faster)	*/
#define CONFIG_SYS_FLASH_EMPTY_INFO		/* print 'E' for empty sector on flinfo */

#else
#define	CONFIG_SYS_NO_FLASH		1	/* No NOR on Acadia when NAND-booting	*/
#endif

#ifdef CONFIG_ENV_IS_IN_FLASH
#define CONFIG_ENV_SECT_SIZE	0x40000 /* size of one complete sector	*/
#define CONFIG_ENV_ADDR		(CONFIG_SYS_MONITOR_BASE-CONFIG_ENV_SECT_SIZE)
#define	CONFIG_ENV_SIZE		0x4000	/* Total Size of Environment Sector	*/

/* Address and size of Redundant Environment Sector	*/
#define CONFIG_ENV_ADDR_REDUND	(CONFIG_ENV_ADDR-CONFIG_ENV_SECT_SIZE)
#define CONFIG_ENV_SIZE_REDUND	(CONFIG_ENV_SIZE)
#endif

#define CONFIG_SYS_NAND_BOOT_SPL_SRC	0xfffff000	/* SPL location			*/
#define CONFIG_SYS_NAND_BOOT_SPL_SIZE	(4 << 10)	/* SPL size			*/
#define CONFIG_SYS_NAND_BOOT_SPL_DST	(CONFIG_SYS_OCM_DATA_ADDR + (16 << 10)) /* Copy SPL here*/
#define CONFIG_SYS_NAND_U_BOOT_DST	0x01000000	/* Load NUB to this addr	*/
#define CONFIG_SYS_NAND_U_BOOT_START	CONFIG_SYS_NAND_U_BOOT_DST /* Start NUB from this addr	*/
#define CONFIG_SYS_NAND_BOOT_SPL_DELTA	(CONFIG_SYS_NAND_BOOT_SPL_SRC - CONFIG_SYS_NAND_BOOT_SPL_DST)

#define CONFIG_SYS_NAND_U_BOOT_OFFS	(16 << 10)	/* Offset to RAM U-Boot image	*/
#define CONFIG_SYS_NAND_U_BOOT_SIZE	(384 << 10)	/* Size of RAM U-Boot image	*/

#define CONFIG_SYS_NAND_PAGE_SIZE	512		/* NAND chip page size		*/
#define CONFIG_SYS_NAND_BLOCK_SIZE	(16 << 10)	/* NAND chip block size		*/
#define CONFIG_SYS_NAND_PAGE_COUNT	32		/* NAND chip page count		*/
#define CONFIG_SYS_NAND_BAD_BLOCK_POS	5		/* Location of bad block marker	*/
#undef CONFIG_SYS_NAND_4_ADDR_CYCLE			/* No fourth addr used (<=32MB)	*/

#define CONFIG_SYS_NAND_ECCSIZE	256
#define CONFIG_SYS_NAND_ECCBYTES	3
#define CONFIG_SYS_NAND_ECCSTEPS	(CONFIG_SYS_NAND_PAGE_SIZE / CONFIG_SYS_NAND_ECCSIZE)
#define CONFIG_SYS_NAND_OOBSIZE	16
#define CONFIG_SYS_NAND_ECCTOTAL	(CONFIG_SYS_NAND_ECCBYTES * CONFIG_SYS_NAND_ECCSTEPS)
#define CONFIG_SYS_NAND_ECCPOS		{0, 1, 2, 3, 6, 7}

#ifdef CONFIG_ENV_IS_IN_NAND
#define CONFIG_ENV_SIZE		CONFIG_SYS_NAND_BLOCK_SIZE
#define CONFIG_ENV_OFFSET		(CONFIG_SYS_NAND_U_BOOT_OFFS + CONFIG_ENV_SIZE)
#define CONFIG_ENV_OFFSET_REDUND	(CONFIG_ENV_OFFSET + CONFIG_ENV_SIZE)
#endif

#define CONFIG_SYS_MBYTES_RAM		64		/* 64MB			*/

#define CONFIG_SYS_I2C_SPEED		400000		/* I2C speed and slave address	*/

#define CONFIG_SYS_I2C_MULTI_EEPROMS
#define CONFIG_SYS_I2C_EEPROM_ADDR	(0xa8>>1)
#define CONFIG_SYS_I2C_EEPROM_ADDR_LEN 1
#define CONFIG_SYS_EEPROM_PAGE_WRITE_BITS 3
#define CONFIG_SYS_EEPROM_PAGE_WRITE_DELAY_MS 10

/* I2C SYSMON (LM75, AD7414 is almost compatible)			*/
#define CONFIG_DTT_LM75		1		/* ON Semi's LM75	*/
#define CONFIG_DTT_AD7414	1		/* use AD7414		*/
#define CONFIG_DTT_SENSORS	{0}		/* Sensor addresses	*/
#define CONFIG_SYS_DTT_MAX_TEMP	70
#define CONFIG_SYS_DTT_LOW_TEMP	-30
#define CONFIG_SYS_DTT_HYSTERESIS	3

#define	CONFIG_PHY_ADDR		0	/* PHY address			*/
#define CONFIG_HAS_ETH0		1

#define	CONFIG_EXTRA_ENV_SETTINGS					\
	CONFIG_AMCC_DEF_ENV						\
	CONFIG_AMCC_DEF_ENV_POWERPC					\
	CONFIG_AMCC_DEF_ENV_PPC_OLD					\
	CONFIG_AMCC_DEF_ENV_NOR_UPD					\
	CONFIG_AMCC_DEF_ENV_NAND_UPD					\
	"kernel_addr=fff10000\0"					\
	"ramdisk_addr=fff20000\0"					\
	"kozio=bootm ffc60000\0"					\
	""

#define CONFIG_USB_OHCI
#define CONFIG_USB_STORAGE

/* Partitions */
#define CONFIG_MAC_PARTITION
#define CONFIG_DOS_PARTITION
#define CONFIG_ISO_PARTITION

#define CONFIG_SUPPORT_VFAT

#define CONFIG_CMD_DTT
#define CONFIG_CMD_NAND
#define CONFIG_CMD_USB

#if defined(CONFIG_NAND_U_BOOT) || defined(CONFIG_NAND_SPL)
#undef CONFIG_CMD_FLASH
#undef CONFIG_CMD_IMLS
#endif

#define CONFIG_SYS_MAX_NAND_DEVICE	1
#define CONFIG_SYS_NAND_BASE		(CONFIG_SYS_NAND_ADDR + CONFIG_SYS_NAND_CS)
#define CONFIG_SYS_NAND_SELECT_DEVICE  1	/* nand driver supports mutipl. chips	*/

#if !defined(CONFIG_NAND_U_BOOT) && !defined(CONFIG_NAND_SPL)
#define CONFIG_SYS_NAND_CS		3
/* Memory Bank 0 (Flash) initialization						*/
#define CONFIG_SYS_EBC_PB0AP		0x03337200
#define CONFIG_SYS_EBC_PB0CR		0xfe0bc000

/* Memory Bank 3 (NAND-FLASH) initialization					*/
#define CONFIG_SYS_EBC_PB3AP		0x018003c0
#define CONFIG_SYS_EBC_PB3CR		(CONFIG_SYS_NAND_ADDR | 0x1c000)

/* Just initial configuration for CRAM. Will be changed in memory.c to sync mode*/
/* Memory Bank 1 (CRAM) initialization						*/
#define CONFIG_SYS_EBC_PB1AP		0x030400c0
#define CONFIG_SYS_EBC_PB1CR		0x000bc000

/* Memory Bank 2 (CRAM) initialization						*/
#define CONFIG_SYS_EBC_PB2AP		0x030400c0
#define CONFIG_SYS_EBC_PB2CR		0x020bc000
#else
#define CONFIG_SYS_NAND_CS		0		/* NAND chip connected to CSx	*/
/* Memory Bank 0 (NAND-FLASH) initialization					*/
#define CONFIG_SYS_EBC_PB0AP		0x018003c0
#define CONFIG_SYS_EBC_PB0CR		(CONFIG_SYS_NAND_ADDR | 0x1c000)

/* Memory Bank 1 (CRAM) initialization						*/
#define CONFIG_SYS_EBC_PB1AP		0x9C0201C0
#define CONFIG_SYS_EBC_PB1CR		0x000bc000

/* Memory Bank 2 (CRAM) initialization						*/
#define CONFIG_SYS_EBC_PB2AP		0x9C0201C0
#define CONFIG_SYS_EBC_PB2CR		0x020bc000
#endif

/* Memory Bank 4 (CPLD) initialization						*/
#define CONFIG_SYS_EBC_PB4AP		0x04006000
#define CONFIG_SYS_EBC_PB4CR		(CONFIG_SYS_CPLD_BASE | 0x18000)

#define CONFIG_SYS_EBC_CFG		0xf8400000

#define CONFIG_SYS_GPIO_CRAM_CLK	8
#define CONFIG_SYS_GPIO_CRAM_WAIT	9		/* GPIO-In		*/
#define CONFIG_SYS_GPIO_CRAM_ADV	10
#define CONFIG_SYS_GPIO_CRAM_CRE	(32 + 21)	/* GPIO-Out		*/

#define CONFIG_SYS_GPIO0_TCR		0xC0A00000
#define CONFIG_SYS_GPIO0_OSRL		0x50004400
#define CONFIG_SYS_GPIO0_OSRH		0x02000055
#define CONFIG_SYS_GPIO0_ISR1L		0x00001000
#define CONFIG_SYS_GPIO0_ISR1H		0x00000055
#define CONFIG_SYS_GPIO0_TSRL		0x02000000
#define CONFIG_SYS_GPIO0_TSRH		0x00000055

#define CONFIG_SYS_GPIO1_TCR		0xFFFF8414
#define CONFIG_SYS_GPIO1_OSRL		0x40000110
#define CONFIG_SYS_GPIO1_OSRH		0x55455555
#define CONFIG_SYS_GPIO1_ISR1L		0x15555445
#define CONFIG_SYS_GPIO1_ISR1H		0x00000000
#define CONFIG_SYS_GPIO1_TSRL		0x00000000
#define CONFIG_SYS_GPIO1_TSRH		0x00000000

#endif	/* __CONFIG_H */
