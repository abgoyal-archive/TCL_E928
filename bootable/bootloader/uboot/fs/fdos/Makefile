include $(TOPDIR)/config.mk

LIB	= $(obj)libfdos.a

AOBJS	=
COBJS-$(CONFIG_CMD_FDOS) := fat.o vfat.o dev.o fdos.o fs.o subdir.o

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
