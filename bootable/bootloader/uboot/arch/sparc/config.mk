CROSS_COMPILE ?= sparc-elf-

STANDALONE_LOAD_ADDR = 0x00000000 -L $(gcclibdir) -T sparc.lds

PLATFORM_CPPFLAGS += -DCONFIG_SPARC -D__sparc__
