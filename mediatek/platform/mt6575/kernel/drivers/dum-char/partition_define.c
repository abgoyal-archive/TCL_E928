#include <linux/module.h>
#include "partition_define.h"
struct excel_info PartInfo[PART_NUM]={
			{"preloader",262144,0x0, EMMC, 0,BOOT_1},
			{"dsp_bl",1966080,0x40000, EMMC, 0,BOOT_1},
			{"mbr",16384,0x220000, EMMC, 0,USER},
			{"ebr1",376832,0x224000, EMMC, 1,USER},
			{"pmt",4194304,0x280000, EMMC, 0,USER},
			{"nvram",3145728,0x680000, EMMC, 0,USER},
			{"seccfg",131072,0x980000, EMMC, 0,USER},
			{"uboot",393216,0x9a0000, EMMC, 0,USER},
			{"bootimg",6291456,0xa00000, EMMC, 0,USER},
			{"recovery",6291456,0x1000000, EMMC, 0,USER},
			{"sec_ro",6291456,0x1600000, EMMC, 5,USER},
			{"misc",393216,0x1c00000, EMMC, 0,USER},
			{"logo",3145728,0x1c60000, EMMC, 0,USER},
			{"expdb",655360,0x1f60000, EMMC, 0,USER},
			{"ebr2",16384,0x2000000, EMMC, 0,USER},
			{"android",537919488,0x2004000, EMMC, 6,USER},
			{"cache",537919488,0x22104000, EMMC, 2,USER},
			{"usrdata",537919488,0x42204000, EMMC, 3,USER},
			{"fat",0,0x62304000, EMMC, 4,USER},
			{"bmtpool",10485760,0xFFFF0050, EMMC, 0,USER},
 };
EXPORT_SYMBOL(PartInfo);
