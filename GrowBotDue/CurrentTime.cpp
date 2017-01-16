// 
// 
// 

#include "CurrentTime.h"


CurrentTime::CurrentTime(int source)
	: RTCDue(source)
{
	this->source = "Internal RTC";
}

void CurrentTime::updateTimeObject() {
	this->current_second = getSeconds();
	this->current_minute = getMinutes();
	this->current_hour = getHours();
	this->current_day = getDay();
	this->current_month = getMonth();
	this->current_year = getYear();
}


void CurrentTime::updateRTCdefault() {
	char month[12];
	int year, day, hour, minute, second;

	const char *monthName[12] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun",  "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };

	uint8_t monthIndex = 1;


	sscanf(__TIME__, "%d:%d:%d", &hour, &minute, &second);
	sscanf(__DATE__, "%s %d %d", month, &day, &year);
	for (monthIndex = 0; monthIndex < 12; monthIndex++) {
		if (strcmp(month, monthName[monthIndex]) == 0) break;
	}


	setSeconds(second);
	setMinutes(minute);
	setHours(hour);
	setDay(day);
	setMonth(monthIndex+1);
	setYear(year);
}


String CurrentTime::createDate() {

	updateTimeObject();

	char timeStr[11];
	snprintf(timeStr, sizeof(timeStr), "%02d.%02d.%4d", current_day, current_month, current_year);
	return timeStr;
}

String CurrentTime::createTime() {

	updateTimeObject();

	char timeStr[6];
	snprintf(timeStr, sizeof(timeStr), "%02d:%02d", current_hour, current_minute);
	return timeStr;
}

String CurrentTime::getTitle()
{
	return String(this->source);
}

void CurrentTime::incMinute() {
	if (current_minute < 59) {
		current_minute++;
	}
	else current_minute = 0;

	setMinutes(current_minute);
}
void CurrentTime::decMinute() {
	if (current_minute > 0) {
		current_minute--;
	}
	else current_minute = 59;

	setMinutes(current_minute);
}
void CurrentTime::incHour() {
	if (current_hour < 23) {
		current_hour++;
	}
	else current_hour = 0;

	setHours(current_hour);
}
void CurrentTime::decHour() {
	if (current_hour > 0) {
		current_hour--;
	}
	else current_hour = 23;

	setHours(current_hour);
}
void CurrentTime::incYear() {
	if (current_year < 2027) {
		current_year++;
	}
	else current_year = 2017;

	setYear(current_year);
}
void CurrentTime::decYear() {
	if (current_year > 2017) {
		current_year--;
	}
	else current_year = 2027;

	setYear(current_year);
}
void CurrentTime::incMonth() {
	if (current_month < 12) {
		current_month++;
	}
	else current_month = 1;

	setMonth(current_month);
}
void CurrentTime::decMonth() {
	if (current_month > 1) {
		current_month--;
	}
	else current_month = 12;

	setMonth(current_month);
}
void CurrentTime::incDay() {
	if (current_month == 1 || current_month == 3 || current_month == 5 || current_month == 7 || current_month == 8 || current_month == 10 || current_month == 12) {
		if (current_day < 31) {
			current_day++;
		}
		else current_day = 1;
	}
	else if (current_month == 4 || current_month == 6 || current_month == 9 || current_month == 11) {
		if (current_day < 30) {
			current_day++;
		}
		else current_day = 1;
	}
	else if (current_month == 2 || (current_year % 4) == 0) {
		if (current_day < 29) {
			current_day++;
		}
		else current_day = 1;
	}
	else {
		if (current_day < 28) {
			current_day++;
		}
		else current_day = 1;

	}
	setDay(current_day);
}
void CurrentTime::decDay() {
	if (current_month == 1 || current_month == 3 || current_month == 5 || current_month == 7 || current_month == 8 || current_month == 10 || current_month == 12) {
		if (current_day > 1) {
			current_day--;
		}
		else current_day = 31;
	}
	else if (current_month == 4 || current_month == 6 || current_month == 9 || current_month == 11) {
		if (current_day > 1) {
			current_day--;
		}
		else current_day = 30;
	}
	else if (current_month == 2 || (current_year % 4) == 0) {
		if (current_day > 1) {
			current_day--;
		}
		else current_day = 29;
	}
	else {
		if (current_day > 1) {
			current_day--;
		}
		else current_day = 28;
	}
	setDay(current_day);
}