include $(TOPDIR)/config.mk

LIB	= $(obj)lib$(CPU).a

START	= start.o

SOBJS-y += cache.o
SOBJS-$(CONFIG_MP) += release.o

COBJS-y	+= cpu.o
COBJS-y	+= cpu_init.o
# 8610 & 8641 are identical w/regards to DDR
COBJS-$(CONFIG_MPC8610) += ddr-8641.o
COBJS-$(CONFIG_MPC8641) += ddr-8641.o
COBJS-$(CONFIG_OF_LIBFDT) += fdt.o
COBJS-y	+= interrupts.o
COBJS-$(CONFIG_MP) += mp.o
COBJS-y	+= speed.o
COBJS-y	+= traps.o

SRCS	:= $(START:.o=.S) $(SOBJS-y:.o=.S) $(COBJS-y:.o=.c)
OBJS	:= $(addprefix $(obj),$(SOBJS-y) $(COBJS-y))
START	:= $(addprefix $(obj),$(START))

all:	$(obj).depend $(START) $(LIB)

$(LIB):	$(OBJS)
	$(AR) $(ARFLAGS) $@ $(ASOBJS) $(OBJS)

#########################################################################

# defines $(obj).depend target
include $(SRCTREE)/rules.mk

sinclude $(obj).depend

#########################################################################
