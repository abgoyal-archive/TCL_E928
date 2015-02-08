




#ifndef __CONFIG_H
#define __CONFIG_H

/* This define must be before the core.h include */
#define CONFIG_DB64360		1	/* this is an DB64360 board	*/

#ifndef __ASSEMBLY__
#include "../board/Marvell/include/core.h"
#endif

/*-----------------------------------------------------*/
/*    #include "../board/db64360/local.h"	      */
#ifndef __LOCAL_H
#define __LOCAL_H

/* first ethernet */
#define CONFIG_ETHADDR		64:36:00:00:00:01
											     /* next two ethernet hwaddrs */
#define CONFIG_HAS_ETH1
#define CONFIG_ETH1ADDR		64:36:00:00:00:02

#define CONFIG_ENV_OVERWRITE
#endif	/* __CONFIG_H */


#define CONFIG_74xx			/* we have a 750FX (override local.h) */

#define CONFIG_DB64360		1	/* this is an DB64360 board	*/

#define CONFIG_BAUDRATE		115200	/* console baudrate = 115000	*/
#undef CONFIG_ECC	 /* enable ECC support */
#define CONFIG_MV64360_ECC

/* which initialization functions to call for this board */
#define CONFIG_MISC_INIT_R     /* initialize the icache L1 */
#define CONFIG_BOARD_EARLY_INIT_F

#define CONFIG_SYS_BOARD_NAME		"DB64360"
#define CONFIG_IDENT_STRING	"Marvell DB64360 (1.1)"

/*#define CONFIG_SYS_HUSH_PARSER */
#undef CONFIG_SYS_HUSH_PARSER

#define CONFIG_SYS_PROMPT_HUSH_PS2	"> "


#define CONFIG_MPSC_PORT	0

/* to change the default ethernet port, use this define (options: 0, 1, 2) */
#define CONFIG_NET_MULTI
#define MV_ETH_DEVS 2

/* #undef CONFIG_ETHER_PORT_MII	 */
#if 0
#define CONFIG_BOOTDELAY	-1	/* autoboot disabled		*/
#else
#define CONFIG_BOOTDELAY	3	/* autoboot after 5 seconds	*/
#endif
#define CONFIG_ZERO_BOOTDELAY_CHECK


#undef	CONFIG_BOOTARGS
/*#define CONFIG_PREBOOT	"echo;echo Type \\\"run flash_nfs\\\" to mount root filesystem over NFS;echo" */

/* ronen - autoboot using tftp */
#if (CONFIG_BOOTDELAY >= 0)
#define CONFIG_BOOTCOMMAND	"tftpboot 0x400000 uImage;\
 setenv bootargs ${bootargs} ${bootargs_root} nfsroot=${serverip}:${rootpath} \
 ip=${ipaddr}:${serverip}${bootargs_end};  bootm 0x400000; "

#define CONFIG_BOOTARGS "console=ttyS0,115200"

#endif

/* ronen - the u-boot.bin should be ~0x30000 bytes */
#define CONFIG_EXTRA_ENV_SETTINGS \
     "burn_uboot_sep= tftp 100000 u-boot.bin;protect off all;era FFF00000 FFF4ffff; \
cp.b 100000 FFF00000 0x40000;protect on 1:0-4;\0" \
      "burn_uboot_dep= tftp 100000 u-boot.bin;protect off all;era FFF00000 FFF7ffff; \
cp.b 100000 FFF00000 0x40000;protect on 1:0-7;\0" \
      "bootargs_root=root=/dev/nfs rw\0" \
      "bootargs_end=:::DB64360:eth0:none \0"\
      "ethprime=mv_enet0\0"\
      "standalone=fsload 0x400000 uImage;setenv bootargs ${bootargs} root=/dev/mtdblock/0 rw \
ip=${ipaddr}:${serverip}${bootargs_end}; bootm 0x400000;\0"

/* --------------------------------------------------------------------------------------------------------------- */
/* New bootcommands for Marvell DB64360 c 2002 Ingo Assmus */

