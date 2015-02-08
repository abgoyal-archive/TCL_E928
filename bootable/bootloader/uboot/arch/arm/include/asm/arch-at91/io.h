

#ifndef __ASM_ARCH_IO_H
#define __ASM_ARCH_IO_H

#include <asm/io.h>

#ifdef CONFIG_AT91_LEGACY

static inline unsigned int at91_sys_read(unsigned int reg_offset)
{
	void *addr = (void *)AT91_BASE_SYS;

	return __raw_readl(addr + reg_offset);
}

static inline void at91_sys_write(unsigned int reg_offset, unsigned long value)
{
	void *addr = (void *)AT91_BASE_SYS;

	__raw_writel(value, addr + reg_offset);
}
#endif

#endif
