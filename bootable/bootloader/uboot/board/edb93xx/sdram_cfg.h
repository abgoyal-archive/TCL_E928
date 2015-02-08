

#include <config.h>
#include <asm/arch/ep93xx.h>

#define SDRAM_BASE_ADDR		PHYS_SDRAM_1

#ifdef CONFIG_EDB93XX_SDCS0
#define SDRAM_DEVCFG_REG	devcfg0
#elif defined(CONFIG_EDB93XX_SDCS3)
#define SDRAM_DEVCFG_REG	devcfg3
#else
#error "SDRAM bank configuration"
#endif

#if defined(CONFIG_EDB9301) || defined(CONFIG_EDB9302) ||	\
	defined(CONFIG_EDB9302A)

#define SDRAM_DEVCFG_VAL (SDRAM_DEVCFG_BANKCOUNT |			\
				SDRAM_DEVCFG_SROMLL |			\
				SDRAM_DEVCFG_CASLAT_2 |			\
				SDRAM_DEVCFG_RASTOCAS_2 |		\
				SDRAM_DEVCFG_EXTBUSWIDTH)

#define SDRAM_MODE_REG_VAL	0x4600

#define SDRAM_BANK_SEL_0	0x00000000 /* A[22:21] = b00 */
#define SDRAM_BANK_SEL_1	0x00200000 /* A[22:21] = b01 */
#define SDRAM_BANK_SEL_2	0x00400000 /* A[22:21] = b10 */
#define SDRAM_BANK_SEL_3	0x00600000 /* A[22:21] = b11 */

#elif defined(CONFIG_EDB9307) || defined(CONFIG_EDB9307A) ||	\
	defined CONFIG_EDB9312 || defined(CONFIG_EDB9315) ||	\
	defined(CONFIG_EDB9315A)

#define SDRAM_DEVCFG_VAL	(SDRAM_DEVCFG_BANKCOUNT |		\
				SDRAM_DEVCFG_SROMLL |			\
				SDRAM_DEVCFG_CASLAT_2 |			\
				SDRAM_DEVCFG_RASTOCAS_2)

#define SDRAM_MODE_REG_VAL	0x8800

#define SDRAM_BANK_SEL_0	0x00000000 /* A[23:22] = b00 */
#define SDRAM_BANK_SEL_1	0x00400000 /* A[23:22] = b01 */
#define SDRAM_BANK_SEL_2	0x00800000 /* A[23:22] = b10 */
#define SDRAM_BANK_SEL_3	0x00c00000 /* A[23:22] = b11 */
#endif
