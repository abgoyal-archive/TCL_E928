include $(TOPDIR)/config.mk

LIB 	:= $(obj)libubi.a

ifdef CONFIG_CMD_UBI
COBJS-y += build.o vtbl.o vmt.o upd.o kapi.o eba.o io.o wl.o scan.o crc32.o

COBJS-y += misc.o
COBJS-y += debug.o
endif

COBJS	:= $(COBJS-y)
SRCS 	:= $(COBJS:.o=.c)
OBJS 	:= $(addprefix $(obj),$(COBJS))

all:	$(LIB)

$(LIB):	$(obj).depend $(OBJS)
	$(AR) $(ARFLAGS) $@ $(OBJS)

#########################################################################

# defines $(obj).depend target
include $(SRCTREE)/rules.mk

sinclude $(obj).depend

#########################################################################
