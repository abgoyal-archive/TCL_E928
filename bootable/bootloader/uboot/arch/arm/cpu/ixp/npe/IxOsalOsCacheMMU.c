

#include "IxOsal.h"

#include <malloc.h>

void *
ixOsalCacheDmaMalloc (UINT32 n)
{
	return malloc(n);
}

void
ixOsalCacheDmaFree (void *ptr)
{
	free(ptr);
}
