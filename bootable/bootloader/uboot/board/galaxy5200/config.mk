sinclude $(TOPDIR)/board/$(BOARDDIR)/config.tmp

ifdef CONFIG_galaxy5200_LOWBOOT
TEXT_BASE = 0xFE000000
endif

ifndef TEXT_BASE
## Standard: boot high
TEXT_BASE = 0xFFF00000
endif

PLATFORM_CPPFLAGS += -DTEXT_BASE=$(TEXT_BASE) -I$(TOPDIR)/board
