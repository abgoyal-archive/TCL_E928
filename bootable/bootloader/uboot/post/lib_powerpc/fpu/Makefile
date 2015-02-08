include $(TOPDIR)/config.mk

LIB	= libpost$(ARCH)fpu.a

COBJS-$(CONFIG_HAS_POST)	+= fpu.o 20001122-1.o 20010114-2.o 20010226-1.o 980619-1.o
COBJS-$(CONFIG_HAS_POST)	+= acc1.o compare-fp-1.o mul-subnormal-single-1.o

include $(TOPDIR)/post/rules.mk

CFLAGS := $(shell echo $(CFLAGS) | sed s/-msoft-float//)
CFLAGS += -mhard-float -fkeep-inline-functions
