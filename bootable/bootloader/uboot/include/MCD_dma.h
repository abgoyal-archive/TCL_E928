

#ifndef _MCD_API_H
#define _MCD_API_H

/* Turn Execution Unit tasks ON (#define) or OFF (#undef) */
#undef MCD_INCLUDE_EU

/* Number of DMA channels */
#define NCHANNELS	16

/* Total number of variants */
#ifdef MCD_INCLUDE_EU
#define NUMOFVARIANTS	6
#else
#define NUMOFVARIANTS	4
#endif

/* Define sizes of the various tables */
#define TASK_TABLE_SIZE		(NCHANNELS*32)
#define VAR_TAB_SIZE		(128)
#define CONTEXT_SAVE_SIZE	(128)
#define FUNCDESC_TAB_SIZE	(256)

#ifdef MCD_INCLUDE_EU
#define FUNCDESC_TAB_NUM	16
#else
#define FUNCDESC_TAB_NUM	1
#endif

#ifndef DEFINESONLY

/* Portability typedefs */
#if 1
#include "common.h"
#else
#ifndef s32
typedef int s32;
#endif
#ifndef u32
typedef unsigned int u32;
#endif
#ifndef s16
typedef short s16;
#endif
#ifndef u16
typedef unsigned short u16;
#endif
#ifndef s8
typedef char s8;
#endif
#ifndef u8
typedef unsigned char u8;
#endif
#endif

struct dmaRegs_s {
	u32 taskbar;		/* task table base address */
	u32 currPtr;
	u32 endPtr;
	u32 varTablePtr;
	u16 dma_rsvd0;
	u16 ptdControl;		/* ptd control */
	u32 intPending;		/* interrupt pending */
	u32 intMask;		/* interrupt mask */
	u16 taskControl[16];	/* task control */
	u8 priority[32];	/* priority */
	u32 initiatorMux;	/* initiator mux control */
	u32 taskSize0;		/* task size control 0. */
	u32 taskSize1;		/* task size control 1. */
	u32 dma_rsvd1;		/* reserved */
	u32 dma_rsvd2;		/* reserved */
	u32 debugComp1;		/* debug comparator 1 */
	u32 debugComp2;		/* debug comparator 2 */
	u32 debugControl;	/* debug control */
	u32 debugStatus;	/* debug status */
	u32 ptdDebug;		/* priority task decode debug */
	u32 dma_rsvd3[31];	/* reserved */
};
typedef volatile struct dmaRegs_s dmaRegs;

#endif

/* PTD contrl reg bits */
#define PTD_CTL_TSK_PRI		0x8000
#define PTD_CTL_COMM_PREFETCH	0x0001

/* Task Control reg bits and field masks */
#define TASK_CTL_EN		0x8000
#define TASK_CTL_VALID		0x4000
#define TASK_CTL_ALWAYS		0x2000
#define TASK_CTL_INIT_MASK	0x1f00
#define TASK_CTL_ASTRT		0x0080
#define TASK_CTL_HIPRITSKEN	0x0040
#define TASK_CTL_HLDINITNUM	0x0020
#define TASK_CTL_ASTSKNUM_MASK	0x000f

/* Priority reg bits and field masks */
#define PRIORITY_HLD		0x80
#define PRIORITY_PRI_MASK	0x07

/* Debug Control reg bits and field masks */
#define DBG_CTL_BLOCK_TASKS_MASK	0xffff0000
#define DBG_CTL_AUTO_ARM		0x00008000
#define DBG_CTL_BREAK			0x00004000
#define DBG_CTL_COMP1_TYP_MASK		0x00003800
#define DBG_CTL_COMP2_TYP_MASK		0x00000070
#define DBG_CTL_EXT_BREAK		0x00000004
#define DBG_CTL_INT_BREAK		0x00000002

#define PTD_DBG_REQ		0x00	/* shows the state of 31 initiators */
#define PTD_DBG_TSK_VLD_INIT	0x01	/* shows which 16 tasks are valid and
					   have initiators asserted */

/* General return values */
#define MCD_OK			0
#define MCD_ERROR		-1
#define MCD_TABLE_UNALIGNED	-2
#define MCD_CHANNEL_INVALID	-3

/* MCD_initDma input flags */
#define MCD_RELOC_TASKS		0x00000001
#define MCD_NO_RELOC_TASKS	0x00000000
#define MCD_COMM_PREFETCH_EN	0x00000002	/* MCF547x/548x ONLY */

#define MCD_NO_DMA		1
#define MCD_IDLE		2
#define MCD_RUNNING		3
#define MCD_PAUSED		4
#define MCD_HALTED		5
#define MCD_DONE		6

/* MCD_startDma parameter defines */

