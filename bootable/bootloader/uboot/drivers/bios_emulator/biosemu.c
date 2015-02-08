

#include <malloc.h>
#include <common.h>
#include "biosemui.h"

BE_sysEnv _BE_env = {{0}};
static X86EMU_memFuncs _BE_mem __attribute__((section(GOT2_TYPE))) = {
	BE_rdb,
	BE_rdw,
	BE_rdl,
	BE_wrb,
	BE_wrw,
	BE_wrl,
	};

static X86EMU_pioFuncs _BE_pio __attribute__((section(GOT2_TYPE))) = {
	BE_inb,
	BE_inw,
	BE_inl,
	BE_outb,
	BE_outw,
	BE_outl,
	};

#define OFF(addr)	(u16)(((addr) >> 0) & 0xffff)
#define SEG(addr)	(u16)(((addr) >> 4) & 0xf000)

int X86API BE_init(u32 debugFlags, int memSize, BE_VGAInfo * info, int shared)
{
#if !defined(__DRIVER__)  && !defined(__KERNEL__)

	PM_init();
#endif
	memset(&M, 0, sizeof(M));
	if (memSize < 20480){
		printf("Emulator requires at least 20Kb of memory!\n");
		return 0;
	}

	M.mem_base = malloc(memSize);

	if (M.mem_base == NULL){
		printf("Biosemu:Out of memory!");
		return 0;
	}
	M.mem_size = memSize;

	_BE_env.emulateVGA = 0;
	_BE_env.busmem_base = (unsigned long)malloc(128 * 1024);
	if ((void *)_BE_env.busmem_base == NULL){
		printf("Biosemu:Out of memory!");
		return 0;
	}
	M.x86.debug = debugFlags;
	_BE_bios_init((u32*)info->LowMem);
	X86EMU_setupMemFuncs(&_BE_mem);
	X86EMU_setupPioFuncs(&_BE_pio);
	BE_setVGA(info);
	return 1;
}

void X86API BE_setVGA(BE_VGAInfo * info)
{

#ifdef __KERNEL__
	_BE_env.vgaInfo.function = info->function;
	_BE_env.vgaInfo.device = info->device;
	_BE_env.vgaInfo.bus = info->bus;
	_BE_env.vgaInfo.pcidev = info->pcidev;
#else
	_BE_env.vgaInfo.pciInfo = info->pciInfo;
#endif
	_BE_env.vgaInfo.BIOSImage = info->BIOSImage;
	if (info->BIOSImage) {
		_BE_env.biosmem_base = (ulong) info->BIOSImage;
		_BE_env.biosmem_limit = 0xC0000 + info->BIOSImageLen - 1;
	} else {
		_BE_env.biosmem_base = _BE_env.busmem_base + 0x20000;
		_BE_env.biosmem_limit = 0xC7FFF;
	}
	if ((info->LowMem[0] == 0) && (info->LowMem[1] == 0) &&
	    (info->LowMem[2] == 0) && (info->LowMem[3] == 0))
		_BE_bios_init((u32 *) info->LowMem);
	memcpy((u8 *) M.mem_base, info->LowMem, sizeof(info->LowMem));
}

void X86API BE_getVGA(BE_VGAInfo * info)
{
#ifdef __KERNEL__
	info->function = _BE_env.vgaInfo.function;
	info->device = _BE_env.vgaInfo.device;
	info->bus = _BE_env.vgaInfo.bus;
	info->pcidev = _BE_env.vgaInfo.pcidev;
#else
	info->pciInfo = _BE_env.vgaInfo.pciInfo;
#endif
	info->BIOSImage = _BE_env.vgaInfo.BIOSImage;
	memcpy(info->LowMem, (u8 *) M.mem_base, sizeof(info->LowMem));
}

void *X86API BE_mapRealPointer(uint r_seg, uint r_off)
{
	u32 addr = ((u32) r_seg << 4) + r_off;

	if (addr >= 0xC0000 && addr <= _BE_env.biosmem_limit) {
		return (void *)(_BE_env.biosmem_base + addr - 0xC0000);
	} else if (addr >= 0xA0000 && addr <= 0xFFFFF) {
		return (void *)(_BE_env.busmem_base + addr - 0xA0000);
	}
	return (void *)(M.mem_base + addr);
}

void *X86API BE_getVESABuf(uint * len, uint * rseg, uint * roff)
{
	*len = 1024;
	*rseg = SEG(0x03C00);
	*roff = OFF(0x03C00);
	return (void *)(M.mem_base + ((u32) * rseg << 4) + *roff);
}

void X86API BE_exit(void)
{
	free(M.mem_base);
	free((void *)_BE_env.busmem_base);
}

