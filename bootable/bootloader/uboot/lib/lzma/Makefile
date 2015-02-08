include $(TOPDIR)/config.mk

LIB	= $(obj)liblzma.a

SOBJS	=

CFLAGS += -D_LZMA_PROB32

COBJS-$(CONFIG_LZMA) += LzmaDec.o LzmaTools.o

COBJS	= $(COBJS-y)
SRCS 	:= $(SOBJS:.o=.S) $(COBJS:.o=.c)
OBJS	:= $(addprefix $(obj),$(SOBJS) $(COBJS))

$(LIB):	$(obj).depend $(OBJS)
	$(AR) $(ARFLAGS) $@ $(OBJS)

#########################################################################

# defines $(obj).depend target
include $(SRCTREE)/rules.mk

sinclude $(obj).depend

#########################################################################
