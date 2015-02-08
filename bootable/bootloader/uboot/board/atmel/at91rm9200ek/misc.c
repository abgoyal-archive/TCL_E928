

#include <common.h>
#include <asm/arch/AT91RM9200.h>
#include <at91rm9200_net.h>
#include <dm9161.h>
#include <net.h>

int board_late_init(void)
{
	DECLARE_GLOBAL_DATA_PTR;

	/* Fix Ethernet Initialization Bug when starting Linux from U-Boot */
	eth_init(gd->bd);
	return 0;
}


/* checks if addr is in RAM */
int addr2ram(ulong addr)
{
	int result = 0;

	if((addr >= PHYS_SDRAM) && (addr < (PHYS_SDRAM + PHYS_SDRAM_SIZE)))
		result = 1;

	return result;
}
