include $(OBJTREE)/include/autoconf.mk

LIB	= libpostppc4xx.a

AOBJS-$(CONFIG_HAS_POST)	+= cache_4xx.o
COBJS-$(CONFIG_HAS_POST)	+= cache.o
COBJS-$(CONFIG_HAS_POST)	+= denali_ecc.o
COBJS-$(CONFIG_HAS_POST)	+= ether.o
COBJS-$(CONFIG_HAS_POST)	+= fpu.o
COBJS-$(CONFIG_HAS_POST)	+= ocm.o
COBJS-$(CONFIG_HAS_POST)	+= spr.o
COBJS-$(CONFIG_HAS_POST)	+= uart.o
COBJS-$(CONFIG_HAS_POST)	+= watchdog.o

include $(TOPDIR)/post/rules.mk
