ifndef NAND_SPL
ifeq ($(CONFIG_MK_NAND), y)
TEXT_BASE = $(CONFIG_RAMBOOT_TEXT_BASE)
LDSCRIPT := $(TOPDIR)/$(CPUDIR)/u-boot-nand.lds
endif
endif

ifndef TEXT_BASE
TEXT_BASE = 0xfff80000
endif
