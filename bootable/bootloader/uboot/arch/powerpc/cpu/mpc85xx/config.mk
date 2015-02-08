PLATFORM_RELFLAGS += -fPIC -meabi

PLATFORM_CPPFLAGS += -ffixed-r2 -Wa,-me500 -msoft-float -mno-string

# -mspe=yes is needed to have -mno-spe accepted by a buggy GCC;
# see "[PATCH,rs6000] make -mno-spe work as expected" on
# http://gcc.gnu.org/ml/gcc-patches/2008-04/msg00311.html
PLATFORM_CPPFLAGS +=$(call cc-option,-mspe=yes)
PLATFORM_CPPFLAGS +=$(call cc-option,-mno-spe)

# Use default linker script.  Board port can override in board/*/config.mk
LDSCRIPT := $(SRCTREE)/arch/powerpc/cpu/mpc85xx/u-boot.lds