#define CONFIG_IPADDR		10.2.40.90

#define CONFIG_SERIAL		"No. 1"
#define CONFIG_SERVERIP		10.2.1.126
#define CONFIG_ROOTPATH /mnt/yellow_dog_mini


#define CONFIG_TESTDRAMDATA	y
#define CONFIG_TESTDRAMADDRESS	n
#define CONFIG_TESETDRAMWALK	n

/* --------------------------------------------------------------------------------------------------------------- */

#define CONFIG_LOADS_ECHO	0	/* echo off for serial download */
#define CONFIG_SYS_LOADS_BAUD_CHANGE		/* allow baudrate changes	*/

#undef	CONFIG_WATCHDOG			/* watchdog disabled		*/
#undef	CONFIG_ALTIVEC			/* undef to disable		*/

#define CONFIG_BOOTP_SUBNETMASK
#define CONFIG_BOOTP_GATEWAY
#define CONFIG_BOOTP_HOSTNAME
#define CONFIG_BOOTP_BOOTPATH
#define CONFIG_BOOTP_BOOTFILESIZE


/* No command line, one static partition, whole device */
#undef CONFIG_CMD_MTDPARTS
#define CONFIG_JFFS2_DEV		"nor1"
#define CONFIG_JFFS2_PART_SIZE		0xFFFFFFFF
#define CONFIG_JFFS2_PART_OFFSET	0x00000000

/* mtdparts command line support */



#include <config_cmd_default.h>

#define CONFIG_CMD_ASKENV
#define CONFIG_CMD_I2C
#define CONFIG_CMD_EEPROM
#define CONFIG_CMD_CACHE
#define CONFIG_CMD_JFFS2
#define CONFIG_CMD_PCI
#define CONFIG_CMD_NET


#define CONFIG_SYS_I2C_EEPROM_ADDR_LEN 1
#define CONFIG_SYS_I2C_MULTI_EEPROMS
#define CONFIG_SYS_I2C_SPEED	40000		/* I2C speed default */

/* #define CONFIG_SYS_GT_DUAL_CPU	 also for JTAG even with one cpu */
#define CONFIG_SYS_LONGHELP			/* undef to save memory		*/
#define CONFIG_SYS_PROMPT	"=> "		/* Monitor Command Prompt	*/
#if defined(CONFIG_CMD_KGDB)
#define CONFIG_SYS_CBSIZE	1024		/* Console I/O Buffer Size	*/
#else
#define CONFIG_SYS_CBSIZE	256		/* Console I/O Buffer Size	*/
#endif
#define CONFIG_SYS_PBSIZE (CONFIG_SYS_CBSIZE+sizeof(CONFIG_SYS_PROMPT)+16) /* Print Buffer Size */
#define CONFIG_SYS_MAXARGS	16		/* max number of command args	*/
#define CONFIG_SYS_BARGSIZE	CONFIG_SYS_CBSIZE	/* Boot Argument Buffer Size	*/

/*#define CONFIG_SYS_MEMTEST_START	0x00400000	 memtest works on	*/
/*#define CONFIG_SYS_MEMTEST_END		0x00C00000	 4 ... 12 MB in DRAM	*/
/*#define CONFIG_SYS_MEMTEST_END		0x07c00000	 4 ... 124 MB in DRAM	*/

#define CONFIG_SYS_DRAM_TEST
#if defined(CONFIG_SYS_DRAM_TEST)
#define CONFIG_SYS_MEMTEST_START		0x00400000	/* memtest works on	*/
/* #define CONFIG_SYS_MEMTEST_END		0x00C00000	 4 ... 12 MB in DRAM	*/
#define CONFIG_SYS_MEMTEST_END		0x07c00000	/* 4 ... 124 MB in DRAM */
#define CONFIG_SYS_DRAM_TEST_DATA
#define CONFIG_SYS_DRAM_TEST_ADDRESS
#define CONFIG_SYS_DRAM_TEST_WALK
#endif /* CONFIG_SYS_DRAM_TEST */

