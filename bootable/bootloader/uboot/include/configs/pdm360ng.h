


#ifndef __CONFIG_H
#define __CONFIG_H

#define CONFIG_PDM360NG 1


#define CONFIG_E300		1	/* E300 Family */
#define CONFIG_MPC512X		1	/* MPC512X family */
#define CONFIG_FSL_DIU_FB	1	/* FSL DIU */

/* Used for silent command in environment */
#define CONFIG_SYS_DEVICE_NULLDEV
#define CONFIG_SILENT_CONSOLE

/* Video */
#define CONFIG_VIDEO

#if defined(CONFIG_VIDEO)
#define CONFIG_CFB_CONSOLE
#define CONFIG_VGA_AS_SINGLE_DEVICE
#define CONFIG_SPLASH_SCREEN
#define CONFIG_VIDEO_LOGO
#define CONFIG_VIDEO_BMP_RLE8
#define CONFIG_VIDEO_XRES	800
#define CONFIG_VIDEO_YRES	480
#endif

#define CONFIG_SYS_MPC512X_CLKIN	33333333	/* in Hz */

#define CONFIG_BOARD_EARLY_INIT_F	/* call board_early_init_f() */
#define CONFIG_MISC_INIT_R

#define CONFIG_SYS_IMMR			0x80000000
#define CONFIG_SYS_DIU_ADDR		((CONFIG_SYS_IMMR) + 0x2100)


/* DDR is system memory */
#define CONFIG_SYS_DDR_BASE		0x00000000
#define CONFIG_SYS_SDRAM_BASE		CONFIG_SYS_DDR_BASE
#define CONFIG_SYS_MAX_RAM_SIZE		0x40000000

/* DDR pin mux and slew rate */
#define CONFIG_SYS_IOCTRL_MUX_DDR	0x00000012

/* Manually set all parameters as there's no SPD etc. */
#define CONFIG_SYS_MDDRC_SYS_CFG	0xEA804A40
#define CONFIG_SYS_MDDRC_TIME_CFG0	0x030C3D2E
#define CONFIG_SYS_MDDRC_TIME_CFG1	0x68EC1168
#define CONFIG_SYS_MDDRC_TIME_CFG2	0x34310864

#define CONFIG_SYS_MDDRC_SYS_CFG_ALT1	0xE8604A40
#define CONFIG_SYS_MDDRC_TIME_CFG0_ALT1	0x030C3D2E
#define CONFIG_SYS_MDDRC_TIME_CFG1_ALT1	0x3CEC1168
#define CONFIG_SYS_MDDRC_TIME_CFG2_ALT1	0x33310863

#define CONFIG_SYS_MDDRC_SYS_CFG_EN	0xF0000000

#define CONFIG_SYS_DDRCMD_NOP		0x01380000
#define CONFIG_SYS_DDRCMD_PCHG_ALL	0x01100400
#define CONFIG_SYS_DDRCMD_EM2		0x01020000  /* EMR2 */
#define CONFIG_SYS_DDRCMD_EM3		0x01030000  /* EMR3 */
/* EMR with 150 ohm ODT todo: verify */
#define CONFIG_SYS_DDRCMD_EN_DLL	0x01010040
#define CONFIG_SYS_DDRCMD_RES_DLL	0x01000100
#define CONFIG_SYS_DDRCMD_RFSH		0x01080000
#define CONFIG_SYS_MICRON_INIT_DEV_OP	0x01000432
/* EMR with 150 ohm ODT todo: verify */
#define CONFIG_SYS_DDRCMD_OCD_DEFAULT	0x010107C0
/* EMR new command with 150 ohm ODT todo: verify */
#define CONFIG_SYS_DDRCMD_OCD_EXIT	0x01010440

