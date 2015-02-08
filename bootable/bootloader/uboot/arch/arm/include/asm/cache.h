

#ifndef _ASM_CACHE_H
#define _ASM_CACHE_H

#include <asm/system.h>

static inline void invalidate_l2_cache(void)
{
	unsigned int val=0;

	asm volatile("mcr p15, 1, %0, c15, c11, 0 @ invl l2 cache"
		: : "r" (val) : "cc");
	isb();
}

void l2_cache_enable(void);
void l2_cache_disable(void);

#endif /* _ASM_CACHE_H */
