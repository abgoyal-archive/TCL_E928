include $(TOPDIR)/config.mk

LIB	= $(obj)libgeneric.a

COBJS-$(CONFIG_ADDR_MAP) += addr_map.o
COBJS-$(CONFIG_BZIP2) += bzlib.o
COBJS-$(CONFIG_BZIP2) += bzlib_crctable.o
COBJS-$(CONFIG_BZIP2) += bzlib_decompress.o
COBJS-$(CONFIG_BZIP2) += bzlib_randtable.o
COBJS-$(CONFIG_BZIP2) += bzlib_huffman.o
COBJS-$(CONFIG_USB_TTY) += circbuf.o
COBJS-y += crc16.o
COBJS-y += crc32.o
COBJS-y += ctype.o
COBJS-y += display_options.o
COBJS-y += div64.o
COBJS-$(CONFIG_GZIP) += gunzip.o
COBJS-$(CONFIG_LMB) += lmb.o
COBJS-y += ldiv.o
COBJS-$(CONFIG_MD5) += md5.o
COBJS-y += net_utils.o
COBJS-$(CONFIG_SHA1) += sha1.o
COBJS-$(CONFIG_SHA256) += sha256.o
COBJS-y += string.o
COBJS-y	+= strmhz.o
COBJS-y += time.o
COBJS-y += vsprintf.o
COBJS-$(CONFIG_ZLIB) += zlib.o
COBJS-$(CONFIG_RBTREE)	+= rbtree.o

COBJS	:= $(COBJS-y)
SRCS	:= $(COBJS:.o=.c)
OBJS	:= $(addprefix $(obj),$(COBJS))

$(LIB):	$(obj).depend $(OBJS)
	$(AR) $(ARFLAGS) $@ $(OBJS)

#########################################################################

# defines $(obj).depend target
include $(SRCTREE)/rules.mk

sinclude $(obj).depend

#########################################################################