/* DDR Priority Manager Configuration */
#define CONFIG_SYS_MDDRCGRP_PM_CFG1	0x00077777
#define CONFIG_SYS_MDDRCGRP_PM_CFG2	0x00000000
#define CONFIG_SYS_MDDRCGRP_HIPRIO_CFG	0x00000001
#define CONFIG_SYS_MDDRCGRP_LUT0_MU	0xFFEEDDCC
#define CONFIG_SYS_MDDRCGRP_LUT0_ML	0xBBAAAAAA
#define CONFIG_SYS_MDDRCGRP_LUT1_MU	0x66666666
#define CONFIG_SYS_MDDRCGRP_LUT1_ML	0x55555555
#define CONFIG_SYS_MDDRCGRP_LUT2_MU	0x44444444
#define CONFIG_SYS_MDDRCGRP_LUT2_ML	0x44444444
#define CONFIG_SYS_MDDRCGRP_LUT3_MU	0x55555555
#define CONFIG_SYS_MDDRCGRP_LUT3_ML	0x55555558
#define CONFIG_SYS_MDDRCGRP_LUT4_MU	0x11111111
#define CONFIG_SYS_MDDRCGRP_LUT4_ML	0x11111122
#define CONFIG_SYS_MDDRCGRP_LUT0_AU	0xaaaaaaaa
#define CONFIG_SYS_MDDRCGRP_LUT0_AL	0xaaaaaaaa
#define CONFIG_SYS_MDDRCGRP_LUT1_AU	0x66666666
#define CONFIG_SYS_MDDRCGRP_LUT1_AL	0x66666666
#define CONFIG_SYS_MDDRCGRP_LUT2_AU	0x11111111
#define CONFIG_SYS_MDDRCGRP_LUT2_AL	0x11111111
#define CONFIG_SYS_MDDRCGRP_LUT3_AU	0x11111111
#define CONFIG_SYS_MDDRCGRP_LUT3_AL	0x11111111
#define CONFIG_SYS_MDDRCGRP_LUT4_AU	0x11111111
#define CONFIG_SYS_MDDRCGRP_LUT4_AL	0x11111111

#define CONFIG_SYS_FLASH_CFI		/* use Common Flash Interface */
#define CONFIG_FLASH_CFI_DRIVER		/* use the CFI driver */
#define CONFIG_SYS_FLASH_USE_BUFFER_WRITE

#define CONFIG_SYS_FLASH_BASE		0xF0000000 /* start of FLASH-Bank0 */
#define CONFIG_SYS_FLASH_SIZE		0x08000000 /* max size of a Bank */
/* start of FLASH-Bank1 */
#define CONFIG_SYS_FLASH1_BASE		(CONFIG_SYS_FLASH_BASE + \
					 CONFIG_SYS_FLASH_SIZE)
#define CONFIG_SYS_MAX_FLASH_SECT	512	/* max sectors per device */
#define CONFIG_SYS_MAX_FLASH_BANKS	2	/* number of banks */
#define CONFIG_SYS_FLASH_BANKS_LIST \
	{CONFIG_SYS_FLASH_BASE, CONFIG_SYS_FLASH1_BASE}

#define CONFIG_SYS_SRAM_BASE		0x50000000
#define CONFIG_SYS_SRAM_SIZE		0x00020000	/* 128 KB */

/* ALE active low, data size 4 bytes */
#define CONFIG_SYS_CS0_CFG		0x05059350
/* ALE active low, data size 4 bytes */
#define CONFIG_SYS_CS1_CFG		0x05059350

#define CONFIG_SYS_MRAM_BASE		0x50040000
#define CONFIG_SYS_MRAM_SIZE		0x00020000
/* ALE active low, data size 4 bytes */
#define CONFIG_SYS_CS2_CFG		0x05059110

/* alt. CS timing for CS0, CS1, CS2 */
#define CONFIG_SYS_CS_ALETIMING		0x00000007

#define CONFIG_CMD_NAND			/* enable NAND support */
#define CONFIG_NAND_MPC5121_NFC
#define CONFIG_SYS_NAND_BASE            0x40000000

#define CONFIG_SYS_MAX_NAND_DEVICE      1
#define NAND_MAX_CHIPS                  CONFIG_SYS_MAX_NAND_DEVICE
#define CONFIG_SYS_NAND_SELECT_DEVICE	/* driver supports mutipl. chips */

#define CONFIG_FSL_NFC_WIDTH 1
#define CONFIG_FSL_NFC_WRITE_SIZE 2048
#define CONFIG_FSL_NFC_SPARE_SIZE 64
#define CONFIG_FSL_NFC_CHIPS CONFIG_SYS_MAX_NAND_DEVICE

#define CONFIG_CMD_MTDPARTS
#define CONFIG_MTD_DEVICE	/* needed for mtdparts commands */
#define CONFIG_FLASH_CFI_MTD
#define MTDIDS_DEFAULT		"nor0=f0000000.flash,nor1=f8000000.flash," \
						"nand0=MPC5121 NAND"

