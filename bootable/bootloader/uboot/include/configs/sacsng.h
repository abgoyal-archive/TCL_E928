

#ifndef __CONFIG_H
#define __CONFIG_H

#undef DEBUG_BOOTP_EXT	      /* Debug received vendor fields */

#undef CONFIG_LOGBUFFER       /* External logbuffer support */


/* What is the oscillator's (UX2) frequency in Hz? */
#define CONFIG_8260_CLKIN  66666600

#define CONFIG_SYS_SBC_MODCK_H 0x05

#define CONFIG_SYS_SBC_BOOT_LOW 1

#define CONFIG_SYS_FLASH0_BASE 0x40000000
#define CONFIG_SYS_FLASH0_SIZE 2

#define CONFIG_SYS_FLASH1_BASE 0x60000000
#define CONFIG_SYS_FLASH1_SIZE 2

#define CONFIG_VERY_BIG_RAM	1

#define CONFIG_SYS_SDRAM0_BASE 0x00000000
#define CONFIG_SYS_SDRAM0_SIZE 64


#define CONFIG_POST		(CONFIG_SYS_POST_MEMORY | \
				 CONFIG_SYS_POST_CPU)


#define CONFIG_CONS_ON_SMC	1	/* define if console on SMC */
#undef	CONFIG_CONS_ON_SCC		/* define if console on SCC */
#undef	CONFIG_CONS_NONE		/* define if console on neither */
#define CONFIG_CONS_INDEX	1	/* which SMC/SCC channel for console */


#undef	CONFIG_ETHER_ON_SCC
#define CONFIG_ETHER_ON_FCC
#undef	CONFIG_ETHER_NONE		/* define if ethernet on neither */

#ifdef	CONFIG_ETHER_ON_SCC
#define CONFIG_ETHER_INDEX	1	/* which SCC/FCC channel for ethernet */
#endif	/* CONFIG_ETHER_ON_SCC */

#ifdef	CONFIG_ETHER_ON_FCC
#define CONFIG_ETHER_INDEX	2	/* which SCC/FCC channel for ethernet */
#undef  CONFIG_ETHER_LOOPBACK_TEST      /* Ethernet external loopback test */
#define CONFIG_MII			/* MII PHY management		*/
#define CONFIG_BITBANGMII		/* bit-bang MII PHY management	*/

#define MDIO_PORT	2	        /* Port A=0, B=1, C=2, D=3 */
#define MDIO_DECLARE	volatile ioport_t *iop = ioport_addr ( \
				(immap_t *) CONFIG_SYS_IMMR, MDIO_PORT )
#define MDC_DECLARE	MDIO_DECLARE

#define MDIO_ACTIVE	(iop->pdir |=  0x40000000)
#define MDIO_TRISTATE	(iop->pdir &= ~0x40000000)
#define MDIO_READ	((iop->pdat &  0x40000000) != 0)

#define MDIO(bit)	if(bit) iop->pdat |=  0x40000000; \
			else	iop->pdat &= ~0x40000000

#define MDC(bit)	if(bit) iop->pdat |=  0x80000000; \
			else	iop->pdat &= ~0x80000000

#define MIIDELAY	udelay(50)
#endif	/* CONFIG_ETHER_ON_FCC */

#if defined(CONFIG_ETHER_ON_SCC) && (CONFIG_ETHER_INDEX == 1)

# define CONFIG_SYS_CMXSCR_VALUE	(CMXSCR_RS1CS_CLK11  | CMXSCR_TS1CS_CLK12)

#elif defined(CONFIG_ETHER_ON_FCC) && (CONFIG_ETHER_INDEX == 2)

# define CONFIG_SYS_CMXFCR_MASK	(CMXFCR_FC2|CMXFCR_RF2CS_MSK|CMXFCR_TF2CS_MSK)
# define CONFIG_SYS_CMXFCR_VALUE	(CMXFCR_RF2CS_CLK13|CMXFCR_TF2CS_CLK14)
# define CONFIG_SYS_CPMFCR_RAMTYPE	0
# define CONFIG_SYS_FCC_PSMR		(FCC_PSMR_FDE | FCC_PSMR_LPB)

