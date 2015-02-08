include $(TOPDIR)/config.mk

LIB	= $(obj)lib$(BOARD).a

COBJS	= $(BOARD).o cpc710_pci.o flash.o sconsole.o \
	  fpga_serial.o pcippc2_fpga.o cpc710_init_ram.o i2c.o

SOBJS	=

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
