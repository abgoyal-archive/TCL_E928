

#include <common.h>

#include <post.h>

#if CONFIG_POST & CONFIG_SYS_POST_FPU

GNU_FPOST_ATTR

int fpu_post_test_math4 (void)
{
	volatile float reale = 1.0f;
	volatile float oneplus;
	int i;

	if (sizeof (float) != 4)
		return 0;

	for (i = 0; ; i++)
	{
		oneplus = 1.0f + reale;
		if (oneplus == 1.0f)
			break;
		reale = reale / 2.0f;
	}
	/* Assumes ieee754 accurate arithmetic above.  */
	if (i != 24) {
		post_log ("Error in FPU math4 test\n");
		return -1;
	}
	return 0;
}

#endif /* CONFIG_POST & CONFIG_SYS_POST_FPU */
