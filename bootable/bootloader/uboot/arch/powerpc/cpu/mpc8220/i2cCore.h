
#ifndef __INCi2ccoreh
#define __INCi2ccoreh
#ifndef __ASSEMBLY__
/* device types */
#define I2C_DEVICE_TYPE_EEPROM 0
#define I2C_EEPROM_ADRS 0xa0
#define I2C_CTRL_ADRS   I2C_EEPROM_ADRS
#define EEPROM_ADDR0    0xA2	/* on Dimm SPD eeprom */
#define EEPROM_ADDR1    0xA4	/* on Board SPD eeprom */
#define EEPROM_ADDR2    0xD2	/* non-standard eeprom - clock generator */
/* Control Register */
#define I2C_CTL_EN      0x80	/* I2C Enable                   */
#define I2C_CTL_IEN     0x40	/* I2C Interrupt Enable         */
#define I2C_CTL_STA     0x20	/* Master/Slave Mode select     */
#define I2C_CTL_TX      0x10	/* Transmit/Receive Mode Select */
#define I2C_CTL_TXAK    0x08	/* Transmit Acknowledge Enable  */
#define I2C_CTL_RSTA    0x04	/* Repeat Start                 */
/* Status Register */
#define I2C_STA_CF      0x80	/* Data Transfer       */
#define I2C_STA_AAS     0x40	/* Adressed As Slave   */
#define I2C_STA_BB      0x20	/* Bus Busy            */
#define I2C_STA_AL      0x10	/* Arbitration Lost    */
#define I2C_STA_SRW     0x04	/* Slave Read/Write    */
#define I2C_STA_IF      0x02	/* I2C Interrupt       */
#define I2C_STA_RXAK    0x01	/* Receive Acknowledge */
/* Interrupt Contol Register */
#define I2C_INT_BNBE2   0x80	/* Bus Not Busy Enable 2 */
#define I2C_INT_TE2     0x40	/* Transmit Enable 2     */
#define I2C_INT_RE2     0x20	/* Receive Enable 2      */
#define I2C_INT_IE2     0x10	/* Interrupt Enable 2    */
#define I2C_INT_BNBE1   0x08	/* Bus Not Busy Enable 1 */
#define I2C_INT_TE1     0x04	/* Transmit Enable 1     */
#define I2C_INT_RE1     0x02	/* Receive Enable 1      */
#define I2C_INT_IE1     0x01	/* Interrupt Enable 1    */
#define I2C_POLL_COUNT 0x100000
#define I2C_ENABLE      0x00000001
#define I2C_DISABLE     0x00000002
#define I2C_START       0x00000004
#define I2C_REPSTART    0x00000008
#define I2C_STOP        0x00000010
#define I2C_BITRATE     0x00000020
#define I2C_SLAVEADR    0x00000040
#define I2C_STARTADR    0x00000080
#undef TWOBYTES
typedef struct i2c_settings {
	/* Device settings */
	int bit_rate;		/* Device bit rate */
	u8 i2c_adr;		/* I2C address */
	u8 slv_adr;		/* Slave address */
#ifdef TWOBYTES
	u16 str_adr;		/* Start address */
#else
	u8 str_adr;		/* Start address */
#endif
	int xfer_size;		/* Transfer Size */

	int bI2c_en;		/* Enable or Disable */
	int cmdFlag;		/* I2c Command Flags */
} i2cset_t;

#endif /* __ASSEMBLY__ */

#endif /* __INCi2ccoreh */
