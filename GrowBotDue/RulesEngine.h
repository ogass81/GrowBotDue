// RulesEngine.h

#ifndef _RULESENGINE_h
#define _RULESENGINE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "Definitions.h"
#include "Sensor.h"
#include "CurrentTime.h"

extern String debug;
extern CurrentTime currenttime;
extern Sensor *sensors[SENSNUMBER];

enum BoolOp { SMALLER, EQUAL, GREATER };
enum Interval { QUARTER, HALF, ONE, TWO, THREE, FOUR, SIX, TWELVE, DAILY, BIDAILY, WEEKLY, BIWEEKLY };

//Abstract Class for Actions
class Action {
public:
	String title;
	bool active;

	virtual void execute();
};

//Instance of Action Class: Used to wrap different callback functions from different classes -> template
template <class ActionType>
class ActionWrapper : Action {
public:
	ActionType *actionObject = NULL;
	void (ActionType::*callback)();

	ActionWrapper(String tile, ActionType *actionObj, void (ActionType::*actionFunc)(), bool active = true);

	void execute();
};

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

//Rulesets are Touples of Triggers, Boolean Operators. If the whole expression is true the assigned action (callback function) is executed
class RulesSet {
public:
	String title PROGMEM;
	bool active;

	Trigger *assignedTrigger[3];
	BoolOp *assignedBoolOp[3];
	Action *assignedAction;

	RulesSet();

	bool checkState();
	void executeAction();
};

//Overall class - creates and references all triggers, rulessets and action objects
class ActionHandler {
public:
	Trigger *trigger[TRIGCAT][TRIGNUMBER];

	RulesSet *rulesets[RULES];

	Action *actions[ACTIONS];

	uint8_t trigger_cat_pointer = 0;
	uint8_t trigger_pointer = 0;
	uint8_t rulesets_pointer = 0;

	ActionHandler();

	//UI Interface
	void incCurrentStartDay();
	void decCurrentStartDay();
	void incCurrentStartMonth();
	void decCurrentStartMonth();
	void incCurrentStartYear();
	void decCurrentStartYear();
	void incCurrentStartHour();
	void decCurrentStartHour();
	void incCurrentStartMinute();
	void decCurrentStartMinute();
	void incCurrentEndDay();
	void decCurrentEndDay();
	void incCurrentEndMonth();
	void decCurrentEndMonth();
	void incCurrentEndYear();
	void decCurrentEndYear();

	void incCurrentInterval();
	void decCurrentInterval();

	void incCurrentBoolOp();
	void decCurrentBoolOp();
	void incCurrentThresh();
	void decCurrentThresh();

	void changeCurrentActive();


	String getCurrentTitle();
	String getCurrentActive();

	String getCurrentStartDay();
	String getCurrentStartMonth();
	String getCurrentStartYear();
	String getCurrentStartHour();
	String getCurrentStartMinute();

	String getCurrentEndDay();
	String getCurrentEndMonth();
	String getCurrentEndYear();

	String getCurrentInterval();
	String getCurrentBoolOp();
	String getCurrentThresh();


	void setTriggerCatPointer(int category);
	void incTriggerPointer();
	void decTriggerPointer();

	void incRuleSetsPointer();
	void decRuleSetsPointer();
};



#endif

