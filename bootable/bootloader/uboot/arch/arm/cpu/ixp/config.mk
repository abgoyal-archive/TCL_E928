BIG_ENDIAN = y

PLATFORM_RELFLAGS += -fno-common -ffixed-r8 -msoft-float -mbig-endian

PLATFORM_CPPFLAGS += -mbig-endian -march=armv5te -mtune=strongarm1100
# =========================================================================
#
# Supply options according to compiler version
#
# =========================================================================
PLATFORM_RELFLAGS +=$(call cc-option,-mshort-load-bytes,$(call cc-option,-malignment-traps,))
