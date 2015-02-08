
#ifndef __CONFIG_H
#define __CONFIG_H


/* for the AY-Revision which does not use the HRCW */
#define CONFIG_SYS_DEFAULT_IMMR	0x00010000

/* What is the oscillator's (UX2) frequency in Hz? */
#define CONFIG_8260_CLKIN  (66 * 1000 * 1000)

#define CONFIG_SYS_SBC_S2  0x04

#define CONFIG_SYS_SBC_MODCK_H 0x06

#define CONFIG_SYS_SBC_BOOT_LOW 1	/* only for HRCW */
#undef CONFIG_SYS_SBC_BOOT_LOW

#define CONFIG_SYS_FLASH0_BASE 0x80000000
#define CONFIG_SYS_FLASH0_SIZE 16

#define CONFIG_SYS_FLASH1_BASE 0
#define CONFIG_SYS_FLASH1_SIZE 0
#undef CONFIG_SYS_FLASH1_BASE
#undef CONFIG_SYS_FLASH1_SIZE

#define CONFIG_SYS_SDRAM0_BASE 0x00000000
#define CONFIG_SYS_SDRAM0_SIZE 64

#define CONFIG_SYS_SDRAM1_BASE 0x04000000
#define CONFIG_SYS_SDRAM1_SIZE 32

#define CONFIG_SYS_LED_BASE 0x00000000

#define CONFIG_CONS_ON_SMC          /* define if console on SMC */
#undef  CONFIG_CONS_ON_SCC          /* define if console on SCC */
#undef  CONFIG_CONS_NONE            /* define if console on neither */
#define CONFIG_CONS_INDEX    1      /* which SMC/SCC channel for console */

#undef  CONFIG_ETHER_ON_SCC           /* define if ethernet on SCC    */
#define CONFIG_ETHER_ON_FCC           /* define if ethernet on FCC    */
#undef  CONFIG_ETHER_NONE             /* define if ethernet on neither */
#define CONFIG_ETHER_INDEX      3     /* which SCC/FCC channel for ethernet */

#if ( CONFIG_ETHER_INDEX == 3 )

# define CONFIG_SYS_CMXFCR_MASK	(CMXFCR_FC3|CMXFCR_RF3CS_MSK|CMXFCR_TF3CS_MSK)
# define CONFIG_SYS_CMXFCR_VALUE	(CMXFCR_RF3CS_CLK15|CMXFCR_TF3CS_CLK16)
# define CONFIG_SYS_CPMFCR_RAMTYPE	0
/*#define CONFIG_SYS_FCC_PSMR		(FCC_PSMR_FDE|FCC_PSMR_LPB) */
# define CONFIG_SYS_FCC_PSMR		0

#else /* CONFIG_ETHER_INDEX */
# error "on RPX Super ethernet must be FCC3"
#endif /* CONFIG_ETHER_INDEX */

#define CONFIG_HARD_I2C         1	/* I2C with hardware support	*/
#define CONFIG_SYS_I2C_SPEED		400000	/* I2C speed and slave address	*/
#define CONFIG_SYS_I2C_SLAVE		0x7F


#define CONFIG_ENV_IN_OWN_SECT

/* Define to allow the user to overwrite serial and ethaddr */
#define CONFIG_ENV_OVERWRITE

/* What should the console's baud rate be? */
#define CONFIG_BAUDRATE         115200

/* Ethernet MAC address */
#define CONFIG_ETHADDR          08:00:22:50:70:63

#define CONFIG_IPADDR		192.168.1.99
#define CONFIG_SERVERIP         192.168.1.3

/* Set to a positive value to delay for running BOOTCOMMAND */
#define CONFIG_BOOTDELAY        -1

/* undef this to save memory */
#define CONFIG_SYS_LONGHELP

/* Monitor Command Prompt       */
#define CONFIG_SYS_PROMPT              "=> "


#define CONFIG_BOOTP_BOOTFILESIZE
#define CONFIG_BOOTP_BOOTPATH
#define CONFIG_BOOTP_GATEWAY
#define CONFIG_BOOTP_HOSTNAME


