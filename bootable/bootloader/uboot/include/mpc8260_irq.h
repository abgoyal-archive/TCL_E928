
#ifndef _MPC8260_IRQ_H
#define _MPC8260_IRQ_H

/****************************************************************************/
/* most of this was ripped out of include/asm-ppc/irq.h from the Linux/PPC  */
/* source. There was no copyright information in the file.		    */

#define NR_IRQS			64

#define NR_SIU_INTS	64

#define	SIU_INT_SMC1		((uint)0x04)
#define	SIU_INT_SMC2		((uint)0x05)
#define	SIU_INT_IRQ1		((uint)0x13)
#define	SIU_INT_IRQ2		((uint)0x14)
#define	SIU_INT_IRQ3		((uint)0x15)
#define	SIU_INT_IRQ4		((uint)0x16)
#define	SIU_INT_IRQ5		((uint)0x17)
#define	SIU_INT_IRQ6		((uint)0x18)
#define	SIU_INT_IRQ7		((uint)0x19)
#define	SIU_INT_FCC1		((uint)0x20)
#define	SIU_INT_FCC2		((uint)0x21)
#define	SIU_INT_FCC3		((uint)0x22)
#define	SIU_INT_SCC1		((uint)0x28)
#define	SIU_INT_SCC2		((uint)0x29)
#define	SIU_INT_SCC3		((uint)0x2a)
#define	SIU_INT_SCC4		((uint)0x2b)

#define NR_MASK_WORDS	((NR_IRQS + 31) / 32)

#endif /* _MPC8260_IRQ_H */
