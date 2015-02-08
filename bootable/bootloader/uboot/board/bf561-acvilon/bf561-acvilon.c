

#include <common.h>
#include <netdev.h>

DECLARE_GLOBAL_DATA_PTR;

int checkboard(void)
{
	printf("Board:  CJSC \"NII STT\"-=Acvilon Platform=- [U-Boot]\n");
	printf("       Support: http://www.niistt.ru/\n");
	return 0;
}

#ifdef CONFIG_SMC911X
int board_eth_init(bd_t *bis)
{
	return smc911x_initialize(0, CONFIG_SMC911X_BASE);
}
#endif