#include <config_cmd_default.h>

#define CONFIG_CMD_IMMAP
#define CONFIG_CMD_ASKENV
#define CONFIG_CMD_I2C
#define CONFIG_CMD_REGINFO

#undef CONFIG_CMD_KGDB


/* Where do the internal registers live? */
#define CONFIG_SYS_IMMR               0xF0000000

/* Where do the on board registers (CS4) live? */
#define CONFIG_SYS_REGS_BASE          0xFA000000


#define CONFIG_MPC8260          1       /* This is an MPC8260 CPU   */
#define CONFIG_RPXSUPER         1       /* on an Embedded Planet RPX Super Board  */
#define CONFIG_CPM2		1	/* Has a CPM2 */

#define CONFIG_BOARD_EARLY_INIT_F 1	/* Call board_early_init_f	*/
#define CONFIG_RESET_PHY_R	1	/* Call reset_phy()		*/

#if defined(CONFIG_CMD_KGDB)
#  define CONFIG_SYS_CBSIZE              1024       /* Console I/O Buffer Size      */
#else
#  define CONFIG_SYS_CBSIZE              256        /* Console I/O Buffer Size      */
#endif

/* Print Buffer Size */
#define CONFIG_SYS_PBSIZE        (CONFIG_SYS_CBSIZE + sizeof(CONFIG_SYS_PROMPT)+16)

#define CONFIG_SYS_MAXARGS       8            /* max number of command args   */

#define CONFIG_SYS_BARGSIZE      CONFIG_SYS_CBSIZE   /* Boot Argument Buffer Size    */

#define CONFIG_SYS_MEMTEST_START 0x04000000   /* memtest works on  */
#define CONFIG_SYS_MEMTEST_END   0x06000000   /* 64-96 MB in SDRAM */

#define	CONFIG_CLOCKS_IN_MHZ	1	/* clocks passsed to Linux in MHz */

#define CONFIG_SYS_LOAD_ADDR     0x100000     /* default load address */
#define CONFIG_SYS_HZ            1000         /* decrementer freq: 1 ms ticks */

/* valid baudrates */
#define CONFIG_SYS_BAUDRATE_TABLE      { 9600, 19200, 38400, 57600, 115200 }


#define CONFIG_SYS_FLASH_BASE    CONFIG_SYS_FLASH0_BASE
#define CONFIG_SYS_SDRAM_BASE    CONFIG_SYS_SDRAM0_BASE

#if defined(CONFIG_SYS_SBC_BOOT_LOW)
#  define  CONFIG_SYS_SBC_HRCW_BOOT_FLAGS  (HRCW_CIP | HRCW_BMS)
#else
#  define  CONFIG_SYS_SBC_HRCW_BOOT_FLAGS  (0)
#endif /* defined(CONFIG_SYS_SBC_BOOT_LOW) */

/* get the HRCW ISB field from CONFIG_SYS_IMMR */
#define CONFIG_SYS_SBC_HRCW_IMMR ( ((CONFIG_SYS_IMMR & 0x10000000) >> 10) |\
			    ((CONFIG_SYS_IMMR & 0x01000000) >> 7)  |\
			    ((CONFIG_SYS_IMMR & 0x00100000) >> 4) )

#define CONFIG_SYS_HRCW_MASTER (HRCW_BPS11                           |\
			 HRCW_DPPC11                          |\
			 CONFIG_SYS_SBC_HRCW_IMMR                    |\
			 HRCW_MMR00                           |\
			 HRCW_LBPC11                          |\
			 HRCW_APPC10                          |\
			 HRCW_CS10PC00                        |\
			 (CONFIG_SYS_SBC_MODCK_H & HRCW_MODCK_H1111) |\
			 CONFIG_SYS_SBC_HRCW_BOOT_FLAGS)

