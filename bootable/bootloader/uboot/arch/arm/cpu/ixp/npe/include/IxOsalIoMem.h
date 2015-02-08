


#ifndef IxOsalIoMem_H
#define IxOsalIoMem_H


#include "IxOsalEndianess.h"


/* Low-level conversion macros - DO NOT USE UNLESS ABSOLUTELY NEEDED */
#ifndef __wince


#ifdef __XSCALE__
static __inline__ UINT32
ixOsalCoreWordSwap (UINT32 wordIn)
{
    /*
     * Storage for the swapped word 
     */
    UINT32 wordOut;

    /*
     * wordIn = A, B, C, D 
     */
    __asm__ (" eor r1, %1, %1, ror #16;"	/* R1 =      A^C, B^D, C^A, D^B */
	     " bic r1, r1, #0x00ff0000;"	/* R1 =      A^C, 0  , C^A, D^B */
	     " mov %0, %1, ror #8;"	/* wordOut = D,   A,   B,   C   */
	     " eor %0, %0, r1, lsr #8;"	/* wordOut = D,   C,   B,   A   */
  : "=r" (wordOut): "r" (wordIn):"r1");

    return wordOut;
}

#define IX_OSAL_SWAP_LONG(wData)          (ixOsalCoreWordSwap(wData))
#else
#define IX_OSAL_SWAP_LONG(wData)          ((wData >> 24) | (((wData >> 16) & 0xFF) << 8) | (((wData >> 8) & 0xFF) << 16) | ((wData & 0xFF) << 24))
#endif

#else /* ndef __wince */
#define IX_OSAL_SWAP_LONG(wData)        ((((UINT32)wData << 24) | ((UINT32)wData >> 24)) | (((wData << 8) & 0xff0000) | ((wData >> 8) & 0xff00)))
#endif /* ndef __wince */

#define IX_OSAL_SWAP_SHORT(sData)         ((sData >> 8) | ((sData & 0xFF) << 8))
#define IX_OSAL_SWAP_SHORT_ADDRESS(sAddr) ((sAddr) ^ 0x2)
#define IX_OSAL_SWAP_BYTE_ADDRESS(bAddr)  ((bAddr) ^ 0x3)

#define IX_OSAL_BE_XSTOBUSL(wData)  (wData)
#define IX_OSAL_BE_XSTOBUSS(sData)  (sData)
#define IX_OSAL_BE_XSTOBUSB(bData)  (bData)
#define IX_OSAL_BE_BUSTOXSL(wData)  (wData)
#define IX_OSAL_BE_BUSTOXSS(sData)  (sData)
#define IX_OSAL_BE_BUSTOXSB(bData)  (bData)

#define IX_OSAL_LE_AC_XSTOBUSL(wAddr) (wAddr)
#define IX_OSAL_LE_AC_XSTOBUSS(sAddr) IX_OSAL_SWAP_SHORT_ADDRESS(sAddr)
#define IX_OSAL_LE_AC_XSTOBUSB(bAddr) IX_OSAL_SWAP_BYTE_ADDRESS(bAddr)
#define IX_OSAL_LE_AC_BUSTOXSL(wAddr) (wAddr)
#define IX_OSAL_LE_AC_BUSTOXSS(sAddr) IX_OSAL_SWAP_SHORT_ADDRESS(sAddr)
#define IX_OSAL_LE_AC_BUSTOXSB(bAddr) IX_OSAL_SWAP_BYTE_ADDRESS(bAddr)

#define IX_OSAL_LE_DC_XSTOBUSL(wData) IX_OSAL_SWAP_LONG(wData)
#define IX_OSAL_LE_DC_XSTOBUSS(sData) IX_OSAL_SWAP_SHORT(sData)
#define IX_OSAL_LE_DC_XSTOBUSB(bData) (bData)
#define IX_OSAL_LE_DC_BUSTOXSL(wData) IX_OSAL_SWAP_LONG(wData)
#define IX_OSAL_LE_DC_BUSTOXSS(sData) IX_OSAL_SWAP_SHORT(sData)
#define IX_OSAL_LE_DC_BUSTOXSB(bData) (bData)


