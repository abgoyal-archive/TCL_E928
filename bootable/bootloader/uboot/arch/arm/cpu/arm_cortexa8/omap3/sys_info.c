

#include <common.h>
#include <asm/io.h>
#include <asm/arch/mem.h>	/* get mem tables */
#include <asm/arch/sys_proto.h>
#include <i2c.h>

extern omap3_sysinfo sysinfo;
static struct sdrc *sdrc_base = (struct sdrc *)OMAP34XX_SDRC_BASE;
static struct ctrl *ctrl_base = (struct ctrl *)OMAP34XX_CTRL_BASE;
static char *rev_s[CPU_3XX_MAX_REV] = {
				"1.0",
				"2.0",
				"2.1",
				"3.0",
				"3.1"};

void dieid_num_r(void)
{
	struct ctrl_id *id_base = (struct ctrl_id *)OMAP34XX_ID_L4_IO_BASE;
	char *uid_s, die_id[34];
	u32 id[4];

	memset(die_id, 0, sizeof(die_id));

	uid_s = getenv("dieid#");

	if (uid_s == NULL) {
		id[3] = readl(&id_base->die_id_0);
		id[2] = readl(&id_base->die_id_1);
		id[1] = readl(&id_base->die_id_2);
		id[0] = readl(&id_base->die_id_3);
		sprintf(die_id, "%08x%08x%08x%08x", id[0], id[1], id[2], id[3]);
		setenv("dieid#", die_id);
		uid_s = die_id;
	}

	printf("Die ID #%s\n", uid_s);
}

u32 get_cpu_type(void)
{
	return readl(&ctrl_base->ctrl_omap_stat);
}

u32 get_cpu_rev(void)
{
	u32 cpuid = 0;
	struct ctrl_id *id_base;

	/*
	 * On ES1.0 the IDCODE register is not exposed on L4
	 * so using CPU ID to differentiate between ES1.0 and > ES1.0.
	 */
	__asm__ __volatile__("mrc p15, 0, %0, c0, c0, 0":"=r"(cpuid));
	if ((cpuid & 0xf) == 0x0)
		return CPU_3XX_ES10;
	else {
		/* Decode the IDs on > ES1.0 */
		id_base = (struct ctrl_id *) OMAP34XX_ID_L4_IO_BASE;

		cpuid = (readl(&id_base->idcode) >> CPU_3XX_ID_SHIFT) & 0xf;

		/* Some early ES2.0 seem to report ID 0, fix this */
		if(cpuid == 0)
			cpuid = CPU_3XX_ES20;

		return cpuid;
	}
}

u32 is_mem_sdr(void)
{
	if (readl(&sdrc_base->cs[CS0].mr) == SDRC_MR_0_SDR)
		return 1;
	return 0;
}

u32 get_sdr_cs_size(u32 cs)
{
	u32 size;

	/* get ram size field */
	size = readl(&sdrc_base->cs[cs].mcfg) >> 8;
	size &= 0x3FF;		/* remove unwanted bits */
	size <<= 21;		/* multiply by 2 MiB to find size in MB */
	return size;
}

u32 get_sdr_cs_offset(u32 cs)
{
	u32 offset;

	if (!cs)
		return 0;

	offset = readl(&sdrc_base->cs_cfg);
	offset = (offset & 15) << 27 | (offset & 0x30) >> 17;

	return offset;
}

u32 get_gpmc0_base(void)
{
	u32 b;

	b = readl(&gpmc_cfg->cs[0].config7);
	b &= 0x1F;		/* keep base [5:0] */
	b = b << 24;		/* ret 0x0b000000 */
	return b;
}

u32 get_gpmc0_width(void)
{
	return WIDTH_16BIT;
}

u32 get_board_rev(void)
{
	return 0x20;
}

u32 get_base(void)
{
	u32 val;

	__asm__ __volatile__("mov %0, pc \n":"=r"(val)::"memory");
	val &= 0xF0000000;
	val >>= 28;
	return val;
}

u32 is_running_in_flash(void)
{
	if (get_base() < 4)
		return 1;	/* in FLASH */

	return 0;		/* running in SRAM or SDRAM */
}

u32 is_running_in_sram(void)
{
	if (get_base() == 4)
		return 1;	/* in SRAM */

	return 0;		/* running in FLASH or SDRAM */
}

u32 is_running_in_sdram(void)
{
	if (get_base() > 4)
		return 1;	/* in SDRAM */

	return 0;		/* running in SRAM or FLASH */
}

u32 get_boot_type(void)
{
	return (readl(&ctrl_base->status) & SYSBOOT_MASK);
}

u32 get_device_type(void)
{
	return ((readl(&ctrl_base->status) & (DEVICE_MASK)) >> 8);
}

#ifdef CONFIG_DISPLAY_CPUINFO
int print_cpuinfo (void)
{
	char *cpu_s, *sec_s;

	switch (get_cpu_type()) {
	case OMAP3503:
		cpu_s = "3503";
		break;
	case OMAP3515:
		cpu_s = "3515";
		break;
	case OMAP3525:
		cpu_s = "3525";
		break;
	case OMAP3530:
		cpu_s = "3530";
		break;
	default:
		cpu_s = "35XX";
		break;
	}

	switch (get_device_type()) {
	case TST_DEVICE:
		sec_s = "TST";
		break;
	case EMU_DEVICE:
		sec_s = "EMU";
		break;
	case HS_DEVICE:
		sec_s = "HS";
		break;
	case GP_DEVICE:
		sec_s = "GP";
		break;
	default:
		sec_s = "?";
	}

	printf("OMAP%s-%s ES%s, CPU-OPP2 L3-165MHz\n",
			cpu_s, sec_s, rev_s[get_cpu_rev()]);

	return 0;
}
#endif	/* CONFIG_DISPLAY_CPUINFO */
