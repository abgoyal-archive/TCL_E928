include $(TOPDIR)/config.mk

LIB	= $(obj)lib$(CPU).a

START	= start.o

COBJS-y += traps.o
COBJS-y += cpu.o
COBJS-y += cpu_init.o
COBJS-y += speed.o
COBJS-y += interrupts.o
COBJS-y += spd_sdram.o
COBJS-y += ecc.o
COBJS-$(CONFIG_QE) += qe_io.o
COBJS-$(CONFIG_FSL_SERDES) += serdes.o
COBJS-$(CONFIG_PCI) += pci.o
COBJS-$(CONFIG_PCIE) += pcie.o
COBJS-$(CONFIG_OF_LIBFDT) += fdt.o

COBJS	:= $(COBJS-y)
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
