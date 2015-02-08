

#include <common.h>


#include <post.h>

#if CONFIG_POST & CONFIG_SYS_POST_CODEC

extern int board_post_codec(int flags);

int codec_post_test (int flags)
{
	return board_post_codec(flags);
}

#endif /* CONFIG_POST & CONFIG_SYS_POST_CODEC */
