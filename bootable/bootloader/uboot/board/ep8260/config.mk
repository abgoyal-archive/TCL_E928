TEXT_BASE = 0xFFF00000

PLATFORM_CPPFLAGS += -DTEXT_BASE=$(TEXT_BASE) -I$(TOPDIR)