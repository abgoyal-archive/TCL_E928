include $(TOPDIR)/config.mk

LIB	= $(obj)lib$(SOC).a

COBJS	= generic.o timer.o
MX27OBJS = reset.o

SRCS	:= $(SOBJS:.o=.S) $(COBJS:.o=.c)
SRCS	+= $(addprefix $(SRCTREE)/arch/arm/cpu/arm926ejs/mx27/,$(MX27OBJS:.o=.c))
OBJS	:= $(addprefix $(obj),$(SOBJS) $(COBJS) $(MX27OBJS))

all:	$(obj).depend $(LIB)

$(LIB):	$(OBJS)
	$(AR) $(ARFLAGS) $@ $(OBJS)

#########################################################################

# defines $(obj).depend target
include $(SRCTREE)/rules.mk

sinclude $(obj).depend

#########################################################################
