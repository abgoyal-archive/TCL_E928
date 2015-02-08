
#ifndef __ADDR_MAP_H
#define __ADDR_MAP_H


#include <asm/types.h>

extern phys_addr_t addrmap_virt_to_phys(void *vaddr);
extern unsigned long addrmap_phys_to_virt(phys_addr_t paddr);
extern void addrmap_set_entry(unsigned long vaddr, phys_addr_t paddr,
				phys_size_t size, int idx);

#endif
