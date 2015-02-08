include $(TOPDIR)/config.mk

LIB	= $(obj)lib$(BOARD).a

COBJS-y	+= eNET.o
COBJS-$(CONFIG_PCI) += eNET_pci.o
SOBJS-y	+= eNET_start16.o
SOBJS-y	+= eNET_start.o

SRCS	:= $(SOBJS-y:.o=.S) $(COBJS-y:.o=.c)
OBJS	:= $(addprefix $(obj),$(SOBJS-y) $(COBJS-y))

$(LIB):	$(obj).depend $(OBJS) $(SOBJS)
	$(AR) $(ARFLAGS) $@ $(OBJS) $(SOBJS)

clean:
	rm -f $(SOBJS) $(OBJS)

distclean:	clean
	rm -f $(LIB) core *.bak $(obj).depend

#########################################################################

# defines $(obj).depend target
include $(SRCTREE)/rules.mk

sinclude $(obj).depend

#########################################################################
