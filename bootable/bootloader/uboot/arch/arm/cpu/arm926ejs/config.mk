PLATFORM_RELFLAGS += -fno-strict-aliasing  -fno-common -ffixed-r8

# Jau remove 	-msoft-float

#PLATFORM_CPPFLAGS += -march=armv5te
PLATFORM_CPPFLAGS += -march=armv4
# =========================================================================
#
# Supply options according to compiler version
#
# =========================================================================
PLATFORM_CPPFLAGS +=$(call cc-option,-mapcs-32,-mabi=apcs-gnu)
PLATFORM_CPPFLAGS +=$(call cc-option,-mno-thumb-interwork,)  # Jauping add
PLATFORM_RELFLAGS +=$(call cc-option,-mshort-load-bytes,$(call cc-option,-malignment-traps,))
#PLATFORM_RELFLAGS +=$(call cc-option,-mshort-load-bytes,$(call cc-option,-malignment-traps,))
