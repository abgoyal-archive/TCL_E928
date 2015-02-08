

.text


.globl	data_to_flash
.globl	data_from_flash
	/* Subroutine that takes data in r0 and formats it so it will be in */
	/* the correct order for the internal flash */
	/* used for LART only */
data_to_flash:
	mov	r1, #0x0

	tst	r0, #0x00000001
	orrne	r1, r1, #0x00001000
	tst	r0, #0x00000002
	orrne	r1, r1, #0x00004000
	tst	r0, #0x00000004
	orrne	r1, r1, #0x00000800
	tst	r0, #0x00000008
	orrne	r1, r1, #0x00000200
	tst	r0, #0x00000010
	orrne	r1, r1, #0x00000001
	tst	r0, #0x00000020
	orrne	r1, r1, #0x00000004
	tst	r0, #0x00000040
	orrne	r1, r1, #0x00000080
	tst	r0, #0x00000080
	orrne	r1, r1, #0x00000020

	tst	r0, #0x00000100
	orrne	r1, r1, #0x00002000
	tst	r0, #0x00000200
	orrne	r1, r1, #0x00008000
	tst	r0, #0x00000400
	orrne	r1, r1, #0x00000400
	tst	r0, #0x00000800
	orrne	r1, r1, #0x00000100
	tst	r0, #0x00001000
	orrne	r1, r1, #0x00000002
	tst	r0, #0x00002000
	orrne	r1, r1, #0x00000008
	tst	r0, #0x00004000
	orrne	r1, r1, #0x00000040
	tst	r0, #0x00008000
	orrne	r1, r1, #0x00000010

	tst	r0, #0x00010000
	orrne	r1, r1, #0x00100000
	tst	r0, #0x00020000
	orrne	r1, r1, #0x00400000
	tst	r0, #0x00040000
	orrne	r1, r1, #0x00080000
	tst	r0, #0x00080000
	orrne	r1, r1, #0x00020000
	tst	r0, #0x00100000
	orrne	r1, r1, #0x01000000
	tst	r0, #0x00200000
	orrne	r1, r1, #0x04000000
	tst	r0, #0x00400000
	orrne	r1, r1, #0x80000000
	tst	r0, #0x00800000
	orrne	r1, r1, #0x20000000

	tst	r0, #0x01000000
	orrne	r1, r1, #0x00200000
	tst	r0, #0x02000000
	orrne	r1, r1, #0x00800000
	tst	r0, #0x04000000
	orrne	r1, r1, #0x00040000
	tst	r0, #0x08000000
	orrne	r1, r1, #0x00010000
	tst	r0, #0x10000000
	orrne	r1, r1, #0x02000000
	tst	r0, #0x20000000
	orrne	r1, r1, #0x08000000
	tst	r0, #0x40000000
	orrne	r1, r1, #0x40000000
	tst	r0, #0x80000000
	orrne	r1, r1, #0x10000000

	mov	r0, r1
	mov	pc, lr

	/* Takes data received from the flash, and unshuffles it. */
data_from_flash:
	mov	r1, #0x00

	tst	r0, #0x00000001
	orrne	r1, r1, #0x00000010
	tst	r0, #0x00000002
	orrne	r1, r1, #0x00001000
	tst	r0, #0x00000004
	orrne	r1, r1, #0x00000020
	tst	r0, #0x00000008
	orrne	r1, r1, #0x00002000
	tst	r0, #0x00000010
	orrne	r1, r1, #0x00008000
	tst	r0, #0x00000020
	orrne	r1, r1, #0x00000080
	tst	r0, #0x00000040
	orrne	r1, r1, #0x00004000
	tst	r0, #0x00000080
	orrne	r1, r1, #0x00000040

	tst	r0, #0x00000100
	orrne	r1, r1, #0x00000800
	tst	r0, #0x00000200
	orrne	r1, r1, #0x00000008
	tst	r0, #0x00000400
	orrne	r1, r1, #0x00000400
	tst	r0, #0x00000800
	orrne	r1, r1, #0x00000004
	tst	r0, #0x00001000
	orrne	r1, r1, #0x00000001
	tst	r0, #0x00002000
	orrne	r1, r1, #0x00000100
	tst	r0, #0x00004000
	orrne	r1, r1, #0x00000002
	tst	r0, #0x00008000
	orrne	r1, r1, #0x00000200

	tst	r0, #0x00010000
	orrne	r1, r1, #0x08000000
	tst	r0, #0x00020000
	orrne	r1, r1, #0x00080000
	tst	r0, #0x00040000
	orrne	r1, r1, #0x04000000
	tst	r0, #0x00080000
	orrne	r1, r1, #0x00040000
	tst	r0, #0x00100000
	orrne	r1, r1, #0x00010000
	tst	r0, #0x00200000
	orrne	r1, r1, #0x01000000
	tst	r0, #0x00400000
	orrne	r1, r1, #0x00020000
	tst	r0, #0x00800000
	orrne	r1, r1, #0x02000000

	tst	r0, #0x01000000
	orrne	r1, r1, #0x00100000
	tst	r0, #0x02000000
	orrne	r1, r1, #0x10000000
	tst	r0, #0x04000000
	orrne	r1, r1, #0x00200000
	tst	r0, #0x08000000
	orrne	r1, r1, #0x20000000
	tst	r0, #0x10000000
	orrne	r1, r1, #0x80000000
	tst	r0, #0x20000000
	orrne	r1, r1, #0x00800000
	tst	r0, #0x40000000
	orrne	r1, r1, #0x40000000
	tst	r0, #0x80000000
	orrne	r1, r1, #0x00400000

	mov	r0, r1
	mov	pc, lr
