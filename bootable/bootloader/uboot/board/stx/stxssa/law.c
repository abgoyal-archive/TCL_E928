

#include <common.h>
#include <asm/fsl_law.h>
#include <asm/mmu.h>


struct law_entry law_table[] = {
#ifndef CONFIG_SPD_EEPROM
	SET_LAW(CONFIG_SYS_DDR_SDRAM_BASE, LAW_SIZE_128M, LAW_TRGT_IF_DDR),
#endif
	SET_LAW(CONFIG_SYS_PCI1_MEM_PHYS, LAW_SIZE_512M, LAW_TRGT_IF_PCI_1),
	SET_LAW(CONFIG_SYS_PCI2_MEM_PHYS, LAW_SIZE_512M, LAW_TRGT_IF_PCI_2),
	SET_LAW(CONFIG_SYS_PCI1_IO_PHYS, LAW_SIZE_16M, LAW_TRGT_IF_PCI_1),
	SET_LAW(CONFIG_SYS_PCI2_IO_PHYS, LAW_SIZE_16M, LAW_TRGT_IF_PCI_2),
	/* Map the whole localbus, including flash and reset latch. */
	SET_LAW(CONFIG_SYS_LBC_OPTION_BASE, LAW_SIZE_256M, LAW_TRGT_IF_LBC),
};

int num_law_entries = ARRAY_SIZE(law_table);
