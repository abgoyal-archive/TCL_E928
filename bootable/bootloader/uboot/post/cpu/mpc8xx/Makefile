include $(OBJTREE)/include/autoconf.mk

LIB	= libpostmpc8xx.a

AOBJS-$(CONFIG_HAS_POST)	+= cache_8xx.o
COBJS-$(CONFIG_HAS_POST)	+= cache.o ether.o spr.o uart.o usb.o watchdog.o

include $(TOPDIR)/post/rules.mk
