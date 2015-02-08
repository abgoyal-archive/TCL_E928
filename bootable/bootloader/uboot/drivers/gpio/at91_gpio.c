

#include <config.h>
#include <common.h>
#include <asm/sizes.h>
#include <asm/arch/hardware.h>
#include <asm/arch/io.h>
#include <asm/arch/at91_pio.h>

int at91_set_pio_pullup(unsigned port, unsigned pin, int use_pullup)
{
	at91_pio_t	*pio 	= (at91_pio_t *) AT91_PIO_BASE;
	u32		mask;

	if ((port < AT91_PIO_PORTS) && (pin < 32)) {
		mask = 1 << pin;
		if (use_pullup)
			writel(1 << pin, &pio->port[port].puer);
		else
			writel(1 << pin, &pio->port[port].pudr);
		writel(mask, &pio->port[port].per);
	}
	return 0;
}

int at91_set_pio_periph(unsigned port, unsigned pin, int use_pullup)
{
	at91_pio_t	*pio 	= (at91_pio_t *) AT91_PIO_BASE;
	u32		mask;

	if ((port < AT91_PIO_PORTS) && (pin < 32)) {
		mask = 1 << pin;
		writel(mask, &pio->port[port].idr);
		at91_set_pio_pullup(port, pin, use_pullup);
		writel(mask, &pio->port[port].per);
	}
	return 0;
}

int at91_set_a_periph(unsigned port, unsigned pin, int use_pullup)
{
	at91_pio_t	*pio 	= (at91_pio_t *) AT91_PIO_BASE;
	u32		mask;

	if ((port < AT91_PIO_PORTS) && (pin < 32)) {
		mask = 1 << pin;
		writel(mask, &pio->port[port].idr);
		at91_set_pio_pullup(port, pin, use_pullup);
		writel(mask, &pio->port[port].asr);
		writel(mask, &pio->port[port].pdr);
	}
	return 0;
}

int at91_set_b_periph(unsigned port, unsigned pin, int use_pullup)
{
	at91_pio_t	*pio 	= (at91_pio_t *) AT91_PIO_BASE;
	u32		mask;

	if ((port < AT91_PIO_PORTS) && (pin < 32)) {
		mask = 1 << pin;
		writel(mask, &pio->port[port].idr);
		at91_set_pio_pullup(port, pin, use_pullup);
		writel(mask, &pio->port[port].bsr);
		writel(mask, &pio->port[port].pdr);
	}
	return 0;
}

int at91_set_pio_input(unsigned port, u32 pin, int use_pullup)
{
	at91_pio_t	*pio 	= (at91_pio_t *) AT91_PIO_BASE;
	u32		mask;

	if ((port < AT91_PIO_PORTS) && (pin < 32)) {
		mask = 1 << pin;
		writel(mask, &pio->port[port].idr);
		at91_set_pio_pullup(port, pin, use_pullup);
		writel(mask, &pio->port[port].odr);
		writel(mask, &pio->port[port].per);
	}
	return 0;
}

int at91_set_pio_output(unsigned port, u32 pin, int value)
{
	at91_pio_t	*pio 	= (at91_pio_t *) AT91_PIO_BASE;
	u32		mask;

	if ((port < AT91_PIO_PORTS) && (pin < 32)) {
		mask = 1 << pin;
		writel(mask, &pio->port[port].idr);
		writel(mask, &pio->port[port].pudr);
		if (value)
			writel(mask, &pio->port[port].sodr);
		else
			writel(mask, &pio->port[port].codr);
		writel(mask, &pio->port[port].oer);
		writel(mask, &pio->port[port].per);
	}
	return 0;
}

int at91_set_pio_deglitch(unsigned port, unsigned pin, int is_on)
{
	at91_pio_t	*pio 	= (at91_pio_t *) AT91_PIO_BASE;
	u32		mask;

	if ((port < AT91_PIO_PORTS) && (pin < 32)) {
		mask = 1 << pin;
		if (is_on)
			writel(mask, &pio->port[port].ifer);
		else
			writel(mask, &pio->port[port].ifdr);
	}
	return 0;
}

int at91_set_pio_multi_drive(unsigned port, unsigned pin, int is_on)
{
	at91_pio_t	*pio 	= (at91_pio_t *) AT91_PIO_BASE;
	u32		mask;

	if ((port < AT91_PIO_PORTS) && (pin < 32)) {
		mask = 1 << pin;
		if (is_on)
			writel(mask, &pio->port[port].mder);
		else
			writel(mask, &pio->port[port].mddr);
	}
	return 0;
}

int at91_set_pio_value(unsigned port, unsigned pin, int value)
{
	at91_pio_t	*pio 	= (at91_pio_t *) AT91_PIO_BASE;
	u32		mask;

	if ((port < AT91_PIO_PORTS) && (pin < 32)) {
		mask = 1 << pin;
		if (value)
			writel(mask, &pio->port[port].sodr);
		else
			writel(mask, &pio->port[port].codr);
	}
	return 0;
}

int at91_get_pio_value(unsigned port, unsigned pin)
{
	u32		pdsr	= 0;
	at91_pio_t	*pio 	= (at91_pio_t *) AT91_PIO_BASE;
	u32		mask;

	if ((port < AT91_PIO_PORTS) && (pin < 32)) {
		mask = 1 << pin;
		pdsr = readl(&pio->port[port].pdsr) & mask;
	}
	return pdsr != 0;
}
