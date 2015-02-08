

#include <common.h>
#include "memio.h"

void enable_nvram(void)
{
    pci_write_cfg_byte(0, 0, 0x56, 0x0b);
}

void disable_nvram(void)
{
    pci_write_cfg_byte(0, 0, 0x56, 0x0);
}
