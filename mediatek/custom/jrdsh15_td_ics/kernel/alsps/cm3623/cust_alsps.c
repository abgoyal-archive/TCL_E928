#include <linux/types.h>
#include <mach/mt6575_pm_ldo.h>
#include <cust_alsps.h>
//#include <mach/mt6575_pm_ldo.h>
static struct alsps_hw cust_alsps_hw = {
    .i2c_num    = 0,
	.polling_mode_ps =1,
	.polling_mode_als =1,
    .power_id   = MT65XX_POWER_NONE,    /*LDO is not used*/
    .power_vol  = VOL_DEFAULT,          /*LDO is not used*/
    .i2c_addr   = {0x0C, 0x48, 0x78, 0x00},
    .als_level  = { 1,  2,  4,  7,  14,  50,  100,  200,   300,   400,   550,   700,   1000,   2800,   4000},
    .als_value  = {10, 20, 40, 90, 160, 225,  320,  640,  1280,  2600,  3500,  9000,  11000,  20000,  30240, 30240},
    .ps_threshold = 10,	//3,
};
struct alsps_hw *get_cust_alsps_hw(void) {
    return &cust_alsps_hw;
}
