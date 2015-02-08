


sc520_cdp_registers:
/* size    offset        value */
.word 1 ; .word 0x040 ; .long 0x00       /* SDRAM buffer control */
.word 2 ; .word 0xc08 ; .long 0x0001     /* GP CS offset */
.word 2 ; .word 0xc09 ; .long 0x0003     /* GP CS width */
.word 2 ; .word 0xc0a ; .long 0x0001     /* GP CS width */
.word 2 ; .word 0xc0b ; .long 0x0003     /* GP RD pulse width */
.word 2 ; .word 0xc0c ; .long 0x0001     /* GP RD offse */
.word 2 ; .word 0xc0d ; .long 0x0003     /* GP WR pulse width */
.word 2 ; .word 0xc0e ; .long 0x0001     /* GP WR offset */
.word 2 ; .word 0xc2c ; .long 0x003f     /* GPIO directionreg 31-16 */
.word 2 ; .word 0xc2a ; .long 0xe000     /* GPIO directionreg 15-0 */
.word 2 ; .word 0xc22 ; .long 0xffc0     /* GPIO pin function 31-16 reg */
.word 2 ; .word 0xc20 ; .long 0x1fff     /* GPIO pin function 15-0 reg */
.word 0 ; .word 0x000 ; .long 0x00

/* board early intialization */
.globl early_board_init
early_board_init:
	movl    $sc520_cdp_registers,%esi
init_loop:
	movl    $0xfffef000,%edi     /* MMCR base to edi */
	movw	(%esi), %bx          /* load size to bx */
	cmpw	$0, %bx              /* if size is 0 we're done */
	je	done
	xorl	%edx,%edx
	movw	2(%esi), %dx        /* load MMCR offset to dx */
	addl	%edx, %edi          /* add offset to base in edi */
	movl	4(%esi), %eax       /* load value in eax */
	cmpw	$1, %bx
	je	byte                 /* byte op? */
	cmpw	$2, %bx
	je	word                 /* word op? */
	movl	%eax, (%edi)         /* must be long, then */
	jmp	next
byte:   movb    %al,(%edi)
	jmp	next
word:	movw	%ax,(%edi)
next:	addl	$8, %esi             /* advance esi */
	jmp	init_loop

	/* light all leds */
done:   movl    $0xfffefc32,%edx
	movw    $0000,(%edx)

	jmp	*%ebp		     /* return to caller */


.globl show_boot_progress_asm
show_boot_progress_asm:
	movl    $0xfffefc32,%edx
	xorw    $0xffff, %ax
	movw    %ax,(%edx)
	jmp	*%ebp
