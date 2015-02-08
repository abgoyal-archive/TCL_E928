
#ifndef __ASM_SH_CLK_H__
#define __ASM_SH_CLK_H__

static inline unsigned long get_peripheral_clk_rate(void)
{
	return CONFIG_SYS_CLK_FREQ;
}

static inline unsigned long get_tmu0_clk_rate(void)
{
	return CONFIG_SYS_CLK_FREQ;
}

#endif /* __ASM_SH_CLK_H__ */
