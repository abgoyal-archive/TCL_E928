

#ifndef __KUP_H
#define __KUP_H

#define PA_8       0x0080
#define PA_11      0x0010
#define PA_12      0x0008

#define PB_14      0x00020000
#define PB_17      0x00004000

#define PC_9       0x0040

#define PA_RS485                 PA_11   /* SCC1: 0=RS232 1=RS485 */
#define PA_LED_YELLOW            PA_8
#define BP_USB_VCC               PB_14   /* VCC for USB devices 0=vcc on, 1=vcc off*/
#define PB_LCD_PWM	         PB_17	 /* PB 17 */
#define PC_SWITCH1               PC_9    /* Reboot switch */

extern void poweron_key (void);

extern void load_sernum_ethaddr(void);

#endif	/* __KUP_H */
