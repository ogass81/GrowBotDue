// Trigger.h

#ifndef _TRIGGER_h
#define _TRIGGER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "Definitions.h"
#include "CurrentTime.h"
#include "Sensor.h"

//Globals
extern String debug;
extern CurrentTime currenttime;
extern Sensor *sensors[SENSNUMBER];


//Trigger is a pair of sensor values and thresholds linked by a boolean operator -> can be TRUE or FALSE, repeatly checked
class Trigger {
public:
	//Basic Information
	long id;

	bool active;

	//Trigger valid timeframe

	uint8_t start_minute;
	uint8_t start_hour;
	uint8_t start_day;
	uint8_t start_month;
	int start_year;

	uint8_t end_minute;
	uint8_t end_hour;
	uint8_t end_day;
	uint8_t end_month;
	int end_year;


	//Sensor and Thresholds
	float average;
	//Threshold
	BoolOp boolop;
	int treshhold;

	//Trigger repeat interval or trigger time windows for average
	Interval interval;

	//Constructor
	Trigger();

	//Ref
	virtual void setReference(Sensor *senspt);

	//Update Values or Validity
	virtual void updateAverage();
	virtual bool checkState();

	//UI Interface
	//Increase/Decrease Start / End Time
	void incStartDay();
	void decStartDay();
	void incStartMonth();
	void decStartMonth();
	void incStartYear();
	void decStartYear();
	void incStartHour();
	void decStartHour();
	void incStartMinute();
	void decStartMinute();
	void incEndDay();
	void decEndDay();
	void incEndMonth();
	void decEndMonth();
	void incEndYear();
	void decEndYear();

	//Increase /Decrease Interval
	void incInterval();
	void decInterval();

	//Change Boolean Operator
	void incBoolOp();
	void decBoolOp();

	//Change Threshold
	void incThresh();
	void decThresh();

	//Toogle Activity
	void changeActive();

	//Generate Output for UI
	virtual String getTitle();
	String getActive();

	String getStartDay();
	String getStartMonth();
	String getStartYear();
	String getStartHour();
	String getStartMinute();

	String getEndDay();
	String getEndMonth();
	String getEndYear();

	String getInterval();

	String getBoolOp();
	String getThresh();
};

//Specialization of Trigger with predefined methods for RTC access
class TimeTrigger : public Trigger {
public:
	CurrentTime *currenttime;

	TimeTrigger(int id, CurrentTime *currenttime);
	bool checkState();
	String getTitle();
};

//Specialization of Trigger with predefined methods for generic sensors
class SensorTrigger : public Trigger {
public:
	Sensor *sens_ptr;

	//Ref to Sensor Object
	SensorTrigger(int id, Sensor *ptr);

	void updateAverage();
	bool checkState();
	String getTitle();
};

#endif