/* no slaves */
#define CONFIG_SYS_HRCW_SLAVE1 0
#define CONFIG_SYS_HRCW_SLAVE2 0
#define CONFIG_SYS_HRCW_SLAVE3 0
#define CONFIG_SYS_HRCW_SLAVE4 0
#define CONFIG_SYS_HRCW_SLAVE5 0
#define CONFIG_SYS_HRCW_SLAVE6 0
#define CONFIG_SYS_HRCW_SLAVE7 0

#define CONFIG_SYS_INIT_RAM_ADDR       CONFIG_SYS_IMMR
#define CONFIG_SYS_INIT_RAM_END        0x4000  /* End of used area in DPRAM    */
#define CONFIG_SYS_GBL_DATA_SIZE      128     /* bytes reserved for initial data */
#define CONFIG_SYS_GBL_DATA_OFFSET    (CONFIG_SYS_INIT_RAM_END - CONFIG_SYS_GBL_DATA_SIZE)
#define CONFIG_SYS_INIT_SP_OFFSET      CONFIG_SYS_GBL_DATA_OFFSET

#define CONFIG_SYS_MONITOR_BASE        (CONFIG_SYS_FLASH0_BASE + 0x00F00000)

#if (CONFIG_SYS_MONITOR_BASE < CONFIG_SYS_FLASH_BASE)
#  define CONFIG_SYS_RAMBOOT
#endif

#define CONFIG_SYS_MONITOR_LEN      (256 << 10)     /* Reserve 256 kB for Monitor   */
#define CONFIG_SYS_MALLOC_LEN       (128 << 10)     /* Reserve 128 kB for malloc()  */

#define CONFIG_SYS_BOOTMAPSZ        (8 << 20)       /* Initial Memory map for Linux */

#define CONFIG_SYS_MAX_FLASH_BANKS   1       /* max number of memory banks         */
#define CONFIG_SYS_MAX_FLASH_SECT    71      /* max number of sectors on one chip  */

#define CONFIG_SYS_FLASH_ERASE_TOUT  8000    /* Timeout for Flash Erase (in ms)    */
#define CONFIG_SYS_FLASH_WRITE_TOUT  1       /* Timeout for Flash Write (in ms)    */

#ifndef CONFIG_SYS_RAMBOOT
#  define CONFIG_ENV_IS_IN_FLASH  1

#  ifdef CONFIG_ENV_IN_OWN_SECT
#    define CONFIG_ENV_ADDR       (CONFIG_SYS_MONITOR_BASE + 0x40000)
#    define CONFIG_ENV_SECT_SIZE  0x40000
#  else
#    define CONFIG_ENV_ADDR (CONFIG_SYS_FLASH_BASE + CONFIG_SYS_MONITOR_LEN - CONFIG_ENV_SECT_SIZE)
#    define CONFIG_ENV_SIZE       0x1000  /* Total Size of Environment Sector */
#    define CONFIG_ENV_SECT_SIZE  0x10000 /* see README - env sect real size */
#  endif /* CONFIG_ENV_IN_OWN_SECT */
#else
#  define CONFIG_ENV_IS_IN_NVRAM  1
#  define CONFIG_ENV_ADDR         (CONFIG_SYS_MONITOR_BASE - 0x1000)
#  define CONFIG_ENV_SIZE         0x200
#endif /* CONFIG_SYS_RAMBOOT */

#define CONFIG_SYS_CACHELINE_SIZE      32      /* For MPC8260 CPU */

#if defined(CONFIG_CMD_KGDB)
#  define CONFIG_SYS_CACHELINE_SHIFT     5     /* log base 2 of the above value */
#endif

#define CONFIG_SYS_HID0_INIT   (/*HID0_ICE  |*/\
			 /*HID0_DCE  |*/\
			 HID0_ICFI |\
			 HID0_DCI  |\
			 HID0_IFEM |\
			 HID0_ABE)

#define CONFIG_SYS_HID0_FINAL  (/*HID0_ICE  |*/\
			 HID0_IFEM |\
			 HID0_ABE  |\
			 HID0_EMCP)
