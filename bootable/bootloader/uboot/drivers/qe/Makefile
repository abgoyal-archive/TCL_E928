include $(TOPDIR)/config.mk

LIB	:= $(obj)qe.a

COBJS-$(CONFIG_OF_LIBFDT) += fdt.o
COBJS-$(CONFIG_QE) += qe.o uccf.o uec.o uec_phy.o

COBJS	:= $(COBJS-y)
SRCS	:= $(COBJS:.o=.c)
OBJS	:= $(addprefix $(obj),$(COBJS))

all:	$(LIB)

$(LIB):	$(obj).depend $(OBJS)
	$(AR) $(ARFLAGS) $@ $(OBJS)

#########################################################################

include $(SRCTREE)/rules.mk

sinclude $(obj).depend

#########################################################################
