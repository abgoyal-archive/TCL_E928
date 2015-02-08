

#include <common.h>
#include <asm/processor.h>

void flush_cache(ulong start_addr, ulong size)
{
	/* Flush All Cache */
	sparc_dcache_flush_all();
	sparc_icache_flush_all();
}
