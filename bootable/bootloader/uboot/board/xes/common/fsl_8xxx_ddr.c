

#include <common.h>
#include <asm/fsl_ddr_sdram.h>
#include <asm/mmu.h>

#if defined(CONFIG_DDR_ECC) && !defined(CONFIG_ECC_INIT_VIA_DDRCONTROLLER)
extern void ddr_enable_ecc(unsigned int dram_size);
#endif

phys_size_t initdram(int board_type)
{
	phys_size_t dram_size = fsl_ddr_sdram();

#ifdef CONFIG_MPC85xx
	dram_size = setup_ddr_tlbs(dram_size / 0x100000);
	dram_size *= 0x100000;
#endif

#if defined(CONFIG_DDR_ECC) && !defined(CONFIG_ECC_INIT_VIA_DDRCONTROLLER)
	/* Initialize and enable DDR ECC */
	ddr_enable_ecc(dram_size);
#endif

	return dram_size;
}
