

#include <common.h>
#include <asm/io.h>
#include <asm/arch/mem.h>
#include <asm/arch/sys_proto.h>
#include <command.h>

unsigned int boot_flash_base;
unsigned int boot_flash_off;
unsigned int boot_flash_sec;
unsigned int boot_flash_type;
volatile unsigned int boot_flash_env_addr;

struct gpmc *gpmc_cfg;

#if defined(CONFIG_CMD_NAND)
static const u32 gpmc_m_nand[GPMC_MAX_REG] = {
	M_NAND_GPMC_CONFIG1,
	M_NAND_GPMC_CONFIG2,
	M_NAND_GPMC_CONFIG3,
	M_NAND_GPMC_CONFIG4,
	M_NAND_GPMC_CONFIG5,
	M_NAND_GPMC_CONFIG6, 0
};

#if defined(CONFIG_ENV_IS_IN_NAND)
#define GPMC_CS 0
#else
#define GPMC_CS 1
#endif

#endif

#if defined(CONFIG_CMD_ONENAND)
static const u32 gpmc_onenand[GPMC_MAX_REG] = {
	ONENAND_GPMC_CONFIG1,
	ONENAND_GPMC_CONFIG2,
	ONENAND_GPMC_CONFIG3,
	ONENAND_GPMC_CONFIG4,
	ONENAND_GPMC_CONFIG5,
	ONENAND_GPMC_CONFIG6, 0
};

#if defined(CONFIG_ENV_IS_IN_ONENAND)
#define GPMC_CS 0
#else
#define GPMC_CS 1
#endif

#endif

static struct sdrc *sdrc_base = (struct sdrc *)OMAP34XX_SDRC_BASE;

void make_cs1_contiguous(void)
{
	u32 size, a_add_low, a_add_high;

	size = get_sdr_cs_size(CS0);
	size >>= 25;	/* divide by 32 MiB to find size to offset CS1 */
	a_add_high = (size & 3) << 8;	/* set up low field */
	a_add_low = (size & 0x3C) >> 2;	/* set up high field */
	writel((a_add_high | a_add_low), &sdrc_base->cs_cfg);

}

u32 mem_ok(u32 cs)
{
	u32 val1, val2, addr;
	u32 pattern = 0x12345678;

	addr = OMAP34XX_SDRC_CS0 + get_sdr_cs_offset(cs);

	writel(0x0, addr + 0x400);	/* clear pos A */
	writel(pattern, addr);		/* pattern to pos B */
	writel(0x0, addr + 4);		/* remove pattern off the bus */
	val1 = readl(addr + 0x400);	/* get pos A value */
	val2 = readl(addr);		/* get val2 */

	if ((val1 != 0) || (val2 != pattern))	/* see if pos A val changed */
		return 0;
	else
		return 1;
}

void sdrc_init(void)
{
	/* only init up first bank here */
	do_sdrc_init(CS0, EARLY_INIT);
}


void do_sdrc_init(u32 cs, u32 early)
{
	struct sdrc_actim *sdrc_actim_base;

	if(cs)
		sdrc_actim_base = (struct sdrc_actim *)SDRC_ACTIM_CTRL1_BASE;
	else
		sdrc_actim_base = (struct sdrc_actim *)SDRC_ACTIM_CTRL0_BASE;

	if (early) {
		/* reset sdrc controller */
		writel(SOFTRESET, &sdrc_base->sysconfig);
		wait_on_value(RESETDONE, RESETDONE, &sdrc_base->status,
			      12000000);
		writel(0, &sdrc_base->sysconfig);

		/* setup sdrc to ball mux */
		writel(SDRC_SHARING, &sdrc_base->sharing);

		/* Disable Power Down of CKE cuz of 1 CKE on combo part */
		writel(WAKEUPPROC | PWDNEN | SRFRONRESET | PAGEPOLICY_HIGH,
				&sdrc_base->power);

		writel(ENADLL | DLLPHASE_90, &sdrc_base->dlla_ctrl);
		sdelay(0x20000);
	}

	writel(RASWIDTH_13BITS | CASWIDTH_10BITS | ADDRMUXLEGACY |
		RAMSIZE_128 | BANKALLOCATION | B32NOT16 | B32NOT16 |
		DEEPPD | DDR_SDRAM, &sdrc_base->cs[cs].mcfg);
	writel(ARCV | ARE_ARCV_1, &sdrc_base->cs[cs].rfr_ctrl);
	writel(V_ACTIMA_165, &sdrc_actim_base->ctrla);
	writel(V_ACTIMB_165, &sdrc_actim_base->ctrlb);

	writel(CMD_NOP, &sdrc_base ->cs[cs].manual);
	writel(CMD_PRECHARGE, &sdrc_base->cs[cs].manual);
	writel(CMD_AUTOREFRESH, &sdrc_base->cs[cs].manual);
	writel(CMD_AUTOREFRESH, &sdrc_base->cs[cs].manual);

	/*
	 * CAS latency 3, Write Burst = Read Burst, Serial Mode,
	 * Burst length = 4
	 */
	writel(CASL3 | BURSTLENGTH4, &sdrc_base->cs[cs].mr);

	if (!mem_ok(cs))
		writel(0, &sdrc_base->cs[cs].mcfg);
}

