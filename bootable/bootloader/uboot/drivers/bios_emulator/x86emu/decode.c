
#include <common.h>
#include "x86emu/x86emui.h"

/*----------------------------- Implementation ----------------------------*/

static void x86emu_intr_handle(void)
{
    u8	intno;

    if (M.x86.intr & INTR_SYNCH) {
	intno = M.x86.intno;
	if (_X86EMU_intrTab[intno]) {
	    (*_X86EMU_intrTab[intno])(intno);
	} else {
	    push_word((u16)M.x86.R_FLG);
	    CLEAR_FLAG(F_IF);
	    CLEAR_FLAG(F_TF);
	    push_word(M.x86.R_CS);
	    M.x86.R_CS = mem_access_word(intno * 4 + 2);
	    push_word(M.x86.R_IP);
	    M.x86.R_IP = mem_access_word(intno * 4);
	    M.x86.intr = 0;
	}
    }
}

void x86emu_intr_raise(
    u8 intrnum)
{
    M.x86.intno = intrnum;
    M.x86.intr |= INTR_SYNCH;
}

void X86EMU_exec(void)
{
    u8 op1;

    M.x86.intr = 0;
    DB(x86emu_end_instr();)

    for (;;) {
DB(	if (CHECK_IP_FETCH())
	    x86emu_check_ip_access();)
	/* If debugging, save the IP and CS values. */
	SAVE_IP_CS(M.x86.R_CS, M.x86.R_IP);
	INC_DECODED_INST_LEN(1);
	if (M.x86.intr) {
	    if (M.x86.intr & INTR_HALTED) {
DB(		if (M.x86.R_SP != 0) {
		    printk("halted\n");
		    X86EMU_trace_regs();
		    }
		else {
		    if (M.x86.debug)
			printk("Service completed successfully\n");
		    })
		return;
	    }
	    if (((M.x86.intr & INTR_SYNCH) && (M.x86.intno == 0 || M.x86.intno == 2)) ||
		!ACCESS_FLAG(F_IF)) {
		x86emu_intr_handle();
	    }
	}
	op1 = (*sys_rdb)(((u32)M.x86.R_CS << 4) + (M.x86.R_IP++));
	(*x86emu_optab[op1])(op1);
	if (M.x86.debug & DEBUG_EXIT) {
	    M.x86.debug &= ~DEBUG_EXIT;
	    return;
	}
    }
}

void X86EMU_halt_sys(void)
{
    M.x86.intr |= INTR_HALTED;
}

void fetch_decode_modrm(
    int *mod,
    int *regh,
    int *regl)
{
    int fetched;

DB( if (CHECK_IP_FETCH())
	x86emu_check_ip_access();)
    fetched = (*sys_rdb)(((u32)M.x86.R_CS << 4) + (M.x86.R_IP++));
    INC_DECODED_INST_LEN(1);
    *mod  = (fetched >> 6) & 0x03;
    *regh = (fetched >> 3) & 0x07;
    *regl = (fetched >> 0) & 0x07;
}

u8 fetch_byte_imm(void)
{
    u8 fetched;

DB( if (CHECK_IP_FETCH())
	x86emu_check_ip_access();)
    fetched = (*sys_rdb)(((u32)M.x86.R_CS << 4) + (M.x86.R_IP++));
    INC_DECODED_INST_LEN(1);
    return fetched;
}

u16 fetch_word_imm(void)
{
    u16 fetched;

DB( if (CHECK_IP_FETCH())
	x86emu_check_ip_access();)
    fetched = (*sys_rdw)(((u32)M.x86.R_CS << 4) + (M.x86.R_IP));
    M.x86.R_IP += 2;
    INC_DECODED_INST_LEN(2);
    return fetched;
}

u32 fetch_long_imm(void)
{
    u32 fetched;

DB( if (CHECK_IP_FETCH())
	x86emu_check_ip_access();)
    fetched = (*sys_rdl)(((u32)M.x86.R_CS << 4) + (M.x86.R_IP));
    M.x86.R_IP += 4;
    INC_DECODED_INST_LEN(4);
    return fetched;
}

