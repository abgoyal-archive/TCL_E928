include $(TOPDIR)/config.mk

LIB = $(obj)lib$(SOC).a

COBJS   = cpu.o led.o speed.o timer.o
SOBJS   = lowlevel_init.o

SRCS    := $(SOBJS:.o=.S) $(COBJS:.o=.c)
OBJS    := $(addprefix $(obj),$(SOBJS) $(COBJS))

all:    $(obj).depend $(LIB)

$(LIB): $(OBJS)
	$(AR) $(ARFLAGS) $@ $(OBJS)

#########################################################################

# defines $(obj).depend target
include $(SRCTREE)/rules.mk

sinclude $(obj).depend

#########################################################################
