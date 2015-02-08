

#include <common.h>
#include <commproc.h>
#include <asm/io.h>

#if defined(CONFIG_POST) || defined(CONFIG_LOGBUFFER)

#if defined(CONFIG_SYS_POST_WORD_ADDR)
# define _POST_ADDR	((CONFIG_SYS_OCM_DATA_ADDR) + (CONFIG_SYS_POST_WORD_ADDR))
#elif defined(CONFIG_SYS_POST_ALT_WORD_ADDR)
# define _POST_ADDR	(CONFIG_SYS_POST_ALT_WORD_ADDR)
#endif

void post_word_store (ulong a)
{
	volatile void *save_addr = (volatile void *)(_POST_ADDR);

	out_be32(save_addr, a);
}

ulong post_word_load (void)
{
	volatile void *save_addr = (volatile void *)(_POST_ADDR);

	return in_be32(save_addr);
}

#endif	/* CONFIG_POST || CONFIG_LOGBUFFER*/
