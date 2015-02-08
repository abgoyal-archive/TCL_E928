

#ifndef __X86EMU_X86EMUI_H
#define __X86EMU_X86EMUI_H


#if defined(__cplusplus) && !defined(_NO_INLINE)
#define _INLINE inline
#else
#define _INLINE static
#endif

/* Get rid of unused parameters in C++ compilation mode */

#ifdef __cplusplus
#define X86EMU_UNUSED(v)
#else
#define X86EMU_UNUSED(v)    v
#endif

#include "x86emu.h"
#include "x86emu/regs.h"
#include "x86emu/debug.h"
#include "x86emu/decode.h"
#include "x86emu/ops.h"
#include "x86emu/prim_ops.h"
#ifndef __KERNEL__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#endif

#define printk printf


/*--------------------------- Inline Functions ----------------------------*/

#ifdef  __cplusplus
extern "C" {			/* Use "C" linkage when in C++ mode */
#endif

	extern u8(X86APIP sys_rdb) (u32 addr);
	extern u16(X86APIP sys_rdw) (u32 addr);
	extern u32(X86APIP sys_rdl) (u32 addr);
	extern void (X86APIP sys_wrb) (u32 addr, u8 val);
	extern void (X86APIP sys_wrw) (u32 addr, u16 val);
	extern void (X86APIP sys_wrl) (u32 addr, u32 val);

	extern u8(X86APIP sys_inb) (X86EMU_pioAddr addr);
	extern u16(X86APIP sys_inw) (X86EMU_pioAddr addr);
	extern u32(X86APIP sys_inl) (X86EMU_pioAddr addr);
	extern void (X86APIP sys_outb) (X86EMU_pioAddr addr, u8 val);
	extern void (X86APIP sys_outw) (X86EMU_pioAddr addr, u16 val);
	extern void (X86APIP sys_outl) (X86EMU_pioAddr addr, u32 val);

#ifdef  __cplusplus
}				/* End of "C" linkage for C++       */
#endif
#endif				/* __X86EMU_X86EMUI_H */
