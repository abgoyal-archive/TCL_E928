

#include <common.h>
#include <asm/arch/AT91RM9200.h>

#define	GREEN_LED	AT91C_PIO_PB0
#define	YELLOW_LED	AT91C_PIO_PB1
#define	RED_LED	AT91C_PIO_PB2

void	green_LED_on(void)
{
	AT91PS_PIO	PIOB	= AT91C_BASE_PIOB;
	PIOB->PIO_CODR		= GREEN_LED;
}

void	 yellow_LED_on(void)
{
	AT91PS_PIO	PIOB	= AT91C_BASE_PIOB;
	PIOB->PIO_CODR		= YELLOW_LED;
}

void	 red_LED_on(void)
{
	AT91PS_PIO	PIOB	= AT91C_BASE_PIOB;
	PIOB->PIO_CODR		= RED_LED;
}

void	green_LED_off(void)
{
	AT91PS_PIO	PIOB	= AT91C_BASE_PIOB;
	PIOB->PIO_SODR		= GREEN_LED;
}

void	yellow_LED_off(void)
{
	AT91PS_PIO	PIOB	= AT91C_BASE_PIOB;
	PIOB->PIO_SODR		= YELLOW_LED;
}

void	red_LED_off(void)
{
	AT91PS_PIO	PIOB	= AT91C_BASE_PIOB;
	PIOB->PIO_SODR		= RED_LED;
}


void coloured_LED_init (void)
{
	AT91PS_PIO	PIOB	= AT91C_BASE_PIOB;
	AT91PS_PMC	PMC	= AT91C_BASE_PMC;
	PMC->PMC_PCER		= (1 << AT91C_ID_PIOB);	/* Enable PIOB clock */
	/* Disable peripherals on LEDs */
	PIOB->PIO_PER		= AT91C_PIO_PB2 | AT91C_PIO_PB1 | AT91C_PIO_PB0;
	/* Enable pins as outputs */
	PIOB->PIO_OER		= AT91C_PIO_PB2 | AT91C_PIO_PB1 | AT91C_PIO_PB0;
	/* Turn all LEDs OFF */
	PIOB->PIO_SODR		= AT91C_PIO_PB2 | AT91C_PIO_PB1 | AT91C_PIO_PB0;
}
