include $(TOPDIR)/config.mk

# CFLAGS += -DET_DEBUG

LIB	= $(obj)lib$(CPU).a

START-y	+= start.o
START-y	+= kgdb.o
COBJS-y	+= bedbug_860.o
COBJS-y	+= commproc.o
COBJS-y	+= cpu.o
COBJS-y	+= cpu_init.o
COBJS-y	+= fec.o
COBJS-$(CONFIG_OF_LIBFDT) += fdt.o
COBJS-y	+= i2c.o
COBJS-y	+= interrupts.o
COBJS-y	+= lcd.o
COBJS-y	+= scc.o
COBJS-y	+= serial.o
COBJS-y	+= speed.o
COBJS-y	+= spi.o
COBJS-y	+= traps.o
COBJS-y	+= upatch.o
COBJS-y	+= video.o
SOBJS-y	+= plprcr_write.o

SRCS	:= $(START-y:.o=.S) $(SOBJS-y:.o=.S) $(COBJS-y:.o=.c)
OBJS	:= $(addprefix $(obj),$(SOBJS-y) $(COBJS-y))
START	:= $(addprefix $(obj),$(START-y))

all:	$(obj).depend $(START) $(LIB)

$(LIB):	$(OBJS)
	$(AR) $(ARFLAGS) $@ $(OBJS) $(obj)kgdb.o

#########################################################################

# defines $(obj).depend target
include $(SRCTREE)/rules.mk

sinclude $(obj).depend

#########################################################################
