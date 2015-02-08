

#include <common.h>
#include <mpc824x.h>
#include <asm/processor.h>

DECLARE_GLOBAL_DATA_PTR;

/* ------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------- */

/* This gives the PCI to Memory multiplier times 10 */
/* The index is the value of PLL_CFG[0:4] */
/* This is documented in the MPC8240/5 Hardware Specs */

short pll_pci_to_mem_multiplier[] = {
#if defined(CONFIG_MPC8240)
	30, 30, 10, 10, 20, 10,  0, 10,
	10,  0, 20,  0, 20,  0, 20,  0,
	30,  0, 15,  0, 20,  0, 20,  0,
	25,  0, 10,  0, 15, 15,  0,  0,
#elif defined(CONFIG_MPC8245)
	30, 30, 10, 10, 20, 10, 10, 10,
	10, 20, 20, 15, 20, 15, 20, 30,
	30, 40, 15, 40, 20, 25, 20, 40,
	25, 20, 10, 20, 15, 15, 15,  0,
#else
#error Specific type of MPC824x must be defined (i.e. CONFIG_MPC8240)
#endif
};

#define CU824_PLL_STATE_REG	0xFE80002F
#define PCR			0x800000E2

/* ------------------------------------------------------------------------- */

/* compute the memory bus clock frequency */
ulong get_bus_freq (ulong dummy)
{
	unsigned char pll_cfg;
#if defined(CONFIG_MPC8240) && !defined(CONFIG_CU824)
	return (CONFIG_SYS_CLK_FREQ) * (CONFIG_PLL_PCI_TO_MEM_MULTIPLIER);
#elif defined(CONFIG_CU824)
	pll_cfg = *(volatile unsigned char *) (CU824_PLL_STATE_REG);
	pll_cfg &= 0x1f;
#else
	CONFIG_READ_BYTE(PCR, pll_cfg);
	pll_cfg = (pll_cfg >> 3) & 0x1f;
#endif
	return ((CONFIG_SYS_CLK_FREQ) * pll_pci_to_mem_multiplier[pll_cfg] + 5) / 10;
}


/* ------------------------------------------------------------------------- */

/* This gives the Memory to CPU Core multiplier times 10 */
/* The index is the value of PLLRATIO in HID1 */
/* This is documented in the MPC8240 Hardware Specs */
/* This is not documented for MPC8245 ? FIXME */
short pllratio_to_factor[] = {
     0,  0,  0, 10, 20, 20, 25, 45,
    30,  0,  0,  0,  0,  0,  0,  0,
     0,  0,  0, 10,  0,  0,  0, 45,
    30,  0, 40,  0,  0,  0, 35,  0,
};

/* compute the CPU and memory bus clock frequencies */
int get_clocks (void)
{
	uint hid1 = mfspr(HID1);
	hid1 = (hid1 >> (32-5)) & 0x1f;
	gd->cpu_clk = (pllratio_to_factor[hid1] * get_bus_freq(0) + 5)
			  / 10;
	gd->bus_clk = get_bus_freq(0);
	return (0);
}
