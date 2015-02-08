ifndef TEXT_BASE
## Standard: boot low
TEXT_BASE = 0xFFE00000
## For testing: boot from RAM
#TEXT_BASE = 0x00100000
endif

PLATFORM_CPPFLAGS += -DTEXT_BASE=$(TEXT_BASE) -I$(TOPDIR)/board
LDSCRIPT := $(SRCTREE)/arch/powerpc/cpu/mpc5xxx/u-boot-customlayout.lds