_INLINE u32 get_data_segment(void)
{
#define GET_SEGMENT(segment)
    switch (M.x86.mode & SYSMODE_SEGMASK) {
      case 0:			/* default case: use ds register */
      case SYSMODE_SEGOVR_DS:
      case SYSMODE_SEGOVR_DS | SYSMODE_SEG_DS_SS:
	return	M.x86.R_DS;
      case SYSMODE_SEG_DS_SS:	/* non-overridden, use ss register */
	return	M.x86.R_SS;
      case SYSMODE_SEGOVR_CS:
      case SYSMODE_SEGOVR_CS | SYSMODE_SEG_DS_SS:
	return	M.x86.R_CS;
      case SYSMODE_SEGOVR_ES:
      case SYSMODE_SEGOVR_ES | SYSMODE_SEG_DS_SS:
	return	M.x86.R_ES;
      case SYSMODE_SEGOVR_FS:
      case SYSMODE_SEGOVR_FS | SYSMODE_SEG_DS_SS:
	return	M.x86.R_FS;
      case SYSMODE_SEGOVR_GS:
      case SYSMODE_SEGOVR_GS | SYSMODE_SEG_DS_SS:
	return	M.x86.R_GS;
      case SYSMODE_SEGOVR_SS:
      case SYSMODE_SEGOVR_SS | SYSMODE_SEG_DS_SS:
	return	M.x86.R_SS;
      default:
#ifdef	DEBUG
	printk("error: should not happen:  multiple overrides.\n");
#endif
	HALT_SYS();
	return 0;
    }
}

u8 fetch_data_byte(
    uint offset)
{
#ifdef DEBUG
    if (CHECK_DATA_ACCESS())
	x86emu_check_data_access((u16)get_data_segment(), offset);
#endif
    return (*sys_rdb)((get_data_segment() << 4) + offset);
}

u16 fetch_data_word(
    uint offset)
{
#ifdef DEBUG
    if (CHECK_DATA_ACCESS())
	x86emu_check_data_access((u16)get_data_segment(), offset);
#endif
    return (*sys_rdw)((get_data_segment() << 4) + offset);
}

u32 fetch_data_long(
    uint offset)
{
#ifdef DEBUG
    if (CHECK_DATA_ACCESS())
	x86emu_check_data_access((u16)get_data_segment(), offset);
#endif
    return (*sys_rdl)((get_data_segment() << 4) + offset);
}

u8 fetch_data_byte_abs(
    uint segment,
    uint offset)
{
#ifdef DEBUG
    if (CHECK_DATA_ACCESS())
	x86emu_check_data_access(segment, offset);
#endif
    return (*sys_rdb)(((u32)segment << 4) + offset);
}

u16 fetch_data_word_abs(
    uint segment,
    uint offset)
{
#ifdef DEBUG
    if (CHECK_DATA_ACCESS())
	x86emu_check_data_access(segment, offset);
#endif
    return (*sys_rdw)(((u32)segment << 4) + offset);
}

u32 fetch_data_long_abs(
    uint segment,
    uint offset)
{
#ifdef DEBUG
    if (CHECK_DATA_ACCESS())
	x86emu_check_data_access(segment, offset);
#endif
    return (*sys_rdl)(((u32)segment << 4) + offset);
}

void store_data_byte(
    uint offset,
    u8 val)
{
#ifdef DEBUG
    if (CHECK_DATA_ACCESS())
	x86emu_check_data_access((u16)get_data_segment(), offset);
#endif
    (*sys_wrb)((get_data_segment() << 4) + offset, val);
}

void store_data_word(
    uint offset,
    u16 val)
{
#ifdef DEBUG
    if (CHECK_DATA_ACCESS())
	x86emu_check_data_access((u16)get_data_segment(), offset);
#endif
    (*sys_wrw)((get_data_segment() << 4) + offset, val);
}

void store_data_long(
    uint offset,
    u32 val)
{
#ifdef DEBUG
    if (CHECK_DATA_ACCESS())
	x86emu_check_data_access((u16)get_data_segment(), offset);
#endif
    (*sys_wrl)((get_data_segment() << 4) + offset, val);
}

