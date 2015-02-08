include $(TOPDIR)/config.mk

LIB	= $(obj)lib$(SOC).a

SOBJS	= reset.o

COBJS-$(CONFIG_S3C6400)	+= cpu_init.o speed.o
COBJS-y	+= timer.o

OBJS	:= $(addprefix $(obj),$(SOBJS) $(COBJS-y))

all:	$(obj).depend $(START) $(LIB)

$(LIB):	$(OBJS)
	$(AR) $(ARFLAGS) $@ $(OBJS)

#########################################################################

# defines $(obj).depend target
include $(SRCTREE)/rules.mk

sinclude $(obj).depend

#########################################################################
