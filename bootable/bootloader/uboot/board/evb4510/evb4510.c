

#include <common.h>
#include <asm/hardware.h>
#include <command.h>

DECLARE_GLOBAL_DATA_PTR;

#ifdef CONFIG_EVB4510

/* ------------------------------------------------------------------------- */


int board_init (void)
{
	icache_enable();

	/* address for the kernel command line */
	gd->bd->bi_boot_params = 0x800;

	/* enable board LEDs for output */
	PUT_REG( REG_IOPDATA, 0x0);
	PUT_REG( REG_IOPMODE, 0xFFFF);
	PUT_REG( REG_IOPDATA, 0xFF);

	return 0;
}

int dram_init (void)
{
	gd->bd->bi_dram[0].start = PHYS_SDRAM_1;
	gd->bd->bi_dram[0].size  = PHYS_SDRAM_1_SIZE;
#if CONFIG_NR_DRAM_BANKS == 2
	gd->bd->bi_dram[1].start = PHYS_SDRAM_2;
	gd->bd->bi_dram[1].size  = PHYS_SDRAM_2_SIZE;
#endif
	return 0;
}

#endif
