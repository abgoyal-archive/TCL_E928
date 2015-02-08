

#include <ppc_asm.tmpl>
#include <config.h>
#include <asm/mmu.h>


	.section .bootpg,"ax"
	.globl tlbtab

tlbtab:
	tlbtab_start

	/*
	 * BOOT_CS (FLASH) must be first. Before relocation SA_I can be off to use the
	 * speed up boot process. It is patched after relocation to enable SA_I
	 */
	tlbentry(0xfff00000, SZ_1M, 0xfff00000, 1, AC_RWX | SA_G)

	tlbentry(0xffc00000, SZ_1M, 0xffc00000, 1, AC_RWX | SA_IG)
	tlbentry(0xffd00000, SZ_1M, 0xffd00000, 1, AC_RWX | SA_IG)
	tlbentry(0xffe00000, SZ_1M, 0xffe00000, 1, AC_RWX | SA_IG)
	tlbentry(0xff900000, SZ_1M, 0xff900000, 1, AC_RWX | SA_IG)
	tlbentry(CONFIG_SYS_EPLD_BASE, SZ_256K, 0xff000000, 1, AC_RW | SA_IG)

	/*
	 * TLB entries for SDRAM are not needed on this platform.
	 * They are dynamically generated in the SPD DDR(2) detection
	 * routine.
	 */

	/* internal ram (l2 cache) */
	tlbentry(CONFIG_SYS_ISRAM_BASE, SZ_256K, 0x80000000, 0, AC_RWX | SA_I)

	/* peripherals at f0000000 */
	tlbentry(CONFIG_SYS_PERIPHERAL_BASE, SZ_4K, CONFIG_SYS_PERIPHERAL_BASE, 1, AC_RW | SA_IG)

	/* PCI */
	tlbentry(CONFIG_SYS_PCI_BASE, SZ_256M, 0x00000000, 9, AC_RW | SA_IG)
	tlbentry(CONFIG_SYS_PCI_MEMBASE, SZ_256M, 0x10000000, 9, AC_RW | SA_IG)
	tlbtab_end
