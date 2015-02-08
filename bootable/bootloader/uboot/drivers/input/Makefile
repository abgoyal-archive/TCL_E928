include $(TOPDIR)/config.mk

LIB	:= $(obj)libinput.a

COBJS-$(CONFIG_I8042_KBD) += i8042.o
ifdef CONFIG_PS2KBD
COBJS-y += keyboard.o pc_keyb.o
COBJS-$(CONFIG_PS2MULT) += ps2mult.o ps2ser.o
endif

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
