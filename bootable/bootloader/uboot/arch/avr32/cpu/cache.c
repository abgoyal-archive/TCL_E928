

#include <common.h>

#include <asm/arch/cacheflush.h>

void dcache_clean_range(volatile void *start, size_t size)
{
	unsigned long v, begin, end, linesz;

	linesz = CONFIG_SYS_DCACHE_LINESZ;

	/* You asked for it, you got it */
	begin = (unsigned long)start & ~(linesz - 1);
	end = ((unsigned long)start + size + linesz - 1) & ~(linesz - 1);

	for (v = begin; v < end; v += linesz)
		dcache_clean_line((void *)v);

	sync_write_buffer();
}

void dcache_invalidate_range(volatile void *start, size_t size)
{
	unsigned long v, begin, end, linesz;

	linesz = CONFIG_SYS_DCACHE_LINESZ;

	/* You asked for it, you got it */
	begin = (unsigned long)start & ~(linesz - 1);
	end = ((unsigned long)start + size + linesz - 1) & ~(linesz - 1);

	for (v = begin; v < end; v += linesz)
		dcache_invalidate_line((void *)v);
}

void dcache_flush_range(volatile void *start, size_t size)
{
	unsigned long v, begin, end, linesz;

	linesz = CONFIG_SYS_DCACHE_LINESZ;

	/* You asked for it, you got it */
	begin = (unsigned long)start & ~(linesz - 1);
	end = ((unsigned long)start + size + linesz - 1) & ~(linesz - 1);

	for (v = begin; v < end; v += linesz)
		dcache_flush_line((void *)v);

	sync_write_buffer();
}

void icache_invalidate_range(volatile void *start, size_t size)
{
	unsigned long v, begin, end, linesz;

	linesz = CONFIG_SYS_ICACHE_LINESZ;

	/* You asked for it, you got it */
	begin = (unsigned long)start & ~(linesz - 1);
	end = ((unsigned long)start + size + linesz - 1) & ~(linesz - 1);

	for (v = begin; v < end; v += linesz)
		icache_invalidate_line((void *)v);
}

void  flush_cache (unsigned long start_addr, unsigned long size)
{
	dcache_clean_range((void *)start_addr, size);
	icache_invalidate_range((void *)start_addr, size);
}
