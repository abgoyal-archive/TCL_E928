

#include <common.h>
#include <asm/arch/omap2420.h>
#include <asm/io.h>
#include <asm/arch/bits.h>
#include <asm/arch/mem.h>	/* get mem tables */
#include <asm/arch/sys_proto.h>
#include <asm/arch/sys_info.h>
#include <i2c.h>

static u32 get_prod_id(void)
{
	u32 p;
	p = __raw_readl(PRODUCTION_ID);	/* get production ID */
	return ((p & CPU_242X_PID_MASK) >> 16);
}

u32 get_cpu_type(void)
{
	u32 v;

	switch (get_prod_id()) {
	case 1:;		/* 2420 */
	case 2:
		return (CPU_2420);
		break;		/* 2420 pop */
	case 4:
		return (CPU_2422);
		break;
	case 8:
		return (CPU_2423);
		break;
	default:
		break;		/* early 2420/2422's unmarked */
	}

	v = __raw_readl(TAP_IDCODE_REG);
	v &= CPU_24XX_ID_MASK;
	/* currently 2420 and 2422 have same id */
	if (v == CPU_2420_CHIPID) {
		if (is_gpmc_muxed() == GPMC_MUXED)	/* if mux'ed */
			return (CPU_2420);
		else
			return (CPU_2422);
	} else
		return (CPU_2420);	/* don't know, say 2420 */
}

u32 get_cpu_rev(void)
{
	u32 v;
	v = __raw_readl(TAP_IDCODE_REG);
	v = v >> 28;
	return (v + 1);		/* currently 2422 and 2420 match up */
}

u32 is_mem_sdr(void)
{
	volatile u32 *burst = (volatile u32 *)(SDRC_MR_0 + SDRC_CS0_OSET);
	if (*burst == H4_2420_SDRC_MR_0_SDR)
		return (1);
	return (0);
}

u32 get_mem_type(void)
{
	u32 cpu, sdr = is_mem_sdr();

	cpu = get_cpu_type();
	if (cpu == CPU_2422 || cpu == CPU_2423)
		return (DDR_STACKED);

	if (get_prod_id() == 0x2)
		return (XDR_POP);

	if (get_board_type() == BOARD_H4_MENELAUS)
		if (sdr)
			return (SDR_DISCRETE);
		else
			return (DDR_COMBO);
	else if (sdr)		/* SDP + SDR kit */
		return (SDR_DISCRETE);
	else
		return (DDR_DISCRETE);	/* origional SDP */
}

u32 get_sdr_cs_size(u32 offset)
{
	u32 size;
	size = __raw_readl(SDRC_MCFG_0 + offset) >> 8;	/* get ram size field */
	size &= 0x2FF;		/* remove unwanted bits */
	size *= SZ_2M;		/* find size in MB */
	return (size);
}

u32 get_board_type(void)
{
	return (BOARD_H4_SDP);
}

inline u32 get_sysboot_value(void)
{
	return (0x00000FFF & __raw_readl(CONTROL_STATUS));
}

u32 get_gpmc0_base(void)
{
	u32 b;

	b = __raw_readl(GPMC_CONFIG7_0);
	b &= 0x1F;		/* keep base [5:0] */
	b = b << 24;		/* ret 0x0b000000 */
	return (b);
}

u32 is_gpmc_muxed(void)
{
	u32 mux;
	mux = get_sysboot_value();
	if ((mux & (BIT0 | BIT1 | BIT2 | BIT3)) == (BIT0 | BIT2 | BIT3))
		return (GPMC_MUXED);	/* NAND Boot mode */
	if (mux & BIT1)		/* if mux'ed */
		return (GPMC_MUXED);
	else
		return (GPMC_NONMUXED);
}

u32 get_gpmc0_type(void)
{
	u32 type;
	type = get_sysboot_value();
	if ((type & (BIT3 | BIT2)) == (BIT3 | BIT2))
		return (TYPE_NAND);
	else
		return (TYPE_NOR);
}

