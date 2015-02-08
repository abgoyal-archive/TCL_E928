


#include <common.h>
#include <mpc8260.h>
#include <common.h>
#include "../common/fpga.h"

fpga_t fpga_list[] = {
	{"FIOX", CONFIG_SYS_FIOX_BASE,
	 CONFIG_SYS_PD_FIOX_INIT, CONFIG_SYS_PD_FIOX_PROG, CONFIG_SYS_PD_FIOX_DONE}
	,
	{"FDOHM", CONFIG_SYS_FDOHM_BASE,
	 CONFIG_SYS_PD_FDOHM_INIT, CONFIG_SYS_PD_FDOHM_PROG, CONFIG_SYS_PD_FDOHM_DONE}
};
int fpga_count = sizeof (fpga_list) / sizeof (fpga_t);


ulong fpga_control (fpga_t * fpga, int cmd)
{
	volatile immap_t *immr = (immap_t *) CONFIG_SYS_IMMR;

	switch (cmd) {
	case FPGA_INIT_IS_HIGH:
		immr->im_ioport.iop_pdird &= ~fpga->init_mask;	/* input */
		return (immr->im_ioport.iop_pdatd & fpga->init_mask) ? 1 : 0;

	case FPGA_INIT_SET_LOW:
		immr->im_ioport.iop_pdird |= fpga->init_mask;	/* output */
		immr->im_ioport.iop_pdatd &= ~fpga->init_mask;
		break;

	case FPGA_INIT_SET_HIGH:
		immr->im_ioport.iop_pdird |= fpga->init_mask;	/* output */
		immr->im_ioport.iop_pdatd |= fpga->init_mask;
		break;

	case FPGA_PROG_SET_LOW:
		immr->im_ioport.iop_pdatd &= ~fpga->prog_mask;
		break;

	case FPGA_PROG_SET_HIGH:
		immr->im_ioport.iop_pdatd |= fpga->prog_mask;
		break;

	case FPGA_DONE_IS_HIGH:
		return (immr->im_ioport.iop_pdatd & fpga->done_mask) ? 1 : 0;

	case FPGA_READ_MODE:
		break;

	case FPGA_LOAD_MODE:
		break;

	case FPGA_GET_ID:
		if (fpga->conf_base == CONFIG_SYS_FIOX_BASE) {
			ulong ver =
				*(volatile ulong *) (fpga->conf_base + 0x10);
			return ((ver >> 10) & 0xf) + ((ver >> 2) & 0xf0);
		} else if (fpga->conf_base == CONFIG_SYS_FDOHM_BASE) {
			return (*(volatile ushort *) fpga->conf_base) & 0xff;
		} else {
			return *(volatile ulong *) fpga->conf_base;
		}

	case FPGA_INIT_PORTS:
		immr->im_ioport.iop_ppard &= ~fpga->init_mask;	/* INIT I/O */
		immr->im_ioport.iop_psord &= ~fpga->init_mask;
		immr->im_ioport.iop_pdird &= ~fpga->init_mask;

		immr->im_ioport.iop_ppard &= ~fpga->prog_mask;	/* PROG Output */
		immr->im_ioport.iop_psord &= ~fpga->prog_mask;
		immr->im_ioport.iop_pdird |= fpga->prog_mask;

		immr->im_ioport.iop_ppard &= ~fpga->done_mask;	/* DONE Input */
		immr->im_ioport.iop_psord &= ~fpga->done_mask;
		immr->im_ioport.iop_pdird &= ~fpga->done_mask;

		break;

	}
	return 0;
}
