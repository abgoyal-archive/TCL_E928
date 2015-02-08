subdirs-$(CONFIG_CMD_CRAMFS) := cramfs
subdirs-$(CONFIG_CMD_EXT2) += ext2
subdirs-$(CONFIG_CMD_FAT) += fat
subdirs-$(CONFIG_CMD_FDOS) += fdos
subdirs-$(CONFIG_CMD_JFFS2) += jffs2
subdirs-$(CONFIG_CMD_REISER) += reiserfs
subdirs-$(CONFIG_YAFFS2) += yaffs2
subdirs-$(CONFIG_CMD_UBIFS) += ubifs

SUBDIRS	:= $(subdirs-y)

$(obj).depend all:
	@for dir in $(SUBDIRS) ; do \
		$(MAKE) -C $$dir $@ ; done
