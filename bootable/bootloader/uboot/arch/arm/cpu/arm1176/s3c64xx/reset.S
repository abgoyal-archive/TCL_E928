

#include <asm/arch/s3c6400.h>

.globl reset_cpu
reset_cpu:
	ldr	r1, =ELFIN_CLOCK_POWER_BASE
	ldr	r2, [r1, #SYS_ID_OFFSET]
	ldr	r3, =0xffff
	and	r2, r3, r2, lsr #12
	str	r2, [r1, #SW_RST_OFFSET]
_loop_forever:
	b	_loop_forever
