include $(TOPDIR)/config.mk

ifneq ($(OBJTREE),$(SRCTREE))
$(shell mkdir -p $(obj)board/$(VENDOR)/common)
endif

LIB	= $(obj)lib$(VENDOR).a

COBJS-$(CONFIG_FSL_PCI_INIT)	+= fsl_8xxx_pci.o
COBJS-$(CONFIG_MPC8572)		+= fsl_8xxx_clk.o
COBJS-$(CONFIG_MPC86xx)		+= fsl_8xxx_clk.o
COBJS-$(CONFIG_FSL_DDR2)	+= fsl_8xxx_ddr.o
COBJS-$(CONFIG_NAND_ACTL)	+= actl_nand.o

SRCS	:= $(SOBJS:.o=.S) $(COBJS-y:.o=.c)
OBJS	:= $(addprefix $(obj),$(COBJS-y))
SOBJS	:= $(addprefix $(obj),$(SOBJS))

$(LIB):	$(obj).depend $(OBJS)
	$(AR) $(ARFLAGS) $@ $(OBJS)

clean:
	rm -f $(SOBJS) $(OBJS)

distclean:	clean
	rm -f $(LIB) core *.bak $(obj).depend

#########################################################################

# defines $(obj).depend target
include $(SRCTREE)/rules.mk

sinclude $(obj).depend

#########################################################################
