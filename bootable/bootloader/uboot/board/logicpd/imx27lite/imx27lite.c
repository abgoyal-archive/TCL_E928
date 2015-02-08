

#include <common.h>
#include <asm/io.h>
#include <asm/arch/imx-regs.h>

DECLARE_GLOBAL_DATA_PTR;

int board_init (void)
{
	struct gpio_regs *regs = (struct gpio_regs *)IMX_GPIO_BASE;
#if defined(CONFIG_SYS_NAND_LARGEPAGE)
	struct system_control_regs *sc_regs =
		(struct system_control_regs *)IMX_SYSTEM_CTL_BASE;
#endif

	gd->bd->bi_arch_number = MACH_TYPE_IMX27LITE;
	gd->bd->bi_boot_params = PHYS_SDRAM_1 + 0x100;

#ifdef CONFIG_MXC_UART
	mx27_uart_init_pins();
#endif
#ifdef CONFIG_FEC_MXC
	mx27_fec_init_pins();
	imx_gpio_mode((GPIO_PORTC | GPIO_OUT | GPIO_PUEN | GPIO_GPIO | 31));
	writel(readl(&regs->port[PORTC].dr) | (1 << 31),
				&regs->port[PORTC].dr);
#endif
#ifdef CONFIG_MXC_MMC
#if defined(CONFIG_MAGNESIUM)
	mx27_sd1_init_pins();
#else
	mx27_sd2_init_pins();
#endif
#endif

#if defined(CONFIG_SYS_NAND_LARGEPAGE)
	/*
	 * set in FMCR NF_FMS Bit(5) to 1
	 * (NAND Flash with 2 Kbyte page size)
	 */
	writel(readl(&sc_regs->fmcr) | (1 << 5), &sc_regs->fmcr);
#endif
	return 0;
}

int dram_init (void)
{

#if CONFIG_NR_DRAM_BANKS > 0
	gd->bd->bi_dram[0].start = PHYS_SDRAM_1;
	gd->bd->bi_dram[0].size = get_ram_size((volatile void *)PHYS_SDRAM_1,
			PHYS_SDRAM_1_SIZE);
#endif
#if CONFIG_NR_DRAM_BANKS > 1
	gd->bd->bi_dram[1].start = PHYS_SDRAM_2;
	gd->bd->bi_dram[1].size = get_ram_size((volatile void *)PHYS_SDRAM_2,
			PHYS_SDRAM_2_SIZE);
#endif

	return 0;
}

int checkboard(void)
{
	puts ("Board: ");
	puts(CONFIG_BOARDNAME);
	return 0;
}
