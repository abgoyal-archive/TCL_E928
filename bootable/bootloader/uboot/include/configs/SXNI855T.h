


/* ------------------------------------------------------------------------- */


#ifndef __CONFIG_H
#define __CONFIG_H

#include <mpc8xx_irq.h>

#define CONFIG_SXNI855T		1	/* SIXNET IPm 855T CPU module */

#define CONFIG_MPC860		1
#define CONFIG_MPC860T		1
#define CONFIG_MPC855T		1

#define	CONFIG_8xx_CONS_SMC1	1	/* Console is on SMC1		*/
#undef	CONFIG_8xx_CONS_SMC2
#undef	CONFIG_8xx_CONS_SCC1
#undef	CONFIG_8xx_CONS_NONE
#define CONFIG_BAUDRATE		9600
#define CONFIG_LOADS_ECHO	1	/* echo on for serial download	*/

#define MPC8XX_FACT		10	/* 50 MHz is 5 MHz in times 10	*/

#define	CONFIG_CLOCKS_IN_MHZ	1	/* clocks passsed to Linux in MHz */

#if 0
#define CONFIG_BOOTDELAY	-1	/* autoboot disabled		*/
#else
#define CONFIG_BOOTDELAY	5	/* autoboot after 5 seconds	*/
#endif

#define CONFIG_HAS_ETH1

#define	CONFIG_STATUS_LED	1	/* Status LED enabled		*/

# define STATUS_LED_PAR		im_ioport.iop_papar
# define STATUS_LED_DIR		im_ioport.iop_padir
# define STATUS_LED_ODR		im_ioport.iop_paodr
# define STATUS_LED_DAT		im_ioport.iop_padat

# define STATUS_LED_BIT		0x8000		/* LED 0 is on PA.0 */
# define STATUS_LED_PERIOD	((CONFIG_SYS_HZ / 2) / 5)	/* blink at 5 Hz */
# define STATUS_LED_STATE	STATUS_LED_BLINKING

# define STATUS_LED_ACTIVE	0		/* LED on for bit == 0	*/

# define STATUS_LED_BOOT	0		/* LED 0 used for boot status */

#ifdef DEV	/* development (debug) settings */
#define CONFIG_BOOT_LED_STATE	STATUS_LED_OFF
#else		/* production settings */
#define CONFIG_BOOT_LED_STATE	STATUS_LED_ON
#endif

#define CONFIG_SHOW_BOOT_PROGRESS 1

#define CONFIG_BOOTCOMMAND	"bootm f8040000 f8100000" /* autoboot command */
#define CONFIG_BOOTARGS		"root=/dev/ram ip=off"

#define CONFIG_MISC_INIT_R		/* have misc_init_r() function */
#define CONFIG_BOARD_POSTCLK_INIT	/* have board_postclk_init() function */

#undef	CONFIG_WATCHDOG			/* watchdog disabled		*/

#define	CONFIG_RTC_DS1306		/* Dallas 1306 real time clock	*/

#define	CONFIG_SOFT_I2C			/* I2C bit-banged		*/
#define PB_SCL		0x00000020	/* PB 26 */
#define PB_SDA		0x00000010	/* PB 27 */

#define I2C_INIT	(immr->im_cpm.cp_pbdir |=  PB_SCL)
#define I2C_ACTIVE	(immr->im_cpm.cp_pbdir |=  PB_SDA)
#define I2C_TRISTATE	(immr->im_cpm.cp_pbdir &= ~PB_SDA)
#define I2C_READ	((immr->im_cpm.cp_pbdat & PB_SDA) != 0)
#define I2C_SDA(bit)	if(bit) immr->im_cpm.cp_pbdat |=  PB_SDA; \
			else    immr->im_cpm.cp_pbdat &= ~PB_SDA
#define I2C_SCL(bit)	if(bit) immr->im_cpm.cp_pbdat |=  PB_SCL; \
			else    immr->im_cpm.cp_pbdat &= ~PB_SCL
#define I2C_DELAY	udelay(5)	/* 1/4 I2C clock duration */

# define CONFIG_SYS_I2C_SPEED		50000
# define CONFIG_SYS_I2C_SLAVE		0xFE
# define CONFIG_SYS_I2C_EEPROM_ADDR	0x50	/* Atmel 24C64			*/
# define CONFIG_SYS_I2C_EEPROM_ADDR_LEN 2	/* two byte address		*/

#define	CONFIG_FEC_ENET		1	/* use FEC ethernet  */
#define	CONFIG_MII		1

#define CONFIG_SYS_DISCOVER_PHY


#define CONFIG_BOOTP_BOOTFILESIZE
#define CONFIG_BOOTP_BOOTPATH
#define CONFIG_BOOTP_GATEWAY
#define CONFIG_BOOTP_HOSTNAME


#include <config_cmd_default.h>

#define CONFIG_CMD_EEPROM
#define CONFIG_CMD_JFFS2
#define CONFIG_CMD_DATE

