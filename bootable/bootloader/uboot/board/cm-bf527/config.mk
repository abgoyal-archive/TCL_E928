CFLAGS_lib += -O2
CFLAGS_lib/lzma += -O2

# Set some default LDR flags based on boot mode.
LDR_FLAGS += $(LDR_FLAGS-$(CONFIG_BFIN_BOOT_MODE))
