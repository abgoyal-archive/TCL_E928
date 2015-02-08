sinclude $(OBJTREE)/board/$(BOARDDIR)/config.tmp

ifndef TEXT_BASE
TEXT_BASE = 0x0DF40000
endif

LDSCRIPT := $(SRCTREE)/board/$(BOARDDIR)/u-boot.lds
