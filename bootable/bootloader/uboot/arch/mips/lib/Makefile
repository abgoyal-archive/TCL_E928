include $(TOPDIR)/config.mk

LIB	= $(obj)lib$(ARCH).a

SOBJS-y	+=

COBJS-y	+= board.o
ifeq ($(CONFIG_QEMU_MIPS),y)
COBJS-y	+= bootm_qemu_mips.o
else
COBJS-y	+= bootm.o
endif
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
