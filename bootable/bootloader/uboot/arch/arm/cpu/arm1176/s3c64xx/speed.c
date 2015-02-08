


#include <common.h>
#include <asm/arch/s3c6400.h>

#define APLL 0
#define MPLL 1
#define EPLL 2

/* ------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------- */

static ulong get_PLLCLK(int pllreg)
{
	ulong r, m, p, s;

	switch (pllreg) {
	case APLL:
		r = APLL_CON_REG;
		break;
	case MPLL:
		r = MPLL_CON_REG;
		break;
	case EPLL:
		r = EPLL_CON0_REG;
		break;
	default:
		hang();
	}

	m = (r >> 16) & 0x3ff;
	p = (r >> 8) & 0x3f;
	s = r & 0x7;

	return m * (CONFIG_SYS_CLK_FREQ / (p * (1 << s)));
}

/* return ARMCORE frequency */
ulong get_ARMCLK(void)
{
	ulong div;

	div = CLK_DIV0_REG;

	return get_PLLCLK(APLL) / ((div & 0x7) + 1);
}

/* return FCLK frequency */
ulong get_FCLK(void)
{
	return get_PLLCLK(APLL);
}

/* return HCLK frequency */
ulong get_HCLK(void)
{
	ulong fclk;

	uint hclkx2_div = ((CLK_DIV0_REG >> 9) & 0x7) + 1;
	uint hclk_div = ((CLK_DIV0_REG >> 8) & 0x1) + 1;

	/*
	 * Bit 7 exists on s3c6410, and not on s3c6400, it is reserved on
	 * s3c6400 and is always 0, and it is indeed running in ASYNC mode
	 */
	if (OTHERS_REG & 0x80)
		fclk = get_FCLK();		/* SYNC Mode	*/
	else
		fclk = get_PLLCLK(MPLL);	/* ASYNC Mode	*/

	return fclk / (hclk_div * hclkx2_div);
}

/* return PCLK frequency */
ulong get_PCLK(void)
{
	ulong fclk;
	uint hclkx2_div = ((CLK_DIV0_REG >> 9) & 0x7) + 1;
	uint pre_div = ((CLK_DIV0_REG >> 12) & 0xf) + 1;

	if (OTHERS_REG & 0x80)
		fclk = get_FCLK();		/* SYNC Mode	*/
	else
		fclk = get_PLLCLK(MPLL);	/* ASYNC Mode	*/

	return fclk / (hclkx2_div * pre_div);
}

/* return UCLK frequency */
ulong get_UCLK(void)
{
	return get_PLLCLK(EPLL);
}

int print_cpuinfo(void)
{
	printf("\nCPU:     S3C6400@%luMHz\n", get_ARMCLK() / 1000000);
	printf("         Fclk = %luMHz, Hclk = %luMHz, Pclk = %luMHz ",
	       get_FCLK() / 1000000, get_HCLK() / 1000000,
	       get_PCLK() / 1000000);

	if (OTHERS_REG & 0x80)
		printf("(SYNC Mode) \n");
	else
		printf("(ASYNC Mode) \n");
	return 0;
}
