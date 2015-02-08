

#ifndef __ADDERUSB__
#define __ADDERUSB__

/* Include the board port */
#include "Adder.h"

#define CONFIG_USB_DEVICE		/* Include UDC driver */
#define CONFIG_USB_TTY			/* Bind the TTY driver to UDC */
#define CONFIG_SYS_USB_EXTC_CLK 0x02		/* Oscillator on EXTC_CLK 2 */
#define CONFIG_SYS_USB_BRG_CLK	0x04		/* or use Baud rate generator 0x04 */
#define CONFIG_SYS_CONSOLE_IS_IN_ENV		/* Console is in env */



#endif /* __ADDERUSB_H__ */
