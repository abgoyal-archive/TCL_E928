TEXT_BASE = 0x01fc0000

PLATFORM_CPPFLAGS += -mno-hw-div -mno-hw-mul
PLATFORM_CPPFLAGS += -I$(TOPDIR)/board/$(VENDOR)/include

ifeq ($(debug),1)
PLATFORM_CPPFLAGS += -DDEBUG
endif
