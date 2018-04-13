// RealTimeClock.h

#ifndef _REALTIMECLOCK_h
#define _REALTIMECLOCK_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "Definitions.h"
#include <RTCDue.h>
#include <TimeLib.h>

extern long sensor_cycles;

class RealTimeClock : public RTCDue {

public:
	//Name
	String source;

	time_t timezone_offset;
	tmElements_t defaulttime;

	RealTimeClock(int src);

	void updateTime(tmElements_t timeset);
	void updateTime(time_t timestamp);
	void updateTime(int year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second);

	void setDefaultTime();

	time_t static toEpochTime(int year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second);

	//UI Output
	String static printDate(time_t timestamp);
	String static printTime(time_t timestamp);

	void syncSensorCycles();
	void syncSensorCycles(int year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute);
	void syncSensorCycles(time_t timestamp);
};
#endif

