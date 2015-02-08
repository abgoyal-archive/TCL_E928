
/* $Id$ */

#ifndef _PPC_H
#define _PPC_H


enum OP_FIELD {
  O_AA = 1, O_BD, O_BI, O_BO, O_crbD, O_crbA, O_crbB, O_CRM, O_d, O_frC, O_frD,
  O_frS, O_IMM, O_LI, O_LK, O_MB, O_ME, O_NB, O_OE, O_rA, O_rB, O_Rc, O_rD,
  O_rS, O_SH, O_SIMM, O_SR, O_TO, O_UIMM, O_crfD, O_crfS, O_L, O_spr, O_tbr,
  O_cr2 };

struct operand {
  enum OP_FIELD	field;		/* The operand identifier from the
				   enum above */

  char *	name;		/* Symbolic name of this operand */

  unsigned int	bits;		/* The number of bits used by this
				   operand */

  unsigned int	shift;		/* How far to the right the operand
				   should be shifted so that it is
				   aligned at the beginning of the
				   word */

  unsigned int	hint;		/* A bitwise-inclusive-OR of the
				   values shown below.  These are used
				   tell the disassembler how to print
				   this operand */
};

/* Values for operand hint */
#define OH_SILENT	0x01	/* dont print this operand */
#define OH_ADDR		0x02	/* this operand is an address */
#define OH_REG		0x04	/* this operand is a register */
#define OH_SPR		0x08	/* this operand is an SPR */
#define OH_TBR		0x10	/* this operand is a TBR */
#define OH_OFFSET	0x20	/* this operand is an offset */
#define OH_LITERAL      0x40    /* a literal string */




#define GET_OPCD(i) (((unsigned long)(i) >> 26) & 0x3f)
#define MAKE_OPCODE(i) ((((unsigned long)(i)) & 0x3f) << 26)




#define I_OPCODE(i,aa,lk) (MAKE_OPCODE(i) | (((aa) & 0x1) << 1) | ((lk) & 0x1))
#define I_MASK I_OPCODE(0x3f,0x1,0x1)



#define B_OPCODE(i,aa,lk) (MAKE_OPCODE(i) | (((aa) & 0x1) << 1) | ((lk) & 0x1))
#define B_MASK B_OPCODE(0x3f,0x1,0x1)



#define SC_OPCODE(i) (MAKE_OPCODE(i) | 0x2)
#define SC_MASK SC_OPCODE(0x3f)



#define D_OPCODE(i) MAKE_OPCODE(i)
#define D_MASK MAKE_OPCODE(0x3f)



#define DS_OPCODE(i,xo) (MAKE_OPCODE(i) | ((xo) & 0x3))
#define DS_MASK DS_OPCODE(0x3f,0x1)



#define X_OPCODE(i,xo,rc) (MAKE_OPCODE(i) | (((xo) & 0x3ff) << 1) | \
			   ((rc) & 0x1))
#define X_MASK X_OPCODE(0x3f,0x3ff,0x1)



#define XL_OPCODE(i,xo,lk) (MAKE_OPCODE(i) | (((xo) & 0x3ff) << 1) | \
			    ((lk) & 0x1))
#define XL_MASK XL_OPCODE(0x3f,0x3ff,0x1)



#define XFX_OPCODE(i,xo,rc) (MAKE_OPCODE(i) | (((xo) & 0x3ff) << 1) | \
			     ((rc) & 0x1))
#define XFX_MASK XFX_OPCODE(0x3f,0x3ff,0x1)



#define XFL_OPCODE(i,xo,rc) (MAKE_OPCODE(i) | (((xo) & 0x3ff) << 1) | \
			     ((rc) & 0x1))
#define XFL_MASK XFL_OPCODE(0x3f,0x3ff,0x1)



#define XS_OPCODE(i,xo,rc) (MAKE_OPCODE(i) | (((xo) & 0x1ff) << 2) | \
			     ((rc) & 0x1))
#define XS_MASK XS_OPCODE(0x3f,0x1ff,0x1)



#define XO_OPCODE(i,xo,oe,rc) (MAKE_OPCODE(i) | (((oe) & 0x1) << 10) | \
			       (((xo) & 0x1ff) << 1) | ((rc) & 0x1))
