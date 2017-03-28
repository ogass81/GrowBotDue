// Action.h

#ifndef _ACTION_h
#define _ACTION_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Relais.h"
#include "DigitalSwitch.h"

//Abstract Class for Actions

class Action {
public:
	String title;
	bool active;

	Action *antaObject = NULL;
	
	String getTitle();
	void setAntagonist(Action *aObject);
	virtual void execute();

};
// Wrapper for Simple Actions that include only one Callback Function
template <class ActionType>
class SimpleAction : public Action {
public:
	ActionType *actionObject = NULL;
	void (ActionType::*callback)();
	
	SimpleAction(String title, ActionType *actionObj, void (ActionType::*cFunct)(), bool active = true);


	void execute();
};


#endif
