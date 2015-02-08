

#ifndef __CONFIG_H
#define __CONFIG_H


#define CONFIG_MPC860		1	/* This is a MPC860 CPU		*/
#define CONFIG_MBX		1	/* ...on an MBX module		*/

#define	CONFIG_8xx_CONS_SMC1	1	/* Console is on SMC1		*/
#undef	CONFIG_8xx_CONS_SMC2
#undef	CONFIG_8xx_CONS_NONE
#define CONFIG_BAUDRATE		9600
/* Define this to use the PCI bus */
#undef CONFIG_USE_PCI

#define	CONFIG_CLOCKS_IN_MHZ	1	/* clocks passsed to Linux in MHz */
#define CONFIG_8xx_GCLK_FREQ    (50000000UL)
#if 1
#define CONFIG_BOOTDELAY	-1	/* autoboot disabled		*/
#else
#define CONFIG_BOOTDELAY	5	/* autoboot after 5 seconds	*/
#endif
#define CONFIG_BOOTCOMMAND	"bootm 20000" /* autoboot command	*/

#define CONFIG_BOOTARGS		"root=/dev/nfs rw "			\
				"nfsroot=10.0.0.2:/opt/eldk/ppc_8xx "	\
				"nfsaddrs=10.0.0.99:10.0.0.2"

#define CONFIG_LOADS_ECHO	1	/* echo on for serial download	*/
#undef	CONFIG_SYS_LOADS_BAUD_CHANGE   /* don't allow baudrate change	*/

#undef	CONFIG_WATCHDOG			/* watchdog disabled		*/


#define CONFIG_BOOTP_BOOTFILESIZE
#define CONFIG_BOOTP_BOOTPATH
#define CONFIG_BOOTP_GATEWAY
#define CONFIG_BOOTP_HOSTNAME


#define CONFIG_CMD_NET
#define CONFIG_CMD_DFL
#define CONFIG_CMD_SDRAM
#define CONFIG_CMD_PCMCIA
#define CONFIG_CMD_IDE


#define CONFIG_DOS_PARTITION

#define CONFIG_SYS_LONGHELP			/* undef to save memory		*/
#define CONFIG_SYS_PROMPT	"=> "		/* Monitor Command Prompt	*/
#undef	CONFIG_SYS_HUSH_PARSER			/* Hush parse for U-Boot	*/
#ifdef	CONFIG_SYS_HUSH_PARSER
#define CONFIG_SYS_PROMPT_HUSH_PS2	"> "
#endif
#if defined(CONFIG_CMD_KGDB)
#define CONFIG_SYS_CBSIZE	1024		/* Console I/O Buffer Size	*/
#else
#define CONFIG_SYS_CBSIZE	256		/* Console I/O Buffer Size	*/
#endif
#define CONFIG_SYS_PBSIZE (CONFIG_SYS_CBSIZE+sizeof(CONFIG_SYS_PROMPT)+16) /* Print Buffer Size */
#define CONFIG_SYS_MAXARGS	16		/* max number of command args	*/
#define CONFIG_SYS_BARGSIZE	CONFIG_SYS_CBSIZE	/* Boot Argument Buffer Size	*/

#define CONFIG_SYS_MEMTEST_START	0x0400000	/* memtest works on	*/
#define CONFIG_SYS_MEMTEST_END		0x0C00000	/* 4 ... 12 MB in DRAM	*/

#define CONFIG_SYS_LOAD_ADDR		0x100000	/* default load address */

#define CONFIG_SYS_HZ		1000		/* decrementer freq: 1 ms ticks */

#define CONFIG_SYS_BAUDRATE_TABLE	{ 9600, 19200, 38400, 57600, 115200 }


#define CONFIG_SYS_IMMR		0xFA200000 /* Internal Memory Mapped Register*/
#define CONFIG_SYS_NVRAM_BASE		0xFA000000 /* NVRAM			     */
#define CONFIG_SYS_NVRAM_OR		0xffe00000 /* w/o speed dependent flags!!    */
#define CONFIG_SYS_CSR_BASE		0xFA100000 /* Control/Status Registers	     */
#define CONFIG_SYS_PCIMEM_BASE		0x80000000 /* PCI I/O and Memory Spaces	     */
#define CONFIG_SYS_PCIMEM_OR		0xA0000108
#define CONFIG_SYS_PCIBRIDGE_BASE	0xFA210000 /* PCI-Bus Bridge Registers	     */
#define CONFIG_SYS_PCIBRIDGE_OR	0xFFFF0108

#define CONFIG_SYS_INIT_RAM_ADDR	CONFIG_SYS_IMMR
#define CONFIG_SYS_INIT_RAM_END	0x2f00	/* End of used area in DPRAM	*/
#define CONFIG_SYS_GBL_DATA_SIZE	64  /* size in bytes reserved for initial data */
#define CONFIG_SYS_GBL_DATA_OFFSET	(CONFIG_SYS_INIT_RAM_END - CONFIG_SYS_GBL_DATA_SIZE)
#define CONFIG_SYS_INIT_VPD_SIZE	256 /* size in bytes reserved for vpd buffer */
#define CONFIG_SYS_INIT_VPD_OFFSET	(CONFIG_SYS_GBL_DATA_OFFSET - CONFIG_SYS_INIT_VPD_SIZE)
#define CONFIG_SYS_INIT_SP_OFFSET	(CONFIG_SYS_INIT_VPD_OFFSET-8)

#define CONFIG_SYS_DPRAMVPD		(CONFIG_SYS_INIT_VPD_OFFSET - 0x2000)

