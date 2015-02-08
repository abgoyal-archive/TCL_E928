

#include <common.h>
#include <asm/fsl_law.h>
#include <asm/mmu.h>

struct law_entry law_table[] = {
#if !defined(CONFIG_SPD_EEPROM)
	SET_LAW(CONFIG_SYS_DDR_SDRAM_BASE, LAW_SIZE_512M, LAW_TRGT_IF_DDR_1),
#endif
	SET_LAW(CONFIG_SYS_PCIE1_MEM_PHYS, LAW_SIZE_256M, LAW_TRGT_IF_PCIE_1),
	SET_LAW(CONFIG_SYS_PCIE2_MEM_PHYS, LAW_SIZE_256M, LAW_TRGT_IF_PCIE_2),
	SET_LAW(PIXIS_BASE, LAW_SIZE_2M, LAW_TRGT_IF_LBC),
	SET_LAW(CONFIG_SYS_PCIE1_IO_PHYS, LAW_SIZE_1M, LAW_TRGT_IF_PCIE_1),
	SET_LAW(CONFIG_SYS_PCIE2_IO_PHYS, LAW_SIZE_1M, LAW_TRGT_IF_PCIE_2),
	SET_LAW(CONFIG_SYS_FLASH_BASE, LAW_SIZE_256M, LAW_TRGT_IF_LBC),
	SET_LAW(CONFIG_SYS_PCI1_MEM_PHYS, LAW_SIZE_256M, LAW_TRGT_IF_PCI_1),
	SET_LAW(CONFIG_SYS_PCI1_IO_PHYS, LAW_SIZE_1M, LAW_TRGT_IF_PCI_1)
};

int num_law_entries = ARRAY_SIZE(law_table);