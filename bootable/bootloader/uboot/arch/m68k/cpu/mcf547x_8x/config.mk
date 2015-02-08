PLATFORM_RELFLAGS += -ffixed-d7 -msep-data
ifneq ($(findstring 4.1,$(shell $(CC) --version)),4.1)
PLATFORM_CPPFLAGS += -mcpu=5485 -fPIC
else
PLATFORM_CPPFLAGS += -m5407 -fPIC
endif

ifneq (,$(findstring -linux-,$(shell $(CC) --version)))
ifneq (,$(findstring GOT,$(shell $(LD) --help)))
PLATFORM_LDFLAGS += --got=single
endif
endif