#define	CONFIG_SYS_LONGHELP			/* undef to save a little memory */
#define	CONFIG_SYS_PROMPT		"=>"	/* Monitor Command Prompt	*/
#if defined(CONFIG_CMD_KGDB)
#define	CONFIG_SYS_CBSIZE	1024		/* Console I/O Buffer Size	*/
#else
#define	CONFIG_SYS_CBSIZE	256		/* Console I/O Buffer Size	*/
#endif
#define	CONFIG_SYS_PBSIZE (CONFIG_SYS_CBSIZE+sizeof(CONFIG_SYS_PROMPT)+16) /* Print Buffer Size */
#define	CONFIG_SYS_MAXARGS	16		/* max number of command args	*/
#define CONFIG_SYS_BARGSIZE	CONFIG_SYS_CBSIZE	/* Boot Argument Buffer Size	*/

#define CONFIG_SYS_MEMTEST_START	0x0100000	/* memtest works on	*/
#define CONFIG_SYS_MEMTEST_END		0x0400000	/* 1 ... 4 MB in DRAM	*/

#define CONFIG_SYS_LOAD_ADDR		0x00100000

#define	CONFIG_SYS_HZ		1000		/* decrementer freq: 1 ms ticks	*/

#define CONFIG_SYS_BAUDRATE_TABLE	{ 9600, 19200, 38400, 57600, 115200 }

#define CONFIG_SYS_IMMR		0xFF000000
#define CONFIG_SYS_IMMR_SIZE		((uint)(64 * 1024))

#define CONFIG_SYS_INIT_RAM_ADDR	CONFIG_SYS_IMMR
#define	CONFIG_SYS_INIT_RAM_END	0x2F00	/* End of used area in DPRAM	*/
#define	CONFIG_SYS_GBL_DATA_SIZE	64  /* size in bytes reserved for initial data */
#define CONFIG_SYS_GBL_DATA_OFFSET	(CONFIG_SYS_INIT_RAM_END - CONFIG_SYS_GBL_DATA_SIZE)
#define	CONFIG_SYS_INIT_SP_OFFSET	CONFIG_SYS_GBL_DATA_OFFSET

#define	CONFIG_SYS_SDRAM_BASE		0x00000000
#define	CONFIG_SYS_SRAM_BASE		0xF4000000
#define	CONFIG_SYS_SRAM_SIZE		0x04000000	/* autosize up to 64Mbyte */

#define CONFIG_SYS_FLASH_BASE		0xF8000000
#define CONFIG_SYS_FLASH_SIZE		((uint)(8 * 1024 * 1024))	/* max 8Mbyte */

#define CONFIG_SYS_DFLASH_BASE		0xff020000 /* DiskOnChip or NAND FLASH */
#define CONFIG_SYS_DFLASH_SIZE		0x00010000

#define CONFIG_SYS_FPGA_BASE		0xFF100000	/* Xilinx FPGA */
#define CONFIG_SYS_FPGA_PROG		0xFF130000	/* Programming address */
#define CONFIG_SYS_FPGA_SIZE		0x00040000	/* 256KiB usable */

#define	CONFIG_SYS_MONITOR_LEN		(256 << 10)	/* Reserve 256 kB for Monitor	*/
#define CONFIG_SYS_MONITOR_BASE	CONFIG_SYS_FLASH_BASE
#define	CONFIG_SYS_MALLOC_LEN		(128 << 10)	/* Reserve 128 kB for malloc()	*/

#define	CONFIG_SYS_BOOTMAPSZ		(8 << 20)	/* Initial Memory map for Linux	*/
#define CONFIG_SYS_MAX_FLASH_BANKS	1	/* max number of memory banks		*/
#define CONFIG_SYS_MAX_FLASH_SECT	135	/* max number of sectors on one chip	*/

#define CONFIG_SYS_FLASH_ERASE_TOUT	120000	/* Timeout for Flash Erase (in ms)	*/
#define CONFIG_SYS_FLASH_WRITE_TOUT	500	/* Timeout for Flash Write (in ms)	*/

#define CONFIG_SYS_CACHELINE_SIZE	16	/* For all MPC8xx CPUs			*/
#if defined(CONFIG_CMD_KGDB)
#define CONFIG_SYS_CACHELINE_SHIFT	4	/* log base 2 of the above value	*/
#endif

#if defined(CONFIG_WATCHDOG)
#define CONFIG_SYS_SYPCR	(SYPCR_SWTC | SYPCR_BMT | SYPCR_BME | SYPCR_SWF | \
			 SYPCR_SWE  | SYPCR_SWRI| SYPCR_SWP)
#else
#define CONFIG_SYS_SYPCR	(SYPCR_SWTC | SYPCR_BMT | SYPCR_BME | SYPCR_SWF | SYPCR_SWP)
#endif

#define CONFIG_SYS_SIUMCR	(SIUMCR_DBGC00 | SIUMCR_DBPC00 | SIUMCR_MLRC01)

#define CONFIG_SYS_TBSCR	(TBSCR_REFA | TBSCR_REFB | TBSCR_TBE)

#define CONFIG_SYS_PISCR	(PISCR_PS | PISCR_PITF)

