include $(TOPDIR)/config.mk

LIB	:= $(obj)libspi_flash.a

COBJS-$(CONFIG_SPI_FLASH)	+= spi_flash.o
COBJS-$(CONFIG_SPI_FLASH_ATMEL)	+= atmel.o
COBJS-$(CONFIG_SPI_FLASH_MACRONIX)	+= macronix.o
COBJS-$(CONFIG_SPI_FLASH_SPANSION)	+= spansion.o
COBJS-$(CONFIG_SPI_FLASH_SST)	+= sst.o
COBJS-$(CONFIG_SPI_FLASH_STMICRO)	+= stmicro.o
COBJS-$(CONFIG_SPI_FLASH_WINBOND)	+= winbond.o
COBJS-$(CONFIG_SPI_M95XXX) += eeprom_m95xxx.o

COBJS	:= $(COBJS-y)
SRCS	:= $(COBJS:.o=.c)
OBJS	:= $(addprefix $(obj),$(COBJS))

all:	$(LIB)

$(LIB): $(obj).depend $(OBJS)
	$(AR) $(ARFLAGS) $@ $(OBJS)

#########################################################################

# defines $(obj).depend target
include $(SRCTREE)/rules.mk

sinclude $(obj).depend

#########################################################################
