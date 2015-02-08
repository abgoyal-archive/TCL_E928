

#ifndef __CONFIG_IP04_H__
#define __CONFIG_IP04_H__

#include <asm/config-pre.h>


#define CONFIG_BFIN_CPU             bf532-0.5
#define CONFIG_BFIN_BOOT_MODE       BFIN_BOOT_NAND


/* CONFIG_CLKIN_HZ is any value in Hz					*/
#define CONFIG_CLKIN_HZ			10000000
/* CLKIN_HALF controls the DF bit in PLL_CTL      0 = CLKIN		*/
/*                                                1 = CLKIN / 2		*/
#define CONFIG_CLKIN_HALF		0
/* PLL_BYPASS controls the BYPASS bit in PLL_CTL  0 = do not bypass	*/
/*                                                1 = bypass PLL	*/
#define CONFIG_PLL_BYPASS		0
/* VCO_MULT controls the MSEL (multiplier) bits in PLL_CTL		*/
/* Values can range from 0-63 (where 0 means 64)			*/
#define CONFIG_VCO_MULT			40
/* CCLK_DIV controls the core clock divider				*/
/* Values can be 1, 2, 4, or 8 ONLY					*/
#define CONFIG_CCLK_DIV			1
/* SCLK_DIV controls the system clock divider				*/
/* Values can range from 1-15						*/
#define CONFIG_SCLK_DIV			3


#define CONFIG_MEM_ADD_WDTH	10
#define CONFIG_MEM_SIZE		64

#define CONFIG_EBIU_SDRRC_VAL	0x408
#define CONFIG_EBIU_SDGCTL_VAL	0x9111cd

#define CONFIG_EBIU_AMGCTL_VAL	0xFF
#define CONFIG_EBIU_AMBCTL0_VAL	0xffc2ffc2
#define CONFIG_EBIU_AMBCTL1_VAL	0xffc2ffc2

#define CONFIG_SYS_MONITOR_LEN		(256 * 1024)
#define CONFIG_SYS_MALLOC_LEN		(128 * 1024)


#define ADI_CMDS_NETWORK	1
#define CONFIG_NET_MULTI	1
#define CONFIG_HOSTNAME		IP04

#define CONFIG_DRIVER_DM9000	1
#define CONFIG_DM9000_NO_SROM
#define CONFIG_DM9000_BASE	0x20100000
#define DM9000_IO		CONFIG_DM9000_BASE
#define DM9000_DATA		(CONFIG_DM9000_BASE + 2)


#define CONFIG_ENV_OVERWRITE	1
#define CONFIG_SYS_NO_FLASH		/* we have only NAND */


#define CONFIG_BFIN_SPI
#define CONFIG_ENV_SPI_MAX_HZ	30000000
#define CONFIG_SF_DEFAULT_SPEED	30000000
#define CONFIG_SPI_FLASH
#define CONFIG_SPI_FLASH_STMICRO
#define CONFIG_SPI_FLASH_WINBOND


#define CONFIG_ENV_IS_IN_SPI_FLASH
#define CONFIG_PREBOOT		"echo starting from spi flash"
#define CONFIG_ENV_OFFSET	0x30000
#define CONFIG_ENV_SIZE		0x10000
#define CONFIG_ENV_SECT_SIZE	0x10000


#define CONFIG_NAND_PLAT
#define CONFIG_SYS_NAND_BASE		0x20000000
#define CONFIG_SYS_MAX_NAND_DEVICE	1

#define BFIN_NAND_CLE(chip) ((unsigned long)(chip)->IO_ADDR_W | (1 << 2))
#define BFIN_NAND_ALE(chip) ((unsigned long)(chip)->IO_ADDR_W | (1 << 1))
#define BFIN_NAND_READY     PF10
#define BFIN_NAND_WRITE(addr, cmd) \
	do { \
		bfin_write8(addr, cmd); \
		SSYNC(); \
	} while (0)

#define NAND_PLAT_WRITE_CMD(chip, cmd) BFIN_NAND_WRITE(BFIN_NAND_CLE(chip), cmd)
#define NAND_PLAT_WRITE_ADR(chip, cmd) BFIN_NAND_WRITE(BFIN_NAND_ALE(chip), cmd)
#define NAND_PLAT_DEV_READY(chip)      (bfin_read_FIO_FLAG_D() & BFIN_NAND_READY)
#define NAND_PLAT_INIT() \
	do { \
		bfin_write_FIO_DIR(bfin_read_FIO_DIR() & ~BFIN_NAND_READY); \
		bfin_write_FIO_INEN(bfin_read_FIO_INEN() | BFIN_NAND_READY); \
		bfin_write_FIO_EDGE(bfin_read_FIO_EDGE() & ~BFIN_NAND_READY); \
		bfin_write_FIO_POLAR(bfin_read_FIO_POLAR() & ~BFIN_NAND_READY); \
	} while (0)


#define CONFIG_BAUDRATE		115200
#define CONFIG_MISC_INIT_R	/* needed for MAC address */
#define CONFIG_UART_CONSOLE	0

#undef CONFIG_SHOW_BOOT_PROGRESS
/* Enable this if bootretry required; currently it's disabled */
#define CONFIG_BOOT_RETRY_TIME	-1
#define CONFIG_BOOTCOMMAND	"run nandboot"
#define CONFIG_AUTOBOOT_PROMPT	"autoboot in %d seconds\n"


#include <configs/bfin_adi_common.h>

#endif
