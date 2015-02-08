

#include <ppc_asm.tmpl>
#include <config.h>

#include <asm/mmu.h>


    .section .bootpg,"ax"
    .globl tlbtab

tlbtab:
    tlbtab_start

    /*
     * BOOT_CS (FLASH) must be first. Before relocation SA_I can be off to use
     * the speed up boot process. It is patched after relocation to enable SA_I
     */
    tlbentry( CONFIG_SYS_BOOT_BASE_ADDR, SZ_256M, CONFIG_SYS_BOOT_BASE_ADDR,
	0, AC_RWX | SA_G/*|SA_I*/)

    /* TLB-entry for init-ram in dcache (SA_I must be turned off!) */
    tlbentry( CONFIG_SYS_INIT_RAM_ADDR, SZ_64K, CONFIG_SYS_INIT_RAM_ADDR,
	0, AC_RWX | SA_G )

    tlbentry( CONFIG_SYS_SDRAM_BASE, SZ_256M, CONFIG_SYS_SDRAM_BASE,
	0, AC_RWX | SA_IG )
    tlbentry( CONFIG_SYS_PCI_BASE, SZ_256M, CONFIG_SYS_PCI_BASE,
	0, AC_RW | SA_IG )

    /* PCI */
    tlbentry( CONFIG_SYS_PCI_MEMBASE, SZ_256M, CONFIG_SYS_PCI_MEMBASE,
	0, AC_RW | SA_IG )
    tlbentry( CONFIG_SYS_PCI_MEMBASE1, SZ_256M, CONFIG_SYS_PCI_MEMBASE1,
	0, AC_RW | SA_IG )
    tlbentry( CONFIG_SYS_PCI_MEMBASE2, SZ_256M, CONFIG_SYS_PCI_MEMBASE2,
	0, AC_RW | SA_IG )
    tlbentry( CONFIG_SYS_PCI_MEMBASE3, SZ_256M, CONFIG_SYS_PCI_MEMBASE3,
	0, AC_RW | SA_IG )

    tlbtab_end