void store_data_byte_abs(
    uint segment,
    uint offset,
    u8 val)
{
#ifdef DEBUG
    if (CHECK_DATA_ACCESS())
	x86emu_check_data_access(segment, offset);
#endif
    (*sys_wrb)(((u32)segment << 4) + offset, val);
}

void store_data_word_abs(
    uint segment,
    uint offset,
    u16 val)
{
#ifdef DEBUG
    if (CHECK_DATA_ACCESS())
	x86emu_check_data_access(segment, offset);
#endif
    (*sys_wrw)(((u32)segment << 4) + offset, val);
}

void store_data_long_abs(
    uint segment,
    uint offset,
    u32 val)
{
#ifdef DEBUG
    if (CHECK_DATA_ACCESS())
	x86emu_check_data_access(segment, offset);
#endif
    (*sys_wrl)(((u32)segment << 4) + offset, val);
}

u8* decode_rm_byte_register(
    int reg)
{
    switch (reg) {
      case 0:
	DECODE_PRINTF("AL");
	return &M.x86.R_AL;
      case 1:
	DECODE_PRINTF("CL");
	return &M.x86.R_CL;
      case 2:
	DECODE_PRINTF("DL");
	return &M.x86.R_DL;
      case 3:
	DECODE_PRINTF("BL");
	return &M.x86.R_BL;
      case 4:
	DECODE_PRINTF("AH");
	return &M.x86.R_AH;
      case 5:
	DECODE_PRINTF("CH");
	return &M.x86.R_CH;
      case 6:
	DECODE_PRINTF("DH");
	return &M.x86.R_DH;
      case 7:
	DECODE_PRINTF("BH");
	return &M.x86.R_BH;
    }
    HALT_SYS();
    return NULL;		/* NOT REACHED OR REACHED ON ERROR */
}

u16* decode_rm_word_register(
    int reg)
{
    switch (reg) {
      case 0:
	DECODE_PRINTF("AX");
	return &M.x86.R_AX;
      case 1:
	DECODE_PRINTF("CX");
	return &M.x86.R_CX;
      case 2:
	DECODE_PRINTF("DX");
	return &M.x86.R_DX;
      case 3:
	DECODE_PRINTF("BX");
	return &M.x86.R_BX;
      case 4:
	DECODE_PRINTF("SP");
	return &M.x86.R_SP;
      case 5:
	DECODE_PRINTF("BP");
	return &M.x86.R_BP;
      case 6:
	DECODE_PRINTF("SI");
	return &M.x86.R_SI;
      case 7:
	DECODE_PRINTF("DI");
	return &M.x86.R_DI;
    }
    HALT_SYS();
    return NULL;		/* NOTREACHED OR REACHED ON ERROR */
}

u32* decode_rm_long_register(
    int reg)
{
    switch (reg) {
      case 0:
	DECODE_PRINTF("EAX");
	return &M.x86.R_EAX;
      case 1:
	DECODE_PRINTF("ECX");
	return &M.x86.R_ECX;
      case 2:
	DECODE_PRINTF("EDX");
	return &M.x86.R_EDX;
      case 3:
	DECODE_PRINTF("EBX");
	return &M.x86.R_EBX;
      case 4:
	DECODE_PRINTF("ESP");
	return &M.x86.R_ESP;
      case 5:
	DECODE_PRINTF("EBP");
	return &M.x86.R_EBP;
      case 6:
	DECODE_PRINTF("ESI");
	return &M.x86.R_ESI;
      case 7:
	DECODE_PRINTF("EDI");
	return &M.x86.R_EDI;
    }
    HALT_SYS();
    return NULL;		/* NOTREACHED OR REACHED ON ERROR */
}

u16* decode_rm_seg_register(
    int reg)
{
    switch (reg) {
      case 0:
	DECODE_PRINTF("ES");
	return &M.x86.R_ES;
      case 1:
	DECODE_PRINTF("CS");
	return &M.x86.R_CS;
      case 2:
	DECODE_PRINTF("SS");
	return &M.x86.R_SS;
      case 3:
	DECODE_PRINTF("DS");
	return &M.x86.R_DS;
      case 4:
	DECODE_PRINTF("FS");
	return &M.x86.R_FS;
      case 5:
	DECODE_PRINTF("GS");
	return &M.x86.R_GS;
      case 6:
      case 7:
	DECODE_PRINTF("ILLEGAL SEGREG");
	break;
    }
    HALT_SYS();
    return NULL;		/* NOT REACHED OR REACHED ON ERROR */
}

