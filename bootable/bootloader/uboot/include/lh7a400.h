


#ifndef __LH7A400_H__
#define __LH7A400_H__

#include "lh7a40x.h"

/* Interrupt Controller (userguide 8.2.1) */
typedef struct {
	volatile u32  intsr;
	volatile u32  intrsr;
	volatile u32  intens;
	volatile u32  intenc;
	volatile u32  rsvd1;
	volatile u32  rsvd2;
	volatile u32  rsvd3;
} /*__attribute__((__packed__))*/ lh7a400_interrupt_t;
#define LH7A400_INTERRUPT_BASE    (0x80000500)
#define LH7A400_INTERRUPT_PTR     ((lh7a400_interrupt_t*) LH7A400_INTERRUPT_BASE)

/* (DMA) Direct Memory Access Controller (userguide 9.2.1) */
typedef struct {
	lh7a40x_dmachan_t  chan[15];
	volatile u32       glblint;
	volatile u32       rsvd1;
	volatile u32       rsvd2;
	volatile u32       rsvd3;
} /*__attribute__((__packed__))*/ lh7a400_dma_t;

#define LH7A400_DMA_BASE      (0x80002800)
#define DMA_USBTX_OFFSET      (0x000)
#define DMA_USBRX_OFFSET      (0x040)
#define DMA_MMCTX_OFFSET      (0x080)
#define DMA_MMCRX_OFFSET      (0x0C0)
#define DMA_AC97_BASE         (0x80002A00)

#define LH7A400_DMA_PTR    ((lh7a400_dma_t*) LH7A400_DMA_BASE)
#define LH7A400_DMA_USBTX \
	((lh7a400_dmachan_t*) (LH7A400_DMA_BASE + DMA_USBTX_OFFSET))
#define LH7A400_DMA_USBRX \
	((lh7a400_dmachan_t*) (LH7A400_DMA_BASE + DMA_USBRX_OFFSET))
#define LH7A400_DMA_MMCTX \
	((lh7a400_dmachan_t*) (LH7A400_DMA_BASE + DMA_MMCTX_OFFSET))
#define LH7A400_DMA_MMCRX \
	((lh7a400_dmachan_t*) (LH7A400_DMA_BASE + DMA_MMCRX_OFFSET))
#define LH7A400_AC97RX(n) \
	((lh7a400_dmachan_t*) (LH7A400_AC97_BASE + \
	((2*n) * sizeof(lh7a400_dmachan_t))))
#define LH7A400_AC97TX(n) \
	((lh7a400_dmachan_t*) (LH7A400_AC97_BASE + \
	(((2*n)+1) * sizeof(lh7a400_dmachan_t))))

#endif  /* __LH7A400_H__ */
