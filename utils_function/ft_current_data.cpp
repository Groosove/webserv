//
// WebServ
//
// Created by Артур Лутфуллин on 07.02.2021.
// Copyright (c) 2021 Артур Лутфуллин. All right reserved. 
//

#include <iostream>
#include <sys/time.h>
#include <ctime>

int ft_get_day_of_week(tm &timeinfo) {
	int last_number = timeinfo.tm_year % 100;
	int year_code = (6 + last_number + last_number / 4) % 7;
	int month = timeinfo.tm_mon + 1;
	int month_code;
	if (month == 1 || month == 10)		month_code = 1;
	else if (month == 5) 				month_code = 2;
	else if (month == 8)				month_code = 3;
	else if (month == 6)				month_code = 5;
	else if (month == 12 || month == 9)	month_code = 6;
	else if (month == 7 || month == 4)	month_code = 0;
	else								month_code = 4;
	int day_of_week = (timeinfo.tm_mday + month_code + year_code) % 7;
	if (day_of_week == 0 || day_of_week == 1)
		day_of_week = (day_of_week == 0) ? 6 : 0;
	return day_of_week;
}

void ft_get_date(tm &timeinfo, long time) {
	int year = 70;
	int number_month = 1;
	timeinfo.tm_min = time % 3600 / 60;
	timeinfo.tm_sec = time % 3600 % 60;
	time /= 3600;
	timeinfo.tm_hour = time % 24 + 3;
	if (timeinfo.tm_hour >= 24) { timeinfo.tm_hour -= 24; ++timeinfo.tm_mday; }
	time = (time - (timeinfo.tm_hour - 3)) / 24 + 1;
	for (; time >= 365; ++year)
		time -= (year % 4 == 0) ? 366 : 365;
	timeinfo.tm_year = year;
	bool leap = timeinfo.tm_year % 4 == 0;
	for (; time >= 28 || (time >= 29 && leap); ++number_month)
		if (number_month == 2)
			time -= (leap) ? 29 : 28;
		else if (number_month <= 8)
			time -= (number_month % 2 != 0) ? 31 : 30;
		else
			time -= (number_month % 2 != 0) ? 30 : 31;
	timeinfo.tm_mon = number_month - 1;
	timeinfo.tm_mday = time;
	timeinfo.tm_wday = ft_get_day_of_week(timeinfo);
}

std::string ft_get_time() {
	struct timeval time;
	struct tm timeinfo;
	char buff[100];

	gettimeofday(&time, NULL);
	ft_get_date(timeinfo, time.tv_sec + (time.tv_usec / 1000000));
	strftime(buff, 100, "%a,  %d %b %Y %X GTM", &timeinfo);
	return std::string(buff);
}