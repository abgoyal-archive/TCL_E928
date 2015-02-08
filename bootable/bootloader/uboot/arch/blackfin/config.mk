CROSS_COMPILE ?= bfin-uclinux-

STANDALONE_LOAD_ADDR = 0x1000 -m elf32bfin

CONFIG_BFIN_CPU := $(strip $(subst ",,$(CONFIG_BFIN_CPU)))
CONFIG_BFIN_BOOT_MODE := $(strip $(subst ",,$(CONFIG_BFIN_BOOT_MODE)))
CONFIG_ENV_OFFSET := $(strip $(subst ",,$(CONFIG_ENV_OFFSET)))
CONFIG_ENV_SIZE := $(strip $(subst ",,$(CONFIG_ENV_SIZE)))

PLATFORM_RELFLAGS += -ffixed-P3 -fomit-frame-pointer -mno-fdpic
PLATFORM_CPPFLAGS += -DCONFIG_BLACKFIN

LDFLAGS += --gc-sections -m elf32bfin
PLATFORM_RELFLAGS += -ffunction-sections -fdata-sections

ifneq (,$(CONFIG_BFIN_CPU))
PLATFORM_RELFLAGS += -mcpu=$(CONFIG_BFIN_CPU)
endif

ifneq ($(CONFIG_BFIN_BOOT_MODE),BFIN_BOOT_BYPASS)
ALL += $(obj)u-boot.ldr
endif
ifeq ($(CONFIG_ENV_IS_EMBEDDED_IN_LDR),y)
CREATE_LDR_ENV = $(obj)tools/envcrc --binary > $(obj)env-ldr.o
else
CREATE_LDR_ENV =
endif

SYM_PREFIX = _

LDR_FLAGS-y :=
LDR_FLAGS-$(CONFIG_BFIN_BOOTROM_USES_EVT1) += -J

LDR_FLAGS += --bmode $(subst BFIN_BOOT_,,$(CONFIG_BFIN_BOOT_MODE))
LDR_FLAGS += --use-vmas
LDR_FLAGS += --initcode $(obj)$(CPUDIR)/initcode.o
ifneq ($(CONFIG_BFIN_BOOT_MODE),BFIN_BOOT_UART)
LDR_FLAGS-$(CONFIG_ENV_IS_EMBEDDED_IN_LDR) += \
	--punchit $$(($(CONFIG_ENV_OFFSET))):$$(($(CONFIG_ENV_SIZE))):$(obj)env-ldr.o
endif
ifneq (,$(findstring s,$(MAKEFLAGS)))
LDR_FLAGS += --quiet
endif

LDR_FLAGS += $(LDR_FLAGS-y)

ifeq ($(wildcard $(TOPDIR)/board/$(BOARD)/u-boot.lds*),)
LDSCRIPT = $(obj)arch/$(ARCH)/lib/u-boot.lds.S
endif
