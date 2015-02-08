sinclude $(OBJTREE)/board/$(BOARDDIR)/config.tmp

ifndef TEXT_BASE
## Standard: boot high
TEXT_BASE = 0xFFF00000
endif
