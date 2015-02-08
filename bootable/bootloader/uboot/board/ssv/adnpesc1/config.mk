TEXT_BASE = 0x02fc0000	# ATTENTION: notice your CONFIG_SYS_MONITOR_LEN setting

ifeq ($(debug),1)
PLATFORM_CPPFLAGS += -DDEBUG
endif
