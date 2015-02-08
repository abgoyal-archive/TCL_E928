


#ifndef __CONFIG_H
#define __CONFIG_H

#define DEBUG 1

#define CONFIG_PXA250		1	/* This is an PXA250 CPU            */
#define CONFIG_CSB226		1	/* on a CSB226 board                */

#undef CONFIG_USE_IRQ			/* we don't need IRQ/FIQ stuff      */
					/* for timer/console/ethernet       */

/* we will never enable dcache, because we have to setup MMU first */
#define CONFIG_SYS_NO_DCACHE


#define CONFIG_PXA_SERIAL
#define CONFIG_FFUART		1	/* we use FFUART on CSB226          */

/* allow to overwrite serial and ethaddr */
#define CONFIG_ENV_OVERWRITE

#define CONFIG_BAUDRATE		19200
#undef  CONFIG_MISC_INIT_R		/* not used yet                     */


#define CONFIG_BOOTP_BOOTFILESIZE
#define CONFIG_BOOTP_BOOTPATH
#define CONFIG_BOOTP_GATEWAY
#define CONFIG_BOOTP_HOSTNAME


#include <config_cmd_default.h>

#define CONFIG_CMD_BDI
#define CONFIG_CMD_LOADB
#define CONFIG_CMD_IMI
#define CONFIG_CMD_FLASH
#define CONFIG_CMD_MEMORY
#define CONFIG_CMD_NET
#define CONFIG_CMD_SAVEENV
#define CONFIG_CMD_RUN
#define CONFIG_CMD_ASKENV
#define CONFIG_CMD_ECHO
#define CONFIG_CMD_DHCP
#define CONFIG_CMD_CACHE


#define CONFIG_BOOTDELAY	3
#define CONFIG_BOOTARGS		"console=ttyS0,19200 ip=192.168.1.10,192.168.1.5,,255,255,255,0,csb root=/dev/nfs, ether=0,0x08000000,eth0"
#define CONFIG_ETHADDR		FF:FF:FF:FF:FF:FF
#define CONFIG_NETMASK		255.255.255.0
#define CONFIG_IPADDR		192.168.1.56
#define CONFIG_SERVERIP		192.168.1.5
#define CONFIG_BOOTCOMMAND	"bootm 0x40000"
#define CONFIG_SHOW_BOOT_PROGRESS

#define CONFIG_CMDLINE_TAG	1

#if defined(CONFIG_CMD_KGDB)
#define CONFIG_KGDB_BAUDRATE	19200		/* speed to run kgdb serial port */
#define CONFIG_KGDB_SER_INDEX	2		/* which serial port to use */
#endif


#define CONFIG_SYS_MALLOC_LEN		(128*1024)
#define CONFIG_SYS_GBL_DATA_SIZE	128		/* size in bytes reserved for initial data */

#define CONFIG_SYS_LONGHELP				/* undef to save memory         */
#define CONFIG_SYS_PROMPT		"uboot> "	/* Monitor Command Prompt       */
#define CONFIG_SYS_CBSIZE		128		/* Console I/O Buffer Size      */
#define CONFIG_SYS_PBSIZE (CONFIG_SYS_CBSIZE+sizeof(CONFIG_SYS_PROMPT)+16) /* Print Buffer Size */
#define CONFIG_SYS_MAXARGS		16		/* max number of command args   */
#define CONFIG_SYS_BARGSIZE		CONFIG_SYS_CBSIZE	/* Boot Argument Buffer Size    */

#define CONFIG_SYS_MEMTEST_START	0xa0400000      /* memtest works on     */
#define CONFIG_SYS_MEMTEST_END         0xa0800000      /* 4 ... 8 MB in DRAM   */

#define CONFIG_SYS_LOAD_ADDR           0xa3000000	/* default load address */
						/* RS: where is this documented? */
						/* RS: is this where U-Boot is  */
						/* RS: relocated to in RAM?      */

#define CONFIG_SYS_HZ			1000
						/* RS: the oscillator is actually 3680130?? */
#define CONFIG_SYS_CPUSPEED            0x141           /* set core clock to 200/200/100 MHz */
						/* 0101000001 */
						/*      ^^^^^ Memory Speed 99.53 MHz         */
						/*    ^^      Run Mode Speed = 2x Mem Speed  */
						/* ^^         Turbo Mode Sp. = 1x Run M. Sp. */

#define CONFIG_SYS_MONITOR_LEN		0x20000		/* 128 KiB */

						/* valid baudrates */
#define CONFIG_SYS_BAUDRATE_TABLE      { 9600, 19200, 38400, 57600, 115200 }

#define CONFIG_NET_MULTI
#define CONFIG_CS8900
#define CONFIG_CS8900_BUS32
#define CONFIG_CS8900_BASE	0x08000000

#define CONFIG_STACKSIZE        (128*1024)      /* regular stack */
#ifdef  CONFIG_USE_IRQ
#define CONFIG_STACKSIZE_IRQ    (4*1024)        /* IRQ stack */
#define CONFIG_STACKSIZE_FIQ    (4*1024)        /* FIQ stack */
#endif

#define CONFIG_NR_DRAM_BANKS	1		/* we have 1 bank of DRAM   */
#define PHYS_SDRAM_1		0xa0000000	/* SDRAM Bank #1            */
#define PHYS_SDRAM_1_SIZE	0x02000000	/* 32 MB                    */

#define PHYS_FLASH_1		0x00000000	/* Flash Bank #1            */
#define PHYS_FLASH_SIZE		0x02000000	/* 32 MB                    */

#define CONFIG_SYS_DRAM_BASE		0xa0000000	/* RAM starts here          */
#define CONFIG_SYS_DRAM_SIZE		0x02000000