/* Constants for the funcDesc parameter */
#define MCD_NO_BYTE_SWAP	0x00045670
#define MCD_BYTE_REVERSE	0x00076540
#define MCD_U16_REVERSE		0x00067450
#define MCD_U16_BYTE_REVERSE	0x00054760
#define MCD_NO_BIT_REV		0x00000000
#define MCD_BIT_REV		0x00088880
/* CRCing: */
#define MCD_CRC16		0xc0100000
#define MCD_CRCCCITT		0xc0200000
#define MCD_CRC32		0xc0300000
#define MCD_CSUMINET		0xc0400000
#define MCD_NO_CSUM		0xa0000000

#define MCD_FUNC_NOEU1		(MCD_NO_BYTE_SWAP | MCD_NO_BIT_REV | \
				 MCD_NO_CSUM)
#define MCD_FUNC_NOEU2		(MCD_NO_BYTE_SWAP | MCD_NO_CSUM)

/* Constants for the flags parameter */
#define MCD_TT_FLAGS_RL		0x00000001	/* Read line */
#define MCD_TT_FLAGS_CW		0x00000002	/* Combine Writes */
#define MCD_TT_FLAGS_SP		0x00000004	/* MCF547x/548x ONLY  */
#define MCD_TT_FLAGS_MASK	0x000000ff
#define MCD_TT_FLAGS_DEF	(MCD_TT_FLAGS_RL | MCD_TT_FLAGS_CW)

#define MCD_SINGLE_DMA		0x00000100	/* Unchained DMA */
#define MCD_CHAIN_DMA		/* TBD */
#define MCD_EU_DMA		/* TBD */
#define MCD_FECTX_DMA		0x00001000	/* FEC TX ring DMA */
#define MCD_FECRX_DMA		0x00002000	/* FEC RX ring DMA */

/* these flags are valid for MCD_startDma and the chained buffer descriptors */
#define MCD_BUF_READY		0x80000000
#define MCD_WRAP		0x20000000
#define MCD_INTERRUPT		0x10000000
#define MCD_END_FRAME		0x08000000
#define MCD_CRC_RESTART		0x40000000

/* Defines for the FEC buffer descriptor control/status word*/
#define MCD_FEC_BUF_READY	0x8000
#define MCD_FEC_WRAP		0x2000
#define MCD_FEC_INTERRUPT	0x1000
#define MCD_FEC_END_FRAME	0x0800

/* Defines for general intuitiveness */

#define MCD_TRUE		1
#define MCD_FALSE		0

/* Three different cases for destination and source. */
#define MINUS1			-1
#define ZERO			0
#define PLUS1			1

#ifndef DEFINESONLY

/* Task Table Entry struct*/
typedef struct {
	u32 TDTstart;		/* task descriptor table start */
	u32 TDTend;		/* task descriptor table end */
	u32 varTab;		/* variable table start */
	u32 FDTandFlags;	/* function descriptor table start & flags */
	volatile u32 descAddrAndStatus;
	volatile u32 modifiedVarTab;
	u32 contextSaveSpace;	/* context save space start */
	u32 literalBases;
} TaskTableEntry;

typedef volatile struct MCD_bufDesc_struct MCD_bufDesc;
struct MCD_bufDesc_struct {
	u32 flags;
	u32 csumResult;
	s8 *srcAddr;
	s8 *destAddr;
	s8 *lastDestAddr;
	u32 dmaSize;
	MCD_bufDesc *next;
	u32 info;
};


typedef volatile struct MCD_XferProg_struct {
	s8 *lastSrcAddr;
	s8 *lastDestAddr;
	u32 dmaSize;
	MCD_bufDesc *currBufDesc;
} MCD_XferProg;

/* FEC buffer descriptor */
typedef volatile struct MCD_bufDescFec_struct {
	u16 statCtrl;
	u16 length;
	u32 dataPointer;
} MCD_bufDescFec;

/*************************************************************************/
/* API function Prototypes  - see MCD_dmaApi.c for further notes */

int MCD_startDma(int channel, s8 * srcAddr, s16 srcIncr, s8 * destAddr,
		 s16 destIncr, u32 dmaSize, u32 xferSize, u32 initiator,
		 int priority, u32 flags, u32 funcDesc);

int MCD_initDma(dmaRegs * sDmaBarAddr, void *taskTableDest, u32 flags);

/* MCD_dmaStatus() returns the status of the DMA on the requested channel. */
int MCD_dmaStatus(int channel);

/* MCD_XferProgrQuery() returns progress of DMA on requested channel */
int MCD_XferProgrQuery(int channel, MCD_XferProg * progRep);

int MCD_killDma(int channel);

int MCD_continDma(int channel);

int MCD_pauseDma(int channel);

int MCD_resumeDma(int channel);

/* MCD_csumQuery provides the checksum/CRC after performing a non-chained DMA */
int MCD_csumQuery(int channel, u32 * csum);

int MCD_getCodeSize(void);

int MCD_getVersion(char **longVersion);

/* macro for setting a location in the variable table */
#define MCD_SET_VAR(taskTab,idx,value) ((u32 *)(taskTab)->varTab)[idx] = value

#endif				/* DEFINESONLY */

#endif				/* _MCD_API_H */
