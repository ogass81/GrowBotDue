// CurrentTime.h

#ifndef _CURRENTTIME_h
#define _CURRENTTIME_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#define LEAP_YEAR(Y)     ( (Y>0) && !(Y%4) && ( (Y%100) || !(Y%400) ) )
static  const uint8_t monthDays[] = { 31,28,31,30,31,30,31,31,30,31,30,31 }; // API starts months from 1, this array starts from 0

#include <RTCDue.h>

class CurrentTime : public RTCDue {

public:
	String source;
	
	//Current Date
	uint8_t current_second;
	uint8_t current_minute;
	uint8_t current_hour;
	uint8_t current_day;
	uint8_t current_month;
	int current_year;
	

	CurrentTime(int source);
	int static epochTime(int year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second);


	void updateTimeObject();
	void updateRTCdefault();

	String createDate();
	String createTime();
	String getTitle();


	void incMinute();
	void decMinute();
	void incHour();
	void decHour();
	void incYear();
	void decYear();
	void incMonth();
	void decMonth();
	void incDay();
	void decDay();


	
	
};

#endif

