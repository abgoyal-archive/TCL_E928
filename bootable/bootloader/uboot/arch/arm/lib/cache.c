

/* for now: just dummy functions to satisfy the linker */

#include <common.h>

void  flush_cache (unsigned long dummy1, unsigned long dummy2)
{
#ifdef CONFIG_OMAP2420
	void arm1136_cache_flush(void);

	arm1136_cache_flush();
#endif
	return;
}
