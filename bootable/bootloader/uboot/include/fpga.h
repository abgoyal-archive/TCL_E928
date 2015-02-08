

#include <linux/types.h>	       /* for ulong typedef */

#ifndef _FPGA_H_
#define _FPGA_H_

#ifndef CONFIG_MAX_FPGA_DEVICES
#define CONFIG_MAX_FPGA_DEVICES		5
#endif

/* these probably belong somewhere else */
#ifndef FALSE
#define FALSE			(0)
#endif
#ifndef TRUE
#define TRUE			(!FALSE)
#endif

/* CONFIG_FPGA bit assignments */
#define CONFIG_SYS_FPGA_MAN(x)		(x)
#define CONFIG_SYS_FPGA_DEV(x)		((x) << 8 )
#define CONFIG_SYS_FPGA_IF(x)		((x) << 16 )

/* FPGA Manufacturer bits in CONFIG_FPGA */
#define CONFIG_SYS_FPGA_XILINX		CONFIG_SYS_FPGA_MAN( 0x1 )
#define CONFIG_SYS_FPGA_ALTERA		CONFIG_SYS_FPGA_MAN( 0x2 )


/* fpga_xxxx function return value definitions */
#define FPGA_SUCCESS		0
#define FPGA_FAIL		-1

/* device numbers must be non-negative */
#define FPGA_INVALID_DEVICE	-1

/* root data type defintions */
typedef enum {			/* typedef fpga_type */
	fpga_min_type,		/* range check value */
	fpga_xilinx,		/* Xilinx Family) */
	fpga_altera,		/* unimplemented */
	fpga_undefined		/* invalid range check value */
} fpga_type;			/* end, typedef fpga_type */

typedef struct {		/* typedef fpga_desc */
	fpga_type devtype;	/* switch value to select sub-functions */
	void *devdesc;		/* real device descriptor */
} fpga_desc;			/* end, typedef fpga_desc */


/* root function definitions */
extern void fpga_init( void );
extern int fpga_add( fpga_type devtype, void *desc );
extern int fpga_count( void );
extern int fpga_load( int devnum, void *buf, size_t bsize );
extern int fpga_dump( int devnum, void *buf, size_t bsize );
extern int fpga_info( int devnum );

#endif	/* _FPGA_H_ */
