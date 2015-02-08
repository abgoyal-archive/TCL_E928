sinclude $(OBJTREE)/board/$(BOARDDIR)/config.tmp

ifndef TEXT_BASE
# For flash image - all models
TEXT_BASE = 0xFFF00000
# For RAM image
# HLAN and LAN
#TEXT_BASE = 0x03F00000
# HGLAN and HGTL
#TEXT_BASE = 0x07F00000
endif

PLATFORM_CPPFLAGS += -DTEXT_BASE=$(TEXT_BASE)
