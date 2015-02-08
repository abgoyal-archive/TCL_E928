CROSS_COMPILE ?= avr32-linux-

STANDALONE_LOAD_ADDR = 0x00000000

PLATFORM_RELFLAGS	+= -ffixed-r5 -fPIC -mno-init-got -mrelax
PLATFORM_LDFLAGS	+= --relax
