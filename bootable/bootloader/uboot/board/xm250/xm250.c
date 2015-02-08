

#include <asm/arch/pxa-regs.h>
#include <common.h>
#include <netdev.h>

DECLARE_GLOBAL_DATA_PTR;

/* ------------------------------------------------------------------------- */

/* local prototypes */

inline void sleep (int i);

inline void
/**********************************************************/
sleep (int i)
/**********************************************************/
{
	while (i--) {
		udelay (1000000);
	}
}


int
/**********************************************************/
board_init (void)
/**********************************************************/
{
	/* arch number of MicroSys XM250 */
	gd->bd->bi_arch_number = MACH_TYPE_XM250;

	/* adress of boot parameters */
	gd->bd->bi_boot_params = 0xa0000100;

	return 0;
}

int
/**********************************************************/
dram_init (void)
/**********************************************************/
{
	gd->bd->bi_dram[0].start = PHYS_SDRAM_1;
	gd->bd->bi_dram[0].size  = PHYS_SDRAM_1_SIZE;
	gd->bd->bi_dram[1].start = PHYS_SDRAM_2;
	gd->bd->bi_dram[1].size  = PHYS_SDRAM_2_SIZE;
	gd->bd->bi_dram[2].start = PHYS_SDRAM_3;
	gd->bd->bi_dram[2].size  = PHYS_SDRAM_3_SIZE;
	gd->bd->bi_dram[3].start = PHYS_SDRAM_4;
	gd->bd->bi_dram[3].size  = PHYS_SDRAM_4_SIZE;

	return (0);
}

#ifdef CONFIG_CMD_NET
int board_eth_init(bd_t *bis)
{
	int rc = 0;
#ifdef CONFIG_SMC91111
	rc = smc91111_initialize(0, CONFIG_SMC91111_BASE);
#endif
	return rc;
}
#endif
