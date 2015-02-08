PLATFORM_RELFLAGS += -fPIC -meabi

PLATFORM_CPPFLAGS += -DCONFIG_MPC512X -DCONFIG_E300 \
			-ffixed-r2 -msoft-float -mcpu=603e

# Use default linker script.
# A board port can override this setting in board/*/config.mk
LDSCRIPT := $(SRCTREE)/arch/powerpc/cpu/mpc512x/u-boot.lds
