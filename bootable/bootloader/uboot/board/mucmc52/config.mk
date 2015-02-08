ifndef TEXT_BASE
## Standard: boot high
TEXT_BASE = 0xFFF00000
## For testing: boot from RAM
#TEXT_BASE = 0x00100000
endif

PLATFORM_CPPFLAGS += -DTEXT_BASE=$(TEXT_BASE) -I$(TOPDIR)/board
LDSCRIPT := $(SRCTREE)/arch/powerpc/cpu/mpc5xxx/u-boot.lds
