PLATFORM_RELFLAGS += -fPIC -meabi

PLATFORM_CPPFLAGS += -DCONFIG_8260 -DCONFIG_CPM2 -ffixed-r2 \
		     -mstring -mcpu=603e -mmultiple

# Use default linker script.  Board port can override in board/*/config.mk
LDSCRIPT := $(SRCTREE)/arch/powerpc/cpu/mpc8260/u-boot.lds
