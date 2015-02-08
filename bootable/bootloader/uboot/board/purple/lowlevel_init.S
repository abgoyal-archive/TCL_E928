

#include <config.h>
#include <asm/regdef.h>

#define MC_IOGP	0xBF800800

	.globl	lowlevel_init
lowlevel_init:
	li	t0, MC_IOGP
	li	t1, 0xf24
	sw	t1, 0(t0)
	jr	ra
	nop
