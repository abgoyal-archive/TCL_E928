
#ifndef __INCdramsetuph
#define __INCdramsetuph
#ifndef __ASSEMBLY__
/* Where various things are in the SPD */
#define LOC_TYPE                    2
#define LOC_CHECKSUM                63
#define LOC_PHYS_BANKS              5
#define LOC_LOGICAL_BANKS           17
#define LOC_ROWS                    3
#define LOC_COLS                    4
#define LOC_WIDTH_HIGH              7
#define LOC_WIDTH_LOW               6
#define LOC_REFRESH                 12
#define LOC_BURSTS                  16
#define LOC_CAS                     18
#define LOC_CS                      19
#define LOC_WE                      20
#define LOC_Tcyc                    9
#define LOC_Tac                     10
#define LOC_Trp                     27
#define LOC_Trrd                    28
#define LOC_Trcd                    29
#define LOC_Tras                    30
#define LOC_Buffered                21
#define TYPE_DRAM                   1	/* plain old dram */
#define TYPE_EDO                    2	/* EDO dram */
#define TYPE_Nibble                 3	/* serial nibble memory */
#define TYPE_SDR                    4	/* SDRAM */
#define TYPE_ROM                    5	/*  */
#define TYPE_SGRRAM                 6	/* graphics memory */
#define TYPE_DDR                    7	/* DDR sdram */
#define SDRAMDS_MASK        0x3	/* each field is 2 bits wide */
#define SDRAMDS_SBE_SHIFT     8	/* Clock enable drive strength */
#define SDRAMDS_SBC_SHIFT     6	/* Clocks drive strength */
#define SDRAMDS_SBA_SHIFT     4	/* Address drive strength */
#define SDRAMDS_SBS_SHIFT     2	/* SDR DQS drive strength */
#define SDRAMDS_SBD_SHIFT     0	/* Data and DQS drive strength */
#define  DRIVE_STRENGTH_HIGH 0
#define  DRIVE_STRENGTH_MED  1
#define  DRIVE_STRENGTH_LOW  2
#define  DRIVE_STRENGTH_OFF  3

#define OK      0
#define ERROR   -1
/* Structure to hold information about address muxing. */
	typedef struct tagMuxDescriptor {
	u8 MuxValue;
	u8 Columns;
	u8 Rows;
	u8 MoreColumns;
} muxdesc_t;

typedef struct tagDramInfo {
	u32 size;		/* size in bytes */
	u32 base;		/* base address */
	u8 ordinal;		/* where in the memory map will we put this */
	u8 type;
	u8 rows;
	u8 cols;
	u16 width;		/* width of each chip in bits */
	u8 banks;		/* number of chips, aka logical banks */
	u8 bursts;		/* bit-encoded allowable burst length */
	u8 CAS;			/* bit-encoded CAS latency values */
	u8 CS;			/* bit-encoded CS latency values */
	u8 WE;			/* bit-encoded WE latency values */
	u8 Trp;			/* bit-encoded row precharge time */
	u8 Trcd;		/* bit-encoded RAS to CAS delay */
	u8 buffered;		/* buffered or not */
	u8 refresh;		/* encoded refresh rate */
} draminfo_t;

#endif /* __ASSEMBLY__ */

#endif /* __INCdramsetuph */
