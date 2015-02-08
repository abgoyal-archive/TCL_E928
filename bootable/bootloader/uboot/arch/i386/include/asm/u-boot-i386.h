

#ifndef _U_BOOT_I386_H_
#define _U_BOOT_I386_H_	1

/* cpu/.../cpu.c */
int cpu_init_r(void);
int cpu_init_f(void);

/* cpu/.../timer.c */
void timer_isr(void *);
typedef void (timer_fnc_t) (void);
int register_timer_isr (timer_fnc_t *isr_func);

/* Architecture specific - can be in arch/i386/cpu/, arch/i386/lib/, or $(BOARD)/ */
int timer_init(void);

/* cpu/.../interrupts.c */
int cpu_init_interrupts(void);

/* board/.../... */
int board_init(void);
int dram_init(void);

void setup_pcat_compatibility(void);

void isa_unmap_rom(u32 addr);
u32 isa_map_rom(u32 bus_addr, int size);

/* arch/i386/lib/... */
int video_bios_init(void);
int video_init(void);


#endif	/* _U_BOOT_I386_H_ */
