PLATFORM_RELFLAGS += -fPIC -meabi

PLATFORM_CPPFLAGS += -DCONFIG_MPC83xx -DCONFIG_E300 \
			-ffixed-r2 -msoft-float

# Use default linker script.  Board port can override in board/*/config.mk
LDSCRIPT := $(SRCTREE)/arch/powerpc/cpu/mpc83xx/u-boot.lds