#define MTDPARTS_DEFAULT	"mtdparts=f0000000.flash:512k(u-boot),"	\
						"256k(environment1),"	\
						"256k(environment2),"	\
						"256k(splash-factory)," \
						"2m(FIT: recovery),"	\
						"4608k(fs-recovery),"   \
						"256k(splash-customer),"\
						"5m(FIT: kernel+dtb),"	\
						"64m(rootfs squash)ro,"	\
						"51m(userfs ubi);"	\
					"f8000000.flash:-(unused);"	\
					"MPC5121 NAND:1024m(extended-userfs)"

#ifdef CONFIG_CMD_MTDPARTS
#define CONFIG_FDT_FIXUP_PARTITIONS
#endif

#define CONFIG_SYS_MONITOR_BASE		TEXT_BASE	/* Start of monitor */
#define CONFIG_SYS_MONITOR_LEN		(512 * 1024)	/* 512 kB for monitor */
#ifdef	CONFIG_FSL_DIU_FB
#define CONFIG_SYS_MALLOC_LEN		(6 * 1024 * 1024) /* for malloc */
#else
#define CONFIG_SYS_MALLOC_LEN		(512 * 1024)
#endif

#define CONFIG_CONS_INDEX     1

#define CONFIG_PSC_CONSOLE	6	/* console is on PSC6 */
#if CONFIG_PSC_CONSOLE != 6
#error CONFIG_PSC_CONSOLE must be 6
#endif

#define CONSOLE_FIFO_TX_SIZE	FIFOC_PSC6_TX_SIZE
#define CONSOLE_FIFO_TX_ADDR	FIFOC_PSC6_TX_ADDR
#define CONSOLE_FIFO_RX_SIZE	FIFOC_PSC6_RX_SIZE
#define CONSOLE_FIFO_RX_ADDR	FIFOC_PSC6_RX_ADDR

#define CONFIG_SERIAL_MULTI
#define CONFIG_SYS_PSC1
#define CONFIG_SYS_PSC4
#define CONFIG_SYS_PSC6

#define CONFIG_SYS_PDM360NG_COPROC_READ_DELAY	5000
#define CONFIG_SYS_PDM360NG_COPROC_BAUDRATE	38400

#define CONFIG_HARD_I2C			/* I2C with hardware support */
#define CONFIG_I2C_MULTI_BUS
#define CONFIG_I2C_CMD_TREE
/* I2C speed and slave address */
#define CONFIG_SYS_I2C_SPEED		100000
#define CONFIG_SYS_I2C_SLAVE		0x7F

#define CONFIG_SYS_I2C_EEPROM_ADDR_LEN		2	/* 16-bit EEPROM addr */
#define CONFIG_SYS_I2C_EEPROM_ADDR		0x50	/* ST AT24C01 */
#define CONFIG_SYS_EEPROM_PAGE_WRITE_DELAY_MS	10	/* 10ms of delay */
#define CONFIG_SYS_EEPROM_PAGE_WRITE_BITS	4	/* 16-Byte Write Mode */

#define CONFIG_SYS_I2C_EEPROM_BUS_NUM		0
#define CONFIG_SYS_I2C_EEPROM_MAC_OFFSET	0x10
#define CONFIG_ENV_OVERWRITE

#define CONFIG_MPC512x_FEC	1
#define CONFIG_NET_MULTI
#define CONFIG_PHY_ADDR		0x1F
#define CONFIG_MII		1	/* MII PHY management	*/
#define CONFIG_FEC_AN_TIMEOUT	1
#define CONFIG_HAS_ETH0

#define CONFIG_RTC_M41T62			/* use M41T00 rtc via i2c */
#define CONFIG_SYS_I2C_RTC_ADDR		0x68	/* at address 0x68	*/

#define CONFIG_ENV_IS_IN_FLASH	1
/* This has to be a multiple of the Flash sector size */
#define CONFIG_ENV_ADDR		(CONFIG_SYS_MONITOR_BASE + \
				 CONFIG_SYS_MONITOR_LEN)
#define CONFIG_ENV_SIZE		0x2000
#define CONFIG_ENV_SECT_SIZE	0x40000		/* one sector (256K) for env */

