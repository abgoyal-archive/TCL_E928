include $(TOPDIR)/config.mk

LIB	= $(obj)lib$(SOC).a

COBJS-$(CONFIG_USE_IRQ) += interrupts.o
COBJS-y	+= speed.o
COBJS-y	+= timer.o
COBJS-y	+= usb.o
COBJS-y	+= usb_ohci.o


SRCS	:= $(SOBJS:.o=.S) $(COBJS-y:.o=.c)
OBJS	:= $(addprefix $(obj),$(SOBJS) $(COBJS-y))

all:	$(obj).depend $(LIB)

$(LIB):	$(OBJS)
	$(AR) $(ARFLAGS) $@ $(OBJS)

#########################################################################

# defines $(obj).depend target
include $(SRCTREE)/rules.mk

sinclude $(obj).depend

#########################################################################
