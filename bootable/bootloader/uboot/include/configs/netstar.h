

#ifndef __CONFIG_H
#define __CONFIG_H

#include <configs/omap1510.h>

#define CONFIG_ARM925T	1		/* This is an arm925t CPU */
#define CONFIG_OMAP	1		/* in a TI OMAP core */
#define CONFIG_OMAP1510 1		/* which is in a 5910 */

/* Input clock of PLL */
#define CONFIG_SYS_CLK_FREQ		150000000	/* 150MHz */
#define CONFIG_XTAL_FREQ		12000000	/*  12MHz */

#undef CONFIG_USE_IRQ			/* we don't need IRQ/FIQ stuff */

#define CONFIG_MISC_INIT_R		/* There is nothing to really init */
#define BOARD_LATE_INIT			/* but we flash the LEDs here */

#define CONFIG_CMDLINE_TAG		1	/* enable passing of ATAGs */
#define CONFIG_SETUP_MEMORY_TAGS	1
#define CONFIG_INITRD_TAG		1

#define CONFIG_SILENT_CONSOLE		1	/* enable silent startup */
#define CONFIG_SYS_CONSOLE_INFO_QUIET

#define CONFIG_NR_DRAM_BANKS		1
#define PHYS_SDRAM_1			0x10000000
#define PHYS_SDRAM_1_SIZE		(64 * 1024 * 1024)
#define PHYS_FLASH_1			0x00000000

#define CONFIG_SYS_MONITOR_BASE		PHYS_FLASH_1
#define CONFIG_SYS_MONITOR_LEN		(256 * 1024)

#define CONFIG_ENV_IS_IN_FLASH
#define CONFIG_ENV_ADDR			0x4000
#define CONFIG_ENV_SIZE			(8 * 1024)
#define CONFIG_ENV_SECT_SIZE		(8 * 1024)
#define CONFIG_ENV_ADDR_REDUND		0x6000
#define CONFIG_ENV_SIZE_REDUND		CONFIG_ENV_SIZE
#define CONFIG_ENV_OVERWRITE

#define CONFIG_SYS_GBL_DATA_SIZE	128
#define CONFIG_SYS_MALLOC_LEN		(4 * 1024 * 1024)

#define CONFIG_STACKSIZE		(1 * 1024 * 1024)

#define CONFIG_SYS_NS16550
#define CONFIG_SYS_NS16550_SERIAL
#define CONFIG_SYS_NS16550_REG_SIZE	(-4)
#define CONFIG_SYS_NS16550_CLK		(CONFIG_XTAL_FREQ)
#define CONFIG_SYS_NS16550_COM1		OMAP1510_UART1_BASE

#define CONFIG_NET_MULTI
#define CONFIG_SMC91111
#define CONFIG_SMC91111_BASE		0x04000300

#define CONFIG_SYS_FLASH_BASE		PHYS_FLASH_1
#define CONFIG_SYS_MAX_FLASH_BANKS	1
#define CONFIG_SYS_MAX_FLASH_SECT	19

#define CONFIG_SYS_FLASH_CFI
#define CONFIG_FLASH_CFI_DRIVER
#define CONFIG_SYS_FLASH_CFI_WIDTH	FLASH_CFI_16BIT
#define CONFIG_FLASH_CFI_LEGACY
#define CONFIG_SYS_FLASH_LEGACY_512Kx16

#define CONFIG_SYS_MAX_NAND_DEVICE	1
#define CONFIG_SYS_NAND_BASE		0x04000000 + (2 << 23)
#define NAND_ALLOW_ERASE_ALL		1

#define CONFIG_HARD_I2C
#define CONFIG_SYS_I2C_SPEED		100000
#define CONFIG_SYS_I2C_SLAVE		1
#define CONFIG_DRIVER_OMAP1510_I2C

#define CONFIG_RTC_DS1307
#define CONFIG_SYS_I2C_RTC_ADDR		0x68


#define CONFIG_CONS_INDEX		1
#define CONFIG_BAUDRATE			115200
#define CONFIG_SYS_BAUDRATE_TABLE	{ 9600, 19200, 38400, 57600, 115200 }

/*#define CONFIG_SKIP_RELOCATE_UBOOT*/
/*#define CONFIG_SKIP_LOWLEVEL_INIT */

#define CONFIG_CMD_MTDPARTS
#define CONFIG_MTD_DEVICE
#define CONFIG_FLASH_CFI_MTD
#define MTDIDS_DEFAULT		"nor0=physmap-flash.0,nand0=gen_nand.0"
#define MTDPARTS_DEFAULT	"mtdparts=" \
	"physmap-flash.0:8k@16k(env),8k(r_env),448k@576k(u-boot);" \
	"gen_nand.0:4M(kernel0),40M(rootfs0),4M(kernel1),40M(rootfs1),-(data)"

#define CONFIG_CMD_BDI
#define CONFIG_CMD_BOOTD
#define CONFIG_CMD_DATE
#define CONFIG_CMD_DHCP
#define CONFIG_CMD_SAVEENV
#define CONFIG_CMD_FLASH
#define CONFIG_CMD_IMI
#define CONFIG_CMD_LOADB
#define CONFIG_CMD_MEMORY
#define CONFIG_CMD_NAND
#define CONFIG_CMD_NET
#define CONFIG_CMD_PING
#define CONFIG_CMD_RUN