#define CONFIG_SYS_PLPRCR	(((MPC8XX_FACT-1) << PLPRCR_MF_SHIFT) |	\
				PLPRCR_SPLSS | PLPRCR_TEXPS | PLPRCR_TMIST)

#define SCCR_MASK	SCCR_EBDF11
#define CONFIG_SYS_SCCR	(SCCR_TBS|SCCR_COM00|SCCR_DFSYNC00|SCCR_DFBRG00|SCCR_DFNL000|SCCR_DFNH000|SCCR_DFLCD000|SCCR_DFALCD00)

 /*-----------------------------------------------------------------------
 *
 *-----------------------------------------------------------------------
 *
 */
#define CONFIG_SYS_DER		0



#define CONFIG_SYS_PRELIM_OR0_AM	0xFC000000	/* OR addr mask */

/* FLASH timing: ACS = 10, TRLX = 1, CSNT = 1, SCY = 3, EHTR = 0	*/
#define CONFIG_SYS_OR_TIMING_FLASH	(OR_CSNT_SAM  | OR_ACS_DIV4 | OR_BI | OR_SCY_3_CLK | OR_TRLX)

#define CONFIG_SYS_OR0_PRELIM	(CONFIG_SYS_PRELIM_OR0_AM | CONFIG_SYS_OR_TIMING_FLASH)

#define CONFIG_FLASH_16BIT
#define CONFIG_SYS_BR0_PRELIM	((CONFIG_SYS_FLASH_BASE & BR_BA_MSK) | BR_PS_16 | BR_V )
#define CONFIG_SYS_FLASH_PROTECTION	/* need to lock/unlock sectors in hardware */

#define CONFIG_SYS_OR_TIMING_FPGA \
	(OR_CSNT_SAM | OR_ACS_DIV2 | OR_BI | OR_SCY_4_CLK | OR_EHTR | OR_TRLX)
#define CONFIG_SYS_BR1_PRELIM	((CONFIG_SYS_FPGA_BASE & BR_BA_MSK) | BR_PS_8 | BR_V )
#define CONFIG_SYS_OR1_PRELIM	(((-CONFIG_SYS_FPGA_SIZE) & OR_AM_MSK) | CONFIG_SYS_OR_TIMING_FPGA)

#define CONFIG_SYS_OR_TIMING_DFLASH \
	(OR_CSNT_SAM | OR_ACS_DIV4 | OR_BI | OR_SCY_2_CLK | OR_EHTR | OR_TRLX)
#define CONFIG_SYS_BR4_PRELIM	((CONFIG_SYS_DFLASH_BASE & BR_BA_MSK) | BR_PS_8 | BR_V )
#define CONFIG_SYS_OR4_PRELIM	(((-CONFIG_SYS_DFLASH_SIZE) & OR_AM_MSK) | CONFIG_SYS_OR_TIMING_DFLASH)

#define CONFIG_SYS_DUART_SIZE	0x8000	/* 32K window, only uses 8 bytes */
#define CONFIG_SYS_DUARTA_BASE	0xff010000
#define CONFIG_SYS_DUARTB_BASE	0xff018000

#define DUART_MBMR	0
#define DUART_OR_VALUE (ORMASK(CONFIG_SYS_DUART_SIZE) | OR_G5LS| OR_BI)
#define DUART_BR_VALUE (BR_MS_UPMB | BR_PS_8 | BR_V)
#define DUART_BR5_VALUE ((CONFIG_SYS_DUARTA_BASE & BR_BA_MSK ) | DUART_BR_VALUE)
#define DUART_BR6_VALUE ((CONFIG_SYS_DUARTB_BASE & BR_BA_MSK ) | DUART_BR_VALUE)

#define	BOOTFLAG_COLD	0x01		/* Normal Power-On: Boot from FLASH	*/
#define BOOTFLAG_WARM	0x02		/* Software reboot			*/

#define CONFIG_RESET_ON_PANIC		/* reset if system panic() */

#define CONFIG_ENV_IS_IN_FLASH
#ifdef CONFIG_ENV_IS_IN_FLASH
  /* environment is in FLASH */
  #define CONFIG_ENV_ADDR		0xF8040000	/* AM29LV641 or AM29LV800BT */
  #define CONFIG_ENV_ADDR_REDUND	0xF8050000	/* AM29LV641 or AM29LV800BT */
  #define CONFIG_ENV_SECT_SIZE	0x00010000
  #define CONFIG_ENV_SIZE		0x00002000
#else
  /* environment is in EEPROM */
  #define CONFIG_ENV_IS_IN_EEPROM		1
  #define CONFIG_ENV_OFFSET		0	/* at beginning of EEPROM */
  #define CONFIG_ENV_SIZE		     1024	/* Use only a part of it*/
#endif

#if 1
#define CONFIG_AUTOBOOT_KEYED		/* use key strings to stop autoboot */
#define CONFIG_AUTOBOOT_PROMPT		"autoboot in %d seconds\n", bootdelay
#define CONFIG_AUTOBOOT_DELAY_STR	"delayabit"
#define CONFIG_AUTOBOOT_STOP_STR	" " /* easy to stop for now */
#endif

#endif	/* __CONFIG_H */
