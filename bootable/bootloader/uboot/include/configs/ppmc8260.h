

#ifndef __CONFIG_H
#define __CONFIG_H


/* What is the oscillator's (UX2) frequency in Hz? */
#define CONFIG_8260_CLKIN  (66 * 1000 * 1000)

#define CONFIG_SYS_PPMC_MODCK_H 0x05

#define CONFIG_SYS_PPMC_BOOT_LOW 1

#define CONFIG_SYS_FLASH0_BASE 0xFE000000
#define CONFIG_SYS_FLASH0_SIZE 16

#define CONFIG_SYS_SDRAM0_BASE 0x00000000
#define CONFIG_SYS_SDRAM0_SIZE 128

#define CONFIG_SYS_SDRAM1_BASE 0x08000000
#define CONFIG_SYS_SDRAM1_SIZE 128

#define CONFIG_SYS_SDRAM2_BASE 0x38000000
#define CONFIG_SYS_SDRAM2_SIZE 16

#define CONFIG_SYS_MAILBOX_BASE 0x32000000
#define CONFIG_SYS_MAILBOX_SIZE 8192


#define CONFIG_SYS_IOSELECT_BASE 0xE0000000
#define CONFIG_SYS_IOSELECT_SIZE 32


#define CONFIG_SYS_LED_BASE 0xF1000000



#define CONFIG_CONS_ON_SMC	1	/* define if console on SMC */
#undef	CONFIG_CONS_ON_SCC		/* define if console on SCC */
#undef	CONFIG_CONS_NONE		/* define if console on neither */
#define CONFIG_CONS_INDEX	1	/* which SMC/SCC channel for console */


#undef	CONFIG_ETHER_ON_SCC		/* define if ethernet on SCC	*/
#define CONFIG_ETHER_ON_FCC		/* define if ethernet on FCC	*/
#undef	CONFIG_ETHER_NONE		/* define if ethernet on neither */
#define CONFIG_ETHER_INDEX	2	/* which SCC/FCC channel for ethernet */
#define CONFIG_MII			/* MII PHY management	*/
#define CONFIG_BITBANGMII		/* bit-bang MII PHY management	*/
#define MDIO_PORT	2	/* Port C */
#define MDIO_DECLARE	volatile ioport_t *iop = ioport_addr ( \
				(immap_t *) CONFIG_SYS_IMMR, MDIO_PORT )
#define MDC_DECLARE	MDIO_DECLARE

#define MDIO_ACTIVE	(iop->pdir |=  0x00400000)
#define MDIO_TRISTATE	(iop->pdir &= ~0x00400000)
#define MDIO_READ	((iop->pdat &  0x00400000) != 0)

#define MDIO(bit)	if(bit) iop->pdat |=  0x00400000; \
			else	iop->pdat &= ~0x00400000

#define MDC(bit)	if(bit) iop->pdat |=  0x00200000; \
			else	iop->pdat &= ~0x00200000

#define MIIDELAY	udelay(1)


#define CONFIG_ENV_IN_OWN_SECT	1

/* Define to allow the user to overwrite serial and ethaddr */
#define CONFIG_ENV_OVERWRITE

/* What should the console's baud rate be? */
#define CONFIG_BAUDRATE		9600

/* Ethernet MAC address */

#define CONFIG_ETHADDR		00:a0:1e:90:2b:00

#define CONFIG_MISC_INIT_R

/* Set to a positive value to delay for running BOOTCOMMAND */
#define CONFIG_BOOTDELAY	5	/* autoboot after 5 seconds */

#if 0
# define CONFIG_AUTOBOOT_KEYED
# define CONFIG_AUTOBOOT_PROMPT \
	"Autobooting in %d seconds, press \" \" to stop\n", bootdelay
# define CONFIG_AUTOBOOT_STOP_STR	" "
# undef CONFIG_AUTOBOOT_DELAY_STR
# define DEBUG_BOOTKEYS		0
#endif

#undef	CONFIG_BOOT_ROOT_INITRD		/* Use ram disk for the root file system */
#define	CONFIG_BOOT_ROOT_NFS		/* Use a NFS mounted root file system */

#ifdef CONFIG_BOOT_ROOT_INITRD
#define CONFIG_BOOTCOMMAND \
	"version;" \
	"echo;" \
	"bootp;" \
	"setenv bootargs root=/dev/ram0 rw " \
	"ip=${ipaddr}:${serverip}:${gatewayip}:${netmask}:${hostname}::off;" \
	"bootm"
#endif /* CONFIG_BOOT_ROOT_INITRD */

