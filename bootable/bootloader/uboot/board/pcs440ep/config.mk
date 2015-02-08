ALL += $(obj)u-boot.sha1

#TEXT_BASE = 0x00001000

ifeq ($(ramsym),1)
TEXT_BASE = 0xFBD00000
else
TEXT_BASE = 0xFFFA0000
endif

PLATFORM_CPPFLAGS += -DCONFIG_440=1

ifeq ($(debug),1)
PLATFORM_CPPFLAGS += -DDEBUG
endif

ifeq ($(dbcr),1)
PLATFORM_CPPFLAGS += -DCONFIG_SYS_INIT_DBCR=0x8cff0000
endif
