

#include <ppc_asm.tmpl>
#include <config.h>
#include <asm/mmu.h>


	.section .bootpg,"ax"
	.globl tlbtab

tlbtab:
	tlbtab_start

	tlbentry(0xf0000000, SZ_256M, 0xf0000000, 1, AC_RWX | SA_IG)

	/*
	 * TLB entries for SDRAM are not needed on this platform.
	 * They are dynamically generated in the SPD DDR(2) detection
	 * routine.
	 */

	tlbentry(CONFIG_SYS_PERIPHERAL_BASE, SZ_256M, 0x40000000, 1, AC_RW | SA_IG)
	tlbentry(CONFIG_SYS_ISRAM_BASE, SZ_4K, 0x80000000, 0, AC_RWX)
	tlbentry(CONFIG_SYS_ISRAM_BASE + 0x1000, SZ_4K, 0x80001000, 0, AC_RWX)
	tlbentry(CONFIG_SYS_PCI_BASE, SZ_256M, 0x00000000, 2, AC_RW | SA_IG)
	tlbentry(CONFIG_SYS_PCI_MEMBASE, SZ_256M, 0x00000000, 3, AC_RW | SA_IG)
	tlbtab_end
