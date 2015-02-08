

#include <common.h>
#include <asm/io.h>
#include <asm/arch/smc.h>

void s5pc1xx_config_sromc(u32 srom_bank, u32 smc_bw_conf, u32 smc_bc_conf)
{
	u32 tmp;
	struct s5pc1xx_smc *srom;

	if (cpu_is_s5pc100())
		srom = (struct s5pc1xx_smc *)S5PC100_SROMC_BASE;
	else
		srom = (struct s5pc1xx_smc *)S5PC110_SROMC_BASE;

	/* Configure SMC_BW register to handle proper SROMC bank */
	tmp = srom->bw;
	tmp &= ~(0xF << (srom_bank * 4));
	tmp |= smc_bw_conf;
	srom->bw = tmp;

	/* Configure SMC_BC register */
	srom->bc[srom_bank] = smc_bc_conf;
}
