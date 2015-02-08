include $(TOPDIR)/config.mk

LIB	= $(obj)lib$(SOC).a

SOBJS	+= lowlevel_init.o

COBJS	+= bcm5221.o
COBJS	+= dm9161.o
COBJS	+= ether.o
COBJS	+= i2c.o
COBJS-$(CONFIG_KS8721_PHY)	+= ks8721.o
COBJS	+= lxt972.o
COBJS	+= reset.o
COBJS	+= spi.o
COBJS	+= timer.o
COBJS	+= usb.o

SRCS	:= $(SOBJS:.o=.S) $(COBJS:.o=.c) $(COBJS-y:.o=.c)
OBJS	:= $(addprefix $(obj),$(SOBJS) $(COBJS) $(COBJS-y))

all:	$(obj).depend $(LIB)

$(LIB):	$(OBJS)
	$(AR) $(ARFLAGS) $@ $(OBJS)

#########################################################################

# defines $(obj).depend target
include $(SRCTREE)/rules.mk

sinclude $(obj).depend

#########################################################################
