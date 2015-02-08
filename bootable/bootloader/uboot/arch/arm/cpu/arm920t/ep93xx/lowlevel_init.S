

#include <version.h>
#include <asm/arch/ep93xx.h>

.globl lowlevel_init
lowlevel_init:
	/* backup return address */
	ldr r1, =SYSCON_SCRATCH0
	str lr, [r1]

	/* Turn on both LEDs */
	bl red_LED_on
	bl green_LED_on

	/* Configure flash wait states before we switch to the PLL */
	bl flash_cfg

	/* Set up PLL */
	bl pll_cfg

	/* Turn off the Green LED and leave the Red LED on */
	bl green_LED_off

	/* Setup SDRAM */
	bl sdram_cfg

	/* Turn on Green LED, Turn off the Red LED */
	bl green_LED_on
	bl red_LED_off

	/* FIXME: we use async mode for now */
	mrc p15, 0, r0, c1, c0, 0
	orr r0, r0, #0xc0000000
	mcr p15, 0, r0, c1, c0, 0

	/* restore return address */
	ldr r1, =SYSCON_SCRATCH0
	ldr lr, [r1]

	mov pc, lr
