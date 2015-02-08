include $(TOPDIR)/config.mk

LIB	=  $(obj)lib$(SOC).a

SOBJS	:= lowlevel_init.o
SOBJS	+= cache.o
SOBJS	+= reset.o

COBJS	+= board.o
COBJS	+= clock.o
COBJS	+= gpio.o
COBJS	+= mem.o
COBJS	+= syslib.o
COBJS	+= sys_info.o
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