#undef CONFIG_DISPLAY_MEMMAP		/* at the end of the bootprocess show the memory map */
#undef CONFIG_SYS_DISPLAY_DIMM_SPD_CONTENT	/* show SPD content during boot */

#define CONFIG_SYS_LOAD_ADDR		0x00400000	/* default load address */

#define CONFIG_SYS_HZ			1000		/* decr freq: 1ms ticks */
/*ronen - this the Sys clock (cpu bus,internal dram and SDRAM) */
#define CONFIG_SYS_BUS_HZ		133000000	/* 133 MHz (CPU = 5*Bus = 666MHz)		*/
#define CONFIG_SYS_BUS_CLK		CONFIG_SYS_BUS_HZ

#define CONFIG_SYS_DDR_SDRAM_CYCLE_COUNT_LOP 7 /* define the SDRAM cycle count */
#define CONFIG_SYS_DDR_SDRAM_CYCLE_COUNT_ROP 50 /* for 400MHZ -> 5.0 ns, for 133MHZ -> 7.50 ns */

/*ronen - this is the Tclk (MV64360 core) */
#define CONFIG_SYS_TCLK		133000000


#define CONFIG_SYS_BAUDRATE_TABLE	{ 9600, 19200, 38400, 57600, 115200, 230400 }

#define CONFIG_SYS_750FX_HID0		0x8000c084
#define CONFIG_SYS_750FX_HID1		0x54800000
#define CONFIG_SYS_750FX_HID2		0x00000000



#define CONFIG_SYS_INIT_RAM_LOCK
#define CONFIG_SYS_INIT_RAM_ADDR	0x40000000 /* unused memory region */
#define CONFIG_SYS_INIT_RAM_END	0x1000
#define CONFIG_SYS_GBL_DATA_SIZE	128  /* size in bytes reserved for init data */
#define CONFIG_SYS_GBL_DATA_OFFSET	(CONFIG_SYS_INIT_RAM_END - CONFIG_SYS_GBL_DATA_SIZE)

#define RELOCATE_INTERNAL_RAM_ADDR
#ifdef RELOCATE_INTERNAL_RAM_ADDR
	#define CONFIG_SYS_INTERNAL_RAM_ADDR	0xf8000000
#endif

#define CONFIG_SYS_SDRAM_BASE		0x00000000
/* Dummies for BAT 4-7 */
#define CONFIG_SYS_SDRAM1_BASE		0x10000000	/* each 256 MByte */
#define CONFIG_SYS_SDRAM2_BASE		0x20000000
#define CONFIG_SYS_SDRAM3_BASE		0x30000000
#define CONFIG_SYS_SDRAM4_BASE		0x40000000
#define CONFIG_SYS_FLASH_BASE			0xfff00000

#define CONFIG_SYS_DFL_BOOTCS_BASE	0xff800000
#define CONFIG_VERY_BIG_RAM		/* we will use up to 256M memory for cause we are short of BATS*/

#define BRIDGE_REG_BASE_BOOTM 0xfbe00000 /* this paramaters are used when booting the linux kernel */
#define UART_BASE_BOOTM	      0xfbb00000 /* in order to be sync with the kernel parameters. */
#define PCI0_IO_BASE_BOOTM    0xfd000000

#define CONFIG_SYS_RESET_ADDRESS		0xfff00100
#define CONFIG_SYS_MONITOR_LEN		(256 << 10)	/* Reserve 256 kB for Monitor */
#define CONFIG_SYS_MONITOR_BASE		CONFIG_SYS_FLASH_BASE
#define CONFIG_SYS_MALLOC_LEN		(256 << 10)	/* Reserve 256 kB for malloc */

/* areas to map different things with the GT in physical space */
#define CONFIG_SYS_DRAM_BANKS		4

/* What to put in the bats. */
#define CONFIG_SYS_MISC_REGION_BASE	0xf0000000

/* Peripheral Device section */

