


#ifndef __CONFIG_H
#define __CONFIG_H

#define GTREGREAD(x) 0xffffffff         /* needed for debug */



/* first ethernet */
#define CONFIG_ETHADDR          00:00:5b:ee:de:ad

#define CONFIG_IPADDR           192.168.0.105
#define CONFIG_SERVERIP         192.168.0.100

#define CONFIG_ELPPC            1       /* this is an BAB740/BAB750 board */

#define CONFIG_BAUDRATE         9600    /* console baudrate */

#undef  CONFIG_WATCHDOG

#define CONFIG_BOOTDELAY        5       /* autoboot after 5 seconds */

#define CONFIG_ZERO_BOOTDELAY_CHECK

#undef  CONFIG_BOOTARGS
#define CONFIG_BOOTCOMMAND                                  \
    "bootp 1000000; "                                       \
    "setenv bootargs root=ramfs console=ttyS00,9600 "       \
    "ip=${ipaddr}:${serverip}:${rootpath}:${gatewayip}:"    \
    "${netmask}:${hostname}:eth0:none; "                    \
    "bootm"

#define CONFIG_LOADS_ECHO       0       /* echo off for serial download */
#define CONFIG_SYS_LOADS_BAUD_CHANGE           /* allow baudrate changes */

#define CONFIG_BOOTP_SUBNETMASK
#define CONFIG_BOOTP_GATEWAY
#define CONFIG_BOOTP_HOSTNAME
#define CONFIG_BOOTP_BOOTPATH

#define CONFIG_BOOTP_BOOTFILESIZE


#include <config_cmd_default.h>

#define CONFIG_CMD_PCI
#define CONFIG_CMD_JFFS2


#define CONFIG_SYS_LONGHELP                    /* undef to save memory */
#define CONFIG_SYS_PROMPT              "=> "   /* Monitor Command Prompt */

#define CONFIG_CONS_INDEX       1

#if defined(CONFIG_CMD_KGDB)
#define CONFIG_SYS_CBSIZE              1024        /* Console I/O Buffer Size */
#else
#define CONFIG_SYS_CBSIZE              256         /* Console I/O Buffer Size */
#endif
#define CONFIG_SYS_PBSIZE              (CONFIG_SYS_CBSIZE+sizeof(CONFIG_SYS_PROMPT)+16) /* Print Buffer Size */
#define CONFIG_SYS_MAXARGS             16          /* max number of command args    */
#define CONFIG_SYS_BARGSIZE            CONFIG_SYS_CBSIZE  /* Boot Argument Buffer Size    */

#define CONFIG_SYS_MEMTEST_START       0x00000000  /* memtest works on    */
#define CONFIG_SYS_MEMTEST_END         0x04000000  /* 0 ... 64 MB in DRAM    */

#define CONFIG_SYS_LOAD_ADDR           0x1000000   /* default load address    */

#define CONFIG_SYS_HZ                  1000        /* dec. freq: 1 ms ticks */

#define CONFIG_SYS_BAUDRATE_TABLE      { 9600, 19200, 38400, 57600, 115200, 230400 }

#define CONFIG_SYS_BOARD_ASM_INIT
#define CONFIG_MISC_INIT_R

#undef  CONFIG_SYS_ADDRESS_MAP_A

#define CONFIG_SYS_PCI_MEMORY_BUS      0x00000000
#define CONFIG_SYS_PCI_MEMORY_PHYS     0x00000000
#define CONFIG_SYS_PCI_MEMORY_SIZE     0x40000000

#define CONFIG_SYS_PCI_MEM_BUS         0x80000000
#define CONFIG_SYS_PCI_MEM_PHYS        0x80000000
#define CONFIG_SYS_PCI_MEM_SIZE        0x7d000000

#define CONFIG_SYS_ISA_MEM_BUS         0x00000000
#define CONFIG_SYS_ISA_MEM_PHYS        0xfd000000
#define CONFIG_SYS_ISA_MEM_SIZE        0x01000000

#define CONFIG_SYS_PCI_IO_BUS          0x00800000
#define CONFIG_SYS_PCI_IO_PHYS         0xfe800000
#define CONFIG_SYS_PCI_IO_SIZE         0x00400000

#define CONFIG_SYS_ISA_IO_BUS          0x00000000
#define CONFIG_SYS_ISA_IO_PHYS         0xfe000000
#define CONFIG_SYS_ISA_IO_SIZE         0x00800000

/* driver defines FDC,IDE,... */
#define CONFIG_SYS_ISA_IO_BASE_ADDRESS CONFIG_SYS_ISA_IO_PHYS
#define CONFIG_SYS_ISA_IO              CONFIG_SYS_ISA_IO_PHYS
#define CONFIG_SYS_60X_PCI_IO_OFFSET   CONFIG_SYS_ISA_IO_PHYS

