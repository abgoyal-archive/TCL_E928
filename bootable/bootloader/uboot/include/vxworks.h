

#ifndef _VXWORKS_H_
#define _VXWORKS_H_

int do_bootvx(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[]);

#ifndef CONFIG_SYS_VXWORKS_BOOT_ADDR
#define CONFIG_SYS_VXWORKS_BOOT_ADDR 0x4200
#endif

#ifndef CONFIG_SYS_VXWORKS_BOOT_DEVICE
#if defined(CONFIG_4xx)
#define		CONFIG_SYS_VXWORKS_BOOT_DEVICE "emac(0,0)"
#elif defined(CONFIG_IOP480)
#define		CONFIG_SYS_VXWORKS_BOOT_DEVICE "dc(0,0)"
#else
#define		CONFIG_SYS_VXWORKS_BOOT_DEVICE "eth(0,0)"
#endif
#endif

#ifndef CONFIG_SYS_VXWORKS_SERVERNAME
#define CONFIG_SYS_VXWORKS_SERVERNAME	"srv"
#endif

#endif
