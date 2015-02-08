

#ifndef __BIOSEMU_H
#define __BIOSEMU_H

#ifdef __KERNEL__
#include "x86emu.h"
#else
#include "x86emu.h"
#include "pmapi.h"
#include "pcilib.h"
#endif

/*---------------------- Macros and type definitions ----------------------*/

#pragma pack(1)

#ifndef __KERNEL__
typedef struct {
	PCIDeviceInfo *pciInfo;
	void *BIOSImage;
	ulong BIOSImageLen;
	uchar LowMem[1536];
} BE_VGAInfo;
#else
typedef struct {
	int function;
	int device;
	int bus;
	u32 VendorID;
	u32 DeviceID;
	pci_dev_t pcidev;
	void *BIOSImage;
	u32 BIOSImageLen;
	u8 LowMem[1536];
} BE_VGAInfo;

#endif				/* __KERNEL__ */

#define CRT_C   24		/* 24  CRT Controller Registers             */
#define ATT_C   21		/* 21  Attribute Controller Registers       */
#define GRA_C   9		/* 9   Graphics Controller Registers        */
#define SEQ_C   5		/* 5   Sequencer Registers                  */
#define PAL_C   768		/* 768 Palette Registers                    */


typedef struct {
	BE_VGAInfo vgaInfo;
	ulong biosmem_base;
	ulong biosmem_limit;
	ulong busmem_base;

	u32 timer0;
	int timer0Latched;
	u32 timer1;
	int timer1Latched;
	u32 timer2;
	int timer2Latched;

	int emulateVGA;
	u8 emu61;
	u8 emu70;
	int flipFlop3C0;
	u32 configAddress;
	u8 emu3C0;
	u8 emu3C1[ATT_C];
	u8 emu3C2;
	u8 emu3C4;
	u8 emu3C5[SEQ_C];
	u8 emu3C6;
	uint emu3C7;
	uint emu3C8;
	u8 emu3C9[PAL_C];
	u8 emu3CE;
	u8 emu3CF[GRA_C];
	u8 emu3D4;
	u8 emu3D5[CRT_C];
	u8 emu3DA;

} BE_sysEnv;

#ifdef __KERNEL__


typedef struct {
	u32 eax;
	u32 ebx;
	u32 ecx;
	u32 edx;
	u32 esi;
	u32 edi;
	u32 cflag;
} RMDWORDREGS;

#ifdef __BIG_ENDIAN__
typedef struct {
	u16 ax_hi, ax;
	u16 bx_hi, bx;
	u16 cx_hi, cx;
	u16 dx_hi, dx;
	u16 si_hi, si;
	u16 di_hi, di;
	u16 cflag_hi, cflag;
} RMWORDREGS;
#else
typedef struct {
	u16 ax, ax_hi;
	u16 bx, bx_hi;
	u16 cx, cx_hi;
	u16 dx, dx_hi;
	u16 si, si_hi;
	u16 di, di_hi;
	u16 cflag, cflag_hi;
} RMWORDREGS;
#endif

#ifdef __BIG_ENDIAN__
typedef struct {
	u16 ax_hi;
	u8 ah, al;
	u16 bx_hi;
	u8 bh, bl;
	u16 cx_hi;
	u8 ch, cl;
	u16 dx_hi;
	u8 dh, dl;
} RMBYTEREGS;
#else
typedef struct {
	u8 al;
	u8 ah;
	u16 ax_hi;
	u8 bl;
	u8 bh;
	u16 bx_hi;
	u8 cl;
	u8 ch;
	u16 cx_hi;
	u8 dl;
	u8 dh;
	u16 dx_hi;
} RMBYTEREGS;
#endif

typedef union {
	RMDWORDREGS e;
	RMWORDREGS x;
	RMBYTEREGS h;
} RMREGS;

typedef struct {
	u16 es;
	u16 cs;
	u16 ss;
	u16 ds;
	u16 fs;
	u16 gs;
} RMSREGS;

#endif				/* __KERNEL__ */

#ifndef __KERNEL__

typedef struct {
	ulong dwSize;
	 ibool(PMAPIP BE_init) (u32 debugFlags, int memSize, BE_VGAInfo * info);
	void (PMAPIP BE_setVGA) (BE_VGAInfo * info);
	void (PMAPIP BE_getVGA) (BE_VGAInfo * info);
	void *(PMAPIP BE_mapRealPointer) (uint r_seg, uint r_off);
	void *(PMAPIP BE_getVESABuf) (uint * len, uint * rseg, uint * roff);
	void (PMAPIP BE_callRealMode) (uint seg, uint off, RMREGS * regs,
				       RMSREGS * sregs);
	int (PMAPIP BE_int86) (int intno, RMREGS * in, RMREGS * out);
	int (PMAPIP BE_int86x) (int intno, RMREGS * in, RMREGS * out,
				RMSREGS * sregs);
	void *reserved1;
	void (PMAPIP BE_exit) (void);
} BE_exports;

typedef BE_exports *(PMAPIP BE_initLibrary_t) (PM_imports * PMImp);
#endif

#pragma pack()

/*---------------------------- Global variables ---------------------------*/

#ifdef  __cplusplus
extern "C" {			/* Use "C" linkage when in C++ mode */
#endif

/* {secret} Global BIOS emulator system environment */
	extern BE_sysEnv _BE_env;

/*-------------------------- Function Prototypes --------------------------*/

/* BIOS emulator library entry points */
	int X86API BE_init(u32 debugFlags, int memSize, BE_VGAInfo * info,
			   int shared);
	void X86API BE_setVGA(BE_VGAInfo * info);
	void X86API BE_getVGA(BE_VGAInfo * info);
	void X86API BE_setDebugFlags(u32 debugFlags);
	void *X86API BE_mapRealPointer(uint r_seg, uint r_off);
	void *X86API BE_getVESABuf(uint * len, uint * rseg, uint * roff);
	void X86API BE_callRealMode(uint seg, uint off, RMREGS * regs,
				    RMSREGS * sregs);
	int X86API BE_int86(int intno, RMREGS * in, RMREGS * out);
	int X86API BE_int86x(int intno, RMREGS * in, RMREGS * out,
			     RMSREGS * sregs);
	void X86API BE_exit(void);

#ifdef  __cplusplus
}				/* End of "C" linkage for C++       */
#endif
#endif				/* __BIOSEMU_H */