unsigned decode_sib_si(
    int scale,
    int index)
{
    scale = 1 << scale;
    if (scale > 1) {
	DECODE_PRINTF2("[%d*", scale);
    } else {
	DECODE_PRINTF("[");
    }
    switch (index) {
      case 0:
	DECODE_PRINTF("EAX]");
	return M.x86.R_EAX * index;
      case 1:
	DECODE_PRINTF("ECX]");
	return M.x86.R_ECX * index;
      case 2:
	DECODE_PRINTF("EDX]");
	return M.x86.R_EDX * index;
      case 3:
	DECODE_PRINTF("EBX]");
	return M.x86.R_EBX * index;
      case 4:
	DECODE_PRINTF("0]");
	return 0;
      case 5:
	DECODE_PRINTF("EBP]");
	return M.x86.R_EBP * index;
      case 6:
	DECODE_PRINTF("ESI]");
	return M.x86.R_ESI * index;
      case 7:
	DECODE_PRINTF("EDI]");
	return M.x86.R_EDI * index;
    }
    HALT_SYS();
    return 0;			/* NOT REACHED OR REACHED ON ERROR */
}

unsigned decode_sib_address(
    int mod)
{
    int sib   = fetch_byte_imm();
    int ss    = (sib >> 6) & 0x03;
    int index = (sib >> 3) & 0x07;
    int base  = sib & 0x07;
    int offset = 0;
    int displacement;

    switch (base) {
      case 0:
	DECODE_PRINTF("[EAX]");
	offset = M.x86.R_EAX;
	break;
      case 1:
	DECODE_PRINTF("[ECX]");
	offset = M.x86.R_ECX;
	break;
      case 2:
	DECODE_PRINTF("[EDX]");
	offset = M.x86.R_EDX;
	break;
      case 3:
	DECODE_PRINTF("[EBX]");
	offset = M.x86.R_EBX;
	break;
      case 4:
	DECODE_PRINTF("[ESP]");
	offset = M.x86.R_ESP;
	break;
      case 5:
	switch (mod) {
	  case 0:
	    displacement = (s32)fetch_long_imm();
	    DECODE_PRINTF2("[%d]", displacement);
	    offset = displacement;
	    break;
	  case 1:
	    displacement = (s8)fetch_byte_imm();
	    DECODE_PRINTF2("[%d][EBP]", displacement);
	    offset = M.x86.R_EBP + displacement;
	    break;
	  case 2:
	    displacement = (s32)fetch_long_imm();
	    DECODE_PRINTF2("[%d][EBP]", displacement);
	    offset = M.x86.R_EBP + displacement;
	    break;
	  default:
	    HALT_SYS();
	}
	DECODE_PRINTF("[EAX]");
	offset = M.x86.R_EAX;
	break;
      case 6:
	DECODE_PRINTF("[ESI]");
	offset = M.x86.R_ESI;
	break;
      case 7:
	DECODE_PRINTF("[EDI]");
	offset = M.x86.R_EDI;
	break;
      default:
	HALT_SYS();
    }
    offset += decode_sib_si(ss, index);
    return offset;

}

