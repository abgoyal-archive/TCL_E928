

#include <common.h>
#include <asm/arch/AT91RM9200.h>
#include <asm/io.h>

#define	GREEN_LED	AT91C_PIO_PB0
#define	YELLOW_LED	AT91C_PIO_PB1
#define	RED_LED		AT91C_PIO_PB2

void	green_LED_on(void)
{
	AT91PS_PIO	PIOB	= AT91C_BASE_PIOB;

	writel(GREEN_LED, PIOB->PIO_CODR);
}

void	 yellow_LED_on(void)
{
	AT91PS_PIO	PIOB	= AT91C_BASE_PIOB;

	writel(YELLOW_LED, PIOB->PIO_CODR);
}

void	 red_LED_on(void)
{
	AT91PS_PIO	PIOB	= AT91C_BASE_PIOB;

	writel(RED_LED, PIOB->PIO_CODR);
}

void	green_LED_off(void)
{
	AT91PS_PIO	PIOB	= AT91C_BASE_PIOB;

	writel(GREEN_LED, PIOB->PIO_SODR);
}

void	yellow_LED_off(void)
{
	AT91PS_PIO	PIOB	= AT91C_BASE_PIOB;

	writel(YELLOW_LED, PIOB->PIO_SODR);
}

void	red_LED_off(void)
{
	AT91PS_PIO	PIOB	= AT91C_BASE_PIOB;

	writel(RED_LED, PIOB->PIO_SODR);
}


void coloured_LED_init (void)
{
	AT91PS_PIO	PIOB	= AT91C_BASE_PIOB;
	AT91PS_PMC	PMC	= AT91C_BASE_PMC;

	/* Enable PIOB clock */
	writel((1 << AT91C_ID_PIOB), PMC->PMC_PCER);
	/* Disable peripherals on LEDs */
	writel(AT91C_PIO_PB2 | AT91C_PIO_PB1 | AT91C_PIO_PB0, PIOB->PIO_PER);
	/* Enable pins as outputs */
	writel(AT91C_PIO_PB2 | AT91C_PIO_PB1 | AT91C_PIO_PB0, PIOB->PIO_OER);
	/* Turn all LEDs OFF */
	writel(AT91C_PIO_PB2 | AT91C_PIO_PB1 | AT91C_PIO_PB0, PIOB->PIO_SODR);
}
