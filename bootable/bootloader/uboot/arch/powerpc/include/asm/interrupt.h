
#ifndef INTERRUPT_H
#define INTERRUPT_H

#if defined(CONFIG_XILINX_440)
#include <asm/xilinx_irq.h>
#else
#include <asm/ppc4xx-uic.h>
#endif

void pic_enable(void);
void pic_irq_enable(unsigned int irq);
void pic_irq_disable(unsigned int irq);
void pic_irq_ack(unsigned int irq);
void external_interrupt(struct pt_regs *regs);
void interrupt_run_handler(int vec);

#endif
