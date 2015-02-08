

#ifndef __X86EMU_REGS_H
#define __X86EMU_REGS_H

/*---------------------- Macros and type definitions ----------------------*/

#pragma pack(1)


#ifdef	__BIG_ENDIAN__

typedef struct {
	u32 e_reg;
} I32_reg_t;

typedef struct {
	u16 filler0, x_reg;
} I16_reg_t;

typedef struct {
	u8 filler0, filler1, h_reg, l_reg;
} I8_reg_t;

#else				/* !__BIG_ENDIAN__ */

typedef struct {
	u32 e_reg;
} I32_reg_t;

typedef struct {
	u16 x_reg;
} I16_reg_t;

typedef struct {
	u8 l_reg, h_reg;
} I8_reg_t;

#endif				/* BIG_ENDIAN */

typedef union {
	I32_reg_t I32_reg;
	I16_reg_t I16_reg;
	I8_reg_t I8_reg;
} i386_general_register;

struct i386_general_regs {
	i386_general_register A, B, C, D;
};

typedef struct i386_general_regs Gen_reg_t;

struct i386_special_regs {
	i386_general_register SP, BP, SI, DI, IP;
	u32 FLAGS;
};


#undef CS
#undef DS
#undef SS
#undef ES
#undef FS
#undef GS

struct i386_segment_regs {
	u16 CS, DS, SS, ES, FS, GS;
};

/* 8 bit registers */
#define R_AH  gen.A.I8_reg.h_reg
#define R_AL  gen.A.I8_reg.l_reg
#define R_BH  gen.B.I8_reg.h_reg
#define R_BL  gen.B.I8_reg.l_reg
#define R_CH  gen.C.I8_reg.h_reg
#define R_CL  gen.C.I8_reg.l_reg
#define R_DH  gen.D.I8_reg.h_reg
#define R_DL  gen.D.I8_reg.l_reg

/* 16 bit registers */
#define R_AX  gen.A.I16_reg.x_reg
#define R_BX  gen.B.I16_reg.x_reg
#define R_CX  gen.C.I16_reg.x_reg
#define R_DX  gen.D.I16_reg.x_reg

/* 32 bit extended registers */
#define R_EAX  gen.A.I32_reg.e_reg
#define R_EBX  gen.B.I32_reg.e_reg
#define R_ECX  gen.C.I32_reg.e_reg
#define R_EDX  gen.D.I32_reg.e_reg

/* special registers */
#define R_SP  spc.SP.I16_reg.x_reg
#define R_BP  spc.BP.I16_reg.x_reg
#define R_SI  spc.SI.I16_reg.x_reg
#define R_DI  spc.DI.I16_reg.x_reg
#define R_IP  spc.IP.I16_reg.x_reg
#define R_FLG spc.FLAGS

/* special registers */
#define R_SP  spc.SP.I16_reg.x_reg
#define R_BP  spc.BP.I16_reg.x_reg
#define R_SI  spc.SI.I16_reg.x_reg
#define R_DI  spc.DI.I16_reg.x_reg
#define R_IP  spc.IP.I16_reg.x_reg
#define R_FLG spc.FLAGS

/* special registers */
#define R_ESP  spc.SP.I32_reg.e_reg
#define R_EBP  spc.BP.I32_reg.e_reg
#define R_ESI  spc.SI.I32_reg.e_reg
#define R_EDI  spc.DI.I32_reg.e_reg
#define R_EIP  spc.IP.I32_reg.e_reg
#define R_EFLG spc.FLAGS

/* segment registers */
#define R_CS  seg.CS
#define R_DS  seg.DS
#define R_SS  seg.SS
#define R_ES  seg.ES
#define R_FS  seg.FS
#define R_GS  seg.GS

/* flag conditions   */
#define FB_CF 0x0001		/* CARRY flag  */
#define FB_PF 0x0004		/* PARITY flag */
#define FB_AF 0x0010		/* AUX	flag   */
#define FB_ZF 0x0040		/* ZERO flag   */
#define FB_SF 0x0080		/* SIGN flag   */
#define FB_TF 0x0100		/* TRAP flag   */
#define FB_IF 0x0200		/* INTERRUPT ENABLE flag */
#define FB_DF 0x0400		/* DIR flag    */
#define FB_OF 0x0800		/* OVERFLOW flag */

/* 80286 and above always have bit#1 set */
#define F_ALWAYS_ON  (0x0002)	/* flag bits always on */

#define F_MSK (FB_CF|FB_PF|FB_AF|FB_ZF|FB_SF|FB_TF|FB_IF|FB_DF|FB_OF)

/* following bits masked in to a 16bit quantity */

#define F_CF 0x0001		/* CARRY flag  */
#define F_PF 0x0004		/* PARITY flag */
#define F_AF 0x0010		/* AUX	flag   */
#define F_ZF 0x0040		/* ZERO flag   */
#define F_SF 0x0080		/* SIGN flag   */
#define F_TF 0x0100		/* TRAP flag   */
#define F_IF 0x0200		/* INTERRUPT ENABLE flag */
#define F_DF 0x0400		/* DIR flag    */
#define F_OF 0x0800		/* OVERFLOW flag */

