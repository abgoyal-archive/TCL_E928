include $(TOPDIR)/config.mk

LIB	= $(obj)lib$(BOARD).a

COBJS-y	+= $(BOARD).o
COBJS-$(CONFIG_FSL_DDR2) += ddr.o
COBJS-y	+= law.o

COBJS-$(CONFIG_FSL_DIU_FB)	+= mpc8610hpcd_diu.o

SRCS	:= $(SOBJS:.o=.S) $(COBJS-y:.o=.c)
OBJS	:= $(addprefix $(obj),$(COBJS-y))
SOBJS	:= $(addprefix $(obj),$(SOBJS))

$(LIB):	$(obj).depend $(OBJS) $(SOBJS)
	$(AR) $(ARFLAGS) $@ $(OBJS)

clean:
	rm -f $(OBJS) $(SOBJS)

.PHONY: distclean
distclean:	clean
	rm -f $(LIB) core *.bak $(obj).depend

#########################################################################

# defines $(obj).depend target
include $(SRCTREE)/rules.mk

sinclude $(obj).depend

#########################################################################
