

#include <common.h>

#include <post.h>

#if CONFIG_POST & CONFIG_SYS_POST_FPU

GNU_FPOST_ATTR

int fpu_post_test_math1 (void)
{
	volatile double a, *p;
	double c, d;
	volatile double b;

	d = 1.0;
	p = &b;

	do
	{
		c = d;
		d = c * 0.5;
		b = 1 + d;
	} while (b != 1.0);

	a = 1.0 + c;

	if (a == 1.0) {
		post_log ("Error in FPU math1 test\n");
		return -1;
	}

	return 0;
}

#endif /* CONFIG_POST & CONFIG_SYS_POST_FPU */
