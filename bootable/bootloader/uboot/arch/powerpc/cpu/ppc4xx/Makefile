include $(TOPDIR)/config.mk

LIB	= $(obj)lib$(CPU).a

START	:= resetvec.o
START	+= start.o

SOBJS	:= cache.o
SOBJS	+= dcr.o
SOBJS	+= kgdb.o

COBJS	:= 40x_spd_sdram.o

COBJS	+= 44x_spd_ddr.o
COBJS	+= 44x_spd_ddr2.o
ifdef CONFIG_PPC4xx_DDR_AUTOCALIBRATION
COBJS	+= 4xx_ibm_ddr2_autocalib.o
endif
COBJS	+= 4xx_pci.o
COBJS	+= 4xx_pcie.o
COBJS	+= bedbug_405.o
ifdef CONFIG_CMD_CHIP_CONFIG
COBJS	+= cmd_chip_config.o
endif
COBJS	+= commproc.o
COBJS	+= cpu.o
COBJS	+= cpu_init.o
COBJS	+= denali_data_eye.o
COBJS	+= denali_spd_ddr2.o
COBJS	+= ecc.o
COBJS	+= fdt.o
COBJS	+= interrupts.o
COBJS	+= iop480_uart.o
ifdef CONFIG_CMD_REGINFO
COBJS	+= reginfo.o
endif
COBJS	+= sdram.o
COBJS	+= speed.o
COBJS	+= tlb.o
COBJS	+= traps.o
COBJS	+= usb.o
COBJS	+= usb_ohci.o
COBJS	+= usbdev.o
ifndef CONFIG_XILINX_440
COBJS	+= 4xx_uart.o
COBJS	+= gpio.o
COBJS	+= miiphy.o
COBJS	+= uic.o
else
COBJS	+= xilinx_irq.o
endif

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
