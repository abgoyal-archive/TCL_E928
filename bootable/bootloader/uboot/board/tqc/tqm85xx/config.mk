ifeq ($(CONFIG_TQM8548_BE),y)
TEXT_BASE = 0xfff80000
else
TEXT_BASE = 0xfffc0000
endif
