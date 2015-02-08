

#include <asm/arch/cpu.h>

#define S5PC100_SWRESET			0xE0200000
#define S5PC110_SWRESET			0xE0102000

.globl reset_cpu
reset_cpu:
	ldr	r1, =S5PC1XX_PRO_ID
	ldr	r2, [r1]
	ldr	r4, =0x00010000
	and	r4, r2, r4
	cmp	r4, #0
	bne	110f
	/* S5PC100 */
	ldr	r1, =S5PC100_SWRESET
	ldr	r2, =0xC100
	b	200f
110:	/* S5PC110 */
	ldr	r1, =S5PC110_SWRESET
	mov	r2, #1
200:
	str	r2, [r1]
_loop_forever:
	b	_loop_forever
