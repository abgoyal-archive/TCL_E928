include $(TOPDIR)/config.mk

COBJS	:= $(COBJS-y)
AOBJS	:= $(AOBJS-y)
SRCS	:= $(AOBJS:.o=.S) $(COBJS:.o=.c)
OBJS	:= $(addprefix $(obj),$(AOBJS) $(COBJS))
LIB	:= $(obj)$(LIB)

CPPFLAGS += -I$(TOPDIR)

all:	$(LIB)

$(LIB):	$(obj).depend $(OBJS)
	$(AR) $(ARFLAGS) $@ $(OBJS)

#########################################################################

# defines $(obj).depend target
include $(SRCTREE)/rules.mk

sinclude $(obj).depend

#########################################################################
