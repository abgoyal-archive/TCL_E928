

#ifndef __X86EMU_X86EMU_H
#define __X86EMU_X86EMU_H

#include <asm/types.h>
#include <common.h>
#include <pci.h>
#include <asm/io.h>
#define X86API
#define X86APIP *
typedef u16 X86EMU_pioAddr;

#include "x86emu/regs.h"

/*---------------------- Macros and type definitions ----------------------*/

#if defined (CONFIG_ARM)
#define GAS_LINE_COMMENT	"@"
#elif defined(CONFIG_MIPS) || defined(CONFIG_PPC)
#define GAS_LINE_COMMENT	"#"
#elif defined (CONFIG_SH)
#define GAS_LINE_COMMENT	"!"
#endif

#define GOT2_TYPE	".got2,\"aw\"\t"GAS_LINE_COMMENT

#pragma pack(1)

typedef struct {
	u8(X86APIP inb) (X86EMU_pioAddr addr);
	u16(X86APIP inw) (X86EMU_pioAddr addr);
	u32(X86APIP inl) (X86EMU_pioAddr addr);
	void (X86APIP outb) (X86EMU_pioAddr addr, u8 val);
	void (X86APIP outw) (X86EMU_pioAddr addr, u16 val);
	void (X86APIP outl) (X86EMU_pioAddr addr, u32 val);
} X86EMU_pioFuncs;

typedef struct {
	u8(X86APIP rdb) (u32 addr);
	u16(X86APIP rdw) (u32 addr);
	u32(X86APIP rdl) (u32 addr);
	void (X86APIP wrb) (u32 addr, u8 val);
	void (X86APIP wrw) (u32 addr, u16 val);
	void (X86APIP wrl) (u32 addr, u32 val);
} X86EMU_memFuncs;

extern u8 X86API rdb(u32 addr);
extern u16 X86API rdw(u32 addr);
extern u32 X86API rdl(u32 addr);
extern void X86API wrb(u32 addr, u8 val);
extern void X86API wrw(u32 addr, u16 val);
extern void X86API wrl(u32 addr, u32 val);

#pragma pack()

/*--------------------- type definitions -----------------------------------*/

typedef void (X86APIP X86EMU_intrFuncs) (int num);
extern X86EMU_intrFuncs _X86EMU_intrTab[256];

/*-------------------------- Function Prototypes --------------------------*/

#ifdef  __cplusplus
extern "C" {			/* Use "C" linkage when in C++ mode */
#endif

	void X86EMU_setupMemFuncs(X86EMU_memFuncs * funcs);
	void X86EMU_setupPioFuncs(X86EMU_pioFuncs * funcs);
	void X86EMU_setupIntrFuncs(X86EMU_intrFuncs funcs[]);
	void X86EMU_prepareForInt(int num);

/* decode.c */

	void X86EMU_exec(void);
	void X86EMU_halt_sys(void);

#ifdef  DEBUG
#define HALT_SYS()  \
    printf("halt_sys: file %s, line %d\n", __FILE__, __LINE__), \
    X86EMU_halt_sys()
#else
#define HALT_SYS()  X86EMU_halt_sys()
#endif

/* Debug options */

#define DEBUG_DECODE_F          0x0001	/* print decoded instruction  */
#define DEBUG_TRACE_F           0x0002	/* dump regs before/after execution */
#define DEBUG_STEP_F            0x0004
#define DEBUG_DISASSEMBLE_F     0x0008
#define DEBUG_BREAK_F           0x0010
#define DEBUG_SVC_F             0x0020
#define DEBUG_SAVE_CS_IP        0x0040
#define DEBUG_FS_F              0x0080
#define DEBUG_PROC_F            0x0100
#define DEBUG_SYSINT_F          0x0200	/* bios system interrupts. */
#define DEBUG_TRACECALL_F       0x0400
#define DEBUG_INSTRUMENT_F      0x0800
#define DEBUG_MEM_TRACE_F       0x1000
#define DEBUG_IO_TRACE_F        0x2000
#define DEBUG_TRACECALL_REGS_F  0x4000
#define DEBUG_DECODE_NOPRINT_F  0x8000
#define DEBUG_EXIT              0x10000
#define DEBUG_SYS_F             (DEBUG_SVC_F|DEBUG_FS_F|DEBUG_PROC_F)

	void X86EMU_trace_regs(void);
	void X86EMU_trace_xregs(void);
	void X86EMU_dump_memory(u16 seg, u16 off, u32 amt);
	int X86EMU_trace_on(void);
	int X86EMU_trace_off(void);

#ifdef  __cplusplus
}				/* End of "C" linkage for C++       */
#endif
#endif				/* __X86EMU_X86EMU_H */
