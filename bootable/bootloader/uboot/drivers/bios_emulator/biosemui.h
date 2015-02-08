

#ifndef __BIOSEMUI_H
#define __BIOSEMUI_H

#include "biosemu.h"
#include <asm/io.h>
/*---------------------- Macros and type definitions ----------------------*/

#ifdef DEBUG
#define DB(x)	x
#else
#define DB(x)	do{}while(0);
#endif

#define BIOS_SEG	0xfff0
extern X86EMU_sysEnv _X86EMU_env;
#define M		_X86EMU_env


#ifdef __BIG_ENDIAN__
#define readb_le(base)	    *((u8*)(base))
#define readw_le(base)	    ((u16)readb_le(base) | ((u16)readb_le((base) + 1) << 8))
#define readl_le(base)	    ((u32)readb_le((base) + 0) | ((u32)readb_le((base) + 1) << 8) | \
			    ((u32)readb_le((base) + 2) << 16) | ((u32)readb_le((base) + 3) << 24))
#define writeb_le(base, v)  *((u8*)(base)) = (v)
#define writew_le(base, v)  writeb_le(base + 0, (v >> 0) & 0xff),	\
			    writeb_le(base + 1, (v >> 8) & 0xff)
#define writel_le(base, v)  writeb_le(base + 0, (v >> 0) & 0xff),	\
			    writeb_le(base + 1, (v >> 8) & 0xff),	\
			    writeb_le(base + 2, (v >> 16) & 0xff),	\
			    writeb_le(base + 3, (v >> 24) & 0xff)
#else
#define readb_le(base)	    *((u8*)(base))
#define readw_le(base)	    *((u16*)(base))
#define readl_le(base)	    *((u32*)(base))
#define writeb_le(base, v)  *((u8*)(base)) = (v)
#define writew_le(base, v)  *((u16*)(base)) = (v)
#define writel_le(base, v)  *((u32*)(base)) = (v)
#endif

typedef enum {
	REG_READ_BYTE = 0,
	REG_READ_WORD = 1,
	REG_READ_DWORD = 2,
	REG_WRITE_BYTE = 3,
	REG_WRITE_WORD = 4,
	REG_WRITE_DWORD = 5
} RegisterFlags;

typedef enum {
	PORT_BYTE = 1,
	PORT_WORD = 2,
	PORT_DWORD = 3,
} PortInfoFlags;

typedef struct {
	u8 type;
	u32 defVal;
	u32 finalVal;
} BE_portInfo;

#define PM_inpb(port)	inb(port+VIDEO_IO_OFFSET)
#define PM_inpw(port)	inw(port+VIDEO_IO_OFFSET)
#define PM_inpd(port)	inl(port+VIDEO_IO_OFFSET)
#define PM_outpb(port,val)	outb(val,port+VIDEO_IO_OFFSET)
#define PM_outpw(port,val)	outw(val,port+VIDEO_IO_OFFSET)
#define PM_outpd(port,val)	outl(val,port+VIDEO_IO_OFFSET)

#define LOG_inpb(port)	PM_inpb(port)
#define LOG_inpw(port)	PM_inpw(port)
#define LOG_inpd(port)	PM_inpd(port)
#define LOG_outpb(port,val)	PM_outpb(port,val)
#define LOG_outpw(port,val)	PM_outpw(port,val)
#define LOG_outpd(port,val)	PM_outpd(port,val)

/*-------------------------- Function Prototypes --------------------------*/

/* bios.c */

void _BE_bios_init(u32 * intrTab);
void _BE_setup_funcs(void);

/* besys.c */
#define DEBUG_IO()	(M.x86.debug & DEBUG_IO_TRACE_F)

u8 X86API BE_rdb(u32 addr);
u16 X86API BE_rdw(u32 addr);
u32 X86API BE_rdl(u32 addr);
void X86API BE_wrb(u32 addr, u8 val);
void X86API BE_wrw(u32 addr, u16 val);
void X86API BE_wrl(u32 addr, u32 val);

u8 X86API BE_inb(X86EMU_pioAddr port);
u16 X86API BE_inw(X86EMU_pioAddr port);
u32 X86API BE_inl(X86EMU_pioAddr port);
void X86API BE_outb(X86EMU_pioAddr port, u8 val);
void X86API BE_outw(X86EMU_pioAddr port, u16 val);
void X86API BE_outl(X86EMU_pioAddr port, u32 val);
#endif
/* __BIOSEMUI_H */
