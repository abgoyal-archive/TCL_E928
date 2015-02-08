

#ifndef _NIOS_PTRACE_H
#define _NIOS_PTRACE_H

struct pt_regs {
	unsigned global[8];
	unsigned in[8];
	unsigned status;
	unsigned istatus;
	unsigned retaddr;
};


#endif /* _NIOS_PTRACE_H */
