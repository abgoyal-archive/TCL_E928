
#ifndef I2C_EXPORT_H
#define I2C_EXPORT_H


typedef enum _i2c_status
{
 I2C_SUCCESS     = 0,
 I2C_ERROR,
} I2C_Status;

typedef enum _i2c_transaction_mode
{
	I2C_MASTER_RCV =  0,
	I2C_MASTER_XMIT = 1,
} I2C_TRANSACTION_MODE;

typedef enum _i2c_interrupt_mode
{
	I2C_INT_DISABLE =  0,
	I2C_INT_ENABLE = 1,
} I2C_INTERRUPT_MODE;

typedef enum _i2c_stop
{
	I2C_NO_STOP =  0,
	I2C_STOP = 1,
} I2C_STOP_MODE;

typedef enum _i2c_restart
{
	I2C_NO_RESTART =  0,
	I2C_RESTART = 1,
} I2C_RESTART_MODE;



extern I2C_Status I2C_Initialize(
	unsigned char addr,            /* driver's I2C slave address */
	I2C_INTERRUPT_MODE en_int,     /* 1 - enable I2C interrupt
					* 0 - disable I2C interrupt
					*/
	int (*app_print_function)(char *,...)); /* pointer to optional "printf"
						 * provided by application
						 */

extern I2C_Status I2C_do_transaction( I2C_INTERRUPT_MODE en_int,
				      I2C_TRANSACTION_MODE act,
				      unsigned char i2c_addr,
				      unsigned char data_addr,
				      int len,
				      char *buffer,
				      I2C_STOP_MODE stop,
				      int retry,
				      I2C_RESTART_MODE rsta);
#endif
