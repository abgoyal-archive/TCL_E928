
 /****************************************************************************
 * Global routines used for VCMA9
 *****************************************************************************/

#include <asm/arch/s3c24x0_cpu.h>

extern int  mem_test(unsigned long start, unsigned long ramsize,int mode);

void print_vcma9_info(void);

#if defined(CONFIG_CMD_NAND)
typedef enum {
	NFCE_LOW,
	NFCE_HIGH
} NFCE_STATE;

static inline void NF_Conf(u16 conf)
{
	struct s3c2410_nand * const nand = s3c2410_get_base_nand();

	nand->NFCONF = conf;
}

static inline void NF_Cmd(u8 cmd)
{
	struct s3c2410_nand * const nand = s3c2410_get_base_nand();

	nand->NFCMD = cmd;
}

static inline void NF_CmdW(u8 cmd)
{
	NF_Cmd(cmd);
	udelay(1);
}

static inline void NF_Addr(u8 addr)
{
	struct s3c2410_nand * const nand = s3c2410_get_base_nand();

	nand->NFADDR = addr;
}

static inline void NF_SetCE(NFCE_STATE s)
{
	struct s3c2410_nand * const nand = s3c2410_get_base_nand();

	switch (s) {
		case NFCE_LOW:
			nand->NFCONF &= ~(1<<11);
			break;

		case NFCE_HIGH:
			nand->NFCONF |= (1<<11);
			break;
	}
}

static inline void NF_WaitRB(void)
{
	struct s3c2410_nand * const nand = s3c2410_get_base_nand();

	while (!(nand->NFSTAT & (1<<0)));
}

static inline void NF_Write(u8 data)
{
	struct s3c2410_nand * const nand = s3c2410_get_base_nand();

	nand->NFDATA = data;
}

static inline u8 NF_Read(void)
{
	struct s3c2410_nand * const nand = s3c2410_get_base_nand();

	return(nand->NFDATA);
}

static inline void NF_Init_ECC(void)
{
	struct s3c2410_nand * const nand = s3c2410_get_base_nand();

	nand->NFCONF |= (1<<12);
}

static inline u32 NF_Read_ECC(void)
{
	struct s3c2410_nand * const nand = s3c2410_get_base_nand();

	return(nand->NFECC);
}

#endif

/* VCMA9 PLD regsiters */
typedef struct {
	u8	ID;
	u8	NIC;
	u8	CAN;
	u8	MISC;
	u8	GPCD;
	u8	BOARD;
	u8	SDRAM;
} /*__attribute__((__packed__))*/ VCMA9_PLD;

#define VCMA9_PLD_BASE	0x2C000100
static inline VCMA9_PLD *VCMA9_get_base_PLD(void)
{
	return (VCMA9_PLD * const)VCMA9_PLD_BASE;
}
