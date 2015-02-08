


#define BOOT_SEG	0xffff0000	/* linear segment of boot code */
#define a32		.byte 0x67;
#define o32		.byte 0x66;

.section .start16, "ax"
.code16
.globl start16
start16:
	/* First we let the BSP do some early initialization
	 * this code have to map the flash to its final position
	 */
	mov	$board_init16_ret, %bp
	jmp	board_init16
board_init16_ret:

	/* Turn of cache (this might require a 486-class CPU) */
	movl	%cr0, %eax
	orl	$0x60000000,%eax
	movl	%eax, %cr0
	wbinvd

	/* load the temporary Global Descriptor Table */
o32 cs	lgdt	gdt_ptr

	/* Now, we enter protected mode */
	movl	%cr0, %eax
	orl	$1,%eax
	movl	%eax, %cr0

	/* Flush the prefetch queue */
	jmp	ff
ff:
	/* Tell 32-bit code it is being entered from hard-reset */
	movw	$0x0001, %bx

	/* Finally jump to the 32bit initialization code */
	movw	$code32start, %ax
	movw	%ax,%bp
o32 cs	ljmp	*(%bp)

	/* 48-bit far pointer */
code32start:
	.long	_start		/* offset */
	.word	0x10		/* segment */

gdt_ptr:
	.word	0x20		/* limit (32 bytes = 4 GDT entries) */
	.long	BOOT_SEG + gdt	/* base */

	/* The GDT table ...
	 *
	 *	 Selector	Type
	 *	 0x00		NULL
	 *	 0x08		Unused
	 *	 0x10		32bit code
	 *	 0x18		32bit data/stack
	 */

gdt:
	.word	0, 0, 0, 0	/* NULL  */
	.word	0, 0, 0, 0	/* unused */

	.word	0xFFFF		/* 4Gb - (0x100000*0x1000 = 4Gb) */
	.word	0		/* base address = 0 */
	.word	0x9B00		/* code read/exec */
	.word	0x00CF		/* granularity = 4096, 386 (+5th nibble of limit) */

	.word	0xFFFF		/* 4Gb - (0x100000*0x1000 = 4Gb) */
	.word	0x0		/* base address = 0 */
	.word	0x9300		/* data read/write */
	.word	0x00CF		/* granularity = 4096, 386 (+5th nibble of limit) */
