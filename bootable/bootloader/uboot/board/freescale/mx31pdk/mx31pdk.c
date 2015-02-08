


#include <common.h>
#include <netdev.h>
#include <asm/arch/mx31.h>
#include <asm/arch/mx31-regs.h>

DECLARE_GLOBAL_DATA_PTR;

int dram_init(void)
{
	gd->bd->bi_dram[0].start = PHYS_SDRAM_1;
	gd->bd->bi_dram[0].size = PHYS_SDRAM_1_SIZE;

	return 0;
}

int board_init(void)
{
	/* CS5: CPLD incl. network controller */
	__REG(CSCR_U(5)) = 0x0000d843;
	__REG(CSCR_L(5)) = 0x22252521;
	__REG(CSCR_A(5)) = 0x22220a00;

	/* Setup UART1 and SPI2 pins */
	mx31_uart1_hw_init();
	mx31_spi2_hw_init();

	gd->bd->bi_arch_number = MACH_TYPE_MX31_3DS; /* board id for linux */
	/* adress of boot parameters */
	gd->bd->bi_boot_params = PHYS_SDRAM_1 + 0x100;

	return 0;
}

int checkboard(void)
{
	printf("Board: i.MX31 MAX PDK (3DS)\n");
	return 0;
}

int board_eth_init(bd_t *bis)
{
	int rc = 0;
#ifdef CONFIG_SMC911X
	rc = smc911x_initialize(0, CONFIG_SMC911X_BASE);
#endif
	return rc;
}
