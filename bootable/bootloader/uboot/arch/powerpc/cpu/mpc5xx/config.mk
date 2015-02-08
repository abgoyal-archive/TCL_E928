PLATFORM_RELFLAGS +=	-fPIC -meabi

PLATFORM_CPPFLAGS +=	-DCONFIG_5xx -ffixed-r2 -mpowerpc -msoft-float

# Use default linker script.  Board port can override in board/*/config.mk
LDSCRIPT := $(SRCTREE)/arch/powerpc/cpu/mpc5xx/u-boot.lds
