include $(TOPDIR)/config.mk

LIB	= $(obj)lib$(SOC).a

COBJS-y				+= cpu.o timer.o psc.o
COBJS-$(CONFIG_SOC_DM355)	+= dm355.o
COBJS-$(CONFIG_SOC_DM365)	+= dm365.o
COBJS-$(CONFIG_SOC_DM644X)	+= dm644x.o
COBJS-$(CONFIG_SOC_DM646X)	+= dm646x.o
COBJS-$(CONFIG_DRIVER_TI_EMAC)	+= lxt972.o dp83848.o

SOBJS	= reset.o

ifndef CONFIG_SKIP_LOWLEVEL_INIT
SOBJS	+= lowlevel_init.o
endif

SRCS	:= $(START:.o=.S) $(SOBJS:.o=.S) $(COBJS-y:.o=.c)
OBJS	:= $(addprefix $(obj),$(COBJS-y) $(SOBJS))
START	:= $(addprefix $(obj),$(START))

all:	$(obj).depend $(LIB)

$(LIB):	$(OBJS)
	$(AR) $(ARFLAGS) $@ $(OBJS)

#########################################################################

# defines $(obj).depend target
include $(SRCTREE)/rules.mk

sinclude $(obj).depend

#########################################################################
