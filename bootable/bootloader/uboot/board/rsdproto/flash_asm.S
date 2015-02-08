

#include <ppc_asm.tmpl>
#include <ppc_defs.h>

	.globl	ull_write
ull_write:
	lfd		0,0(r4)
	stfd	0,0(r3)
	blr

	.globl	ull_read
ull_read:
	lfd		0, 0(r3)
	stfd	0, 0(r4)
	blr
