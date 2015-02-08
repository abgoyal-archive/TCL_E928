

#ifndef _HARDWARE_H_
#define _HARDWARE_H_

#include "cpc710.h"
#include "cpc710_pci.h"
#include "pcippc2_fpga.h"
#include "ns16550.h"

#define REG(r, x)	(HW_PHYS_##r + HW_##r##_##x)

  /* Address map:
   *
   * 0x00000000-0x20000000	SDRAM
   * 0x40000000-0x00008000	Init RAM in the CPU DCache
   * 0xf0000000-0xf8000000	CPCI MEM
   * 0xf8000000-0xfc000000	Local PCI MEM
   * 0xfc000000-0xfe000000	CPCI I/O
   * 0xfe000000-0xff000000	Local PCI I/O
   * 0xff000000-0xff201000	System configuration space
   * 0xff400000-0xff500000	Local PCI bridge space
   * 0xff500000-0xff600000	CPCI bridge space
   * 0xfff00000-0xfff80000	Boot Flash
   */

#endif
