PLATFORM_RELFLAGS += -ffixed-d7 -msep-data

cfg=$(shell grep configs $(OBJTREE)/include/config.h | sed 's/.*<\(configs.*\)>/\1/')
is5301x:=$(shell grep CONFIG_MCF5301x $(TOPDIR)/include/$(cfg))
is532x:=$(shell grep CONFIG_MCF532x $(TOPDIR)/include/$(cfg))

ifneq ($(findstring 4.1,$(shell $(CC) --version)),4.1)

ifneq (,$(findstring CONFIG_MCF5301x,$(is5301x)))
PLATFORM_CPPFLAGS += -mcpu=53015 -fPIC
endif
ifneq (,$(findstring CONFIG_MCF532x,$(is532x)))
PLATFORM_CPPFLAGS += -mcpu=5329 -fPIC
endif

else
PLATFORM_CPPFLAGS += -m5307 -fPIC
endif