#endif /* CONFIG_ETHER_ON_FCC, CONFIG_ETHER_INDEX */

#define CONFIG_SHOW_BOOT_PROGRESS 1	/* boot progress enabled	*/

#undef  CONFIG_SYS_DRAM_TEST			/* calls other tests in board.c	*/


#define CONFIG_STATUS_LED	1	/* Status LED enabled		*/

#define STATUS_LED_PAR		im_ioport.iop_ppara
#define STATUS_LED_DIR		im_ioport.iop_pdira
#define STATUS_LED_ODR		im_ioport.iop_podra
#define STATUS_LED_DAT		im_ioport.iop_pdata

#define STATUS_LED_BIT		0x00000800	/* LED 0 is on PA.20	*/
#define STATUS_LED_PERIOD	(CONFIG_SYS_HZ)
#define STATUS_LED_STATE	STATUS_LED_OFF
#define STATUS_LED_BIT1		0x00001000	/* LED 1 is on PA.19	*/
#define STATUS_LED_PERIOD1	(CONFIG_SYS_HZ)
#define STATUS_LED_STATE1	STATUS_LED_OFF
#define STATUS_LED_BIT2		0x00002000	/* LED 2 is on PA.18	*/
#define STATUS_LED_PERIOD2	(CONFIG_SYS_HZ/2)
#define STATUS_LED_STATE2	STATUS_LED_ON

#define STATUS_LED_ACTIVE	0		/* LED on for bit == 0	*/

#define STATUS_LED_YELLOW	0
#define STATUS_LED_GREEN	1
#define STATUS_LED_RED		2
#define STATUS_LED_BOOT		1


#define CONFIG_SOFT_SPI		/* Enable SPI driver */
#define MAX_SPI_BYTES   4	/* Maximum number of bytes we can handle */
#undef  DEBUG_SPI               /* Disable SPI debugging */

#ifdef CONFIG_SOFT_SPI

#define I2C_SCLK	0x00002000      /* PD 18: Shift clock */
#define I2C_MOSI	0x00004000      /* PD 17: Master Out, Slave In */
#define I2C_MISO	0x00008000      /* PD 16: Master In, Slave Out */

#undef  SPI_INIT			/* no port initialization needed */
#define SPI_READ        ((immr->im_ioport.iop_pdatd & I2C_MISO) != 0)
#define SPI_SDA(bit)    do {						\
			if(bit) immr->im_ioport.iop_pdatd |=  I2C_MOSI; \
			else    immr->im_ioport.iop_pdatd &= ~I2C_MOSI;	\
			} while (0)
#define SPI_SCL(bit)    do {						\
			if(bit) immr->im_ioport.iop_pdatd |=  I2C_SCLK; \
			else    immr->im_ioport.iop_pdatd &= ~I2C_SCLK;	\
			} while (0)
#define SPI_DELAY                       /* No delay is needed */
#endif /* CONFIG_SOFT_SPI */


#undef  CONFIG_HARD_I2C			/* I2C with hardware support	*/
#define CONFIG_SOFT_I2C		1	/* I2C bit-banged		*/
#define CONFIG_SYS_I2C_SPEED		400000	/* I2C speed and slave address	*/
#define CONFIG_SYS_I2C_SLAVE		0x7F

#ifdef CONFIG_SOFT_I2C
#define I2C_PORT	3		/* Port A=0, B=1, C=2, D=3 */
#define I2C_ACTIVE	(iop->pdir |=  0x00010000)
#define I2C_TRISTATE	(iop->pdir &= ~0x00010000)
#define I2C_READ	((iop->pdat & 0x00010000) != 0)
#define I2C_SDA(bit)	if(bit) iop->pdat |=  0x00010000; \
			else    iop->pdat &= ~0x00010000
#define I2C_SCL(bit)	if(bit) iop->pdat |=  0x00020000; \
			else    iop->pdat &= ~0x00020000
#define I2C_DELAY	udelay(20)	/* 1/4 I2C clock duration */
#endif /* CONFIG_SOFT_I2C */

#define CONFIG_ENV_IN_OWN_SECT	1

