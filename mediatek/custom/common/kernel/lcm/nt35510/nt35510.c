

#include <linux/string.h>

#ifndef BUILD_UBOOT
#include <mach/mt6575_gpio.h>
#endif

#include "lcm_drv.h"

// ---------------------------------------------------------------------------
//  Local Constants
// ---------------------------------------------------------------------------

#define FRAME_WIDTH  										(480)
#define FRAME_HEIGHT 										(800)
//#define LCM_ID       (0x55)
#define LCM_ID       (0x01)
#define REGFLAG_DELAY             							0XFE
#define REGFLAG_END_OF_TABLE      							0xFF   // END OF REGISTERS MARKER


#ifndef TRUE
    #define TRUE 1
#endif

#ifndef FALSE
    #define FALSE 0
#endif

static unsigned int lcm_esd_test = FALSE;      ///only for ESD test
#define LCM_DSI_CMD_MODE									1

// ---------------------------------------------------------------------------
//  Local Variables
// ---------------------------------------------------------------------------

static LCM_UTIL_FUNCS lcm_util = {0};

#define SET_RESET_PIN(v)    								(lcm_util.set_reset_pin((v)))

#define UDELAY(n) 											(lcm_util.udelay(n))
#define MDELAY(n) 											(lcm_util.mdelay(n))


// ---------------------------------------------------------------------------
//  Local Functions
// ---------------------------------------------------------------------------

#define dsi_set_cmdq_V2(cmd, count, ppara, force_update)	        lcm_util.dsi_set_cmdq_V2(cmd, count, ppara, force_update)
#define dsi_set_cmdq(pdata, queue_size, force_update)		lcm_util.dsi_set_cmdq(pdata, queue_size, force_update)
#define wrtie_cmd(cmd)										lcm_util.dsi_write_cmd(cmd)
#define write_regs(addr, pdata, byte_nums)					lcm_util.dsi_write_regs(addr, pdata, byte_nums)
#define read_reg(cmd)											lcm_util.dsi_dcs_read_lcm_reg(cmd)
#define read_reg_v2(cmd, buffer, buffer_size)   				lcm_util.dsi_dcs_read_lcm_reg_v2(cmd, buffer, buffer_size)

struct LCM_setting_table {
    unsigned char cmd;
    unsigned char count;
    unsigned char para_list[64];
};


static struct LCM_setting_table lcm_initialization_setting[] = {

	/*
	Note :

	Data ID will depends on the following rule.

		count of parameters > 1	=> Data ID = 0x39
		count of parameters = 1	=> Data ID = 0x15
		count of parameters = 0	=> Data ID = 0x05

	Structure Format :

	{DCS command, count of parameters, {parameter list}}
	{REGFLAG_DELAY, milliseconds of time, {}},

	...

	Setting ending by predefined flag

	{REGFLAG_END_OF_TABLE, 0x00, {}}
	*/

	{0xF0,	5,	{0x55, 0xaa, 0x52,0x08,0x01}},
	{REGFLAG_DELAY, 10, {}},

	{0xBc,	3,	{0x00, 0x78, 0x1a}},
	{REGFLAG_DELAY, 10, {}},

	{0xBd,	3,	{0x00, 0x78,0x1a}},
	{REGFLAG_DELAY, 10, {}},

	{0xBe,	2,	{0x00, 0x4e}},
	{REGFLAG_DELAY, 10, {}},

	{0xD1,	52, {0x00, 0x00, 0x00, 0x13,
				 0x00, 0x27, 0x00, 0x46,
				 0x00, 0x6a, 0x00, 0xa4,
				 0x00, 0xd5, 0x01, 0x1e,
				 0x01, 0x53, 0x01, 0x9b,
				 0x01, 0xcb, 0x02, 0x16,
				 0x02, 0x4e, 0x02, 0x4f,
				 0x02, 0x7f, 0x02, 0xb3,
				 0x02, 0xcf, 0x02, 0xee,
				 0x03, 0x01, 0x03, 0x1b,
				 0x03, 0x2a, 0x03, 0x40,
				 0x03, 0x50, 0x03, 0x67,
				 0x03, 0xa8, 0x03, 0xd8}},
	{REGFLAG_DELAY, 10, {}},

