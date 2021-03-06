

#include <common.h>
#include <asm/fsl_law.h>
#include <asm/mmu.h>


struct law_entry law_table[] = {
#ifndef CONFIG_SPD_EEPROM
	SET_LAW(CONFIG_SYS_DDR_SDRAM_BASE, LAW_SIZE_512M, LAW_TRGT_IF_DDR),
#endif
	SET_LAW(CONFIG_SYS_PCI_MEM_PHYS, LAW_SIZE_256M, LAW_TRGT_IF_PCI),
	SET_LAW(CONFIG_SYS_LBC_SDRAM_BASE, LAW_SIZE_512M, LAW_TRGT_IF_LBC),
};

int num_law_entries = ARRAY_SIZE(law_table);
