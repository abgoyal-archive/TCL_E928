include $(TOPDIR)/config.mk

SRCS	:= $(obj)crc32.c  fw_env.c  fw_env_main.c
HEADERS	:= fw_env.h

CPPFLAGS := -Wall -DUSE_HOSTCC -I$(SRCTREE)/include

ifeq ($(MTD_VERSION),old)
CPPFLAGS += -DMTD_OLD
endif

all:	$(obj)fw_printenv

$(obj)fw_printenv:	$(SRCS) $(HEADERS)
	$(CROSS_COMPILE)gcc $(CPPFLAGS) $(SRCS) -o $(obj)fw_printenv

clean:
	rm -f $(obj)fw_printenv $(obj)crc32.c

$(obj)crc32.c:
	ln -s $(src)../../lib/crc32.c $(obj)crc32.c

#########################################################################

include $(TOPDIR)/rules.mk

sinclude $(obj).depend

#########################################################################
