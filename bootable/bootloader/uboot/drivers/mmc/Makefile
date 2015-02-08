include $(TOPDIR)/config.mk

LIB	:= $(obj)libmmc.a

COBJS-$(CONFIG_GENERIC_MMC) += mmc.o
COBJS-$(CONFIG_ATMEL_MCI) += atmel_mci.o
COBJS-$(CONFIG_BFIN_SDH) += bfin_sdh.o
COBJS-$(CONFIG_OMAP3_MMC) += omap3_mmc.o
COBJS-$(CONFIG_FSL_ESDHC) += fsl_esdhc.o
COBJS-$(CONFIG_MXC_MMC) += mxcmmc.o
COBJS-$(CONFIG_PXA_MMC) += pxa_mmc.o

COBJS	:= $(COBJS-y)
SRCS	:= $(COBJS:.o=.c)
OBJS	:= $(addprefix $(obj),$(COBJS))

all:	$(LIB)

$(LIB): $(obj).depend $(OBJS)
	$(AR) $(ARFLAGS) $@ $(OBJS)

#########################################################################

# defines $(obj).depend target
include $(SRCTREE)/rules.mk

sinclude $(obj).depend

#########################################################################