/* Address and size of Redundant Environment Sector	*/
#define CONFIG_ENV_ADDR_REDUND	(CONFIG_ENV_ADDR + CONFIG_ENV_SECT_SIZE)
#define CONFIG_ENV_SIZE_REDUND	(CONFIG_ENV_SIZE)

#define CONFIG_LOADS_ECHO	1	/* echo on for serial download */
#define CONFIG_SYS_LOADS_BAUD_CHANGE	1	/* allow baudrate change */

#include <config_cmd_default.h>

#define CONFIG_CMD_ASKENV
#define CONFIG_CMD_DATE
#define CONFIG_CMD_DHCP
#define CONFIG_CMD_EEPROM
#define CONFIG_CMD_I2C
#define CONFIG_CMD_MII
#define CONFIG_CMD_PING
#define CONFIG_CMD_REGINFO

#ifdef CONFIG_VIDEO
#define CONFIG_CMD_BMP
#endif

#define CONFIG_SYS_LONGHELP			/* undef to save memory */
#define CONFIG_SYS_LOAD_ADDR	0x2000000	/* default load address */
#define CONFIG_SYS_PROMPT	"=> "		/* Monitor Command Prompt */

#ifdef CONFIG_CMD_KGDB
	#define CONFIG_SYS_CBSIZE	1024	/* Console I/O Buffer Size */
#else
	#define CONFIG_SYS_CBSIZE	256	/* Console I/O Buffer Size */
#endif

/* Print Buffer Size */
#define CONFIG_SYS_PBSIZE (CONFIG_SYS_CBSIZE + sizeof(CONFIG_SYS_PROMPT) + 16)
/* Max number of command args */
#define CONFIG_SYS_MAXARGS	16
/* Boot Argument Buffer Size */
#define CONFIG_SYS_BARGSIZE	CONFIG_SYS_CBSIZE
/* Decrementer freq: 1ms ticks */
#define CONFIG_SYS_HZ		1000

/* Initial Memory map for Linux */
#define CONFIG_SYS_BOOTMAPSZ	(8 << 20)

/* Cache Configuration */
#define CONFIG_SYS_DCACHE_SIZE		32768
#define CONFIG_SYS_CACHELINE_SIZE	32
#ifdef CONFIG_CMD_KGDB
/* log base 2 of the above value */
#define CONFIG_SYS_CACHELINE_SHIFT	5
#endif

#define CONFIG_SYS_HID0_INIT	0x000000000
#define CONFIG_SYS_HID0_FINAL	(HID0_ENABLE_MACHINE_CHECK | HID0_ICE)
#define CONFIG_SYS_HID2	HID2_HBE

#define CONFIG_HIGH_BATS	1	/* High BATs supported */

#define BOOTFLAG_COLD		0x01	/* Normal Power-On: Boot from FLASH */
#define BOOTFLAG_WARM		0x02	/* Software reboot */

#ifdef CONFIG_CMD_KGDB
#define CONFIG_KGDB_BAUDRATE	230400	/* speed of kgdb serial port */
#define CONFIG_KGDB_SER_INDEX	2	/* which serial port to use */
#endif

#ifdef CONFIG_SERIAL_MULTI
/* POST support */
#define CONFIG_POST             (CONFIG_SYS_POST_COPROC)
#endif

#define CONFIG_TIMESTAMP

#define CONFIG_HOSTNAME		pdm360ng
/* default location for tftp and bootm */
#define CONFIG_LOADADDR		400000

#define CONFIG_BOOTDELAY	5	/* -1 disables auto-boot */

#define CONFIG_PREBOOT	"echo;"	\
	"echo PDM360NG SAMPLE;" \
	"echo"

#define CONFIG_BOOTCOMMAND	"run env_cont"

#define CONFIG_OF_LIBFDT	1
#define CONFIG_OF_BOARD_SETUP	1
#define CONFIG_OF_SUPPORT_OLD_DEVICE_TREES	1
#define CONFIG_FIT
#define CONFIG_FIT_VERBOSE

#define OF_CPU			"PowerPC,5121@0"
#define OF_SOC_COMPAT		"fsl,mpc5121-immr"
#define OF_TBCLK		(bd->bi_busfreq / 4)
#define OF_STDOUT_PATH		"/soc@80000000/serial@11600"

#include "mpc5121-common.h"

#endif	/* __CONFIG_H */
