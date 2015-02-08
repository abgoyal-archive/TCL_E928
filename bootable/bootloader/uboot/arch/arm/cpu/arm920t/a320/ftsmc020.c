

#include <config.h>
#include <common.h>
#include <asm/io.h>
#include <asm/arch/ftsmc020.h>

struct ftsmc020_config {
	unsigned int	config;
	unsigned int	timing;
};

static struct ftsmc020_config config[] = CONFIG_SYS_FTSMC020_CONFIGS;

static struct ftsmc020 *smc = (struct ftsmc020 *)CONFIG_FTSMC020_BASE;

static void ftsmc020_setup_bank(unsigned int bank, struct ftsmc020_config *cfg)
{
	if (bank > 3) {
		printf("bank # %u invalid\n", bank);
		return;
	}

	writel(cfg->config, &smc->bank[bank].cr);
	writel(cfg->timing, &smc->bank[bank].tpr);
}

void ftsmc020_init(void)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(config); i++)
		ftsmc020_setup_bank(i, &config[i]);
}
