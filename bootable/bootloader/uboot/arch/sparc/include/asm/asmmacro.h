

#ifndef __SPARC_ASMMACRO_H__
#define __SPARC_ASMMACRO_H__

#include <config.h>

#define SAVE_ALL_HEAD \
	sethi	%hi(trap_setup+(CONFIG_SYS_RELOC_MONITOR_BASE-TEXT_BASE)), %l4; \
	jmpl	%l4 + %lo(trap_setup+(CONFIG_SYS_RELOC_MONITOR_BASE-TEXT_BASE)), %l6;
#define SAVE_ALL \
	SAVE_ALL_HEAD \
	nop;

/* All traps low-level code here must end with this macro. */
#define RESTORE_ALL b ret_trap_entry; clr %l6;

#endif
