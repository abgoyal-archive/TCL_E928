
#ifndef __ASM_U_BOOT_H__
#define __ASM_U_BOOT_H__ 1

typedef struct bd_info {
	unsigned long		bi_baudrate;
	unsigned long		bi_ip_addr;
	unsigned char		bi_phy_id[4];
	struct environment_s	*bi_env;
	unsigned long		bi_board_number;
	void			*bi_boot_params;
	struct {
		unsigned long	start;
		unsigned long	size;
	}			bi_dram[CONFIG_NR_DRAM_BANKS];
	unsigned long		bi_flashstart;
	unsigned long		bi_flashsize;
	unsigned long		bi_flashoffset;
} bd_t;

#define bi_memstart bi_dram[0].start
#define bi_memsize bi_dram[0].size

#endif /* __ASM_U_BOOT_H__ */
