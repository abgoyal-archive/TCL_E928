include $(TOPDIR)/config.mk

LIB	= $(obj)lib$(BOARD).a

COBJS	:= voiceblue.o
SOBJS	:= setup.o

SRCS	:= $(SOBJS:.o=.S) $(COBJS:.o=.c)
OBJS	:= $(addprefix $(obj),$(COBJS))
SOBJS	:= $(addprefix $(obj),$(SOBJS))

LOAD_ADDR = 0x10400000

#########################################################################

all:	$(obj).depend $(LIB) $(obj)eeprom.srec $(obj)eeprom.bin

$(LIB):	$(OBJS) $(SOBJS)
	$(AR) $(ARFLAGS) $@ $^

$(obj)eeprom_start.o:
	echo "b eeprom" | $(CC) $(AFLAGS) -c -x assembler -o $@ -

$(obj)eeprom:		$(obj)eeprom_start.o $(obj)eeprom.o
	$(LD) -Ttext $(LOAD_ADDR) -e eeprom -o $@ $^ \
		-L$(obj)../../examples/standalone -lstubs \
		$(PLATFORM_LIBS)

$(obj)eeprom.srec:	$(obj)eeprom
	$(OBJCOPY) -S -O srec $(<:.o=) $@

$(obj)eeprom.bin:	$(obj)eeprom
	$(OBJCOPY) -S -O binary $< $@

clean:
	rm -f $(SOBJS) $(OBJS) $(obj)eeprom \
		$(obj)eeprom.srec $(obj)eeprom.bin \
		$(obj)eeprom.o $(obj)eeprom_start.o

distclean:	clean
	rm -f $(LIB) core *.bak $(obj).depend

#########################################################################

# defines $(obj).depend target
include $(SRCTREE)/rules.mk

sinclude $(obj).depend

#########################################################################
