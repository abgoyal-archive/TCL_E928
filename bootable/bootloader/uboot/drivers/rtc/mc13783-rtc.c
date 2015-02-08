

#include <common.h>
#include <rtc.h>
#include <spi.h>
#include <fsl_pmic.h>

int rtc_get(struct rtc_time *rtc)
{
	u32 day1, day2, time;
	int tim, i = 0;

	do {
		day1 = pmic_reg_read(REG_RTC_DAY);
		if (day1 < 0)
			return -1;

		time = pmic_reg_read(REG_RTC_TIME);
		if (time < 0)
			return -1;

		day2 = pmic_reg_read(REG_RTC_DAY);
		if (day2 < 0)
			return -1;

	} while (day1 != day2 && i++ < 3);

	tim = day1 * 86400 + time;

	to_tm(tim, rtc);

	rtc->tm_yday = 0;
	rtc->tm_isdst = 0;

	return 0;
}

int rtc_set(struct rtc_time *rtc)
{
	u32 time, day;

	time = mktime(rtc->tm_year, rtc->tm_mon, rtc->tm_mday,
		      rtc->tm_hour, rtc->tm_min, rtc->tm_sec);
	day = time / 86400;
	time %= 86400;

	pmic_reg_write(REG_RTC_DAY, day);
	pmic_reg_write(REG_RTC_TIME, time);

	return 0;
}

void rtc_reset(void)
{
}
