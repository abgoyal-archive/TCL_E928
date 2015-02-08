include $(TOPDIR)/config.mk
ifneq ($(OBJTREE),$(SRCTREE))
$(shell mkdir -p $(obj)../../Marvell/common)
endif

LIB	= $(obj)lib$(BOARD).a

SOBJS	= misc.o

COBJS	= $(BOARD).o serial.o ../../Marvell/common/memory.o pci.o \
	  mv_eth.o  mpsc.o i2c.o \
	  sdram_init.o ide.o

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
