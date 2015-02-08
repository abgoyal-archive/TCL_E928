

#include <config.h>
#include <version.h>

/* Set up the platform, once the cpu has been initialized */
.globl lowlevel_init
lowlevel_init:

	/* All done by Versatile's boot monitor! */
	mov pc, lr
