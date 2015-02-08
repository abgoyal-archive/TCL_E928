

#include <common.h>
#include <lh7a40x.h>


/* ------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------- */

ulong get_PLLCLK (void)
{
	return CONFIG_SYS_CLK_FREQ;
}

/* return FCLK frequency */
ulong get_FCLK (void)
{
	lh7a40x_csc_t* csc = LH7A40X_CSC_PTR;
	ulong maindiv1, maindiv2, prediv, ps;

	/*
	 * from userguide 6.1.1.2
	 *
	 * FCLK = ((MAINDIV1 +2) * (MAINDIV2 +2) * 14.7456MHz) /
	 *                   ((PREDIV+2) * (2^PS))
	 */
	maindiv2 = (csc->clkset & CLKSET_MAINDIV2) >> 11;
	maindiv1 = (csc->clkset & CLKSET_MAINDIV1) >> 7;
	prediv = (csc->clkset & CLKSET_PREDIV) >> 2;
	ps = (csc->clkset & CLKSET_PS) >> 16;

	return (((maindiv2 + 2) * (maindiv1 + 2) * CONFIG_SYS_CLK_FREQ) /
		((prediv + 2) * (1 << ps)));
}


/* return HCLK frequency */
ulong get_HCLK (void)
{
	lh7a40x_csc_t* csc = LH7A40X_CSC_PTR;

	return (get_FCLK () / ((csc->clkset & CLKSET_HCLKDIV) + 1));
}

/* return PCLK frequency */
ulong get_PCLK (void)
{
	lh7a40x_csc_t* csc = LH7A40X_CSC_PTR;

	return (get_HCLK () /
		(1 << (((csc->clkset & CLKSET_PCLKDIV) >> 16) + 1)));
}
