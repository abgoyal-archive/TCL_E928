


#ifndef _FPGA_H_
#define _FPGA_H_

#define FPGA_INIT_IS_HIGH   0
#define FPGA_INIT_SET_HIGH  1
#define FPGA_INIT_SET_LOW   2
#define FPGA_PROG_SET_HIGH  3
#define FPGA_PROG_SET_LOW   4
#define FPGA_DONE_IS_HIGH   5
#define	FPGA_READ_MODE      6
#define FPGA_LOAD_MODE      7
#define FPGA_GET_ID         8
#define FPGA_INIT_PORTS     9

#define FPGA_NAME_LEN       8
typedef struct {
    char  name[FPGA_NAME_LEN];
    ulong conf_base;
    uint  init_mask;
    uint  prog_mask;
    uint  done_mask;
} fpga_t;

extern fpga_t fpga_list[];
extern int    fpga_count;

ulong fpga_control (fpga_t* fpga, int cmd);

#endif /* _FPGA_H_ */
