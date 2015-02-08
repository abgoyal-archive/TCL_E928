

#ifndef __X86EMU_OPS_H
#define __X86EMU_OPS_H

extern void (*x86emu_optab[0x100])(u8 op1);
extern void (*x86emu_optab2[0x100])(u8 op2);

#endif /* __X86EMU_OPS_H */
