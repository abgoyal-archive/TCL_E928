


#include <common.h>
#include <command.h>

int cleanup_before_linux (void)
{
	/*
	 * this function is called just before we call linux
	 * it prepares the processor for linux
	 *
	 * we turn off caches etc ...
	 */

	disable_interrupts ();

	/* Since the CM has unknown processor we do not support
	 * cache operations
	 */

	return (0);
}
