include $(TOPDIR)/config.mk

LIB	:= $(obj)libphy.a

COBJS-$(CONFIG_BITBANGMII) += miiphybb.o
COBJS-$(CONFIG_MV88E61XX_SWITCH) += mv88e61xx.o

COBJS	:= $(COBJS-y)
SRCS	:= $(COBJS:.o=.c)
OBJS	:= $(addprefix $(obj),$(COBJS))

all:	$(LIB)

$(LIB):	$(obj).depend $(OBJS)
	$(AR) $(ARFLAGS) $@ $(OBJS)

#########################################################################

# defines $(obj).depend target
include $(SRCTREE)/rules.mk

sinclude $(obj).depend

#########################################################################