	{0xD2,	52, {0x00, 0x00, 0x00, 0x13,
				 0x00, 0x27, 0x00, 0x46,
				 0x00, 0x6a, 0x00, 0xa4,
				 0x00, 0xd5, 0x01, 0x1e,
				 0x01, 0x53, 0x01, 0x9b,
				 0x01, 0xcb, 0x02, 0x16,
				 0x02, 0x4e, 0x02, 0x4f,
				 0x02, 0x7f, 0x02, 0xb3,
				 0x02, 0xcf, 0x02, 0xee,
				 0x03, 0x01, 0x03, 0x1b,
				 0x03, 0x2a, 0x03, 0x40,
				 0x03, 0x50, 0x03, 0x67,
				 0x03, 0xa8, 0x03, 0xd8}},
	{REGFLAG_DELAY, 10, {}},

	{0xD3,	52, {0x00, 0x00, 0x00, 0x13,
				 0x00, 0x27, 0x00, 0x46,
				 0x00, 0x6a, 0x00, 0xa4,
				 0x00, 0xd5, 0x01, 0x1e,
				 0x01, 0x53, 0x01, 0x9b,
				 0x01, 0xcb, 0x02, 0x16,
				 0x02, 0x4e, 0x02, 0x4f,
				 0x02, 0x7f, 0x02, 0xb3,
				 0x02, 0xcf, 0x02, 0xee,
				 0x03, 0x01, 0x03, 0x1b,
				 0x03, 0x2a, 0x03, 0x40,
				 0x03, 0x50, 0x03, 0x67,
				 0x03, 0xa8, 0x03, 0xd8}},
	{REGFLAG_DELAY, 10, {}},

	{0xD4,	52, {0x00, 0x00, 0x00, 0x13,
				 0x00, 0x27, 0x00, 0x46,
				 0x00, 0x6a, 0x00, 0xa4,
				 0x00, 0xd5, 0x01, 0x1e,
				 0x01, 0x53, 0x01, 0x9b,
				 0x01, 0xcb, 0x02, 0x16,
				 0x02, 0x4e, 0x02, 0x4f,
				 0x02, 0x7f, 0x02, 0xb3,
				 0x02, 0xcf, 0x02, 0xee,
				 0x03, 0x01, 0x03, 0x1b,
				 0x03, 0x2a, 0x03, 0x40,
				 0x03, 0x50, 0x03, 0x67,
				 0x03, 0xa8, 0x03, 0xd8}},
	{REGFLAG_DELAY, 10, {}},

	{0xD5,	52, {0x00, 0x00, 0x00, 0x13,
				 0x00, 0x27, 0x00, 0x46,
				 0x00, 0x6a, 0x00, 0xa4,
				 0x00, 0xd5, 0x01, 0x1e,
				 0x01, 0x53, 0x01, 0x9b,
				 0x01, 0xcb, 0x02, 0x16,
				 0x02, 0x4e, 0x02, 0x4f,
				 0x02, 0x7f, 0x02, 0xb3,
				 0x02, 0xcf, 0x02, 0xee,
				 0x03, 0x01, 0x03, 0x1b,
				 0x03, 0x2a, 0x03, 0x40,
				 0x03, 0x50, 0x03, 0x67,
				 0x03, 0xa8, 0x03, 0xd8}},
	{REGFLAG_DELAY, 10, {}},

