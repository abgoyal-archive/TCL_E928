include $(TOPDIR)/config.mk

LIB	= $(obj)lib$(BOARD).a

COBJS	:= trab.o flash.o vfd.o cmd_trab.o memory.o tsc2000.o auto_update.o
SOBJS	:= lowlevel_init.o

COBJS_FKT := trab_fkt.o rs485.o tsc2000.o

SRCS	:= $(SOBJS:.o=.S) $(COBJS:.o=.c) $(COBJS_FKT:.o=.c)
OBJS	:= $(addprefix $(obj),$(COBJS))
SOBJS	:= $(addprefix $(obj),$(SOBJS))

OBJS_FKT := $(addprefix $(obj),$(COBJS_FKT))

LOAD_ADDR = 0xc100000

#########################################################################

all:	$(LIB) $(obj)trab_fkt.srec $(obj)trab_fkt.bin

$(LIB):	$(obj).depend $(OBJS) $(SOBJS)
	$(AR) $(ARFLAGS) $@ $(OBJS) $(SOBJS)

$(obj)trab_fkt.srec:	$(OBJS_FKT) $(LIB)
	$(LD) -g -Ttext $(LOAD_ADDR) -o $(<:.o=) -e trab_fkt $^ $(LIB) \
		-L$(obj)../../examples/standalone -lstubs \
		-L$(obj)../../lib -lgeneric \
		$(PLATFORM_LIBS)
	$(OBJCOPY) -O srec $(<:.o=) $@

$(obj)trab_fkt.bin:	$(obj)trab_fkt.srec
	$(OBJCOPY) -I srec -O binary $< $@

clean:
	rm -f $(SOBJS) $(OBJS) $(OBJS_FKT)

distclean:	clean
	rm -f $(LIB) core *.bak $(obj).depend

#########################################################################

# defines $(obj).depend target
include $(SRCTREE)/rules.mk

sinclude $(obj).depend

#########################################################################
