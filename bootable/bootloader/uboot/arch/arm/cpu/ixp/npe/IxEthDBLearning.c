

#include "IxEthDB_p.h"

UINT32 ixEthDBEntryXORHash(void *entry)
{
    MacDescriptor *descriptor = (MacDescriptor *) entry;

    return ixEthDBKeyXORHash(descriptor->macAddress);
}

UINT32 ixEthDBKeyXORHash(void *key)
{
    UINT32 hashValue;
    UINT8 *value = (UINT8 *) key;
    
    hashValue  = (value[5] << 8) | value[4];
    hashValue ^= (value[3] << 8) | value[2];
    hashValue ^= (value[1] << 8) | value[0];

    return hashValue;
}

BOOL ixEthDBAddressMatch(void *reference, void *entry)
{
    return (ixEthDBAddressCompare(reference, ((MacDescriptor *) entry)->macAddress) == 0);
}

UINT32 ixEthDBAddressCompare(UINT8 *mac1, UINT8 *mac2)
{
    UINT32 local_index;

    for (local_index = 0 ; local_index < IX_IEEE803_MAC_ADDRESS_SIZE ; local_index++)
    {
        if (mac1[local_index] > mac2[local_index])
        {
            return 1;
        }
        else if (mac1[local_index] < mac2[local_index])
        {
            return -1;
        }
    }

    return 0;
}

