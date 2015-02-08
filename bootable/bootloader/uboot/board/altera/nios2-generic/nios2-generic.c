

#include <common.h>
#include <netdev.h>

void text_base_hook(void); /* nop hook for text_base.S */

int board_early_init_f(void)
{
	text_base_hook();
	return 0;
}

int checkboard(void)
{
	printf("BOARD : %s\n", CONFIG_BOARD_NAME);
	return 0;
}

phys_size_t initdram(int board_type)
{
	return 0;
}

#ifdef CONFIG_CMD_NET
int board_eth_init(bd_t *bis)
{
	int rc = 0;
#ifdef CONFIG_SMC91111
	rc += smc91111_initialize(0, CONFIG_SMC91111_BASE);
#endif
#ifdef CONFIG_DRIVER_DM9000
	rc += dm9000_initialize(bis);
#endif
#ifdef CONFIG_ALTERA_TSE
	rc += altera_tse_initialize(0,
				    CONFIG_SYS_ALTERA_TSE_MAC_BASE,
				    CONFIG_SYS_ALTERA_TSE_SGDMA_RX_BASE,
				    CONFIG_SYS_ALTERA_TSE_SGDMA_TX_BASE);
#endif
#ifdef CONFIG_ETHOC
	rc += ethoc_initialize(0, CONFIG_SYS_ETHOC_BASE);
#endif
	return rc;
}
#endif
