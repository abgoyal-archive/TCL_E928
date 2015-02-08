include $(TOPDIR)/config.mk

LIB	:= $(obj)lib$(SOC).a

COBJS	:= portmux.o clk.o
SRCS	:= $(SOBJS:.o=.S) $(COBJS:.o=.c)
OBJS	:= $(addprefix $(obj),$(SOBJS) $(COBJS))

all: $(obj).depend $(LIB)

$(LIB): $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

#########################################################################

# defines $(obj).depend target
include $(SRCTREE)/rules.mk

sinclude $(obj).depend

#########################################################################
