include $(TOPDIR)/config.mk

LIB	= $(obj)lib$(ARCH).a

SOBJS-y	+=

COBJS-y	+= board.o
COBJS-y	+= bootm.o
COBJS-y	+= time.o

SRCS	:= $(SOBJS-y:.o=.S) $(COBJS-y:.o=.c)
OBJS	:= $(addprefix $(obj),$(SOBJS-y) $(COBJS-y))

$(LIB):	$(obj).depend $(OBJS)
	$(AR) $(ARFLAGS) $@ $(OBJS)

#########################################################################

# defines $(obj).depend target
include $(SRCTREE)/rules.mk

sinclude $(obj).depend

#########################################################################
