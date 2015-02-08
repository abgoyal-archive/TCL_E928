

#include <config.h>
#include <asm/arch/kirkwood.h>

#define KW_REG_CPUCS_WIN_BAR(x)		(KW_REGISTER(0x1500) + (x * 0x08))
#define KW_REG_CPUCS_WIN_SZ(x)		(KW_REGISTER(0x1504) + (x * 0x08))
u32 kw_sdram_bar(enum memory_bank bank)
{
	u32 result = 0;
	u32 enable = 0x01 & readl(KW_REG_CPUCS_WIN_SZ(bank));

	if ((!enable) || (bank > BANK3))
		return 0;

	result = readl(KW_REG_CPUCS_WIN_BAR(bank));
	return result;
}

u32 kw_sdram_bs(enum memory_bank bank)
{
	u32 result = 0;
	u32 enable = 0x01 & readl(KW_REG_CPUCS_WIN_SZ(bank));

	if ((!enable) || (bank > BANK3))
		return 0;
	result = 0xff000000 & readl(KW_REG_CPUCS_WIN_SZ(bank));
	result += 0x01000000;
	return result;
}
