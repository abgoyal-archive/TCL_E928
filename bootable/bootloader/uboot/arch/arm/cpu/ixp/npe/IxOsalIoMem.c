

/* Access to the global mem map is only allowed in this file */
#define IxOsalIoMem_C

#include "IxOsal.h"

#define SEARCH_PHYSICAL_ADDRESS (1)
#define SEARCH_VIRTUAL_ADDRESS  (2)

PRIVATE IxOsalMemoryMap *
ixOsalMemMapFind (UINT32 requestedAddress,
    UINT32 size, UINT32 searchCriteria, UINT32 requestedEndianType)
{
    UINT32 mapIndex;

    UINT32 numMapElements =
        sizeof (ixOsalGlobalMemoryMap) / sizeof (IxOsalMemoryMap);

    for (mapIndex = 0; mapIndex < numMapElements; mapIndex++)
    {
        IxOsalMemoryMap *map = &ixOsalGlobalMemoryMap[mapIndex];

        if (searchCriteria == SEARCH_PHYSICAL_ADDRESS
            && requestedAddress >= map->physicalAddress
            && (requestedAddress + size) <= (map->physicalAddress + map->size)
            && (map->mapEndianType & requestedEndianType) != 0)
        {
            return map;
        }
        else if (searchCriteria == SEARCH_VIRTUAL_ADDRESS
            && requestedAddress >= map->virtualAddress
            && requestedAddress <= (map->virtualAddress + map->size)
            && (map->mapEndianType & requestedEndianType) != 0)
        {
            return map;
        }
        else if (searchCriteria == SEARCH_PHYSICAL_ADDRESS)
        {
            ixOsalLog (IX_OSAL_LOG_LVL_DEBUG3,
                IX_OSAL_LOG_DEV_STDOUT,
                "Osal: Checking [phys addr 0x%x:size 0x%x:endianType %d]\n",
                map->physicalAddress, map->size, map->mapEndianType, 0, 0, 0);
        }
    }

    /*
     * not found 
     */
    return NULL;
}

PUBLIC void *
ixOsalIoMemMap (UINT32 requestedAddress,
    UINT32 size, IxOsalMapEndianessType requestedEndianType)
{
    IxOsalMemoryMap *map;

    ixOsalLog (IX_OSAL_LOG_LVL_DEBUG3,
        IX_OSAL_LOG_DEV_STDOUT,
        "OSAL: Mapping [addr 0x%x:size 0x%x:endianType %d]\n",
        requestedAddress, size, requestedEndianType, 0, 0, 0);

    if (requestedEndianType == IX_OSAL_LE)
    {
        ixOsalLog (IX_OSAL_LOG_LVL_ERROR,
            IX_OSAL_LOG_DEV_STDOUT,
            "ixOsalIoMemMap: Please specify component coherency mode to use MEM functions \n",
            0, 0, 0, 0, 0, 0);
        return (NULL);
    }
    map = ixOsalMemMapFind (requestedAddress,
        size, SEARCH_PHYSICAL_ADDRESS, requestedEndianType);
    if (map != NULL)
    {
        UINT32 offset = requestedAddress - map->physicalAddress;

        ixOsalLog (IX_OSAL_LOG_LVL_DEBUG3,
            IX_OSAL_LOG_DEV_STDOUT, "OSAL: Found map [", 0, 0, 0, 0, 0, 0);
        ixOsalLog (IX_OSAL_LOG_LVL_DEBUG3,
            IX_OSAL_LOG_DEV_STDOUT, map->name, 0, 0, 0, 0, 0, 0);
        ixOsalLog (IX_OSAL_LOG_LVL_DEBUG3,
            IX_OSAL_LOG_DEV_STDOUT,
            ":addr 0x%x: virt 0x%x:size 0x%x:ref %d:endianType %d]\n",
            map->physicalAddress, map->virtualAddress,
            map->size, map->refCount, map->mapEndianType, 0);

        if (map->type == IX_OSAL_DYNAMIC_MAP && map->virtualAddress == 0)
        {
            if (map->mapFunction != NULL)
            {
                map->mapFunction (map);

                if (map->virtualAddress == 0)
                {
                    /*
                     * failed 
                     */
                    ixOsalLog (IX_OSAL_LOG_LVL_FATAL,
                        IX_OSAL_LOG_DEV_STDERR,
                        "OSAL: Remap failed - [addr 0x%x:size 0x%x:endianType %d]\n",
                        requestedAddress, size, requestedEndianType, 0, 0, 0);
                    return NULL;
                }
            }
            else
            {
                /*
                 * error, no map function for a dynamic map 
                 */
                ixOsalLog (IX_OSAL_LOG_LVL_FATAL,
                    IX_OSAL_LOG_DEV_STDERR,
                    "OSAL: No map function for a dynamic map - "
                    "[addr 0x%x:size 0x%x:endianType %d]\n",
                    requestedAddress, size, requestedEndianType, 0, 0, 0);

                return NULL;
            }
        }

        /*
         * increment reference count 
         */
        map->refCount++;

        return (void *) (map->virtualAddress + offset);
    }

    /*
     * requested address is not described in the global memory map 
     */
    ixOsalLog (IX_OSAL_LOG_LVL_FATAL,
        IX_OSAL_LOG_DEV_STDERR,
        "OSAL: No mapping found - [addr 0x%x:size 0x%x:endianType %d]\n",
        requestedAddress, size, requestedEndianType, 0, 0, 0);
    return NULL;
}

