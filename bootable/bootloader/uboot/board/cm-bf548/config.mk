CFLAGS_lib += -O2
CFLAGS_lib/lzma += -O2

# Set some default LDR flags based on boot mode.
LDR_FLAGS-BFIN_BOOT_PARA       := --dma 6
LDR_FLAGS-BFIN_BOOT_FIFO       := --dma 1
LDR_FLAGS-BFIN_BOOT_SPI_MASTER := --dma 1
LDR_FLAGS-BFIN_BOOT_UART       := --dma 1
LDR_FLAGS += $(LDR_FLAGS-$(CONFIG_BFIN_BOOT_MODE))
