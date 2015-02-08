include $(TOPDIR)/config.mk

LIB	= $(obj)libfdt.a

SOBJS	=

COBJS-libfdt += fdt.o fdt_ro.o fdt_rw.o fdt_strerror.o fdt_sw.o fdt_wip.o

COBJS-$(CONFIG_OF_LIBFDT) += $(COBJS-libfdt)
COBJS-$(CONFIG_FIT) += $(COBJS-libfdt)


COBJS	:= $(sort $(COBJS-y))
SRCS	:= $(SOBJS:.o=.S) $(COBJS:.o=.c)
OBJS	:= $(addprefix $(obj),$(SOBJS) $(COBJS))

$(LIB):	$(obj).depend $(OBJS)
	$(AR) $(ARFLAGS) $@ $(OBJS)

#########################################################################

# defines $(obj).depend target
include $(SRCTREE)/rules.mk

sinclude $(obj).depend

#########################################################################