void enable_gpmc_cs_config(const u32 *gpmc_config, struct gpmc_cs *cs, u32 base,
			u32 size)
{
	writel(0, &cs->config7);
	sdelay(1000);
	/* Delay for settling */
	writel(gpmc_config[0], &cs->config1);
	writel(gpmc_config[1], &cs->config2);
	writel(gpmc_config[2], &cs->config3);
	writel(gpmc_config[3], &cs->config4);
	writel(gpmc_config[4], &cs->config5);
	writel(gpmc_config[5], &cs->config6);
	/* Enable the config */
	writel((((size & 0xF) << 8) | ((base >> 24) & 0x3F) |
		(1 << 6)), &cs->config7);
	sdelay(2000);
}

void gpmc_init(void)
{
	/* putting a blanket check on GPMC based on ZeBu for now */
	gpmc_cfg = (struct gpmc *)GPMC_BASE;
#if defined(CONFIG_CMD_NAND) || defined(CONFIG_CMD_ONENAND)
	const u32 *gpmc_config = NULL;
	u32 base = 0;
	u32 size = 0;
#if defined(CONFIG_ENV_IS_IN_NAND) || defined(CONFIG_ENV_IS_IN_ONENAND)
	u32 f_off = CONFIG_SYS_MONITOR_LEN;
	u32 f_sec = 0;
#endif
#endif
	u32 config = 0;

	/* global settings */
	writel(0, &gpmc_cfg->irqenable); /* isr's sources masked */
	writel(0, &gpmc_cfg->timeout_control);/* timeout disable */

	config = readl(&gpmc_cfg->config);
	config &= (~0xf00);
	writel(config, &gpmc_cfg->config);

	/*
	 * Disable the GPMC0 config set by ROM code
	 * It conflicts with our MPDB (both at 0x08000000)
	 */
	writel(0, &gpmc_cfg->cs[0].config7);
	sdelay(1000);

#if defined(CONFIG_CMD_NAND)	/* CS 0 */
	gpmc_config = gpmc_m_nand;

	base = PISMO1_NAND_BASE;
	size = PISMO1_NAND_SIZE;
	enable_gpmc_cs_config(gpmc_config, &gpmc_cfg->cs[0], base, size);
#if defined(CONFIG_ENV_IS_IN_NAND)
	f_off = SMNAND_ENV_OFFSET;
	f_sec = (128 << 10);	/* 128 KiB */
	/* env setup */
	boot_flash_base = base;
	boot_flash_off = f_off;
	boot_flash_sec = f_sec;
	boot_flash_env_addr = f_off;
#endif
#endif

#if defined(CONFIG_CMD_ONENAND)
	gpmc_config = gpmc_onenand;
	base = PISMO1_ONEN_BASE;
	size = PISMO1_ONEN_SIZE;
	enable_gpmc_cs_config(gpmc_config, &gpmc_cfg->cs[0], base, size);
#if defined(CONFIG_ENV_IS_IN_ONENAND)
	f_off = ONENAND_ENV_OFFSET;
	f_sec = (128 << 10);	/* 128 KiB */
	/* env setup */
	boot_flash_base = base;
	boot_flash_off = f_off;
	boot_flash_sec = f_sec;
	boot_flash_env_addr = f_off;
#endif
#endif
}
