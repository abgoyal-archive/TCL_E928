

#include <common.h>


#include <post.h>

#if CONFIG_POST & CONFIG_SYS_POST_WATCHDOG

#include <watchdog.h>

int watchdog_post_test (int flags)
{
	if (flags & POST_REBOOT) {
		/* Test passed */
		return 0;
	}
	else {
		/* 10-second delay */
		int ints = disable_interrupts ();
		ulong base = post_time_ms (0);

		while (post_time_ms (base) < 10000)
			;
		if (ints)
			enable_interrupts ();

		/*
		 * If we have reached this point, the watchdog timer
		 * does not work
		 */
		return -1;
	}
}

#endif /* CONFIG_POST & CONFIG_SYS_POST_WATCHDOG */