#define CONFIG_BOOTP_SUBNETMASK
#define CONFIG_BOOTP_GATEWAY
#define CONFIG_BOOTP_HOSTNAME
#define CONFIG_BOOTP_BOOTPATH

#define CONFIG_LOOPW

#define CONFIG_BOOTDELAY	3
#define CONFIG_ZERO_BOOTDELAY_CHECK	/* allow to break in always */
#undef  CONFIG_BOOTARGS		/* the boot command will set bootargs*/
#define CONFIG_SYS_AUTOLOAD		"n"		/* No autoload */
#define CONFIG_BOOTCOMMAND	"run fboot"
#define CONFIG_PREBOOT		"run setup"
#define	CONFIG_EXTRA_ENV_SETTINGS					\
	"autostart=yes\0"						\
	"ospart=0\0"							\
	"setup=setenv bootargs console=ttyS0,$baudrate $mtdparts\0"	\
	"setpart="							\
	"if test -n $swapos; then "					\
		"setenv swapos; saveenv; "				\
		"if test $ospart -eq 0; then "				\
			"setenv ospart 1; "				\
		"else "							\
			"setenv ospart 0; "				\
		"fi; "							\
	"fi\0"								\
	"nfsargs=setenv bootargs $bootargs "				\
		"ip=$ipaddr:$serverip:$gatewayip:$netmask:$hostname::off " \
		"nfsroot=$rootpath root=/dev/nfs\0"			\
	"flashargs=run setpart;setenv bootargs $bootargs "		\
		"root=mtd:rootfs$ospart ro "				\
		"rootfstype=jffs2\0"					\
	"ip=$ipaddr:$serverip:$gatewayip:$netmask:$hostname::off\0"	\
	"fboot=run flashargs;nboot kernel$ospart\0"			\
	"nboot=bootp;run nfsargs;tftp\0"

#if 0	/* feel free to disable for development */
#define	CONFIG_AUTOBOOT_KEYED		/* Enable password protection	*/
#define CONFIG_AUTOBOOT_PROMPT		\
	"\nNetStar PBX - boot in %d secs...\n", bootdelay
#define CONFIG_AUTOBOOT_DELAY_STR	"."	/* 1st "password"	*/
#endif

#define CONFIG_SYS_LONGHELP
#define CONFIG_SYS_PROMPT		"# "
#define CONFIG_SYS_CBSIZE		256
#define CONFIG_SYS_PBSIZE		(CONFIG_SYS_CBSIZE + \
	 sizeof(CONFIG_SYS_PROMPT) + 16)
#define CONFIG_SYS_MAXARGS		16
#define CONFIG_SYS_BARGSIZE		CONFIG_SYS_CBSIZE

#define CONFIG_SYS_HUSH_PARSER
#define CONFIG_SYS_PROMPT_HUSH_PS2	"> "
#define CONFIG_AUTO_COMPLETE

#define CONFIG_SYS_MEMTEST_START	PHYS_SDRAM_1
#define CONFIG_SYS_MEMTEST_END		PHYS_SDRAM_1 + PHYS_SDRAM_1_SIZE - \
	(CONFIG_SYS_MONITOR_LEN + CONFIG_SYS_MALLOC_LEN + CONFIG_STACKSIZE)

#define CONFIG_SYS_LOAD_ADDR		(PHYS_SDRAM_1 + 0x400000)

#define CONFIG_SYS_TIMERBASE		OMAP1510_TIMER1_BASE
#define CONFIG_SYS_PTV			7
#define CONFIG_SYS_HZ			1000

#define OMAP5910_DPLL_DIV		1
#define OMAP5910_DPLL_MUL		\
	((CONFIG_SYS_CLK_FREQ * (1 << OMAP5910_DPLL_DIV)) / CONFIG_XTAL_FREQ)

#define OMAP5910_ARM_PER_DIV	2	/* CKL/4 */
#define OMAP5910_LCD_DIV	2	/* CKL/4 */
#define OMAP5910_ARM_DIV	0	/* CKL/1 */
#define OMAP5910_DSP_DIV	0	/* CKL/1 */
#define OMAP5910_TC_DIV		1	/* CKL/2 */
#define OMAP5910_DSP_MMU_DIV	1	/* CKL/2 */
#define OMAP5910_ARM_TIM_SEL	1	/* CKL used for MPU timers */

#define OMAP5910_ARM_EN_CLK	0x03d6	/* 0000 0011 1101 0110b */
#define OMAP5910_ARM_CKCTL	((OMAP5910_ARM_PER_DIV)  |	\
				 (OMAP5910_LCD_DIV << 2) |	\
				 (OMAP5910_ARM_DIV << 4) |	\
				 (OMAP5910_DSP_DIV << 6) |	\
				 (OMAP5910_TC_DIV << 8) |	\
				 (OMAP5910_DSP_MMU_DIV << 10) |	\
				 (OMAP5910_ARM_TIM_SEL << 12))

#endif	/* __CONFIG_H */