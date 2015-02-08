
#ifndef _MUSB_OMAP3_H_
#define _MUSB_OMAP3_H_

#include "musb_core.h"

/* Base address of MUSB registers */
#define MENTOR_USB0_BASE (OMAP34XX_CORE_L4_IO_BASE + 0xAB000)

/* Base address of OTG registers */
#define OMAP3_OTG_BASE (MENTOR_USB0_BASE + 0x400)

/* Timeout for USB module */
#define OMAP3_USB_TIMEOUT 0x3FFFFFF

int musb_platform_init(void);

#endif /* _MUSB_OMAP3_H */
