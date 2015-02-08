include $(TOPDIR)/config.mk

LIB = $(obj)libyaffs2.a

COBJS-$(CONFIG_YAFFS2) := \
	yaffscfg.o yaffs_ecc.o yaffsfs.o yaffs_guts.o yaffs_packedtags1.o \
	yaffs_tagscompat.o yaffs_packedtags2.o yaffs_tagsvalidity.o \
	yaffs_nand.o yaffs_checkptrw.o yaffs_qsort.o yaffs_mtdif.o \
	yaffs_mtdif2.o

SRCS    := $(COBJS-y:.o=.c)
OBJS    := $(addprefix $(obj),$(COBJS-y))

# -DCONFIG_YAFFS_NO_YAFFS1
CFLAGS +=    -DCONFIG_YAFFS_DIRECT -DCONFIG_YAFFS_SHORT_NAMES_IN_RAM -DCONFIG_YAFFS_YAFFS2 -DNO_Y_INLINE -DLINUX_VERSION_CODE=0x20622

all:  $(LIB)

$(LIB): $(obj).depend $(OBJS)
	$(AR) $(ARFLAGS) $@ $(OBJS)

.PHONY: clean distclean
clean:
	rm -f $(OBJS)

distclean:  clean
	rm -f $(LIB) core *.bak .depend

#########################################################################

# defines $(obj).depend target
include $(SRCTREE)/rules.mk

sinclude $(obj).depend

#########################################################################
