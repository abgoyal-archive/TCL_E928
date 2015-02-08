include $(TOPDIR)/config.mk

LIB	= $(obj)lib$(BOARD).a

COBJS-y += $(BOARD).o
COBJS-y += led.o
COBJS-y += misc.o
ifdef CONFIG_HAS_DATAFLASH
COBJS-$(CONFIG_DATAFLASH_MMC_SELECT) += mux.o
COBJS-y += partition.o
endif

SRCS	:= $(SOBJS:.o=.S) $(COBJS-y:.o=.c)
OBJS	:= $(addprefix $(obj),$(COBJS-y))
SOBJS	:= $(addprefix $(obj),$(SOBJS))

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