	{0xD6,	52, {0x00, 0x00, 0x00, 0x13,
				 0x00, 0x27, 0x00, 0x46,
				 0x00, 0x6a, 0x00, 0xa4,
				 0x00, 0xd5, 0x01, 0x1e,
				 0x01, 0x53, 0x01, 0x9b,
				 0x01, 0xcb, 0x02, 0x16,
				 0x02, 0x4e, 0x02, 0x4f,
				 0x02, 0x7f, 0x02, 0xb3,
				 0x02, 0xcf, 0x02, 0xee,
				 0x03, 0x01, 0x03, 0x1b,
				 0x03, 0x2a, 0x03, 0x40,
				 0x03, 0x50, 0x03, 0x67,
				 0x03, 0xa8, 0x03, 0xd8}},
	{REGFLAG_DELAY, 10, {}},

	{0xB0,	3,	{0x00, 0x00, 0x00}},
	{REGFLAG_DELAY, 10, {}},

	{0xB6,	3,	{0x36, 0x36, 0x36}},
	{REGFLAG_DELAY, 10, {}},

	{0xB8,	3,	{0x26, 0x26, 0x26}},
	{REGFLAG_DELAY, 10, {}},

	{0xB1,	3,	{0x00, 0x00, 0x00}},
	{REGFLAG_DELAY, 10, {}},

	{0xB7,	3,	{0x26, 0x26, 0x26}},
	{REGFLAG_DELAY, 10, {}},

	{0xBa,	3,	{0x16, 0x16, 0x16}},
	{REGFLAG_DELAY, 10, {}},

	{0xB9,	3,	{0x34, 0x34, 0x34}},
	{REGFLAG_DELAY, 10, {}},
//
	{0xf0,	5,	{0x55, 0xaa, 0x52, 0x08, 0x00}},
	{REGFLAG_DELAY, 10, {}},

	{0xB1, 	1,	{0xcc}},
	{REGFLAG_DELAY, 10, {}},

	{0xB4,	1,	{0x10}},

	{0xFF, 	4,	{0xaa,0x55,0x25,0x01}},

	{0xF9, 	11,	{0x14,0x00,0x0d,0x1a,
					0x26,0x33,0x40,0x4d,
					0x5a,0x66,0x73}},

	{0xB6,	1,	{0x07}},

	{0xB7,	2,	{0x71, 0x71}},
	{0xB8,	4,	{0x01, 0x0a, 0x0a,0x0a}},
	{REGFLAG_DELAY, 10, {}},

	{0xBC,	3,	{0x05, 0x05, 0x05}},
	{0xBD,	5,	{0x01, 0x84, 0x07,0x31,0x00}},

	{0xBe,	5,	{0x01, 0x84, 0x07,0x31,0x00}},

	{0xBf,	5,	{0x01, 0x84, 0x07,0x31,0x00}},

	{0x35,	1,	{0x00}},

	{0x3a,	1,	{0x77}},

	{0x29,	1,	{0x00}},
//
	{0xf0,	5,	{0x55, 0xaa, 0x52, 0x08, 0x00}},
	{REGFLAG_DELAY, 10, {}},

	{0xC7,	1,	{0x02}},

	{0xc9,	5,	{0x11, 0x00, 0x00, 0x00, 0x00}},
	{REGFLAG_DELAY, 10, {}},

	{0x21,	1,	{0x00}},

	{0xf0,	5,	{0x55, 0xaa, 0x52, 0x08, 0x01}},
	{REGFLAG_DELAY, 10, {}},

	{0xBe,	2,	{0x00, 0x4c}},

	{0x2c, 1, {0x00}},

	// Note
	// Strongly recommend not to set Sleep out / Display On here. That will cause messed frame to be shown as later the backlight is on.

	{0x53,	1,	{0x24}},
	{REGFLAG_DELAY, 10, {}},

	// Setting ending by predefined flag
	{REGFLAG_END_OF_TABLE, 0x00, {}}
};

