
#ifndef _OMAP24XX_CLOCKS_H_
#define _OMAP24XX_CLOCKS_H_

#define COMMIT_DIVIDERS  0x1

#define MODE_BYPASS_FAST 0x2
#define APLL_LOCK        0xc
#ifdef CONFIG_APTIX
#define DPLL_LOCK        0x1   /* stay in bypass mode */
#else
#define DPLL_LOCK        0x3   /* DPLL lock */
#endif

#define II_DPLL_OUT_X2   0x2    /* x2 core out */
#define II_MPU_DIV       0x2    /* mpu = core/2 */
#define II_DSP_DIV       0x343  /* dsp & iva divider */
#define II_GFX_DIV       0x2
#define II_BUS_DIV       0x04601026
#define II_DPLL_300      0x01832100

#define III_DPLL_OUT_X2   0x2    /* x2 core out */
#define III_MPU_DIV       0x2    /* mpu = core/2 */
#define III_DSP_DIV       0x23C3 /* dsp & iva divider sych enabled*/
#define III_GFX_DIV       0x2
#define III_BUS_DIV       0x08301044
#define III_DPLL_266      0x01885500

/* set defaults for boot up */
#ifdef PRCM_CONFIG_II
# define DPLL_OUT         II_DPLL_OUT_X2
# define MPU_DIV          II_MPU_DIV
# define DSP_DIV          II_DSP_DIV
# define GFX_DIV          II_GFX_DIV
# define BUS_DIV          II_BUS_DIV
# define DPLL_VAL         II_DPLL_300
#elif PRCM_CONFIG_III
# define DPLL_OUT         III_DPLL_OUT_X2
# define MPU_DIV          III_MPU_DIV
# define DSP_DIV          III_DSP_DIV
# define GFX_DIV          III_GFX_DIV
# define BUS_DIV          III_BUS_DIV
# define DPLL_VAL         III_DPLL_266
#endif

/* lock delay time out */
#define LDELAY           12000000

#endif
