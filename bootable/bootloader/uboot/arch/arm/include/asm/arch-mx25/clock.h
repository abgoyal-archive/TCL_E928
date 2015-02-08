

#ifndef __ASM_ARCH_CLOCK_H
#define __ASM_ARCH_CLOCK_H

ulong imx_get_perclk(int clk);
ulong imx_get_ahbclk(void);

#define imx_get_uartclk() imx_get_perclk(15)
#define imx_get_fecclk() (imx_get_ahbclk()/2)


#endif /* __ASM_ARCH_CLOCK_H */
