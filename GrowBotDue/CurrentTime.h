// CurrentTime.h

#ifndef _CURRENTTIME_h
#define _CURRENTTIME_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

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

