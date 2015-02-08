include $(TOPDIR)/config.mk

$(shell mkdir -p $(OBJTREE)/board/freescale/common)

LIB	= $(obj)lib$(CPU).a

START	= start.o
COBJS-y	:= cpu.o
COBJS-y	+= traps.o
COBJS-y += common.o
COBJS-y += cpu_init.o
COBJS-y += fixed_sdram.o
COBJS-y += i2c.o
COBJS-y += interrupts.o
COBJS-y += iopin.o
COBJS-y += serial.o
COBJS-y += speed.o
COBJS-$(CONFIG_FSL_DIU_FB) += diu.o
COBJS-$(CONFIG_FSL_DIU_FB) += ../../../../board/freescale/common/fsl_diu_fb.o
COBJS-$(CONFIG_FSL_DIU_FB) += ../../../../board/freescale/common/fsl_logo_bmp.o
COBJS-$(CONFIG_CMD_IDE) += ide.o
COBJS-$(CONFIG_IIM) += iim.o
COBJS-$(CONFIG_PCI) += pci.o

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
