

#include <config.h>
#include <version.h>
#include <asm/arch/pxa-regs.h>

.globl lowlevel_init
lowlevel_init:

	mov	r10, lr

	mov	r0,#0x2700			/* wait 200 us @ 99.5 MHz */
1:	subs	r0, r0, #1
	bne	1b
/*	TODO: complete step 1 for Synchronous Static memory*/

	ldr	r0, =0x48000000			/* MC_BASE */


	ldr	r1, =0x000012B3			/* MSC0_RRR0(1) | MSC0_RDN0(2) | MSC0_RDF0(11) | MSC0_RT0(3) */
	str	r1, [r0, #0x8]			/* MSC0_OFFSET */

	ldr	r1, [r0, #4]			/* MDREFR_OFFSET */
	ldr	r2, =0x01000FFF			/* MDREFR_K1FREE | MDREFR_DRI_MASK */
	bic	r1, r1, r2
#if defined( WEP_SDRAM_K4S281633 )
	orr	r1, r1, #48			/* MDREFR_DRI(48) */
#elif defined( WEP_SDRAM_K4S561633 )
	orr	r1, r1, #24			/* MDREFR_DRI(24) */
#else
#error SDRAM chip is not defined
#endif

	str	r1, [r0, #4]			/* MDREFR_OFFSET */

	orr	r1, r1, #0x00010000		/* MDREFR_K1RUN */
	bic	r1, r1, #0x00020000		/* MDREFR_K1DB2 */
	str	r1, [r0, #4]			/* MDREFR_OFFSET */

/*	Step 4.b - clear MDREFR:SLFRSH */
	bic	r1, r1, #0x00400000		/* MDREFR_SLFRSH */
	str	r1, [r0, #4]			/* MDREFR_OFFSET */

/*	Step 4.c - set MDREFR:E1PIN */
	orr	r1, r1, #0x00008000		/* MDREFR_E1PIN */
	str	r1, [r0, #4]			/* MDREFR_OFFSET */

#if defined( WEP_SDRAM_K4S281633 )
	ldr	r1, =0x00000AA8			/* MDCNFG_DTC0(2) | MDCNFG_DLATCH0 | MDCNFG_DCAC0(1) | MDCNFG_DRAC0(1) | MDCNFG_DNB0 */
#elif defined( WEP_SDRAM_K4S561633 )
	ldr	r1, =0x00000AC8			/* MDCNFG_DTC0(2) | MDCNFG_DLATCH0 | MDCNFG_DCAC0(1) | MDCNFG_DRAC0(2) | MDCNFG_DNB0 */
#else
#error SDRAM chip is not defined
#endif
	str	r1, [r0, #0]			/* MDCNFG_OFFSET */

	mov	r2,#0x2700			/* wait 200 us @ 99.5 MHz */
1:	subs	r2, r2, #1
	bne	1b

	mov	r2, #0xA0000000
	ldr	r3, [r2]
	ldr	r3, [r2]
	ldr	r3, [r2]
	ldr	r3, [r2]
	ldr	r3, [r2]
	ldr	r3, [r2]
	ldr	r3, [r2]
	ldr	r3, [r2]

	orr	r1, r1, #1			/* MDCNFG_DE0 */
	str	r1, [r0, #0]			/* MDCNFG_OFFSET */

/*	Step 10 - write MDMRS */
	mov	r1, #0
	str	r1, [r0, #0x40]			/* MDMRS_OFFSET */

/*	Step 11 - optional (TODO) */

	mov	pc,r10
