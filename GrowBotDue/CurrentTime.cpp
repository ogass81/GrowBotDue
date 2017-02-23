// 
// 
// 

#include "CurrentTime.h"


CurrentTime::CurrentTime(int source)
	: RTCDue(source)
{
	this->source = "RTC";
}

int CurrentTime::epochTime(int year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second)
{
	int seconds = 0;

	// seconds from 1970 till 1 jan 00:00:00 of the given year
	seconds = year * 365 * 24 * 60 * 60;
	for (int i = 0; i < year; i++) {
		if (LEAP_YEAR(i)) {
			seconds += 24 * 60 * 60;   // add extra days for leap years
		}
	}

	// add days for this year, months start from 1
	for (int i = 1; i < month; i++) {
		if ((i == 2) && LEAP_YEAR(year)) {
			seconds += 24 * 60 * 60 * 29;
		}
		else {
			seconds += 24 * 60 * 60* monthDays[i - 1];  //monthDay array starts from 0
		}
	}
	seconds += (day - 1) * 24 * 60 * 60;
	seconds += hour * 60 * 60;
	seconds += minute * 60;
	seconds += second;

	return (int)seconds;
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
	if (this->current_minute < 59) {
		this->current_minute++;
	}
	else this->current_minute = 0;

	setMinutes(this->current_minute);
}
void CurrentTime::decMinute() {
	if (this->current_minute > 0) {
		this->current_minute--;
	}
	else this->current_minute = 59;

	setMinutes(this->current_minute);
}
void CurrentTime::incHour() {
	if (this->current_hour < 23) {
		this->current_hour++;
	}
	else this->current_hour = 0;

	setHours(this->current_hour);
}
void CurrentTime::decHour() {
	if (this->current_hour > 0) {
		this->current_hour--;
	}
	else this->current_hour = 23;

	setHours(this->current_hour);
}
void CurrentTime::incYear() {
	if (this->current_year < 2027) {
		this->current_year++;
	}
	else this->current_year = 2017;

	setYear(this->current_year);
}
void CurrentTime::decYear() {
	if (this->current_year > 2017) {
		this->current_year--;
	}
	else this->current_year = 2027;

	setYear(this->current_year);
}
void CurrentTime::incMonth() {
	if (this->current_month < 12) {
		this->current_month++;
	}
	else this->current_month = 1;

	setMonth(this->current_month);
}
void CurrentTime::decMonth() {
	if (this->current_month > 1) {
		this->current_month--;
	}
	else this->current_month = 12;

	setMonth(this->current_month);
}
void CurrentTime::incDay() {
	if (this->current_month == 1 || this->current_month == 3 || this->current_month == 5 || this->current_month == 7 || this->current_month == 8 || this->current_month == 10 || this->current_month == 12) {
		if (this->current_day < 31) {
			this->current_day++;
		}
		else this->current_day = 1;
	}
	else if (this->current_month == 4 || this->current_month == 6 || this->current_month == 9 || this->current_month == 11) {
		if (this->current_day < 30) {
			this->current_day++;
		}
		else this->current_day = 1;
	}
	else if (this->current_month == 2 || (this->current_year % 4) == 0) {
		if (this->current_day < 29) {
			this->current_day++;
		}
		else this->current_day = 1;
	}
	else {
		if (this->current_day < 28) {
			this->current_day++;
		}
		else this->current_day = 1;

	}
	setDay(this->current_day);
}
void CurrentTime::decDay() {
	if (this->current_month == 1 || this->current_month == 3 || this->current_month == 5 || this->current_month == 7 || this->current_month == 8 || this->current_month == 10 || this->current_month == 12) {
		if (this->current_day > 1) {
			this->current_day--;
		}
		else this->current_day = 31;
	}
	else if (this->current_month == 4 || this->current_month == 6 || this->current_month == 9 || this->current_month == 11) {
		if (this->current_day > 1) {
			this->current_day--;
		}
		else this->current_day = 30;
	}
	else if (this->current_month == 2 || (this->current_year % 4) == 0) {
		if (this->current_day > 1) {
			this->current_day--;
		}
		else this->current_day = 29;
	}
	else {
		if (this->current_day > 1) {
			this->current_day--;
		}
		else this->current_day = 28;
	}
	setDay(this->current_day);
}