void X86API BE_callRealMode(uint seg, uint off, RMREGS * regs, RMSREGS * sregs)
{
	M.x86.R_EAX = regs->e.eax;
	M.x86.R_EBX = regs->e.ebx;
	M.x86.R_ECX = regs->e.ecx;
	M.x86.R_EDX = regs->e.edx;
	M.x86.R_ESI = regs->e.esi;
	M.x86.R_EDI = regs->e.edi;
	M.x86.R_DS = sregs->ds;
	M.x86.R_ES = sregs->es;
	M.x86.R_FS = sregs->fs;
	M.x86.R_GS = sregs->gs;

	((u8 *) M.mem_base)[0x4000] = 0x9A;
	((u8 *) M.mem_base)[0x4001] = (u8) off;
	((u8 *) M.mem_base)[0x4002] = (u8) (off >> 8);
	((u8 *) M.mem_base)[0x4003] = (u8) seg;
	((u8 *) M.mem_base)[0x4004] = (u8) (seg >> 8);
	((u8 *) M.mem_base)[0x4005] = 0xF1;	/* Illegal op-code */
	M.x86.R_CS = SEG(0x04000);
	M.x86.R_IP = OFF(0x04000);

	M.x86.R_SS = SEG(M.mem_size - 2);
	M.x86.R_SP = OFF(M.mem_size - 2) + 2;

	X86EMU_exec();

	regs->e.cflag = M.x86.R_EFLG & F_CF;
	regs->e.eax = M.x86.R_EAX;
	regs->e.ebx = M.x86.R_EBX;
	regs->e.ecx = M.x86.R_ECX;
	regs->e.edx = M.x86.R_EDX;
	regs->e.esi = M.x86.R_ESI;
	regs->e.edi = M.x86.R_EDI;
	sregs->ds = M.x86.R_DS;
	sregs->es = M.x86.R_ES;
	sregs->fs = M.x86.R_FS;
	sregs->gs = M.x86.R_GS;
}

int X86API BE_int86(int intno, RMREGS * in, RMREGS * out)
{
	M.x86.R_EAX = in->e.eax;
	M.x86.R_EBX = in->e.ebx;
	M.x86.R_ECX = in->e.ecx;
	M.x86.R_EDX = in->e.edx;
	M.x86.R_ESI = in->e.esi;
	M.x86.R_EDI = in->e.edi;
	((u8 *) M.mem_base)[0x4000] = 0xCD;
	((u8 *) M.mem_base)[0x4001] = (u8) intno;
	((u8 *) M.mem_base)[0x4002] = 0xF1;
	M.x86.R_CS = SEG(0x04000);
	M.x86.R_IP = OFF(0x04000);

	M.x86.R_SS = SEG(M.mem_size - 1);
	M.x86.R_SP = OFF(M.mem_size - 1) - 1;

	X86EMU_exec();
	out->e.cflag = M.x86.R_EFLG & F_CF;
	out->e.eax = M.x86.R_EAX;
	out->e.ebx = M.x86.R_EBX;
	out->e.ecx = M.x86.R_ECX;
	out->e.edx = M.x86.R_EDX;
	out->e.esi = M.x86.R_ESI;
	out->e.edi = M.x86.R_EDI;
	return out->x.ax;
}

int X86API BE_int86x(int intno, RMREGS * in, RMREGS * out, RMSREGS * sregs)
{
	M.x86.R_EAX = in->e.eax;
	M.x86.R_EBX = in->e.ebx;
	M.x86.R_ECX = in->e.ecx;
	M.x86.R_EDX = in->e.edx;
	M.x86.R_ESI = in->e.esi;
	M.x86.R_EDI = in->e.edi;
	M.x86.R_DS = sregs->ds;
	M.x86.R_ES = sregs->es;
	M.x86.R_FS = sregs->fs;
	M.x86.R_GS = sregs->gs;
	((u8 *) M.mem_base)[0x4000] = 0xCD;
	((u8 *) M.mem_base)[0x4001] = (u8) intno;
	((u8 *) M.mem_base)[0x4002] = 0xF1;
	M.x86.R_CS = SEG(0x04000);
	M.x86.R_IP = OFF(0x04000);

	M.x86.R_SS = SEG(M.mem_size - 1);
	M.x86.R_SP = OFF(M.mem_size - 1) - 1;

	X86EMU_exec();
	out->e.cflag = M.x86.R_EFLG & F_CF;
	out->e.eax = M.x86.R_EAX;
	out->e.ebx = M.x86.R_EBX;
	out->e.ecx = M.x86.R_ECX;
	out->e.edx = M.x86.R_EDX;
	out->e.esi = M.x86.R_ESI;
	out->e.edi = M.x86.R_EDI;
	sregs->ds = M.x86.R_DS;
	sregs->es = M.x86.R_ES;
	sregs->fs = M.x86.R_FS;
	sregs->gs = M.x86.R_GS;
	return out->x.ax;
}
