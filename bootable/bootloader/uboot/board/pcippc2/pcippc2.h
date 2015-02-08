

#ifndef _PCIPPC2_H_
#define _PCIPPC2_H_

#include <config.h>
#include <common.h>

#include "hardware.h"

#define FPGA(r, p)	(pcippc2_fpga0_phys + HW_FPGA0_##r##_##p)
#define UART(r)		(pcippc2_fpga0_phys + HW_FPGA0_UART1 + NS16550_##r * 4)
#define RTC(r)		(pcippc2_fpga1_phys + HW_FPGA1_RTC + r)

extern u32		pcippc2_fpga0_phys;
extern u32		pcippc2_fpga1_phys;

extern u32	pcippc2_sdram_size		(void);

extern void	pcippc2_fpga_init		(void);

extern void	pcippc2_cpci3264_init	(void);

extern void	cpc710_pci_init			(void);
extern void	cpc710_pci_enable_timeout	(void);

extern unsigned long
		cpc710_ram_init			(void);

#endif
