sinclude $(OBJTREE)/board/$(BOARDDIR)/config.tmp

ifndef TEXT_BASE
## Standard: boot low
TEXT_BASE = 0xFC000000
## For a backup copy of U-Boot at the end of flash: boot high
# TEXT_BASE = 0xFFF00000
## For testing: boot from RAM
# TEXT_BASE = 0x00100000
endif

PLATFORM_CPPFLAGS += -DTEXT_BASE=$(TEXT_BASE) -I$(TOPDIR)/board
