include $(TOPDIR)/config.mk

LIB	= $(obj)lib$(ARCH).a

SOBJS-y	+= ppccache.o
SOBJS-y	+= ppcstring.o
SOBJS-y	+= ticks.o
SOBJS-y	+= reloc.o

COBJS-y	+= bat_rw.o
COBJS-y	+= board.o
COBJS-y	+= bootm.o
COBJS-$(CONFIG_BOOTCOUNT_LIMIT) += bootcount.o
COBJS-y	+= cache.o
COBJS-y	+= extable.o
COBJS-y	+= interrupts.o
COBJS-$(CONFIG_CMD_KGDB) += kgdb.o
COBJS-y	+= time.o

SRCS	:= $(SOBJS-y:.o=.S) $(COBJS-y:.o=.c)
OBJS	:= $(addprefix $(obj),$(SOBJS-y) $(COBJS-y))

$(LIB):	$(obj).depend $(OBJS)
	@if ! $(CROSS_COMPILE)readelf -S $(OBJS) | grep -q '\.fixup.*PROGBITS';\
	then \
		echo "ERROR: Your compiler doesn't generate .fixup sections!";\
		echo "       Upgrade to a recent toolchain."; \
		exit 1; \
	fi;
	$(AR) $(ARFLAGS) $@ $(OBJS)

#########################################################################

# defines $(obj).depend target
include $(SRCTREE)/rules.mk

sinclude $(obj).depend

#########################################################################
