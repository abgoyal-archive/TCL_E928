


#ifndef __CONFIG_H
#define __CONFIG_H

#define CONFIG_PXA250		1	/* This is an PXA250 CPU            */
#define CONFIG_INNOKOM		1	/* on an Auerswald Innokom board    */

#undef CONFIG_USE_IRQ			/* we don't need IRQ/FIQ stuff      */
					/* for timer/console/ethernet       */

/* we will never enable dcache, because we have to setup MMU first */
#define CONFIG_SYS_NO_DCACHE


#define CONFIG_PXA_SERIAL
#define CONFIG_FFUART		1	/* we use FFUART on CSB226 */

/* allow to overwrite serial and ethaddr */
#define CONFIG_ENV_OVERWRITE

#define CONFIG_BAUDRATE		19200
#define CONFIG_MISC_INIT_R	1	/* we have a misc_init_r() function */


#define CONFIG_BOOTP_BOOTFILESIZE
#define CONFIG_BOOTP_BOOTPATH
#define CONFIG_BOOTP_GATEWAY
#define CONFIG_BOOTP_HOSTNAME



#define CONFIG_CMD_ASKENV
#define CONFIG_CMD_BDI
#define CONFIG_CMD_CACHE
#define CONFIG_CMD_DHCP
#define CONFIG_CMD_ECHO
#define CONFIG_CMD_SAVEENV
#define CONFIG_CMD_FLASH
#define CONFIG_CMD_I2C
#define CONFIG_CMD_IMI
#define CONFIG_CMD_LOADB
#define CONFIG_CMD_MEMORY
#define CONFIG_CMD_NET
#define CONFIG_CMD_RUN


#define CONFIG_BOOTDELAY	3
/* #define CONFIG_BOOTARGS	"root=/dev/nfs ip=bootp console=ttyS0,19200" */
#define CONFIG_BOOTARGS		"console=ttyS0,19200"
#define CONFIG_ETHADDR		FF:FF:FF:FF:FF:FF
#define CONFIG_NETMASK		255.255.255.0
#define CONFIG_IPADDR		192.168.1.56
#define CONFIG_SERVERIP		192.168.1.2
#define CONFIG_BOOTCOMMAND	"bootm 0x40000"
#define CONFIG_SHOW_BOOT_PROGRESS

#define CONFIG_CMDLINE_TAG	1


#define CONFIG_SYS_MALLOC_LEN		(256*1024)
#define CONFIG_SYS_GBL_DATA_SIZE	128		/* size in bytes reserved for initial data */

#define CONFIG_SYS_LONGHELP				/* undef to save memory         */
#define CONFIG_SYS_PROMPT		"uboot> "	/* Monitor Command Prompt       */
#define CONFIG_SYS_CBSIZE		256		/* Console I/O Buffer Size      */
#define CONFIG_SYS_PBSIZE (CONFIG_SYS_CBSIZE+sizeof(CONFIG_SYS_PROMPT)+16) /* Print Buffer Size */
#define CONFIG_SYS_MAXARGS		16		/* max number of command args   */
#define CONFIG_SYS_BARGSIZE		CONFIG_SYS_CBSIZE	/* Boot Argument Buffer Size    */

#define CONFIG_SYS_MEMTEST_START	0xa0400000      /* memtest works on     */
#define CONFIG_SYS_MEMTEST_END         0xa0800000      /* 4 ... 8 MB in DRAM   */

#define CONFIG_SYS_LOAD_ADDR           0xa3000000      /* load kernel to this address   */

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

#define CONFIG_HARD_I2C			1
#define CONFIG_SYS_I2C_SPEED			50000
#define CONFIG_SYS_I2C_SLAVE			0xfe

#define CONFIG_ENV_IS_IN_EEPROM		1

#define CONFIG_ENV_OFFSET			0x00	/* environment starts here  */
#define CONFIG_ENV_SIZE			1024	/* 1 KiB                    */
#define CONFIG_SYS_I2C_EEPROM_ADDR		0x50	/* A0 = 0 (hardwired)       */
#define CONFIG_SYS_EEPROM_PAGE_WRITE_BITS	5	/* 5 bits = 32 octets       */
#define CONFIG_SYS_EEPROM_PAGE_WRITE_DELAY_MS	15	/* between stop and start   */
#define CONFIG_SYS_I2C_EEPROM_ADDR_LEN		2	/* length of address        */
#define CONFIG_SYS_EEPROM_SIZE			4096	/* size in bytes            */
#define CONFIG_SYS_I2C_INIT_BOARD		1	/* board has it's own init  */

#define CONFIG_NET_MULTI
#define CONFIG_SMC91111		1
#define CONFIG_SMC91111_BASE		0x14000000 /* chip select 5         */
#undef  CONFIG_SMC_USE_32_BIT		           /* 16 bit bus access     */
#undef  CONFIG_SMC_91111_EXT_PHY		   /* we use internal phy   */
#define CONFIG_SMC_AUTONEG_TIMEOUT	10	   /* timeout 10 seconds    */
#undef  CONFIG_SHOW_ACTIVITY
#define CONFIG_NET_RETRY_COUNT		10	   /* # of retries          */

#define CONFIG_STACKSIZE        (128*1024)      /* regular stack */
#ifdef  CONFIG_USE_IRQ
#define CONFIG_STACKSIZE_IRQ    (4*1024)        /* IRQ stack */
#define CONFIG_STACKSIZE_FIQ    (4*1024)        /* FIQ stack */
#endif

#define CONFIG_NR_DRAM_BANKS	1		/* we have 1 bank of DRAM   */
#define PHYS_SDRAM_1		0xa0000000	/* SDRAM Bank #1            */
#define PHYS_SDRAM_1_SIZE	0x04000000	/* 64 MB                    */

#define PHYS_FLASH_1		0x00000000	/* Flash Bank #1            */
#define PHYS_FLASH_SIZE		0x01000000	/* 16 MB                    */

#define CONFIG_SYS_DRAM_BASE		0xa0000000	/* RAM starts here          */
#define CONFIG_SYS_DRAM_SIZE		0x04000000

#define CONFIG_SYS_FLASH_BASE          PHYS_FLASH_1

/* development flash */
#define CONFIG_MTD_INNOKOM_16MB	1
#undef CONFIG_MTD_INNOKOM_64MB

/* production flash */

/* No command line, one static partition, whole device */
#undef CONFIG_CMD_MTDPARTS
#define CONFIG_JFFS2_DEV		"nor0"
#define CONFIG_JFFS2_PART_SIZE		0xFFFFFFFF
#define CONFIG_JFFS2_PART_OFFSET	0x00000000

/* mtdparts command line support */
/* Note: fake mtd_id used, no linux mtd map file */

/* development flash */

/* production flash */

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


#define CONFIG_SYS_MAX_FLASH_BANKS     1	/* max number of memory banks       */
#define CONFIG_SYS_MAX_FLASH_SECT	128	/* max number of sect. on one chip  */

/* timeout values are in ticks */
#define CONFIG_SYS_FLASH_ERASE_TOUT    (2*CONFIG_SYS_HZ) /* Timeout for Flash Erase       */
#define CONFIG_SYS_FLASH_WRITE_TOUT    (2*CONFIG_SYS_HZ) /* Timeout for Flash Write       */

#endif  /* __CONFIG_H */
