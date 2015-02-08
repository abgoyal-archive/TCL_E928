CROSS_COMPILE ?= m68k-elf-

clibdir = $(shell dirname `$(CC) $(CFLAGS) -print-file-name=libc.a`)
STANDALONE_LOAD_ADDR = 0x20000 -L $(clibdir)

PLATFORM_CPPFLAGS += -DCONFIG_M68K -D__M68K__
PLATFORM_LDFLAGS  += -n
