

#ifndef __ASM_ARCH_CLOCK_H
#define __ASM_ARCH_CLOCK_H

enum mxc_clock {
	MXC_ARM_CLK = 0,
	MXC_AHB_CLK,
	MXC_IPG_CLK,
	MXC_IPG_PERCLK,
	MXC_UART_CLK,
	MXC_CSPI_CLK,
	MXC_FEC_CLK,
};

unsigned int imx_decode_pll(unsigned int pll, unsigned int f_ref);

u32 imx_get_uartclk(void);
u32 imx_get_fecclk(void);
unsigned int mxc_get_clock(enum mxc_clock clk);

#endif /* __ASM_ARCH_CLOCK_H */
