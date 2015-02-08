

#ifndef _SPR_XLOADER_TABLE_H
#define _SPR_XLOADER_TABLE_H

#define XLOADER_TABLE_VERSION_1_1	2
#define XLOADER_TABLE_VERSION_1_2	3

#define XLOADER_TABLE_ADDRESS		0xD2801FF0

#define DDRMOBILE	1
#define DDR2		2

#define REV_BA		1
#define REV_AA		2
#define REV_AB		3

struct xloader_table_1_1 {
	unsigned short ddrfreq;
	unsigned char ddrsize;
	unsigned char ddrtype;

	unsigned char soc_rev;
} __attribute__ ((packed));

struct xloader_table_1_2 {
	unsigned const char *version;

	unsigned short ddrfreq;
	unsigned char ddrsize;
	unsigned char ddrtype;

	unsigned char soc_rev;
} __attribute__ ((packed));

union table_contents {
	struct xloader_table_1_1 table_1_1;
	struct xloader_table_1_2 table_1_2;
};

struct xloader_table {
	unsigned char table_version;
	union table_contents table;
} __attribute__ ((packed));

#endif
