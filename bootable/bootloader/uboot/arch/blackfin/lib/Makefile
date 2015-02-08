include $(TOPDIR)/config.mk

CFLAGS += -DBFIN_BOARD_NAME='"$(BOARD)"'

LIB	= $(obj)lib$(ARCH).a

SOBJS-y	+= ins.o
SOBJS-y	+= memcmp.o
SOBJS-y	+= memcpy.o
SOBJS-y	+= memmove.o
SOBJS-y	+= memset.o
SOBJS-y	+= outs.o
SOBJS-$(CONFIG_CMD_KGDB) += __kgdb.o

COBJS-y	+= board.o
COBJS-y	+= boot.o
COBJS-y	+= cache.o
COBJS-y	+= clocks.o
COBJS-$(CONFIG_CMD_CACHE_DUMP) += cmd_cache_dump.o
COBJS-$(CONFIG_CMD_KGDB) += kgdb.o
COBJS-y	+= muldi3.o
COBJS-$(CONFIG_POST) += post.o tests.o
COBJS-y	+= string.o

SRCS	:= $(SOBJS-y:.o=.S) $(COBJS-y:.o=.c)
OBJS	:= $(addprefix $(obj),$(SOBJS-y) $(COBJS-y))

$(LIB):	$(obj).depend $(OBJS)
	$(AR) $(ARFLAGS) $@ $(OBJS)

#########################################################################

# defines $(obj).depend target
include $(SRCTREE)/rules.mk

sinclude $(obj).depend

#########################################################################
