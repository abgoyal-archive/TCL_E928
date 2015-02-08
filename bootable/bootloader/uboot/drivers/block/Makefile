include $(TOPDIR)/config.mk

LIB	:= $(obj)libblock.a

COBJS-$(CONFIG_ATA_PIIX) += ata_piix.o
COBJS-$(CONFIG_CMD_MG_DISK) += mg_disk.o
COBJS-$(CONFIG_FSL_SATA) += fsl_sata.o
COBJS-$(CONFIG_IDE_SIL680) += sil680.o
COBJS-$(CONFIG_LIBATA) += libata.o
COBJS-$(CONFIG_PATA_BFIN) += pata_bfin.o
COBJS-$(CONFIG_SATA_DWC) += sata_dwc.o
COBJS-$(CONFIG_SATA_SIL3114) += sata_sil3114.o
COBJS-$(CONFIG_SCSI_AHCI) += ahci.o
COBJS-$(CONFIG_SCSI_SYM53C8XX) += sym53c8xx.o
COBJS-$(CONFIG_SYSTEMACE) += systemace.o

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
