

#include <config.h>
#include <ppc4xx.h>

#define _LINUX_CONFIG_H 1	/* avoid reading Linux autoconf.h file	*/

#include <ppc_asm.tmpl>
#include <ppc_defs.h>

#include <asm/cache.h>
#include <asm/mmu.h>

	.globl ext_bus_cntlr_init
ext_bus_cntlr_init:
		mfdcr r24,CPC0_PSR		/* xxxx xxxx xxxx xxx? ?xxx xxxx xxxx xxxx
						   0 0 -> 8 bit external ROM
						   0 1 -> 16 bit internal ROM */
		addi r4,0,2
		srw r24,r24,r4				/* shift right r24 two positions */
		andi. r24,r24,0x06000
		lis r25,0x0800
		ori r25,r25,0x0280			/* 0000 1000 0xxx 0000 0000 0010 100x xxxx = 0x03800280
		lis r26,0x8900
		ori r26,r26,0x0280			/* 1000 1001 0xxx 0000 0000 0010 100x xxxx
		mflr r4					/* save link register */
		bl ..getAddr
..getAddr:
		mflr r3					/* get address of ..getAddr */
		mtlr r4					/* restore link register */
		addi r4,0,14				/* set ctr to 10; used to prefetch */
		mtctr r4				/* 10 cache lines to fit this function
							in cache (gives us 8x10=80 instructions) */
..ebcloop:
		icbt r0,r3				/* prefetch cache line for addr in r3 */
		addi r3,r3,32				/* move to next cache line */
		bdnz ..ebcloop				/* continue for 10 cache lines */
		lis r3,0x0
		ori r3,r3,0xA000			/* ensure 200usec have passed since reset */
		mtctr r3
..spinlp:
		bdnz ..spinlp				/* spin loop */


		li r4,PB1AP				/* PB0AP=Peripheral Bank 0 Access Parameters */
		mtdcr EBC0_CFGADDR,r4

		mr r4,r26				/* assume internal fast flash is boot flash */
		cmpwi r24,0x2000			/* assumption true? ... */
		beq 1f					/* ...yes! */
		mr r4,r25				/* ...no, use the slow variant */
		mr r25,r26				/* use this for the other flash */
1:
		mtdcr EBC0_CFGDATA,r4			/* change timing now */

		li r4,PB0CR				/* PB0CR=Peripheral Bank 0 Control Register */
		mtdcr EBC0_CFGADDR,r4
		mfdcr r4,EBC0_CFGDATA
		lis r3,0x0001
		ori r3,r3,0x8000			/* allow reads and writes */
		or r4,r4,r3
		mtdcr EBC0_CFGDATA,r4


		li r4,PB3AP				/* Peripheral Bank 1 Access Parameter */
		mtdcr EBC0_CFGADDR,r4
		mtdcr EBC0_CFGDATA,r2			/* change timing */

		li r4,PB3CR				/* Peripheral Bank 1 Configuration Registers */
		mtdcr EBC0_CFGADDR,r4

		lis r4,0xF003
		ori r4,r4,0x8000
		xori r24,r24,0x2000			/* invert current bus width */
		or r4,r4,r24
		mtdcr EBC0_CFGDATA,r4


		li r4,PB1AP				/* Peripheral Bank 1 Access Parameter */
		mtdcr EBC0_CFGADDR,r4

		lis r4,0x0000
		ori r4,r4,0x0200
		mtdcr EBC0_CFGDATA,r4

		li r4,PB1CR				/* Peripheral Bank 1 Configuration Registers */
		mtdcr EBC0_CFGADDR,r4

		lis r4,0x77D1
		ori r4,r4,0x8000
		mtdcr EBC0_CFGDATA,r4


/* USB init (without acceleration) */
#ifndef CONFIG_ISP1161_PRESENT
		li r4,PB4AP				/* PB4AP=Peripheral Bank 4 Access Parameters */
		mtdcr EBC0_CFGADDR,r4
		lis r4,0x0180
		ori r4,r4,0x5940
		mtdcr EBC0_CFGDATA,r4
