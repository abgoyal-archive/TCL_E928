


#include <config.h>
#include <version.h>


/* some parameters for the board */
/* setting up the memory */
#define	SRAM_START	0x60000000
#define	SRAM_SIZE	0x0000c000

.globl lowlevel_init
lowlevel_init:
	mov	r0, #0x70		/* 32-bit code + data, MMU mandatory */
	mcr	p15, 0, r0, c1, c0, 0	/* MMU init */

	mov	r0, #0
	mcr	p15, 0, r0, c7, c7, 0	/* flush v3/v4 cache */
	mcr	p15, 0, r0, c8, c7, 0	/* flush v4 TLB */

	mov	r0, #0x80000000		/* I/O base */

	mov	r1, #0x6		/* CLKCTL_73 in SYSCON3 */
	add	r2, r0, #0x2200		/* address of SYSCON3 in r2 */
	str	r1, [r2]		/* set clock speed to 73.728 MHz */

	mov	r1, #0x81		/* 64KHz DRAM refresh period */
	str	r1, [r0, #0x200]	/* set DRFPR */

	mov	r1, #0x500		/* permanent enable, 16bits wide */
	add	r1, r1, #0x42		/* 128Mbit, CAS lat = 2 SDRAM */
	add	r2, r0, #0x2300		/* load address in r2 */
	str	r1, [r2]

	mov	r1, #0x100		/* SDRAM refresh rate */
	add	r2, r0, #0x2340		/* load address in r2 */
	str	r1, [r2]

	mov	sp, #SRAM_START		/* init stack pointer */
	add	sp, sp, #SRAM_SIZE

	/* everything is fine now */
	mov	pc, lr