#ifdef CONFIG_BOOT_ROOT_NFS
#define CONFIG_BOOTCOMMAND \
	"version;" \
	"echo;" \
	"bootp;" \
	"setenv bootargs root=/dev/nfs rw nfsroot=${serverip}:${rootpath} " \
	"ip=${ipaddr}:${serverip}:${gatewayip}:${netmask}:${hostname}::off;" \
	"bootm"
#endif /* CONFIG_BOOT_ROOT_NFS */


#define CONFIG_BOOTP_SUBNETMASK
#define CONFIG_BOOTP_GATEWAY
#define CONFIG_BOOTP_HOSTNAME
#define CONFIG_BOOTP_BOOTPATH
#define CONFIG_BOOTP_BOOTFILESIZE
#define CONFIG_BOOTP_DNS


/* undef this to save memory */
#define CONFIG_SYS_LONGHELP

/* Monitor Command Prompt */
#define CONFIG_SYS_PROMPT		"=> "


#include <config_cmd_default.h>

#define CONFIG_CMD_ELF
#define CONFIG_CMD_ASKENV
#define CONFIG_CMD_REGINFO
#define CONFIG_CMD_MEMTEST
#define CONFIG_CMD_MII
#define CONFIG_CMD_IMMAP

#undef CONFIG_CMD_KGDB


/* Where do the internal registers live? */
#define CONFIG_SYS_IMMR		0xf0000000


#define CONFIG_MPC8260		1	/* This is an MPC8260 CPU   */
#define CONFIG_PPMC8260		1	/* on an Wind River PPMC8260 Board  */
#define CONFIG_CPM2		1	/* Has a CPM2 */

#if defined(CONFIG_CMD_KGDB)
#  define CONFIG_SYS_CBSIZE		1024	/* Console I/O Buffer Size	     */
#else
#  define CONFIG_SYS_CBSIZE		256	/* Console I/O Buffer Size	     */
#endif

/* Print Buffer Size */
#define CONFIG_SYS_PBSIZE	  (CONFIG_SYS_CBSIZE + sizeof(CONFIG_SYS_PROMPT)+16)

#define CONFIG_SYS_MAXARGS		32	/* max number of command args	*/

#define CONFIG_SYS_BARGSIZE		CONFIG_SYS_CBSIZE /* Boot Argument Buffer Size	   */

#define CONFIG_SYS_LOAD_ADDR		0x140000   /* default load address */
#define CONFIG_SYS_HZ			1000	/* decrementer freq: 1 ms ticks */

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


#if defined(CONFIG_ETHER_ON_SCC) && (CONFIG_ETHER_INDEX == 1)
#define CONFIG_SYS_CMXSCR_VALUE       (CMXSCR_RS1CS_CLK11  |\
				CMXSCR_TS1CS_CLK12)

#elif defined(CONFIG_ETHER_ON_FCC) && (CONFIG_ETHER_INDEX == 2)
#define CONFIG_SYS_CMXFCR_MASK		(CMXFCR_FC2|CMXFCR_RF2CS_MSK|CMXFCR_TF2CS_MSK)
#define CONFIG_SYS_CMXFCR_VALUE	(CMXFCR_RF2CS_CLK13|CMXFCR_TF2CS_CLK14)
#define CONFIG_SYS_CPMFCR_RAMTYPE	0
#define CONFIG_SYS_FCC_PSMR		(FCC_PSMR_FDE | FCC_PSMR_LPB)
#endif	/* CONFIG_ETHER_INDEX */

#define CONFIG_SYS_FLASH_BASE	CONFIG_SYS_FLASH0_BASE
#define CONFIG_SYS_FLASH_SIZE	CONFIG_SYS_FLASH0_SIZE
#define CONFIG_SYS_SDRAM_BASE	CONFIG_SYS_SDRAM0_BASE
#define CONFIG_SYS_SDRAM_SIZE	(CONFIG_SYS_SDRAM0_SIZE + CONFIG_SYS_SDRAM1_SIZE)

#if defined(CONFIG_SYS_PPMC_BOOT_LOW)
#  define  CONFIG_SYS_PPMC_HRCW_BOOT_FLAGS  (HRCW_CIP | HRCW_BMS)
#else
#  define  CONFIG_SYS_PPMC_HRCW_BOOT_FLAGS  (0)
#endif /* defined(CONFIG_SYS_PPMC_BOOT_LOW) */

/* get the HRCW ISB field from CONFIG_SYS_IMMR */
#define CONFIG_SYS_PPMC_HRCW_IMMR	( ((CONFIG_SYS_IMMR & 0x10000000) >> 10) | \
				  ((CONFIG_SYS_IMMR & 0x01000000) >>  7) | \
				  ((CONFIG_SYS_IMMR & 0x00100000) >>  4) )

