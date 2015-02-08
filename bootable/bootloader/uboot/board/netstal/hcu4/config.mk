TEXT_BASE = 0xFFFB0000

ifeq ($(debug),1)
PLATFORM_CPPFLAGS += -DDEBUG -g
endif
