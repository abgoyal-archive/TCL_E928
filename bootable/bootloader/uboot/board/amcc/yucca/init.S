

#include <ppc_asm.tmpl>
#include <config.h>
#include <asm/mmu.h>


	.section .bootpg,"ax"

	.globl tlbtabA
tlbtabA:
	tlbtab_start

	/*
	 * BOOT_CS (FLASH) must be first. Before relocation SA_I can be off to use the
	 * speed up boot process. It is patched after relocation to enable SA_I
	 */
	tlbentry(0xff000000, SZ_16M, 0xff000000, 4, AC_RWX | SA_G)

	/*
	 * TLB entries for SDRAM are not needed on this platform.
	 * They are dynamically generated in the SPD DDR(2) detection
	 * routine.
	 */

	tlbentry(CONFIG_SYS_ISRAM_BASE, SZ_256K, 0x00000000, 4, AC_RWX | SA_I)
	tlbentry(CONFIG_SYS_FPGA_BASE, SZ_1K, 0xE2000000, 4,AC_RW | SA_I)

	tlbentry(CONFIG_SYS_OPER_FLASH, SZ_16M, 0xE7000000, 4,AC_RWX | SA_IG)
	tlbentry(CONFIG_SYS_PERIPHERAL_BASE, SZ_4K, 0xF0000000, 4, AC_RW | SA_IG)

	tlbentry(CONFIG_SYS_PCI_BASE, SZ_256M, 0x00000000, 0xC, AC_RW | SA_IG)
	tlbentry(CONFIG_SYS_PCI_MEMBASE, SZ_256M, 0x10000000, 0xC, AC_RW | SA_IG)
	tlbentry(CONFIG_SYS_PCIE_MEMBASE, SZ_256M, 0xB0000000, 0xD, AC_RW | SA_IG)
	tlbentry(CONFIG_SYS_PCIE_BASE, SZ_16K, 0x20000000, 0xC, AC_RW | SA_IG)

	tlbentry(CONFIG_SYS_PCIE0_CFGBASE, SZ_16M, 0x40000000, 0xC, AC_RW | SA_IG)
	tlbentry(CONFIG_SYS_PCIE1_CFGBASE, SZ_16M, 0x80000000, 0xC, AC_RW | SA_IG)
	tlbentry(CONFIG_SYS_PCIE2_CFGBASE, SZ_16M, 0xC0000000, 0xC, AC_RW | SA_IG)
	tlbentry(CONFIG_SYS_PCIE0_XCFGBASE, SZ_1K, 0x50000000, 0xC, AC_RW | SA_IG)
	tlbentry(CONFIG_SYS_PCIE1_XCFGBASE, SZ_1K, 0x90000000, 0xC, AC_RW | SA_IG)
	tlbentry(CONFIG_SYS_PCIE2_XCFGBASE, SZ_1K, 0xD0000000, 0xC, AC_RW | SA_IG)
	tlbtab_end

	.globl tlbtabB
tlbtabB:
	tlbtab_start

	/*
	 * BOOT_CS (FLASH) must be first. Before relocation SA_I can be off to use the
	 * speed up boot process. It is patched after relocation to enable SA_I
	 */
	tlbentry(0xff000000, SZ_16M, 0xff000000, 4, AC_RWX | SA_G)

	/*
	 * TLB entries for SDRAM are not needed on this platform.
	 * They are dynamically generated in the SPD DDR(2) detection
	 * routine.
	 */

	tlbentry(CONFIG_SYS_ISRAM_BASE, SZ_256K, 0x00000000, 4, AC_RWX | SA_I)
	tlbentry(CONFIG_SYS_FPGA_BASE, SZ_1K, 0xE2000000, 4,AC_RW | SA_I)

	tlbentry(CONFIG_SYS_OPER_FLASH, SZ_16M, 0xE7000000, 4,AC_RWX | SA_IG)
	tlbentry(CONFIG_SYS_PERIPHERAL_BASE, SZ_4K, 0xF0000000, 4, AC_RW | SA_IG)

	tlbentry(CONFIG_SYS_PCI_BASE, SZ_256M, 0x00000000, 0xC, AC_RW | SA_IG)
	tlbentry(CONFIG_SYS_PCI_MEMBASE, SZ_256M, 0x10000000, 0xC, AC_RW | SA_IG)
	tlbentry(CONFIG_SYS_PCIE_MEMBASE, SZ_256M, 0xB0000000, 0xD, AC_RW | SA_IG)

	tlbentry(CONFIG_SYS_PCIE0_CFGBASE, SZ_16M, 0x00000000, 0xD, AC_RW | SA_IG)
	tlbentry(CONFIG_SYS_PCIE1_CFGBASE, SZ_16M, 0x20000000, 0xD, AC_RW | SA_IG)
	tlbentry(CONFIG_SYS_PCIE2_CFGBASE, SZ_16M, 0x40000000, 0xD, AC_RW | SA_IG)
	tlbentry(CONFIG_SYS_PCIE0_XCFGBASE, SZ_1K, 0x10000000, 0xD, AC_RW | SA_IG)
	tlbentry(CONFIG_SYS_PCIE1_XCFGBASE, SZ_1K, 0x30000000, 0xD, AC_RW | SA_IG)
	tlbentry(CONFIG_SYS_PCIE2_XCFGBASE, SZ_1K, 0x50000000, 0xD, AC_RW | SA_IG)
	tlbtab_end
