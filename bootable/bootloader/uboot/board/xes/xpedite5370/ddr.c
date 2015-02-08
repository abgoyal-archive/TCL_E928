

#include <common.h>
#include <i2c.h>

#include <asm/fsl_ddr_sdram.h>
#include <asm/fsl_ddr_dimm_params.h>

static void get_spd(ddr2_spd_eeprom_t *spd, unsigned char i2c_address)
{
	i2c_read(i2c_address, SPD_EEPROM_OFFSET, 2, (uchar *)spd,
		 sizeof(ddr2_spd_eeprom_t));
}

unsigned int fsl_ddr_get_mem_data_rate(void)
{
	return get_ddr_freq(0);
}

void fsl_ddr_get_spd(ddr2_spd_eeprom_t *ctrl_dimms_spd,
		      unsigned int ctrl_num)
{
	unsigned int i;
	unsigned int i2c_address = 0;

	for (i = 0; i < CONFIG_DIMM_SLOTS_PER_CTLR; i++) {
		if (ctrl_num == 0)
			i2c_address = SPD_EEPROM_ADDRESS1;
		if (ctrl_num == 1)
			i2c_address = SPD_EEPROM_ADDRESS2;
		get_spd(&(ctrl_dimms_spd[i]), i2c_address);
	}
}


typedef struct board_memctl_options {
	uint16_t datarate_mhz_low;
	uint16_t datarate_mhz_high;
	uint8_t clk_adjust;
	uint8_t cpo_override;
	uint8_t write_data_delay;
} board_memctl_options_t;

static struct board_memctl_options bopts_ctrl[][2] = {
	{
		/* Controller 0 */
		{
			/* DDR2 600/667 */
			.datarate_mhz_low	= 500,
			.datarate_mhz_high	= 750,
			.clk_adjust		= 5,
			.cpo_override		= 8,
			.write_data_delay	= 2,
		},
		{
			/* DDR2 800 */
			.datarate_mhz_low	= 750,
			.datarate_mhz_high	= 850,
			.clk_adjust		= 5,
			.cpo_override		= 9,
			.write_data_delay	= 2,
		},
	},
	{
		/* Controller 1 */
		{
			/* DDR2 600/667 */
			.datarate_mhz_low	= 500,
			.datarate_mhz_high	= 750,
			.clk_adjust		= 5,
			.cpo_override		= 7,
			.write_data_delay	= 2,
		},
		{
			/* DDR2 800 */
			.datarate_mhz_low	= 750,
			.datarate_mhz_high	= 850,
			.clk_adjust		= 5,
			.cpo_override		= 8,
			.write_data_delay	= 2,
		},
	},
};

void fsl_ddr_board_options(memctl_options_t *popts,
			   dimm_params_t *pdimm,
			   unsigned int ctrl_num)
{
	struct board_memctl_options *bopts = bopts_ctrl[ctrl_num];
	sys_info_t sysinfo;
	int i;
	unsigned int datarate;

	get_sys_info(&sysinfo);
	datarate = sysinfo.freqDDRBus / 1000 / 1000;

	for (i = 0; i < ARRAY_SIZE(bopts_ctrl[ctrl_num]); i++) {
		if ((bopts[i].datarate_mhz_low <= datarate) &&
		    (bopts[i].datarate_mhz_high >= datarate)) {
			debug("controller %d:\n", ctrl_num);
			debug(" clk_adjust = %d\n", bopts[i].clk_adjust);
			debug(" cpo = %d\n", bopts[i].cpo_override);
			debug(" write_data_delay = %d\n",
			      bopts[i].write_data_delay);
			popts->clk_adjust = bopts[i].clk_adjust;
			popts->cpo_override = bopts[i].cpo_override;
			popts->write_data_delay = bopts[i].write_data_delay;
		}
	}

	/*
	 * Factors to consider for half-strength driver enable:
	 *	- number of DIMMs installed
	 */
	popts->half_strength_driver_enable = 0;
}
