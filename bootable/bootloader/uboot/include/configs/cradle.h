

#ifndef __CONFIG_H
#define __CONFIG_H

#define CONFIG_PXA250           1       /* This is an PXA250 CPU    */
#define CONFIG_HHP_CRADLE       1       /* on an Cradle Board       */

#undef CONFIG_USE_IRQ                   /* we don't need IRQ/FIQ stuff */

/* we will never enable dcache, because we have to setup MMU first */
#define CONFIG_SYS_NO_DCACHE

#define CONFIG_SYS_MALLOC_LEN		(CONFIG_ENV_SIZE + 128*1024)
#define CONFIG_SYS_GBL_DATA_SIZE	128	/* size in bytes reserved for initial data */

#define CONFIG_NET_MULTI
#define CONFIG_SMC91111
#define CONFIG_SMC91111_BASE 0x10000300
#define CONFIG_SMC91111_EXT_PHY
#define CONFIG_SMC_USE_32_BIT

#define CONFIG_PXA_SERIAL
#define CONFIG_FFUART          1       /* we use FFUART on LUBBOCK */

/* allow to overwrite serial and ethaddr */
#define CONFIG_ENV_OVERWRITE

#define CONFIG_BAUDRATE         115200


#define CONFIG_BOOTP_BOOTFILESIZE
#define CONFIG_BOOTP_BOOTPATH
#define CONFIG_BOOTP_GATEWAY
#define CONFIG_BOOTP_HOSTNAME


#include <config_cmd_default.h>


#define CONFIG_BOOTDELAY        3
#define CONFIG_BOOTARGS         "root=/dev/mtdblock2 console=ttyS0,115200"
#define CONFIG_ETHADDR          08:00:3e:26:0a:5b
#define CONFIG_NETMASK          255.255.0.0
#define CONFIG_IPADDR           192.168.0.21
#define CONFIG_SERVERIP         192.168.0.250
#define CONFIG_BOOTCOMMAND      "bootm 40000"
#define CONFIG_CMDLINE_TAG

#define CONFIG_SYS_LONGHELP                            /* undef to save memory         */
#define CONFIG_SYS_PROMPT              "=> "   /* Monitor Command Prompt       */
#define CONFIG_SYS_CBSIZE              256             /* Console I/O Buffer Size      */
#define CONFIG_SYS_PBSIZE (CONFIG_SYS_CBSIZE+sizeof(CONFIG_SYS_PROMPT)+16) /* Print Buffer Size */
#define CONFIG_SYS_MAXARGS             16              /* max number of command args   */
#define CONFIG_SYS_BARGSIZE            CONFIG_SYS_CBSIZE      /* Boot Argument Buffer Size    */

#define CONFIG_SYS_MEMTEST_START       0xa0400000      /* memtest works on     */
#define CONFIG_SYS_MEMTEST_END         0xa0800000      /* 4 ... 8 MB in DRAM   */

#define CONFIG_SYS_LOAD_ADDR           0xa2000000      /* default load address */

#define CONFIG_SYS_HZ			1000
#define CONFIG_SYS_CPUSPEED            0x141           /* set core clock to 200/200/100 MHz */

						/* valid baudrates */
#define CONFIG_SYS_BAUDRATE_TABLE      { 9600, 19200, 38400, 57600, 115200 }

#define CONFIG_STACKSIZE        (128*1024)      /* regular stack */
#ifdef CONFIG_USE_IRQ
#define CONFIG_STACKSIZE_IRQ    (4*1024)        /* IRQ stack */
#define CONFIG_STACKSIZE_FIQ    (4*1024)        /* FIQ stack */
#endif

#define CONFIG_NR_DRAM_BANKS    4          /* we have 2 banks of DRAM */
#define PHYS_SDRAM_1            0xa0000000 /* SDRAM Bank #1 */
#define PHYS_SDRAM_1_SIZE       0x01000000 /* 64 MB */
#define PHYS_SDRAM_2            0xa4000000 /* SDRAM Bank #2 */
#define PHYS_SDRAM_2_SIZE       0x00000000 /* 0 MB */
#define PHYS_SDRAM_3            0xa8000000 /* SDRAM Bank #3 */
#define PHYS_SDRAM_3_SIZE       0x00000000 /* 0 MB */
#define PHYS_SDRAM_4            0xac000000 /* SDRAM Bank #4 */
#define PHYS_SDRAM_4_SIZE       0x00000000 /* 0 MB */

#define PHYS_FLASH_1            0x00000000 /* Flash Bank #1 */
#define PHYS_FLASH_2            0x04000000 /* Flash Bank #1 */
#define PHYS_FLASH_SIZE         0x02000000 /* 32 MB */

#define CONFIG_SYS_DRAM_BASE           0xa0000000
#define CONFIG_SYS_DRAM_SIZE           0x04000000

#define CONFIG_SYS_FLASH_BASE          PHYS_FLASH_1

#define CONFIG_SYS_MAX_FLASH_BANKS     1     /* max number of memory banks           */
#define CONFIG_SYS_MAX_FLASH_SECT      32    /* max number of sectors on one chip    */

