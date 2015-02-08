TEXT_BASE = 0x40000000

PLATFORM_CPPFLAGS += -I$(TOPDIR)

OBJCFLAGS = --remove-section=.ppcenv

LDSCRIPT := $(SRCTREE)/board/hymod/u-boot.lds