#define CONFIG_SYS_FLASH_BASE          PHYS_FLASH_1

# if 0
/* FIXME: switch to _documented_ registers */
#define CONFIG_SYS_GPSR0_VAL       0x03008000
#define CONFIG_SYS_GPSR1_VAL       0xC0028282
#define CONFIG_SYS_GPSR2_VAL       0x0001C000

#define CONFIG_SYS_GPCR0_VAL       0x00800004
#define CONFIG_SYS_GPCR1_VAL       0x30002000
#define CONFIG_SYS_GPCR2_VAL       0x00000100

#define CONFIG_SYS_GPDR0_VAL       0x03808004
#define CONFIG_SYS_GPDR1_VAL       0xF002A282
#define CONFIG_SYS_GPDR2_VAL       0x0001C200

#define CONFIG_SYS_GAFR0_L_VAL     0x80000000
#define CONFIG_SYS_GAFR0_U_VAL     0x001A8010
#define CONFIG_SYS_GAFR1_L_VAL     0x60088058
#define CONFIG_SYS_GAFR1_U_VAL     0x00000008
#define CONFIG_SYS_GAFR2_L_VAL     0xA0000000
#define CONFIG_SYS_GAFR2_U_VAL     0x00000002


/* FIXME: set GPIO_RER/FER */

#define CONFIG_SYS_PSSR_VAL		0x37

#define CONFIG_SYS_MSC0_VAL		0x25b825b8 /* flash banks                   */

#define CONFIG_SYS_MSC1_VAL		0x123C593C /* TDM switch, DSP               */

#define CONFIG_SYS_MSC2_VAL		0x123C6CDC /* extra bus, LAN controller     */

/* use the configuration above but disable partition 0 */
#define CONFIG_SYS_MDCNFG_VAL		0x000019c8

#define CONFIG_SYS_MDREFR_VAL		0x0081D018

#define CONFIG_SYS_MDMRS_VAL		0x00020022

#define CONFIG_SYS_MECR_VAL		0x00000000
#define CONFIG_SYS_MCMEM0_VAL		0x00000000
#define CONFIG_SYS_MCMEM1_VAL		0x00000000
#define CONFIG_SYS_MCATT0_VAL		0x00000000
#define CONFIG_SYS_MCATT1_VAL		0x00000000
#define CONFIG_SYS_MCIO0_VAL		0x00000000
#define CONFIG_SYS_MCIO1_VAL		0x00000000
#endif

#define CONFIG_SYS_GPSR0_VAL		0xFFFFFFFF
#define CONFIG_SYS_GPSR1_VAL		0xFFFFFFFF
#define CONFIG_SYS_GPSR2_VAL		0xFFFFFFFF
#define CONFIG_SYS_GPCR0_VAL		0x08022080
#define CONFIG_SYS_GPCR1_VAL		0x00000000
#define CONFIG_SYS_GPCR2_VAL		0x00000000
#define CONFIG_SYS_GPDR0_VAL		0xCD82A878
#define CONFIG_SYS_GPDR1_VAL		0xFCFFAB80
#define CONFIG_SYS_GPDR2_VAL		0x0001FFFF
#define CONFIG_SYS_GAFR0_L_VAL		0x80000000
#define CONFIG_SYS_GAFR0_U_VAL		0xA5254010
#define CONFIG_SYS_GAFR1_L_VAL		0x599A9550
#define CONFIG_SYS_GAFR1_U_VAL		0xAAA5AAAA
#define CONFIG_SYS_GAFR2_L_VAL		0xAAAAAAAA
#define CONFIG_SYS_GAFR2_U_VAL		0x00000002

/* FIXME: set GPIO_RER/FER */

#define CONFIG_SYS_PSSR_VAL        0x20


#define CONFIG_SYS_MSC0_VAL            0x2ef15af0
#define CONFIG_SYS_MSC1_VAL            0x00003ff4
#define CONFIG_SYS_MSC2_VAL            0x7ff07ff0
#define CONFIG_SYS_MDCNFG_VAL          0x09a909a9
#define CONFIG_SYS_MDREFR_VAL          0x038ff030
#define CONFIG_SYS_MDMRS_VAL           0x00220022

#define CONFIG_SYS_MECR_VAL        0x00000000
#define CONFIG_SYS_MCMEM0_VAL      0x00000000
#define CONFIG_SYS_MCMEM1_VAL      0x00000000
#define CONFIG_SYS_MCATT0_VAL      0x00000000
#define CONFIG_SYS_MCATT1_VAL      0x00000000
#define CONFIG_SYS_MCIO0_VAL       0x00000000
#define CONFIG_SYS_MCIO1_VAL       0x00000000

#define CSB226_USER_LED0	0x00000008
#define CSB226_USER_LED1	0x00000010
#define CSB226_USER_LED2	0x00000020


#define CONFIG_SYS_MAX_FLASH_BANKS     1	/* max number of memory banks       */
#define CONFIG_SYS_MAX_FLASH_SECT	128	/* max number of sect. on one chip  */

/* timeout values are in ticks */
#define CONFIG_SYS_FLASH_ERASE_TOUT    (2*CONFIG_SYS_HZ) /* Timeout for Flash Erase       */
#define CONFIG_SYS_FLASH_WRITE_TOUT    (2*CONFIG_SYS_HZ) /* Timeout for Flash Write       */

#define	CONFIG_ENV_IS_IN_FLASH	1
#define CONFIG_ENV_ADDR            (PHYS_FLASH_1 + 0x1C000)
					/* Addr of Environment Sector       */
#define CONFIG_ENV_SIZE            0x4000  /* Total Size of Environment Sector */

#endif  /* __CONFIG_H */
