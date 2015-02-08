
#include <common.h>
#include <asm/arch/mux.h>

#define write_config_reg(reg, value)                                    \
do {                                                                    \
	writeb(value, reg);                                             \
} while (0)

int board_init(void)
{
	return 0;
}

#ifdef CONFIG_SYS_PRINTF
/* Pin Muxing registers used for UART1 */
static void muxSetupUART1(void)
{
	/* UART1_CTS pin configuration, PIN = D21 */
	write_config_reg(CONTROL_PADCONF_UART1_CTS, 0);
	/* UART1_RTS pin configuration, PIN = H21 */
	write_config_reg(CONTROL_PADCONF_UART1_RTS, 0);
	/* UART1_TX pin configuration, PIN = L20 */
	write_config_reg(CONTROL_PADCONF_UART1_TX, 0);
	/* UART1_RX pin configuration, PIN = T21 */
	write_config_reg(CONTROL_PADCONF_UART1_RX, 0);
}
#endif

int s_init(int skip)
{
#ifdef CONFIG_SYS_PRINTF
	muxSetupUART1();
#endif
	return 0;
}