#define CONFIG_EXTRA_ENV_SETTINGS \
"quiet=0\0" \
"serverip=192.168.123.205\0" \
"ipaddr=192.168.123.203\0" \
"checkhostname=VR8500\0" \
"reprog="\
    "bootp; " \
    "tftpboot 0x140000 /bdi2000/u-boot.bin; " \
    "protect off 60000000 6003FFFF; " \
    "erase 60000000 6003FFFF; " \
    "cp.b 140000 60000000 ${filesize}; " \
    "protect on 60000000 6003FFFF\0" \
"copyenv="\
    "protect off 60040000 6004FFFF; " \
    "erase 60040000 6004FFFF; " \
    "cp.b 40040000 60040000 10000; " \
    "protect on 60040000 6004FFFF\0" \
"copyprog="\
    "protect off 60000000 6003FFFF; " \
    "erase 60000000 6003FFFF; " \
    "cp.b 40000000 60000000 40000; " \
    "protect on 60000000 6003FFFF\0" \
"zapenv="\
    "protect off 40040000 4004FFFF; " \
    "erase 40040000 4004FFFF; " \
    "protect on 40040000 4004FFFF\0" \
"zapotherenv="\
    "protect off 60040000 6004FFFF; " \
    "erase 60040000 6004FFFF; " \
    "protect on 60040000 6004FFFF\0" \
"root-on-initrd="\
    "setenv bootcmd "\
    "version\\;" \
    "echo\\;" \
    "bootp\\;" \
    "setenv bootargs root=/dev/ram0 rw quiet " \
    "ip=\\${ipaddr}:\\${serverip}:\\${gatewayip}:\\${netmask}:\\${hostname}::off\\;" \
    "run boot-hook\\;" \
    "bootm\0" \
"root-on-initrd-debug="\
    "setenv bootcmd "\
    "version\\;" \
    "echo\\;" \
    "bootp\\;" \
    "setenv bootargs root=/dev/ram0 rw debug " \
    "ip=\\${ipaddr}:\\${serverip}:\\${gatewayip}:\\${netmask}:\\${hostname}::off\\;" \
    "run debug-hook\\;" \
    "run boot-hook\\;" \
    "bootm\0" \
"root-on-nfs="\
    "setenv bootcmd "\
    "version\\;" \
    "echo\\;" \
    "bootp\\;" \
    "setenv bootargs root=/dev/nfs rw quiet " \
    "nfsroot=\\${serverip}:\\${rootpath} " \
    "ip=\\${ipaddr}:\\${serverip}:\\${gatewayip}:\\${netmask}:\\${hostname}::off\\;" \
    "run boot-hook\\;" \
    "bootm\0" \
"root-on-nfs-debug="\
    "setenv bootcmd "\
    "version\\;" \
    "echo\\;" \
    "bootp\\;" \
    "setenv bootargs root=/dev/nfs rw debug " \
    "nfsroot=\\${serverip}:\\${rootpath} " \
    "ip=\\${ipaddr}:\\${serverip}:\\${gatewayip}:\\${netmask}:\\${hostname}::off\\;" \
    "run debug-hook\\;" \
    "run boot-hook\\;" \
    "bootm\0" \
"debug-checkout="\
    "setenv checkhostname;" \
    "setenv ethaddr 00:09:70:00:00:01;" \
    "bootp;" \
    "setenv bootargs root=/dev/nfs rw nfsroot=${serverip}:${rootpath} debug " \
    "ip=${ipaddr}:${serverip}:${gatewayip}:${netmask}:${hostname}::off;" \
    "run debug-hook;" \
    "run boot-hook;" \
    "bootm\0" \
"debug-hook="\
    "echo ipaddr    ${ipaddr};" \
    "echo serverip  ${serverip};" \
    "echo gatewayip ${gatewayip};" \
    "echo netmask   ${netmask};" \
    "echo hostname  ${hostname}\0" \
"ana=run adc ; run dac\0" \
"adc=run adc-12 ; run adc-34\0" \
"adc-12=echo ### ADC-12 ; i2c md e 81 e\0" \
"adc-34=echo ### ADC-34 ; i2c md f 81 e\0" \
"dac=echo ### DAC ; i2c md 11 81 5\0" \
"boot-hook=echo\0"

