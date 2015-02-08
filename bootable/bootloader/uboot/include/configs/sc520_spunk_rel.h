

#ifndef _outer_config
#define _outer_config

#include "sc520_spunk.h"

#undef CONFIG_BOOTCOMMAND
#define CONFIG_BOOTCOMMAND	"fsload boot/vmlinuz ; bootm"

#endif