#endif

		li r4,PB2AP				/* PB2AP=Peripheral Bank 2 Access Parameters */
		mtdcr EBC0_CFGADDR,r4

#if 1
/* faster access to isa-bus */
		lis r4,0x0180
		ori r4,r4,0x5940
#else
		lis r4,0x0100
		ori r4,r4,0x0340
#endif
		mtdcr EBC0_CFGDATA,r4

#ifdef IDE_USES_ISA_EMULATION
		li r25,PB5AP				/* PB5AP=Peripheral Bank 5 Access Parameters */
		mtdcr EBC0_CFGADDR,r25
		mtdcr EBC0_CFGDATA,r4
#endif

		li r25,PB6AP				/* PB6AP=Peripheral Bank 6 Access Parameters */
		mtdcr EBC0_CFGADDR,r25
		mtdcr EBC0_CFGDATA,r4
		li r25,PB7AP				/* PB7AP=Peripheral Bank 7 Access Parameters */
		mtdcr EBC0_CFGADDR,r25
		mtdcr EBC0_CFGDATA,r4

		li r25,PB2CR				/* PB2CR=Peripheral Bank 2 Configuration Register */
		mtdcr EBC0_CFGADDR,r25

		lis r4,0x780B
		ori r4,r4,0xA000
		mtdcr EBC0_CFGDATA,r4
		lis r4,0x7401
		ori r4,r4,0xA000

		li r25,PB6CR				/* PB6CR=Peripheral Bank 6 Configuration Register */
		mtdcr EBC0_CFGADDR,r25
		lis r4,0x7401
		ori r4,r4,0xA000
		mtdcr EBC0_CFGDATA,r4

		li r25,PB7CR				/* PB7CR=Peripheral Bank 7 Configuration Register */
		mtdcr EBC0_CFGADDR,r25
		lis r4,0x7411
		ori r4,r4,0xA000
		mtdcr EBC0_CFGDATA,r4

#ifndef CONFIG_ISP1161_PRESENT
		li r25,PB4CR				/* PB4CR=Peripheral Bank 4 Configuration Register */
		mtdcr EBC0_CFGADDR,r25
		lis r4,0x7421
		ori r4,r4,0xA000
		mtdcr EBC0_CFGDATA,r4
#endif
#ifdef IDE_USES_ISA_EMULATION
		li r25,PB5CR				/* PB5CR=Peripheral Bank 5 Configuration Register */
		mtdcr EBC0_CFGADDR,r25
		lis r4,0x0000
		ori r4,r4,0x0000
		mtdcr EBC0_CFGDATA,r4
#endif


#ifdef CONFIG_ISP1161_PRESENT

		li r4,PB4AP				/* PB4AP=Peripheral Bank 4 Access Parameters */
		mtdcr EBC0_CFGADDR,r4

		lis r4,0x030D
		ori r4,r4,0x5E80
		mtdcr EBC0_CFGDATA,r4

		li r4,PB4CR				/* PB2CR=Peripheral Bank 4 Configuration Register */
		mtdcr EBC0_CFGADDR,r4

		lis r4,0x77C1
		ori r4,r4,0xA000
		mtdcr EBC0_CFGDATA,r4

#endif

#ifndef IDE_USES_ISA_EMULATION


		li r4,PB5AP
		mtdcr EBC0_CFGADDR,r4
		lis r4,0x040C
		ori r4,r4,0x0200
		mtdcr EBC0_CFGDATA,r4

		li r4,PB5CR			/* PB2CR=Peripheral Bank 2 Configuration Register */
		mtdcr EBC0_CFGADDR,r4

		lis r4,0x7A01
		ori r4,r4,0xA000
		mtdcr EBC0_CFGDATA,r4
#endif
		li r4,EBC0_CFG
		mtdcr EBC0_CFGADDR,r4

		lis r4,0xB84E
		ori r4,r4,0xF000
		mtdcr EBC0_CFGDATA,r4
		lis r4,0x7900
		ori r4,r4,0x0080
		li r3,0x0001
		stb r3,0(r4)			/* 01 -> external bus controller is initialized */
		nop				/* pass2 DCR errata #8 */
		blr
