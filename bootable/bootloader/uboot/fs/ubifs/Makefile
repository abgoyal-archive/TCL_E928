include $(TOPDIR)/config.mk

LIB	= $(obj)libubifs.a

COBJS-$(CONFIG_CMD_UBIFS) := ubifs.o io.o super.o sb.o master.o lpt.o
COBJS-$(CONFIG_CMD_UBIFS) += lpt_commit.o scan.o lprops.o
COBJS-$(CONFIG_CMD_UBIFS) += tnc.o tnc_misc.o debug.o crc16.o budget.o
COBJS-$(CONFIG_CMD_UBIFS) += log.o orphan.o recovery.o replay.o

SRCS	:= $(AOBJS:.o=.S) $(COBJS-y:.o=.c)
OBJS	:= $(addprefix $(obj),$(AOBJS) $(COBJS-y))

all:	$(LIB) $(AOBJS)

$(LIB):	$(obj).depend $(OBJS)
	$(AR) $(ARFLAGS) $@ $(OBJS)

#########################################################################

# defines $(obj).depend target
include $(SRCTREE)/rules.mk

sinclude $(obj).depend

#########################################################################
