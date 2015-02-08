

#ifndef _I2C_H_
#define _I2C_H_

#include <common.h>

extern int	i2c_read_byte	(u8 *		data,
				 u8		dev,
				 u8 offset);

extern unsigned int i2c_reset (void);


#endif
