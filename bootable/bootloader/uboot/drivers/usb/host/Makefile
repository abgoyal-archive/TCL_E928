include $(TOPDIR)/config.mk

LIB	:= $(obj)libusb_host.a

# ohci
COBJS-$(CONFIG_USB_OHCI_NEW) += ohci-hcd.o
COBJS-$(CONFIG_USB_ATMEL) += ohci-at91.o
COBJS-$(CONFIG_USB_ISP116X_HCD) += isp116x-hcd.o
COBJS-$(CONFIG_USB_R8A66597_HCD) += r8a66597-hcd.o
COBJS-$(CONFIG_USB_S3C64XX) += s3c64xx-hcd.o
COBJS-$(CONFIG_USB_SL811HS) += sl811-hcd.o

# echi
COBJS-$(CONFIG_USB_EHCI) += ehci-hcd.o
COBJS-$(CONFIG_USB_EHCI_FSL) += ehci-fsl.o
COBJS-$(CONFIG_USB_EHCI_PPC4XX) += ehci-ppc4xx.o
COBJS-$(CONFIG_USB_EHCI_IXP4XX) += ehci-ixp.o
COBJS-$(CONFIG_USB_EHCI_KIRKWOOD) += ehci-kirkwood.o
COBJS-$(CONFIG_USB_EHCI_PCI) += ehci-pci.o
COBJS-$(CONFIG_USB_EHCI_VCT) += ehci-vct.o

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
