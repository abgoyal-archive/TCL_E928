

#ifndef __NET_ARM_REGISTERS_H
#define __NET_ARM_REGISTERS_H

#include <config.h>

/* fundamental constants : */
/* the input crystal/clock frequency ( in Hz ) */
#define	NETARM_XTAL_FREQ_25MHz		(18432000)
#define	NETARM_XTAL_FREQ_33MHz		(23698000)
#define	NETARM_XTAL_FREQ_48MHz		(48000000)
#define	NETARM_XTAL_FREQ_55MHz		(55000000)
#define NETARM_XTAL_FREQ_EMLIN1		(20000000)

/* the frequency of SYS_CLK */
#if defined(CONFIG_NETARM_EMLIN)

/* EMLIN board:  33 MHz (exp.) */
#define	NETARM_PLL_COUNT_VAL		6
#define NETARM_XTAL_FREQ		NETARM_XTAL_FREQ_25MHz

#elif defined(CONFIG_NETARM_NET40_REV2)

/* NET+40 Rev2 boards:  33 MHz (with NETARM_XTAL_FREQ_25MHz) */
#define	NETARM_PLL_COUNT_VAL		6
#define	NETARM_XTAL_FREQ		NETARM_XTAL_FREQ_25MHz

#elif defined(CONFIG_NETARM_NET40_REV4)

#define	NETARM_PLL_COUNT_VAL		4
#define	NETARM_XTAL_FREQ		NETARM_XTAL_FREQ_25MHz

#elif defined(CONFIG_NETARM_NET50)

/* NET+50 boards:  40 MHz (with NETARM_XTAL_FREQ_25MHz) */
#define NETARM_PLL_COUNT_VAL		8
#define	NETARM_XTAL_FREQ		NETARM_XTAL_FREQ_25MHz

#else	/* CONFIG_NETARM_NS7520 */

#define	NETARM_PLL_COUNT_VAL		0

#if defined(CONFIG_BOARD_UNC20)
#define	NETARM_XTAL_FREQ		NETARM_XTAL_FREQ_48MHz
#else
#define	NETARM_XTAL_FREQ		NETARM_XTAL_FREQ_55MHz
#endif

#endif

/* #include "arm_registers.h" */
#include <asm/arch/netarm_gen_module.h>
#include <asm/arch/netarm_mem_module.h>
#include <asm/arch/netarm_ser_module.h>
#include <asm/arch/netarm_eni_module.h>
#include <asm/arch/netarm_dma_module.h>
#include <asm/arch/netarm_eth_module.h>

#endif
