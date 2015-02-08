include $(TOPDIR)/config.mk

LIB	:= $(obj)libfpga.a

ifdef CONFIG_FPGA
COBJS-y += fpga.o
COBJS-$(CONFIG_FPGA_SPARTAN2) += spartan2.o
COBJS-$(CONFIG_FPGA_SPARTAN3) += spartan3.o
COBJS-$(CONFIG_FPGA_VIRTEX2) += virtex2.o
COBJS-$(CONFIG_FPGA_XILINX) += xilinx.o
ifdef CONFIG_FPGA_ALTERA
COBJS-y += altera.o
COBJS-$(CONFIG_FPGA_ACEX1K) += ACEX1K.o
COBJS-$(CONFIG_FPGA_CYCLON2) += cyclon2.o
COBJS-$(CONFIG_FPGA_STRATIX_II) += stratixII.o
endif
endif

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
