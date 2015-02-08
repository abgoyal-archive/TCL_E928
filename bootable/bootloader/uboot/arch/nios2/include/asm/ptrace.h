

#ifndef __ASM_NIOS2_PTRACE_H_
#define __ASM_NIOS2_PTRACE_H_

struct pt_regs {
	unsigned reg[32];
	unsigned status;
};


#endif /* __ASM_NIOS2_PTRACE_H_ */