#define CONFIG_SYS_HRCW_MASTER		( HRCW_EBM				| \
				  HRCW_BPS11				| \
				  HRCW_L2CPC10				| \
				  HRCW_DPPC00				| \
				  CONFIG_SYS_PPMC_HRCW_IMMR			| \
				  HRCW_MMR00				| \
				  HRCW_LBPC00				| \
				  HRCW_APPC10				| \
				  HRCW_CS10PC00				| \
				  (CONFIG_SYS_PPMC_MODCK_H & HRCW_MODCK_H1111) | \
				  CONFIG_SYS_PPMC_HRCW_BOOT_FLAGS )

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

#ifndef CONFIG_SYS_MONITOR_BASE
#define CONFIG_SYS_MONITOR_BASE	0x0ff80000
#endif

#if (CONFIG_SYS_MONITOR_BASE < CONFIG_SYS_FLASH_BASE)
#  define CONFIG_SYS_RAMBOOT
#endif

#define CONFIG_SYS_MONITOR_LEN		(256 << 10)	/* Reserve 374 kB for Monitor	*/
#define CONFIG_SYS_MALLOC_LEN		(128 << 10)	/* Reserve 128 kB for malloc()	*/

#define CONFIG_SYS_BOOTMAPSZ		(8 << 20)	/* Initial Memory map for Linux */


#define CONFIG_SYS_FLASH_CFI		1	/* Flash is CFI conformant		*/
#define CONFIG_FLASH_CFI_DRIVER	1	/* Use the common driver		*/
#define CONFIG_SYS_MAX_FLASH_SECT	128	/* max number of sectors on one chip	*/
#define CONFIG_SYS_MAX_FLASH_BANKS	1	/* max number of memory banks		*/
#define CONFIG_SYS_FLASH_INCREMENT	0	/* there is only one bank		*/
#define CONFIG_SYS_FLASH_PROTECTION	1	/* use hardware protection		*/
#define CONFIG_SYS_FLASH_USE_BUFFER_WRITE 1    /* use buffered writes (20x faster)     */


#ifndef CONFIG_SYS_RAMBOOT

#  define CONFIG_ENV_IS_IN_FLASH	1
#  ifdef CONFIG_ENV_IN_OWN_SECT
#    define CONFIG_ENV_ADDR	(CONFIG_SYS_MONITOR_BASE + 0x40000)
#    define CONFIG_ENV_SECT_SIZE	0x40000
#  else
#    define CONFIG_ENV_ADDR (CONFIG_SYS_FLASH_BASE + CONFIG_SYS_MONITOR_LEN - CONFIG_ENV_SECT_SIZE)
#    define CONFIG_ENV_SIZE	0x1000	/* Total Size of Environment Sector	*/
#    define CONFIG_ENV_SECT_SIZE	0x40000 /* see README - env sect real size	*/
#  endif /* CONFIG_ENV_IN_OWN_SECT */

#else
#  define CONFIG_ENV_IS_IN_FLASH	1
#  define CONFIG_ENV_ADDR		(CONFIG_SYS_FLASH_BASE + 0x40000)
#define CONFIG_ENV_SIZE		0x1000
#  define CONFIG_ENV_SECT_SIZE	0x40000
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

#define CONFIG_SYS_BCR		(BCR_EBM      |\
			 0x30000000)


#define CONFIG_SYS_SIUMCR	(SIUMCR_ESE	 |\
			 SIUMCR_DPPC00	 |\
			 SIUMCR_L2CPC10	 |\
			 SIUMCR_LBPC00	 |\
			 SIUMCR_APPC10	 |\
			 SIUMCR_CS10PC00 |\
			 SIUMCR_BCTLC00	 |\
			 SIUMCR_MMR00)


#define CONFIG_SYS_SYPCR	(SYPCR_SWTC |\
			 SYPCR_BMT  |\
			 SYPCR_PBME |\
			 SYPCR_LBME |\
			 SYPCR_SWRI |\
			 SYPCR_SWP)

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
			 BRx_PS_32			|\
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

#define CONFIG_SYS_BR3_PRELIM	((CONFIG_SYS_SDRAM1_BASE & BRx_BA_MSK) |\
			 BRx_PS_64			|\
			 BRx_MS_SDRAM_P			|\
			 BRx_V)


