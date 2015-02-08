include $(TOPDIR)/board/$(BOARDDIR)/config.mk

# PAD_TO used to generate a 4kByte binary needed for the combined image
# -> PAD_TO = TEXT_BASE + 4096
PAD_TO	:= $(shell expr $$[$(TEXT_BASE) + 4096])

ifeq ($(debug),1)
PLATFORM_CPPFLAGS += -DDEBUG
endif
