include $(TOPDIR)/config.mk

LIB	= $(obj)lib$(SOC).a

SOBJS	= cache.o
SOBJS	+= reset.o

COBJS	+= clock.o
COBJS	+= cpu_info.o
COBJS	+= sromc.o
COBJS	+= timer.o

SRCS	:= $(SOBJS:.o=.S) $(COBJS:.o=.c)
OBJS	:= $(addprefix $(obj),$(COBJS) $(SOBJS))

all:	 $(obj).depend $(LIB)

$(LIB):	$(OBJS)
	$(AR) $(ARFLAGS) $@ $(OBJS)

#########################################################################

# defines $(obj).depend target
include $(SRCTREE)/rules.mk

sinclude $(obj).depend

#########################################################################