#if 0
static struct LCM_setting_table lcm_set_window[] = {
	{0x2A,	4,	{0x00, 0x00, (FRAME_WIDTH>>8), (FRAME_WIDTH&0xFF)}},
	{0x2B,	4,	{0x00, 0x00, (FRAME_HEIGHT>>8), (FRAME_HEIGHT&0xFF)}},
	{REGFLAG_END_OF_TABLE, 0x00, {}}
};
#endif

static struct LCM_setting_table lcm_sleep_out_setting[] = {
    // Sleep Out
	{0x11, 1, {0x00}},
    	{REGFLAG_DELAY, 100, {}},

    // Display ON
	{0x29, 1, {0x00}},
    	{REGFLAG_DELAY, 120, {}},

	//{0x2c, 1, {0x00}},
	{REGFLAG_END_OF_TABLE, 0x00, {}}
};


static struct LCM_setting_table lcm_deep_sleep_mode_in_setting[] = {
	// Display off sequence
	{0x28, 1, {0x00}},
    	{REGFLAG_DELAY, 20, {}},
    // Sleep Mode On
	{0x10, 1, {0x00}},
    	{REGFLAG_DELAY, 120, {}},

	{REGFLAG_END_OF_TABLE, 0x00, {}}
};

static struct LCM_setting_table lcm_compare_id_setting[] = {
	// Display off sequence
	{0xF0,	5,	{0x55, 0xaa, 0x52,0x08,0x01}},
	{REGFLAG_DELAY, 10, {}},

    // Sleep Mode On
//	{0xC3, 1, {0xFF}},

	{REGFLAG_END_OF_TABLE, 0x00, {}}
};

static struct LCM_setting_table lcm_backlight_level_setting[] = {
	{0x51, 1, {0xFF}},
	{REGFLAG_END_OF_TABLE, 0x00, {}}
};


static void push_table(struct LCM_setting_table *table, unsigned int count, unsigned char force_update)
{
	unsigned int i;

    for(i = 0; i < count; i++) {

        unsigned cmd;
        cmd = table[i].cmd;

        switch (cmd) {

            case REGFLAG_DELAY :
                MDELAY(table[i].count);
                break;

            case REGFLAG_END_OF_TABLE :
                break;

            default:
				dsi_set_cmdq_V2(cmd, table[i].count, table[i].para_list, force_update);
       	}
    }

}


// ---------------------------------------------------------------------------
//  LCM Driver Implementations
// ---------------------------------------------------------------------------

static void lcm_set_util_funcs(const LCM_UTIL_FUNCS *util)
{
    memcpy(&lcm_util, util, sizeof(LCM_UTIL_FUNCS));
}


static void lcm_get_params(LCM_PARAMS *params)
{
		memset(params, 0, sizeof(LCM_PARAMS));

		params->type   = LCM_TYPE_DSI;

		params->width  = FRAME_WIDTH;
		params->height = FRAME_HEIGHT;

		// enable tearing-free
		params->dbi.te_mode 				= LCM_DBI_TE_MODE_VSYNC_ONLY;
		params->dbi.te_edge_polarity		= LCM_POLARITY_RISING;

#if (LCM_DSI_CMD_MODE)
		params->dsi.mode   = CMD_MODE;
#else
		params->dsi.mode   = SYNC_PULSE_VDO_MODE;
#endif

		// DSI
		/* Command mode setting */
		params->dsi.LANE_NUM				= LCM_TWO_LANE;
		//The following defined the fomat for data coming from LCD engine.
		params->dsi.data_format.color_order = LCM_COLOR_ORDER_RGB;
		params->dsi.data_format.trans_seq   = LCM_DSI_TRANS_SEQ_MSB_FIRST;
		params->dsi.data_format.padding     = LCM_DSI_PADDING_ON_LSB;
		params->dsi.data_format.format      = LCM_DSI_FORMAT_RGB888;

		// Highly depends on LCD driver capability.
		// Not support in MT6573
		params->dsi.packet_size=256;

		// Video mode setting
		params->dsi.intermediat_buffer_num = 2;

		params->dsi.PS=LCM_PACKED_PS_24BIT_RGB888;
		params->dsi.word_count=480*3;

		params->dsi.vertical_sync_active=2;   ////3
		params->dsi.vertical_backporch=2;  ////12
		params->dsi.vertical_frontporch=2;
		params->dsi.vertical_active_line=800;

		params->dsi.line_byte=2180;		// 2256 = 752*3   2048
		params->dsi.horizontal_sync_active_byte=26;
		params->dsi.horizontal_backporch_byte=206;   ///146
		params->dsi.horizontal_frontporch_byte=206;   ///146
		params->dsi.rgb_byte=(480*3+6);

		params->dsi.horizontal_sync_active_word_count=20;
		params->dsi.horizontal_backporch_word_count=200;  ///140
		params->dsi.horizontal_frontporch_word_count=200;  ///140

		// Bit rate calculation
		params->dsi.pll_div1=34;	//38	// fref=26MHz, fvco=fref*(div1+1)	(div1=0~63, fvco=500MHZ~1GHz)
		params->dsi.pll_div2=1;			// div2=0~15: fout=fvo/(2*div2)

}


