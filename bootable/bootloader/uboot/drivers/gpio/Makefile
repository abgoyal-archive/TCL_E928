include $(TOPDIR)/config.mk

LIB 	:= $(obj)libgpio.a

COBJS-$(CONFIG_AT91_GPIO)	+= at91_gpio.o
COBJS-$(CONFIG_KIRKWOOD_GPIO)	+= kw_gpio.o
COBJS-$(CONFIG_MX31_GPIO)	+= mx31_gpio.o
COBJS-$(CONFIG_PCA953X)		+= pca953x.o
COBJS-$(CONFIG_S5PC1XX)		+= s5p_gpio.o

COBJS	:= $(COBJS-y)
SRCS 	:= $(COBJS:.o=.c)
OBJS 	:= $(addprefix $(obj),$(COBJS))

all:	$(LIB)

$(LIB):	$(obj).depend $(OBJS)
	$(AR) $(ARFLAGS) $@ $(OBJS)


#########################################################################

# defines $(obj).depend target
include $(SRCTREE)/rules.mk

sinclude $(obj).depend

########################################################################
