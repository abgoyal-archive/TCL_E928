


#ifndef __CONFIG_H
#define __CONFIG_H

#define CONFIG_MPC852T		1	/* This is a MPC852T CPU	*/
#define CONFIG_KMSUPX4		1	/* ...on a kmsupx4 board	*/
#define CONFIG_HOSTNAME		kmsupx4

/* include common defines/options for all Keymile 8xx boards */
#include "km8xx.h"

#define CONFIG_SYS_DELAYED_ICACHE	1	/* enable ICache not before
						 * running in RAM.
						 */
#endif	/* __CONFIG_H */
