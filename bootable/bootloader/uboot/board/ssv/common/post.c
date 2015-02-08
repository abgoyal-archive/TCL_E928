

#include <common.h>

#if defined(CONFIG_POST) || defined(CONFIG_LOGBUFFER)

#if !defined(CONFIG_SYS_NIOS_POST_WORD_ADDR)
#error "*** CONFIG_SYS_NIOS_POST_WORD_ADDR not defined ***"
#endif

void post_word_store (ulong a)
{
	volatile void *save_addr = (void *)(CONFIG_SYS_NIOS_POST_WORD_ADDR);
	*(volatile ulong *) save_addr = a;
}

ulong post_word_load (void)
{
	volatile void *save_addr = (void *)(CONFIG_SYS_NIOS_POST_WORD_ADDR);
	return *(volatile ulong *) save_addr;
}

#endif	/* CONFIG_POST || CONFIG_LOGBUFFER*/
