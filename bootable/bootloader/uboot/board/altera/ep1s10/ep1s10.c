

#include <common.h>
#include <netdev.h>

int board_early_init_f (void)
{
	return 0;
}

int checkboard (void)
{
	puts ("BOARD : Altera EP-1S10\n");
	return 0;
}

phys_size_t initdram (int board_type)
{
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
