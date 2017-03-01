// Trigger.h

#ifndef _TRIGGER_h
#define _TRIGGER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "Definitions.h"
#include <ArduinoJson.h>
#include "CurrentTime.h"
#include "Sensor.h"


//Globals
extern String debug;
extern CurrentTime currenttime;
extern Sensor *sensors[SENSNUMBER];
extern long sensor_cycles;



//Trigger is a pair of sensor values and thresholds linked by a boolean operator -> can be TRUE or FALSE, repeatly checked
class Trigger {
public:
	//Basic Information
	long id;

	bool active;

	//Trigger valid timeframe

	uint8_t start_second;
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
	//Threshold
	RelOp relop;
	int threshold;

	//Trigger repeat interval or trigger time windows for average
	Interval interval;

	//Constructor
	Trigger();

	//Update Values or Validity
	virtual bool checkState();

	virtual String getTitle();

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
	void incRelOp();
	void decRelOp();

	//Change Threshold
	void incThresh();
	void decThresh();

	//Toogle Activity
	void changeActive();

	
	//Generate Output for UI
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

	String getRelOp();
	String getThresh();

	//Settings
	void reset();

	//Serialization
	void serializeJSON(uint8_t cat, uint8_t id, char* json, size_t maxSize);
	bool deserializeJSON(JsonObject& data);
};

//Specialization of Trigger with predefined methods for RTC access
class TimeTrigger : public Trigger {
public:
	TimeTrigger(int id);
	bool checkState();
	String getTitle();
};

//Specialization of Trigger with predefined methods for generic sensors
class SensorTrigger : public Trigger {
public:
	Sensor *sens_ptr;

	//Ref to Sensor Object
	SensorTrigger(int id, Sensor *ptr);

	bool checkState();
	String getTitle();
};

#endif

