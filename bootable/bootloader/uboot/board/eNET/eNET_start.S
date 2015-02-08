

#include "hardware.h"

/* board early intialization */
.globl early_board_init
early_board_init:
	/* No 32-bit board specific initialisation */
	jmp	*%ebp		/* return to caller */

.globl show_boot_progress_asm
show_boot_progress_asm:

	movb	%al, %dl	/* Create Working Copy */
	andb	$0x80, %dl	/* Mask in only Error bit */
	shrb	$0x02, %dl	/* Shift Error bit to Error LED */
	andb	$0x0f, %al	/* Mask out 'Error' bit */
	orb	%dl, %al	/* Mask in ERR LED */
	movw	$LED_LATCH_ADDRESS, %dx
	outb	%al, %dx
	jmp	*%ebp		/* return to caller */

.globl cpu_halt_asm
cpu_halt_asm:
	movb	$0x0f, %al
	movw	$LED_LATCH_ADDRESS, %dx
	outb	%al, %dx
	hlt
	jmp cpu_halt_asm