PUBLIC void
ixOsalIoMemUnmap (UINT32 requestedAddress, UINT32 endianType)
{
    IxOsalMemoryMap *map;

    if (endianType == IX_OSAL_LE)
    {
        ixOsalLog (IX_OSAL_LOG_LVL_ERROR,
            IX_OSAL_LOG_DEV_STDOUT,
            "ixOsalIoMemUnmap: Please specify component coherency mode to use MEM functions \n",
            0, 0, 0, 0, 0, 0);
        return;
    }

    if (requestedAddress == 0)
    {
        /*
         * invalid virtual address 
         */
        return;
    }

    map =
        ixOsalMemMapFind (requestedAddress, 0, SEARCH_VIRTUAL_ADDRESS,
        endianType);

    if (map != NULL)
    {
        if (map->refCount > 0)
        {
            /*
             * decrement reference count 
             */
            map->refCount--;

            if (map->refCount == 0)
            {
                /*
                 * no longer used, deallocate 
                 */
                if (map->type == IX_OSAL_DYNAMIC_MAP
                    && map->unmapFunction != NULL)
                {
                    map->unmapFunction (map);
                }
            }
        }
    }
    else
    {
        ixOsalLog (IX_OSAL_LOG_LVL_WARNING,
            IX_OSAL_LOG_DEV_STDERR,
            "OSAL: ixOsServMemUnmap didn't find the requested map "
            "[virt addr 0x%x: endianType %d], ignoring call\n",
            requestedAddress, endianType, 0, 0, 0, 0);
    }
}

PUBLIC UINT32
ixOsalIoMemVirtToPhys (UINT32 virtualAddress, UINT32 requestedCoherency)
{
    IxOsalMemoryMap *map =
        ixOsalMemMapFind (virtualAddress, 0, SEARCH_VIRTUAL_ADDRESS,
        requestedCoherency);

    if (map != NULL)
    {
        return map->physicalAddress + virtualAddress - map->virtualAddress;
    }
    else
    {
        return (UINT32) IX_OSAL_MMU_VIRT_TO_PHYS (virtualAddress);
    }
}

PUBLIC UINT32
ixOsalIoMemPhysToVirt (UINT32 physicalAddress, UINT32 requestedCoherency)
{
    IxOsalMemoryMap *map =
        ixOsalMemMapFind (physicalAddress, 0, SEARCH_PHYSICAL_ADDRESS,
        requestedCoherency);

    if (map != NULL)
    {
        return map->virtualAddress + physicalAddress - map->physicalAddress;
    }
    else
    {
        return (UINT32) IX_OSAL_MMU_PHYS_TO_VIRT (physicalAddress);
    }
}
