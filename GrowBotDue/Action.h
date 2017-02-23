// Action.h

#ifndef _ACTION_h
#define _ACTION_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Relais.h"

//Abstract Class for Actions
class Action {
public:
	String title;
	bool active;

	virtual void execute();
};

//Instance of Action Class: Used to wrap different callback functions from different classes -> template
template <class ActionType>
class ActionWrapper : public Action {
public:
	ActionType *actionObject = NULL;
	void (ActionType::*callback)();

	ActionWrapper(String tile, ActionType *actionObj, void (ActionType::*actionFunc)(), bool active = true);

	void execute();
};
#endif

