
#ifndef __ASM_AVR32_CACHEFLUSH_H
#define __ASM_AVR32_CACHEFLUSH_H

static inline void dcache_invalidate_line(volatile void *vaddr)
{
	asm volatile("cache %0[0], 0x0b" : : "r"(vaddr) : "memory");
}

static inline void dcache_clean_line(volatile void *vaddr)
{
	asm volatile("cache %0[0], 0x0c" : : "r"(vaddr) : "memory");
}

static inline void dcache_flush_line(volatile void *vaddr)
{
	asm volatile("cache %0[0], 0x0d" : : "r"(vaddr) : "memory");
}

static inline void icache_invalidate_line(volatile void *vaddr)
{
	asm volatile("cache %0[0], 0x01" : : "r"(vaddr) : "memory");
}

void dcache_invalidate_range(volatile void *start, size_t len);
void dcache_clean_range(volatile void *start, size_t len);
void dcache_flush_range(volatile void *start, size_t len);
void icache_invalidate_range(volatile void *start, size_t len);

static inline void dcache_flush_unlocked(void)
{
	asm volatile("cache %0[5], 0x08" : : "r"(0) : "memory");
}

#define sync_write_buffer() asm volatile("sync 0" : : : "memory")

#endif /* __ASM_AVR32_CACHEFLUSH_H */
