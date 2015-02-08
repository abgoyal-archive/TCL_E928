

#include <common.h>
#include <asm/inca-ip.h>


uint incaip_get_cpuclk (void)
{
	/*-------------------------------------------------------------------------*/
	/* CPU Clock Input Multiplexer (MUX I)                                     */
	/* Multiplexer MUX I selects the maximum input clock to the CPU.           */
	/*-------------------------------------------------------------------------*/
	if (*((volatile ulong *) INCA_IP_CGU_CGU_MUXCR) &
	    INCA_IP_CGU_CGU_MUXCR_MUXI) {
		/* MUX I set to 150 MHz clock */
		return 150000000;
	} else {
		/* MUX I set to 100/133 MHz clock */
		if (*((volatile ulong *) INCA_IP_CGU_CGU_DIVCR) & 0x40) {
			/* Division value is 1/3, maximum CPU operating */
			/* frequency is 133.3 MHz                       */
			return 133333333;
		} else {
			/* Division value is 1/4, maximum CPU operating */
			/* frequency is 100 MHz                         */
			return 100000000;
		}
	}
}

uint incaip_get_fpiclk (void)
{
	uint clkCPU;

	clkCPU = incaip_get_cpuclk ();

	switch (*((volatile ulong *) INCA_IP_CGU_CGU_DIVCR) & 0xC) {
	case 0x4:
		return clkCPU >> 1;	/* devided by 2 */
		break;
	case 0x8:
		return clkCPU >> 2;	/* devided by 4 */
		break;
	default:
		return clkCPU;
		break;
	}
}

int incaip_set_cpuclk (void)
{
	extern void ebu_init(long);
	extern void cgu_init(long);
	extern void sdram_init(long);
	char tmp[64];
	ulong cpuclk;

	if (getenv_r ("cpuclk", tmp, sizeof (tmp)) > 0) {
		cpuclk = simple_strtoul (tmp, NULL, 10) * 1000000;
		cgu_init (cpuclk);
		ebu_init (cpuclk);
		sdram_init (cpuclk);
	}

	return 0;
}
