

	.align	5
.globl reset_cpu
reset_cpu:
	ldr	r1, rstctl1	/* get clkm1 reset ctl */
	mov	r3, #0x0
	strh	r3, [r1]	/* clear it */
	mov	r3, #0x8
	strh	r3, [r1]	/* force dsp+arm reset */
_loop_forever:
	b	_loop_forever

rstctl1:
	.word	0xfffece10
