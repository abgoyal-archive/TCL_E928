

#include <fpga.h>

#ifndef _XILINX_H_
#define _XILINX_H_

#define CONFIG_SYS_SPARTAN2			CONFIG_SYS_FPGA_DEV( 0x1 )
#define CONFIG_SYS_VIRTEX_E			CONFIG_SYS_FPGA_DEV( 0x2 )
#define CONFIG_SYS_VIRTEX2			CONFIG_SYS_FPGA_DEV( 0x4 )
#define CONFIG_SYS_SPARTAN3			CONFIG_SYS_FPGA_DEV( 0x8 )
#define CONFIG_SYS_XILINX_SPARTAN2	(CONFIG_SYS_FPGA_XILINX | CONFIG_SYS_SPARTAN2)
#define CONFIG_SYS_XILINX_VIRTEX_E	(CONFIG_SYS_FPGA_XILINX | CONFIG_SYS_VIRTEX_E)
#define CONFIG_SYS_XILINX_VIRTEX2	(CONFIG_SYS_FPGA_XILINX | CONFIG_SYS_VIRTEX2)
#define CONFIG_SYS_XILINX_SPARTAN3	(CONFIG_SYS_FPGA_XILINX | CONFIG_SYS_SPARTAN3)
/* XXX - Add new models here */


#define CONFIG_SYS_XILINX_IF_SS	CONFIG_SYS_FPGA_IF( 0x1 )	/* slave serial		*/
#define CONFIG_SYS_XILINX_IF_MS	CONFIG_SYS_FPGA_IF( 0x2 )	/* master serial	*/
#define CONFIG_SYS_XILINX_IF_SP	CONFIG_SYS_FPGA_IF( 0x4 )	/* slave parallel	*/
#define CONFIG_SYS_XILINX_IF_JTAG	CONFIG_SYS_FPGA_IF( 0x8 )	/* jtag			*/
#define CONFIG_SYS_XILINX_IF_MSM	CONFIG_SYS_FPGA_IF( 0x10 )	/* master selectmap	*/
#define CONFIG_SYS_XILINX_IF_SSM	CONFIG_SYS_FPGA_IF( 0x20 )	/* slave selectmap	*/

typedef enum {			/* typedef Xilinx_iface */
	min_xilinx_iface_type,	/* low range check value */
	slave_serial,		/* serial data and external clock */
	master_serial,		/* serial data w/ internal clock (not used) */
	slave_parallel,		/* parallel data w/ external latch */
	jtag_mode,		/* jtag/tap serial (not used ) */
	master_selectmap,	/* master SelectMap (virtex2)           */
	slave_selectmap,	/* slave SelectMap (virtex2)            */
	max_xilinx_iface_type	/* insert all new types before this */
} Xilinx_iface;			/* end, typedef Xilinx_iface */

typedef enum {			/* typedef Xilinx_Family */
	min_xilinx_type,	/* low range check value */
	Xilinx_Spartan2,	/* Spartan-II Family */
	Xilinx_VirtexE,		/* Virtex-E Family */
	Xilinx_Virtex2,		/* Virtex2 Family */
	Xilinx_Spartan3,	/* Spartan-III Family */
	max_xilinx_type		/* insert all new types before this */
} Xilinx_Family;		/* end, typedef Xilinx_Family */

typedef struct {		/* typedef Xilinx_desc */
	Xilinx_Family family;	/* part type */
	Xilinx_iface iface;	/* interface type */
	size_t size;		/* bytes of data part can accept */
	void *iface_fns;	/* interface function table */
	int cookie;		/* implementation specific cookie */
} Xilinx_desc;			/* end, typedef Xilinx_desc */

extern int xilinx_load( Xilinx_desc *desc, void *image, size_t size );
extern int xilinx_dump( Xilinx_desc *desc, void *buf, size_t bsize );
extern int xilinx_info( Xilinx_desc *desc );

typedef int (*Xilinx_pgm_fn)( int assert_pgm, int flush, int cookie );
typedef int (*Xilinx_init_fn)( int cookie );
typedef int (*Xilinx_err_fn)( int cookie );
typedef int (*Xilinx_done_fn)( int cookie );
typedef int (*Xilinx_clk_fn)( int assert_clk, int flush, int cookie );
typedef int (*Xilinx_cs_fn)( int assert_cs, int flush, int cookie );
typedef int (*Xilinx_wr_fn)( int assert_write, int flush, int cookie );
typedef int (*Xilinx_rdata_fn)( unsigned char *data, int cookie );
typedef int (*Xilinx_wdata_fn)( unsigned char data, int flush, int cookie );
typedef int (*Xilinx_busy_fn)( int cookie );
typedef int (*Xilinx_abort_fn)( int cookie );
typedef int (*Xilinx_pre_fn)( int cookie );
typedef int (*Xilinx_post_fn)( int cookie );
typedef int (*Xilinx_bwr_fn)( void *buf, size_t len, int flush, int cookie );

#endif  /* _XILINX_H_ */