/*******************************************************/
/* We have on the db64360 Board :		   */
/* GT-Chipset Register Area				*/
/* GT-Chipset internal SRAM 256k		    */
/* SRAM on external device module		   */
/* Real time clock on external device module	  */
/* dobble UART on external device module	 */
/* Data flash on external device module		    */
/* Boot flash on external device module		    */
/*******************************************************/
#define CONFIG_SYS_DFL_GT_REGS		0x14000000				/* boot time GT_REGS */
#define	 CONFIG_SYS_DB64360_RESET_ADDR 0x14000000				/* After power on Reset the DB64360 is here */

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#define CONFIG_SYS_GT_REGS		0xf1000000				/* GT Registers will be mapped here */
#define CONFIG_SYS_DEV_BASE		0xfc000000				/* GT Devices CS start here */

#define CONFIG_SYS_DEV0_SPACE		CONFIG_SYS_DEV_BASE				/* DEV_CS0 device modul sram */
#define CONFIG_SYS_DEV1_SPACE		(CONFIG_SYS_DEV0_SPACE + CONFIG_SYS_DEV0_SIZE)	/* DEV_CS1 device modul real time clock (rtc) */
#define CONFIG_SYS_DEV2_SPACE		(CONFIG_SYS_DEV1_SPACE + CONFIG_SYS_DEV1_SIZE)	/* DEV_CS2 device modul doubel uart (duart) */
#define CONFIG_SYS_DEV3_SPACE		(CONFIG_SYS_DEV2_SPACE + CONFIG_SYS_DEV2_SIZE)	/* DEV_CS3 device modul large flash */

#define CONFIG_SYS_DEV0_SIZE		 _8M					/* db64360 sram	 @ 0xfc00.0000 */
#define CONFIG_SYS_DEV1_SIZE		 _8M					/* db64360 rtc	 @ 0xfc80.0000 */
#define CONFIG_SYS_DEV2_SIZE		_16M					/* db64360 duart @ 0xfd00.0000 */
#define CONFIG_SYS_DEV3_SIZE		_16M					/* db64360 flash @ 0xfe00.0000 */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/* Reset values for Port behavior (8bit/ 32bit, etc.) only corrected by device width */
#define CONFIG_SYS_DEV0_PAR		0x8FEFFFFF				/* 32Bit  sram */
#define CONFIG_SYS_DEV1_PAR		0x8FCFFFFF				/* 8Bit	 rtc */
#define CONFIG_SYS_DEV2_PAR		0x8FCFFFFF				/* 8Bit duart */
#define CONFIG_SYS_8BIT_BOOT_PAR	0x8FCFFFFF				/* 8Bit flash */
#define CONFIG_SYS_32BIT_BOOT_PAR	0x8FEFFFFF				/* 32Bit flash */

	/*   c	  4    a      8	    2	  4    1      c		*/
	/* 33 22|2222|22 22|111 1|11 11|1 1  |	  |		*/
	/* 10 98|7654|32 10|987 6|54 32|1 098|7 654|3 210	*/
	/* 11|00|0100|10 10|100|0 00|10 0|100 0|001 1|100	*/
	/*  3| 0|.... ..| 2| 4 |  0 |  4 |  8  |  3  | 4	*/


/* ronen - update MPP Control MV64360*/
#define CONFIG_SYS_MPP_CONTROL_0	0x02222222
#define CONFIG_SYS_MPP_CONTROL_1	0x11333011
#define CONFIG_SYS_MPP_CONTROL_2	0x40431111
#define CONFIG_SYS_MPP_CONTROL_3	0x00000044

/*# define CONFIG_SYS_SERIAL_PORT_MUX	0x00000102	 0=hiZ	1=MPSC0 2=ETH 0 and 2 RMII */


# define CONFIG_SYS_GPP_LEVEL_CONTROL	0x2c600000	/* 1111 1001 0000 1111 1100 0000 0000 0000*/
							/* gpp[31]		gpp[30]		gpp[29]		gpp[28] */
				/* gpp[27]			gpp[24]*/
							/* gpp[19:14] */

