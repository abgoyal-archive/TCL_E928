include $(TOPDIR)/config.mk
ifneq ($(OBJTREE),$(SRCTREE))
$(shell mkdir -p $(obj)drivers/epic)
$(shell mkdir -p $(obj)drivers/i2c)
endif

LIB	= $(obj)lib$(CPU).a

START	= start.o
COBJS	= traps.o cpu.o cpu_init.o interrupts.o speed.o \
	  drivers/epic/epic1.o drivers/i2c/i2c.o pci.o
COBJS_LN = bedbug_603e.o

SRCS	:= $(START:.o=.S) $(SOBJS:.o=.S) $(COBJS:.o=.c) $(addprefix $(obj),$(COBJS_LN:.o=.c))
OBJS	:= $(addprefix $(obj),$(SOBJS) $(COBJS) $(COBJS_LN))
START	:= $(addprefix $(obj),$(START))

all:	$(obj).depend $(START) $(LIB)

$(LIB):	$(OBJS)
	$(AR) $(ARFLAGS) $@ $(OBJS)

$(obj)bedbug_603e.c:
	ln -sf $(src)../mpc8260/bedbug_603e.c $(obj)bedbug_603e.c

#########################################################################

# defines $(obj).depend target
include $(SRCTREE)/rules.mk

sinclude $(obj).depend

#########################################################################
