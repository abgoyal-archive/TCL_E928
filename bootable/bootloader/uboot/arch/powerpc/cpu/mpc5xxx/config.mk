PLATFORM_RELFLAGS += -fPIC -meabi

PLATFORM_CPPFLAGS += -DCONFIG_MPC5xxx -ffixed-r2 \
		     -mstring -mcpu=603e -mmultiple

# Use default linker script.  Board port can override in board/*/config.mk
LDSCRIPT := $(SRCTREE)/arch/powerpc/cpu/mpc5xxx/u-boot.lds
