include $(TOPDIR)/config.mk

LIB	= $(obj)libcramfs.a

AOBJS	=
COBJS-$(CONFIG_CMD_CRAMFS) := cramfs.o
COBJS-$(CONFIG_CMD_CRAMFS) += uncompress.o

SRCS	:= $(AOBJS:.o=.S) $(COBJS-y:.o=.c)
OBJS	:= $(addprefix $(obj),$(AOBJS) $(COBJS-y))

#CPPFLAGS +=

all:	$(LIB) $(AOBJS)

$(LIB):	$(obj).depend $(OBJS)
	$(AR) $(ARFLAGS) $@ $(OBJS)


#########################################################################

# defines $(obj).depend target
include $(SRCTREE)/rules.mk

sinclude $(obj).depend

#########################################################################
