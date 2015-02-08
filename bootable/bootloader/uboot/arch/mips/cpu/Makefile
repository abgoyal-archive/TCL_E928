include $(TOPDIR)/config.mk

LIB	= $(obj)lib$(CPU).a

START	= start.o
SOBJS-y	= cache.o
COBJS-y	= cpu.o interrupts.o

SOBJS-$(CONFIG_INCA_IP)	+= incaip_wdt.o
COBJS-$(CONFIG_INCA_IP)	+= asc_serial.o incaip_clock.o
COBJS-$(CONFIG_PURPLE)	+= asc_serial.o
COBJS-$(CONFIG_SOC_AU1X00) += au1x00_eth.o au1x00_serial.o au1x00_usb_ohci.o

SRCS	:= $(START:.o=.S) $(SOBJS-y:.o=.S) $(COBJS-y:.o=.c)
OBJS	:= $(addprefix $(obj),$(SOBJS-y) $(COBJS-y))
START	:= $(addprefix $(obj),$(START))

all:	$(obj).depend $(START) $(LIB)

$(LIB):	$(OBJS)
	$(AR) $(ARFLAGS) $@ $(OBJS)

#########################################################################

# defines $(obj).depend target
include $(SRCTREE)/rules.mk

sinclude $(obj).depend

#########################################################################
