sinclude $(OBJTREE)/board/$(BOARDDIR)/config.tmp

ifndef TEXT_BASE
TEXT_BASE = 0xFFFA0000
endif

ifeq ($(debug),1)
PLATFORM_CPPFLAGS += -DDEBUG
endif

ifdef CONFIG_NAND_U_BOOT
LDSCRIPT := $(TOPDIR)/board/$(BOARDDIR)/u-boot-nand.lds
endif
