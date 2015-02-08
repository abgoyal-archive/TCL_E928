include $(TOPDIR)/config.mk

LIB	= $(obj)lib$(CPU).a

START	= start.o kgdb.o
COBJS	= traps.o serial_smc.o serial_scc.o cpu.o cpu_init.o speed.o \
	  interrupts.o ether_fcc.o i2c.o commproc.o \
	  bedbug_603e.o pci.o spi.o

COBJS-$(CONFIG_ETHER_ON_SCC) = ether_scc.o

COBJS	+= $(COBJS-y)

SRCS	:= $(START:.o=.S) $(SOBJS:.o=.S) $(COBJS:.o=.c)
OBJS	:= $(addprefix $(obj),$(SOBJS) $(COBJS))
START	:= $(addprefix $(obj),$(START))

all:	$(obj).depend $(START) $(LIB)

$(LIB):	$(OBJS)
	$(AR) $(ARFLAGS) $@ $(OBJS) $(obj)kgdb.o

#########################################################################

# defines $(obj).depend target
include $(SRCTREE)/rules.mk

sinclude $(obj).depend

#########################################################################