/* setup new config_value for MV64360 DDR-RAM !! */
# define CONFIG_SYS_SDRAM_CONFIG	0x58200400	/* 0x1400  copied from Dink32 bzw. VxWorks*/

#define CONFIG_SYS_DUART_IO		CONFIG_SYS_DEV2_SPACE
#define CONFIG_SYS_DUART_CHAN		1		/* channel to use for console */
#define CONFIG_SYS_INIT_CHAN1
#define CONFIG_SYS_INIT_CHAN2

#define SRAM_BASE		CONFIG_SYS_DEV0_SPACE
#define SRAM_SIZE		0x00100000		/* 1 MB of sram */



#define PCI_HOST_ADAPTER 0		/* configure ar pci adapter	*/
#define PCI_HOST_FORCE	1		/* configure as pci host	*/
#define PCI_HOST_AUTO	2		/* detected via arbiter enable	*/

#define CONFIG_PCI			/* include pci support		*/
#define CONFIG_PCI_HOST PCI_HOST_FORCE	/* select pci host function	*/
#define CONFIG_PCI_PNP			/* do pci plug-and-play		*/
#define CONFIG_EEPRO100			/* ronen - Support for Intel 82557/82559/82559ER chips */

/* PCI MEMORY MAP section */
#define CONFIG_SYS_PCI0_MEM_BASE	0x80000000
#define CONFIG_SYS_PCI0_MEM_SIZE	_128M
#define CONFIG_SYS_PCI1_MEM_BASE	0x88000000
#define CONFIG_SYS_PCI1_MEM_SIZE	_128M

#define CONFIG_SYS_PCI0_0_MEM_SPACE	(CONFIG_SYS_PCI0_MEM_BASE)
#define CONFIG_SYS_PCI1_0_MEM_SPACE	(CONFIG_SYS_PCI1_MEM_BASE)

/* PCI I/O MAP section */
#define CONFIG_SYS_PCI0_IO_BASE	0xfa000000
#define CONFIG_SYS_PCI0_IO_SIZE	_16M
#define CONFIG_SYS_PCI1_IO_BASE	0xfb000000
#define CONFIG_SYS_PCI1_IO_SIZE	_16M

#define CONFIG_SYS_PCI0_IO_SPACE	(CONFIG_SYS_PCI0_IO_BASE)
#define CONFIG_SYS_PCI0_IO_SPACE_PCI	(CONFIG_SYS_PCI0_IO_BASE) /* ronen we want phy=bus 0x00000000 */
#define CONFIG_SYS_PCI1_IO_SPACE	(CONFIG_SYS_PCI1_IO_BASE)
#define CONFIG_SYS_PCI1_IO_SPACE_PCI	(CONFIG_SYS_PCI1_IO_BASE) /* ronen we want phy=bus 0x00000000 */

#if defined (CONFIG_750CX)
#define CONFIG_SYS_PCI_IDSEL 0x0
#else
#define CONFIG_SYS_PCI_IDSEL 0x30
#endif


/* SDRAM */
#define CONFIG_SYS_IBAT0L (CONFIG_SYS_SDRAM_BASE | BATL_PP_RW | BATL_CACHEINHIBIT)
#define CONFIG_SYS_IBAT0U (CONFIG_SYS_SDRAM_BASE | BATU_BL_256M | BATU_VS | BATU_VP)
#define CONFIG_SYS_DBAT0L (CONFIG_SYS_SDRAM_BASE | BATL_PP_RW | BATL_CACHEINHIBIT | BATL_GUARDEDSTORAGE)
#define CONFIG_SYS_DBAT0U CONFIG_SYS_IBAT0U

/* init ram */
#define CONFIG_SYS_IBAT1L  (CONFIG_SYS_INIT_RAM_ADDR | BATL_PP_RW | BATL_MEMCOHERENCE)
#define CONFIG_SYS_IBAT1U  (CONFIG_SYS_INIT_RAM_ADDR | BATU_BL_256K | BATU_VS | BATU_VP)
#define CONFIG_SYS_DBAT1L  CONFIG_SYS_IBAT1L
#define CONFIG_SYS_DBAT1U  CONFIG_SYS_IBAT1U

