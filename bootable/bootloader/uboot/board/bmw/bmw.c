

#include <common.h>
#include <common.h>
#include <watchdog.h>
#include <command.h>
#include <malloc.h>
#include <stdio_dev.h>
#include <net.h>
#include <timestamp.h>
#include <dtt.h>
#include <mpc824x.h>
#include <asm/processor.h>
#include <linux/mtd/doc2000.h>

#include "bmw.h"
#include "m48t59y.h"
#include <pci.h>


int checkboard(void)
{
    ulong busfreq  = get_bus_freq(0);
    char  buf[32];

    puts ("Board: BMW MPC8245/KAHLUA2 - CHRP (MAP B)\n");
    printf("Built: %s at %s\n", U_BOOT_DATE, U_BOOT_TIME);
    /* printf("MPLD:  Revision %d\n", SYS_REVID_GET()); */
    printf("Local Bus at %s MHz\n", strmhz(buf, busfreq));
    return 0;
}

phys_size_t initdram(int board_type)
{
    return 64*1024*1024;
}


void
get_tod(void)
{
    int year, month, day, hour, minute, second;

    m48_tod_get(&year,
		&month,
		&day,
		&hour,
		&minute,
		&second);

    printf("  Current date/time: %d/%d/%d %d:%d:%d \n",
	   month, day, year, hour, minute, second);

}

int misc_init_f (void)
{
#if 0
    m48_tod_init(); /* Init SGS M48T59Y TOD/NVRAM */
    printf("RTC:   M48T589 TOD/NVRAM (%d) bytes\n",
	   TOD_NVRAM_SIZE);
    get_tod();
#endif

    sys_led_msg("BOOT");
    return 0;
}


struct pci_controller hose;

void pci_init_board (void)
{
    pci_mpc824x_init(&hose);
    /* pci_dev_init(0); */
}

void
sys_led_msg(char* msg)
{
    LED_REG(0) = msg[3];
    LED_REG(1) = msg[2];
    LED_REG(2) = msg[1];
    LED_REG(3) = msg[0];
}

#ifdef CONFIG_CMD_DOC
void doc_init (void)
{
    doc_probe(DOC_BASE_ADDR);
}
#endif

#define NV_ADDR	((volatile unsigned char *) CONFIG_ENV_ADDR)

/* Read from NVRAM */
void*
nvram_read(void *dest, const long src, size_t count)
{
    int i;
    volatile unsigned char* d = (unsigned char*)dest;
    volatile unsigned char* s = (unsigned char*)src;

    for( i = 0; i < count;i++)
	d[i] = s[i];

    return dest;
}

/* Write to NVRAM */
void
nvram_write(long dest, const void *src, size_t count)
{
    int i;
    volatile unsigned char* d = (unsigned char*)dest;
    volatile unsigned char* s = (unsigned char*)src;

    SYS_TOD_UNPROTECT();

    for( i = 0; i < count;i++)
	d[i] = s[i];

    SYS_TOD_PROTECT();
}
