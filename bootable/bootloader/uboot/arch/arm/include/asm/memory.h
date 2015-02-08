
#ifndef __ASM_ARM_MEMORY_H
#define __ASM_ARM_MEMORY_H

#if 0	/* XXX###XXX */

#include <linux/config.h>
#include <asm/arch/memory.h>

#define PHYS_PFN_OFFSET	(PHYS_OFFSET >> PAGE_SHIFT)

static inline unsigned long virt_to_phys(void *x)
{
	return __virt_to_phys((unsigned long)(x));
}

static inline void *phys_to_virt(unsigned long x)
{
	return (void *)(__phys_to_virt((unsigned long)(x)));
}

#define __pa(x)			__virt_to_phys((unsigned long)(x))
#define __va(x)			((void *)__phys_to_virt((unsigned long)(x)))

#define virt_to_bus(x)		(__virt_to_bus((unsigned long)(x)))
#define bus_to_virt(x)		((void *)(__bus_to_virt((unsigned long)(x))))

#ifndef CONFIG_DISCONTIGMEM

#define page_to_pfn(page)	(((page) - mem_map) + PHYS_PFN_OFFSET)
#define pfn_to_page(pfn)	((mem_map + (pfn)) - PHYS_PFN_OFFSET)
#define pfn_valid(pfn)		((pfn) >= PHYS_PFN_OFFSET && (pfn) < (PHYS_PFN_OFFSET + max_mapnr))

#define virt_to_page(kaddr)	(pfn_to_page(__pa(kaddr) >> PAGE_SHIFT))
#define virt_addr_valid(kaddr)	((kaddr) >= PAGE_OFFSET && (kaddr) < (unsigned long)high_memory)

#define PHYS_TO_NID(addr)	(0)

#define VALID_PAGE(page)	((page - mem_map) < max_mapnr)

#else

#define page_to_pfn(page)					\
	(((page) - page_zone(page)->zone_mem_map)		\
	  + (page_zone(page)->zone_start_paddr >> PAGE_SHIFT))

#define pfn_to_page(pfn)					\
	(PFN_TO_MAPBASE(pfn) + LOCAL_MAP_NR((pfn) << PAGE_SHIFT))

#define pfn_valid(pfn)						\
  ({								\
	unsigned int node = PFN_TO_NID(pfn);			\
	struct pglist_data *nd = NODE_DATA(node);		\
	((node < NR_NODES) &&					\
	 ((pfn - (nd->node_start_paddr >> PAGE_SHIFT)) < nd->node_size));\
   })

#define virt_to_page(kaddr)					\
	(ADDR_TO_MAPBASE(kaddr) + LOCAL_MAP_NR(kaddr))

#define virt_addr_valid(kaddr)	(KVADDR_TO_NID(kaddr) < NR_NODES)

#define PHYS_TO_NID(addr)	PFN_TO_NID((addr) >> PAGE_SHIFT)

#define VALID_PAGE(page) \
({ unsigned int node = KVADDR_TO_NID(page); \
   ((node < NR_NODES) && \
     ((unsigned)((page) - NODE_MEM_MAP(node)) < NODE_DATA(node)->node_size)); \
})

#endif

#define page_to_bus(page)	(virt_to_bus(page_address(page)))

#endif	/* XXX###XXX */

#endif	/* __ASM_ARM_MEMORY_H */