#define CONFIG_SYS_OR2_PRELIM	(MEG_TO_AM(CONFIG_SYS_SDRAM0_SIZE)	|\
			 ORxS_BPD_4			|\
			 ORxS_ROWST_PBI0_A7		|\
			 ORxS_NUMR_13)

#define CONFIG_SYS_OR3_PRELIM	(MEG_TO_AM(CONFIG_SYS_SDRAM1_SIZE)	|\
			 ORxS_BPD_4			|\
			 ORxS_ROWST_PBI0_A7		|\
			 ORxS_NUMR_13)



#define CONFIG_SYS_PSDMR	(PSDMR_RFEN	      |\
			 PSDMR_SDAM_A14_IS_A5 |\
			 PSDMR_BSMA_A13_A15   |\
			 PSDMR_SDA10_PBI0_A9  |\
			 PSDMR_RFRC_7_CLK     |\
			 PSDMR_PRETOACT_3W    |\
			 PSDMR_ACTTORW_2W     |\
			 PSDMR_LDOTOPRE_1C    |\
			 PSDMR_WRC_1C	      |\
			 PSDMR_EAMUX	      |\
			 PSDMR_CL_2)


#define CONFIG_SYS_PSRT	0x0e
#define CONFIG_SYS_MPTPR	MPTPR_PTP_DIV32




#define CONFIG_SYS_BR4_PRELIM	((CONFIG_SYS_SDRAM2_BASE & BRx_BA_MSK) |\
			 BRx_PS_32			|\
			 BRx_DECC_NONE			|\
			 BRx_MS_SDRAM_L			|\
			 BRx_V)


#define CONFIG_SYS_OR4_PRELIM	(MEG_TO_AM(CONFIG_SYS_SDRAM2_SIZE)	|\
			 ORxS_BPD_4			|\
			 ORxS_ROWST_PBI0_A10		|\
			 ORxS_NUMR_12)



#define CONFIG_SYS_LSDMR	(PSDMR_RFEN	      |\
			 PSDMR_SDAM_A13_IS_A5 |\
			 PSDMR_BSMA_A15_A17   |\
			 PSDMR_SDA10_PBI0_A11 |\
			 PSDMR_RFRC_7_CLK     |\
			 PSDMR_PRETOACT_2W    |\
			 PSDMR_ACTTORW_2W     |\
			 PSDMR_BL	      |\
			 PSDMR_LDOTOPRE_1C    |\
			 PSDMR_WRC_1C	      |\
			 PSDMR_CL_2)

#define CONFIG_SYS_LSRT	0x0e




#define CONFIG_SYS_BR5_PRELIM	((CONFIG_SYS_MAILBOX_BASE & BRx_BA_MSK) |\
			 BRx_PS_8			 |\
			 BRx_DECC_NONE			 |\
			 BRx_MS_GPCM_P			 |\
			 BRx_V)

#define CONFIG_SYS_OR5_PRELIM ((P2SZ_TO_AM(CONFIG_SYS_MAILBOX_SIZE) & ~0x80000000) |\
			 ORxG_ACS_DIV2				     |\
			 ORxG_SCY_15_CLK			     |\
			 ORxG_TRLX				     |\
			 ORxG_EHTR)



#define CONFIG_SYS_BR6_PRELIM	((CONFIG_SYS_IOSELECT_BASE & BRx_BA_MSK) |\
			   BRx_PS_16			  |\
			   BRx_MS_GPCM_P		  |\
			   BRx_V)


#define CONFIG_SYS_OR6_PRELIM (MEG_TO_AM(CONFIG_SYS_IOSELECT_SIZE) |\
			 ORxG_ACS_DIV2		     |\
			 ORxG_SCY_15_CLK	     |\
			 ORxG_TRLX		     |\
			 ORxG_EHTR)



#ifdef CONFIG_SYS_LED_BASE

#define CONFIG_SYS_BR7_PRELIM	((CONFIG_SYS_LED_BASE & BRx_BA_MSK)	 |\
			   BRx_PS_8			 |\
			   BRx_DECC_NONE		 |\
			   BRx_MS_GPCM_P		 |\
			   BRx_V)

#define CONFIG_SYS_OR7_PRELIM	(ORxG_AM_MSK		       |\
			 ORxG_CSNT		       |\
			 ORxG_ACS_DIV1		       |\
			 ORxG_SCY_15_CLK	       |\
			 ORxG_TRLX		       |\
			 ORxG_EHTR)
#endif /* CONFIG_SYS_LED_BASE */

#define BOOTFLAG_COLD	0x01	/* Normal Power-On: Boot from FLASH  */
#define BOOTFLAG_WARM	0x02	/* Software reboot		     */

#endif	/* __CONFIG_H */