#define CONFIG_SYS_SDRAM_BASE          0x00000000

#define CONFIG_SYS_USR_LED_BASE        0x78000000
#define CONFIG_SYS_NVRAM_BASE          0xff000000
#define CONFIG_SYS_UART_BASE           0xff400000
#define CONFIG_SYS_FLASH_BASE          0xfff00000

#define MPC107_EUMB_ADDR        0xfce00000
#define MPC107_EUMB_PI          0xfce41090
#define MPC107_EUMB_GCR         0xfce41020
#define MPC107_EUMB_IACKR       0xfce600a0
#define MPC107_I2C_ADDR         0xfce03000

#define CONFIG_SYS_INIT_RAM_ADDR       0x00fd0000  /* above the memtest region */
#define CONFIG_SYS_INIT_RAM_END        0x4000
#define CONFIG_SYS_GBL_DATA_SIZE       64          /* size in bytes reserved for init data */
#define CONFIG_SYS_GBL_DATA_OFFSET     (CONFIG_SYS_INIT_RAM_END - CONFIG_SYS_GBL_DATA_SIZE)
#define CONFIG_SYS_INIT_SP_OFFSET      CONFIG_SYS_GBL_DATA_OFFSET

#define FLASH_BASE0_PRELIM      0xff800000
#define FLASH_BASE1_PRELIM      0xffc00000

#define CONFIG_SYS_MAX_FLASH_BANKS     2           /* max number of memory banks    */
#define CONFIG_SYS_MAX_FLASH_SECT      67          /* max number of sectors on one chip */

#define CONFIG_SYS_FLASH_ERASE_TOUT    120000      /* Timeout for Flash Erase (in ms) */
#define CONFIG_SYS_FLASH_WRITE_TOUT    500         /* Timeout for Flash Write (in ms) */

/* No command line, one static partition, whole device */
#undef CONFIG_CMD_MTDPARTS
#define CONFIG_JFFS2_DEV		"nor0"
#define CONFIG_JFFS2_PART_SIZE		0xFFFFFFFF
#define CONFIG_JFFS2_PART_OFFSET	0x00000000

/* mtdparts command line support */
/* Note: fake mtd_id used, no linux mtd map file */

#define CONFIG_SYS_MONITOR_BASE        CONFIG_SYS_FLASH_BASE
#define CONFIG_SYS_MONITOR_LEN         0x40000     /* Reserve 256 kB for Monitor */
#define CONFIG_SYS_MALLOC_LEN          0x20000     /* Reserve 128 kB for malloc() */
#undef  CONFIG_SYS_MEMTEST

#define CONFIG_ENV_OVERWRITE
#define CONFIG_ENV_IS_IN_NVRAM     1           /* use NVRAM for environment vars */
#define CONFIG_SYS_NVRAM_SIZE          0x800       /* NVRAM size (2kB) */
#define CONFIG_ENV_SIZE            0x400       /* Size of Environment vars (1kB) */
#define CONFIG_ENV_ADDR            0x0
#define CONFIG_ENV_MAP_ADRS        0xff000000
#define CONFIG_SYS_NV_SROM_COPY_ADDR   (CONFIG_ENV_ADDR + CONFIG_ENV_SIZE)
#define CONFIG_SYS_NVRAM_ACCESS_ROUTINE            /* only byte accsess alowed */
#define CONFIG_SYS_SROM_SIZE           0x100       /* shadow of revision info is in nvram */

#define CONFIG_SYS_NS16550
#define CONFIG_SYS_NS16550_SERIAL
#define CONFIG_SYS_NS16550_REG_SIZE    1
#define CONFIG_SYS_NS16550_CLK         24000000
#define CONFIG_SYS_NS16550_COM1        (CONFIG_SYS_UART_BASE + 0)
#define CONFIG_SYS_NS16550_COM2        (CONFIG_SYS_UART_BASE + 8)

#define CONFIG_PCI                                /* include pci support */
#define CONFIG_PCI_PNP                            /* pci plug-and-play */
#define CONFIG_PCI_HOST         PCI_HOST_AUTO
#undef  CONFIG_PCI_SCAN_SHOW

#define CONFIG_VIDEO
#define CONFIG_CFB_CONSOLE
#define VIDEO_KBD_INIT_FCT    (simple_strtol (getenv("console"), NULL, 10))
#define VIDEO_TSTC_FCT        serial_tstc
#define VIDEO_GETC_FCT        serial_getc

#define CONFIG_VIDEO_SMI_LYNXEM
#define CONFIG_VIDEO_LOGO
#define CONFIG_CONSOLE_EXTRA_INFO

