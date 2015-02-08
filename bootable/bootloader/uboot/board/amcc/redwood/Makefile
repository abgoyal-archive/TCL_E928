include $(TOPDIR)/config.mk

LIB	= $(obj)lib$(BOARD).a

COBJS	= $(BOARD).o
SOBJS	= init.o

SRCS	:= $(SOBJS:.o=.S) $(COBJS:.o=.c)
OBJS	:= $(addprefix $(obj),$(COBJS))
SOBJS	:= $(addprefix $(obj),$(SOBJS))

$(LIB):	$(obj).depend $(OBJS) $(SOBJS)
	$(AR) $(ARFLAGS) $@ $(OBJS)

clean:
	rm -f $(SOBJS) $(OBJS)

distclean:	clean
	rm -f $(LIB) core *.bak .depend *~

#########################################################################

include $(SRCTREE)/rules.mk

sinclude $(obj).depend

#########################################################################
