#include <cust_cmmb.h>
#include <mach/mt6575_gpio.h>
#include <cust_gpio_usage.h>
#include <mach/eint.h>
#include <cust_eint.h>
#include <mach/mt6575_pm_ldo.h>	
#include <linux/module.h>

#define inno_msg(fmt, arg...)	printk(KERN_ERR "[cmmb-drv]%s: " fmt "\n", __func__, ##arg)
void cust_cmmb_power_on(void)
{
	mt_set_gpio_mode(GPIO_CMMB_LDO_EN_PIN, GPIO_CMMB_LDO_EN_PIN_M_GPIO);
	mt_set_gpio_dir(GPIO_CMMB_LDO_EN_PIN, GPIO_DIR_OUT);
	mt_set_gpio_out(GPIO_CMMB_LDO_EN_PIN, GPIO_OUT_ONE);  
//	mt_set_gpio_pull_enable(GPIO_CMMB_LDO_EN_PIN, 1);                              // no need to pull, beause BB output power is enough
//	mt_set_gpio_pull_select(GPIO_CMMB_LDO_EN_PIN,  1);
	inno_msg("CMMB GPIO LDO PIN mode:num:%d, %d,out:%d, dir:%d,pullen:%d,pullup%d",GPIO_CMMB_LDO_EN_PIN,mt_get_gpio_mode(GPIO_CMMB_LDO_EN_PIN),mt_get_gpio_out(GPIO_CMMB_LDO_EN_PIN),
			mt_get_gpio_dir(GPIO_CMMB_LDO_EN_PIN),mt_get_gpio_pull_enable(GPIO_CMMB_LDO_EN_PIN),mt_get_gpio_pull_select(GPIO_CMMB_LDO_EN_PIN));    

}
EXPORT_SYMBOL(cust_cmmb_power_on);

void cust_cmmb_power_off(void)
{
	mt_set_gpio_mode(GPIO_CMMB_LDO_EN_PIN, GPIO_CMMB_LDO_EN_PIN_M_GPIO);
	mt_set_gpio_out(GPIO_CMMB_LDO_EN_PIN, GPIO_OUT_ZERO);  
	mt_set_gpio_dir(GPIO_CMMB_LDO_EN_PIN, GPIO_DIR_IN);
	inno_msg("CMMB GPIO LDO PIN mode:num:%d, %d,out:%d, dir:%d,pullen:%d,pullup%d",GPIO_CMMB_LDO_EN_PIN,mt_get_gpio_mode(GPIO_CMMB_LDO_EN_PIN),mt_get_gpio_out(GPIO_CMMB_LDO_EN_PIN),mt_get_gpio_dir(GPIO_CMMB_LDO_EN_PIN),mt_get_gpio_pull_enable(GPIO_CMMB_LDO_EN_PIN),mt_get_gpio_pull_select(GPIO_CMMB_LDO_EN_PIN));    

	mt_set_gpio_mode(GPIO_CMMB_RST_PIN, GPIO_CMMB_RST_PIN_M_GPIO);
	mt_set_gpio_out(GPIO_CMMB_RST_PIN, GPIO_OUT_ZERO); 			 
	mt_set_gpio_dir(GPIO_CMMB_RST_PIN, GPIO_DIR_IN);
	inno_msg("CMMB GPIO RST PIN mode:num:%d, %d,out:%d, dir:%d,pullen:%d,pullup%d",GPIO_CMMB_RST_PIN,mt_get_gpio_mode(GPIO_CMMB_RST_PIN),mt_get_gpio_out(GPIO_CMMB_RST_PIN),mt_get_gpio_dir(GPIO_CMMB_RST_PIN),mt_get_gpio_pull_enable(GPIO_CMMB_RST_PIN),mt_get_gpio_pull_select(GPIO_CMMB_RST_PIN));    	 
}
EXPORT_SYMBOL(cust_cmmb_power_off);
