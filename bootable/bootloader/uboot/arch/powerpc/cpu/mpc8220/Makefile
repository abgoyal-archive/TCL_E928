include $(TOPDIR)/config.mk

LIB	= $(obj)lib$(CPU).a

START	= start.o
SOBJS	= io.o fec_dma_tasks.o
COBJS	= cpu.o cpu_init.o dramSetup.o fec.o i2c.o \
	  interrupts.o loadtask.o speed.o \
	  traps.o uart.o pci.o

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