static void lcm_init(void)
{
    SET_RESET_PIN(1);
    MDELAY(20);
    SET_RESET_PIN(0);
    MDELAY(20);
    SET_RESET_PIN(1);
    MDELAY(120);

	push_table(lcm_initialization_setting, sizeof(lcm_initialization_setting) / sizeof(struct LCM_setting_table), 1);
}


static void lcm_suspend(void)
{
	push_table(lcm_deep_sleep_mode_in_setting, sizeof(lcm_deep_sleep_mode_in_setting) / sizeof(struct LCM_setting_table), 1);
}


static void lcm_resume(void)
{
	//lcm_init();
	push_table(lcm_sleep_out_setting, sizeof(lcm_sleep_out_setting) / sizeof(struct LCM_setting_table), 1);
}


static void lcm_update(unsigned int x, unsigned int y,
                       unsigned int width, unsigned int height)
{
	unsigned int x0 = x;
	unsigned int y0 = y;
	unsigned int x1 = x0 + width - 1;
	unsigned int y1 = y0 + height - 1;

	unsigned char x0_MSB = ((x0>>8)&0xFF);
	unsigned char x0_LSB = (x0&0xFF);
	unsigned char x1_MSB = ((x1>>8)&0xFF);
	unsigned char x1_LSB = (x1&0xFF);
	unsigned char y0_MSB = ((y0>>8)&0xFF);
	unsigned char y0_LSB = (y0&0xFF);
	unsigned char y1_MSB = ((y1>>8)&0xFF);
	unsigned char y1_LSB = (y1&0xFF);

	unsigned int data_array[16];

	data_array[0]= 0x00053902;
	data_array[1]= (x1_MSB<<24)|(x0_LSB<<16)|(x0_MSB<<8)|0x2a;
	data_array[2]= (x1_LSB);
	data_array[3]= 0x00053902;
	data_array[4]= (y1_MSB<<24)|(y0_LSB<<16)|(y0_MSB<<8)|0x2b;
	data_array[5]= (y1_LSB);
	data_array[6]= 0x002c3909;

	dsi_set_cmdq(data_array, 7, 0);

}


static void lcm_setbacklight(unsigned int level)
{
#if 0
	//unsigned int default_level = 145;
	unsigned int mapped_level = 0;

	//for LGE backlight IC mapping table
	if(level > 255)
			level = 255;

	if(level >0)
			//mapped_level = default_level+(level)*(255-default_level)/(255);
			mapped_level = level;
	else
			mapped_level=0;

	// Refresh value of backlight level.
	lcm_backlight_level_setting[0].para_list[0] = mapped_level;

	push_table(lcm_backlight_level_setting, sizeof(lcm_backlight_level_setting) / sizeof(struct LCM_setting_table), 1);
#endif

	unsigned int data_array[16];

	//for LGE backlight IC mapping table
	if(level > 255)
			level = 255;
	if(level >0 && level <30)
			level =30;

	data_array[0]= 0x00023902;
	data_array[1] =(0x51|(level<<8));
	dsi_set_cmdq(&data_array, 2, 1);

}

