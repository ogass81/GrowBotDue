// 
// 
// 

#include "RealTimeClock.h"

RealTimeClock::RealTimeClock(int src)
	: RTCDue(src)
{
	source = "RTC";
	timezone_offset = 0;
}

void RealTimeClock::updateTime(tmElements_t timeset)
{
	time_t timestamp = makeTime(timeset);
	timestamp += timezone_offset;
	
	breakTime(timestamp, timeset);
		
	//Update RTC with Values from Data Model
	setDate(timeset.Day, timeset.Month, timeset.Year);
	setTime(timeset.Hour, timeset.Minute, timeset.Second);

	LOGDEBUG2(F("[RealTimeClock]"), F("setTime(timeset)"), F("OK: Updated RTC"), "", "", "");

	syncSensorCycles(timeset.Year, timeset.Month, timeset.Day, timeset.Hour, timeset.Minute);
}

void RealTimeClock::updateTime(time_t timestamp)
{
	tmElements_t timeset; 

	timestamp += timezone_offset;

	breakTime(timestamp, timeset);

	//Update RTC with Values from Data Model
	setDate(timeset.Day, timeset.Month, timeset.Year);
	setTime(timeset.Hour, timeset.Minute, timeset.Second);

	LOGDEBUG2(F("[RealTimeClock]"), F("setTime(timestamp)"), F("OK: Updated RTC"), "", "", "");

	syncSensorCycles(timeset.Year, timeset.Month, timeset.Day, timeset.Hour, timeset.Minute);
}

void RealTimeClock::updateTime(int year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second)
{
	time_t timestamp = toEpochTime(year, month, day, hour, minute, second) + timezone_offset;

	tmElements_t timeset;
	
	breakTime(timestamp, timeset);

	//Update RTC with Values from Data Model
	setDate(timeset.Day, timeset.Month, timeset.Year);
	setTime(timeset.Hour, timeset.Minute, timeset.Second);
	
	LOGDEBUG2(F("[RealTimeClock]"), F("updateTime(single values)"), F("OK: Updated RTC"), "", "", "");

	syncSensorCycles(timeset.Year, timeset.Month, timeset.Day, timeset.Hour, timeset.Minute);
}

void RealTimeClock::setDefaultTime()
{
	char month[12];

	const char *monthName[12] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun",  "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };

	uint8_t monthIndex = 0;


	sscanf(__TIME__, "%d:%d:%d", &defaulttime.Hour, &defaulttime.Minute, &defaulttime.Second);
	sscanf(__DATE__, "%s %d %d", month, &defaulttime.Day, &defaulttime.Year);

	for (monthIndex = 0; monthIndex < 12; monthIndex++) {
		if (strcmp(month, monthName[monthIndex]) == 0) break;
	}
	defaulttime.Month = monthIndex + 1;

	setDate(defaulttime.Day, defaulttime.Month, defaulttime.Year);
	setTime(defaulttime.Hour, defaulttime.Minute, defaulttime.Second);

	LOGDEBUG2(F("[RealTimeClock]"), F("setDefaultTime()"), String(defaulttime.Year), String(defaulttime.Month), String(defaulttime.Day), String(defaulttime.Hour));

	syncSensorCycles(defaulttime.Year, defaulttime.Month, defaulttime.Day, defaulttime.Hour, defaulttime.Minute);
}


time_t RealTimeClock::toEpochTime(int year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second)
{
	tmElements_t timeset;

	//Update Data Model with Values from input
	timeset.Year = year;
	timeset.Month = month;
	timeset.Day = day;

	timeset.Hour = hour;
	timeset.Minute = minute;
	timeset.Second = second;
	
	return makeTime(timeset);
}


String RealTimeClock::printDate(time_t timestamp)
{
	tmElements_t timeset;

	breakTime(timestamp, timeset);

	char dateStr[11];
	snprintf(dateStr, sizeof(dateStr), "%02d.%02d.%4d", timeset.Day, timeset.Month, timeset.Year);

	return String(dateStr);
}

String RealTimeClock::printTime(time_t timestamp)
{
	tmElements_t timeset;

	breakTime(timestamp, timeset);

	char timeStr[9];
	snprintf(timeStr, sizeof(timeStr), "%02d:%02d:%02d", timeset.Hour, timeset.Minute, timeset.Second);

	return String(timeStr);
}

void RealTimeClock::syncSensorCycles()
{
	tmElements_t timeset;

	//Update Data Model with Values from RTC
	timeset.Year = getYear();
	timeset.Month = getMonth();
	timeset.Day = getDay();

	timeset.Hour = getHours();
	timeset.Minute = getMinutes();
	timeset.Second = 0;

	sensor_cycles =  makeTime(timeset) / SENS_FRQ_SEC;
	LOGDEBUG2(F("[RealTimeClock]"), F("syncSensorCycles()"), F("OK: Set new sensor cycle"), String(sensor_cycles), "", "");
}

void RealTimeClock::syncSensorCycles(int year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute)
{
	sensor_cycles = toEpochTime(year, month, day, hour, minute, 0);
	LOGDEBUG2(F("[RealTimeClock]"), F("syncSensorCycles(single values)"), F("OK: Set new sensor cycle"), String(sensor_cycles), "", "");
}

void RealTimeClock::syncSensorCycles(time_t timestamp)
{
	sensor_cycles = timestamp / SENS_FRQ_SEC;
	LOGDEBUG2(F("[RealTimeClock]"), F("syncSensorCycles(timestamp)"), F("OK: Set new sensor cycle"), String(sensor_cycles), "", "");
}
