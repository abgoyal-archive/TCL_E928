include $(TOPDIR)/config.mk

LIB	= $(obj)lib$(SOC).a

COBJS	= flash.o mmc.o mmc_hw.o spi.o
SOBJS	= $(obj)iap_entry.o

SRCS	:= $(COBJS:.o=.c)
OBJS	:= $(addprefix $(obj),$(COBJS))

all:	$(obj).depend $(LIB)

$(LIB):	$(OBJS) $(SOBJS)
	$(AR) $(ARFLAGS) $@ $(OBJS) $(SOBJS)

# this MUST be compiled as thumb code!
$(SOBJS):
	$(CC) $(AFLAGS) -march=armv4t -c -o $(SOBJS) iap_entry.S

#########################################################################

# defines $(obj).depend target
include $(SRCTREE)/rules.mk

sinclude $(obj).depend

#########################################################################
