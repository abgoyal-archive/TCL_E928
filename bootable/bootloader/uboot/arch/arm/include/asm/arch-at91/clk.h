
#ifndef __ASM_ARM_ARCH_CLK_H__
#define __ASM_ARM_ARCH_CLK_H__

#include <asm/arch/hardware.h>

unsigned long get_cpu_clk_rate(void);
unsigned long get_main_clk_rate(void);
unsigned long get_mck_clk_rate(void);
unsigned long get_plla_clk_rate(void);
unsigned long get_pllb_clk_rate(void);
unsigned int  get_pllb_init(void);

static inline unsigned long get_macb_pclk_rate(unsigned int dev_id)
{
	return get_mck_clk_rate();
}

static inline unsigned long get_usart_clk_rate(unsigned int dev_id)
{
	return get_mck_clk_rate();
}

static inline unsigned long get_lcdc_clk_rate(unsigned int dev_id)
{
	return get_mck_clk_rate();
}

static inline unsigned long get_spi_clk_rate(unsigned int dev_id)
{
	return get_mck_clk_rate();
}

static inline unsigned long get_twi_clk_rate(unsigned int dev_id)
{
	return get_mck_clk_rate();
}

int at91_clock_init(unsigned long main_clock);
#endif /* __ASM_ARM_ARCH_CLK_H__ */
