//
// WebServ
//
// Created by Артур Лутфуллин on 07.02.2021.
// Copyright (c) 2021 Артур Лутфуллин. All right reserved. 
//

#include <iostream>
#include <sys/time.h>
#include <ctime>

void ft_get_year(tm &timeinfo, long time, int& leap_count) {
	int year = 1970;
	int dayCount = time / 3600 / 24;
	for (; dayCount >= 365; ++year) {
		if (year % 4 == 0) {
			dayCount -= 366;
			++leap_count;
		}
		else
			dayCount -= 365;
	}
	timeinfo.tm_year = year;
}

void ft_get_month(tm &timeinfo, long time, int& leap_count) {
	int year = 1970;
	int months = 0;
	int dayCount = (time / 3600 / 24) - leap_count;
	dayCount -= (timeinfo.tm_year - 1970) * 365;
	std::cout << dayCount << std::endl;
}

void ft_get_day(tm &timeinfo, long time) {

}

void ft_get_day_of_week(tm &timeinfo, long time) {

}

void ft_get_hour(tm &timeinfo, long time) {

}

void ft_get_minute(tm &timeinfo, long time) {

}

void ft_get_second(tm &timeinfo, long time) {

}

void ft_get_time(tm& timeinfo, long time) {
	int leap_count = 0;
	ft_get_year(timeinfo, time, leap_count);
	ft_get_month(timeinfo, time, leap_count);
	std::cout << "Leap Year Count: " << leap_count << std::endl;
	std::cout << "Year: "<< timeinfo.tm_year << std::endl;

}

int main() {
	struct timeval time;
	struct tm timeinfo;


	gettimeofday(&time, NULL);
	ft_get_time(timeinfo, time.tv_sec + (time.tv_usec / 1000000));
}