u32 get_gpmc0_width(void)
{
	u32 width;
	width = get_sysboot_value();
	if ((width & 0xF) == (BIT3 | BIT2))
		return (WIDTH_8BIT);
	else
		return (WIDTH_16BIT);
}

u32 wait_on_value(u32 read_bit_mask, u32 match_value, u32 read_addr, u32 bound)
{
	u32 i = 0, val;
	do {
		++i;
		val = __raw_readl(read_addr) & read_bit_mask;
		if (val == match_value)
			return (1);
		if (i == bound)
			return (0);
	} while (1);
}

void display_board_info(u32 btype)
{
	char cpu_2420[] = "2420";	/* cpu type */
	char cpu_2422[] = "2422";
	char cpu_2423[] = "2423";
	char db_men[] = "Menelaus";	/* board type */
	char db_ip[] = "IP";
	char mem_sdr[] = "mSDR";	/* memory type */
	char mem_ddr[] = "mDDR";
	char t_tst[] = "TST";	/* security level */
	char t_emu[] = "EMU";
	char t_hs[] = "HS";
	char t_gp[] = "GP";
	char unk[] = "?";

	char *cpu_s, *db_s, *mem_s, *sec_s;
	u32 cpu, rev, sec;

	rev = get_cpu_rev();
	cpu = get_cpu_type();
	sec = get_device_type();

	if (is_mem_sdr())
		mem_s = mem_sdr;
	else
		mem_s = mem_ddr;

	if (cpu == CPU_2423)
		cpu_s = cpu_2423;
	else if (cpu == CPU_2422)
		cpu_s = cpu_2422;
	else
		cpu_s = cpu_2420;

	if (btype == BOARD_H4_MENELAUS)
		db_s = db_men;
	else
		db_s = db_ip;

	switch (sec) {
	case TST_DEVICE:
		sec_s = t_tst;
		break;
	case EMU_DEVICE:
		sec_s = t_emu;
		break;
	case HS_DEVICE:
		sec_s = t_hs;
		break;
	case GP_DEVICE:
		sec_s = t_gp;
		break;
	default:
		sec_s = unk;
	}

	printf("OMAP%s-%s revision %d\n", cpu_s, sec_s, rev - 1);
	printf("Samsung Apollon SDP Base Board + %s \n", mem_s);
}

u32 get_board_rev(void)
{
	u32 rev = 0;
	u32 btype = get_board_type();

	if (btype == BOARD_H4_MENELAUS)
		rev = 1;
	return (rev);
}

u32 get_base(void)
{
	u32 val;
	__asm__ __volatile__("mov %0, pc \n":"=r"(val)::"memory");
	val &= 0xF0000000;
	val >>= 28;
	return (val);
}

u32 get_base2(void)
{
	u32 val;
	__asm__ __volatile__("mov %0, pc \n":"=r"(val)::"memory");
	val &= 0xFF000000;
	val >>= 24;
	return (val);
}

u32 running_in_flash(void)
{
	if (get_base() < 4)
		return (1);	/* in flash */
	return (0);		/* running in SRAM or SDRAM */
}

u32 running_in_sram(void)
{
	if (get_base() == 4)
		return (1);	/* in SRAM */
	return (0);		/* running in FLASH or SDRAM */
}

u32 running_in_sdram(void)
{
	if (get_base() > 4)
		return (1);	/* in sdram */
	return (0);		/* running in SRAM or FLASH */
}

u32 running_from_internal_boot(void)
{
	u32 v, base;

	v = get_sysboot_value() & BIT3;
	base = get_base2();
	/* if running at mask rom flash address and
	 * sysboot3 says this was an internal boot
	 */
	if ((base == 0x08) && v)
		return (1);
	else
		return (0);
}

u32 get_device_type(void)
{
	int mode;
	mode = __raw_readl(CONTROL_STATUS) & (BIT10 | BIT9 | BIT8);
	return (mode >>= 8);
}
