

#include <common.h>
#include <asm/arch/s3c6400.h>

int usb_cpu_init(void)
{
	OTHERS_REG |= 0x10000;
	return 0;
}

int usb_cpu_stop(void)
{
	OTHERS_REG &= ~0x10000;
	return 0;
}

void usb_cpu_init_fail(void)
{
	OTHERS_REG &= ~0x10000;
}
