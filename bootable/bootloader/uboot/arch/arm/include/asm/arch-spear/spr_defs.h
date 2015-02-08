

#ifndef __SPR_DEFS_H__
#define __SPR_DEFS_H__

extern int spear_board_init(ulong);
extern void setfreq(unsigned int, unsigned int);
extern unsigned int setfreq_sz;

struct chip_data {
	int cpufreq;
	int dramfreq;
	int dramtype;
	uchar version[32];
};

/* HW mac id in i2c memory definitions */
#define MAGIC_OFF	0x0
#define MAGIC_LEN	0x2
#define MAGIC_BYTE0	0x55
#define MAGIC_BYTE1	0xAA
#define MAC_OFF		0x2
#define MAC_LEN		0x6

#endif
