PLATFORM_RELFLAGS += -fPIC -meabi
PLATFORM_CPPFLAGS += -DCONFIG_4xx -ffixed-r2 -mstring -msoft-float

cfg=$(shell grep configs $(OBJTREE)/include/config.h | sed 's/.*<\(configs.*\)>/\1/')
is440:=$(shell grep CONFIG_440 $(TOPDIR)/include/$(cfg))

ifneq (,$(findstring CONFIG_440,$(is440)))
PLATFORM_CPPFLAGS += -Wa,-m440 -mcpu=440
else
PLATFORM_CPPFLAGS += -Wa,-m405 -mcpu=405
endif

# Use default linker script.  Board port can override in board/*/config.mk
LDSCRIPT := $(SRCTREE)/arch/powerpc/cpu/ppc4xx/u-boot.lds
