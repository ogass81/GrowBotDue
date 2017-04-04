// 
// 
// 

#include "Action.h"


template<class ActionType>
SimpleAction<ActionType>::SimpleAction(String name, ActionType * actionObj, void(ActionType::*cFunct)(), bool active)
{
	title = name;
	actionObject = actionObj;
	callback = cFunct;
	active = active;
}

template<class ActionType>
void SimpleAction<ActionType>::execute()
{
	if (active == true && actionObject != NULL && callback != NULL) {
		LOGDEBUG(F("[Action]"), F("execute()"), F("OK: Execute Action"), title, "", "");
		(actionObject->*callback)();
	}
}

void Action::execute()
{
}

String Action::getTitle()
{
	return String(title);
}

void Action::setAntagonist(Action * aObject)
{
	LOGDEBUG(F("[Action]"), F("setAntagonist()"), F("OK: Setting Antagonist Object"), "", "", "");
	antaObject = aObject;
}

//All Types of Templates used:
template class SimpleAction<RelaisBoard>;
template class SimpleAction<DigitalSwitch>;