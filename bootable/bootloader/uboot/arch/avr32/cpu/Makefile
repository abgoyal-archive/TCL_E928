include $(TOPDIR)/config.mk

LIB	:= $(obj)lib$(CPU).a

START-y			+= start.o

COBJS-y			+= cpu.o
COBJS-$(CONFIG_SYS_HSDRAMC) += hsdramc.o
COBJS-y			+= exception.o
COBJS-y			+= cache.o
COBJS-y			+= interrupts.o
COBJS-$(CONFIG_PORTMUX_PIO) += portmux-pio.o
COBJS-$(CONFIG_PORTMUX_GPIO) += portmux-gpio.o

SRCS	:= $(START-y:.o=.S) $(SOBJS-y:.o=.S) $(COBJS-y:.o=.c)
OBJS	:= $(addprefix $(obj),$(SOBJS-y) $(COBJS-y))
START	:= $(addprefix $(obj),$(START-y))

all: $(obj).depend $(START) $(LIB)

$(LIB): $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

#########################################################################

# defines $(obj).depend target
include $(SRCTREE)/rules.mk

sinclude $(obj).depend

#########################################################################
