include $(TOPDIR)/config.mk

LIB	= $(obj)lib$(BOARD).a

COBJS	:= $(BOARD).o fpga.o

SRCS    := $(SOBJS:.o=.S) $(COBJS:.o=.c)
OBJS    := $(addprefix $(obj),$(COBJS))
SOBJS   := $(addprefix $(obj),$(SOBJS))

$(LIB): $(obj).depend $(OBJS)
	        $(AR) $(ARFLAGS) $@ $(OBJS)
	@mkimage -T script -C none -n mvSMR_Script -d bootscript $(obj)bootscript.img

clean:
	rm -f $(SOBJS) $(OBJS)

distclean:	clean
	rm -f $(LIB) core *.bak $(obj).depend $(obj)bootscript.img

#########################################################################

include $(SRCTREE)/rules.mk

sinclude $(obj).depend