#define TOGGLE_FLAG(flag)	(M.x86.R_FLG ^= (flag))
#define SET_FLAG(flag)		(M.x86.R_FLG |= (flag))
#define CLEAR_FLAG(flag)	(M.x86.R_FLG &= ~(flag))
#define ACCESS_FLAG(flag)	(M.x86.R_FLG & (flag))
#define CLEARALL_FLAG(m)	(M.x86.R_FLG = 0)

#define CONDITIONAL_SET_FLAG(COND,FLAG) \
  if (COND) SET_FLAG(FLAG); else CLEAR_FLAG(FLAG)

#define F_PF_CALC 0x010000	/* PARITY flag has been calced	  */
#define F_ZF_CALC 0x020000	/* ZERO flag has been calced	  */
#define F_SF_CALC 0x040000	/* SIGN flag has been calced	  */

#define F_ALL_CALC	0xff0000	/* All have been calced	  */

#define SYSMODE_SEG_DS_SS	0x00000001
#define SYSMODE_SEGOVR_CS	0x00000002
#define SYSMODE_SEGOVR_DS	0x00000004
#define SYSMODE_SEGOVR_ES	0x00000008
#define SYSMODE_SEGOVR_FS	0x00000010
#define SYSMODE_SEGOVR_GS	0x00000020
#define SYSMODE_SEGOVR_SS	0x00000040
#define SYSMODE_PREFIX_REPE	0x00000080
#define SYSMODE_PREFIX_REPNE	0x00000100
#define SYSMODE_PREFIX_DATA	0x00000200
#define SYSMODE_PREFIX_ADDR	0x00000400
#define SYSMODE_INTR_PENDING	0x10000000
#define SYSMODE_EXTRN_INTR	0x20000000
#define SYSMODE_HALTED		0x40000000

#define SYSMODE_SEGMASK (SYSMODE_SEG_DS_SS	| \
			 SYSMODE_SEGOVR_CS	| \
			 SYSMODE_SEGOVR_DS	| \
			 SYSMODE_SEGOVR_ES	| \
			 SYSMODE_SEGOVR_FS	| \
			 SYSMODE_SEGOVR_GS	| \
			 SYSMODE_SEGOVR_SS)
#define SYSMODE_CLRMASK (SYSMODE_SEG_DS_SS	| \
			 SYSMODE_SEGOVR_CS	| \
			 SYSMODE_SEGOVR_DS	| \
			 SYSMODE_SEGOVR_ES	| \
			 SYSMODE_SEGOVR_FS	| \
			 SYSMODE_SEGOVR_GS	| \
			 SYSMODE_SEGOVR_SS	| \
			 SYSMODE_PREFIX_DATA	| \
			 SYSMODE_PREFIX_ADDR)

#define	 INTR_SYNCH	      0x1
#define	 INTR_ASYNCH	      0x2
#define	 INTR_HALTED	      0x4

typedef struct {
	struct i386_general_regs gen;
	struct i386_special_regs spc;
	struct i386_segment_regs seg;
	/*
	 * MODE contains information on:
	 *  REPE prefix		    2 bits  repe,repne
	 *  SEGMENT overrides	    5 bits  normal,DS,SS,CS,ES
	 *  Delayed flag set	    3 bits  (zero, signed, parity)
	 *  reserved		    6 bits
	 *  interrupt #		    8 bits  instruction raised interrupt
	 *  BIOS video segregs	    4 bits
	 *  Interrupt Pending	    1 bits
	 *  Extern interrupt	    1 bits
	 *  Halted		    1 bits
	 */
	long mode;
	u8 intno;
	volatile int intr;	/* mask of pending interrupts */
	int debug;
#ifdef DEBUG
	int check;
	u16 saved_ip;
	u16 saved_cs;
	int enc_pos;
	int enc_str_pos;
	char decode_buf[32];	/* encoded byte stream	*/
	char decoded_buf[256];	/* disassembled strings */
#endif
} X86EMU_regs;

#undef x86
typedef struct {
	X86EMU_regs x86;
	u8 *mem_base;
	u32 mem_size;
	void *private;
} X86EMU_sysEnv;

#pragma pack()

/*----------------------------- Global Variables --------------------------*/

#ifdef	__cplusplus
extern "C" {			/* Use "C" linkage when in C++ mode */
#endif


	extern X86EMU_sysEnv _X86EMU_env;
#define	  M		_X86EMU_env

/*-------------------------- Function Prototypes --------------------------*/

/* Function to log information at runtime */

#ifndef __KERNEL__
	void printk(const char *fmt, ...);
#endif

#ifdef	__cplusplus
}				/* End of "C" linkage for C++	    */
#endif
#endif				/* __X86EMU_REGS_H */
