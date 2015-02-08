TEXT_BASE = 0x06000000
CFLAGS_common/dlmalloc.o += -Wa,--no-warn -fno-strict-aliasing
PLATFORM_RELFLAGS += -fvisibility=hidden
PLATFORM_CPPFLAGS += -fno-dwarf2-cfi-asm
PLATFORM_LDFLAGS += -pic --emit-relocs -Bsymbolic -Bsymbolic-functions
