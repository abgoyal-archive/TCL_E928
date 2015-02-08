
#ifndef _SYS_PROTO_H_
#define _SYS_PROTO_H_

typedef struct {
	u32 mtype;
	char *board_string;
	char *nand_string;
} omap3_sysinfo;

void prcm_init(void);
void per_clocks_enable(void);

void memif_init(void);
void sdrc_init(void);
void do_sdrc_init(u32, u32);
void gpmc_init(void);
void enable_gpmc_cs_config(const u32 *gpmc_config, struct gpmc_cs *cs, u32 base,
			u32 size);

void watchdog_init(void);
void set_muxconf_regs(void);

u32 get_cpu_rev(void);
u32 get_mem_type(void);
u32 get_sysboot_value(void);
u32 is_gpmc_muxed(void);
u32 get_gpmc0_type(void);
u32 get_gpmc0_width(void);
u32 get_sdr_cs_size(u32);
u32 get_sdr_cs_offset(u32);
u32 is_running_in_sdram(void);
u32 is_running_in_sram(void);
u32 is_running_in_flash(void);
u32 get_device_type(void);
void l2cache_enable(void);
void secureworld_exit(void);
void setup_auxcr(void);
void try_unlock_memory(void);
u32 get_boot_type(void);
void invalidate_dcache(u32);
void sr32(void *, u32, u32, u32);
u32 wait_on_value(u32, u32, void *, u32);
void sdelay(unsigned long);
void make_cs1_contiguous(void);
void omap_nand_switch_ecc(int);
void power_init_r(void);
void dieid_num_r(void);

#endif