#define CONFIG_SYS_HID2        0

#define CONFIG_SYS_RMR         0

#define CONFIG_SYS_BCR         (BCR_EBM   |\
			 BCR_PLDP  |\
			 BCR_EAV   |\
			 BCR_NPQM0)


#define CONFIG_SYS_SIUMCR      (SIUMCR_L2CPC01 |\
			 SIUMCR_APPC10  |\
			 SIUMCR_CS10PC01)


#define CONFIG_SYS_SYPCR       (SYPCR_SWTC |\
			 SYPCR_BMT  |\
			 SYPCR_PBME |\
			 SYPCR_LBME |\
			 SYPCR_SWRI |\
			 SYPCR_SWP)

#define CONFIG_SYS_TMCNTSC     (TMCNTSC_SEC |\
			 TMCNTSC_ALR |\
			 TMCNTSC_TCF |\
			 TMCNTSC_TCE)

#define CONFIG_SYS_PISCR       (PISCR_PS  |\
			 PISCR_PTF |\
			 PISCR_PTE)

#define CONFIG_SYS_SCCR        (SCCR_DFBRG01)

#define CONFIG_SYS_RCCR        0


#define CONFIG_SYS_BR0_PRELIM  ((CONFIG_SYS_FLASH0_BASE & BRx_BA_MSK) |\
			 BRx_PS_64                      |\
			 BRx_DECC_NONE                  |\
			 BRx_MS_GPCM_P                  |\
			 BRx_V)

#define CONFIG_SYS_OR0_PRELIM  (MEG_TO_AM(CONFIG_SYS_FLASH0_SIZE)     |\
			 ORxG_CSNT                      |\
			 ORxG_ACS_DIV1                  |\
			 ORxG_SCY_6_CLK                 |\
			 ORxG_EHTR)

#define CONFIG_SYS_BR1_PRELIM  ((CONFIG_SYS_SDRAM0_BASE & BRx_BA_MSK) |\
			 BRx_PS_64                      |\
			 BRx_MS_SDRAM_P                 |\
			 BRx_V)

#define CONFIG_SYS_OR1_PRELIM  (MEG_TO_AM(CONFIG_SYS_SDRAM0_SIZE)     |\
			 ORxS_BPD_4                     |\
			 ORxS_ROWST_PBI0_A8             |\
			 ORxS_NUMR_12                   |\
			 ORxS_IBID)

#define CONFIG_SYS_PSDMR       0x014DA412
#define CONFIG_SYS_PSRT	0x79


#define CONFIG_SYS_BR2_PRELIM  ((CONFIG_SYS_SDRAM1_BASE & BRx_BA_MSK) |\
			 BRx_PS_32                      |\
			 BRx_MS_SDRAM_L                 |\
			 BRx_V)

#define CONFIG_SYS_OR2_PRELIM  (MEG_TO_AM(CONFIG_SYS_SDRAM1_SIZE)     |\
			 ORxS_BPD_4                     |\
			 ORxS_ROWST_PBI0_A9             |\
			 ORxS_NUMR_12)

#define CONFIG_SYS_LSDMR       0x0169A512
#define CONFIG_SYS_LSRT	0x79

#define CONFIG_SYS_MPTPR	(0x0800 & MPTPR_PTP_MSK)

#define CONFIG_SYS_BR4_PRELIM   ((CONFIG_SYS_REGS_BASE & BRx_BA_MSK)  |\
			   BRx_PS_8                     |\
			   BRx_MS_GPCM_P                |\
			   BRx_V)

#define CONFIG_SYS_OR4_PRELIM    (ORxG_AM_MSK                 |\
			   ORxG_CSNT                   |\
			   ORxG_ACS_DIV1               |\
			   ORxG_SCY_5_CLK              |\
			   ORxG_TRLX)

#define BOOTFLAG_COLD   0x01    /* Normal Power-On: Boot from FLASH  */
#define BOOTFLAG_WARM   0x02    /* Software reboot                   */

#endif  /* __CONFIG_H */
