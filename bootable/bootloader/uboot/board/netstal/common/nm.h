

extern void hcu_led_set(u32 value);
extern u32 get_serial_number(void);
extern u32 hcu_get_slot(void);
extern int board_with_pci(void);
extern void nm_show_print(int generation, int index, int hw_capabilities);
extern void set_params_for_sw_install(int install_requested, char *board_name );
extern void common_misc_init_r(void);

enum {
	/* HW_GENERATION_HCU1/2 is no longer supported */
	HW_GENERATION_HCU3  = 0x10,
	HW_GENERATION_HCU4  = 0x20,
	HW_GENERATION_HCU5  = 0x30,
	HW_GENERATION_MCU   = 0x08,
	HW_GENERATION_MCU20 = 0x0a,
	HW_GENERATION_MCU25 = 0x09,
};

#ifdef CONFIG_405GP
#if defined(DEBUG)
void show_sdram_registers(void);
#endif
long int init_ppc405_sdram(unsigned int dram_size);
#endif
