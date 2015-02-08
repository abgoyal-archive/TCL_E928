include $(TOPDIR)/config.mk

LIB	:= $(obj)libspi.a

COBJS-$(CONFIG_ATMEL_DATAFLASH_SPI) += atmel_dataflash_spi.o
COBJS-$(CONFIG_ATMEL_SPI) += atmel_spi.o
COBJS-$(CONFIG_BFIN_SPI) += bfin_spi.o
COBJS-$(CONFIG_CF_SPI) += cf_spi.o
COBJS-$(CONFIG_DAVINCI_SPI) += davinci_spi.o
COBJS-$(CONFIG_KIRKWOOD_SPI) += kirkwood_spi.o
COBJS-$(CONFIG_MPC52XX_SPI) += mpc52xx_spi.o
COBJS-$(CONFIG_MPC8XXX_SPI) += mpc8xxx_spi.o
COBJS-$(CONFIG_MXC_SPI) += mxc_spi.o
COBJS-$(CONFIG_SOFT_SPI) += soft_spi.o

COBJS	:= $(COBJS-y)
SRCS	:= $(COBJS:.o=.c)
OBJS	:= $(addprefix $(obj),$(COBJS))

all:	$(LIB)

$(LIB):	$(obj).depend $(OBJS)
	$(AR) $(ARFLAGS) $@ $(OBJS)

#########################################################################

# defines $(obj).depend target
include $(SRCTREE)/rules.mk

sinclude $(obj).depend

#########################################################################
