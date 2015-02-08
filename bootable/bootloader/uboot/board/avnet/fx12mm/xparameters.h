

#ifndef __XPARAMETER_H__
#define __XPARAMETER_H__

/* RS232 */
#define XPAR_UARTNS550_0_CLOCK_FREQ_HZ 100000000
#define XPAR_UARTNS550_0_BASEADDR 0x83E00000


/* INT_C */
#define XPAR_XPS_INTC_0_DEVICE_ID 0
#define XPAR_XPS_INTC_0_BASEADDR 0x81800000
#define XPAR_INTC_MAX_NUM_INTR_INPUTS 2

/* CPU core clock */
#define XPAR_CORE_CLOCK_FREQ_HZ 300000000
#define XPAR_PLB_CLOCK_FREQ_HZ  100000000

/* RAM */
#define XPAR_DDR2_SDRAM_MEM_BASEADDR 0x00000000

/* FLASH */
#define XPAR_FLASH_MEM0_BASEADDR 0xFFC00000

#endif