/* What should the console's baud rate be? */
#define CONFIG_BAUDRATE		9600

/* Ethernet MAC address */
#define CONFIG_ETHADDR		00:09:70:00:00:00

/* The default Ethernet MAC address can be overwritten just once  */
#ifdef  CONFIG_ETHADDR
#define CONFIG_OVERWRITE_ETHADDR_ONCE 1
#endif

#define CONFIG_MISC_INIT_R

/* Set to a positive value to delay for running BOOTCOMMAND */
#define CONFIG_BOOTDELAY	1	/* autoboot after 1 second */

#define CONFIG_AUTOBOOT_KEYED
#define CONFIG_AUTOBOOT_PROMPT	"Autobooting...\n"
#define CONFIG_AUTOBOOT_STOP_STR	" "
#undef  CONFIG_AUTOBOOT_DELAY_STR
#define CONFIG_ZERO_BOOTDELAY_CHECK
#define DEBUG_BOOTKEYS		0

#undef	CONFIG_BOOT_ROOT_INITRD		/* Use ram disk for the root file system */
#define	CONFIG_BOOT_ROOT_NFS		/* Use a NFS mounted root file system */

#ifdef CONFIG_BOOT_ROOT_INITRD
#define CONFIG_BOOTCOMMAND \
	"version;" \
	"echo;" \
	"bootp;" \
	"setenv bootargs root=/dev/ram0 rw quiet " \
	"ip=${ipaddr}:${serverip}:${gatewayip}:${netmask}:${hostname}::off;" \
	"run boot-hook;" \
	"bootm"
#endif /* CONFIG_BOOT_ROOT_INITRD */

#ifdef CONFIG_BOOT_ROOT_NFS
#define CONFIG_BOOTCOMMAND \
	"version;" \
	"echo;" \
	"bootp;" \
	"setenv bootargs root=/dev/nfs rw nfsroot=${serverip}:${rootpath} quiet " \
	"ip=${ipaddr}:${serverip}:${gatewayip}:${netmask}:${hostname}::off;" \
	"run boot-hook;" \
	"bootm"
#endif /* CONFIG_BOOT_ROOT_NFS */

#define CONFIG_BOOTP_RANDOM_DELAY       /* Randomize the BOOTP retry delay */

#define CONFIG_BOOTP_SUBNETMASK
#define CONFIG_BOOTP_GATEWAY
#define CONFIG_BOOTP_HOSTNAME
#define CONFIG_BOOTP_BOOTPATH
#define CONFIG_BOOTP_BOOTFILESIZE
#define  CONFIG_BOOTP_DNS
#define  CONFIG_BOOTP_DNS2
#define  CONFIG_BOOTP_SEND_HOSTNAME


/* undef this to save memory */
#define CONFIG_SYS_LONGHELP

/* Monitor Command Prompt */
#define CONFIG_SYS_PROMPT		"=> "

#undef  CONFIG_SYS_HUSH_PARSER
#ifdef  CONFIG_SYS_HUSH_PARSER
#define CONFIG_SYS_PROMPT_HUSH_PS2     "> "
#endif

#define CONFIG_TIMESTAMP

#define CONFIG_VERSION_VARIABLE


#include <config_cmd_default.h>

#define CONFIG_CMD_ELF
#define CONFIG_CMD_ASKENV
#define CONFIG_CMD_I2C
#define CONFIG_CMD_SPI
#define CONFIG_CMD_SDRAM
#define CONFIG_CMD_REGINFO
#define CONFIG_CMD_IMMAP
#define CONFIG_CMD_IRQ
#define CONFIG_CMD_PING

#undef CONFIG_CMD_KGDB

#ifdef CONFIG_ETHER_ON_FCC
#define CONFIG_CMD_MII
#endif


/* Where do the internal registers live? */
#define CONFIG_SYS_IMMR		0xF0000000

#undef	CONFIG_WATCHDOG			/* disable the watchdog */


