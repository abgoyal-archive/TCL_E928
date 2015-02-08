
#include <common.h>
#include <asm/io.h>
#include <asm/arch/clk.h>

/* Default is s5pc100 */
unsigned int s5pc1xx_cpu_id = 0xC100;

#ifdef CONFIG_ARCH_CPU_INIT
int arch_cpu_init(void)
{
	s5pc1xx_cpu_id = readl(S5PC1XX_PRO_ID);
	s5pc1xx_cpu_id = 0xC000 | ((s5pc1xx_cpu_id & 0x00FFF000) >> 12);

	s5pc1xx_clock_init();

	return 0;
}
#endif

u32 get_device_type(void)
{
	return s5pc1xx_cpu_id;
}

#ifdef CONFIG_DISPLAY_CPUINFO
int print_cpuinfo(void)
{
	char buf[32];

	printf("CPU:\tS5P%X@%sMHz\n",
			s5pc1xx_cpu_id, strmhz(buf, get_arm_clk()));

	return 0;
}
#endif
