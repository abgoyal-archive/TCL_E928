sinclude $(OBJTREE)/board/$(BOARDDIR)/config.tmp

ifndef CONFIG_NAND_SPL
TEXT_BASE = $(RAM_TEXT)
else
TEXT_BASE = 0
endif

LDSCRIPT := $(SRCTREE)/board/$(BOARDDIR)/u-boot-nand.lds