#define CONFIG_SYS_SDRAM_BASE		0x00000000
#define CONFIG_SYS_FLASH_BASE		0xfe000000
#ifdef	DEBUG
#define CONFIG_SYS_MONITOR_LEN		(256 << 10)	/* Reserve 256 kB for Monitor	*/
#else
#define CONFIG_SYS_MONITOR_LEN		(256 << 10)	/* Reserve 256 kB for Monitor	*/
#endif
#undef	CONFIG_SYS_MONITOR_BASE	/* 0x200000	   to run U-Boot from RAM */
#define CONFIG_SYS_MONITOR_BASE	CONFIG_SYS_FLASH_BASE
#define CONFIG_SYS_MALLOC_LEN		(128 << 10)	/* Reserve 128 kB for malloc()	*/

#define CONFIG_SYS_BOOTMAPSZ		(8 << 20)	/* Initial Memory map for Linux */

#define CONFIG_SYS_MAX_FLASH_BANKS	1	/* max number of memory banks		*/
#define CONFIG_SYS_MAX_FLASH_SECT	16	/* max number of sectors on one chip	*/

#define CONFIG_SYS_FLASH_ERASE_TOUT	120000	/* Timeout for Flash Erase (in ms)	*/
#define CONFIG_SYS_FLASH_WRITE_TOUT	500	/* Timeout for Flash Write (in ms)	*/

#define CONFIG_ENV_IS_IN_NVRAM	1	/* turn on NVRAM env feature */
#define CONFIG_ENV_ADDR		(CONFIG_SYS_NVRAM_BASE + 0x1000)
#define CONFIG_ENV_SIZE		0x1000

#define CONFIG_SYS_CACHELINE_SIZE	16	/* For all MPC8xx CPUs			*/
#if defined(CONFIG_CMD_KGDB)
#define CONFIG_SYS_CACHELINE_SHIFT	4	/* log base 2 of the above value	*/
#endif

#if defined(CONFIG_WATCHDOG)
#define CONFIG_SYS_SYPCR	(SYPCR_SWTC | SYPCR_BMT | SYPCR_BME | SYPCR_SWF | \
			 SYPCR_SWE  | SYPCR_SWRI| SYPCR_SWP)
#else
#define CONFIG_SYS_SYPCR	(SYPCR_SWTC | SYPCR_BMT | SYPCR_BME | SYPCR_SWF)
#endif

/* #define CONFIG_SYS_SIUMCR	(SIUMCR_DBGC11 | SIUMCR_DPC | SIUMCR_MLRC10 | SIUMCR_SEME) */
#define CONFIG_SYS_SIUMCR	(SIUMCR_DBGC11 | SIUMCR_DPC | SIUMCR_MLRC11 | SIUMCR_SEME | SIUMCR_BSC )

#define CONFIG_SYS_TBSCR	(TBSCR_REFA | TBSCR_REFB | TBSCR_TBF)

#define CONFIG_SYS_PISCR	(PISCR_PS | PISCR_PITF | PISCR_PTE)

#define CONFIG_SYS_PLPRCR	(PLPRCR_SPLSS | PLPRCR_TEXPS | PLPRCR_TMIST)

#define SCCR_MASK	(SCCR_RTDIV | SCCR_RTSEL)
#define CONFIG_SYS_SCCR	SCCR_TBS

#define CONFIG_SYS_PCMCIA_MEM_ADDR	(0xE0000000)
#define CONFIG_SYS_PCMCIA_MEM_SIZE	( 64 << 20 )
#define CONFIG_SYS_PCMCIA_DMA_ADDR	(0xE4000000)
#define CONFIG_SYS_PCMCIA_DMA_SIZE	( 64 << 20 )
#define CONFIG_SYS_PCMCIA_ATTRB_ADDR	(0xE8000000)
#define CONFIG_SYS_PCMCIA_ATTRB_SIZE	( 64 << 20 )
#define CONFIG_SYS_PCMCIA_IO_ADDR	(0xEC000000)
#define CONFIG_SYS_PCMCIA_IO_SIZE	( 64 << 20 )

#define CONFIG_SYS_PCMCIA_INTERRUPT	SIU_LEVEL6

#define CONFIG_PCMCIA_SLOT_A	1



#define CONFIG_IDE_8xx_PCCARD	1	/* Use IDE with PC Card Adapter */

#undef	CONFIG_IDE_8xx_DIRECT		/* Direct IDE	 not supported	*/
#undef	CONFIG_IDE_LED			/* LED	 for ide not supported	*/
#undef	CONFIG_IDE_RESET		/* reset for ide not supported	*/

#define CONFIG_SYS_IDE_MAXBUS		1	/* max. 1 IDE bus		*/
#define CONFIG_SYS_IDE_MAXDEVICE	1	/* max. 1 drive per IDE bus	*/

#define CONFIG_SYS_ATA_IDE0_OFFSET	0x0000

#define CONFIG_SYS_ATA_BASE_ADDR	CONFIG_SYS_PCMCIA_MEM_ADDR

/* Offset for data I/O */
#define CONFIG_SYS_ATA_DATA_OFFSET	(CONFIG_SYS_PCMCIA_MEM_SIZE + 0x320)

/* Offset for normal register accesses */
#define CONFIG_SYS_ATA_REG_OFFSET	(2 * CONFIG_SYS_PCMCIA_MEM_SIZE + 0x320)

/* Offset for alternate registers */
#define CONFIG_SYS_ATA_ALT_OFFSET	0x0100

#define CONFIG_SYS_DER 0

#define BOOTFLAG_COLD	0x01		/* Normal Power-On: Boot from FLASH	*/
#define BOOTFLAG_WARM	0x02		/* Software reboot			*/

#endif	/* __CONFIG_H */