#define CONFIG_MPC8260		1	/* This is an MPC8260 CPU   */
#define CONFIG_SBC8260		1	/* on an EST SBC8260 Board  */
#define CONFIG_SACSng		1	/* munged for the SACSng */
#define CONFIG_CPM2		1	/* Has a CPM2 */

#define CONFIG_SYS_BOOTM_HEADER_QUIET 1        /* Suppress the image header dump    */
					/* in the bootm command.             */
#define CONFIG_SYS_BOOTM_PROGESS_QUIET 1       /* Suppress the progress displays,   */
					/* "## <message>" from the bootm cmd */
#define CONFIG_SYS_BOOTP_CHECK_HOSTNAME 1      /* If checkhostname environment is   */
					/* defined, then the hostname param  */
					/* validated against checkhostname.  */
#define CONFIG_SYS_BOOTP_RETRY_COUNT 0x40000000 /* # of timeouts before giving up   */
#define CONFIG_SYS_BOOTP_SHORT_RANDOM_DELAY 1  /* Use a short random delay value    */
					/* (limited to maximum of 1024 msec) */
#define CONFIG_SYS_CHK_FOR_ABORT_AT_LEAST_ONCE 1
					/* Check for abort key presses       */
					/* at least once in dependent of the */
					/* CONFIG_BOOTDELAY value.           */
#define CONFIG_SYS_CONSOLE_INFO_QUIET 1        /* Don't print console @ startup     */
#define CONFIG_SYS_FAULT_ECHO_LINK_DOWN 1      /* Echo the inverted Ethernet link   */
					/* state to the fault LED.           */
#define CONFIG_SYS_FAULT_MII_ADDR 0x02         /* MII addr of the PHY to check for  */
					/* the Ethernet link state.          */
#define CONFIG_SYS_STATUS_FLASH_UNTIL_TFTP_OK 1 /* Keeping the status LED flashing  */
					/* until the TFTP is successful.     */
#define CONFIG_SYS_STATUS_OFF_AFTER_NETBOOT 1  /* After a successful netboot,       */
					/* turn off the STATUS LEDs.         */
#define CONFIG_SYS_TFTP_BLINK_STATUS_ON_DATA_IN 1 /* Blink status LED based on      */
					/* incoming data.                    */
#define CONFIG_SYS_TFTP_BLOCKS_PER_HASH 100    /* For every XX blocks, output a '#' */
					/* to signify that tftp is moving.   */
#define CONFIG_SYS_TFTP_HASHES_PER_FLASH 200   /* For every '#' hashes,             */
					/* flash the status LED.             */
#define CONFIG_SYS_TFTP_HASHES_PER_LINE 65     /* Only output XX '#'s per line      */
					/* during the tftp file transfer.    */
#define CONFIG_SYS_TFTP_PROGESS_QUIET 1        /* Suppress the progress displays    */
					/* '#'s from the tftp command.       */
#define CONFIG_SYS_TFTP_STATUS_QUIET 1         /* Suppress the status displays      */
					/* issued during the tftp command.   */
#define CONFIG_SYS_TFTP_TIMEOUT_COUNT 5        /* How many timeouts TFTP will allow */
					/* before it gives up.               */

#if defined(CONFIG_CMD_KGDB)
#  define CONFIG_SYS_CBSIZE		1024	/* Console I/O Buffer Size	     */
#else
#  define CONFIG_SYS_CBSIZE		256	/* Console I/O Buffer Size	     */
#endif

/* Print Buffer Size */
#define CONFIG_SYS_PBSIZE	  (CONFIG_SYS_CBSIZE + sizeof(CONFIG_SYS_PROMPT)+16)

#define CONFIG_SYS_MAXARGS		32	/* max number of command args	*/

#define CONFIG_SYS_BARGSIZE		CONFIG_SYS_CBSIZE /* Boot Argument Buffer Size	   */

#define CONFIG_SYS_LOAD_ADDR		0x400000   /* default load address */
#define CONFIG_SYS_HZ			1000	/* decrementer freq: 1 ms ticks */

#define CONFIG_SYS_ALT_MEMTEST                 /* Select full-featured memory test */
#define CONFIG_SYS_MEMTEST_START	0x2000	/* memtest works from the end of */
					/* the exception vector table */
					/* to the end of the DRAM  */
					/* less monitor and malloc area */
