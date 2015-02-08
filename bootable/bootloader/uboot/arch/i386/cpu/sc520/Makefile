include $(TOPDIR)/config.mk

LIB	:= $(obj)lib$(SOC).a

COBJS-$(CONFIG_SYS_SC520) += sc520.o
COBJS-$(CONFIG_SYS_SC520_SSI) += sc520_ssi.o
COBJS-$(CONFIG_SYS_SC520_TIMER) += sc520_timer.o
COBJS-$(CONFIG_PCI) += sc520_pci.o

SOBJS-$(CONFIG_SYS_SC520) += sc520_asm.o

SRCS	:= $(SOBJS-y:.o=.S) $(COBJS-y:.o=.c)
OBJS	:= $(addprefix $(obj),$(SOBJS-y) $(COBJS-y))

all: $(obj).depend $(LIB)

$(LIB):	$(OBJS)
	$(AR) $(ARFLAGS) $@ $(OBJS)

#########################################################################

# defines $(obj).depend target
include $(SRCTREE)/rules.mk

sinclude $(obj).depend

#########################################################################