static unsigned int lcm_esd_check(void)
{
#ifndef BUILD_UBOOT
	unsigned char buffer[2];
	unsigned int array[16];
        if(lcm_esd_test)
        {
            lcm_esd_test = FALSE;
            return TRUE;
        }

        /// please notice: the max return packet size is 1
        /// if you want to change it, you can refer to the following marked code
        /// but read_reg currently only support read no more than 4 bytes....
        /// if you need to read more, please let BinHan knows.
        /*
                unsigned int data_array[16];
                unsigned int max_return_size = 1;

                data_array[0]= 0x00003700 | (max_return_size << 16);

                dsi_set_cmdq(&data_array, 1, 1);
        */
	push_table(lcm_compare_id_setting, sizeof(lcm_compare_id_setting) / sizeof(struct LCM_setting_table), 1);

	array[0] = 0x00023700;// read id return two byte,version and id
	dsi_set_cmdq(array, 1, 1);
	read_reg_v2(0xbe,buffer, 2);

        	printk("[%s],  vcom is %x,%x-----------------------------------------\n",__func__, buffer[0], buffer[1]);

        if(buffer[1] == 0x4c)  //4c
        {
            return FALSE;
        }
        else
        {
            return TRUE;
        }
#endif
}

static unsigned int lcm_esd_recover(void)
{
    unsigned char para = 0;

    SET_RESET_PIN(1);
    SET_RESET_PIN(0);
    MDELAY(1);
    SET_RESET_PIN(1);
    MDELAY(50);

	  push_table(lcm_initialization_setting, sizeof(lcm_initialization_setting) / sizeof(struct LCM_setting_table), 1);
    MDELAY(10);
	  push_table(lcm_sleep_out_setting, sizeof(lcm_sleep_out_setting) / sizeof(struct LCM_setting_table), 1);
    MDELAY(10);
    //dsi_set_cmdq_V2(0x35, 1, &para, 1);     ///enable TE
    //MDELAY(10);
    lcm_setbacklight(200);
    return TRUE;
}

static unsigned int lcm_compare_id(void)
{

	unsigned int id=0;

   	mt_set_gpio_mode(50,0);  // gpio mode   high
	mt_set_gpio_pull_enable(50,0);
	mt_set_gpio_dir(50,0);  //input

	mt_set_gpio_mode(47,0);  // gpio mode   low
	mt_set_gpio_pull_enable(47,0);
	mt_set_gpio_dir(47,0);

	id = (mt_get_gpio_in(50) <<4) | mt_get_gpio_in(47);

#if defined(BUILD_UBOOT)
	printf("%s, id1 = 0x%08x\n", __func__, id);
#endif
         return (LCM_ID == id)?1:0;
}
// ---------------------------------------------------------------------------
//  Get LCM Driver Hooks
// ---------------------------------------------------------------------------
LCM_DRIVER nt35510_lcm_drv =
{
    .name			= "nt35510",
	.set_util_funcs = lcm_set_util_funcs,
	.get_params     = lcm_get_params,
	.init           = lcm_init,
	.suspend        = lcm_suspend,
	.resume         = lcm_resume,
#if (LCM_DSI_CMD_MODE)
	.update         = lcm_update,
	.set_backlight	= lcm_setbacklight,
//	.set_pwm        = lcm_setpwm,
//	.get_pwm        = lcm_getpwm,
	.esd_check   = lcm_esd_check,
   	.esd_recover   = lcm_esd_recover,
	.compare_id    = lcm_compare_id,
#endif
};


