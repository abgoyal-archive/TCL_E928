include $(TOPDIR)/config.mk

LIB	= $(obj)lib$(BOARD).a


# NOBJS : Netstal common objects
NOBJS	= nm_bsp.o
COBJS	= $(BOARD).o sdram.o
SOBJS	= init.o

SRCS	:= $(SOBJS:.o=.S) $(COBJS:.o=.c) $(addprefix ../common/,$(NOBJS:.o=.c))
OBJS	:= $(addprefix $(obj),$(COBJS))
NOBJS	:= $(addprefix $(obj)../common/,$(NOBJS))
SOBJS	:= $(addprefix $(obj),$(SOBJS))

$(LIB):	$(OBJS) $(SOBJS) $(NOBJS)
	$(AR) $(ARFLAGS) $@ $(OBJS) $(SOBJS) $(NOBJS)

clean:
	rm -f $(SOBJS) $(OBJS)

distclean:	clean
	rm -f $(LIB) core *.bak $(obj).depend

#########################################################################

# defines $(obj).depend target
include $(SRCTREE)/rules.mk

sinclude $(obj).depend

#########################################################################
