PLATFORM_RELFLAGS += -ffixed-d7 -msep-data
ifneq ($(findstring 4.1,$(shell $(CC) --version)),4.1)
PLATFORM_CPPFLAGS += -mcpu=5235 -fPIC
else
PLATFORM_CPPFLAGS += -m5307 -fPIC
endif
