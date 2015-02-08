

#include <ppc_asm.tmpl>
#include <asm/mmu.h>
#include <config.h>


	.section .bootpg,"ax"
	.globl tlbtab

tlbtab:
	tlbtab_start
	tlbentry(0xff000000, SZ_16M, 0xff000000, 1, AC_RWX | SA_IG )
	tlbentry(CONFIG_SYS_PERIPHERAL_BASE, SZ_256M, 0x40000000, 1, AC_RW | SA_IG)
	tlbentry(CONFIG_SYS_ISRAM_BASE, SZ_4K, 0x80000000, 0, AC_RWX)
	tlbentry(CONFIG_SYS_ISRAM_BASE + 0x1000, SZ_4K, 0x80001000, 0, AC_RWX)
#ifdef CONFIG_4xx_DCACHE
	tlbentry(CONFIG_SYS_SDRAM_BASE, SZ_256M, 0x00000000, 0, AC_RWX | SA_G)
#else
	tlbentry(CONFIG_SYS_SDRAM_BASE, SZ_256M, 0x00000000, 0, AC_RWX | SA_IG)
#endif

#ifdef CONFIG_SYS_INIT_RAM_DCACHE
	/* TLB-entry for init-ram in dcache (SA_I must be turned off!) */
	tlbentry(CONFIG_SYS_INIT_RAM_ADDR, SZ_64K, CONFIG_SYS_INIT_RAM_ADDR, 0, AC_RWX | SA_G)
#endif
	tlbentry(CONFIG_SYS_PCI_BASE, SZ_256M, 0x00000000, 2, AC_RW | SA_IG)

	/* PCI */
	tlbentry(CONFIG_SYS_PCI_MEMBASE, SZ_256M, CONFIG_SYS_PCI_MEMBASE, 3, AC_RW | SA_IG)
	tlbentry(CONFIG_SYS_PCI_MEMBASE1, SZ_256M, CONFIG_SYS_PCI_MEMBASE1, 3, AC_RW | SA_IG)
	tlbentry(CONFIG_SYS_PCI_MEMBASE2, SZ_256M, CONFIG_SYS_PCI_MEMBASE2, 3, AC_RW | SA_IG)

	/* NAND */
	tlbentry(CONFIG_SYS_NAND_BASE, SZ_4K, CONFIG_SYS_NAND_BASE, 1, AC_RWX | SA_IG)
	tlbtab_end
