

#ifndef __ASM_ARCH_CLOCK_H
#define __ASM_ARCH_CLOCK_H
unsigned int imx_decode_pll(unsigned int pll, unsigned int f_ref);

ulong imx_get_mpllclk(void);
ulong imx_get_armclk(void);
ulong imx_get_spllclk(void);
ulong imx_get_fclk(void);
ulong imx_get_hclk(void);
ulong imx_get_bclk(void);
ulong imx_get_perclk1(void);
ulong imx_get_perclk2(void);
ulong imx_get_perclk3(void);
ulong imx_get_ahbclk(void);

#define imx_get_uartclk imx_get_perclk1
#define imx_get_fecclk imx_get_ahbclk

#endif /* __ASM_ARCH_CLOCK_H */
