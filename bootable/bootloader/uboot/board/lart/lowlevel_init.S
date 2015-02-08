


#include <config.h>
#include <version.h>


/* some parameters for the board */

MEM_BASE:	.long	0xa0000000
MEM_START:	.long	0xc0000000

#define	MDCNFG	0x00
#define MDCAS0	0x04
#define MDCAS1	0x08
#define MDCAS2	0x0c
#define MSC0	0x10
#define MSC1	0x14
#define MECR	0x18

mdcas0:		.long	0xc71c703f
mdcas1:		.long	0xffc71c71
mdcas2:		.long	0xffffffff
/* mdcnfg:		.long   0x0bb2bcbf */
mdcnfg:		.long	0x0334b22f	@ alt
/* mcs0:		.long   0xfff8fff8 */
msc0:		.long	0xad8c4888	@ alt
mecr:		.long	0x00060006
/* mecr:		.long	0x994a994a	@ alt */

/* setting up the memory */

.globl lowlevel_init
lowlevel_init:
	ldr	r0, MEM_BASE

	/* Setup the flash memory */
	ldr	r1, msc0
	str	r1, [r0, #MSC0]

	/* Set up the DRAM */

	/* MDCAS0 */
	ldr	r1, mdcas0
	str	r1, [r0, #MDCAS0]

	/* MDCAS1 */
	ldr	r1, mdcas1
	str	r1, [r0, #MDCAS1]

	/* MDCAS2 */
	ldr	r1, mdcas2
	str	r1, [r0, #MDCAS2]

	/* MDCNFG */
	ldr	r1, mdcnfg
	str	r1, [r0, #MDCNFG]

	/* Set up PCMCIA space */
	ldr	r1, mecr
	str	r1, [r0, #MECR]

	/* Load something to activate bank */
	ldr	r1, MEM_START

.rept	8
	ldr	r0, [r1]
.endr

	/* everything is fine now */
	mov	pc, lr
