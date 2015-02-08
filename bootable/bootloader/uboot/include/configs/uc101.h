

#ifndef __CONFIG_H
#define __CONFIG_H


#define CONFIG_UC101		1	/* UC101 board		*/
#define CONFIG_HOSTNAME		uc101

#include "manroland/common.h"
#include "manroland/mpc5200-common.h"

#define CONFIG_BAUDRATE		115200	/* ... at 115200 bps	*/

#define CONFIG_BOOTP_BOOTFILESIZE
#define CONFIG_BOOTP_BOOTPATH
#define CONFIG_BOOTP_GATEWAY
#define CONFIG_BOOTP_HOSTNAME

#define CONFIG_SYS_MAX_FLASH_SECT	140

#define CONFIG_ENV_SECT_SIZE	0x10000

#define	CONFIG_SYS_IB_MASTER		0xc0510000	/* CS 6 */
#define CONFIG_SYS_IB_EPLD		0xc0500000	/* CS 7 */

/* SRAM */
#define SRAM_BASE		CONFIG_SYS_SRAM_BASE
#define SRAM_LEN		0x1fffff
#define SRAM_END		(SRAM_BASE + SRAM_LEN)

#define CONFIG_SYS_GPS_PORT_CONFIG	0x4d558044

#define CONFIG_SYS_MEMTEST_START	0x00300000
#define CONFIG_SYS_MEMTEST_END		0x00f00000

#define CONFIG_SYS_LOAD_ADDR		0x300000

#define CONFIG_SYS_BOOTCS_CFG		0x00045D00

/* 8Mbit SRAM @0x80100000 */
#define CONFIG_SYS_CS1_SIZE		0x00200000
#define CONFIG_SYS_CS1_CFG		0x21D00

/* Display H1, Status Inputs, EPLD @0x80600000 8 Bit */
#define CONFIG_SYS_CS3_START		CONFIG_SYS_DISPLAY_BASE
#define CONFIG_SYS_CS3_SIZE		0x00000100
#define CONFIG_SYS_CS3_CFG		0x00081802

/* Interbus Master 16 Bit */
#define CONFIG_SYS_CS6_START		CONFIG_SYS_IB_MASTER
#define CONFIG_SYS_CS6_SIZE		0x00010000
#define CONFIG_SYS_CS6_CFG		0x00FF3500

/* Interbus EPLD 8 Bit */
#define CONFIG_SYS_CS7_START		CONFIG_SYS_IB_EPLD
#define CONFIG_SYS_CS7_SIZE		0x00010000
#define CONFIG_SYS_CS7_CFG		0x00081800


#define CONFIG_SYS_IDE_MAXDEVICE	1	/* max. 2 drives per IDE bus*/

/*---------------------------------------------------------------------*/
/* Display addresses						       */
/*---------------------------------------------------------------------*/
#define CONFIG_SYS_DISP_CHR_RAM	(CONFIG_SYS_DISPLAY_BASE + 0x38)
#define CONFIG_SYS_DISP_CWORD		(CONFIG_SYS_DISPLAY_BASE + 0x30)

#endif /* __CONFIG_H */
