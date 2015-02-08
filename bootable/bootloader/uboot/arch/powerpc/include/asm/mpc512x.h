
#ifndef __ASMPPC_MPC512X_H
#define __ASMPPC_MPC512X_H

#define CSAW_START(start)	((start) & 0xFFFF0000)
#define CSAW_STOP(start, size)	(((start) + (size) - 1) >> 16)


static inline void sync_law(volatile void *addr)
{
	in_be32(addr);
	__asm__ __volatile__ ("isync");
}

extern long int fixed_sdram(ddr512x_config_t *mddrc_config,
				u32 *dram_init_seq, int seq_sz);
extern int mpc5121_diu_init(void);
extern void ide_set_reset(int idereset);

#endif /* __ASMPPC_MPC512X_H */