unsigned decode_rm00_address(
    int rm)
{
    unsigned offset;

    if (M.x86.mode & SYSMODE_PREFIX_ADDR) {
	/* 32-bit addressing */
	switch (rm) {
	  case 0:
	    DECODE_PRINTF("[EAX]");
	    return M.x86.R_EAX;
	  case 1:
	    DECODE_PRINTF("[ECX]");
	    return M.x86.R_ECX;
	  case 2:
	    DECODE_PRINTF("[EDX]");
	    return M.x86.R_EDX;
	  case 3:
	    DECODE_PRINTF("[EBX]");
	    return M.x86.R_EBX;
	  case 4:
	    return decode_sib_address(0);
	  case 5:
	    offset = fetch_long_imm();
	    DECODE_PRINTF2("[%08x]", offset);
	    return offset;
	  case 6:
	    DECODE_PRINTF("[ESI]");
	    return M.x86.R_ESI;
	  case 7:
	    DECODE_PRINTF("[EDI]");
	    return M.x86.R_EDI;
	}
    } else {
	/* 16-bit addressing */
	switch (rm) {
	  case 0:
	    DECODE_PRINTF("[BX+SI]");
	    return (M.x86.R_BX + M.x86.R_SI) & 0xffff;
	  case 1:
	    DECODE_PRINTF("[BX+DI]");
	    return (M.x86.R_BX + M.x86.R_DI) & 0xffff;
	  case 2:
	    DECODE_PRINTF("[BP+SI]");
	    M.x86.mode |= SYSMODE_SEG_DS_SS;
	    return (M.x86.R_BP + M.x86.R_SI) & 0xffff;
	  case 3:
	    DECODE_PRINTF("[BP+DI]");
	    M.x86.mode |= SYSMODE_SEG_DS_SS;
	    return (M.x86.R_BP + M.x86.R_DI) & 0xffff;
	  case 4:
	    DECODE_PRINTF("[SI]");
	    return M.x86.R_SI;
	  case 5:
	    DECODE_PRINTF("[DI]");
	    return M.x86.R_DI;
	  case 6:
	    offset = fetch_word_imm();
	    DECODE_PRINTF2("[%04x]", offset);
	    return offset;
	  case 7:
	    DECODE_PRINTF("[BX]");
	    return M.x86.R_BX;
	}
    }
    HALT_SYS();
    return 0;
}

unsigned decode_rm01_address(
    int rm)
{
    int displacement;

    if (M.x86.mode & SYSMODE_PREFIX_ADDR) {
	/* 32-bit addressing */
	if (rm != 4)
	    displacement = (s8)fetch_byte_imm();
	else
	    displacement = 0;

	switch (rm) {
	  case 0:
	    DECODE_PRINTF2("%d[EAX]", displacement);
	    return M.x86.R_EAX + displacement;
	  case 1:
	    DECODE_PRINTF2("%d[ECX]", displacement);
	    return M.x86.R_ECX + displacement;
	  case 2:
	    DECODE_PRINTF2("%d[EDX]", displacement);
	    return M.x86.R_EDX + displacement;
	  case 3:
	    DECODE_PRINTF2("%d[EBX]", displacement);
	    return M.x86.R_EBX + displacement;
	  case 4: {
	    int offset = decode_sib_address(1);
	    displacement = (s8)fetch_byte_imm();
	    DECODE_PRINTF2("[%d]", displacement);
	    return offset + displacement;
	  }
	  case 5:
	    DECODE_PRINTF2("%d[EBP]", displacement);
	    return M.x86.R_EBP + displacement;
	  case 6:
	    DECODE_PRINTF2("%d[ESI]", displacement);
	    return M.x86.R_ESI + displacement;
	  case 7:
	    DECODE_PRINTF2("%d[EDI]", displacement);
	    return M.x86.R_EDI + displacement;
	}
    } else {
	/* 16-bit addressing */
	displacement = (s8)fetch_byte_imm();
	switch (rm) {
	  case 0:
	    DECODE_PRINTF2("%d[BX+SI]", displacement);
	    return (M.x86.R_BX + M.x86.R_SI + displacement) & 0xffff;
	  case 1:
	    DECODE_PRINTF2("%d[BX+DI]", displacement);
	    return (M.x86.R_BX + M.x86.R_DI + displacement) & 0xffff;
	  case 2:
	    DECODE_PRINTF2("%d[BP+SI]", displacement);
	    M.x86.mode |= SYSMODE_SEG_DS_SS;
	    return (M.x86.R_BP + M.x86.R_SI + displacement) & 0xffff;
	  case 3:
	    DECODE_PRINTF2("%d[BP+DI]", displacement);
	    M.x86.mode |= SYSMODE_SEG_DS_SS;
	    return (M.x86.R_BP + M.x86.R_DI + displacement) & 0xffff;
	  case 4:
	    DECODE_PRINTF2("%d[SI]", displacement);
	    return (M.x86.R_SI + displacement) & 0xffff;
	  case 5:
	    DECODE_PRINTF2("%d[DI]", displacement);
	    return (M.x86.R_DI + displacement) & 0xffff;
	  case 6:
	    DECODE_PRINTF2("%d[BP]", displacement);
	    M.x86.mode |= SYSMODE_SEG_DS_SS;
	    return (M.x86.R_BP + displacement) & 0xffff;
	  case 7:
	    DECODE_PRINTF2("%d[BX]", displacement);
	    return (M.x86.R_BX + displacement) & 0xffff;
	}
    }
    HALT_SYS();
    return 0;			/* SHOULD NOT HAPPEN */
}