#if 1

#define CONFIG_SYS_IBAT0L 0
#define CONFIG_SYS_IBAT0U 0
#define CONFIG_SYS_DBAT0L CONFIG_SYS_IBAT1L
#define CONFIG_SYS_DBAT0U CONFIG_SYS_IBAT1U

#define CONFIG_SYS_IBAT1L 0
#define CONFIG_SYS_IBAT1U 0
#define CONFIG_SYS_DBAT1L CONFIG_SYS_IBAT1L
#define CONFIG_SYS_DBAT1U CONFIG_SYS_IBAT1U

#define CONFIG_SYS_IBAT2L 0
#define CONFIG_SYS_IBAT2U 0
#define CONFIG_SYS_DBAT2L CONFIG_SYS_IBAT2L
#define CONFIG_SYS_DBAT2U CONFIG_SYS_IBAT2U

#define CONFIG_SYS_IBAT3L 0
#define CONFIG_SYS_IBAT3U 0
#define CONFIG_SYS_DBAT3L CONFIG_SYS_IBAT3L
#define CONFIG_SYS_DBAT3U CONFIG_SYS_IBAT3U

#else

/* SDRAM */
#define CONFIG_SYS_IBAT0L (CONFIG_SYS_SDRAM_BASE | BATL_RW)
#define CONFIG_SYS_IBAT0U (CONFIG_SYS_SDRAM_BASE | BATU_BL_256M | BATU_VS | BATU_VP)
#define CONFIG_SYS_DBAT0L CONFIG_SYS_IBAT1L
#define CONFIG_SYS_DBAT0U CONFIG_SYS_IBAT1U

/* address range for flashes */
#define CONFIG_SYS_IBAT1L (CONFIG_SYS_FLASH_BASE | BATL_RW | BATL_CACHEINHIBIT)
#define CONFIG_SYS_IBAT1U (CONFIG_SYS_FLASH_BASE | BATU_BL_16M | BATU_VS | BATU_VP)
#define CONFIG_SYS_DBAT1L CONFIG_SYS_IBAT1L
#define CONFIG_SYS_DBAT1U CONFIG_SYS_IBAT1U

/* ISA IO space */
#define CONFIG_SYS_IBAT2L (CONFIG_SYS_ISA_IO | BATL_RW | BATL_CACHEINHIBIT)
#define CONFIG_SYS_IBAT2U (CONFIG_SYS_ISA_IO | BATU_BL_16M | BATU_VS | BATU_VP)
#define CONFIG_SYS_DBAT2L CONFIG_SYS_IBAT2L
#define CONFIG_SYS_DBAT2U CONFIG_SYS_IBAT2U

/* ISA memory space */
#define CONFIG_SYS_IBAT3L (CONFIG_SYS_ISA_MEM | BATL_RW | BATL_CACHEINHIBIT)
#define CONFIG_SYS_IBAT3U (CONFIG_SYS_ISA_MEM | BATU_BL_16M | BATU_VS | BATU_VP)
#define CONFIG_SYS_DBAT3L CONFIG_SYS_IBAT3L
#define CONFIG_SYS_DBAT3U CONFIG_SYS_IBAT3U

#endif

#define CONFIG_SYS_BUS_HZ              100000000
#define CONFIG_SYS_CPU_CLK             400000000
#define CONFIG_SYS_BUS_CLK             CONFIG_SYS_BUS_HZ

#define CONFIG_SYS_BOOTMAPSZ           (8 << 20)           /* Initial Memory map for Linux */

#define CONFIG_SYS_CACHELINE_SIZE        32    /* For all MPC74xx CPUs */
#if defined(CONFIG_CMD_KGDB)
#define CONFIG_SYS_CACHELINE_SHIFT        5    /* log base 2 of the above value */
#endif


#define CONFIG_SYS_L2

#if 1
#define L2_INIT     0       /* cpu 750 CXe*/
#else
#define L2_INIT     (L2CR_L2SIZ_2M | L2CR_L2CLK_3 | L2CR_L2RAM_BURST | \
		     L2CR_L2OH_5   | L2CR_L2CTL | L2CR_L2WT)
#endif
#define L2_ENABLE   (L2_INIT | L2CR_L2E)

#define BOOTFLAG_COLD           0x01    /* Normal Power-On: Boot from FLASH */
#define BOOTFLAG_WARM           0x02    /* Software reboot */

#define CONFIG_NET_MULTI        /* Multi ethernet cards support */
#define CONFIG_EEPRO100
#define CONFIG_SYS_RX_ETH_BUFFER	8               /* use 8 rx buffer on eepro100  */
#define CONFIG_EEPRO100_SROM_WRITE

#endif    /* __CONFIG_H */
