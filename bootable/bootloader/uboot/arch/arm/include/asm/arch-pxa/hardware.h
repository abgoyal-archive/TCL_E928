

#ifndef __ASM_ARCH_HARDWARE_H
#define __ASM_ARCH_HARDWARE_H

#include <linux/config.h>
#include <asm/mach-types.h>


#define PCMCIA_IO_0_BASE	0xf6000000
#define PCMCIA_IO_1_BASE	0xf7000000


#define PCIO_BASE		0

#define UNCACHED_PHYS_0		0xff000000
#define UNCACHED_ADDR		UNCACHED_PHYS_0


/* FIXME: Only this does work for u-boot... find out why... [RS] */
#define UBOOT_REG_FIX 1

#ifndef UBOOT_REG_FIX
#ifndef __ASSEMBLY__

#define io_p2v(x)	( ((x) | 0xbe000000) ^ (~((x) >> 1) & 0x06000000) )
#define io_v2p( x )	( ((x) & 0x41ffffff) ^ ( ((x) & 0x06000000) << 1) )

#include <asm/types.h>
typedef struct { volatile u32 offset[4096]; } __regbase;
# define __REGP(x)	((__regbase *)((x)&~4095))->offset[((x)&4095)>>2]
# define __REG(x)	__REGP(io_p2v(x))
#endif

/* Let's kick gcc's ass again... */
# define __REG2(x,y)	\
	( __builtin_constant_p(y) ? (__REG((x) + (y))) \
				  : (*(volatile u32 *)((u32)&__REG(x) + (y))) )

# define __PREG(x)	(io_v2p((u32)&(x)))

#else

# define __REG(x)	io_p2v(x)
# define __PREG(x)	io_v2p(x)

# undef io_p2v
# undef __REG
# ifndef __ASSEMBLY__
#  define io_p2v(PhAdd)	   (PhAdd)
#  define __REG(x)	(*((volatile u32 *)io_p2v(x)))
#  define __REG2(x,y)	(*(volatile u32 *)((u32)&__REG(x) + (y)))
# else
#  define __REG(x) (x)
#  ifdef CONFIG_CPU_MONAHANS /* Hack to make this work with mona's pxa-regs.h */
#   define __REG_2(x) (x)
#   define __REG_3(x) (x)
#  endif
# endif
#endif /* UBOOT_REG_FIX */

#include "pxa-regs.h"

#ifndef __ASSEMBLY__

#define GPIO_FALLING_EDGE	1
#define GPIO_RISING_EDGE	2
#define GPIO_BOTH_EDGES		3
extern void set_GPIO_IRQ_edge( int gpio_nr, int edge_mask );

extern void set_GPIO_mode( int gpio_mode );

extern unsigned int get_lclk_frequency_10khz(void);

#endif



#ifdef CONFIG_ARCH_LUBBOCK
#include "lubbock.h"
#endif

#ifdef CONFIG_ARCH_PXA_IDP
#include "idp.h"
#endif

#ifdef CONFIG_ARCH_PXA_CERF
#include "cerf.h"
#endif

#ifdef CONFIG_ARCH_CSB226
#include "csb226.h"
#endif

#ifdef CONFIG_ARCH_INNOKOM
#include "innokom.h"
#endif

#ifdef CONFIG_ARCH_PLEB
#include "pleb.h"
#endif

#endif	/* _ASM_ARCH_HARDWARE_H */
