

#ifndef __ASM_ARCH_MEMORY_H
#define __ASM_ARCH_MEMORY_H


#define TASK_SIZE       (0xc0000000UL)
#define TASK_SIZE_26	(0x04000000UL)

#define TASK_UNMAPPED_BASE (TASK_SIZE / 3)

#define PAGE_OFFSET     (0xc0000000UL)

#define PHYS_OFFSET	(0x0c000000UL)

#include <linux/config.h>


/* Modified for S3C2400, by chc, 20010509 */
#define RAM_IN_BANK_0  32*1024*1024
#define RAM_IN_BANK_1  0
#define RAM_IN_BANK_2  0
#define RAM_IN_BANK_3  0

#define MEM_SIZE  (RAM_IN_BANK_0+RAM_IN_BANK_1+RAM_IN_BANK_2+RAM_IN_BANK_3)


/* translation macros */
#define __virt_to_phys__is_a_macro
#define __phys_to_virt__is_a_macro

#if (RAM_IN_BANK_1 + RAM_IN_BANK_2 + RAM_IN_BANK_3 == 0)

#define __virt_to_phys(x) ( (x) - PAGE_OFFSET + 0x0c000000 )
#define __phys_to_virt(x) ( (x) - 0x0c000000 + PAGE_OFFSET )

#elif (RAM_IN_BANK_0 == RAM_IN_BANK_1) && \
      (RAM_IN_BANK_2 + RAM_IN_BANK_3 == 0)

/* Two identical banks */
#define __virt_to_phys(x) \
	  ( ((x) < PAGE_OFFSET+RAM_IN_BANK_0) ? \
	    ((x) - PAGE_OFFSET + _DRAMBnk0) : \
	    ((x) - PAGE_OFFSET - RAM_IN_BANK_0 + _DRAMBnk1) )
#define __phys_to_virt(x) \
	  ( ((x)&0x07ffffff) + \
	    (((x)&0x08000000) ? PAGE_OFFSET+RAM_IN_BANK_0 : PAGE_OFFSET) )
#else

/* It's more efficient for all other cases to use the function call */
#undef __virt_to_phys__is_a_macro
#undef __phys_to_virt__is_a_macro
extern unsigned long __virt_to_phys(unsigned long vpage);
extern unsigned long __phys_to_virt(unsigned long ppage);

#endif

#define __virt_to_bus__is_a_macro
#define __virt_to_bus(x)        __virt_to_phys(x)
#define __bus_to_virt__is_a_macro
#define __bus_to_virt(x)        __phys_to_virt(x)


#ifdef CONFIG_DISCONTIGMEM
#error "CONFIG_DISCONTIGMEM will not work on S3C2400"

#define NR_NODES	4

#define KVADDR_TO_NID(addr) \
		(((unsigned long)(addr) - 0xc0000000) >> 27)

#define PHYS_TO_NID(addr) KVADDR_TO_NID(__phys_to_virt(addr))

#define ADDR_TO_MAPBASE(kaddr) \
			NODE_MEM_MAP(KVADDR_TO_NID((unsigned long)(kaddr)))

#define LOCAL_MAP_NR(kvaddr) \
	(((unsigned long)(kvaddr) & 0x07ffffff) >> PAGE_SHIFT)

#define virt_to_page(kaddr) \
	(ADDR_TO_MAPBASE(kaddr) + LOCAL_MAP_NR(kaddr))

#define VALID_PAGE(page) \
({ unsigned int node = KVADDR_TO_NID(page); \
   ( (node < NR_NODES) && \
     ((unsigned)((page) - NODE_MEM_MAP(node)) < NODE_DATA(node)->node_size) ); \
})

#else

#define PHYS_TO_NID(addr)	(0)

#endif
#endif /* __ASM_ARCH_MEMORY_H */
