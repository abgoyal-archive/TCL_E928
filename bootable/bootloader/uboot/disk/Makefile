include $(TOPDIR)/config.mk

#CFLAGS += -DET_DEBUG -DDEBUG

LIB	= $(obj)libdisk.a

COBJS-y += part.o
COBJS-$(CONFIG_MAC_PARTITION)   += part_mac.o
COBJS-$(CONFIG_DOS_PARTITION)   += part_dos.o
COBJS-$(CONFIG_ISO_PARTITION)   += part_iso.o
COBJS-$(CONFIG_AMIGA_PARTITION) += part_amiga.o
COBJS-$(CONFIG_EFI_PARTITION)   += part_efi.o

COBJS	:= $(COBJS-y)
SRCS	:= $(COBJS:.o=.c)
OBJS	:= $(addprefix $(obj),$(COBJS))

all:	$(LIB)

$(LIB):	$(obj).depend $(OBJS)
	$(AR) $(ARFLAGS) $@ $(OBJS)

#########################################################################

# defines $(obj).depend target
include $(SRCTREE)/rules.mk

sinclude $(obj).depend

#########################################################################
