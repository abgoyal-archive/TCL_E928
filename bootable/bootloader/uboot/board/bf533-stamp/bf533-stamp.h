

#ifndef __STAMP_H__
#define __STAMP_H__

extern void init_Flags(void);

extern volatile unsigned long *ambctl0;
extern volatile unsigned long *ambctl1;
extern volatile unsigned long *amgctl;

/* Definitions used in  Compact Flash Boot support */
#define FIO_EDGE_CF_BITS	0x0000
#define FIO_POLAR_CF_BITS	0x0000
#define	FIO_EDGE_BITS		0x1E0
#define	FIO_POLAR_BITS		0x160

/* Compact flash status bits in status register */
#define CF_STAT_BITS		0x00000060

#define CF_PF0			0x0001
#define CF_PF1			0x0002
#define CF_PF1_PF0		0x0003

#endif