#define CONFIG_SYS_STACK_USAGE		0x10000 /* Reserve 64k for the stack usage */
#define CONFIG_SYS_MEM_END_USAGE	( CONFIG_SYS_MONITOR_LEN \
				+ CONFIG_SYS_MALLOC_LEN \
				+ CONFIG_ENV_SECT_SIZE \
				+ CONFIG_SYS_STACK_USAGE )

#define CONFIG_SYS_MEMTEST_END		( CONFIG_SYS_SDRAM_SIZE * 1024 * 1024 \
				- CONFIG_SYS_MEM_END_USAGE )

/* valid baudrates */
#define CONFIG_SYS_BAUDRATE_TABLE	{ 9600, 19200, 38400, 57600, 115200 }


#define CONFIG_SYS_FLASH_BASE	CONFIG_SYS_FLASH0_BASE
#define CONFIG_SYS_FLASH_SIZE	CONFIG_SYS_FLASH0_SIZE
#define CONFIG_SYS_SDRAM_BASE	CONFIG_SYS_SDRAM0_BASE
#define CONFIG_SYS_SDRAM_SIZE	CONFIG_SYS_SDRAM0_SIZE

#if defined(CONFIG_SYS_SBC_BOOT_LOW)
#  define  CONFIG_SYS_SBC_HRCW_BOOT_FLAGS  (HRCW_CIP | HRCW_BMS)
#else
#  define  CONFIG_SYS_SBC_HRCW_BOOT_FLAGS  (0)
#endif /* defined(CONFIG_SYS_SBC_BOOT_LOW) */

/* get the HRCW ISB field from CONFIG_SYS_IMMR */
#define CONFIG_SYS_SBC_HRCW_IMMR	( ((CONFIG_SYS_IMMR & 0x10000000) >> 10) | \
				  ((CONFIG_SYS_IMMR & 0x01000000) >>  7) | \
				  ((CONFIG_SYS_IMMR & 0x00100000) >>  4) )

#define CONFIG_SYS_HRCW_MASTER		( HRCW_BPS10				| \
				  HRCW_DPPC11				| \
				  CONFIG_SYS_SBC_HRCW_IMMR			| \
				  HRCW_MMR00				| \
				  HRCW_LBPC11				| \
				  HRCW_APPC10				| \
				  HRCW_CS10PC00				| \
				  (CONFIG_SYS_SBC_MODCK_H & HRCW_MODCK_H1111)	| \
				  CONFIG_SYS_SBC_HRCW_BOOT_FLAGS )

/* no slaves */
#define CONFIG_SYS_HRCW_SLAVE1		0
#define CONFIG_SYS_HRCW_SLAVE2		0
#define CONFIG_SYS_HRCW_SLAVE3		0
#define CONFIG_SYS_HRCW_SLAVE4		0
#define CONFIG_SYS_HRCW_SLAVE5		0
#define CONFIG_SYS_HRCW_SLAVE6		0
#define CONFIG_SYS_HRCW_SLAVE7		0

#define CONFIG_SYS_INIT_RAM_ADDR	CONFIG_SYS_IMMR
#define CONFIG_SYS_INIT_RAM_END	0x4000	/* End of used area in DPRAM	*/
#define CONFIG_SYS_GBL_DATA_SIZE	128	/* bytes reserved for initial data */
#define CONFIG_SYS_GBL_DATA_OFFSET	(CONFIG_SYS_INIT_RAM_END - CONFIG_SYS_GBL_DATA_SIZE)
#define CONFIG_SYS_INIT_SP_OFFSET	CONFIG_SYS_GBL_DATA_OFFSET

#define CONFIG_SYS_MONITOR_BASE	CONFIG_SYS_FLASH0_BASE

#if (CONFIG_SYS_MONITOR_BASE < CONFIG_SYS_FLASH_BASE)
#  define CONFIG_SYS_RAMBOOT
#endif

#define CONFIG_SYS_MONITOR_LEN		(256 << 10)	/* Reserve 256 kB for Monitor	*/
#define CONFIG_SYS_MALLOC_LEN		(128 << 10)	/* Reserve 128 kB for malloc()	*/

