

#include <common.h>


void flush_cache (ulong addr, ulong size)
{
	/* Nios cache is write-thru -- nothing to do here.
	 */
	return;
}
