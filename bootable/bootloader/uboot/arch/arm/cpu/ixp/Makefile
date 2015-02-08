include $(TOPDIR)/config.mk

LIB	= $(obj)lib$(CPU).a

START	= start.o

COBJS-y	+= cpu.o
COBJS-$(CONFIG_USE_IRQ)	+= interrupts.o
COBJS-y	+= timer.o

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