/* timeout values are in ticks */
#define CONFIG_SYS_FLASH_ERASE_TOUT    (2*CONFIG_SYS_HZ) /* Timeout for Flash Erase */
#define CONFIG_SYS_FLASH_WRITE_TOUT    (2*CONFIG_SYS_HZ) /* Timeout for Flash Write */

#define CONFIG_ENV_IS_IN_FLASH	1
#define CONFIG_ENV_ADDR				0x00020000	/* absolute address for now   */
#define CONFIG_ENV_SIZE				0x20000	   /* 8K ouch, this may later be */


/* Pin direction control */
/* NOTE GPIO 0, 61, 62 are set for inputs due to CPLD SPAREs */
#define CONFIG_SYS_GPDR0_VAL       0xfff3bf02
#define CONFIG_SYS_GPDR1_VAL       0xfbffbf83
#define CONFIG_SYS_GPDR2_VAL       0x0001ffff
/* Set and Clear registers */
#define CONFIG_SYS_GPSR0_VAL       0x00400800
#define CONFIG_SYS_GPSR1_VAL       0x00000480
#define CONFIG_SYS_GPSR2_VAL       0x00014000
#define CONFIG_SYS_GPCR0_VAL       0x00000000
#define CONFIG_SYS_GPCR1_VAL       0x00000000
#define CONFIG_SYS_GPCR2_VAL       0x00000000
/* Edge detect registers (these are set by the kernel) */
#define CONFIG_SYS_GRER0_VAL       0x00000000
#define CONFIG_SYS_GRER1_VAL       0x00000000
#define CONFIG_SYS_GRER2_VAL       0x00000000
#define CONFIG_SYS_GFER0_VAL       0x00000000
#define CONFIG_SYS_GFER1_VAL       0x00000000
#define CONFIG_SYS_GFER2_VAL       0x00000000
/* Alternate function registers */
#define CONFIG_SYS_GAFR0_L_VAL     0x00000000
#define CONFIG_SYS_GAFR0_U_VAL     0x00000010
#define CONFIG_SYS_GAFR1_L_VAL     0x900a9550
#define CONFIG_SYS_GAFR1_U_VAL     0x00000008
#define CONFIG_SYS_GAFR2_L_VAL     0x20000000
#define CONFIG_SYS_GAFR2_U_VAL     0x00000002

#define CONFIG_SYS_PSSR_VAL        0x00000020
#define CONFIG_SYS_CCCR_VAL        0x00000141  /* 100 MHz memory, 200 MHz CPU  */
#define CONFIG_SYS_CKEN_VAL        0x00000060  /* FFUART and STUART enabled    */
#define CONFIG_SYS_ICMR_VAL        0x00000000  /* No interrupts enabled        */


#define CONFIG_SYS_MSC0_VAL        0x000023FA  /* flash bank    (cs0)   */
/*#define CONFIG_SYS_MSC1_VAL        0x00003549  / * SuperIO bank  (cs2)   */
#define CONFIG_SYS_MSC1_VAL        0x0000354c  /* SuperIO bank  (cs2)   */
#define CONFIG_SYS_MSC2_VAL        0x00001224  /* Ethernet bank (cs4)   */
#ifdef REDBOOT_WAY
#define CONFIG_SYS_MDCNFG_VAL      0x00001aa1  /* FIXME can DTC be 01?     */
#define CONFIG_SYS_MDMRS_VAL       0x00000000
#define CONFIG_SYS_MDREFR_VAL      0x00018018
#else
#define CONFIG_SYS_MDCNFG_VAL      0x00001aa1  /* FIXME can DTC be 01?     */
#define CONFIG_SYS_MDMRS_VAL       0x00000000
#define CONFIG_SYS_MDREFR_VAL      0x00403018  /* Initial setting, individual bits set in lowlevel_init.S */
#endif

#define CONFIG_SYS_MECR_VAL          0x00000000
#define CONFIG_SYS_MCMEM0_VAL        0x00010504
#define CONFIG_SYS_MCMEM1_VAL        0x00010504
#define CONFIG_SYS_MCATT0_VAL        0x00010504
#define CONFIG_SYS_MCATT1_VAL        0x00010504
#define CONFIG_SYS_MCIO0_VAL         0x00004715
#define CONFIG_SYS_MCIO1_VAL         0x00004715

/* Board specific defines */

/* LED defines */
#define YELLOW    0x03
#define RED       0x02
#define GREEN     0x01
#define OFF       0x00
#define LED_IRDA0 0
#define LED_IRDA1 2
#define LED_IRDA2 4
#define LED_IRDA3 6
#define CRADLE_LED_SET_REG GPSR2
#define CRADLE_LED_CLR_REG GPCR2

/* SuperIO defines */
#define CRADLE_SIO_INDEX      0x2e
#define CRADLE_SIO_DATA       0x2f

/* IO defines */
#define CRADLE_CPLD_PHYS      0x08000000
#define CRADLE_SIO1_PHYS      0x08100000
#define CRADLE_SIO2_PHYS      0x08200000
#define CRADLE_SIO3_PHYS      0x08300000
#define CRADLE_ETH_PHYS       0x10000000

#ifndef __ASSEMBLY__

/* global prototypes */
void led_code(int code, int color);

#endif

#endif  /* __CONFIG_H */