#define CONFIG_SYS_BOOTMAPSZ		(8 << 20)	/* Initial Memory map for Linux */


#define CONFIG_SYS_FLASH_CFI		1	/* Flash is CFI conformant		*/
#undef  CONFIG_SYS_FLASH_PROTECTION		/* use hardware protection		*/
#define CONFIG_SYS_MAX_FLASH_BANKS	2	/* max number of memory banks		*/
#define CONFIG_SYS_MAX_FLASH_SECT	(64+4)	/* max number of sectors on one chip	*/

#define CONFIG_SYS_FLASH_ERASE_TOUT	8000	/* Timeout for Flash Erase (in ms)	*/
#define CONFIG_SYS_FLASH_WRITE_TOUT	1	/* Timeout for Flash Write (in ms)	*/

#ifndef CONFIG_SYS_RAMBOOT
#  define CONFIG_ENV_IS_IN_FLASH	1

#  ifdef CONFIG_ENV_IN_OWN_SECT
#    define CONFIG_ENV_ADDR	(CONFIG_SYS_MONITOR_BASE + CONFIG_SYS_MONITOR_LEN)
#    define CONFIG_ENV_SECT_SIZE	0x10000
#  else
#    define CONFIG_ENV_ADDR (CONFIG_SYS_FLASH_BASE + CONFIG_SYS_MONITOR_LEN - CONFIG_ENV_SECT_SIZE)
#    define CONFIG_ENV_SIZE	0x1000	/* Total Size of Environment Sector	*/
#    define CONFIG_ENV_SECT_SIZE	0x10000 /* see README - env sect real size	*/
#  endif /* CONFIG_ENV_IN_OWN_SECT */

#else
#  define CONFIG_ENV_IS_IN_NVRAM	1
#  define CONFIG_ENV_ADDR		(CONFIG_SYS_MONITOR_BASE - 0x1000)
#  define CONFIG_ENV_SIZE		0x200
#endif /* CONFIG_SYS_RAMBOOT */

#define CONFIG_SYS_CACHELINE_SIZE	32	/* For MPC8260 CPU */

#if defined(CONFIG_CMD_KGDB)
# define CONFIG_SYS_CACHELINE_SHIFT	5	/* log base 2 of the above value */
#endif

#define CONFIG_SYS_HID0_INIT	(HID0_ICE  |\
			 HID0_DCE  |\
			 HID0_ICFI |\
			 HID0_DCI  |\
			 HID0_IFEM |\
			 HID0_ABE)

#define CONFIG_SYS_HID0_FINAL	(HID0_ICE  |\
			 HID0_IFEM |\
			 HID0_ABE  |\
			 HID0_EMCP)
#define CONFIG_SYS_HID2	0

#define CONFIG_SYS_RMR		0

#define CONFIG_SYS_BCR		(BCR_ETM)


#define CONFIG_SYS_SIUMCR	(SIUMCR_DPPC11	|\
			 SIUMCR_L2CPC00 |\
			 SIUMCR_APPC10	|\
			 SIUMCR_MMR00)


#if defined(CONFIG_WATCHDOG)
#define CONFIG_SYS_SYPCR	(SYPCR_SWTC |\
			 SYPCR_BMT  |\
			 SYPCR_PBME |\
			 SYPCR_LBME |\
			 SYPCR_SWRI |\
			 SYPCR_SWP  |\
			 SYPCR_SWE)
#else
#define CONFIG_SYS_SYPCR	(SYPCR_SWTC |\
			 SYPCR_BMT  |\
			 SYPCR_PBME |\
			 SYPCR_LBME |\
			 SYPCR_SWRI |\
			 SYPCR_SWP)
#endif /* CONFIG_WATCHDOG */

#define CONFIG_SYS_TMCNTSC	(TMCNTSC_SEC |\
			 TMCNTSC_ALR |\
			 TMCNTSC_TCF |\
			 TMCNTSC_TCE)

#define CONFIG_SYS_PISCR	(PISCR_PS  |\
			 PISCR_PTF |\
			 PISCR_PTE)

