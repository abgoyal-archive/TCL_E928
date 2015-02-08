

#ifndef __ASM_REALMODE_H_
#define __ASM_REALMODE_H_
#include <asm/ptrace.h>

int bios_setup(void);
int enter_realmode(u16 seg, u16 off, struct pt_regs *in, struct pt_regs *out);
int enter_realmode_int(u8 lvl, struct pt_regs *in, struct pt_regs *out);

#endif
