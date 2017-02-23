// 
// 
// 

#include "Action.h"


//ActionWrapper
template<class ActionType>
ActionWrapper<ActionType>::ActionWrapper(String title, ActionType * actionObj, void(ActionType::*actionFunc)(), bool active)
{
	this->title = title;
	this->actionObject = actionObj;
	this->callback = actionFunc;
	this->active = active;
}

template<class ActionType>
void ActionWrapper<ActionType>::execute()
{
	if (this->active == true && this->actionObject != NULL) {
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

//All Types of Templates used:
template class ActionWrapper<RelaisBoard>;