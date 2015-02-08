include $(TOPDIR)/config.mk

LIB	= $(obj)lib$(CPU).a

START	= start.o resetvec.o
SOBJS-$(CONFIG_MP)	+= release.o
SOBJS	= $(SOBJS-y)

COBJS-$(CONFIG_CPM2)	+= commproc.o

# supports ddr1
COBJS-$(CONFIG_MPC8540) += ddr-gen1.o
COBJS-$(CONFIG_MPC8560) += ddr-gen1.o
COBJS-$(CONFIG_MPC8541) += ddr-gen1.o
COBJS-$(CONFIG_MPC8555) += ddr-gen1.o

# supports ddr1/2
COBJS-$(CONFIG_MPC8548) += ddr-gen2.o
COBJS-$(CONFIG_MPC8568) += ddr-gen2.o
COBJS-$(CONFIG_MPC8544) += ddr-gen2.o

# supports ddr1/2/3
COBJS-$(CONFIG_MPC8572) += ddr-gen3.o
COBJS-$(CONFIG_MPC8536) += ddr-gen3.o
COBJS-$(CONFIG_MPC8569)	+= ddr-gen3.o
COBJS-$(CONFIG_P1011)	+= ddr-gen3.o
COBJS-$(CONFIG_P1012)	+= ddr-gen3.o
COBJS-$(CONFIG_P1013)	+= ddr-gen3.o
COBJS-$(CONFIG_P1020)	+= ddr-gen3.o
COBJS-$(CONFIG_P1021)	+= ddr-gen3.o
COBJS-$(CONFIG_P1022)	+= ddr-gen3.o
COBJS-$(CONFIG_P2010)	+= ddr-gen3.o
COBJS-$(CONFIG_P2020)	+= ddr-gen3.o
COBJS-$(CONFIG_PPC_P4080)	+= ddr-gen3.o

COBJS-$(CONFIG_CPM2)	+= ether_fcc.o
COBJS-$(CONFIG_OF_LIBFDT) += fdt.o
COBJS-$(CONFIG_MP)	+= mp.o
COBJS-$(CONFIG_MPC8536) += mpc8536_serdes.o
COBJS-$(CONFIG_PCI)	+= pci.o
COBJS-$(CONFIG_QE)	+= qe_io.o
COBJS-$(CONFIG_CPM2)	+= serial_scc.o

COBJS	= $(COBJS-y)
COBJS	+= cpu.o
COBJS	+= cpu_init.o
COBJS	+= cpu_init_early.o
COBJS	+= interrupts.o
COBJS	+= speed.o
COBJS	+= tlb.o
COBJS	+= traps.o

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
