

/* Reset vector, jumps to start16.S */

.extern start16

.section .resetvec, "ax"
.code16
reset_vector:
	cli
	cld
	jmp start16

	.org 0xf
	nop
