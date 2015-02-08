include $(TOPDIR)/config.mk

LIB	= $(obj)lib$(CPU).a

START	= start.o
SOBJS	= io.o firmware_sc_task_bestcomm.impl.o
COBJS	= i2c.o traps.o cpu.o cpu_init.o ide.o interrupts.o \
	  loadtask.o pci_mpc5200.o serial.o speed.o usb_ohci.o usb.o

SRCS	:= $(START:.o=.S) $(SOBJS:.o=.S) $(COBJS:.o=.c)
OBJS	:= $(addprefix $(obj),$(SOBJS) $(COBJS))
START	:= $(addprefix $(obj),$(START))

all:	$(obj).depend $(START) $(LIB)

$(LIB):	$(OBJS)
	$(AR) $(ARFLAGS) $@ $(OBJS)

#########################################################################

# defines $(obj).depend target
include $(SRCTREE)/rules.mk

sinclude $(obj).depend

#########################################################################
