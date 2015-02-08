include $(TOPDIR)/config.mk

# CFLAGS += -DDEBUG

LIB	= $(obj)libnet.a

COBJS-$(CONFIG_CMD_NET)  += bootp.o
COBJS-$(CONFIG_CMD_DNS)  += dns.o
COBJS-$(CONFIG_CMD_NET)  += eth.o
COBJS-$(CONFIG_CMD_NET)  += net.o
COBJS-$(CONFIG_CMD_NFS)  += nfs.o
COBJS-$(CONFIG_CMD_NET)  += rarp.o
COBJS-$(CONFIG_CMD_SNTP) += sntp.o
COBJS-$(CONFIG_CMD_NET)  += tftp.o

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
