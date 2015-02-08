

#ifndef __ASM_ARM_ARCH_CLK_H_
#define __ASM_ARM_ARCH_CLK_H_

#define APLL	0
#define MPLL	1
#define EPLL	2
#define HPLL	3
#define VPLL	4

void s5pc1xx_clock_init(void);

extern unsigned long (*get_pll_clk)(int pllreg);
extern unsigned long (*get_arm_clk)(void);
extern unsigned long (*get_pclk)(void);

#endif
