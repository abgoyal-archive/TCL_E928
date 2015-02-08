

#include <common.h>
#include <netdev.h>
#include <SA-1100.h>

DECLARE_GLOBAL_DATA_PTR;


int
board_init(void)
{
	gd->bd->bi_arch_number = MACH_TYPE_GRAPHICSCLIENT;

	gd->bd->bi_boot_params = 0xc000003c; /* Weird address? */

	/* Most of the ADS GCPlus I/O is connected to Static nCS2.
	 * So I'm brute forcing nCS2 timiming here for worst case.
	 */
	MSC1 &= ~0xFFFF;
	MSC1 |= 0x8649;

	/* Nothing is connected to Static nCS4 or nCS5. But I'm using
	 * nCS4 as a paranoia safe guard to force nCS2, nOE; nWE high
	 * after accessing I/O via (non-VLIO) nCS2. What can I say, I'm
	 * paranoid and lack decent tools to alleviate my fear. I sure
	 * do wish I had a logic analyzer. : (
	 */

	MSC2 =  0xfff9fff9;

	return 0;
}

int
dram_init(void)
{
	gd->bd->bi_dram[0].start = PHYS_SDRAM_1;
	gd->bd->bi_dram[0].size = PHYS_SDRAM_1_SIZE;
	gd->bd->bi_dram[1].start = PHYS_SDRAM_2;
	gd->bd->bi_dram[1].size = PHYS_SDRAM_2_SIZE;

	return (0);
}

#ifdef CONFIG_CMD_NET
int board_eth_init(bd_t *bis)
{
	int rc = 0;
#ifdef CONFIG_LAN91C96
	rc = lan91c96_initialize(0, CONFIG_LAN91C96_BASE);
#endif
	return rc;
}
#endif