#define CONFIG_SYS_SCCR	0

#define CONFIG_SYS_RCCR	0




#define CONFIG_SYS_BR0_PRELIM	((CONFIG_SYS_FLASH0_BASE & BRx_BA_MSK) |\
			 BRx_PS_16			|\
			 BRx_MS_GPCM_P			|\
			 BRx_V)

#define CONFIG_SYS_OR0_PRELIM	(MEG_TO_AM(CONFIG_SYS_FLASH0_SIZE)	|\
			 ORxG_CSNT			|\
			 ORxG_ACS_DIV1			|\
			 ORxG_SCY_5_CLK			|\
			 ORxG_TRLX			|\
			 ORxG_EHTR)



#define CONFIG_SYS_BR2_PRELIM	((CONFIG_SYS_SDRAM0_BASE & BRx_BA_MSK) |\
			 BRx_PS_64			|\
			 BRx_MS_SDRAM_P			|\
			 BRx_V)

#define CONFIG_SYS_BR3_PRELIM	((CONFIG_SYS_SDRAM0_BASE & BRx_BA_MSK) |\
			 BRx_PS_64			|\
			 BRx_MS_SDRAM_P			|\
			 BRx_V)

#if (CONFIG_SYS_SDRAM0_SIZE == 64)
#define CONFIG_SYS_OR2_PRELIM	(MEG_TO_AM(CONFIG_SYS_SDRAM0_SIZE)	|\
			 ORxS_BPD_4			|\
			 ORxS_ROWST_PBI0_A8		|\
			 ORxS_NUMR_12)
#else
#error "INVALID SDRAM CONFIGURATION"
#endif


#define SDRAM_SPD_ADDR 0x50

#if (CONFIG_SYS_SDRAM0_SIZE == 64)
#define CONFIG_SYS_PSDMR	(PSDMR_RFEN	      |\
			 PSDMR_SDAM_A14_IS_A5 |\
			 PSDMR_BSMA_A14_A16   |\
			 PSDMR_SDA10_PBI0_A9  |\
			 PSDMR_RFRC_7_CLK     |\
			 PSDMR_PRETOACT_3W    |\
			 PSDMR_ACTTORW_2W     |\
			 PSDMR_LDOTOPRE_1C    |\
			 PSDMR_WRC_1C	      |\
			 PSDMR_CL_2)
#else
#error "INVALID SDRAM CONFIGURATION"
#endif

#if (CONFIG_8260_CLKIN >= (60 * 1000 * 1000))
#define CONFIG_SYS_MPTPR	MPTPR_PTP_DIV64
#elif (CONFIG_8260_CLKIN >= (30 * 1000 * 1000))
#define CONFIG_SYS_MPTPR	MPTPR_PTP_DIV32
#else
#warning "Unconfigured bus clock freq: check CONFIG_SYS_MPTPR and CONFIG_SYS_PSRT are OK"
#define CONFIG_SYS_MPTPR	MPTPR_PTP_DIV32
#endif
#define CONFIG_SYS_PSRT	14



#if (defined(CONFIG_SYS_FLASH1_BASE) && defined(CONFIG_SYS_FLASH1_SIZE))

#  define CONFIG_SYS_BR6_PRELIM  ((CONFIG_SYS_FLASH1_BASE & BRx_BA_MSK) |\
			   BRx_PS_16			  |\
			   BRx_MS_GPCM_P		  |\
			   BRx_V)

#  define CONFIG_SYS_OR6_PRELIM  (MEG_TO_AM(CONFIG_SYS_FLASH1_SIZE)  |\
			   ORxG_CSNT		       |\
			   ORxG_ACS_DIV1	       |\
			   ORxG_SCY_5_CLK	       |\
			   ORxG_TRLX		       |\
			   ORxG_EHTR)
#endif /* (defined(CONFIG_SYS_FLASH1_BASE) && defined(CONFIG_SYS_FLASH1_SIZE)) */

#define BOOTFLAG_COLD	0x01	/* Normal Power-On: Boot from FLASH  */
#define BOOTFLAG_WARM	0x02	/* Software reboot		     */

#endif	/* __CONFIG_H */