#define XO_MASK XO_OPCODE(0x3f,0x1ff,0x1,0x1)



#define A_OPCODE(i,xo,rc) (MAKE_OPCODE(i) | (((xo) & 0x1f) << 1) | \
			   ((rc) & 0x1))
#define A_MASK A_OPCODE(0x3f,0x1f,0x1)



#define M_OPCODE(i,rc) (MAKE_OPCODE(i) | ((rc) & 0x1))
#define M_MASK M_OPCODE(0x3f,0x1)



#define MD_OPCODE(i,xo,rc) (MAKE_OPCODE(i) | (((xo) & 0x7) << 2) | \
			   ((rc) & 0x1))
#define MD_MASK MD_OPCODE(0x3f,0x7,0x1)



#define MDS_OPCODE(i,xo,rc) (MAKE_OPCODE(i) | (((xo) & 0xf) << 1) | \
			   ((rc) & 0x1))
#define MDS_MASK MDS_OPCODE(0x3f,0xf,0x1)

#ifndef FALSE
#define FALSE 0
#define TRUE (!FALSE)
#endif

#define INSTRUCTION( memaddr ) ntohl(*(unsigned long *)(memaddr))

#define MAX_OPERANDS  8

struct ppc_ctx;

struct opcode {
  unsigned long	opcode;		/* The complete opcode as produced by
				   one of the XXX_OPCODE macros above */

  unsigned long	mask;		/* The mask to use on an instruction
				   before comparing with the opcode
				   field to see if it matches */

  enum OP_FIELD	fields[MAX_OPERANDS];
				/* An array defining the operands for
				   this opcode.  The values of the
				   array are the operand identifiers */

  int (*hfunc)(struct ppc_ctx *);
				/* Address of a function to handle the given
				   mnemonic */

  char *	name;		/* The symbolic name of this opcode */

  unsigned int	hint;		/* A bitwise-inclusive-OR of the
				   values shown below.  These are used
				   tell the disassembler how to print
				   some operands for this opcode */
};

/* values for opcode hints */
#define H_RELATIVE	0x1	/* The address operand is relative */
#define H_IMM_HIGH	0x2	/* [U|S]IMM field shifted high */
#define H_RA0_IS_0	0x4	/* If rA = 0 then treat as literal 0 */

struct ppc_ctx {
  struct opcode *	op;
  unsigned long		instr;
  unsigned int		flags;
  int			datalen;
  char			data[ 256 ];
  char			radix_fmt[ 8 ];
  unsigned char *	virtual;
};



/* Values for flags as passed to various ppc routines */
#define F_RADOCTAL	0x1	/* output radix = unsigned octal */
#define F_RADUDECIMAL	0x2	/* output radix = unsigned decimal */
#define F_RADSDECIMAL	0x4	/* output radix = signed decimal */
#define F_RADHEX	0x8	/* output radix = unsigned hex */
#define F_SIMPLE	0x10	/* use simplified mnemonics */
#define F_SYMBOL	0x20	/* use symbol lookups for addresses */
#define F_INSTR		0x40	/* output the raw instruction */
#define F_LOCALMEM	0x80	/* retrieve opcodes from local memory
				   rather than from the HMI */
#define F_LINENO	0x100	/* show line number info if available */
#define F_VALIDONLY	0x200	/* cache: valid entries only */

/* Values for assembler error codes */
#define E_ASM_BAD_OPCODE	1
#define E_ASM_NUM_OPERANDS	2
#define E_ASM_BAD_REGISTER	3
#define E_ASM_BAD_SPR		4
#define E_ASM_BAD_TBR		5

extern int disppc __P((unsigned char *,unsigned char *,int,
		       int (*)(const char *), unsigned long));
extern int print_source_line __P((char *,char *,int,
				  int (*pfunc)(const char *)));
extern int find_next_address __P((unsigned char *,int,struct pt_regs *));
extern int handle_bc __P((struct ppc_ctx *));
extern unsigned long asmppc __P((unsigned long,char*,int*));
extern char *asm_error_str __P((int));


extern struct operand operands[];
extern const unsigned int n_operands;
extern struct opcode opcodes[];
extern const unsigned int n_opcodes;

#endif /* _PPC_H */


