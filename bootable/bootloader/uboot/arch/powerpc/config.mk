CROSS_COMPILE ?= ppc_8xx-

STANDALONE_LOAD_ADDR = 0x40000

PLATFORM_RELFLAGS += -mrelocatable
PLATFORM_CPPFLAGS += -DCONFIG_PPC -D__powerpc__
PLATFORM_LDFLAGS  += -n

#
# When cross-compiling on NetBSD, we have to define __PPC__ or else we
# will pick up a va_list declaration that is incompatible with the
# actual argument lists emitted by the compiler.
#
# [Tested on NetBSD/i386 1.5 + cross-powerpc-netbsd-1.3]

ifeq ($(CROSS_COMPILE),powerpc-netbsd-)
PLATFORM_CPPFLAGS+= -D__PPC__
endif
ifeq ($(CROSS_COMPILE),powerpc-openbsd-)
PLATFORM_CPPFLAGS+= -D__PPC__
endif
