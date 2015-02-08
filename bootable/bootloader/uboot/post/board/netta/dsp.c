

#include <common.h>


#include <post.h>

#if CONFIG_POST & CONFIG_SYS_POST_DSP

extern int board_post_dsp(int flags);

int dsp_post_test (int flags)
{
	return board_post_dsp(flags);
}

#endif /* CONFIG_POST & CONFIG_SYS_POST_DSP */
