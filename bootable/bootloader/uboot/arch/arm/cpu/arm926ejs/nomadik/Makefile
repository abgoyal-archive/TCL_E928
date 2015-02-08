include $(TOPDIR)/config.mk

LIB	= $(obj)lib$(SOC).a

COBJS	= timer.o gpio.o
SOBJS	= reset.o

SRCS	:= $(SOBJS:.o=.S) $(COBJS:.o=.c)
OBJS	:= $(addprefix $(obj),$(COBJS)) $(addprefix $(obj),$(SOBJS))

all:	$(obj).depend $(LIB)

$(LIB):	$(OBJS)
	$(AR) $(ARFLAGS) $@ $(OBJS)

#########################################################################

# defines $(obj).depend target
include $(SRCTREE)/rules.mk

sinclude $(obj).depend

#########################################################################
