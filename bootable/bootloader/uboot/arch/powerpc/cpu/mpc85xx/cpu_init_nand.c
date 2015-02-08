

#include <common.h>
#include <asm/io.h>

void cpu_init_f(void)
{
	ccsr_lbc_t *lbc = (void *)(CONFIG_SYS_MPC85xx_LBC_ADDR);

	/*
	 * LCRR - Clock Ratio Register - set up local bus timing
	 * when needed
	 */
	out_be32(&lbc->lcrr, LCRR_DBYP | LCRR_CLKDIV_8);

#if defined(CONFIG_NAND_BR_PRELIM) && defined(CONFIG_NAND_OR_PRELIM)
	out_be32(&lbc->br0, CONFIG_NAND_BR_PRELIM);
	out_be32(&lbc->or0, CONFIG_NAND_OR_PRELIM);
#else
#error  CONFIG_NAND_BR_PRELIM, CONFIG_NAND_OR_PRELIM must be defined
#endif

#if defined(CONFIG_SYS_RAMBOOT) && defined(CONFIG_SYS_INIT_L2_ADDR)
	ccsr_l2cache_t *l2cache = (void *)CONFIG_SYS_MPC85xx_L2_ADDR;
	char *l2srbar;
	int i;

	out_be32(&l2cache->l2srbar0, CONFIG_SYS_INIT_L2_ADDR);

	/* set MBECCDIS=1, SBECCDIS=1 */
	out_be32(&l2cache->l2errdis,
		(MPC85xx_L2ERRDIS_MBECC | MPC85xx_L2ERRDIS_SBECC));

	/* set L2E=1 & L2SRAM=001 */
	out_be32(&l2cache->l2ctl,
		(MPC85xx_L2CTL_L2E | MPC85xx_L2CTL_L2SRAM_ENTIRE));

	/* Initialize L2 SRAM to zero */
	l2srbar = (char *)CONFIG_SYS_INIT_L2_ADDR;
	for (i = 0; i < CONFIG_SYS_L2_SIZE; i++)
		l2srbar[i] = 0;
#endif
}
