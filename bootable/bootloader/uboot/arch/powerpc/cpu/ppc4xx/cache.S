

#include <config.h>
#include <config.h>
#include <ppc4xx.h>
#include <ppc_asm.tmpl>
#include <ppc_defs.h>
#include <asm/cache.h>
#include <asm/mmu.h>

_GLOBAL(invalidate_icache)
	iccci	r0,r0
	isync
	blr

_GLOBAL(flush_icache_range)
	li	r5,L1_CACHE_BYTES-1
	andc	r3,r3,r5
	subf	r4,r3,r4
	add	r4,r4,r5
	srwi.	r4,r4,L1_CACHE_SHIFT
	beqlr
	mtctr	r4
	mr	r6,r3
1:	dcbst	0,r3
	addi	r3,r3,L1_CACHE_BYTES
	bdnz	1b
	sync				/* wait for dcbst's to get to ram */
	mtctr	r4
2:	icbi	0,r6
	addi	r6,r6,L1_CACHE_BYTES
	bdnz	2b
	sync				/* additional sync needed on g4 */
	isync
	blr

_GLOBAL(clean_dcache_range)
	li	r5,L1_CACHE_BYTES-1
	andc	r3,r3,r5
	subf	r4,r3,r4
	add	r4,r4,r5
	srwi.	r4,r4,L1_CACHE_SHIFT
	beqlr
	mtctr	r4

1:	dcbst	0,r3
	addi	r3,r3,L1_CACHE_BYTES
	bdnz	1b
	sync				/* wait for dcbst's to get to ram */
	blr

_GLOBAL(flush_dcache_range)
	li	r5,L1_CACHE_BYTES-1
	andc	r3,r3,r5
	subf	r4,r3,r4
	add	r4,r4,r5
	srwi.	r4,r4,L1_CACHE_SHIFT
	beqlr
	mtctr	r4

1:	dcbf	0,r3
	addi	r3,r3,L1_CACHE_BYTES
	bdnz	1b
	sync				/* wait for dcbst's to get to ram */
	blr

_GLOBAL(invalidate_dcache_range)
	li	r5,L1_CACHE_BYTES-1
	andc	r3,r3,r5
	subf	r4,r3,r4
	add	r4,r4,r5
	srwi.	r4,r4,L1_CACHE_SHIFT
	beqlr
	mtctr	r4

1:	dcbi	0,r3
	addi	r3,r3,L1_CACHE_BYTES
	bdnz	1b
	sync				/* wait for dcbi's to get to ram */
	blr

#define CACHE_NWAYS     64
#define CACHE_NLINES    32

_GLOBAL(flush_dcache)
	li	r4,(2 * CACHE_NWAYS * CACHE_NLINES)
	mtctr	r4
	lis	r5,0
1:	lwz	r3,0(r5)		/* Load one word from every line */
	addi	r5,r5,L1_CACHE_BYTES
	bdnz	1b
	sync
	blr

_GLOBAL(invalidate_dcache)
	addi	r6,0,0x0000		/* clear GPR 6 */
	/* Do loop for # of dcache congruence classes. */
	lis	r7,(CONFIG_SYS_DCACHE_SIZE / L1_CACHE_BYTES / 2)@ha	/* TBS for large sized cache */
	ori	r7,r7,(CONFIG_SYS_DCACHE_SIZE / L1_CACHE_BYTES / 2)@l
					/* NOTE: dccci invalidates both */
	mtctr	r7			/* ways in the D cache */
..dcloop:
	dccci	0,r6			/* invalidate line */
	addi	r6,r6,L1_CACHE_BYTES	/* bump to next line */
	bdnz	..dcloop
	sync
	blr

#ifdef CONFIG_440

       .globl  dcache_disable
       .globl  dcache_enable
       .globl  icache_disable
       .globl  icache_enable
dcache_disable:
dcache_enable:
icache_disable:
icache_enable:
	blr

	.globl	dcache_status
	.globl	icache_status
dcache_status:
icache_status:
	mr	r3,  0
	blr

#else /* CONFIG_440 */

	.globl	icache_enable
icache_enable:
	mflr	r8
	bl	invalidate_icache
	mtlr	r8
	isync
	addis	r3,r0, 0xc000	      /* set bit 0 */
	mticcr	r3
	blr

	.globl	icache_disable
icache_disable:
	addis	r3,r0, 0x0000	      /* clear bit 0 */
	mticcr	r3
	isync
	blr

	.globl	icache_status
icache_status:
	mficcr	r3
	srwi	r3, r3, 31	/* >>31 => select bit 0 */
	blr

	.globl	dcache_enable
dcache_enable:
	mflr	r8
	bl	invalidate_dcache
	mtlr	r8
	isync
	addis	r3,r0, 0x8000	      /* set bit 0 */
	mtdccr	r3
	blr

	.globl	dcache_disable
dcache_disable:
	mflr	r8
	bl	flush_dcache
	mtlr	r8
	addis	r3,r0, 0x0000	      /* clear bit 0 */
	mtdccr	r3
	blr

	.globl	dcache_status
dcache_status:
	mfdccr	r3
	srwi	r3, r3, 31	/* >>31 => select bit 0 */
	blr

#endif /* CONFIG_440 */
