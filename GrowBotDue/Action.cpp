// 
// 
// 

#include "Action.h"


//ActionWrapper
template<class ActionType>
SimpleAction<ActionType>::SimpleAction(String title, ActionType * actionObj, void(ActionType::*cFunct)(), bool active)
{
	this->title = title;
	this->actionObject = actionObj;
	this->callback = cFunct;
	this->active = active;
}


template<class ActionType>
void SimpleAction<ActionType>::execute()
{
	if (this->active == true && this->actionObject != NULL && this->callback != NULL) {
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
	this->antaObject = aObject;
}

//All Types of Templates used:
template class SimpleAction<RelaisBoard>;
template class SimpleAction<DigitalSwitch>;