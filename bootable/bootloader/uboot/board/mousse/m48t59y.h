

#ifndef __M48_T59_Y_H
#define __M48_T59_Y_H


int m48_tod_init(void);

int m48_tod_set(int year,
		int month,
		int day,
		int hour,
		int minute,
		int second);

int m48_tod_get(int *year,
		int *month,
		int *day,
		int *hour,
		int *minute,
		int *second);

int m48_tod_get_second(void);

void m48_watchdog_arm(int usec);

#endif /*!__M48_T59_Y_H */
