

#include <common.h>
#include <asm/arch/omap2420.h>
#include <asm/io.h>
#include <asm/arch/bits.h>
#include <asm/arch/mux.h>
#include <asm/arch/mem.h>
#include <asm/arch/clocks.h>
#include <asm/arch/sys_proto.h>
#include <asm/arch/sys_info.h>

#include "mem.h"

void sdelay(unsigned long loops)
{
	__asm__("1:\n" "subs %0, %1, #1\n"
		  "bne 1b":"=r" (loops):"0"(loops));
}

void prcm_init(void) { }

void make_cs1_contiguous(void)
{
	u32 size, a_add_low, a_add_high;

	size = get_sdr_cs_size(SDRC_CS0_OSET);
	size /= SZ_32M;		/* find size to offset CS1 */
	a_add_high = (size & 3) << 8;	/* set up low field */
	a_add_low = (size & 0x3C) >> 2;	/* set up high field */
	__raw_writel((a_add_high | a_add_low), SDRC_CS_CFG);

}

u32 mem_ok(void)
{
	u32 val1, val2;
	u32 pattern = 0x12345678;

	/* clear pos A */
	__raw_writel(0x0, OMAP2420_SDRC_CS0 + 0x400);
	/* pattern to pos B */
	__raw_writel(pattern, OMAP2420_SDRC_CS0);
	/* remove pattern off the bus */
	__raw_writel(0x0, OMAP2420_SDRC_CS0 + 4);
	/* get pos A value */
	val1 = __raw_readl(OMAP2420_SDRC_CS0 + 0x400);
	val2 = __raw_readl(OMAP2420_SDRC_CS0);	/* get val2 */

	/* see if pos A value changed */
	if ((val1 != 0) || (val2 != pattern))
		return (0);
	else
		return (1);
}

void sdrc_init(void)
{
#define EARLY_INIT 1
	/* only init up first bank here */
	do_sdrc_init(SDRC_CS0_OSET, EARLY_INIT);
}

void do_sdrc_init(u32 offset, u32 early)
{
}

