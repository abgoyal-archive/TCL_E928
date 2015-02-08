include $(TOPDIR)/config.mk

LIB	= $(obj)lib$(BOARD).a

SOBJS	= misc.o
COBJS	= $(BOARD).o flash.o serial.o memory.o pci.o \
	  eth.o eth_addrtbl.o mpsc.o i2c.o \
	  sdram_init.o zuma_pbb.o intel_flash.o zuma_pbb_mbox.o

SRCS	:= $(SOBJS:.o=.S) $(COBJS:.o=.c)
OBJS	:= $(addprefix $(obj),$(COBJS))
SOBJS	:= $(addprefix $(obj),$(SOBJS))

$(LIB):	$(obj).depend $(OBJS) $(SOBJS)
	$(AR) $(ARFLAGS) $@ $(OBJS) $(SOBJS)

#########################################################################

# defines $(obj).depend target
include $(SRCTREE)/rules.mk

sinclude $(obj).depend

#########################################################################
