

#ifndef __ASM_INTERRUPT_H_
#define __ASM_INTERRUPT_H_ 1

/* arch/i386/cpu/interrupts.c */
void set_vector(u8 intnum, void *routine);

/* arch/i386/lib/interupts.c */
void disable_irq(int irq);
void enable_irq(int irq);

/* Architecture specific functions */
void mask_irq(int irq);
void unmask_irq(int irq);
void specific_eoi(int irq);

extern char exception_stack[];

#define __isr__ void __attribute__ ((regparm(0)))

#endif
