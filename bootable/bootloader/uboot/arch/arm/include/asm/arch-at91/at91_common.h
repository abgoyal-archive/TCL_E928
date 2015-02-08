

#ifndef AT91_COMMON_H
#define AT91_COMMON_H

void at91_can_hw_init(void);
void at91_macb_hw_init(void);
void at91_serial_hw_init(void);
void at91_serial0_hw_init(void);
void at91_serial1_hw_init(void);
void at91_serial2_hw_init(void);
void at91_serial3_hw_init(void);
void at91_spi0_hw_init(unsigned long cs_mask);
void at91_spi1_hw_init(unsigned long cs_mask);
void at91_uhp_hw_init(void);

#endif /* AT91_COMMON_H */
