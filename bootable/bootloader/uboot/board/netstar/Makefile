include $(TOPDIR)/config.mk

LIB	= $(obj)lib$(BOARD).a

COBJS	:= netstar.o
SOBJS	:= setup.o

SRCS	:= $(SOBJS:.o=.S) $(COBJS:.o=.c)
OBJS	:= $(addprefix $(obj),$(COBJS))
SOBJS	:= $(addprefix $(obj),$(SOBJS))

LOAD_ADDR = 0x10400000

#########################################################################

all:	$(obj).depend $(LIB) $(obj)eeprom.srec $(obj)eeprom.bin \
		$(obj)crcek.srec $(obj)crcek.bin $(obj)crcit

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

$(obj)crcek.srec:	$(obj)crcek.o
	$(LD) -g -Ttext 0x00000000 -e crcek -o $(<:.o=) $^
	$(OBJCOPY) -S -O srec $(<:.o=) $@

$(obj)crcek.bin:	$(obj)crcek.srec
	$(OBJCOPY) -I srec -O binary $< $@

$(obj)crcit:		$(obj)crcit.o $(obj)crc32.o
	$(HOSTCC) $(HOSTCFLAGS) -o $@ $^

$(obj)crcit.o:		crcit.c
	$(HOSTCC) $(HOSTCFLAGS) -o $@ -c $<

$(obj)crc32.o:		$(SRCTREE)/lib/crc32.c
	$(HOSTCC) $(HOSTCFLAGS) -DUSE_HOSTCC -I$(TOPDIR)/include \
		-o $@ -c $<

clean:
	rm -f $(SOBJS) $(OBJS) \
		$(obj)eeprom_start.o $(obj)eeprom.o \
		$(obj)eeprom $(obj)eeprom.srec 	$(obj)eeprom.bin \
		$(obj)crcek.o $(obj)crcek $(obj)crcek.srec $(obj)crcek.bin

distclean:	clean
	rm -f $(LIB) core *.bak $(obj).depend

#########################################################################

# defines $(obj).depend target
include $(SRCTREE)/rules.mk

sinclude $(obj).depend

#########################################################################
