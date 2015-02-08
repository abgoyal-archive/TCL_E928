


#ifndef __LPD7A400_10_H
#define __LPD7A400_10_H


#define CONFIG_ARM920T		1	/* arm920t core */
#define CONFIG_LH7A40X		1	/* Sharp LH7A40x SoC family */
#define CONFIG_LH7A400		1   /* Sharp LH7A400 S0C */

/* The system clock PLL input frequency */
#define CONFIG_SYS_CLK_FREQ		14745600   /* System Clock PLL Input (Hz) */

/* ticks per second */
#define CONFIG_SYS_HZ	(508469)

#define CONFIG_STACKSIZE	(128*1024)	/* regular stack */
#ifdef CONFIG_USE_IRQ
#define CONFIG_STACKSIZE_IRQ	(4*1024)	/* IRQ stack */
#define CONFIG_STACKSIZE_FIQ	(4*1024)	/* FIQ stack */
#endif

#define CONFIG_NR_DRAM_BANKS	1	   /* we have 1 bank of DRAM */
#define PHYS_SDRAM_1		0xc0000000 /* SDRAM Bank #1 */
#define PHYS_SDRAM_1_SIZE	0x02000000 /* 32 MB */

#define CONFIG_SYS_FLASH_BASE		0x00000000 /* Flash Bank #1 */

#define CONFIG_SYS_MAX_FLASH_BANKS	1	/* max number of memory banks */
#define CONFIG_SYS_MAX_FLASH_SECT	(64)	/* max number of sectors on one chip */

/* timeout values are in ticks */
#define CONFIG_SYS_FLASH_ERASE_TOUT	(5*CONFIG_SYS_HZ) /* Timeout for Flash Erase */
#define CONFIG_SYS_FLASH_WRITE_TOUT	(5*CONFIG_SYS_HZ) /* Timeout for Flash Write */

#define CONFIG_NET_MULTI
#define CONFIG_SMC91111
#define CONFIG_SMC91111_BASE	(0x70000000)
#undef CONFIG_SMC_USE_32_BIT

#endif  /* __LPD7A400_10_H */
