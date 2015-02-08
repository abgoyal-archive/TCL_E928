include $(TOPDIR)/config.mk

LIB	:= $(obj)libdma.a

COBJS-$(CONFIG_FSLDMAFEC) += MCD_tasksInit.o MCD_dmaApi.o MCD_tasks.o
COBJS-$(CONFIG_FSL_DMA) += fsl_dma.o

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
