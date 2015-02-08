TEXT_BASE = 0xE0013000

# PAD_TO used to generate a 16kByte binary needed for the combined image
# -> PAD_TO = TEXT_BASE + 0x4000
PAD_TO	= 0xE0017000

PLATFORM_CPPFLAGS += -DCONFIG_440=1

ifeq ($(debug),1)
PLATFORM_CPPFLAGS += -DDEBUG
endif

ifeq ($(dbcr),1)
PLATFORM_CPPFLAGS += -DCONFIG_SYS_INIT_DBCR=0x8cff0000
endif
