PLATFORM_RELFLAGS += -fPIC -meabi

PLATFORM_CPPFLAGS += -DCONFIG_MPC8220 -ffixed-r2 \
		     -mstring -mcpu=603e -mmultiple

# Use default linker script.  Board port can override in board/*/config.mk
LDSCRIPT := $(SRCTREE)/arch/powerpc/cpu/mpc8220/u-boot.lds
