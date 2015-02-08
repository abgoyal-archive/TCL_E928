

#include <common.h>
#include "x86emu/x86emui.h"

/*------------------------- Global Variables ------------------------------*/

X86EMU_sysEnv _X86EMU_env;	/* Global emulator machine state */
X86EMU_intrFuncs _X86EMU_intrTab[256];

int debug_intr;

/*----------------------------- Implementation ----------------------------*/

u8 X86API rdb(u32 addr)
{
	return 0;
}

u16 X86API rdw(u32 addr)
{
	return 0;
}

u32 X86API rdl(u32 addr)
{
	return 0;
}

void X86API wrb(u32 addr, u8 val)
{
}

void X86API wrw(u32 addr, u16 val)
{
}

void X86API wrl(u32 addr, u32 val)
{
}

static u8 X86API p_inb(X86EMU_pioAddr addr)
{
	DB(if (DEBUG_IO_TRACE())
	   printk("inb %#04x \n", addr);)
		return 0;
}

static u16 X86API p_inw(X86EMU_pioAddr addr)
{
	DB(if (DEBUG_IO_TRACE())
	   printk("inw %#04x \n", addr);)
		return 0;
}

static u32 X86API p_inl(X86EMU_pioAddr addr)
{
	DB(if (DEBUG_IO_TRACE())
	   printk("inl %#04x \n", addr);)
		return 0;
}

static void X86API p_outb(X86EMU_pioAddr addr, u8 val)
{
	DB(if (DEBUG_IO_TRACE())
	   printk("outb %#02x -> %#04x \n", val, addr);)
		return;
}

static void X86API p_outw(X86EMU_pioAddr addr, u16 val)
{
	DB(if (DEBUG_IO_TRACE())
	   printk("outw %#04x -> %#04x \n", val, addr);)
		return;
}

static void X86API p_outl(X86EMU_pioAddr addr, u32 val)
{
	DB(if (DEBUG_IO_TRACE())
	   printk("outl %#08x -> %#04x \n", val, addr);)
		return;
}

/*------------------------- Global Variables ------------------------------*/

u8(X86APIP sys_rdb) (u32 addr) = rdb;
u16(X86APIP sys_rdw) (u32 addr) = rdw;
u32(X86APIP sys_rdl) (u32 addr) = rdl;
void (X86APIP sys_wrb) (u32 addr, u8 val) = wrb;
void (X86APIP sys_wrw) (u32 addr, u16 val) = wrw;
void (X86APIP sys_wrl) (u32 addr, u32 val) = wrl;
u8(X86APIP sys_inb) (X86EMU_pioAddr addr) = p_inb;
u16(X86APIP sys_inw) (X86EMU_pioAddr addr) = p_inw;
u32(X86APIP sys_inl) (X86EMU_pioAddr addr) = p_inl;
void (X86APIP sys_outb) (X86EMU_pioAddr addr, u8 val) = p_outb;
void (X86APIP sys_outw) (X86EMU_pioAddr addr, u16 val) = p_outw;
void (X86APIP sys_outl) (X86EMU_pioAddr addr, u32 val) = p_outl;

/*----------------------------- Setup -------------------------------------*/

void X86EMU_setupMemFuncs(X86EMU_memFuncs * funcs)
{
	sys_rdb = funcs->rdb;
	sys_rdw = funcs->rdw;
	sys_rdl = funcs->rdl;
	sys_wrb = funcs->wrb;
	sys_wrw = funcs->wrw;
	sys_wrl = funcs->wrl;
}

void X86EMU_setupPioFuncs(X86EMU_pioFuncs * funcs)
{
	sys_inb = funcs->inb;
	sys_inw = funcs->inw;
	sys_inl = funcs->inl;
	sys_outb = funcs->outb;
	sys_outw = funcs->outw;
	sys_outl = funcs->outl;
}

void X86EMU_setupIntrFuncs(X86EMU_intrFuncs funcs[])
{
	int i;

	for (i = 0; i < 256; i++)
		_X86EMU_intrTab[i] = NULL;
	if (funcs) {
		for (i = 0; i < 256; i++)
			_X86EMU_intrTab[i] = funcs[i];
	}
}

void X86EMU_prepareForInt(int num)
{
	push_word((u16) M.x86.R_FLG);
	CLEAR_FLAG(F_IF);
	CLEAR_FLAG(F_TF);
	push_word(M.x86.R_CS);
	M.x86.R_CS = mem_access_word(num * 4 + 2);
	push_word(M.x86.R_IP);
	M.x86.R_IP = mem_access_word(num * 4);
	M.x86.intr = 0;
}
