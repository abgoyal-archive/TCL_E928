

#ifndef __CONFIG_BF537_STAMP_H__
#define __CONFIG_BF537_STAMP_H__

#include <asm/config-pre.h>


#define CONFIG_BFIN_CPU             bf537-0.2
#define CONFIG_BFIN_BOOT_MODE       BFIN_BOOT_BYPASS


/* CONFIG_CLKIN_HZ is any value in Hz					*/
#define CONFIG_CLKIN_HZ			25000000
/* CLKIN_HALF controls the DF bit in PLL_CTL      0 = CLKIN		*/
/*                                                1 = CLKIN / 2		*/
#define CONFIG_CLKIN_HALF		0
/* PLL_BYPASS controls the BYPASS bit in PLL_CTL  0 = do not bypass	*/
/*                                                1 = bypass PLL	*/
#define CONFIG_PLL_BYPASS		0
/* VCO_MULT controls the MSEL (multiplier) bits in PLL_CTL		*/
/* Values can range from 0-63 (where 0 means 64)			*/
#define CONFIG_VCO_MULT			20
/* CCLK_DIV controls the core clock divider				*/
/* Values can be 1, 2, 4, or 8 ONLY					*/
#define CONFIG_CCLK_DIV			1
/* SCLK_DIV controls the system clock divider				*/
/* Values can range from 1-15						*/
#define CONFIG_SCLK_DIV			4


#define CONFIG_MEM_ADD_WDTH	10
#define CONFIG_MEM_SIZE		64

#define CONFIG_EBIU_SDRRC_VAL	0x306
#define CONFIG_EBIU_SDGCTL_VAL	0x91114d

#define CONFIG_EBIU_AMGCTL_VAL	0xFF
#define CONFIG_EBIU_AMBCTL0_VAL	0x7BB07BB0
#define CONFIG_EBIU_AMBCTL1_VAL	0xFFC27BB0

#define CONFIG_SYS_MONITOR_LEN		(512 * 1024)
#define CONFIG_SYS_MALLOC_LEN		(384 * 1024)


#ifndef __ADSPBF534__
#define ADI_CMDS_NETWORK	1
#define CONFIG_BFIN_MAC
#define CONFIG_NETCONSOLE	1
#define CONFIG_NET_MULTI	1
#endif
#define CONFIG_HOSTNAME		bf537-stamp
/* Uncomment next line to use fixed MAC address */
/* #define CONFIG_ETHADDR	02:80:ad:20:31:e8 */


#define CONFIG_FLASH_CFI_DRIVER
#define CONFIG_SYS_FLASH_BASE		0x20000000
#define CONFIG_SYS_FLASH_CFI
#define CONFIG_SYS_FLASH_PROTECTION
#define CONFIG_SYS_MAX_FLASH_BANKS	1
/* some have 67 sectors (M29W320DB), but newer have 71 (M29W320EB) */
#define CONFIG_SYS_MAX_FLASH_SECT	71


#define CONFIG_BFIN_SPI
#define CONFIG_ENV_SPI_MAX_HZ	30000000
#define CONFIG_SF_DEFAULT_SPEED	30000000
#define CONFIG_SPI_FLASH
#define CONFIG_SPI_FLASH_ATMEL
#define CONFIG_SPI_FLASH_SPANSION
#define CONFIG_SPI_FLASH_STMICRO
#define CONFIG_SPI_FLASH_WINBOND


#if (CONFIG_BFIN_BOOT_MODE == BFIN_BOOT_SPI_MASTER)
#define CONFIG_ENV_IS_IN_SPI_FLASH
#define CONFIG_ENV_OFFSET	0x10000
#define CONFIG_ENV_SIZE		0x2000
#define CONFIG_ENV_SECT_SIZE	0x10000
#else
#define CONFIG_ENV_IS_IN_FLASH
#define CONFIG_ENV_OFFSET	0x4000
#define CONFIG_ENV_ADDR		(CONFIG_SYS_FLASH_BASE + CONFIG_ENV_OFFSET)
#define CONFIG_ENV_SIZE		0x2000
#define CONFIG_ENV_SECT_SIZE	0x2000
#endif
#if (CONFIG_BFIN_BOOT_MODE == BFIN_BOOT_BYPASS)
#define ENV_IS_EMBEDDED
#else
#define CONFIG_ENV_IS_EMBEDDED_IN_LDR
#endif
#ifdef ENV_IS_EMBEDDED
# define LDS_BOARD_TEXT \
	arch/blackfin/cpu/traps.o		(.text .text.*); \
	arch/blackfin/cpu/interrupt.o	(.text .text.*); \
	arch/blackfin/cpu/serial.o		(.text .text.*); \
	common/dlmalloc.o		(.text .text.*); \
	lib/crc32.o		(.text .text.*); \
	. = DEFINED(env_offset) ? env_offset : .; \
	common/env_embedded.o		(.text .text.*);
#endif


#define CONFIG_BFIN_TWI_I2C	1
#define CONFIG_HARD_I2C		1
#define CONFIG_SYS_I2C_SPEED	50000
#define CONFIG_SYS_I2C_SLAVE	0


#define CONFIG_MMC
#define CONFIG_SPI_MMC


/* #define CONFIG_NAND_PLAT */
#define CONFIG_SYS_NAND_BASE		0x20212000
#define CONFIG_SYS_MAX_NAND_DEVICE	1

