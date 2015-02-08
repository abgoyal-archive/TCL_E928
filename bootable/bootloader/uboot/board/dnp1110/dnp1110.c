

#include <common.h>
#include <netdev.h>
#include <SA-1100.h>

DECLARE_GLOBAL_DATA_PTR;


int board_init (void)
{
	/* memory and cpu-speed are setup before relocation */
	/* so we do _nothing_ here */

	/* arch number of DNP1110-Board */
	gd->bd->bi_arch_number = MACH_TYPE_DNP1110;

	/* flash vpp on */
	PPDR |= 0x80;	/* assumes LCD controller is off */
	PPSR |= 0x80;

	return 0;
}

int dram_init (void)
{
	gd->bd->bi_dram[0].start = PHYS_SDRAM_1;
	gd->bd->bi_dram[0].size = PHYS_SDRAM_1_SIZE;

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
