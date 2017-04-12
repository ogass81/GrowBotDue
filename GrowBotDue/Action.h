// Action.h

#ifndef _ACTION_h
#define _ACTION_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <ArduinoJson.h>
#include "Relais.h"
#include "DigitalSwitch.h"
#include "RCSocketController.h"

//Abstract Class for Actions
class Action {
public:
	String name;
	bool visible;
	//Pointer to Action that does the opposite
	Action *antaObject = NULL;

	void setAntagonist(Action *aObject);
	virtual void execute();
	//Serialize
	virtual void serializeJSON(uint8_t id, char* json, size_t maxSize);

	//UI Output
	String getTitle();
};
// Wrapper for Simple Actions that include only one Callback Function
template <class ActionType>
class SimpleAction : public Action {
public:
	ActionType *actionObject = NULL;
	void (ActionType::*callback)();
	
	SimpleAction(String title, ActionType *actionObj, void (ActionType::*cFunct)(), bool visible = false);

	//Serialize
	void serializeJSON(uint8_t id, char* json, size_t maxSize);

	void execute();
};

template <class ActionType>
class ParameterizedSimpleAction : public Action {
public:
	ActionType *actionObject = NULL;
	void (ActionType::*callback)(int);
	int parameter;

	ParameterizedSimpleAction(String title, ActionType *actionObj, void (ActionType::*cFunct)(int), int par, bool visible = false);

	//Serialize
	void serializeJSON(uint8_t id, char* json, size_t maxSize);

	void execute();
};
#endif
