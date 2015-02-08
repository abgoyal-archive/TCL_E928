

#ifndef __CONFIG_H
#define __CONFIG_H

#define CONFIG_SPEAR600				1

#include <configs/spear-common.h>

/* Serial Configuration (PL011) */
#define CONFIG_SYS_SERIAL0			0xD0000000
#define CONFIG_SYS_SERIAL1			0xD0080000
#define CONFIG_PL01x_PORTS			{ (void *)CONFIG_SYS_SERIAL0, \
						(void *)CONFIG_SYS_SERIAL1 }

#define CONFIG_SYS_NAND_BASE			(0xD2000000)

#endif  /* __CONFIG_H */
