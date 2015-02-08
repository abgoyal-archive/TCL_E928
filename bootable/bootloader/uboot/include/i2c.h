

#ifndef _I2C_H_
#define _I2C_H_


#define I2C_RXTX_LEN	128	/* maximum tx/rx buffer length */

#if defined(CONFIG_I2C_MULTI_BUS)
#if !defined(CONFIG_SYS_MAX_I2C_BUS)
#define CONFIG_SYS_MAX_I2C_BUS		2
#endif
#define I2C_GET_BUS()		i2c_get_bus_num()
#define I2C_SET_BUS(a)		i2c_set_bus_num(a)
#else
#define CONFIG_SYS_MAX_I2C_BUS		1
#define I2C_GET_BUS()		0
#define I2C_SET_BUS(a)
#endif

/* define the I2C bus number for RTC and DTT if not already done */
#if !defined(CONFIG_SYS_RTC_BUS_NUM)
#define CONFIG_SYS_RTC_BUS_NUM		0
#endif
#if !defined(CONFIG_SYS_DTT_BUS_NUM)
#define CONFIG_SYS_DTT_BUS_NUM		0
#endif
#if !defined(CONFIG_SYS_SPD_BUS_NUM)
#define CONFIG_SYS_SPD_BUS_NUM		0
#endif

#ifndef I2C_SOFT_DECLARATIONS
# if defined(CONFIG_MPC8260)
#  define I2C_SOFT_DECLARATIONS volatile ioport_t *iop = ioport_addr((immap_t *)CONFIG_SYS_IMMR, I2C_PORT);
# elif defined(CONFIG_8xx)
#  define I2C_SOFT_DECLARATIONS	volatile immap_t *immr = (immap_t *)CONFIG_SYS_IMMR;

# elif (defined(CONFIG_AT91RM9200) || \
	defined(CONFIG_AT91SAM9260) ||  defined(CONFIG_AT91SAM9261) || \
	defined(CONFIG_AT91SAM9263)) && !defined(CONFIG_AT91_LEGACY)
#  define I2C_SOFT_DECLARATIONS	at91_pio_t *pio	= (at91_pio_t *) AT91_PIO_BASE;
# else
#  define I2C_SOFT_DECLARATIONS
# endif
#endif

#ifdef CONFIG_8xx
#ifndef	CONFIG_SYS_I2C_SPEED
#define	CONFIG_SYS_I2C_SPEED	50000
#endif
#endif

#ifndef	CONFIG_SYS_I2C_SLAVE
#define	CONFIG_SYS_I2C_SLAVE	0xfe
#endif

void i2c_init(int speed, int slaveaddr);
#ifdef CONFIG_SYS_I2C_INIT_BOARD
void i2c_init_board(void);
#endif
#ifdef CONFIG_SYS_I2C_BOARD_LATE_INIT
void i2c_board_late_init(void);
#endif

#if defined(CONFIG_I2C_MUX)

typedef struct _mux {
	uchar	chip;
	uchar	channel;
	char	*name;
	struct _mux	*next;
} I2C_MUX;

typedef struct _mux_device {
	int	busid;
	I2C_MUX	*mux;	/* List of muxes, to reach the device */
	struct _mux_device	*next;
} I2C_MUX_DEVICE;

I2C_MUX_DEVICE	*i2c_mux_search_device(int id);
I2C_MUX_DEVICE *i2c_mux_ident_muxstring (uchar *buf);
int i2x_mux_select_mux(int bus);
int i2c_mux_ident_muxstring_f (uchar *buf);
#endif

int i2c_probe(uchar chip);

int i2c_read(uchar chip, uint addr, int alen, uchar *buffer, int len);
int i2c_write(uchar chip, uint addr, int alen, uchar *buffer, int len);

static inline u8 i2c_reg_read(u8 addr, u8 reg)
{
	u8 buf;

#ifdef CONFIG_8xx
	/* MPC8xx needs this.  Maybe one day we can get rid of it. */
	i2c_init(CONFIG_SYS_I2C_SPEED, CONFIG_SYS_I2C_SLAVE);
#endif

#ifdef DEBUG
	printf("%s: addr=0x%02x, reg=0x%02x\n", __func__, addr, reg);
#endif

	i2c_read(addr, reg, 1, &buf, 1);

	return buf;
}

static inline void i2c_reg_write(u8 addr, u8 reg, u8 val)
{
#ifdef CONFIG_8xx
	/* MPC8xx needs this.  Maybe one day we can get rid of it. */
	i2c_init(CONFIG_SYS_I2C_SPEED, CONFIG_SYS_I2C_SLAVE);
#endif

#ifdef DEBUG
	printf("%s: addr=0x%02x, reg=0x%02x, val=0x%02x\n",
	       __func__, addr, reg, val);
#endif

	i2c_write(addr, reg, 1, &val, 1);
}


int i2c_set_bus_num(unsigned int bus);


unsigned int i2c_get_bus_num(void);

int i2c_set_bus_speed(unsigned int);


unsigned int i2c_get_bus_speed(void);

#endif	/* _I2C_H_ */
