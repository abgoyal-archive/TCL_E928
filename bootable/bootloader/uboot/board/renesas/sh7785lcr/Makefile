include $(TOPDIR)/config.mk

LIB	= $(obj)lib$(BOARD).a

COBJS	:= sh7785lcr.o selfcheck.o rtl8169_mac.o
SOBJS	:= lowlevel_init.o

$(LIB):	$(obj).depend $(COBJS) $(SOBJS)
	$(AR) $(ARFLAGS) $@ $(COBJS) $(SOBJS)

clean:
	rm -f $(SOBJS) $(OBJS)

distclean:	clean
	rm -f $(LIB) core *.bak $(obj).depend

#########################################################################

# defines $(obj).depend target
include $(SRCTREE)/rules.mk

sinclude $(obj).depend

#########################################################################
