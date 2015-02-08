

#ifndef _CPU_H_
#define _CPU_H_

#include <command.h>

void board_reset(void) __attribute__((__weak__));
void bfin_reset_or_hang(void) __attribute__((__noreturn__));
void bfin_panic(struct pt_regs *reg);
void dump(struct pt_regs *regs);

asmlinkage void trap(void);
asmlinkage void evt_default(void);

#endif
