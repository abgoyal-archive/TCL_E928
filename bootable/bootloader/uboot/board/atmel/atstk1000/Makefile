include $(TOPDIR)/config.mk

LIB			:= $(obj)lib$(BOARD).a

COBJS-y			+= $(BOARD).o
COBJS-y			+= flash.o

SRCS			:= $(SOBJS-y:.o=.S) $(COBJS-y:.o=.c)
OBJS			:= $(addprefix $(obj),$(SOBJS-y) $(COBJS-y))

$(LIB): $(obj).depend $(OBJS)
	$(AR) $(ARFLAGS) $@ $(OBJS)

#########################################################################

# defines $(obj).depend target
include $(SRCTREE)/rules.mk

sinclude $(obj).depend

#########################################################################
