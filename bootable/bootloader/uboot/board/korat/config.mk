PLATFORM_CPPFLAGS += -DCONFIG_440=1

ifeq ($(debug),1)
PLATFORM_CPPFLAGS += -DDEBUG
endif

ifeq ($(emul),1)
PLATFORM_CPPFLAGS += -fno-schedule-insns -fno-schedule-insns2
endif

ifeq ($(dbcr),1)
PLATFORM_CPPFLAGS += -DCONFIG_SYS_INIT_DBCR=0x8CFF0000
endif

ifeq ($(perm),1)
PLATFORM_CPPFLAGS += -DCONFIG_KORAT_PERMANENT
TEXT_BASE = 0xFFFA0000
else
TEXT_BASE = 0xF7F60000
LDSCRIPT := $(TOPDIR)/board/$(BOARDDIR)/u-boot-F7FC.lds
endif
