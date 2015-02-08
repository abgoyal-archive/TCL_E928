


#include "config.h"
#include "version.h"


	.globl	lowlevel_init
lowlevel_init:
	/* The ADS GC+ for Linux Boot Rom Ver. 1.73 does memory init for us.
	 * However the darn thing leaves the MMU enabled before handing control
	 * over to us. So we need to disable the MMU and we use lowlevel_init
	 * to do it.
	 */

@ The following code segment was borrowed with gratitude from:
@	linux-2.4.19-rmk7/arch/arm/boot/compressed/head-sa1100.S

	@ Data cache might be active.
	@ Be sure to flush kernel binary out of the cache,
	@ whatever state it is, before it is turned off.
	@ This is done by fetching through currently executed
	@ memory to be sure we hit the same cache.
	bic	r2, pc, #0x1f
	add	r3, r2, #0x4000		@ 16 kb is quite enough...
1:	ldr	r0, [r2], #32
	teq	r2, r3
	bne	1b
	mcr	p15, 0, r0, c7, c10, 4	@ drain WB
	mcr	p15, 0, r0, c7, c7, 0	@ flush I & D caches

	@ disabling MMU and caches
	mrc	p15, 0, r0, c1, c0, 0	@ read control reg
	bic	r0, r0, #0x0d		@ clear WB, DC, MMU
	bic	r0, r0, #0x1000		@ clear Icache
	mcr	p15, 0, r0, c1, c0, 0

	nop
	nop
	nop
	nop
	nop

	b	2f
2:
	nop
	nop
	nop
	nop
	nop


	mov	pc, lr
