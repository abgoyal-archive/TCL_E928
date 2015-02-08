_depend:	$(obj).depend

$(obj).depend:	$(src)Makefile $(TOPDIR)/config.mk $(SRCS) $(HOSTSRCS)
		@rm -f $@
		@for f in $(SRCS); do \
			g=`basename $$f | sed -e 's/\(.*\)\.\w/\1.o/'`; \
			$(CC) -M $(CPPFLAGS) -MQ $(obj)$$g $$f >> $@ ; \
		done
		@for f in $(HOSTSRCS); do \
			g=`basename $$f | sed -e 's/\(.*\)\.\w/\1.o/'`; \
			$(HOSTCC) -M $(HOSTCPPFLAGS) -MQ $(obj)$$g $$f >> $@ ; \
		done

$(HOSTOBJS): $(obj)%.o: %.c
	$(HOSTCC) $(HOSTCFLAGS) $(HOSTCFLAGS_$(@F)) $(HOSTCFLAGS_$(BCURDIR)) -o $@ $< -c
$(NOPEDOBJS): $(obj)%.o: %.c
	$(HOSTCC) $(HOSTCFLAGS_NOPED) $(HOSTCFLAGS_$(@F)) $(HOSTCFLAGS_$(BCURDIR)) -o $@ $< -c

#########################################################################

include $(SRCTREE)/mtk-config.mk
