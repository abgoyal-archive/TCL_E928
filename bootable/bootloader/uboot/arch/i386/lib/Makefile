include $(TOPDIR)/config.mk

LIB	= $(obj)lib$(ARCH).a

SOBJS-y	+= bios.o
SOBJS-y	+= bios_pci.o
SOBJS-y	+= realmode_switch.o

COBJS-y	+= bios_setup.o
COBJS-y	+= board.o
COBJS-y	+= bootm.o
COBJS-y	+= interrupts.o
COBJS-$(CONFIG_SYS_PCAT_INTERRUPTS) += pcat_interrupts.o
COBJS-$(CONFIG_SYS_GENERIC_TIMER) += pcat_timer.o
COBJS-$(CONFIG_PCI) += pci.o
COBJS-$(CONFIG_PCI) += pci_type1.o
COBJS-y	+= realmode.o
COBJS-y	+= timer.o
COBJS-y	+= video_bios.o
COBJS-y	+= video.o
COBJS-y	+= zimage.o

SRCS	:= $(SOBJS-y:.o=.S) $(COBJS-y:.o=.c)
OBJS	:= $(addprefix $(obj),$(SOBJS-y) $(COBJS-y))

$(LIB):	$(obj).depend $(OBJS)
	$(AR) $(ARFLAGS) $@ $(OBJS)

#########################################################################

# defines $(obj).depend target
include $(SRCTREE)/rules.mk

sinclude $(obj).depend

#########################################################################
