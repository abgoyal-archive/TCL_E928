include $(TOPDIR)/config.mk

LIB	= $(obj)lib$(BOARD).a

SOBJS-y	:= lowlevel_init.o

COBJS-y	:= integrator.o
COBJS-$(CONFIG_PCI) += pci.o
COBJS-y += timer.o

SRCS	:= $(SOBJS-y:.o=.S) $(COBJS-y:.o=.c)
COBJS	:= $(addprefix $(obj),$(COBJS-y))
SOBJS	:= $(addprefix $(obj),$(SOBJS-y))

$(LIB):	$(obj).depend $(COBJS) $(SOBJS)
	$(AR) $(ARFLAGS) $@ $(COBJS) $(SOBJS)

clean:
	rm -f $(SOBJS) $(COBJS)

distclean:	clean
	rm -f $(LIB) core *.bak $(obj).depend

#########################################################################

# defines $(obj).depend target
include $(SRCTREE)/rules.mk

sinclude $(obj).depend

#########################################################################
