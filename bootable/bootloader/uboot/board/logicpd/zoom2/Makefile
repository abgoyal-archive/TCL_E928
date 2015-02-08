include $(TOPDIR)/config.mk

LIB	= $(obj)lib$(BOARD).a

COBJS-y := $(BOARD).o
COBJS-y += debug_board.o
COBJS-y += zoom2_serial.o
COBJS-$(CONFIG_STATUS_LED) += led.o

COBJS	:= $(sort $(COBJS-y))
SRCS	:= $(COBJS:.o=.c)
OBJS	:= $(addprefix $(obj),$(COBJS))

$(LIB):	$(obj).depend $(OBJS)
	$(AR) $(ARFLAGS) $@ $(OBJS)

clean:
	rm -f $(OBJS)

distclean:	clean
	rm -f $(LIB) core *.bak $(obj).depend

#########################################################################

# defines $(obj).depend target
include $(SRCTREE)/rules.mk

sinclude $(obj).depend

#########################################################################