unsigned decode_rm10_address(
    int rm)
{
    if (M.x86.mode & SYSMODE_PREFIX_ADDR) {
	int displacement;

	/* 32-bit addressing */
	if (rm != 4)
	    displacement = (s32)fetch_long_imm();
	else
	    displacement = 0;

	switch (rm) {
	  case 0:
	    DECODE_PRINTF2("%d[EAX]", displacement);
	    return M.x86.R_EAX + displacement;
	  case 1:
	    DECODE_PRINTF2("%d[ECX]", displacement);
	    return M.x86.R_ECX + displacement;
	  case 2:
	    DECODE_PRINTF2("%d[EDX]", displacement);
	    return M.x86.R_EDX + displacement;
	  case 3:
	    DECODE_PRINTF2("%d[EBX]", displacement);
	    return M.x86.R_EBX + displacement;
	  case 4: {
	    int offset = decode_sib_address(2);
	    displacement = (s32)fetch_long_imm();
	    DECODE_PRINTF2("[%d]", displacement);
	    return offset + displacement;
	  }
	  case 5:
	    DECODE_PRINTF2("%d[EBP]", displacement);
	    return M.x86.R_EBP + displacement;
	  case 6:
	    DECODE_PRINTF2("%d[ESI]", displacement);
	    return M.x86.R_ESI + displacement;
	  case 7:
	    DECODE_PRINTF2("%d[EDI]", displacement);
	    return M.x86.R_EDI + displacement;
	}
    } else {
	int displacement = (s16)fetch_word_imm();

	/* 16-bit addressing */
	switch (rm) {
	  case 0:
	    DECODE_PRINTF2("%d[BX+SI]", displacement);
	    return (M.x86.R_BX + M.x86.R_SI + displacement) & 0xffff;
	  case 1:
	    DECODE_PRINTF2("%d[BX+DI]", displacement);
	    return (M.x86.R_BX + M.x86.R_DI + displacement) & 0xffff;
	  case 2:
	    DECODE_PRINTF2("%d[BP+SI]", displacement);
	    M.x86.mode |= SYSMODE_SEG_DS_SS;
	    return (M.x86.R_BP + M.x86.R_SI + displacement) & 0xffff;
	  case 3:
	    DECODE_PRINTF2("%d[BP+DI]", displacement);
	    M.x86.mode |= SYSMODE_SEG_DS_SS;
	    return (M.x86.R_BP + M.x86.R_DI + displacement) & 0xffff;
	  case 4:
	    DECODE_PRINTF2("%d[SI]", displacement);
	    return (M.x86.R_SI + displacement) & 0xffff;
	  case 5:
	    DECODE_PRINTF2("%d[DI]", displacement);
	    return (M.x86.R_DI + displacement) & 0xffff;
	  case 6:
	    DECODE_PRINTF2("%d[BP]", displacement);
	    M.x86.mode |= SYSMODE_SEG_DS_SS;
	    return (M.x86.R_BP + displacement) & 0xffff;
	  case 7:
	    DECODE_PRINTF2("%d[BX]", displacement);
	    return (M.x86.R_BX + displacement) & 0xffff;
	}
    }
    HALT_SYS();
    return 0;			/* SHOULD NOT HAPPEN */
}


unsigned decode_rmXX_address(int mod, int rm)
{
  if(mod == 0)
    return decode_rm00_address(rm);
  if(mod == 1)
    return decode_rm01_address(rm);
  return decode_rm10_address(rm);
}
