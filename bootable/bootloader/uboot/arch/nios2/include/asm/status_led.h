
#ifndef __ASM_STATUS_LED_H__
#define __ASM_STATUS_LED_H__

typedef unsigned led_id_t;
extern void __led_init (led_id_t mask, int state);
extern void __led_set (led_id_t mask, int state);
inline void __led_toggle (led_id_t mask);

#endif	/* __ASM_STATUS_LED_H__ */
