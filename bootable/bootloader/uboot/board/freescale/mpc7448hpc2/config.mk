TEXT_BASE = 0xFF000000
# RAM address
#TEXT_BASE = 0x00400000

PLATFORM_CPPFLAGS += -DTEXT_BASE=$(TEXT_BASE) -maltivec -mabi=altivec -msoft-float