#include "IxOsalMemAccess.h"


typedef enum
{
    IX_OSAL_STATIC_MAP = 0,	 /**<Set map entry type to static map */
    IX_OSAL_DYNAMIC_MAP	     /**<Set map entry type to dynamic map */
} IxOsalMapEntryType;


typedef enum
{
    IX_OSAL_BE = 0x1,      /**<Set map endian mode to Big Endian */
    IX_OSAL_LE_AC = 0x2,   /**<Set map endian mode to Little Endian, Address Coherent */
    IX_OSAL_LE_DC = 0x4,   /**<Set map endian mode to Little Endian, Data Coherent */
    IX_OSAL_LE = 0x8       /**<Set map endian mode to Little Endian without specifying coherency mode */
} IxOsalMapEndianessType;


typedef struct _IxOsalMemoryMap
{
    IxOsalMapEntryType type;   /**< map type - IX_OSAL_STATIC_MAP or IX_OSAL_DYNAMIC_MAP */

    UINT32 physicalAddress;    /**< physical address of the memory mapped I/O zone */

    UINT32 size;               /**< size of the map */

    UINT32 virtualAddress;     /**< virtual address of the zone; must be predefined
                                    in the global memory map for static maps and has
                                    to be NULL for dynamic maps (populated on allocation)
								*/
    /*
     * pointer to a map function called to map a dynamic map; 
     * will populate the virtualAddress field 
     */
    void (*mapFunction) (struct _IxOsalMemoryMap * map);   /**< pointer to a map function called to map a dynamic map */

    /*
     * pointer to a map function called to unmap a dynamic map; 
     * will reset the virtualAddress field to NULL 
     */
    void (*unmapFunction) (struct _IxOsalMemoryMap * map); /**< pointer to a map function called to unmap a dynamic map */

    /*
     * reference count describing how many components share this map; 
     * actual allocation/deallocation for dynamic maps is done only 
     * between 0 <=> 1 transitions of the counter 
     */
    UINT32 refCount;   /**< reference count describing how many components share this map */

    /*
     * memory endian type for the map; can be a combination of IX_OSAL_BE (Big 
     * Endian) and IX_OSAL_LE or IX_OSAL_LE_AC or IX_OSAL_LE_DC
     * (Little Endian, Address Coherent or Data Coherent). Any combination is
     * allowed provided it contains at most one LE flag - e.g.
     * (IX_OSAL_BE), (IX_OSAL_LE_AC), (IX_OSAL_BE | IX_OSAL_LE_DC) are valid
     * combinations while (IX_OSAL_BE | IX_OSAL_LE_DC | IX_OSAL_LE_AC) is not. 
     */
    IxOsalMapEndianessType mapEndianType; /**< memory endian type for the map */

    char *name;      /**< user-friendly name */
} IxOsalMemoryMap;




PUBLIC void *ixOsalIoMemMap (UINT32 requestedAddress,
			     UINT32 size,
			     IxOsalMapEndianessType requestedCoherency);


PUBLIC void ixOsalIoMemUnmap (UINT32 requestedAddress, UINT32 coherency);


PUBLIC UINT32 ixOsalIoMemVirtToPhys (UINT32 virtualAddress, UINT32 coherency);


PUBLIC UINT32
ixOsalIoMemPhysToVirt (UINT32 physicalAddress, UINT32 coherency);

#define IX_OSAL_MEM_MAP(physAddr, size) \
    ixOsalIoMemMap((physAddr), (size), IX_OSAL_COMPONENT_MAPPING)


#define IX_OSAL_MEM_UNMAP(virtAddr) \
    ixOsalIoMemUnmap ((virtAddr), IX_OSAL_COMPONENT_MAPPING)

#define IX_OSAL_MMAP_VIRT_TO_PHYS(virtAddr) \
    ixOsalIoMemVirtToPhys(virtAddr, IX_OSAL_COMPONENT_MAPPING)


#define IX_OSAL_MMAP_PHYS_TO_VIRT(physAddr) \
    ixOsalIoMemPhysToVirt(physAddr, IX_OSAL_COMPONENT_MAPPING)


#endif /* IxOsalIoMem_H */
