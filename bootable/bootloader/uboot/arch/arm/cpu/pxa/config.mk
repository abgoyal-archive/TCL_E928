PLATFORM_RELFLAGS += -fno-common -ffixed-r8 -msoft-float

PLATFORM_CPPFLAGS += -march=armv5te -mtune=xscale
# =========================================================================
#
# Supply options according to compiler version
#
# ========================================================================
PLATFORM_RELFLAGS +=$(call cc-option,-mshort-load-bytes,$(call cc-option,-malignment-traps,))
