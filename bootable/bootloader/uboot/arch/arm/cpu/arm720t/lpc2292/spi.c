

#include <config.h>
#include <common.h>
#include <asm/errno.h>
#include <asm/arch/hardware.h>
#include <asm/arch/spi.h>

unsigned long spi_flags;
unsigned char spi_idle = 0x00;

int spi_init(void)
{
	unsigned long pinsel0_value;

	/* activate spi pins */
	pinsel0_value = GET32(PINSEL0);
	pinsel0_value &= ~(0xFFl << 8);
	pinsel0_value |= (0x55l << 8);
	PUT32(PINSEL0, pinsel0_value);

	return 0;
}
