

#include <common.h>
#include <commproc.h>

DECLARE_GLOBAL_DATA_PTR;

#ifdef CONFIG_SYS_ALLOC_DPRAM

int dpram_init (void)
{
	/* Reclaim the DP memory for our use. */
	gd->dp_alloc_base = CPM_DATAONLY_BASE;
	gd->dp_alloc_top  = CPM_DATAONLY_BASE + CPM_DATAONLY_SIZE;

	return (0);
}

uint dpram_alloc (uint size)
{
	uint addr = gd->dp_alloc_base;

	if ((gd->dp_alloc_base + size) >= gd->dp_alloc_top)
		return (CPM_DP_NOSPACE);

	gd->dp_alloc_base += size;

	return addr;
}

uint dpram_base (void)
{
	return gd->dp_alloc_base;
}

uint dpram_alloc_align (uint size, uint align)
{
	uint addr, mask = align - 1;

	addr = (gd->dp_alloc_base + mask) & ~mask;

	if ((addr + size) >= gd->dp_alloc_top)
		return (CPM_DP_NOSPACE);

	gd->dp_alloc_base = addr + size;

	return addr;
}

uint dpram_base_align (uint align)
{
	uint mask = align - 1;

	return (gd->dp_alloc_base + mask) & ~mask;
}
#endif	/* CONFIG_SYS_ALLOC_DPRAM */

#if defined(CONFIG_POST) || defined(CONFIG_LOGBUFFER)

void post_word_store (ulong a)
{
	volatile void *save_addr =
		((immap_t *) CONFIG_SYS_IMMR)->im_cpm.cp_dpmem + CPM_POST_WORD_ADDR;

	*(volatile ulong *) save_addr = a;
}

ulong post_word_load (void)
{
	volatile void *save_addr =
		((immap_t *) CONFIG_SYS_IMMR)->im_cpm.cp_dpmem + CPM_POST_WORD_ADDR;

	return *(volatile ulong *) save_addr;
}

#endif	/* CONFIG_POST || CONFIG_LOGBUFFER*/
