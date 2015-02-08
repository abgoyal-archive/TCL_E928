include $(TOPDIR)/config.mk

LIB	= $(obj)libapi.a

COBJS-$(CONFIG_API) += api.o api_net.o api_storage.o api_platform-$(ARCH).o

COBJS	:= $(COBJS-y)
SRCS	:= $(COBJS:.o=.c)
OBJS	:= $(addprefix $(obj),$(COBJS))

$(LIB):	$(obj).depend $(OBJS)
	$(AR) $(ARFLAGS) $@ $(OBJS)

# defines $(obj).depend target
include $(SRCTREE)/rules.mk

sinclude $(obj).depend