void gpmc_init(void)
{
	u32 mux = 0, mtype, mwidth, rev, tval;

	rev = get_cpu_rev();
	if (rev == CPU_2420_2422_ES1)
		tval = 1;
	else
		tval = 0;	/* disable bit switched meaning */

	/* global settings */
	__raw_writel(0x10, GPMC_SYSCONFIG);	/* smart idle */
	__raw_writel(0x0, GPMC_IRQENABLE);	/* isr's sources masked */
	__raw_writel(tval, GPMC_TIMEOUT_CONTROL);	/* timeout disable */
#ifdef CONFIG_SYS_NAND_BOOT
	/* set nWP, disable limited addr */
	__raw_writel(0x001, GPMC_CONFIG);
#else
	/* set nWP, disable limited addr */
	__raw_writel(0x111, GPMC_CONFIG);
#endif

	/* discover bus connection from sysboot */
	if (is_gpmc_muxed() == GPMC_MUXED)
		mux = BIT9;
	mtype = get_gpmc0_type();
	mwidth = get_gpmc0_width();

	/* setup cs0 */
	__raw_writel(0x0, GPMC_CONFIG7_0);	/* disable current map */
	sdelay(1000);

#ifdef CONFIG_SYS_NOR_BOOT
	__raw_writel(APOLLON_24XX_GPMC_CONFIG1_3, GPMC_CONFIG1_0);
	__raw_writel(APOLLON_24XX_GPMC_CONFIG2_3, GPMC_CONFIG2_0);
	__raw_writel(APOLLON_24XX_GPMC_CONFIG3_3, GPMC_CONFIG3_0);
	__raw_writel(APOLLON_24XX_GPMC_CONFIG4_3, GPMC_CONFIG4_0);
	__raw_writel(APOLLON_24XX_GPMC_CONFIG5_3, GPMC_CONFIG5_0);
	__raw_writel(APOLLON_24XX_GPMC_CONFIG6_3, GPMC_CONFIG6_0);
	__raw_writel(APOLLON_24XX_GPMC_CONFIG7_3, GPMC_CONFIG7_0);
#else
	__raw_writel(APOLLON_24XX_GPMC_CONFIG1_0 | mux | mtype | mwidth,
		     GPMC_CONFIG1_0);
	__raw_writel(APOLLON_24XX_GPMC_CONFIG2_0, GPMC_CONFIG2_0);
	__raw_writel(APOLLON_24XX_GPMC_CONFIG3_0, GPMC_CONFIG3_0);
	__raw_writel(APOLLON_24XX_GPMC_CONFIG4_0, GPMC_CONFIG4_0);
	__raw_writel(APOLLON_24XX_GPMC_CONFIG5_0, GPMC_CONFIG5_0);
	__raw_writel(APOLLON_24XX_GPMC_CONFIG6_0, GPMC_CONFIG6_0);
	__raw_writel(APOLLON_24XX_GPMC_CONFIG7_0, GPMC_CONFIG7_0);
#endif
	sdelay(2000);

	/* setup cs1 */
	__raw_writel(0, GPMC_CONFIG7_1);	/* disable any mapping */
	sdelay(1000);

	__raw_writel(APOLLON_24XX_GPMC_CONFIG1_1, GPMC_CONFIG1_1);
	__raw_writel(APOLLON_24XX_GPMC_CONFIG2_1, GPMC_CONFIG2_1);
	__raw_writel(APOLLON_24XX_GPMC_CONFIG3_1, GPMC_CONFIG3_1);
	__raw_writel(APOLLON_24XX_GPMC_CONFIG4_1, GPMC_CONFIG4_1);
	__raw_writel(APOLLON_24XX_GPMC_CONFIG5_1, GPMC_CONFIG5_1);
	__raw_writel(APOLLON_24XX_GPMC_CONFIG6_1, GPMC_CONFIG6_1);
	__raw_writel(APOLLON_24XX_GPMC_CONFIG7_1, GPMC_CONFIG7_1);
	sdelay(2000);

	/* setup cs2 */
	__raw_writel(0x0, GPMC_CONFIG7_2);	/* disable current map */
	sdelay(1000);
	__raw_writel(APOLLON_24XX_GPMC_CONFIG1_0 | mux | mtype | mwidth,
		     GPMC_CONFIG1_2);
	/* It's same as cs 0 */
	__raw_writel(APOLLON_24XX_GPMC_CONFIG2_0, GPMC_CONFIG2_2);
	__raw_writel(APOLLON_24XX_GPMC_CONFIG3_0, GPMC_CONFIG3_2);
	__raw_writel(APOLLON_24XX_GPMC_CONFIG4_0, GPMC_CONFIG4_2);
	__raw_writel(APOLLON_24XX_GPMC_CONFIG5_0, GPMC_CONFIG5_2);
	__raw_writel(APOLLON_24XX_GPMC_CONFIG6_0, GPMC_CONFIG6_2);
#ifdef CONFIG_SYS_NOR_BOOT
	__raw_writel(APOLLON_24XX_GPMC_CONFIG7_0, GPMC_CONFIG7_2);
#else
	__raw_writel(APOLLON_24XX_GPMC_CONFIG7_2, GPMC_CONFIG7_2);
#endif

#ifndef CONFIG_SYS_NOR_BOOT
	/* setup cs3 */
	__raw_writel(0, GPMC_CONFIG7_3);	/* disable any mapping */
	sdelay(1000);

	__raw_writel(APOLLON_24XX_GPMC_CONFIG1_3, GPMC_CONFIG1_3);
	__raw_writel(APOLLON_24XX_GPMC_CONFIG2_3, GPMC_CONFIG2_3);
	__raw_writel(APOLLON_24XX_GPMC_CONFIG3_3, GPMC_CONFIG3_3);
	__raw_writel(APOLLON_24XX_GPMC_CONFIG4_3, GPMC_CONFIG4_3);
	__raw_writel(APOLLON_24XX_GPMC_CONFIG5_3, GPMC_CONFIG5_3);
	__raw_writel(APOLLON_24XX_GPMC_CONFIG6_3, GPMC_CONFIG6_3);
	__raw_writel(APOLLON_24XX_GPMC_CONFIG7_3, GPMC_CONFIG7_3);
#endif

#ifndef ASYNC_NOR
	__raw_writew(0xaa, (APOLLON_CS3_BASE + 0xaaa));
	__raw_writew(0x55, (APOLLON_CS3_BASE + 0x554));
	__raw_writew(0xc0, (APOLLON_CS3_BASE | SYNC_NOR_VALUE));
#endif
	sdelay(2000);
}
