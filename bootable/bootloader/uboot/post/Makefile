include $(TOPDIR)/config.mk
include $(OBJTREE)/include/autoconf.mk

LIB				= libpost.a
GPLIB-$(CONFIG_HAS_POST)	+= libgenpost.a
COBJS-$(CONFIG_HAS_POST)	+= post.o tests.o

SPLIB-$(CONFIG_HAS_POST) = drivers/libpostdrivers.a
SPLIB-$(CONFIG_HAS_POST) += $(shell if [ -d lib_$(ARCH) ]; then echo \
			    "lib_$(ARCH)/libpost$(ARCH).a"; fi)
SPLIB-$(CONFIG_HAS_POST) += $(shell if [ -d lib_$(ARCH)/fpu ]; then echo \
			    "lib_$(ARCH)/fpu/libpost$(ARCH)fpu.a"; fi)
SPLIB-$(CONFIG_HAS_POST) += $(shell if [ -d cpu/$(CPU) ]; then echo \
			    "cpu/$(CPU)/libpost$(CPU).a"; fi)
SPLIB-$(CONFIG_HAS_POST) += $(shell if [ -d board/$(BOARD) ]; then echo \
			    "board/$(BOARD)/libpost$(BOARD).a"; fi)

GPLIB	:= $(addprefix $(obj),$(GPLIB-y))
SPLIB	:= $(addprefix $(obj),$(SPLIB-y))
COBJS	:= $(COBJS-y)
SRCS	:= $(SOBJS:.o=.S) $(COBJS:.o=.c)
OBJS	:= $(addprefix $(obj),$(COBJS))
LIB	:= $(obj)$(LIB)

all:	$(LIB)

postdeps:
	@for lib in $(SPLIB-y) ; do \
		$(MAKE) -C `dirname $$lib` all ; \
	done

# generic POST library
$(GPLIB): $(obj).depend $(OBJS)
	$(AR) $(ARFLAGS) $@ $(OBJS)

# specific POST libraries
$(SPLIB): $(obj).depend postdeps
	$(MAKE) -C $(dir $(subst $(obj),,$@))

# the POST lib archive
$(LIB): $(GPLIB) $(SPLIB)
	(echo create $(LIB); for lib in $(GPLIB) $(SPLIB) ; \
	 do echo addlib $$lib; done; echo save) \
	| $(AR) -M

#########################################################################

# defines $(obj).depend target
include $(SRCTREE)/rules.mk

sinclude $(obj).depend

#########################################################################
