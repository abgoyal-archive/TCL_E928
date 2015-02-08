

typedef struct {
	ulong ddr;
	ulong mode;
	ulong emode;
	ulong control;
	ulong config1;
	ulong config2;
	ulong tapdelay;
} sdram_conf_t;

long int mpc5xxx_sdram_init (sdram_conf_t *sdram_conf);