#define BFIN_NAND_CLE(chip) ((unsigned long)(chip)->IO_ADDR_W | (1 << 2))
#define BFIN_NAND_ALE(chip) ((unsigned long)(chip)->IO_ADDR_W | (1 << 1))
#define BFIN_NAND_READY     PF3
#define BFIN_NAND_WRITE(addr, cmd) \
	do { \
		bfin_write8(addr, cmd); \
		SSYNC(); \
	} while (0)

#define NAND_PLAT_WRITE_CMD(chip, cmd) BFIN_NAND_WRITE(BFIN_NAND_CLE(chip), cmd)
#define NAND_PLAT_WRITE_ADR(chip, cmd) BFIN_NAND_WRITE(BFIN_NAND_ALE(chip), cmd)
#define NAND_PLAT_DEV_READY(chip)      (bfin_read_PORTFIO() & BFIN_NAND_READY)
#define NAND_PLAT_INIT() \
	do { \
		bfin_write_PORTF_FER(bfin_read_PORTF_FER() & ~BFIN_NAND_READY); \
		bfin_write_PORTFIO_DIR(bfin_read_PORTFIO_DIR() & ~BFIN_NAND_READY); \
		bfin_write_PORTFIO_INEN(bfin_read_PORTFIO_INEN() | BFIN_NAND_READY); \
	} while (0)




/* #define CONFIG_BFIN_TRUE_IDE */


/* #define CONFIG_BFIN_CF_IDE */


/* #define CONFIG_BFIN_HDD_IDE */

#if defined(CONFIG_BFIN_CF_IDE) || \
    defined(CONFIG_BFIN_HDD_IDE) || \
    defined(CONFIG_BFIN_TRUE_IDE)
# define CONFIG_BFIN_IDE	1
# define CONFIG_CMD_IDE
#endif

#if defined(CONFIG_BFIN_IDE)

#define CONFIG_DOS_PARTITION	1
#undef  CONFIG_IDE_8xx_DIRECT	/* no pcmcia interface required */
#undef  CONFIG_IDE_LED		/* no led for ide supported */
#undef  CONFIG_IDE_RESET	/* no reset for ide supported */

#define CONFIG_SYS_IDE_MAXBUS		1
#define CONFIG_SYS_IDE_MAXDEVICE	(CONFIG_SYS_IDE_MAXBUS * 1)

#undef  CONFIG_EBIU_AMBCTL1_VAL
#define CONFIG_EBIU_AMBCTL1_VAL		0xFFC3FFC3

#define CONFIG_CF_ATASEL_DIS	0x20311800
#define CONFIG_CF_ATASEL_ENA	0x20311802

#if defined(CONFIG_BFIN_TRUE_IDE)
#define CONFIG_SYS_ATA_BASE_ADDR	0x2031C000
#define CONFIG_SYS_ATA_IDE0_OFFSET	0x0000
#define CONFIG_SYS_ATA_DATA_OFFSET	0x0020	/* data I/O */
#define CONFIG_SYS_ATA_REG_OFFSET	0x0020	/* normal register accesses */
#define CONFIG_SYS_ATA_ALT_OFFSET	0x001C	/* alternate registers */
#define CONFIG_SYS_ATA_STRIDE		2	/* CF.A0 --> Blackfin.A13 */

#elif defined(CONFIG_BFIN_CF_IDE)
#define CONFIG_SYS_ATA_BASE_ADDR	0x20211800
#define CONFIG_SYS_ATA_IDE0_OFFSET	0x0000
#define CONFIG_SYS_ATA_DATA_OFFSET	0x0000	/* data I/O */
#define CONFIG_SYS_ATA_REG_OFFSET	0x0000	/* normal register accesses */
#define CONFIG_SYS_ATA_ALT_OFFSET	0x000E	/* alternate registers */
#define CONFIG_SYS_ATA_STRIDE		1	/* CF_A0=0, with /CE1 /CE2 odd/even byte selects */

#elif defined(CONFIG_BFIN_HDD_IDE)
#define CONFIG_SYS_ATA_BASE_ADDR	0x20314000
#define CONFIG_SYS_ATA_IDE0_OFFSET	0x0000
#define CONFIG_SYS_ATA_DATA_OFFSET	0x0020	/* data I/O */
#define CONFIG_SYS_ATA_REG_OFFSET	0x0020	/* normal register accesses */
#define CONFIG_SYS_ATA_ALT_OFFSET	0x001C	/* alternate registers */
#define CONFIG_SYS_ATA_STRIDE		2	/* CF.A0 --> Blackfin.A1 */
#undef  CONFIG_SCLK_DIV
#define CONFIG_SCLK_DIV		8
#endif

#endif


#define CONFIG_MISC_INIT_R
#define CONFIG_RTC_BFIN
#define CONFIG_UART_CONSOLE	0

/* #define CONFIG_BF537_STAMP_LEDCMD	1 */

/* Define if want to do post memory test */
#undef CONFIG_POST
#ifdef CONFIG_POST
#define FLASH_START_POST_BLOCK	11	/* Should > = 11 */
#define FLASH_END_POST_BLOCK	71	/* Should < = 71 */
#endif

/* These are for board tests */
#if 0
#define CONFIG_BOOTCOMMAND       "bootldr 0x203f0100"
#define CONFIG_AUTOBOOT_KEYED
#define CONFIG_AUTOBOOT_PROMPT \
	"autoboot in %d seconds: press space to stop\n", bootdelay
#define CONFIG_AUTOBOOT_STOP_STR " "
#endif


#include <configs/bfin_adi_common.h>

#endif
