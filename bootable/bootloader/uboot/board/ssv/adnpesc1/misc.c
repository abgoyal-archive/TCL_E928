

#include <common.h>

#if	defined(CONFIG_STATUS_LED)
#include "../common/cmd_sled.c"
#endif

#if	defined(CONFIG_HW_WATCHDOG)
#include "../common/wd_pio.c"
#endif

#if	defined(CONFIG_POST) || defined(CONFIG_LOGBUFFER)
#include "../common/post.c"
#endif
