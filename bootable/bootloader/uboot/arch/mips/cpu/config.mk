v=$(shell $(AS) --version | grep 'GNU assembler' | egrep -o '2\.[0-9\.]+' | cut -d. -f2)
MIPSFLAGS:=$(shell \
if [ "$v" -lt "14" ]; then \
	echo "-mcpu=4kc"; \
else \
	echo "-march=4kc -mtune=4kc"; \
fi)

ifneq (,$(findstring 4KCle,$(CROSS_COMPILE)))
ENDIANNESS = -EL
else
ENDIANNESS = -EB
endif

MIPSFLAGS += $(ENDIANNESS)

PLATFORM_CPPFLAGS += $(MIPSFLAGS)
