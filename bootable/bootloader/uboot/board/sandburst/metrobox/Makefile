include $(TOPDIR)/config.mk
ifneq ($(OBJTREE),$(SRCTREE))
$(shell mkdir -p $(obj)../common)
endif

# TBS: add for debugging purposes
BUILDUSER := $(shell whoami)
FORCEBUILD := $(shell rm -f $(LIB) $(BOARD).o)

CFLAGS += -DBUILDUSER='"$(BUILDUSER)"'
# TBS: end debugging


LIB	= $(obj)lib$(BOARD).a

COBJS	= $(BOARD).o ../common/flash.o ../common/ppc440gx_i2c.o \
	../common/sb_common.o
SOBJS	= init.o

SRCS	:= $(SOBJS:.o=.S) $(COBJS:.o=.c)
OBJS	:= $(addprefix $(obj),$(COBJS))
SOBJS	:= $(addprefix $(obj),$(SOBJS))

$(LIB):	$(OBJS) $(SOBJS)
	$(AR) $(ARFLAGS) $@ $(OBJS)

clean:
	rm -f $(SOBJS) $(OBJS)

distclean:	clean
	rm -f $(LIB) core *.bak $(obj).depend

#########################################################################

# defines $(obj).depend target
include $(SRCTREE)/rules.mk

sinclude $(obj).depend

#########################################################################
