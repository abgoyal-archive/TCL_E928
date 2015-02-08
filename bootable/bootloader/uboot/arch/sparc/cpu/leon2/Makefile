include $(TOPDIR)/config.mk

LIB	= $(obj)lib$(CPU).a

START	= start.o
SOBJS	=
COBJS	= cpu_init.o serial.o cpu.o interrupts.o prom.o

SRCS	:= $(START:.o=.S) $(SOBJS:.o=.S) $(COBJS:.o=.c)
OBJS	:= $(addprefix $(obj),$(SOBJS) $(COBJS))
START	:= $(addprefix $(obj),$(START))

all:	$(obj).depend $(START) $(LIB)

$(LIB):	$(OBJS)
	$(AR) $(ARFLAGS) $@ $(OBJS)

#########################################################################

# defines $(obj).depend target
include $(SRCTREE)/rules.mk

$(START): $(START:.o=.S)
	$(CC) -D__ASSEMBLY__ $(DBGFLAGS) $(OPTFLAGS) -D__KERNEL__ -DTEXT_BASE=$(TEXT_BASE) \
	-I$(TOPDIR)/include -fno-builtin -ffreestanding -nostdinc -isystem $(gccincdir) -pipe \
	$(PLATFORM_CPPFLAGS) -Wall -Wstrict-prototypes \
	-I$(TOPDIR)/board -c -o $(START) $(START:.o=.S)

sinclude $(obj).depend

#########################################################################
