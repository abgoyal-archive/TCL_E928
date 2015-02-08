CFLAGS_lib_generic += -O2
CFLAGS_lzma += -O2

# Set some default LDR flags based on boot mode.
LDR_FLAGS-BFIN_BOOT_PARA := --bits 16 --dma 8
LDR_FLAGS-BFIN_BOOT_UART := --port g --gpio 6
LDR_FLAGS += $(LDR_FLAGS-$(CONFIG_BFIN_BOOT_MODE))