/* PCI0, PCI1 in one BAT */
#define CONFIG_SYS_IBAT2L BATL_NO_ACCESS
#define CONFIG_SYS_IBAT2U CONFIG_SYS_DBAT2U
#define CONFIG_SYS_DBAT2L (CONFIG_SYS_PCI0_MEM_BASE | BATL_CACHEINHIBIT | BATL_PP_RW | BATL_GUARDEDSTORAGE)
#define CONFIG_SYS_DBAT2U (CONFIG_SYS_PCI0_MEM_BASE | BATU_BL_256M | BATU_VS | BATU_VP)

/* GT regs, bootrom, all the devices, PCI I/O */
#define CONFIG_SYS_IBAT3L (CONFIG_SYS_MISC_REGION_BASE | BATL_CACHEINHIBIT | BATL_PP_RW)
#define CONFIG_SYS_IBAT3U (CONFIG_SYS_MISC_REGION_BASE | BATU_VS | BATU_VP | BATU_BL_256M)
#define CONFIG_SYS_DBAT3L (CONFIG_SYS_MISC_REGION_BASE | BATL_CACHEINHIBIT | BATL_PP_RW | BATL_GUARDEDSTORAGE)
#define CONFIG_SYS_DBAT3U CONFIG_SYS_IBAT3U

/* I2C addresses for the two DIMM SPD chips */
#define DIMM0_I2C_ADDR	0x56
#define DIMM1_I2C_ADDR	0x54

#define CONFIG_SYS_BOOTMAPSZ		(8<<20) /* Initial Memory map for Linux */

#define CONFIG_SYS_MAX_FLASH_BANKS	2	/* max number of memory banks	*/
#define CONFIG_SYS_MAX_FLASH_SECT	67	/* max number of sectors on one chip */

#define CONFIG_SYS_EXTRA_FLASH_DEVICE	DEVICE3 /* extra flash at device 3 */
#define CONFIG_SYS_EXTRA_FLASH_WIDTH	4	/* 32 bit */
#define CONFIG_SYS_BOOT_FLASH_WIDTH	1	/* 8 bit */

#define CONFIG_SYS_FLASH_ERASE_TOUT	120000	/* Timeout for Flash Erase (in ms) */
#define CONFIG_SYS_FLASH_WRITE_TOUT	500	/* Timeout for Flash Write (in ms) */
#define CONFIG_SYS_FLASH_LOCK_TOUT	500	/* Timeout for Flash Lock (in ms) */
#define CONFIG_SYS_FLASH_CFI		1

#define CONFIG_ENV_IS_IN_FLASH	1
#define CONFIG_ENV_SIZE		0x1000	/* Total Size of Environment Sector */
#define CONFIG_ENV_SECT_SIZE	0x10000
#define CONFIG_ENV_ADDR	      0xFFF78000 /* Marvell 8-Bit Bootflash last sector */
/* #define CONFIG_ENV_ADDR	   (CONFIG_SYS_FLASH_BASE+CONFIG_SYS_MONITOR_LEN-CONFIG_ENV_SECT_SIZE) */

#define CONFIG_SYS_CACHELINE_SIZE	32	/* For all MPC74xx CPUs		 */
#if defined(CONFIG_CMD_KGDB)
#define CONFIG_SYS_CACHELINE_SHIFT	5	/* log base 2 of the above value */
#endif


#define CONFIG_SYS_L2


#if defined (CONFIG_750CX) || defined (CONFIG_750FX)
#define L2_INIT 0
#else

#define L2_INIT		0
#endif

#define L2_ENABLE	(L2_INIT | L2CR_L2E)

#define BOOTFLAG_COLD	0x01		/* Normal Power-On: Boot from FLASH */
#define BOOTFLAG_WARM	0x02		/* Software reboot		    */

#define CONFIG_SYS_BOARD_ASM_INIT	1

#endif	/* __CONFIG_H */
