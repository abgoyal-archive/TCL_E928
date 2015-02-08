

.globl reset_cpu
reset_cpu:
	ldr	r0, WDT_TGCR
	mov	r1, $0x08
	str	r1, [r0]
	ldr	r1, [r0]
	orr	r1, r1, $0x03
	str	r1, [r0]
	mov	r1, $0
	ldr	r0, WDT_TIM12
	str	r1, [r0]
	ldr	r0, WDT_TIM34
	str	r1, [r0]
	ldr	r0, WDT_PRD12
	str	r1, [r0]
	ldr	r0, WDT_PRD34
	str	r1, [r0]
	ldr	r0, WDT_TCR
	ldr	r1, [r0]
	orr	r1, r1, $0x40
	str	r1, [r0]
	ldr	r0, WDT_WDTCR
	ldr	r1, [r0]
	orr	r1, r1, $0x4000
	str	r1, [r0]
	ldr	r1, WDTCR_VAL1
	str	r1, [r0]
	ldr	r1, WDTCR_VAL2
	str	r1, [r0]
	/* Write an invalid value to the WDKEY field to trigger
	 * an immediate watchdog reset */
	mov     r1, $0x4000
	str     r1, [r0]
	nop
	nop
	nop
	nop
reset_cpu_loop:
	b	reset_cpu_loop

WDT_TGCR:
	.word	0x01c21c24
WDT_TIM12:
	.word	0x01c21c10
WDT_TIM34:
	.word	0x01c21c14
WDT_PRD12:
	.word	0x01c21c18
WDT_PRD34:
	.word	0x01c21c1c
WDT_TCR:
	.word	0x01c21c20
WDT_WDTCR:
	.word	0x01c21c28
WDTCR_VAL1:
	.word	0xa5c64000
WDTCR_VAL2:
	.word	0xda7e4000
