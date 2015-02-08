

#ifndef __NIOS2_H__
#define __NIOS2_H__

#define CTL_STATUS	0		/* Processor status reg		*/
#define CTL_ESTATUS	1		/* Exception status reg		*/
#define CTL_BSTATUS	2		/* Break status reg		*/
#define CTL_IENABLE	3		/* Interrut enable reg		*/
#define CTL_IPENDING	4		/* Interrut pending reg		*/

#define _str_(x) #x

#define rdctl(reg)\
	({unsigned int val;\
	asm volatile( "rdctl %0, ctl" _str_(reg)\
		: "=r" (val) ); val;})

#define wrctl(reg,val)\
	asm volatile( "wrctl ctl" _str_(reg) ",%0"\
		: : "r" (val))

#define STATUS_IE	(1<<0)		/* Interrupt enable		*/
#define STATUS_U	(1<<1)		/* User-mode			*/

#define CACHE_BYPASS(a) ((a) | 0x80000000)
#define CACHE_NO_BYPASS(a) ((a) & ~0x80000000)

#endif /* __NIOS2_H__ */
